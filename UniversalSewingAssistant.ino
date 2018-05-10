

#include "ap_autoStart.h"
#include "pinsx.h"

#include "syncx.h"
///#include "autoWheelcutter.h"
#include "utilityFunction.h"

#include "Nextion.h"
#include <ChibiOS_ARM.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "statements.h"
//#include "display.h"
#include "RTSOdataShare.h"
#include "analogProcessing.h"
#include "Interrupt_service_rootings.h"
#include "smartGlow.h"
#include "cycleTimer.h"
#include "autoCreasing.h"
#include "sdloader.h"
#include "OneButton.h"
#include "utilityFunction.h"
#include "sewing_machine_parameter_loader.h"

#include "smart_paddle_sensor.h"
#include <SoftwareSerial.h>

SoftwareSerial ESPSerial(20, 21); // RX, TX



OneButton button(creasingIn, true);
SPI_PROFILE_CATOGERY spi_vs_speed_profile_type_saving = DEFAULT_PROFILE;
SPI_PROFILE_CATOGERY spi_vs_speed_profile_type_auto_pilot = DEFAULT_PROFILE;
//eMotor_type Active_motor_type;
#include <SD.h>
#include <SPI.h>

const int chipSelect = BUILTIN_SDCARD;
/*#define BLUE 2
#define RED 4
#define GREEN 3*/
#define BLUE 3
#define RED 4
#define GREEN 2
Adafruit_MCP4725 dac;
smartGlow RGB_leds(RED,GREEN,BLUE);
cycleTimer runTimer(100,250);
autoCreasing creaZer;
AutoCutter WheelCutter(RLY2);
SmartPaddle primery_sensor(analogPin0);
SmartPaddle secondry_sensor(analogPin1);
autoPilot MyAutoPilot(AP_AUTO_START_SENS);


syncx defaultProfileEvent("USADATA/SPI/DEFAULT/SVC_DF.TXT");
syncx neckProfileEvent("USADATA/SPI/DEFAULT/SVC_1.TXT");
syncx armLProfileEvent("USADATA/SPI/DEFAULT/SVC_2.TXT");
syncx armRProfileEvent("USADATA/SPI/DEFAULT/SVC_3.TXT");

syncx default_trim_Event("USADATA/SPI/DEFAULT/SVFT_DF.TXT");
syncx neck_trim_Event("USADATA/SPI/DEFAULT/SVFT_1.TXT");
syncx armL_trim_Event("USADATA/SPI/DEFAULT/SVFT_2.TXT");
syncx armR_trim_Event("USADATA/SPI/DEFAULT/SVFT_3.TXT");

syncx default_foot_Event("USADATA/SPI/DEFAULT/SVF_DF.TXT");
syncx neck_foot_Event("USADATA/SPI/DEFAULT/SVF_1.TXT");
syncx armL_foot_Event("USADATA/SPI/DEFAULT/SVF_2.TXT");
syncx armR_foot_Event("USADATA/SPI/DEFAULT/SVF_3.TXT");



syncx* myCutterEvent = &defaultProfileEvent;
syncx* my_trim_Event = &default_trim_Event;
syncx* my_foot_Event = &default_foot_Event;


// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (8)

//------------------------------------------------------------------------------
// Thread 1, turn the LED off when signalled by thread 2.

// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd1_main, 2560);

static THD_FUNCTION(Thd1_main, arg) {
	
	sys_dbSerialPrintln("Looking for directories..");
	sdloader::format_sd_file_structure();
	Serial.print("Loading Files..");
	SD_OPERATION_RESULTS result = sdloader :: loading_profile(DACData, SIZE_OF_DAC_DATA_ARRY, spi_vs_speed_profile_type_auto_pilot, SPI_speed_profil_length_SH);	


	if(result == NO_SD)
	{
		Serial.println("SD_NOT_FOUND");
	}
	else if(result == FILE_NOT_FOUND)
	{
		Serial.println("FILE_NOT_FOUND");
	}
	else if (result == ERROR_OPENNING)
	{
		Serial.println("ERROR_OPENNING");
	}

	else if (result == SD_OK)
	{
		SPI_speed_profil_length_SH = getTeachProfile_length(DACData,SIZE_OF_DAC_DATA_ARRY);
		Serial.println("SD_OK");
	}
	else if (result == LOADING_COMPLETE)
	{
		SPI_speed_profil_length_SH = getTeachProfile_length(DACData,SIZE_OF_DAC_DATA_ARRY);
		Serial.println("LOADING_COMPLETE");
	}
	if ((result == LOADING_COMPLETE)||(result == SD_OK))
	{
		loading_parameters_from_SD();
		//sdloader ::load_param_value_from_sd_file("USADATA\SYSTEM\sys.txt", "active_machine_type", motor_type_id);
		//sdloader :: loading_machine_para(CALIB_ideal_DAC_value,CALIB_MAX_RPM_DAC_value,CALIB_AuroPilot_DAC_ideal_value,Active_motor_type_struct.motor_foot_lifting_vale,Active_motor_type_struct.motor_trimmer_activation_value)
	}
	
	while (1)
	{
		mainTask();
		chThdSleepMicroseconds(1);
	}
	
}
//------------------------------------------------------------------------------
// Thread 2, turn the LED on and signal thread 1 to turn the LED off.

// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd2_sysBreathing, 64);

