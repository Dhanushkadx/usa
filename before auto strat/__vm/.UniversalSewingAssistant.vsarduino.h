/* 
	Editor: http://www.visualmicro.com
			visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
			the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
			all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
			note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Teensy 3.6, Platform=teensy3, Package=teensy
*/

#define __HARDWARE_MK66fx1m0__
#define __HARDWARE_MK66FX1M0__
#define ARDUINO 10801
#define ARDUINO_MAIN
#define printf iprintf
#define __TEENSY3__
#define __MK66FX1M0__
#define TEENSYDUINO 131
#define __FPU_PRESENT 1U
#define ARDUINO 10801
#define F_CPU {build.fcpu}
#define {build.usbtype}
#define LAYOUT_{build.keylayout}
static THD_FUNCTION(Thd1_main, arg);
static THD_FUNCTION(Thd2_sysBreathing, arg);
static THD_FUNCTION(Thd4_display, arg);
static THD_FUNCTION(Thd5_Serial, arg);
static THD_FUNCTION(Thd6_analogCh1, arg);
static THD_FUNCTION(Thd7_analogCh0, arg);
static THD_FUNCTION(Thd8_creasing, arg);
static THD_FUNCTION(Thd9_smartGlow, arg);
static THD_FUNCTION(Thd10_audio, arg);
static THD_FUNCTION(Thd11_paddlEvents, arg);
static THD_FUNCTION(Thd12_Sensor, arg);
static THD_FUNCTION(Trim, arg);
void system_initialization();
void cutter_on();
void cutter_off();
//
void chSetup();
//
void mainTask();
eResult_teaching_states teachingSewing(unsigned int _dacout);
unsigned int manualSewing();
eAUTO_PILOT_RESULTS autoPilotProcessor();
void serialEventRTOS();
void serialPrinting();
unsigned int getTeachProfile_length(unsigned int array[][4], unsigned int length_of_array);
void Reset_other_parameters();
void resetTeachProfile();
void teachingTerminator();
void mechanical_sw_mode_creasing_out();
void mechanical_Rotary_sw_mode_session_chenge();
void Loading_profile_switch(SPI_PROFILE_CATOGERY profile_type);
void mechanical_button_mode_chenge();
void profile_type_print(SPI_PROFILE_CATOGERY temp);
void foot_activate();
void trim_activate();
void ideal();
void endcutter_event_reg_wrap();

#include "wprogram.h"
#include "UniversalSewingAssistant.ino"
