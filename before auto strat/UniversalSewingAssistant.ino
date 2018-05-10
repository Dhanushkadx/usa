#include "pinsx.h"

#include "syncx.h"
#include "autoWheelcutter.h"
#include "utilityFunction.h"

#include "Nextion.h"
#include <ChibiOS_ARM.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "statements.h"
#include "display.h"
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

OneButton button(creasingIn, true);
SPI_PROFILE_CATOGERY spi_vs_speed_profile_type_saving = DEFAULT_PROFILE;
SPI_PROFILE_CATOGERY spi_vs_speed_profile_type_auto_pilot = DEFAULT_PROFILE;
//eMotor_type Active_motor_type;
#include <SD.h>
#include <SPI.h>

const int chipSelect = BUILTIN_SDCARD;

Adafruit_MCP4725 dac;
smartGlow RGB_leds(4,2,3);
cycleTimer runTimer(1000,250);
autoCreasing creaZer;
AutoCutter WheelCutter(RLY2);
SmartPaddle primery_sensor(analogPin0);
SmartPaddle secondry_sensor(analogPin1);

syncx defaultProfileEvent("USADATA/SPI/DEFAULT/SVC_DF.TXT");
syncx neckProfileEvent("USADATA/SPI/DEFAULT/SVC_1.TXT");
syncx armLProfileEvent("USADATA/SPI/DEFAULT/SVC_2.TXT");
syncx armRProfileEvent("USADATA/SPI/DEFAULT/SVC_3.TXT");

syncx* myEvent = &defaultProfileEvent;


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
		eMotor_type _Active_motor_type;
		sdloader :: getActive_motor_type_from_sd(_Active_motor_type);
		Active_motor_type_struct.Active_motor_type = _Active_motor_type;
		sdloader :: loading_machine_para(_Active_motor_type,CALIB_ideal_DAC_value,CALIB_MAX_RPM_DAC_value,CALIB_AuroPilot_DAC_ideal_value,Active_motor_type_struct.motor_foot_lifting_vale,Active_motor_type_struct.motor_trimmer_activation_value);
		sdloader :: loading_stepper_sysnc_para(pulse_width, au_feeder_cutter_act_delay, au_feeder_cutting_delay);
		sdloader :: loading_FT(TH_ch1_detection_min_threshold_GLOBAL,TI_first_pulse_registering_delay_GLOBAL,TI_second_puls_stating_delay_GLOBAL,
		TH_ch1_trim_detection_threshold_GLOBAL,TI_second_pulse_rising_delay_GLOBAL, TI_second_pulse_rising_debounce_GLOBAL);
		primery_sensor.set_CH0_AN_MIN_value(analogLowCH0);
		primery_sensor.set_CH0_AN_MAX_value(analogHighCH0);
		primery_sensor.set_ch0_to_dac_limits(CALIB_MAX_RPM_DAC_value,CALIB_ideal_DAC_value);

		secondry_sensor.set_CH0_AN_MIN_value(analogLowCH1);
		secondry_sensor.set_CH0_AN_MAX_value(analogHighCH1);
		secondry_sensor.set_ch0_to_dac_limits(1023,0);
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
static THD_WORKING_AREA(waThd4_display, 3536);

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
static THD_WORKING_AREA(waThd6_analogCh1, 128);
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
		TI_second_puls_stating_delay = TI_second_puls_stating_delay_GLOBAL;// ms default
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
static THD_WORKING_AREA(waThd7_analogCh0, 256);

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
		/*if (WheelCutter.getCutterActivation_request())&&(Teaching_en == False)
		{
			WheelCutter.setCutterActivation_request(false);
			Serial.println("resuest detected");
			CUTTER_STATES result = WheelCutter.getState();
			if (result == ACTIVE )
			{
				WheelCutter.Activate();
			}
			else if (result == DEACTIVE)
			{
				WheelCutter.Deactivate();
			}
		}
		
		// pooling mechanical switch for creasing
	/*	if (creaZer.poolingCreasingSwitch())
		{
			Serial.println("creasing Set");
			creaZer.setSPIcreasingDetect(true);
			creaZer.creasingPulseOut();
			creaZer.advance_numberOfCreasing();
			setLCD_Event_creasing(true);
		}
		*/
		// Display thread will use following creasingSem 
		
		//chBSemWaitTimeout(&creasingSem, 100);
	/*	if(!chBSemGetStateI(&creasingSem)){
			chBSemReset(&creasingSem,true);
			Serial.println("creasing Set");
			creaZer.setSPIcreasingDetect(true);
			creaZer.creasingPulseOut();
			creaZer.advance_numberOfCreasing();
			setLCD_Event_creasing(true);
			
		}*/
		
			
				
	}
}