static THD_FUNCTION(Thd2_sysBreathing, arg) {
pinMode(BREATHING_LED,OUTPUT);
digitalWrite(BREATHING_LED,LOW);

while (1)
{
	chThdSleepMilliseconds(100);
	digitalWrite(BREATHING_LED,HIGH);
	chThdSleepMilliseconds(100);
	digitalWrite(BREATHING_LED,LOW);
}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Thread 4, Display

// 128 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd4_display, 10120);

static THD_FUNCTION(Thd4_display, arg) {
	
	registerNextionEventsCallbacks();
	while (1) {		
		 
		  chThdSleepMicroseconds(1);
		  display_main();
	}
}
//------------------------------------------------------------------------------
// Thread 5, serial event handling 

// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd5_Serial, 2560);
static THD_FUNCTION(Thd5_Serial, arg){
	 
	while (1)
	{
		chThdSleepMicroseconds(1);
		serialEventRTOS();
		serialPrinting();		
	}
}


// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd6_analogCh1, 1024);
static THD_FUNCTION(Thd6_analogCh1, arg){
	unsigned int sampaleOfZero_received_time, sampaleOf100_recevied_time, sampaleOf900_recevied_time;
	unsigned int stage = 0;

	unsigned int TH_ch1_detection_min_threshold = 100;
	unsigned int TI_first_pulse_registering_delay = 200;//ms
	unsigned int TI_second_puls_stating_delay = 200;// ms default	
	unsigned int TH_ch1_trim_detection_threshold = 900;
	unsigned int TI_second_pulse_rising_delay = 500;
	unsigned int TI_second_pulse_rising_debounce = 250;
	pinMode(TRIM,OUTPUT);
	pinMode(FOOT,OUTPUT);
	secondry_sensor.attach_click(foot_activate);
	secondry_sensor.attach_Dclick(trim_activate);
	secondry_sensor.attach_stopclick(ideal);

	while (1)
	{
	// copy data in a safe area
		chMtxLock(&Foot_trim_data);
		TH_ch1_detection_min_threshold = TH_ch1_detection_min_threshold_GLOBAL;
		TI_first_pulse_registering_delay = TI_first_pulse_registering_delay_GLOBAL;//ms
		TI_second_puls_stating_delay = 350;// TI_second_puls_stating_delay_GLOBAL;// ms default
		TH_ch1_trim_detection_threshold = TH_ch1_trim_detection_threshold_GLOBAL;
		TI_second_pulse_rising_delay = TI_second_pulse_rising_delay_GLOBAL;
		TI_second_pulse_rising_debounce = TI_second_pulse_rising_debounce_GLOBAL;
		chMtxUnlock(&Foot_trim_data);
		chThdSleepMicroseconds(1);
		secondry_sensor.setEvent_para(TH_ch1_trim_detection_threshold, TI_first_pulse_registering_delay,TI_second_puls_stating_delay,TH_ch1_trim_detection_threshold,
		TI_second_pulse_rising_delay,TI_second_pulse_rising_debounce );


		 long AN_CH1_sensor_data_RAW_THD = 0, AN_CH1_sensor_data_AVR_THD = 0;
		 unsigned long now; // current (relative) time in msecs.
		 secondry_sensor.process_paddleSensorAnalogDataCH0(AN_CH1_sensor_data_RAW_THD, AN_CH1_sensor_data_AVR_THD, now);
		 


		 unsigned int CH1_AVRanalogValue = AN_CH1_sensor_data_RAW_THD;	
		 
		ePADDLE_EVENTS event = secondry_sensor.event_detecting(AN_CH1_sensor_data_RAW_THD, now);
		 
	}
}

// Thread 7 channel 0 proccessing 
// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd7_analogCh0, 512);

static THD_FUNCTION(Thd7_analogCh0, arg){
	
	pinMode(LED,OUTPUT);
	while (1)
	{
		chThdSleepMicroseconds(1);
		//***************************************************************
		long AN_CH0_sensor_data_RAW_THD = 0, AN_CH0_sensor_data_AVR_THD = 0;
		unsigned long now;
		primery_sensor.process_paddleSensorAnalogDataCH0(AN_CH0_sensor_data_RAW_THD, AN_CH0_sensor_data_AVR_THD, now);
		chMtxLock(&ADC_DATA_SH);
		AN_CH0_sensor_data_AVR_GLOB = AN_CH0_sensor_data_AVR_THD;
		AN_CH0_sensor_data_RAW_GLOB = AN_CH0_sensor_data_RAW_THD;	
		chMtxUnlock(&ADC_DATA_SH);
		//***************************************************************
		//int tempAnalog_value_ch0 = paddleSensorAnalogDataProcessCH0();
		
		unsigned int _event_ch0 = getEventofAnalogCH0(AN_CH0_sensor_data_AVR_THD);
		if (_event_ch0)
		{
			
			setEvent_ch0(_event_ch0);
		}
		// map analog value for display paddling progress bar
		chMtxLock(&General_LCDcommunication);
		trueDACout_forDisplay_SH =map(AN_CH0_sensor_data_AVR_THD,analogLowCH0,analogHighCH0,0,100);		
		chMtxUnlock(&General_LCDcommunication);		
	}
}


// Thread 8 channel creasing
// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd8_creasing, 1024);

static THD_FUNCTION(Thd8_creasing, arg){
	pinMode(CREASING_OUT,OUTPUT);
	digitalWrite(CREASING_OUT,LOW);
	while (1)
	{
		button.tick();
		chThdSleepMicroseconds(1);
				
	}
}

//------------------------------------------------------------------------------
// Thread 2, smartGlow.

// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd9_smartGlow, 512);

static THD_FUNCTION(Thd9_smartGlow, arg) {
	boolean prev_machine_status = 0;
	String buff = "";
	RGB_leds.set_smartGlow(INIT);
	while (1)
	{
		chThdSleepMicroseconds(1);
		RGB_leds.smartGlowRun();
		runTimer.cycleTimerRun(SPIdetect);
		//runTimer.security_run_check();
		boolean machine_status = runTimer.getMachineStatus();
		//Serial.println(machine_status);
		if (machine_status !=prev_machine_status)
		{
			
			prev_machine_status = machine_status;
			if (machine_status)
			{
				Serial.println("SEWING");
				unsigned long waiting_time = ( runTimer.getMachineStartedTime_micros() - runTimer.getMachineStopedTime_micros());
				buff = String("waiting_end=");
				buff += String(waiting_time);
				//sprintf(buff, "sewing_end=%d", waiting_time);
				Serial.println(buff.c_str());
				ESPSerial.println(buff.c_str());

			}
			else{
				Serial.println("END");
				unsigned long sew_time = ( runTimer.getMachineStopedTime_micros() - runTimer.getMachineStartedTime_micros());
				Serial.println(sew_time);
				
				buff = String("sewing_end=");
				buff += String(sew_time);
				//sprintf(buff, "sewing_end=%d", sew_time);
				Serial.println(buff.c_str());
				ESPSerial.println(buff.c_str());
			}
		}
		
	}
	
}

//------------------------------------------------------------------------------
// Thread 10, Audio

// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd10_audio, 64);

static THD_FUNCTION(Thd10_audio, arg) {
pinMode(BUZZER,OUTPUT);	
digitalWrite(BUZZER,LOW);	

	while (1)
	{
		chThdSleepMicroseconds(1);
		// wait for event
		chBSemWait(&buzzerSem);
		digitalWrite(BUZZER,HIGH);
		chThdSleepMilliseconds(50);
		digitalWrite(BUZZER,LOW);	
		//chThdSleepMilliseconds(100);	
		
	}
	
}

// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd11_paddlEvents, 512);

static THD_FUNCTION(Thd11_paddlEvents, arg) {
	pinMode(STEPPER_PULSE,OUTPUT);
	digitalWrite(STEPPER_PULSE,HIGH);
	while (1)
	{
		chThdSleepMicroseconds(1);
		chMtxLock(&au_feeder_data);
		unsigned int  pulse_width_THD = pulse_width;		
		chMtxUnlock(&au_feeder_data);
		// wait for event
		chBSemWait(&isrStepperSync);
		
		// print elapsed time
		uint32_t t = micros();
	/*	Serial.print("Handler: ");
		Serial.println(t - tIsr);
		Serial.println("pulse width ");
		Serial.print(pulse_width);*/	
		digitalWrite(STEPPER_PULSE,LOW);
		delay(pulse_width);
		digitalWrite(STEPPER_PULSE,HIGH);
}
}

//------------------------------------------------------------------------------
// Thread , Sensor scaning

// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd12_Sensor, 128);
static THD_FUNCTION(Thd12_Sensor, arg){
	boolean lastButtonState = HIGH;
	boolean buttonState = LOW;
	//chThdSleepMilliseconds(3000);
	

	while (1)
	{
		chThdSleepMicroseconds(1);
		
		buttonState=digitalRead(END_CUTTER_SENS);
		if (buttonState==LOW)
		{
		Serial.println("off");
		}
		
		
		// compare the buttonState to its previous state
		if (buttonState != lastButtonState){
			// if the state has changed, increment the counter
			if (buttonState == LOW){
				// if the current state is HIGH then the button went from off to on:
				Serial.println("on");		
				if (getState_foot())
				{	
					if (!getState_trim())
					{
						set_endCutter_EN(true);
					}
				}
				delay(50);
				
				
				
				} else {
				// if the current state is LOW then the button went from on to off:
				Serial.println("off");
			}
			// Delay a little bit to avoid bouncing
			delay(50);
		}
		// save the current state as the last state, for next time through the loop
		lastButtonState = buttonState;
		
	}
}

static THD_WORKING_AREA(waTrim,128);
static THD_FUNCTION(Trim, arg){

	chThdSleepMicroseconds(3000);
	while (1)
	{
		chMtxLock(&au_feeder_data);
		unsigned int au_feeder_cutter_act_delay_THD = au_feeder_cutter_act_delay;
		unsigned int au_feeder_cutting_delay_THD = au_feeder_cutting_delay;
		chMtxUnlock(&au_feeder_data);
		chThdSleepMicroseconds(1);
		//if ((get_endCutter_EN()&&(getState_foot())))
		if(get_endCutter_EN())
		{
			set_endCutter_EN(false);
			//chMtxLock(&VANTAGE_MC_MASTER_EN);
			//vantage_machine.set_Voltage(ISM_IDEAL_TRUE_VOLTAGE_3_L,false);
			
				Serial.println("END CUTTER");
				if (au_feeder_cutter_act_delay){
				chThdSleepMilliseconds(au_feeder_cutter_act_delay_THD);}
				digitalWrite(END_CUTTER_OUT,HIGH);
				if(au_feeder_cutting_delay){
				chThdSleepMilliseconds(au_feeder_cutting_delay_THD);}
				digitalWrite(END_CUTTER_OUT,LOW);
				//chThdSleepMilliseconds(1000);			
			//chMtxUnlock(&VANTAGE_MC_MASTER_EN);
		}
	}
}

void system_initialization(){
	// put your setup code here, to run once:
	nexInit();
	//dbSerialPrintln("setup done");
//	Serial.begin(115200);
	 // Open serial communications and wait for port to open:
	 ESPSerial.begin(115200);
	ESPSerial.println("Hi");
	//dac.begin(0x63);
	Wire.begin();
	byte dac_address; 
	boolean scan_result = I2C_scane(dac_address);
	Serial.println(dac_address,HEX);
	if (!scan_result)
	{
		Serial.println("NO DAC module found!");
		LCD_Event_dac_module = false;
	}
	else{
		LCD_Event_dac_module = true;
	}
	
	dac.begin(0x60);
	analogWriteResolution(12);
	
	Serial.print("Initializing SD card...");
	
	SD_OPERATION_RESULTS sd_state = sdloader::SD_initilization();
	if (sd_state == NO_SD)
	{
		LCD_Event_sd = false;
		Serial.println("Insert SD card");
	}
	else{ LCD_Event_sd = true;
	}
	button.attachClick(mechanical_sw_mode_creasing_out);
	
	button.attachDoubleClick(mechanical_button_mode_chenge);

	defaultProfileEvent.setOn_CallBack(cutter_on);
	defaultProfileEvent.setOff_CallBack(cutter_off);

	neckProfileEvent.setOn_CallBack(cutter_on);
	neckProfileEvent.setOff_CallBack(cutter_off);

	armLProfileEvent.setOn_CallBack(cutter_on);
	armLProfileEvent.setOff_CallBack(cutter_off);

	armRProfileEvent.setOn_CallBack(cutter_on);
	armRProfileEvent.setOff_CallBack(cutter_off);

	//foot trim
	default_trim_Event.setOn_CallBack(trim_activate);
	neck_trim_Event.setOn_CallBack(trim_activate);	
	armL_trim_Event.setOn_CallBack(trim_activate);
	armR_trim_Event.setOn_CallBack(trim_activate);	

	default_foot_Event.setOn_CallBack(foot_activate);
	neck_foot_Event.setOn_CallBack(foot_activate);
	armL_foot_Event.setOn_CallBack(foot_activate);
	armR_foot_Event.setOn_CallBack(foot_activate);
	
		

	// auto pilot
	MyAutoPilot.attach_Dclick(buzze_on);
	MyAutoPilot.attach_stopclick(buzze_off);
	}

void cutter_on(){ WheelCutter.Activate(); Serial.println("end cutter activation call back function");}
void cutter_off(){WheelCutter.Deactivate(); Serial.println("end cutter deactivation call back function");}

void mechanical_sw_mode_ap_wating_scape(){
	MyAutoPilot.set_state_external_trigger(true);
}

void setup() {
	
	pinMode(interruptPin,INPUT_PULLUP);
	pinMode(creasingIn,INPUT_PULLUP);
	pinMode(END_CUTTER_SENS,INPUT_PULLUP);
	pinMode(END_CUTTER_OUT,OUTPUT);
	analogWriteResolution(12);
	digitalWrite(END_CUTTER_OUT,LOW);
	system_initialization();	
	chBegin(chSetup);
	// chBegin never returns, main thread continues with mainThread()
	while(1) {
	}
}
//------------------------------------------------------------------------------
// main thread runs at NORMALPRIO
void chSetup() {

	// start blink thread
	chThdCreateStatic(waThd1_main, sizeof(waThd1_main), HIGHPRIO + 10, Thd1_main, NULL);

	chThdCreateStatic(waThd2_sysBreathing, sizeof(waThd2_sysBreathing),NORMALPRIO + 1, Thd2_sysBreathing, NULL);
	 
	 chThdCreateStatic(waThd4_display, sizeof(waThd4_display),  NORMALPRIO + 1, Thd4_display, NULL);
	 
	chThdCreateStatic(waThd5_Serial, sizeof(waThd5_Serial), NORMALPRIO + 1, Thd5_Serial, NULL);
	
	chThdCreateStatic(waThd6_analogCh1, sizeof(waThd6_analogCh1), NORMALPRIO + 1, Thd6_analogCh1, NULL);
	
	chThdCreateStatic(waThd7_analogCh0, sizeof(waThd7_analogCh0), NORMALPRIO + 1, Thd7_analogCh0, NULL);
	
	chThdCreateStatic(waThd8_creasing, sizeof(waThd8_creasing), NORMALPRIO + 1, Thd8_creasing, NULL);
	
	chThdCreateStatic(waThd9_smartGlow, sizeof(waThd9_smartGlow), NORMALPRIO + 1, Thd9_smartGlow, NULL);
	
	chThdCreateStatic(waThd10_audio, sizeof(waThd10_audio), NORMALPRIO + 1, Thd10_audio, NULL);

	chThdCreateStatic(waThd11_paddlEvents, sizeof(waThd11_paddlEvents), NORMALPRIO + 1, Thd11_paddlEvents, NULL);

	chThdCreateStatic(waTrim, sizeof(waTrim),
	NORMALPRIO + 1, Trim, NULL);

	chThdCreateStatic(waThd12_Sensor, sizeof(waThd12_Sensor),
	NORMALPRIO + 1, Thd12_Sensor, NULL);
	
}
//------------------------------------------------------------------------------
void loop() {
	// not used
}



unsigned int manualSewing(){


long AN_CH0_sensor_data_RAW_THD=0;
long AN_CH0_sensor_data_AVR_THD=0;
unsigned int trueDAC_out_1 = 0;
unsigned int trueDAC_out_2 = 0;

chMtxLock(&ADC_DATA_SH);// protected area to copy data
AN_CH0_sensor_data_RAW_THD = AN_CH0_sensor_data_RAW_GLOB;
AN_CH0_sensor_data_AVR_THD = AN_CH0_sensor_data_AVR_GLOB;
chMtxUnlock(&ADC_DATA_SH);

trueDAC_out_1 = primery_sensor.getSensor_value_to_DAC(AN_CH0_sensor_data_AVR_THD);
//trueDAC_out_1 = manual_machine.dac_limits_cutoff_filter(trueDAC_out_1);
//manual_machine.set_Voltage(trueDAC_out_1,false);


// chMtxLock(&DAC_DATA_SH);
// trueDAC_GLOB_1 = trueDAC_out_1;
// chMtxUnlock(&DAC_DATA_SH);

//**********************************************************************************************************

	static unsigned int prev_trueDACout = 0;

	// process analog input to smooth and calibrations	
		
		//trueDAC_out_1 = map(AN_CH0_sensor_data_AVR_THD,analogLowCH0, analogHighCH0, CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value, CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value);
		
		trueDAC_out_1 = ((trueDAC_out_1<=CALIB_ideal_DAC_value)? CALIB_ideal_DAC_value : trueDAC_out_1);// set DAC value to zero if below CALIBRATE_DACout_MIN
		// incase the value is greater that 4096 it should not be passed to DAC
		trueDAC_out_1 = ((trueDAC_out_1>DAC_MAX_RESOLUTION_DAC_VALUE)? DAC_MAX_RESOLUTION_DAC_VALUE : trueDAC_out_1);//
			
		if ((AN_out_MC_EN)&&(!getState_foot()))
		{
			if (prev_trueDACout != trueDAC_out_1)
			{
					dac.setVoltage(trueDAC_out_1, false);
					
					prev_trueDACout = trueDAC_out_1;
			}
		
			if (trueDAC_out_1)// trueDACout isn't zero means we are going to start the machine.
			{
				runTimer.setTrueDACout_writtrn_time(micros());// recode stating initiating time.
			}
			
		}
		else if(!AN_out_MC_EN){ dac.setVoltage(CALIB_ideal_DAC_value,false);}
			
			return trueDAC_out_1;

}

eAUTO_PILOT_RESULTS autoPilotProcessor(){	
	 unsigned int trueDAC_proccesed = CALIB_ideal_DAC_value;
	 // Auto pilot protection service by auto start sensor
			if (MyAutoPilot.get_auto_pilot_protection_by_start_sensor())
			{
				if ((!getState_foot())&&(MyAutoPilot.garment_avalability())&&(MyAutoPilot.get_auPiolot_State()==AP_ON_GOING))
				{
					DACDataIndex_AP=0;
					SPI_updated=false;
					dac.setVoltage(trueDAC_proccesed, false);
					return RESULT_AU_CANCEL;
				}
			
			}

			if (DACDataIndex_AP>=SIZE_OF_DAC_DATA_ARRY)
			{
				AutoDriveTest_EN=false;
				DACDataIndex_AP=0;
				return RESULT_AU_BUF_OVER;
			}
			if (getMode()==AUTO_DRIVE_TEST)
			{
				if (!getAutoDriveTest_EN())
				{
					DACDataIndex_AP=0;
					SPI_updated=false;
					return RESULT_AU_CANCEL;
				}
				
			}
			if (getMode()==AUTO_PILOT)
			{
				if (!getAutoPilot_EN())
				{
					DACDataIndex_AP=0;
					SPI_updated=false;
					dac.setVoltage(trueDAC_proccesed, false);
					return RESULT_AU_CANCEL;
				}
				
			}
			if (DACDataIndex_AP>SPI_speed_profil_length_SH)
			{
				DACDataIndex_AP = 0;
				trueDAC_proccesed = CALIB_ideal_DAC_value;
				SPI_updated = false;
				dac.setVoltage(trueDAC_proccesed, false);
				creaZer.setcurrentCreasingPoints(0);
				setLCD_refresh(true);				
				return RESULT_AU_SUCSEDD_DONE;
			}
		
			// int r = paddleSensorAnalogDataProcessCH0();
			 chMtxLock(&SerialDataSH_Mutex_CH0);
			 int r = AN_CH0_sensor_data_AVR_GLOB;
			 chMtxUnlock(&SerialDataSH_Mutex_CH0);
			 //if (millis()-lastPWMWriteTime>PWMWritingInterval)
			 
			 if(SPI_updated)
			 {
				 SPI_updated=false;
				 // check for zero speeds
				 /*get time difference of spi in auto pilot */
				// if(DACData[DACDataIndex_AP][2]>800000){// try this if((DACData[DACDataIndex_AP][2]>800000)&&(DACDataIndex_AP>2))
				if((DACData[DACDataIndex_AP][2]>1000000)&&(DACDataIndex_AP>1)){
				//Serial.print("waiting at");
				//Serial.print(DACDataIndex_AP);
				//Serial.print(":");
				//Serial.print(DACData[DACDataIndex_AP][0]);

				if(!getState_foot()) dac.setVoltage(CALIB_ideal_DAC_value,false);// if foot is not lifted manually go stay in ideal mode
				if (automatic_foot_lifting)// if automatic foot lifting enable
				{
					if(!getState_foot()){
					//Serial.print("before spi");
					//Serial.print(DACDataIndex_AP);
					 DACDataIndex_AP++;
					//Serial.print("now spi");
					//Serial.print(DACDataIndex_AP);
					my_foot_Event->autoEvent_activator(DACDataIndex_AP);// check for automatic foot lifting in this waiting time
					my_trim_Event->autoEvent_activator(DACDataIndex_AP);// check for automatic foot lifting in this waiting time
					 DACDataIndex_AP--;
					}
				}
				/*else if (!automatic_foot_lifting){
					if(!getState_foot()) dac.setVoltage(CALIB_ideal_DAC_value,false);
				}*/
				 unsigned int TimeDifference_AP = (micros() - Time_lastDACWritten);
				 int TimeGap = TimeDifference_AP - DACData[DACDataIndex_AP][2] ;
							 if (Serial_push_EN_autoPilotData) {
																Serial.print("Time_lastDACwrittn: ");
																Serial.print(Time_lastDACWritten);
																Serial.print("  DACDataIndex: ");
																Serial.print(DACData[DACDataIndex_AP][2]);
																Serial.print("Time Diff: ");
																Serial.print(TimeDifference_AP);
																Serial.print("   Time gap: ");
																Serial.print(TimeGap);
																}
				// time gap will be minus if we are too early to write next DAC value
				// there are 2 methods to exit from waiting
				// 1. escape by external switch
				// 2. escape by start sensor
				// 3. time out
				// check enable method
				if (MyAutoPilot.get_auto_pilot_waiting_escape_by_external_trigger())
				{
					if (!MyAutoPilot.get_state_external_trigger())
					{
						SPI_updated=true;// if didn't make this true, we will not come to this timing check function
						return RESULT_AU_PROCCESING;
						
					}

					MyAutoPilot.set_state_external_trigger(false);
				}

				else if ((MyAutoPilot.get_auto_pilot_waiting_escape_by_start_sensor())&&(getState_foot()))
				{
					MyAutoPilot.set_auPiolot_State(WAIT_FOR_START);
					SPI_updated=true;
					if (!MyAutoPilot.wait_for_start_signal())//
					{
						chThdSleepMilliseconds(1);
						Serial.println("waiting sensor escape");
						SPI_updated=true;//if didn't make this true, we will not come to this timing check function
						return RESULT_AU_PROCCESING;
					}

					Serial.println("sensor ok");

					
				} 
				else 
				{
					if (TimeGap<0)
					{
						if (r<AP_semiAuto_en_min_analogCH0_input)// user can stop the mc even in a waiting time
						{
							SPI_updated=true;// if didn't make this true, we will not come to this timing check function
							return RESULT_AU_PROCCESING;
							
						}
						else{// if user want to stop mc during the waiting period
							setEvent_ch0(0);
							dac.setVoltage(CALIB_ideal_DAC_value, false);
							Time_lastDACWritten = micros();
							Serial.println("stopped during the waiting");
							return RESULT_AU_CANCEL;
						}
						
					}
				}
				 
				 if(getState_foot()){
				  SPI_updated=true;// if didn't make this true, we will not come to this timing check function
				  Serial.println("foot is not ready");
				  if (!automatic_foot_lifting)
				  {
					 return RESULT_AU_PROCCESING;
				  }
				  // we are in automatic foot lifting so put down the foot for user
				  ideal();
				  chThdSleepMilliseconds(100);
				 }
				 }

				 trueDAC_proccesed = (DACData[DACDataIndex_AP][1]<CALIB_AuroPilot_DAC_ideal_value)? CALIB_AuroPilot_DAC_ideal_value : DACData[DACDataIndex_AP][1] ;
				 switch (AutoPilot_MODE)
				 {
				 case SEMI_AUTO:{// AP_semiAuto_en_min_analogCH0_input
									//Serial.println("semi auto mode");
									if (DACDataIndex_AP<2)// we are starting
									{
										if (r>AP_semiAuto_en_min_analogCH0_input)
										{											
											dac.setVoltage(trueDAC_proccesed, false);
											Time_lastDACWritten=micros();
																				
										}
										else{SPI_updated =true; return RESULT_AU_PROCCESING;}
									}									 
									 else// we are in the middle
									 {	
										 if (r<AP_semiAuto_en_min_analogCH0_input)
										 {		dac.setVoltage(CALIB_ideal_DAC_value, false);	
												Time_lastDACWritten=micros();
											 	return RESULT_AU_PUS;					
											}
										else{dac.setVoltage(trueDAC_proccesed, false); Time_lastDACWritten=micros();}
									 }
								}
				 				break;
					 
				 case FULL_AUTO:{
									/*Serial.println("fully auto mode");
									dac.setVoltage(trueDAC_proccesed, false);
									Time_lastDACWritten=micros();*/
									// AP_semiAuto_en_min_analogCH0_input
									//Serial.println("fully auto mode");
									if (DACDataIndex_AP<1)// we are starting
									{
										// auto pilot waiting time out
										unsigned long currentMillis = millis();
										
										if(currentMillis - MyAutoPilot.get_last_time_ap_done() > 60000) {
											// save the last time you blinked the LED
											MyAutoPilot.set_last_time_ap_done(currentMillis);
											ap_time_out();
										}

									/*	if (((getState_foot())||(getState_trim()))&&(automatic_foot_lifting))
										{
											ch
											ideal();
										}*/

										//Serial.println("waitinf for starting");
										if ((getEvent_ch0()==4)||(getForceStart_autoPilot())||((automatic_ap_start)&&(MyAutoPilot.wait_for_start_signal())))
										{
											Serial.println("we are starting");
											if ((getState_foot())||(getState_trim()))
											{
												ideal();
											}
											setForceStart_autoPilot(false);	
											Reset_other_parameters();
											
											profile_type_print(spi_vs_speed_profile_type_auto_pilot);
											sdloader::resetArray_to_null(DACData,SIZE_OF_DAC_DATA_ARRY);
											SD_OPERATION_RESULTS result = sdloader :: loading_profile(DACData, SIZE_OF_DAC_DATA_ARRY, spi_vs_speed_profile_type_auto_pilot, SPI_speed_profil_length_SH);
											myCutterEvent->reset_event_profile();
											myCutterEvent->import_data_from_sd();
											my_trim_Event->reset_event_profile();
											my_trim_Event->import_data_from_sd();
											my_foot_Event->reset_event_profile();
											my_foot_Event->import_data_from_sd();

											button.attachClick(mechanical_sw_mode_ap_wating_scape);
											profile_type_print(spi_vs_speed_profile_type_auto_pilot);
											if (result!=SD_OK)
											{
												Serial.println("error");
												return RESULT_AU_CANCEL;
											}
											
											
											SPI_speed_profil_length_SH - getTeachProfile_length(DACData,SIZE_OF_DAC_DATA_ARRY);
											Serial.print("Length of new loaded profile: ");
											Serial.println(SPI_speed_profil_length_SH);
											// we should re calculate "trueDAC_proccesed" value
											trueDAC_proccesed = (DACData[DACDataIndex_AP][1]<CALIB_AuroPilot_DAC_ideal_value)? CALIB_AuroPilot_DAC_ideal_value : DACData[DACDataIndex_AP][1] ;
											
											dac.setVoltage(trueDAC_proccesed, false);
											
											Time_lastDACWritten=micros();
											setEvent_ch0(0);
											
											// there is a bug and following print will use full to locate it
											Serial.println("event detected - autopilot began to write DAC ");									
										}
										
										else{SPI_updated =true; return RESULT_AU_PROCCESING;}// waiting for starting signal
									}
									else// we are in the middle
									{	
										//Serial.println("we are in the middle");
										if (r<AP_semiAuto_en_min_analogCH0_input)
										{	
											//chMtxLock(&DAC_HPV_90_LOCK);
											dac.setVoltage(trueDAC_proccesed, false); Time_lastDACWritten=micros();
											//DACDataIndex_AP++;//********************we canot increas the index here as we have to do much yet
											//chMtxUnlock(&DAC_HPV_90_LOCK);									
										}
										
										else{
											setEvent_ch0(0);
											dac.setVoltage(CALIB_ideal_DAC_value, false);
											Time_lastDACWritten = micros();
											return RESULT_AU_CANCEL;
										}
									}
								}
								break;
				 }	
				 
				 			 
				  myCutterEvent->autoEvent_activator(DACDataIndex_AP);
				

				 if (Serial_push_EN_autoPilotData)
				 {
					 Serial.print("SPI updated ");
					 // push auto pilot data via serial
					 Serial.print("RECED. @ ");
					 //Serial.print(milastSapleTakenTime);
					 Serial.print( DACData[DACDataIndex_AP][0]);
					 Serial.print(":");
					 Serial.print(DACDataIndex_AP);
					 Serial.print(" DAC ");
					 Serial.println(trueDAC_proccesed);
				 }

				 DACDataIndex_AP++;//*********************************************moved 
				 //DACDataIndex_AP = DACData[DACDataIndex_AP][0];
				 // we check for creasing/auto cutter or foot now
				 if ((DACData[DACDataIndex_AP][3] == CREASING_NUMERICAL_VALUE_OF_REG) || (DACData[DACDataIndex_AP][3] == ACTIVATE_CUTTER_WITH_CREAZING_NUMERICAL_VALUE_OF_REG)||(DACData[DACDataIndex_AP][3] == DEACTIVATE_CUTTER_WITH_CREAZING_NUMERICAL_VALUE_OF_REG))
				 {
					 // set binary semaphore to issue creasing pulse
					 creaZer.creasingPulseOut();
					 unsigned int currentvalue = getcurrentCreasingPoints();
					 currentvalue++;
					 creaZer.setcurrentCreasingPoints(currentvalue);
					 setLCD_Event_creasing(true);
				 }
				 			  
				  //data sharing area
				  // wait to enter protected region
				  chMtxLock(&SerialDataSH_Mutex_CH0);
				  DACoutValue_autoPilot_proccessed_SH = trueDAC_proccesed;
				  DACDataArray_SPI_of_curruntIndexValue_SH = DACData[DACDataIndex_AP][0];
				  // exit protected region
				  chMtxUnlock(&SerialDataSH_Mutex_CH0);
				  setnexUpdate_force();
				 
			 }			 
		return RESULT_AU_PROCCESING;
}




void serialEventRTOS() {

  while (Serial.available()) {
    // get the new byte:
	chThdSleepMicroseconds(1);
    char inChar = (char)Serial.read();
    // add it to the inputString:
     serial1inputString[serial1inputStringBuffIndex]= inChar;
	 serial1inputStringBuffIndex++;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
     serial1stringComplete = true;
	  serial1inputStringBuffIndex=0;
    }
  }
  
  if (serial1stringComplete) {
	  
	if (strncmp("ap_en/n",serial1inputString,5)==0)
	{
		SPI_updated=true;
		setAutoDriveTest_EN(true);
		
	}
	if (strncmp("ap_de/n",serial1inputString,5)==0)
	{
		setAutoDriveTest_EN(false);
		
	}
	  
	if (strncmp("an_data_en/n",serial1inputString,10)==0)
	{
		
		Serial_push_EN_analogInputData=true;
	}
	   
	if (strncmp("an_data_de/n",serial1inputString,10)==0)
	{
		Serial_push_EN_analogInputData=false;
	}
	if (strncmp("ap_data_en/n",serial1inputString,10)==0)
	{
		
		Serial_push_EN_autoPilotData=true;
	}
	
	if (strncmp("ap_data_de/n",serial1inputString,10)==0)
	{
		Serial_push_EN_autoPilotData=false;
	}
	if (strncmp("teaching_en/n",serial1inputString,11)==0)
	{
		setTeachingSewing_EN(true);
		//setMode(SPI_TEACHING);
		Serial.print("teaching_started!");
	}
	if (strncmp("teaching_de/n",serial1inputString,11)==0)
	{		
		SPI_speed_profil_teaching_EN=false;
		Serial.print("teaching_stoped!");
	}
	if (strncmp("prof_reset/n",serial1inputString,10)==0)// updated
	{

		SPI_speed_profil_reset=true;
		//resetTeachProfile();
		sdloader :: resetArray_to_null(DACData, SIZE_OF_DAC_DATA_ARRY);
	}
	if (strncmp("prof_type_1/n",serial1inputString,11)==0)
	{
		spi_vs_speed_profile_type_saving = NECK_LINE; Serial.println("Profile type change to NECK LINE");
		spi_vs_speed_profile_type_auto_pilot = NECK_LINE;
		msg_teaching_t0_message = LCD_text_meassage1;
		setLCD_Event_autopilot_session_chenged(true);
	}
	if (strncmp("prof_type_2/n",serial1inputString,11)==0)
	{
		spi_vs_speed_profile_type_saving = ARM_LEFT; Serial.println("Profile type change to ARM LEFT");
		spi_vs_speed_profile_type_auto_pilot = ARM_LEFT;
		msg_teaching_t0_message = LCD_text_meassage2;		
		setLCD_Event_autopilot_session_chenged(true);
	}
	if (strncmp("prof_type_3/n",serial1inputString,11)==0)
	{
		spi_vs_speed_profile_type_saving = ARM_RIGHT; Serial.println("Profile type change to ARM RIGHT");
		spi_vs_speed_profile_type_auto_pilot = ARM_RIGHT;
		msg_teaching_t0_message = LCD_text_meassage3;
		setLCD_Event_autopilot_session_chenged(true);
	}
	if (strncmp("prof_type_d/n",serial1inputString,11)==0)
	{
		spi_vs_speed_profile_type_saving = DEFAULT_PROFILE; Serial.println("Profile type change to DEFAULT");
		spi_vs_speed_profile_type_auto_pilot = DEFAULT_PROFILE;
		msg_teaching_t0_message = LCD_text_meassage0;
		setLCD_Event_autopilot_session_chenged(true);
	}
		
	
	if (strncmp("mc_en/n",serial1inputString,5)==0)// ?
	{

		 AN_out_MC_EN=true;
	}
	
	if (strncmp("mc_de/n",serial1inputString,5)==0)// ?
	{

		 AN_out_MC_EN=false;
	}
	if (strncmp("SPI_reset/n",serial1inputString,9)==0)// ?
	{

		currentSPI=0;
	}
	if (strncmp("sewass_en/n",serial1inputString,9)==0)// doesn't work
	{
		sewingAssistent_EN=true;
		SPI_updated=true;
	}
	if (strncmp("sewass_de/n",serial1inputString,9)==0)// doesn't work
	{
		sewingAssistent_EN=false;
	}
	if (strncmp("ap_mode_a/n",serial1inputString,9)==0)// doesn't work
	{
		AutoPilot_MODE=FULL_AUTO;
	}
	if (strncmp("ap_mode_s/n",serial1inputString,9)==0)// doesn't work
	{
		AutoPilot_MODE=SEMI_AUTO;
	}  
	if (strncmp("get_l/n",serial1inputString,5)==0)// updated
	{
		Serial.println(getTeachProfile_length(DACData,SIZE_OF_DAC_DATA_ARRY));
	}
	if (strncmp("get_profile/n",serial1inputString,11)==0)// updated
	{
		Serial.println("getting raw data..");
		for (int tempIndex =0; tempIndex<=SIZE_OF_DAC_DATA_ARRY-1; tempIndex++)
		{
			 Serial.print("REC. @ ");
			 Serial.print( DACData[tempIndex][0]);
			 Serial.print(" DAC ");
			 Serial.print(DACData[tempIndex][1]);
			 Serial.print(" TD ");
			 Serial.print( DACData[tempIndex][2]);
			 Serial.print(" CZ ");
			 Serial.println( DACData[tempIndex][3]);
			
		}
		Serial.println("all raw data done!");
	}
	if (strncmp("ism/n",serial1inputString,3)==0)// updated
	{
		Serial.println("ISM loading");
		unsigned int ideal_DAC_value;
		unsigned int MAX_RPM_DAC_value;
		unsigned int AuroPilot_DAC_ideal_value;
		SD_OPERATION_RESULTS result = sdloader :: loading_ISM(ideal_DAC_value,MAX_RPM_DAC_value,AuroPilot_DAC_ideal_value);
		if (result == LOADING_FAIL)
		{
			Serial.println("Loading Error");
		}
		else{
		Serial.println(ideal_DAC_value);
		Serial.println(MAX_RPM_DAC_value);
		Serial.println(AuroPilot_DAC_ideal_value);
		
		}
	}
	if (strncmp("hpv_90/n",serial1inputString,6)==0)// updated
	{
		Serial.println("HPV_90_1L loading");
		unsigned int ideal_DAC_value;
		unsigned int MAX_RPM_DAC_value;
		unsigned int AuroPilot_DAC_ideal_value;
		unsigned int foot_dac;
		unsigned int trim_dac;
		SD_OPERATION_RESULTS result = sdloader :: loading_pegasus_HPV_90_single_line(ideal_DAC_value,MAX_RPM_DAC_value,AuroPilot_DAC_ideal_value,foot_dac,trim_dac);
		if (result == LOADING_FAIL)
		{
			Serial.println("Loading Error");
		}
		else{
			Serial.println(ideal_DAC_value);
			Serial.println(MAX_RPM_DAC_value);
			Serial.println(AuroPilot_DAC_ideal_value);
			Serial.println(foot_dac);
			Serial.println(trim_dac);
		}
	}
	if (strncmp("trim/n",serial1inputString,4)==0)// updated
	{

	foot_activate();
		//Serial.println();
	}
	if (strncmp("acm/n",serial1inputString,3)==0)// updated
	{char buff[50];
	eMotor_type acm;
		SD_OPERATION_RESULTS result =  sdloader::getActive_motor_type_from_sd(acm);
		sdloader :: loading_machine_para(acm,CALIB_ideal_DAC_value,CALIB_MAX_RPM_DAC_value,CALIB_AuroPilot_DAC_ideal_value,Active_motor_type_struct.motor_foot_lifting_vale,Active_motor_type_struct.motor_trimmer_activation_value);
		//Serial.println(buff);
		if (result == LOADING_FAIL)
		{
			Serial.println("Loading Error");
		}
		else{
			
		}
	}

	if (strncmp("file_ftdf/n",serial1inputString,9)==0)
	{
		Serial.println("Dumping file");
		String data;
		data.reserve(1024);
		sdloader :: dump_file("USADATA/SPI/DEFAULT/SVFT_DF.TXT", data);
	
		//Serial.println(data);
	}
	if (strncmp("file_fdf/n",serial1inputString,8)==0)
	{
		Serial.println("Dumping file");
		String data;
		data.reserve(1024);
		sdloader :: dump_file("USADATA/SPI/DEFAULT/SVF_DF.TXT", data);
		
		//Serial.println(data);
	}
	if (strncmp("file_df/n",serial1inputString,7)==0)
	{
		Serial.println("Dumping file");
		String data;
		data.reserve(1024);
		sdloader :: dump_file("USADATA/SPI/DEFAULT/SVS_DF.TXT", data);
		
		//Serial.println(data);
	}

	if (strncmp("events/n",serial1inputString,6)==0)
	{
		Serial.println("reading event file");
		unsigned int array[11][2];
		sdloader :: loading_event_data_from_SD("USADATA/SPI/DEFAULT/SVC_1.TXT",array,10);
		for (int k=0; k<=9; k++)
		{
			Serial.print(array[k][0]);
			Serial.print(" : ");
			Serial.println(array[k][1]); 
		}
		//sdloader :: write_event_data_to_SD("USADATA/SPI/DEFAULT/SVC_1.TXT" , array, 9);
		
	}

	if (strncmp("reg/n",serial1inputString,3)==0)
	{
		Serial.println("registering event file");
		myCutterEvent->export_data_to_sd();
	}
	if (strncmp("gete/n",serial1inputString,4)==0)
	{
		Serial.println("getting events");
		myCutterEvent->import_data_from_sd();
		currentSPI=0;
		
	}
	  // clear the string:
	  memset(serial1inputString,0,25);
	  serial1stringComplete = false;
  }
  
  
}

