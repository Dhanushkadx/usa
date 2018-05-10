/*
 * statements.h
 *
 * Created: 3/9/2017 8:57:36 AM
 *  Author: DhanushkaC
 */ 


#ifndef STATEMENTS_H_
#define STATEMENTS_H_
#include "sdloader.h"
#include "pinsx.h"

// spi emulator
long previousMillis = 0;       


long interval = 1000;
// Nextion LCD
#define mySerial Serial2
#define DAC_MAX_RESOLUTION_DAC_VALUE 4090
// Machine parameters
//#define JUKI
#define PEGASUS
#define JUKI_MAX_RPM_TRUE_VOLTAGE_3_L 1.8
#define ISM_MAX_RPM_TRUE_VOLTAGE_3_L 1.8

#define PEGASUS_HPV_90_MAX_RPM_TRUE_VOLTAGE_1L 5
#define PEGASUS_HPV_90_IDEAL_TRUE_VOLTAGE_1L 2.23
#define PEGASUS_HPV_90_AP_IDEAL_TRUE_VOLTAGE_1L 2.4
#define ISM_IDEAL_TRUE_VOLTAGE_3_L 0


//#define DEFAULT_CALIB_MAX_RPM_DAC_VALUE (ISM_MAX_RPM_TRUE_VOLTAGE_3_L*1000)/1.2
//#define DEFAULT_CALIB_IDEAL_DAC_VALUE (ISM_IDEAL_TRUE_VOLTAGE_3_L*1000)/1.2
//#define DEFAULT_CALIB_IDEAL_AUTO_PILOT DEFAULT_CALIB_IDEAL_DAC_VALUE +1100

#define DEFAULT_CALIB_MAX_RPM_DAC_VALUE (PEGASUS_HPV_90_MAX_RPM_TRUE_VOLTAGE_1L*1000)/1.2
#define DEFAULT_CALIB_IDEAL_DAC_VALUE (PEGASUS_HPV_90_IDEAL_TRUE_VOLTAGE_1L*1000)/1.2
#define DEFAULT_CALIB_IDEAL_AUTO_PILOT (PEGASUS_HPV_90_AP_IDEAL_TRUE_VOLTAGE_1L * 1000)/1.2

// analog chanel offsets
#define DEAFULT_AN_CH0_OFFSET 550
#define DEAFULT_AN_CH1_OFFSET 0


//Calibrations
int CALIBRATE_analogSamplesAverageCH0_adjestment = DEAFULT_AN_CH0_OFFSET;
int CALIBRATE_analogSamplesAverageCH1_adjestment = DEAFULT_AN_CH1_OFFSET;

// we use a structure for storing machine specific data

// Parameter Data**************
struct Sewing_machine_calib_data {	
	char* motor_brand_name;
	char* motor_model_number;
	eMotor_type Active_motor_type;
	unsigned int motor_ideal_value;
	unsigned int motor_max_RPM_value;
	unsigned int motor_foot_lifting_vale;
	unsigned int motor_trimmer_activation_value;
} JUKY_3ZZ_struct, ISM_struct, PEGASUS_HPV_90_struct,  Active_motor_type_struct;



//JUKY_3ZZ.motor_brand_name = "JUKY 3 Step (3ZZ)";

//For ISM or JUKY 3 step 
//unsigned int CALIBRATE_DAC_IDEAL_VALUE = 0;
//unsigned int CALIBRATE_DACout_MIN=850;
//unsigned int CALIBRATE_AuroPilot_DACout_MIN=1080;
//int CALIBRATE_DACout_MAX=1400;
//int CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value=DAC_VALUE_OF_1_8V_OUT;
//int CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value=CALIBRATE_DACout_MIN;
//int CALIBRATE_PWMout_MIN=100;

//Here we assigning values for actual variables 
unsigned int CALIB_ideal_DAC_value = DEFAULT_CALIB_IDEAL_DAC_VALUE;
unsigned int CALIB_MAX_RPM_DAC_value = DEFAULT_CALIB_MAX_RPM_DAC_VALUE;

unsigned int CALIB_AuroPilot_DAC_ideal_value= DEFAULT_CALIB_IDEAL_AUTO_PILOT;


int CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value;
int CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value;

static int analogLowCH0 = 00; //613 [82] analog reading from load cell for low end test load
static int analogLowCH1 = 300; //613 [82] analog reading from load cell for low end test load

// High end of the test load values

static int analogHighCH0 = 475; // [1022] analog reading from load cell for high end test load
static int analogHighCH1 = 780; // [1022] analog reading from load cell for high end test load
/*

#ifdef JUKI
int AP_semiAuto_en_min_analogCH0_input=400;
int SPI_teaching_en_min_analogCH0_input=160;  
#else if YAMATO
int AP_semiAuto_en_min_analogCH0_input=450;
int SPI_teaching_en_min_analogCH0_input=450;
#endif*/

