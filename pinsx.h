/*
 * pinsx.h
 *
 * Created: 12/20/2017 12:19:37 PM
 *  Author: dhanushkac
 */ 


#ifndef PINSX_H_
#define PINSX_H_


#define DEBUG_LED 13
#define LED 13

#define  PCB_VER2
// pins
#define analogPin0 A15
#define analogPin1 A16

#define creasingIn 39

//new board
/*
#ifdef PCB_VER_1_1

//#define AUTO_CUTTER 15

#define RLY2 14
#define FOOT 7
#define TRIM 6
#define BUZZER 32
#define BREATHING_LED 5
#define CREASING_OUT 16
#define END_CUTTER_SENS 9
#define AP_AUTO_START_SENS 29
#define END_CUTTER_OUT 15
#define STEPPER_PULSE 8
#define interruptPin 28
*/

#ifdef PCB_VER2

//#define interruptPin 30
#define interruptPin 28
#define RLY2 14
#define FOOT 7
#define TRIM 6
#define BUZZER 32
#define BREATHING_LED 5
#define CREASING_OUT 16
#define END_CUTTER_SENS 9
#define AP_AUTO_START_SENS 29
#define END_CUTTER_OUT 15
#define STEPPER_PULSE 8
#else

//#define FOOT 28
//#define TRIM 14
#define BUZZER 33
#define BREATHING_LED 1
#define CREASING_OUT 29
#endif


#endif /* PINSX_H_ */