//------------------------------------------------------------------------------
// Thread 2, smartGlow.

// 64 byte stack beyond task switch and interrupt needs
static THD_WORKING_AREA(waThd9_smartGlow, 64);

static THD_FUNCTION(Thd9_smartGlow, arg) {
	
	RGB_leds.set_smartGlow(INIT);
	while (1)
	{
		chThdSleepMicroseconds(1);
		RGB_leds.smartGlowRun();	
		//runTimer.cycleTimerRun(SPIdetect);
		//runTimer.security_run_check();
		
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
		Serial.print("Handler: ");
		Serial.println(t - tIsr);
		Serial.println("pulse width ");
		Serial.print(pulse_width);	
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
				if (!getState_foot())
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
				chThdSleepMilliseconds(au_feeder_cutter_act_delay_THD);
				digitalWrite(END_CUTTER_OUT,HIGH);
				chThdSleepMilliseconds(au_feeder_cutting_delay_THD);
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
	
	//dac.begin(0x63);
	dac.begin(0x62);
	analogWriteResolution(12);
	
	Serial.print("Initializing SD card...");
	
	SD_OPERATION_RESULTS sd_state = sdloader::SD_initilization();
	if (sd_state == NO_SD)
	{
		Serial.println("Insert SD card");
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
}

void cutter_on(){ WheelCutter.Activate(); Serial.println("end cutter activation call back function");}
void cutter_off(){WheelCutter.Deactivate(); Serial.println("end cutter deactivation call back function");}

void setup() {
	
	pinMode(interruptPin,INPUT_PULLUP);
	pinMode(creasingIn,INPUT_PULLUP);
	pinMode(END_CUTTER_SENS,INPUT_PULLUP);
	pinMode(END_CUTTER_OUT,OUTPUT);
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


void mainTask()
{
	/*myEvent.autoEvent_activator(currentSPI);
	// spi emulator
	unsigned long currentMillis = millis();
	
	if(currentMillis - previousMillis > interval) {
		// save the last time you blinked the LED
		previousMillis = currentMillis;
		currentSPI++;
		
	}*/

	long AN_CH1_sensor_data_RAW_THD=0;
	long AN_CH0_sensor_data_RAW_THD=0;
	long AN_CH0_sensor_data_AVR_THD=0;
	unsigned int trueDAC_out_1 = 0;
	unsigned int trueDAC_out_2 = 0;
	
	chMtxLock(&ADC_DATA_SH);// protected area to copy data
	AN_CH0_sensor_data_RAW_THD = AN_CH0_sensor_data_RAW_GLOB;
	AN_CH0_sensor_data_AVR_THD = AN_CH0_sensor_data_AVR_GLOB;
	AN_CH1_sensor_data_RAW_THD = AN_CH1_sensor_data_RAW_GLOB;
	chMtxUnlock(&ADC_DATA_SH);

	switch (getMode())
	{
	case MANUAL_SEW:{// default mode
						if(prev_MODE!=MANUAL_SEW){ DACDataIndex=0; Serial.println("Manuel mode - interrupt activated!"); prev_MODE=MANUAL_SEW; attachInterrupt(digitalPinToInterrupt(interruptPin), EXinterruptRooting, RISING); 
							Serial.println("mechanical button mode - Session");
							switch_mode = CREASING;
							dac.setVoltage(CALIB_ideal_DAC_value,false);
							button.attachClick(mechanical_sw_mode_creasing_out);
							
							}//detachInterrupt(digitalPinToInterrupt(interruptPin)); }
						 unsigned int dacout = manualSewing();
						 chMtxLock(&Flags_communication);
						 DACoutValue_Actual_SH = dacout;
						 chMtxUnlock(&Flags_communication);
						 RGB_leds.set_smartGlow(INIT);
						 boolean spi_update_flag = SPI_updated;
						 SPI_updated = false;
						 Utility :: count_spi(spi_update_flag);
						// attachInterrupt(digitalPinToInterrupt(creasingIn), InterruptRooting_creasing, FALLING );
						
						 if (getsetteachingSewing_EN())
						 {
							 setMode(SPI_TEACHING);
							 Serial.println("control hand over to spi teaching");
						 }
						 
						 if (getAutoDriveTest_EN())
						 {
							  setMode(AUTO_DRIVE_TEST);
							  Serial.println("control hand over to auto drive test");
						 }
						 if (getAutoPilot_EN())
						 {
							 setMode(AUTO_PILOT_CYCLE_REST);
							 Serial.println("control hand over to autopilot");					
						 }
						 if (getTeachingReset_EN())
						 {
							 setTeachingReset_EN(false);
							 resetTeachProfile();							 
						 }
						 if (getSetup_EN())
						 {
							 setMode(SETUP_ANALOG);
						 }			
						 //************************************************************************
						 // detect wheel cutter sets
// 						 if (WheelCutter.getCutterActivation_request())
// 						 {
// 							 Serial.print("cutter request detected");
// 							 WheelCutter.setCutterActivation_request(false);
// 							 CUTTER_STATES result = WheelCutter.getState();
// 							 switch (result)
// 							 {
// 								 case ACTIVE:{WheelCutter.Activate(); }
// 								 break;
// 								 case DEACTIVE:{WheelCutter.Deactivate(); }
// 								 break;
// 							 }
// 						 }			
		
					}
		break;
	case SPI_TEACHING:{
						if(prev_MODE!=SPI_TEACHING){
							Serial.println("Teaching mode - interrupt activated!");
							prev_MODE=SPI_TEACHING;
							DACDataIndex=0;
							resetTeachProfile();
							currentSPI=0;
							previousSPI_register_time = micros();
							attachInterrupt(digitalPinToInterrupt(interruptPin), EXinterruptRooting, RISING);
							RGB_leds.set_smartGlow(TEACHING);
							RGB_leds.set_smartFlickering(3);
							myEvent->reset_event_profile();
							}
						
						unsigned int dacout = manualSewing();
						chMtxLock(&Flags_communication);
						DACoutValue_Actual_SH = dacout;
						chMtxUnlock(&Flags_communication);
						//detect tape creasing
						if (creaZer.getSPIcreasingDetect()){
							creaZer.setSPIcreasingDetect(false);
							DACData[DACDataIndex][3] = CREASING_NUMERICAL_VALUE_OF_REG + DACData[DACDataIndex][3];// what will happened if creasing press more than once?????
						}
						// detect wheel cutter sets
						
						
						
							
							
							chMtxLock(&Wheel_Cutter);
							myEvent->sync_rec(currentSPI);
							myEvent->sync_actions();
							chMtxUnlock(&Wheel_Cutter);
						

						unsigned int results = teachingSewing(dacout);
						if (results == RESULT_SPI_TEACHING_CANCEL)
						{								 
							setMode(MANUAL_SEW);
							teachingTerminator();
						}					
	
					}
		break;
	case AUTO_DRIVE_TEST:{
						if(prev_MODE!=AUTO_DRIVE_TEST){
							Serial.println("Auto Drive Test mode - interrupt activated!"); 
							SPI_updated=true; DACDataIndex_AP=0 ; Time_lastDACWritten = micros();
							prev_MODE=AUTO_DRIVE_TEST;
							attachInterrupt(digitalPinToInterrupt(interruptPin), EXinterruptRooting, RISING);
							}
							
						eAUTO_PILOT_RESULTS results = autoPilotProcessor();
						
						if (results==RESULT_AU_SUCSEDD_DONE)
						{
							Serial.println("AP successfully done !");
							setAutoDriveTest_EN(false);
							setMode(MANUAL_SEW);
						}
						else if (results == RESULT_AU_CANCEL)
						{
							setAutoDriveTest_EN(false);
							setMode(MANUAL_SEW);
							Serial.println("AU_RESULT_CANCEL !");
						}
						else if (results == RESULT_AU_BUF_OVER)
						{
							Serial.println("AU_RESULT_BUF_OVER !");
							
						}					
	
					}
		break;
		
		case AUTO_PILOT:{
						if(prev_MODE!=AUTO_PILOT){
							Serial.println("Auto pilot mode - interrupt activated!");
							SPI_updated=true; DACDataIndex_AP=0;  Time_lastDACWritten = micros(); 
							prev_MODE=AUTO_PILOT;
							setEvent_ch0(0);	
							attachInterrupt(digitalPinToInterrupt(interruptPin), EXinterruptRooting, RISING);
							RGB_leds.set_smartGlow(AUTO_PILO);
							Serial.println("mechanical button mode - Session");
							switch_mode = SESSION_CHENGE;
							button.attachClick(mechanical_Rotary_sw_mode_session_chenge);
						}
						
						eAUTO_PILOT_RESULTS results = autoPilotProcessor();
						
						if (results==RESULT_AU_SUCSEDD_DONE)
						{
							Serial.println("AP successfully done !");
							setAutoPilot_EN(true);
							detachInterrupt(digitalPinToInterrupt(interruptPin));
							setMode(AUTO_PILOT_CYCLE_REST);
						}
						else if (results == RESULT_AU_CANCEL)
						{
							//setAutoDriveTest_EN(false);
							setAutoPilot_EN(false);
							detachInterrupt(digitalPinToInterrupt(interruptPin));
							 chMtxLock(&SerialDataSH_Mutex_CH0);
							 int r = AN_CH0_sensor_data_AVR_GLOB;
							 chMtxUnlock(&SerialDataSH_Mutex_CH0);
							 if (r<AP_semiAuto_en_min_analogCH0_input)// only if the paddle has been released we got manual otherwise the disaster will occur 
							 {
								 setMode(MANUAL_SEW);
								 setLCD_Event_autopilot_canceled(true);
								 Serial.println("AU_RESULT_CANCEL !");
							 }
						}
						else if (results == RESULT_AU_BUF_OVER)
						{
							Serial.println("AU_RESULT_BUF_OVER !");
							
						}
						else if (results == RESULT_AU_PUS)
						{
							setAutoPilot_EN(false);
							detachInterrupt(digitalPinToInterrupt(interruptPin));
							setMode(MANUAL_SEW);
							Serial.println("RESULT_AU_PUS !");
						}
			
			}
		break;
		
		case AUTO_PILOT_CYCLE_REST:{
									switch(prev_MODE){
										case MANUAL_SEW:{// just starting 
														Serial.println("starting auto pilot cycle");
														//while(1);
														prev_MODE = AUTO_PILOT_CYCLE_REST;
										
											}
											break;
										case AUTO_PILOT:{// going to next cycle
														Serial.println("next auto pilot cycle");
														prev_MODE = AUTO_PILOT_CYCLE_REST;
														setMode(AUTO_PILOT);
														// single cycle only
														/*setAutoPilot_EN(false);
														setLCD_Event_autopilot_canceled(true);
														Serial.println("Single Auto Cycle only !");*/
										}
										break;
									}
									
									if (getAutoPilot_EN())
									{
										setMode(AUTO_PILOT);
									}
									else{
										setMode(MANUAL_SEW);
									}
									
			}
			break;
		case SETUP_ANALOG:{
							if(prev_MODE!=SETUP_ANALOG){
								Serial.println("Setup analog!");
								prev_MODE = SETUP_ANALOG;
								//attachInterrupt(digitalPinToInterrupt(interruptPin), EXinterruptRooting, RISING);
							}
							// process analog input to smooth and calibrations
							long analogSamplesAverageCH1 = 0;
							long analogSamplesAverageCH0 = 0; // Running average of the sum of the buffer
							// process analog input to smooth and calibrations
							//analogSamplesAverageCH0= paddleSensorAnalogDataProcessCH0();
							chMtxLock(&SerialDataSH_Mutex_CH0);
							analogSamplesAverageCH0 = AN_CH0_sensor_data_AVR_GLOB;
							chMtxUnlock(&SerialDataSH_Mutex_CH0);

							chMtxLock(&SerialDataSH_Mutex_CH1);
							analogSamplesAverageCH1 = AN_CH1_sensor_data_AVR_GLOB;
							chMtxUnlock(&SerialDataSH_Mutex_CH1);

							analogSamplesAverageCH0= paddleSensorAnalogDataProcessCH0();	
							analogSamplesAverageCH1= paddleSensorAnalogDataProcessCH1();						
							if (!getSetup_EN())
							{
								setMode(MANUAL_SEW);
								Serial.println("returning to manual");
								
							}		
							
							chMtxLock(&DAC_data);
							unsigned int truDAC_out = DACoutValue_Actual_SH ; 
							chMtxUnlock(&DAC_data);		
							
							dac.setVoltage(truDAC_out , false);
							
							
			
			}
			break;
	}


}

eResult_teaching_states teachingSewing(unsigned int _dacout){
	
	if (!getsetteachingSewing_EN())
	{
		return RESULT_SPI_TEACHING_CANCEL;
	}
	// we are listing to the paddle to start the teaching recoding
	 chMtxLock(&SerialDataSH_Mutex_CH0);
	 int r = AN_CH0_sensor_data_AVR_GLOB;
	 chMtxUnlock(&SerialDataSH_Mutex_CH0);
	 // teaching wont be started till press the paddle at first
	if ((DACDataIndex<zeroSpeed_detectionTime_starting_point)&&(r<SPI_teaching_en_min_analogCH0_input))
	{
		previousSPI_register_time = micros();	
		//Serial.println("press paddle to start");	
		return RESULT_SPI_TEACHING_PROCCESING;
	}
	
	
	
	if (SPI_updated)
	{
		
		SPI_updated=false;
		_dacout = (_dacout<CALIB_ideal_DAC_value)? 0: _dacout;// calibrate dacout****************** 0???
		DACData[DACDataIndex][0] = currentSPI;
		DACData[DACDataIndex][1] = _dacout;
		DACData[DACDataIndex][2] = currentSPI_register_time;		
		
		Serial.print("REC. @ ");
		Serial.print( DACData[DACDataIndex][0]);
		Serial.print(" DAC ");
		Serial.print(DACData[DACDataIndex][1]);
		Serial.print(" TD ");
		Serial.println( DACData[DACDataIndex][2]);
		
		//data sharing area
		// wait to enter protected region
		chMtxLock(&SerialDataSH_Mutex_CH0);
		DACoutValue_teachng_REC_SH = DACData[DACDataIndex][1];
		DACDataArray_SPI_of_curruntIndexValue_SH = DACData[DACDataIndex][0];
		// exit protected region
		chMtxUnlock(&SerialDataSH_Mutex_CH0);
		
		DACDataIndex = (DACDataIndex<SIZE_OF_DAC_DATA_ARRY)? DACDataIndex+1 :  DACData_buf_full=true;
		
		setnexUpdate_force();// set display update flag
	
	}
	
	return RESULT_SPI_TEACHING_PROCCESING;
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
			if (DACDataIndex_AP>=SIZE_OF_DAC_DATA_ARRY)
			{
				AutoDriveTest_EN=false;
				DACDataIndex_AP=0;
				return RESULT_AU_BUF_OVER;
			}
			if (!getAutoDriveTest_EN()&&(getMode()==AUTO_DRIVE_TEST))
			{
				DACDataIndex_AP=0;
				SPI_updated=false;
				return RESULT_AU_CANCEL;
			}
			if (!getAutoPilot_EN()&&(getMode()==AUTO_PILOT))
			{
				DACDataIndex_AP=0;
				SPI_updated=false;
				dac.setVoltage(trueDAC_proccesed, false);
				return RESULT_AU_CANCEL;
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
				if((DACData[DACDataIndex_AP][2]>800000)&&(DACDataIndex_AP>1)){
				if(!getState_foot())dac.setVoltage(CALIB_ideal_DAC_value,false);
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
				 if (TimeGap<0)
				 {
					 if (r<AP_semiAuto_en_min_analogCH0_input)// user can stop the mc even in a waiting time
					 {
						 SPI_updated=true;// if didnt make this true, we will not come to this timing check function
						 Serial.print("waiting @  ");
						 Serial.println(millis());
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
				 if(getState_foot()){
				  SPI_updated=true;// if didnt make this true, we will not come to this timing check function
					Serial.println("foot is not ready");
					return RESULT_AU_PROCCESING;
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
										//Serial.println("waitinf for starting");
										if ((getEvent_ch0()==4)||(getForceStart_autoPilot()))
										{
											Serial.println("we are starting");
											setForceStart_autoPilot(false);	
											Reset_other_parameters();
											
											profile_type_print(spi_vs_speed_profile_type_auto_pilot);
											sdloader::resetArray_to_null(DACData,SIZE_OF_DAC_DATA_ARRY);
											SD_OPERATION_RESULTS result = sdloader :: loading_profile(DACData, SIZE_OF_DAC_DATA_ARRY, spi_vs_speed_profile_type_auto_pilot, SPI_speed_profil_length_SH);
											myEvent->reset_event_profile();
											myEvent->import_data_from_sd();
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
											DACDataIndex_AP = 0;// since we are at the beginning we should make this zero
											dac.setVoltage(trueDAC_proccesed, false);
											DACDataIndex_AP++;//************************************
											Time_lastDACWritten=micros();
											setEvent_ch0(0);
											//setForceStart_autoPilot(false);		
											// there is a bug and following print will use full to locate it
											Serial.println("event detected - autopilot began to write DAC ");									
										}
										
										else{SPI_updated =true; return RESULT_AU_PROCCESING;}
									}
									else// we are in the middle
									{	
										//Serial.println("we are in the middle");
										if (r<AP_semiAuto_en_min_analogCH0_input)
										{	
											dac.setVoltage(trueDAC_proccesed, false); Time_lastDACWritten=micros();
											DACDataIndex_AP++;//*******************************************************
																				
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
				 
				// DACDataIndex_AP++;*********************************************moved 
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
				/* if (WheelCutter.getRegister(DACData,DACDataIndex_AP) == ACTIVE)
				 {
					 WheelCutter.Activate();
					 RGB_leds.set_smartFlickering(5);
				 }
				 else if (WheelCutter.getRegister(DACData,DACDataIndex_AP) == DEACTIVE)
				 {
					 WheelCutter.Deactivate();
				 }*/
				 myEvent->autoEvent_activator(DACDataIndex_AP);
				// if (Serial_push_EN_autoPilotData)
				// {
					 Serial.print("SPI updated ");
					 // push auto pilot data via serial
					 Serial.print("RECED. @ ");
					 //Serial.print(milastSapleTakenTime);
					 Serial.print( DACData[DACDataIndex_AP][0]);
					 Serial.print(" DAC ");
					 Serial.println(trueDAC_proccesed);
				// }				  
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

	if (strncmp("filedump/n",serial1inputString,8)==0)
	{
		Serial.println("Dumping file");
		String data;
		sdloader :: dump_file("USADATA/SPI/DEFAULT/SVC_1.TXT", data);
	
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
		myEvent->export_data_to_sd();
	}
	if (strncmp("gete/n",serial1inputString,4)==0)
	{
		Serial.println("getting events");
		myEvent->import_data_from_sd();
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

unsigned int getTeachProfile_length(unsigned int array[][4], unsigned int length_of_array){
	
	for (int tempIndex=length_of_array-1; tempIndex>=0 ;tempIndex--)
	{
		if (array[tempIndex][0]>0)
		{
			return tempIndex;
		}	
	}
	return 0;
}

void Reset_other_parameters(){
	SPI_speed_profil_reset = false;
	
	creaZer.clrCreasingPoints();
	SPI_speed_profil_length_SH = getTeachProfile_length(DACData, SIZE_OF_DAC_DATA_ARRY);
	Serial.println("Reset Done !");
}

void resetTeachProfile(){
	SPI_speed_profil_reset = false;
	for (int tempIndex =0; tempIndex<=SIZE_OF_DAC_DATA_ARRY-1; tempIndex++)
	{
		DACData[tempIndex][0] = 0;
		DACData[tempIndex][1] = 0;
		DACData[tempIndex][2] = 0;
		DACData[tempIndex][3] = 0;
	}
	creaZer.clrCreasingPoints();
	SPI_speed_profil_length_SH = getTeachProfile_length(DACData, SIZE_OF_DAC_DATA_ARRY);
	Serial.println("Reset Done !");
}

void teachingTerminator(){
	SPI_speed_profil_length_SH = getTeachProfile_length(DACData, SIZE_OF_DAC_DATA_ARRY);
	Serial.print("length = ");
	Serial.println(SPI_speed_profil_length_SH);
	// save DACData array data to a file in sd card
	
	//sdloader::saveArry_to_file(spi_vs_speed_profile_1_location, DACData, SPI_speed_profil_length_SH);
	
	Serial.println("data saved to sd");
	
	//Serial.println("saving arm right profile");sdloader::saveArry_to_file(spi_vs_speed_default_profile_location, DACData, SPI_speed_profil_length_SH);
	
	switch (spi_vs_speed_profile_type_saving)
	{
	case DEFAULT_PROFILE:{sdloader::saveArry_to_file(spi_vs_speed_default_profile_location, DACData, SPI_speed_profil_length_SH); }
		break;
	case NECK_LINE:{Serial.println("saving neck line profile"); sdloader::saveArry_to_file(spi_vs_speed_profile_1_location, DACData, SPI_speed_profil_length_SH);} break;
	case ARM_LEFT:{Serial.println("saving arm left profile");sdloader::saveArry_to_file(spi_vs_speed_profile_2_location, DACData, SPI_speed_profil_length_SH);} break;
	case ARM_RIGHT:{Serial.println("saving arm right profile");sdloader::saveArry_to_file(spi_vs_speed_profile_3_location, DACData, SPI_speed_profil_length_SH);}break; 
	}
	
	myEvent->export_data_to_sd();
}


void mechanical_sw_mode_creasing_out(){
	Serial.println("creasing Set");
	creaZer.setSPIcreasingDetect(true);
	creaZer.creasingPulseOut();
	creaZer.advance_numberOfCreasing();
	setLCD_Event_creasing(true);
}

void mechanical_Rotary_sw_mode_session_chenge(){// these fuction will be called by the mechanical button to change the profile type which is to be loadded tp next
	Serial.println("session changed");
	RGB_leds.set_smartFlickering(5);
	// auto pilot session changing. read different files from SD card.
	switch (spi_vs_speed_profile_type_auto_pilot)// Rotary switch
	{
		case DEFAULT_PROFILE:{Loading_profile_switch(NECK_LINE);}break;
		case NECK_LINE:{Loading_profile_switch(ARM_LEFT);} break;
		case ARM_LEFT:{Loading_profile_switch(ARM_RIGHT);} break;
		case ARM_RIGHT:{Loading_profile_switch(DEFAULT_PROFILE);}break;
	}
}

void Loading_profile_switch(SPI_PROFILE_CATOGERY profile_type){// LCD will call these functions to change the profile type which is to be lodded to next
	switch (profile_type)
	{
	case DEFAULT_PROFILE:{msg_teaching_t0_message =  msg_sew_assist_auto_t3_message = LCD_text_meassage0; spi_vs_speed_profile_type_saving = spi_vs_speed_profile_type_auto_pilot = DEFAULT_PROFILE;  myEvent = &defaultProfileEvent; Serial.println("Profile type change to DEFAULT");}
		break;
	case NECK_LINE:{ msg_teaching_t0_message =  msg_sew_assist_auto_t3_message = LCD_text_meassage1; spi_vs_speed_profile_type_saving = spi_vs_speed_profile_type_auto_pilot = NECK_LINE;  myEvent = &neckProfileEvent; Serial.println("Profile type change to NECK LINE");}
		break;
	case ARM_LEFT:{msg_teaching_t0_message =  msg_sew_assist_auto_t3_message = LCD_text_meassage2; spi_vs_speed_profile_type_saving = spi_vs_speed_profile_type_auto_pilot = ARM_LEFT;  myEvent = &armLProfileEvent; Serial.println("Profile type change to ARM LEFT");}
		break;
	case ARM_RIGHT:{msg_teaching_t0_message = msg_sew_assist_auto_t3_message = LCD_text_meassage3; spi_vs_speed_profile_type_saving = spi_vs_speed_profile_type_auto_pilot = ARM_RIGHT;  myEvent = &armRProfileEvent; Serial.println("Profile type change to ARM RIGHT");}
		break;
	}

	Reset_other_parameters();	
	profile_type_print(spi_vs_speed_profile_type_auto_pilot);
	sdloader::resetArray_to_null(DACData,SIZE_OF_DAC_DATA_ARRY);
	SD_OPERATION_RESULTS result = sdloader :: loading_profile(DACData, SIZE_OF_DAC_DATA_ARRY, spi_vs_speed_profile_type_auto_pilot, SPI_speed_profil_length_SH);
	
	profile_type_print(spi_vs_speed_profile_type_auto_pilot);
	if (result!=SD_OK)
	{
		Serial.println("error");
		
	}	
	SPI_speed_profil_length_SH - getTeachProfile_length(DACData,SIZE_OF_DAC_DATA_ARRY);
	
	setLCD_Event_autopilot_session_chenged(true);
}


void mechanical_button_mode_chenge(){
	if ((switch_mode == CREASING)&&(getAutoPilot_EN()))
	{
		Serial.println("mechanical button mode - Session");
		switch_mode = SESSION_CHENGE;
		button.attachClick(mechanical_Rotary_sw_mode_session_chenge);
		return;
	}
	else if (switch_mode == SESSION_CHENGE)
	{
		Serial.println("mechanical button mode - Creasing");
		switch_mode = CREASING;
		button.attachClick(mechanical_sw_mode_creasing_out);
		return;
	}
}

void profile_type_print(SPI_PROFILE_CATOGERY temp){
	Serial.print("profile type: ");
	// auto pilot session changing. read different files from SD card.
	switch (temp)
	{
		case NECK_LINE:{ Serial.println("Profile type NECK LINE");}break;
		case ARM_LEFT:{Serial.println("Profile type ARM LEFT");} break;
		case ARM_RIGHT:{Serial.println("Profile type ARM RIGHT");} break;
		case DEFAULT_PROFILE:{Serial.println("Profile type DEFAULT");}break;
	}
}



void foot_activate(){

	switch (Active_motor_type_struct.Active_motor_type)
	{
		case ISM:{
			digitalWrite(FOOT,HIGH);
		}
		break;
		case PEGASUS_HPV_90:{

			dac.setVoltage(680,false);
		}
		break;

	}
	setState_trim(false);
	setState_foot(true);
}
void trim_activate(){
	unsigned int value = Active_motor_type_struct.motor_trimmer_activation_value;
	switch (Active_motor_type_struct.Active_motor_type)
	{

		case ISM:{
			digitalWrite(TRIM,HIGH);
		}
		break;
		case PEGASUS_HPV_90:{
			//dac.setVoltage((Active_motor_type_struct.motor_trimmer_activation_value*1000)/1.2,false);
			dac.setVoltage(300,false);
		}
		break;

	}	
		setState_foot(true);
		setState_trim(true);
	}

	void ideal(){ switch (Active_motor_type_struct.Active_motor_type)
		{
			case ISM:{
				digitalWrite(FOOT,LOW);
				digitalWrite(TRIM,LOW);
			}
			break;
			case PEGASUS_HPV_90:{
				dac.setVoltage(1600,false);
			}
			break;

		}

		setState_foot(false);
		setState_trim(false);
		}

void endcutter_event_reg_wrap(){
	chMtxLock(&Wheel_Cutter);
	myEvent->setRegistation_request(true);
	myEvent->setAction_request(true);
	chMtxUnlock(&Wheel_Cutter);
}