#ifdef PEGASUS
int AP_semiAuto_en_min_analogCH0_input=300;//************************ check this
int SPI_teaching_en_min_analogCH0_input=100;
#endif

//Analog Processor 

// analog sampling
long Time_lastPWM_out_sample_recorded=0,Time_lastPWMWritten=0;
unsigned long Time_lastDAC_out_sample_recorded=0,Time_lastDACWritten=0;
long SPI_updating_time_out=200;

int DACDataIndex = 0;


#define SIZE_OF_DAC_DATA_ARRY 3000

unsigned int DACData[SIZE_OF_DAC_DATA_ARRY][4];


// Values for the analog sample buffer for running average to smooth analogue reads
static int samplesBufferCH0 = 25; // Should be the same as the number of samples
int analogSamplesCH0[25] = {0}; // Number of analog samples to average and set to 0
int lastSampleIndexCH0 = 0; // Last analog sample
long sampleBufferTotalCH0 = 0; // The sum of all the samples held in the buffer


static int samplesBufferCH1 = 5; // Should be the same as the number of samples
int analogSamplesCH1[5] = {0}; // Number of analog samples to average and set to 0
int lastSampleIndexCH1 = 0; // Last analog sample
long sampleBufferTotalCH1 = 0; // The sum of all the samples held in the buffer


//SPI 
volatile boolean SPIdetect = false;
volatile unsigned int currentSPI=0;
volatile unsigned long previousSPI_register_time=0;
volatile unsigned int currentSPI_register_time=0;
volatile unsigned int SPI_count_teaching_session_SH=0;
boolean DACData_buf_full =false;
unsigned int zeroSpeed_detectionTime_starting_point =1;
// ISR entry time
volatile uint32_t tIsr = 0;


//Second Sensor analog events
long start_ThReceivedTime =0;
long firstThReceivedTime=0,SecondThReceivedTime=0, therdrdThReceivedTime =0;
long Th_1ReceivedTime=0, Th_2ReceivedTime=0;
bool paddle_new_detection_foot = true , paddle_new_detection_trim = true;

//state , event flags
volatile int occurenc_control = 0;
volatile unsigned int eventCH1=0;
 unsigned int eventCH0=0;
// initialize semaphore as taken
BSEMAPHORE_DECL(isrStepperSync, 1);
// initialize semaphore as taken
BSEMAPHORE_DECL(footSem, 1);
// initialize semaphore as taken
BSEMAPHORE_DECL(trimSem, 1);
// initialize semaphore as taken
BSEMAPHORE_DECL(creasingSem, 1);
// initialize semaphore as taken
BSEMAPHORE_DECL(buzzerSem, 1);


/*
 * Pointer to the UART handler thread.
 */
thread_t *pThread6Special_functions;
thread_t *pThread4;

//serial event hadling
// Mutex for atomic access to data.
MUTEX_DECL(SerialDataSH_Mutex_CH0);
MUTEX_DECL(SerialDataSH_Mutex_CH1);
MUTEX_DECL(SerialLCDcommunication);
MUTEX_DECL(Flags_communication);
MUTEX_DECL(Event_communication);
MUTEX_DECL(Event_creasing);
MUTEX_DECL(General_LCDcommunication);
MUTEX_DECL(Foot_trim_data);
MUTEX_DECL(DAC_data);
MUTEX_DECL(ADC_DATA_SH);
MUTEX_DECL(Wheel_Cutter);
MUTEX_DECL(au_feeder_data);


//event_source_t network_event_source;
//event_source_t serial_event_source;


char  serial1inputString [25] = "";         // a string to hold incoming data
int  serial1inputStringBuffIndex=0;

char  serial2inputString [25] = "";         // a string to hold incoming data
int  serial2inputStringBuffIndex=0;
String stringOne = "A/n";
boolean serial1stringComplete = false;  // whether the string is complete
boolean serial2stringComplete = false;


typedef enum eStateMODE_autoPilot_mode {FULL_AUTO,SEMI_AUTO};
	eStateMODE_autoPilot_mode AutoPilot_MODE=FULL_AUTO;
	
typedef enum  eStateMODE {UNKNOWNS,AUTO_DRIVE_TEST, AUTO_PILOT, AUTO_PILOT_CYCLE_REST, MANUAL_SEW, SPI_TEACHING, SETUP_ANALOG} ;
	eStateMODE current_MODE = MANUAL_SEW;
	eStateMODE prev_MODE = UNKNOWNS;
	
typedef enum eAUTO_PILOT_RESULTS {RESULT_AU_BUF_OVER, RESULT_AU_CANCEL, RESULT_AU_PUS, RESULT_AU_SUCSEDD_DONE, RESULT_AU_PROCCESING}; 	
	