void serialPrinting(){
	//printing 0CH analog data
	if (Serial_push_EN_analogInputData)
	{
		chMtxLock(&SerialDataSH_Mutex_CH0);
		Serial.print(" AN_RAW_CH0: ");
		Serial.print(AN_CH0_sensor_data_RAW_GLOB);
		Serial.print(" AN_AVR_CH0:   ");
		Serial.println(AN_CH0_sensor_data_AVR_GLOB);
		chMtxUnlock(&SerialDataSH_Mutex_CH0);
		
		//printing 1CH analog data
		chMtxLock(&SerialDataSH_Mutex_CH1);
		//Serial.print("  AN_RAW_CH1: ");
		//Serial.print(CH1_RAWAnalogValueSH);
		Serial.print(" AN_AVR_CH1: ");
		Serial.print(AN_CH1_sensor_data_AVR_GLOB);
		Serial.print(" DAC: ");
		Serial.print( DACoutValue_Actual_SH);
		
		chMtxUnlock(&SerialDataSH_Mutex_CH1);
	}
	
}

void endcutter_event_reg_wrap(){
	chMtxLock(&Wheel_Cutter);
	myCutterEvent->setRegistation_request(true);
	myCutterEvent->setAction_request(true);
	chMtxUnlock(&Wheel_Cutter);
}