typedef enum eResult_teaching_states {RESULT_SPI_TEACHING_CANCEL,RESULT_SPI_TEACHING_PROCCESING}; 	
//#define RESULT_SPI_TEACHING_CANCEL 1
//#define RESULT_SPI_TEACHING_PROCCESING 0
//enablers
boolean Serial_push_EN_analogInputData = false;
boolean Serial_push_EN_autoPilotData = true;
boolean SPI_speed_profil_teaching_EN = false;
boolean SPI_speed_teaching_teminator_EN = false;
boolean SPI_speed_profil_reset = false;
boolean SPI_zero_recode =false;
boolean AN_out_MC_EN= true;
boolean Setup_EN =false;

boolean AutoDriveTest_EN=false, AutoPilot_EN_DIS=false;
boolean AutoPilot_EN =false, AutoPilot_forceStart_EN = false;
boolean sewingAssistent_EN=false;
boolean lcd_debug=false;



boolean Sta_foot = false , Sta_trim =false;
boolean EN_foot = false , EN_trim =false;
boolean END_CUT_EN = false;
// Global Serial Data


volatile int AN_CH0_sensor_data_RAW_GLOB=0;
volatile int AN_CH1_sensor_data_RAW_GLOB=0;
volatile int AN_CH0_sensor_data_AVR_GLOB=0;
volatile int AN_CH1_sensor_data_AVR_GLOB=0;

volatile int trueDACout_forDisplay_SH = 0;
//volatile long analogSamplesAverageCH0_SH=0;

volatile int DACoutValue_teachng_REC_SH=0;
volatile unsigned int DACoutValue_Actual_SH=0;
volatile int DACoutValue_autoPilot_proccessed_SH = 0;
volatile unsigned int DACDataIndex_SH=0;
volatile unsigned int DACDataArray_curruntIndexValue_SH=0;
volatile unsigned int DACDataArray_SPI_of_curruntIndexValue_SH=0;
unsigned int SPI_speed_profil_length_SH=0;

unsigned int DACDataIndex_AP=0;
// updaters
volatile boolean SPI_updated=true;

//LCD
boolean LCD_Event_creasing = false;
boolean LCD_Event_autopilot_canceled =false;
boolean LCD_Event_autopilot_session_chenged = false;
boolean LCD_refresh = false;
boolean Nex_LCD_LastUpdate_Force =false;
boolean drawSavedSPI =false;

//LCD text messages
char* LCD_message_Strings[]={"NECK LINE", "ARM HOLE LEFT", "ARM HOLE RIGHT",
"This is string 4", "This is string 5","This is string 6"};

String LCD_text_meassage0 = "DEFAULT SEW";
String LCD_text_meassage1 = "NECK_LINE";
String LCD_text_meassage2 = "ARM HOLE LEFT";
String LCD_text_meassage3 = "ARM HOLE RIGHT";

//LCD massage holders
String msg_sew_assist_auto_t3_message = LCD_text_meassage0;
String msg_teaching_t0_message = LCD_text_meassage0;
//msg_teaching_t0_message = LCD_text_meassage0;

//SD
char* spi_vs_speed_default_profile_location = "USADATA/SPI/Default/svs_df.txt";
char* spi_vs_speed_profile_1_location = "USADATA/SPI/Default/svs_1.txt";
char* spi_vs_speed_profile_2_location = "USADATA/SPI/Default/svs_2.txt";
char* spi_vs_speed_profile_3_location = "USADATA/SPI/Default/svs_3.txt";

//Foot and trim behavior control
unsigned int TH_ch1_detection_min_threshold_GLOBAL;
unsigned int TI_first_pulse_registering_delay_GLOBAL;//ms
unsigned int TI_second_puls_stating_delay_GLOBAL;// ms default
unsigned int TH_ch1_trim_detection_threshold_GLOBAL;
unsigned int TI_second_pulse_rising_delay_GLOBAL;
unsigned int TI_second_pulse_rising_debounce_GLOBAL;

	
	
	
//creasing
#define CREASING_NUMERICAL_VALUE_OF_REG 1
typedef enum eMECHANICAL_BUTTON_MODE {CREASING, SESSION_CHENGE};
	eMECHANICAL_BUTTON_MODE switch_mode = CREASING;
	
#define sys_dbSerial Serial	
	
#ifdef SYSTEM_DEBUG_SERIAL_ENABLE
#define sys_dbSerialPrint(a)    sys_dbSerial.print(a)
#define sys_dbSerialPrintln(a)  sys_dbSerial.println(a)
#define sys_dbSerialBegin(a)    sys_dbSerial.begin(a)
#else
#define sys_dbSerialPrint(a)    do{}while(0)
#define sys_dbSerialPrintln(a)  do{}while(0)
#define sys_dbSerialBegin(a)    do{}while(0)
#endif




// auto feeder and stepperSync parameters

unsigned int pulse_width, au_feeder_cutter_act_delay, au_feeder_cutting_delay;
#endif /* STATEMENTS_H_ */