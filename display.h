
/*
 * display.h
 *
 * Created: 4/7/2017 10:16:32 AM
 *  Author: DhanushkaC
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_


#include "Arduino.h"
#include "autoCreasing.h"
#include "smart_paddle_sensor.h"
//autoCreasing :: creaZer;
void Loading_profile_switch(SPI_PROFILE_CATOGERY profile_type);
void mechanical_Rotary_sw_mode_session_chenge();
unsigned int getntotalCreasingPointstoLCD(autoCreasing obj);
void setTeachingSewing_EN(boolean);
void setAutoDriveTest_EN(boolean);
void setAutoPilot_EN(boolean);
void setTeachingReset_EN(boolean);
void setSetup_EN(boolean);
void setSerial_push_autoPilotData_EN(boolean);
boolean getSerial_push_autoPilotData_EN();
void setSerial_push_analogInputData_EN(boolean);
boolean getSerial_push_analogInputData_EN();
void setForceStart_autoPilot(boolean);
//boolean getForceStart_autoPilot();
void setSPIcreasingDetect(boolean);
void mechanical_sw_mode_creasing_out();
void setLCD_Event_creasing(boolean);
boolean getLCD_Event_creasing();
boolean getLCD_refresh();
void setLCD_refresh(boolean);
boolean getLCD_Event_LCD_Event_autopilot_canceled();
boolean getLCD_Event_autopilot_session_chenged();
void setLCD_Event_autopilot_canceled(boolean _xstate);
void setLCD_Event_autopilot_session_chenged(boolean _xstate);
void setCutterActivation_request_LCD(boolean _xstate); 
void setState_from_LCD(CUTTER_STATES _xstate);
void endcutter_event_reg_wrap();


long Nex_LCD_LastUpdate_Millis = 0;  
long Nex_LCD_update_interval = 20; 
typedef enum eNex_screenID {eNex_unknown, eNex_teaching, eNex_autopilot, eNex_debug,eNex_debug_advanced, eNex_autoDrive, eNex_home, eNex_msg, eNex_main_setup, eNex_ap_setup, eNex_stepperSync, eNex_setup_foot_trim, eNex_menu, eNex_setup_analog, eNex_setup_autoPilot, eNex_machine_type_select};
	eNex_screenID NexCurrent_screenID= eNex_home;
	eNex_screenID NexPrev_screenID= eNex_unknown;
	
//wave form
NexWaveform s0 = NexWaveform(3, 1, "s0");
// Progress Bar
NexProgressBar home_paddiling_progress_bar = NexProgressBar(0,10,"j0");
NexText home_t0 = NexText(0, 11, "t0");

NexProgressBar auto_pilot_Cycle_progress_bar = NexProgressBar(4,6,"j0");
NexProgressBar auto_pilot_RPM_progress_bar = NexProgressBar(4,8,"j1");

NexProgressBar sew_assist_auto_pilot_Cycle_progress_bar = NexProgressBar(7,5,"j1");
NexProgressBar sew_assist_auto_pilot_RPM_progress_bar = NexProgressBar(7,2,"j0");

NexText auto_pilot_progress_barText = NexText(4,5,"t2");

NexText sew_assist_auto_pilot_progress_barText = NexText(7,6,"t5");
NexText sew_assist_auto_pilot_modeText = NexText(7,1,"t0");
NexText sew_assist_auto_t2 = NexText (7, 12, "t2");
NexText sew_assist_auto_t3 = NexText (7, 13, "t3");
// msg

NexText msg_t0 =  NexText(17,2,"t0");
NexButton msg_b0 = NexButton(17, 3, "b0");
NexButton msg_b1 = NexButton(17, 4, "b1");
//buttons
//**********Home_page**********
NexButton home_b0 = NexButton(0, 1, "b0");
NexButton home_b1 = NexButton(0, 2, "b1");
//**********teaching_page******
NexDSButton bt0 = NexDSButton(3, 7, "bt0");
NexDSButton bt1 = NexDSButton(3, 8, "bt1");
NexDSButton bt2 = NexDSButton(3, 10, "bt2");

NexDSButton bt3 = NexDSButton(3, 12, "bt3");
NexDSButton bt4 = NexDSButton(3, 13, "bt4");
NexDSButton bt5 = NexDSButton(3, 14, "bt5");
NexDSButton bt6 = NexDSButton(3, 15, "bt6");

NexButton b0 = NexButton(3, 9, "b0");
NexButton b2 = NexButton(3, 6, "b2");
//NexButton b3 = NexButton(3, 7, "b3");
NexButton b5 = NexButton(3, 2, "b5");
NexNumber n0 = NexNumber(3, 4, "n0");

NexText t0 = NexText (3, 11, "t0");// session 
NexText t1 = NexText (3, 3, "t1");// creasing
NexText t2 = NexText (3, 5, "t2");
NexText t3 = NexText(3, 16, "t3");

//**********Setup_main_page**********
NexText setup_main_t0 = NexText(10, 1, "t0");

NexButton setup_main_b0 = NexButton(10, 2, "b0");
NexButton setup_main_b1 = NexButton(10, 3, "b1");
NexButton setup_main_b2 = NexButton(10, 4, "b2");
NexButton setup_main_b3 = NexButton(10, 5, "b3");
NexButton setup_main_b4 = NexButton(10, 6, "b4");

//**********Setup_ap_page**********
NexButton setup_ap_b0 = NexButton(12, 8, "b0");
NexButton setup_ap_b1 = NexButton(12, 9, "b1");

NexDSButton setup_ap_bt0 = NexDSButton(12, 2, "bt0");
NexDSButton setup_ap_bt1 = NexDSButton(12, 5, "bt1");
NexDSButton setup_ap_bt2 = NexDSButton(12, 6, "bt2");
NexDSButton setup_ap_bt3 = NexDSButton(12, 11, "bt3");
NexDSButton setup_ap_bt4 = NexDSButton(12, 15, "bt4");
NexDSButton setup_ap_bt5 = NexDSButton(12, 16, "bt5");
NexDSButton setup_ap_bt6 = NexDSButton(12, 20, "bt6");
NexDSButton setup_ap_bt7 = NexDSButton(12, 21, "bt7");

NexNumber setup_ap_n0 = NexNumber(12, 12, "n0");
NexText setup_ap_t7 = NexText(12, 18, "t7");
NexText setup_ap_t0 = NexText(12, 10, "t0");


//**********Setup_analog_page********
NexButton setup_analog_b0 = NexButton(11, 9, "b0");
NexButton setup_analog_b1 = NexButton(11, 10, "b1");
NexButton setup_analog_b2 = NexButton(11, 8, "b2");
NexButton setup_analog_b3 = NexButton(11, 3, "b3");
NexButton setup_analog_b4 = NexButton(11, 18, "b4");
NexButton setup_analog_b5 = NexButton(11, 19, "b5");
NexButton setup_analog_b6 = NexButton(11, 26, "b6");

NexNumber setup_analog_n0 = NexNumber(11, 13, "n0");
NexNumber setup_analog_n1 = NexNumber(11, 15, "n1");
NexNumber setup_analog_n2 = NexNumber(11, 16, "n2");
NexNumber setup_analog_n3 = NexNumber(11, 2, "n3");
NexNumber setup_analog_n4 = NexNumber(11, 6, "n4");
NexNumber setup_analog_n5 = NexNumber(11, 4, "n5");
NexNumber setup_analog_n6 = NexNumber(11, 20, "n6");
NexNumber setup_analog_n7 = NexNumber(11, 22, "n7");
NexNumber setup_analog_n8 = NexNumber(11, 23, "n8");

//***********Foot_trim_page**************
NexText Foot_trim_t0 = NexText (14, 1, "t0");
NexText Foot_trim_t1 = NexText (14, 1, "t1");
NexText Foot_trim_t2 = NexText (14, 1, "t2");
NexText Foot_trim_t3 = NexText (14, 1, "t3");
NexText Foot_trim_t4 = NexText (14, 1, "t4");
NexText Foot_trim_t5 = NexText (14, 1, "t5");
NexText Foot_trim_t6 = NexText (14, 1, "t6");
NexText Foot_trim_t8 = NexText (14, 21, "t8");
NexDSButton Foot_trim_bt0 = NexDSButton(14, 2, "bt0");
NexDSButton Foot_trim_bt1 = NexDSButton(14, 3, "bt1");
NexDSButton Foot_trim_bt2 = NexDSButton(14, 4, "bt2");
NexButton Foot_trim_b0 = NexButton(14,5,"b0");
NexButton Foot_trim_b1 = NexButton(14,18,"b1");

NexNumber Foot_trim_n0 = NexNumber(14, 6, "n0");
NexNumber Foot_trim_n1 = NexNumber(14, 7, "n1");
NexNumber Foot_trim_n2 = NexNumber(14, 8, "n2");
NexNumber Foot_trim_n3 = NexNumber(14, 9, "n3");
NexNumber Foot_trim_n4 = NexNumber(14, 10, "n4");
NexNumber Foot_trim_n5 = NexNumber(14, 11, "n5");
NexNumber Foot_trim_n6 = NexNumber(14, 19, "n6");

//**********auto_drive page*****
NexDSButton Auto_bt0 = NexDSButton(4, 8, "bt0");
NexButton Auto_b1 = NexButton(4, 1, "b1");
NexButton Auto_b5 = NexButton(4, 2, "b5");

//**********debug page**********
//NexButton debug_b0 = NexButton(5,1,"b0");
NexButton debug_b5 = NexButton(5,4,"b5");
NexButton debug_b7 = NexButton(5,10,"b7");

NexDSButton debug_bt0 = NexDSButton(5, 5, "bt0");
NexDSButton debug_bt1 = NexDSButton(5, 6, "bt1");
NexDSButton debug_bt2 = NexDSButton(5, 8, "bt2");
NexDSButton debug_bt3 = NexDSButton(5, 9, "bt2");
NexNumber debug_n0 = NexNumber(5, 10, "n0");
NexText debug_t0 = NexText(5,  1,  "t0");

//***********debug_advanced_page***********
NexSlider debug_advanced_h0 = NexSlider(15, 12, "h0");
NexText debug_advanced_t7 = NexText(15,  14,  "t7");
NexNumber debug_advanced_n1 = NexNumber(15,  3,  "n1");
NexNumber debug_advanced_n2 = NexNumber(15,  6,  "n2");

NexDSButton debug_advanced_bt0 = NexDSButton(15, 16, "bt0");
NexDSButton debug_advanced_bt1 = NexDSButton(15, 17, "bt1");
NexDSButton debug_advanced_bt2 = NexDSButton(15, 18, "bt2");

NexButton debug_advanced_b0 = NexButton(15, 4, "b0");
NexButton debug_advanced_b1 = NexButton(15, 5, "b1");

NexButton debug_advanced_b2 = NexButton(15, 7, "b2");
NexButton debug_advanced_b3 = NexButton(15, 8, "b3");

NexButton debug_advanced_b4 = NexButton(15, 13, "b4");
NexButton debug_advanced_b5 = NexButton(15, 2, "b4");
NexButton debug_advanced_b6 = NexButton(15, 19, "b6");

//****************stepperSync************************
NexNumber stepperSync_n0 = NexNumber(16,  16,  "n0");
NexNumber stepperSync_n1 = NexNumber(16,  3,  "n1");
NexNumber stepperSync_n2 = NexNumber(16,  6,  "n2");

NexButton stepperSync_b0 = NexButton(16, 4, "b0");
NexButton stepperSync_b1 = NexButton(16, 5, "b1");
NexButton stepperSync_b4 = NexButton(16, 12, "b4");
NexButton stepperSync_b5 = NexButton(16, 2, "b5");

NexButton stepperSync_b2 = NexButton(16, 7, "b2");
NexButton stepperSync_b3 = NexButton(16, 8, "b3");
NexButton stepperSync_b7 = NexButton(16, 15, "b7");
NexButton stepperSync_b8 = NexButton(16, 17, "b8");

NexText stepperSync_t7 = NexText(16,  14,  "t7");


//**********main_menu page******
NexButton menu_b7 = NexButton(2,6,"b7");
NexButton menu_b1 = NexButton(2,7,"b1");
NexButton menu_b2 = NexButton(2,2,"b2");
NexButton menu_b3 = NexButton(2,3,"b3");
NexButton menu_b4 = NexButton(2,4,"b4");
NexButton menu_b0 = NexButton(2,1,"b0");
NexButton menu_b5 = NexButton(2,9,"b5");

NexText menu_t0 = NexText (2, 8, "t0");

//sewing_assistant page*********
NexDSButton sew_assist_bt0 = NexDSButton(7, 9, "bt0");
NexDSButton sew_assist_bt1 = NexDSButton(7, 10, "bt1");
NexDSButton sew_assist_bt2 = NexDSButton(7, 11, "bt2");
NexDSButton sew_assist_bt3 = NexDSButton(7, 15, "bt3");

NexButton sew_assist_b3 = NexButton(7,4,"b3");

NexText sew_assist_t0 = NexText (7,1,"t0");
NexText sew_assist_t4 = NexText (7,15,"t4");
NexText sew_assist_t5 = NexText (7,6,"t5");
//NexText sew_assist_t7 = NexText (7,15,"t7");
//NexText sew_assist_t8 = NexText (7,16,"t8");

NexText sew_assist_t10 = NexText (7, 17, "t10");

NexText auto_t1 = NexText (4,5,"t1");
//NexPage sewAssistantpage = NexPage("sewAssistant")
/*
 * Register a button object to the touch event list.  
 */

 //Machine type select page
 NexText machine_select_t0 = NexText (13, 1, "t0");
 NexText machine_select_t8 = NexText (13, 8, "t8");
 NexDSButton machine_select_bt0 = NexDSButton(13, 2, "bt0");
 NexDSButton machine_select_bt1 = NexDSButton(13, 3, "bt1");
 NexDSButton machine_select_bt2 = NexDSButton(13, 4, "bt2");
 NexButton machine_select_b0 = NexButton(13,5,"b0");
 NexButton machine_select_b1 = NexButton(13,18,"b1");

 NexNumber machine_select_n0 = NexNumber(13, 6, "n0");
 NexNumber machine_select_n1 = NexNumber(13, 7, "n1");
 NexNumber machine_select_n2 = NexNumber(13, 8, "n2");
 NexNumber machine_select_n3 = NexNumber(13, 9, "n3");
 NexNumber machine_select_n4 = NexNumber(13, 10, "n4");
 NexNumber machine_select_n5 = NexNumber(13, 11, "n5");
 NexNumber machine_select_n6 = NexNumber(13, 19, "n6");


NexTouch *nex_listen_list_msg_page[] =
{
	&msg_t0,
	&msg_b0,
	&msg_b1,
	NULL
};


NexTouch *nex_listen_list_home_page[] =
{
	&home_b0,
	&home_b1,
	NULL
};

NexTouch *nex_listen_list_main_menu_page[] =
{
	&menu_b0,
	&menu_b1,
	&menu_b2,
	&menu_b3,
	&menu_b4,
	&menu_b7,
	&menu_b5,
	NULL
};

NexTouch *nex_listen_list_autoDrive_page[] =
{
	&Auto_bt0,
	&Auto_b1,
	&Auto_b5,
	NULL
};

NexTouch *nex_listen_list_teaching_page[] = 
{	&t0,
	&b0,
    &bt0,
	&bt1,
	&bt2,
	&bt3,
	&bt4,
	&bt5,
	&bt6,
	&b5,
	&b2,	
    NULL
};

NexTouch *nex_listen_list_sew_assistant_page[] =
{
	&sew_assist_bt0,
	&sew_assist_bt1,
	&sew_assist_bt2,
	&sew_assist_bt3,
	&sew_assist_b3,
	&sew_assist_auto_t3,
	NULL
};

NexTouch *nex_listen_list_debug_page[] =
{
	&debug_bt0,
	&debug_bt1,
	&debug_b5,
	&debug_b7,
	//&debug_b1,
	//&debug_b0,
	NULL
};

NexTouch *nex_listen_list_debug_advanced_page[] ={
	&debug_advanced_h0,
	&debug_advanced_bt0,
	&debug_advanced_bt1,
	&debug_advanced_bt2,
	&debug_advanced_b0,
	&debug_advanced_b1,
	&debug_advanced_b2,
	&debug_advanced_b3,
	&debug_advanced_b4,
	&debug_advanced_b5,
	&debug_advanced_b6,
	//&debug_b0,
	NULL

};

NexTouch *nex_listen_list_main_setup_page[] =
{
	&setup_main_b0,
	&setup_main_b1,
	&setup_main_b2,
	&setup_main_b3,
	&setup_main_b4,
	
	NULL
};

NexTouch *nex_listen_list_ap_setup_page[] =
{
	&setup_ap_b0,
	&setup_ap_b1,
	&setup_ap_bt0,
	&setup_ap_bt1,
	&setup_ap_bt2,
	&setup_ap_bt3,
	&setup_ap_bt4,
	&setup_ap_bt5,
	&setup_ap_bt6,
	&setup_ap_bt7,
	
	NULL
};


NexTouch *nex_listen_list_stepperSync_page[] =
{
	&stepperSync_b0,
	&stepperSync_b1,
	&stepperSync_b4,
	&stepperSync_b5,
	&stepperSync_b2,
	&stepperSync_b3,
	&stepperSync_b7,
	&stepperSync_b8,
	
	NULL
};

NexTouch *nex_listen_list_setup_foot_trim_page[] =
{
	&Foot_trim_bt0,
	&Foot_trim_bt1,
	&Foot_trim_bt2,
	&Foot_trim_b0,
	&Foot_trim_b1,
	NULL
};


NexTouch *nex_listen_list_analog_setup_page[] =
{
	&setup_analog_b0,
	&setup_analog_b1,
	&setup_analog_b2,
	&setup_analog_b3,
	&setup_analog_b4,
	&setup_analog_b5,
	&setup_analog_b6,
	NULL
};

NexTouch *nex_listen_list_machine_select_page[] =
{
	&machine_select_bt0,
	&machine_select_bt1,
	&machine_select_bt2,
	&machine_select_b0,
	&machine_select_b1,
	NULL
};

//Teaching graph
BSEMAPHORE_DECL(BS_teaching_graph, 1);

//NexText t0 = NexText(0,4,"t0");
//**********************************************************Msg******************************************************************
void msg_bt0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID=eNex_home;Serial.println("going Home"); sendCommand("page 0"); }
void msg_bt1PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID=eNex_home;Serial.println("going Home"); sendCommand("page 0"); LCD_Event_sd=true; LCD_Event_dac_module=true;}

//**********************************************************Home******************************************************************	

void home_bt0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID=eNex_menu;Serial.println("going Menu"); sendCommand("page 2"); }
void home_bt1PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID=eNex_menu;}
void home_bt2PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID=eNex_setup_analog;}
//***********************************************************teaching*******************************************************************

void t0PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	mechanical_Rotary_sw_mode_session_chenge();
}	

void bt0PopCallback(void *ptr){
	//nexSerial.print("click 2, 0");

	chBSemSignal(&buzzerSem);
	uint32_t dual_state;  
	bt0.getValue(&dual_state); 
	if(dual_state){bt1.setValue(0); setTeachingSewing_EN(true); }
	else{}	
	 }
void bt1PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	 uint32_t dual_state;
	 bt0.getValue(&dual_state);
	 if(dual_state){bt0.setValue(0); setTeachingSewing_EN(false); }
	 else{}
	 }
	 
void bt2PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	
	uint32_t dual_state;
	bt2.getValue(&dual_state);
	if(dual_state){  endcutter_event_reg_wrap(); }
	else{endcutter_event_reg_wrap();  }
}

void bt3PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state;
	bt3.getValue(&dual_state);
	if(dual_state){bt4.setValue(0); bt5.setValue(0); bt6.setValue(0); Loading_profile_switch(DEFAULT_PROFILE);}
	else{bt3.setValue(1);}

}
void bt4PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state;
	bt4.getValue(&dual_state);
	if(dual_state){bt3.setValue(0); bt5.setValue(0); bt6.setValue(0); Loading_profile_switch(NECK_LINE);}
	else{bt4.setValue(1);}	
}
void bt5PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state;
	bt5.getValue(&dual_state);
	if(dual_state){bt3.setValue(0); bt4.setValue(0); bt6.setValue(0); Loading_profile_switch(ARM_LEFT);}
	else{bt5.setValue(1);}
}
void bt6PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state;
	bt6.getValue(&dual_state);
	if(dual_state){bt3.setValue(0); bt4.setValue(0); bt5.setValue(0); Loading_profile_switch(ARM_RIGHT);}
	else{bt6.setValue(1);}
}

void b0PopCallback(void *ptr){chBSemSignal(&buzzerSem);  mechanical_sw_mode_creasing_out(); char buf[10]={0};  t1.setText(utoa(getntotalCreasingPointstoLCD(), buf, 10));}	 
void b5PopCallback(void *ptr){chBSemSignal(&buzzerSem);Serial.println("going back to Menu"); NexCurrent_screenID=eNex_menu; setTeachingSewing_EN(false); sendCommand("page 2");}
	
void b2PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	Serial.println("reset request"); 
	uint32_t dual_state;
	bt0.getValue(&dual_state);
	if(dual_state){bt0.setValue(0); setTeachingSewing_EN(false);}
	else{}
	setTeachingReset_EN(true); 
	setLCD_refresh(true);
	}
//**********************************************************auto_drive_test_main******************************************************************	
void Auto_bt0PopCallback(void *ptr){chBSemSignal(&buzzerSem); setAutoDriveTest_EN(true); setForceStart_autoPilot(true);}
void Auto_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); setAutoDriveTest_EN(false); Auto_bt0.setValue(false);}
void Auto_b5PopCallback(void *ptr){chBSemSignal(&buzzerSem); setAutoDriveTest_EN(false); NexCurrent_screenID=eNex_menu;}
	

//**********************************************************debug**********************************************************************	
void debug_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); Serial_push_EN_analogInputData=false;}
void debug_b5PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_menu;}
void debug_b7PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_debug_advanced; setSetup_EN(true);}

	
	void debug_bt0PopCallback(void *ptr){
		chBSemSignal(&buzzerSem);
		uint32_t dual_state;
		debug_bt0.getValue(&dual_state);
		if(dual_state){setSerial_push_analogInputData_EN(true); }
		else{setSerial_push_analogInputData_EN(false);}
	}
	
	void debug_bt1PopCallback(void *ptr){
		chBSemSignal(&buzzerSem);
		uint32_t dual_state;
		debug_bt1.getValue(&dual_state);
		if(dual_state){setSerial_push_autoPilotData_EN(true); }
		else{setSerial_push_autoPilotData_EN(false);}
	}
	void debug_bt2PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	uint32_t dual_state;
	debug_bt2.getValue(&dual_state);
	if (dual_state){}//Utility::enable_inttrupt_counting();}
	else{}//Utility::desable_inttrupt_counting();}
	}

//*********************************************************Advanced_debag_page**************************************************************
void debug_advanced_h0PopCallback(void *ptr)
{
	uint32_t dual_state; debug_advanced_bt2.getValue(&dual_state); if(!dual_state){debug_advanced_t7.setText("Invalid !");return;}
	uint32_t number = 0;
	debug_advanced_h0.getValue(&number);
	chMtxLock(&DAC_data);
	DACoutValue_Actual_SH = number;
	chMtxUnlock(&DAC_data);
	Serial.println(number);
	
	
}
void debug_advanced_bt0PopCallback(void *ptr){chBSemSignal(&buzzerSem); debug_advanced_bt1.setValue(0); debug_advanced_bt2.setValue(0); uint32_t temp; debug_advanced_n1.getValue(&temp); chMtxLock(&DAC_data); DACoutValue_Actual_SH = temp; chMtxUnlock(&DAC_data);}
void debug_advanced_bt1PopCallback(void *ptr){chBSemSignal(&buzzerSem); debug_advanced_bt0.setValue(0); debug_advanced_bt2.setValue(0); uint32_t temp; debug_advanced_n2.getValue(&temp); chMtxLock(&DAC_data); DACoutValue_Actual_SH = temp; chMtxUnlock(&DAC_data);}
void debug_advanced_bt2PopCallback(void *ptr){chBSemSignal(&buzzerSem); debug_advanced_bt0.setValue(0); debug_advanced_bt1.setValue(0); debug_advanced_h0.setValue(0); chMtxLock(&DAC_data); DACoutValue_Actual_SH = CALIB_ideal_DAC_value; chMtxUnlock(&DAC_data);  }

void debug_advanced_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state; debug_advanced_bt0.getValue(&dual_state); if(!dual_state){debug_advanced_t7.setText("Invalid !");return;} if(Active_motor_type_struct.Active_motor_type != PEGASUS_HPV_90){ debug_advanced_t7.setText("Invalid !"); return;}uint32_t temp; debug_advanced_n1.getValue(&temp); if(temp>0){temp--;} debug_advanced_n1.setValue(temp); chMtxLock(&DAC_data); DACoutValue_Actual_SH = temp; chMtxUnlock(&DAC_data); debug_advanced_t7.setText("");}            
void debug_advanced_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state; debug_advanced_bt0.getValue(&dual_state); if(!dual_state){debug_advanced_t7.setText("Invalid !");return;} if(Active_motor_type_struct.Active_motor_type != PEGASUS_HPV_90){ debug_advanced_t7.setText("Invalid !"); return;}uint32_t temp; debug_advanced_n1.getValue(&temp); temp++; debug_advanced_n1.setValue(temp);			 chMtxLock(&DAC_data); DACoutValue_Actual_SH = temp; chMtxUnlock(&DAC_data); debug_advanced_t7.setText("");}
void debug_advanced_b2PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state; debug_advanced_bt1.getValue(&dual_state); if(!dual_state){debug_advanced_t7.setText("Invalid !");return;} if(Active_motor_type_struct.Active_motor_type != PEGASUS_HPV_90){ debug_advanced_t7.setText("Invalid !"); return;}uint32_t temp; debug_advanced_n2.getValue(&temp); if(temp>0){temp--;} debug_advanced_n2.setValue(temp);  chMtxLock(&DAC_data); DACoutValue_Actual_SH = temp; chMtxUnlock(&DAC_data);debug_advanced_t7.setText("");}
void debug_advanced_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state; debug_advanced_bt1.getValue(&dual_state); if(!dual_state){debug_advanced_t7.setText("Invalid !");return;} if(Active_motor_type_struct.Active_motor_type != PEGASUS_HPV_90){ debug_advanced_t7.setText("Invalid !"); return;}uint32_t temp; debug_advanced_n2.getValue(&temp); temp++; debug_advanced_n2.setValue(temp);			   chMtxLock(&DAC_data); DACoutValue_Actual_SH = temp; chMtxUnlock(&DAC_data);debug_advanced_t7.setText("");}

void debug_advanced_b5PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_debug; setSetup_EN(false); }
void debug_advanced_b4PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state; debug_advanced_bt0.getValue(&dual_state); if(!dual_state){debug_advanced_t7.setText("Invalid !");return;} if(Active_motor_type_struct.Active_motor_type != PEGASUS_HPV_90){ debug_advanced_t7.setText("Invalid!"); return;}uint32_t temp; debug_advanced_n1.getValue(&temp); String v0 = String(temp); sdloader :: write_param_value_to_sd("USADATA/MASHINE/HPV901L.txt", "foot_dac_value", v0.c_str()); debug_advanced_t7.setText("Saved"); 
											
											sdloader :: loading_machine_para(Active_motor_type_struct.Active_motor_type,CALIB_ideal_DAC_value,CALIB_MAX_RPM_DAC_value,CALIB_AuroPilot_DAC_ideal_value,Active_motor_type_struct.motor_foot_lifting_vale,Active_motor_type_struct.motor_trimmer_activation_value);
											CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value = CALIB_MAX_RPM_DAC_value;
											CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value = CALIB_ideal_DAC_value;
}

void debug_advanced_b6PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t dual_state; debug_advanced_bt1.getValue(&dual_state); if(!dual_state){debug_advanced_t7.setText("Invalid !");return;} if(Active_motor_type_struct.Active_motor_type != PEGASUS_HPV_90){ debug_advanced_t7.setText("Invalid!"); return;}uint32_t temp; debug_advanced_n2.getValue(&temp); String v0 = String(temp); sdloader :: write_param_value_to_sd("USADATA/MASHINE/HPV901L.txt", "trim_dac_value", v0.c_str()); debug_advanced_t7.setText("Saved");
											sdloader :: loading_machine_para(Active_motor_type_struct.Active_motor_type,CALIB_ideal_DAC_value,CALIB_MAX_RPM_DAC_value,CALIB_AuroPilot_DAC_ideal_value,Active_motor_type_struct.motor_foot_lifting_vale,Active_motor_type_struct.motor_trimmer_activation_value);
											CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value = CALIB_MAX_RPM_DAC_value;
											CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value = CALIB_ideal_DAC_value;
}





//**********************************************************main_menu******************************************************************	
void menu_b7PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_home; }
void menu_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_main_setup; sendCommand("page 10");}
void menu_b4PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_debug; sendCommand("page 5");}
void menu_b5PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_autopilot; setLCD_Event_autopilot_session_chenged(true); sendCommand("page 7"); chThdSleepMilliseconds(50);  }//sew_assist_t0.setText("Select mode to start !"); }
void menu_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_autoDrive;  }
void menu_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_teaching; drawSavedSPI =true; setLCD_Event_autopilot_session_chenged(true); sendCommand("page 3"); chThdSleepMilliseconds(50);}	
void menu_b2PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_machine_type_select; sendCommand("page 13");}	
//**********************************************************sewAssist******************************************************************	
void sewAssist_bt0PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	uint32_t dual_state;  
	sew_assist_bt0.getValue(&dual_state); 
	if(dual_state){sew_assist_bt2.setValue(0); sew_assist_bt1.setValue(0);AutoPilot_MODE= FULL_AUTO; sew_assist_auto_pilot_modeText.setText("AUTO"); sew_assist_auto_pilot_modeText.Set_background_color_bco(63488); setAutoPilot_EN(true);} 
	else{setAutoPilot_EN(false); sew_assist_auto_pilot_modeText.setText("MANUAL");
		sew_assist_auto_pilot_modeText.Set_background_color_bco(3579);
	}
	}
	
void sewAssist_bt1PopCallback(void *ptr){
	chBSemSignal(&buzzerSem); 
	uint32_t dual_state;
	sew_assist_bt1.getValue(&dual_state);
	if (dual_state){sew_assist_bt0.setValue(0); sew_assist_bt2.setValue(0); setAutoPilot_EN(true); AutoPilot_MODE=SEMI_AUTO;sew_assist_auto_pilot_modeText.setText("Semi Auto");sew_assist_auto_pilot_modeText.Set_background_color_bco(4119);}
	else{setAutoPilot_EN(false); sew_assist_auto_pilot_modeText.setText("MANUAL");
		sew_assist_auto_pilot_modeText.Set_background_color_bco(3579);
	}
	}
	  
void sewAssist_bt2PopCallback(void *ptr){ 
	chBSemSignal(&buzzerSem);
	uint32_t dual_state;
	sew_assist_bt2.getValue(&dual_state);
	if(dual_state){sew_assist_bt0.setValue(0);sew_assist_bt1.setValue(0); sewingAssistent_EN=true; setAutoDriveTest_EN(false); sew_assist_auto_pilot_modeText.setText("Sew Assist");sew_assist_auto_pilot_modeText.Set_background_color_bco(650);}
	else{sewingAssistent_EN=false; sew_assist_auto_pilot_modeText.setText("MANUAL");
		sew_assist_auto_pilot_modeText.Set_background_color_bco(3579);
	}
	}

void sewAssist_bt3PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	uint32_t dual_state;
	sew_assist_bt3.getValue(&dual_state);
	if(dual_state){ cutter_on(); }
	else{ cutter_off(); };
	
}

void sewAssist_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem); setAutoPilot_EN(false); NexCurrent_screenID=eNex_menu; sendCommand("page 2");}
void sewAssist_t3PopCallbacl(void *ptr){chBSemSignal(&buzzerSem); mechanical_Rotary_sw_mode_session_chenge();}
//**********************************************************setup_main******************************************************************
void setup_main_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_menu; setSetup_EN(false); sendCommand("page 2"); }
void setup_main_b2PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_setup_analog; setSetup_EN(true); sendCommand("page 11"); }
void setup_main_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_ap_setup; sendCommand("page 12");}
void setup_main_b4PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_stepperSync; sendCommand("page 16");}
//**********************************************************setup_analog******************************************************************	
void setup_analog_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_main_setup; setSetup_EN(false); sendCommand("page 10"); }
	
void setup_analog_b1PopCallback(void *ptr){/*saving data*/
	chBSemSignal(&buzzerSem);
	uint32_t temp; 
	setup_analog_n7.getValue(&temp); 
	CALIBRATE_analogSamplesAverageCH0_adjestment = temp;
	setup_analog_n8.getValue(&temp);
	CALIBRATE_analogSamplesAverageCH1_adjestment = temp;
	setup_analog_n0.getValue(&temp);
	analogHighCH0 = temp;
	setup_analog_n1.getValue(&temp);
	analogLowCH0 = temp;
	 }

void setup_analog_b2PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t temp; setup_analog_n4.getValue(&temp); setup_analog_n0.setValue(temp);}
void setup_analog_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t temp; setup_analog_n4.getValue(&temp); setup_analog_n1.setValue(temp);}
void setup_analog_b6PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_setup_foot_trim; sendCommand("page 14"); }

//**********************************************************setup_ap******************************************************************
void setup_ap_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem);  
	uint32_t dual_state, value1; String v0 = ""; String v1 = "";  String v2 = ""; String v3 = ""; String v4 = ""; String v5 = ""; String v6 = ""; String v7 = ""; String v8 = "";
	setup_ap_bt0.getValue(&dual_state);if (dual_state){ v0 = "1";}else{ v0 = "0";}
	setup_ap_bt1.getValue(&dual_state);if (dual_state){ v1 = "1";}else{ v1 = "0";}
	setup_ap_bt2.getValue(&dual_state);if (dual_state){ v2 = "1";}else{ v2 = "0";}
	setup_ap_bt3.getValue(&dual_state);if (dual_state){ v3 = "1";}else{ v3 = "0";}
	setup_ap_bt4.getValue(&dual_state);if (dual_state){ v5 = "1";}else{ v5 = "0";}
	setup_ap_bt5.getValue(&dual_state);if (dual_state){ v6 = "1";}else{ v6 = "0";}
	setup_ap_bt6.getValue(&dual_state);if (dual_state){ v7 = "1";}else{ v7 = "0";}
	setup_ap_bt7.getValue(&dual_state);if (dual_state){ v8 = "1";}else{ v8 = "0";}
	setup_ap_n0.getValue(&value1); v4 = String(value1);

	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt","automatic_foot_lifting",v0.c_str());
	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt", "automatic_ap_start",v1.c_str());
	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt", "continuous_cycle_ap",v2.c_str());
	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt", "automatic_foot_lifting_with_trim",v3.c_str());
	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt", "ap_auto_start_delay",v4.c_str());
	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt", "ap_protection_by_start_sensor",v5.c_str());
	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt", "ap_protection_stop_when_trim",v6.c_str());
	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt", "auto_pilot_waiting_escape_by_start_sensor",v7.c_str());

	sdloader::write_param_value_to_sd("USADATA/SYSTEM/sysv.txt", "ap_waiting_escape_by_external_trigger",v8.c_str());
	// reload 
	unsigned int temp1,temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9;
	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "automatic_ap_start", temp1);
	automatic_ap_start = temp1;
	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "automatic_foot_lifting",temp2);
	automatic_foot_lifting = temp2;
	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "continuous_cycle_ap",temp3);
	continuous_cycle_ap = temp3;
	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "automatic_foot_lifting_with_trim",temp4);
	automatic_foot_lifting_with_trim = temp4;
	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "ap_auto_start_delay",temp5);
	MyAutoPilot.set_ap_autoStart_delay(temp5);
	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "ap_protection_by_start_sensor",temp6);
	MyAutoPilot.set_auto_pilot_protection_by_start_sensor(temp6);
	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "ap_protection_stop_when_trim",temp7);
	MyAutoPilot.set_auto_pilot_protection_stop_when_trim(temp7);

	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "auto_pilot_waiting_escape_by_start_sensor",temp8);
	MyAutoPilot.set_auto_pilot_waiting_escape_by_start_sensor(temp8);

	sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.txt", "ap_waiting_escape_by_external_trigger",temp9);
	MyAutoPilot.set_auto_pilot_waiting_escape_by_external_trigger(temp9);

	setup_ap_t7.setText("Saved !");
}
void setup_ap_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_main_setup; sendCommand("page 10");  }

void setup_ap_bt0PopCallback(void *ptr){chBSemSignal(&buzzerSem); setup_ap_t7.setText(""); }
void setup_ap_bt1PopCallback(void *ptr){chBSemSignal(&buzzerSem); setup_ap_t7.setText(""); }
void setup_ap_bt2PopCallback(void *ptr){chBSemSignal(&buzzerSem); setup_ap_t7.setText(""); }
void setup_ap_bt3PopCallback(void *ptr){chBSemSignal(&buzzerSem); setup_ap_t7.setText(""); }
void setup_ap_bt4PopCallback(void *ptr){chBSemSignal(&buzzerSem); setup_ap_t7.setText(""); }
void setup_ap_bt5PopCallback(void *ptr){chBSemSignal(&buzzerSem); setup_ap_t7.setText(""); }

void setup_ap_bt6PopCallback(void *ptr){chBSemSignal(&buzzerSem); 
	uint32_t dual_state; setup_ap_bt6.getValue(&dual_state);
	if (dual_state)
	{
		setup_ap_bt7.setValue(0);
	}
	setup_ap_t7.setText(""); 
}

void setup_ap_bt7PopCallback(void *ptr){chBSemSignal(&buzzerSem); 
	uint32_t dual_state; setup_ap_bt7.getValue(&dual_state);
	if (dual_state)
	{
		setup_ap_bt6.setValue(0);
	}
	setup_ap_t7.setText(""); 
}

//**********************************************************Foot_trim*******************************************************************************

void Foot_trim_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_setup_analog; sendCommand("page 11"); }
void Foot_trim_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem);

	uint32_t value0 ,value1, value2, value3, value4, value5, value6;
	Foot_trim_n0.getValue(&value0);
	Foot_trim_n1.getValue(&value1);
	Foot_trim_n2.getValue(&value2);
	Foot_trim_n3.getValue(&value3);
	Foot_trim_n4.getValue(&value4);
	Foot_trim_n5.getValue(&value5);
	String v0 = String(value0);
	String v1 = String(value1);
	String v2 = String(value2);
	String v3 = String(value3);
	String v4 = String(value4);
	String v5 = String(value5);
	
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/FT_data.txt","TH_ch1_detection_min_threshold",v0.c_str());
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/FT_data.txt", "TI_first_pulse_registering_delay", v1.c_str());
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/FT_data.txt", "TI_second_puls_stating_delay", v2.c_str());
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/FT_data.txt", "TH_ch1_trim_detection_threshold",v3.c_str());
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/FT_data.txt", "TI_second_pulse_rising_delay",v4.c_str());
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/FT_data.txt", "TI_second_pulse_rising_debounce",v5.c_str());

	// saved notification
	Foot_trim_t8.setText("Saved !");
	// Reloading variables
	chMtxLock(&Foot_trim_data);
	sdloader :: loading_FT(TH_ch1_detection_min_threshold_GLOBAL,TI_first_pulse_registering_delay_GLOBAL,TI_second_puls_stating_delay_GLOBAL,
	TH_ch1_trim_detection_threshold_GLOBAL,TI_second_pulse_rising_delay_GLOBAL, TI_second_pulse_rising_debounce_GLOBAL);
	chMtxUnlock(&Foot_trim_data);	
	

}

//**********************************************************setupStepperSync***********************************************************************
void stepperSync_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t temp; stepperSync_n1.getValue(&temp); if(temp>0){temp--;} stepperSync_n1.setValue(temp);}
void stepperSync_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t temp; stepperSync_n1.getValue(&temp); temp++; stepperSync_n1.setValue(temp);}

void stepperSync_b2PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t temp; stepperSync_n2.getValue(&temp); if(temp>0){temp--;} stepperSync_n2.setValue(temp);}
void stepperSync_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t temp; stepperSync_n2.getValue(&temp); temp++; stepperSync_n2.setValue(temp);}
void stepperSync_b7PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t temp; stepperSync_n0.getValue(&temp); if(temp>0){temp--;} stepperSync_n0.setValue(temp);}
void stepperSync_b8PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t temp; stepperSync_n0.getValue(&temp); temp++; stepperSync_n0.setValue(temp);}


void stepperSync_b4PopCallback(void *ptr){chBSemSignal(&buzzerSem); uint32_t value0 ,value1, value2;
		stepperSync_n1.getValue(&value1);  stepperSync_t7.setText("Saved");
		stepperSync_n2.getValue(&value2);
		stepperSync_n0.getValue(&value0);	

		String v0 = String(value0);
		String v1 = String(value1);
		String v2 = String(value2);

		sdloader::write_param_value_to_sd("USADATA/SYSTEM/SYSV.txt", "pulse_width", v1.c_str());
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/SYSV.txt", "au_feeder_cutter_act_delay", v2.c_str());
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/SYSV.txt", "au_feeder_cutting_delay", v0.c_str());

		chMtxLock(&au_feeder_data);
		sdloader :: loading_stepper_sysnc_para(pulse_width, au_feeder_cutter_act_delay, au_feeder_cutting_delay);
		chMtxUnlock(&au_feeder_data);
		
}
void stepperSync_b5PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_main_setup; sendCommand("page 10"); }











//**********************************************************Machine_type_select**********************************************************************	
void machine_select_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_menu;}

void machine_select_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); //sendCommand("tsw b0,0");
	// get values from lcd
	uint32_t value0 ,value1, value2, value3, value4, value5, value6;
	machine_select_n0.getValue(&value0);
	machine_select_n1.getValue(&value1);
	machine_select_n2.getValue(&value2);
	machine_select_n3.getValue(&value3);
	machine_select_n4.getValue(&value4);
	machine_select_n5.getValue(&value5);
	String v0 = String(value0);
	String v1 = String(value1);
	String v2 = String(value2);
	String v3 = String(value3);
	String v4 = String(value4);
	String v5 = String(value5);
	//check selected mc to save
	uint32_t dual_state;
	machine_select_bt0.getValue(&dual_state);
	if (dual_state)
	{
		sdloader::write_param_value_to_sd("USADATA/SYSTEM/sys.txt","active_motor","ism");
		sdloader::write_param_value_to_sd("USADATA/MASHINE/ISM.txt", "ideal_dac", v0.c_str());
		sdloader::write_param_value_to_sd("USADATA/MASHINE/ISM.txt", "max_rpm_dac", v3.c_str());
		sdloader::write_param_value_to_sd("USADATA/MASHINE/ISM.txt", "ideal_ap_dac_value",v4.c_str());

		
	}

	else
	{
		machine_select_bt1.getValue(&dual_state);
		if (dual_state){sdloader::write_param_value_to_sd("USADATA/SYSTEM/sys.txt","active_motor","pegasus_hpv_90_1l");
						sdloader :: write_param_value_to_sd("USADATA/MASHINE/HPV901L.txt", "ideal_dac",v0.c_str() );
						sdloader :: write_param_value_to_sd("USADATA/MASHINE/HPV901L.txt", "max_rpm_dac", v3.c_str());
						sdloader :: write_param_value_to_sd("USADATA/MASHINE/HPV901L.txt", "ideal_ap_dac_value",v4.c_str());
						sdloader :: write_param_value_to_sd("USADATA/MASHINE/HPV901L.txt", "foot_dac_value", v1.c_str());
						sdloader :: write_param_value_to_sd("USADATA/MASHINE/HPV901L.txt", "trim_dac_value", v2.c_str());
						
		}
		else{
			machine_select_bt2.getValue(&dual_state);
			if (dual_state){ sdloader::write_param_value_to_sd("USADATA/SYSTEM/sys.txt","active_motor","jukey_3zz");}
		}
	}
	// saved notification
	machine_select_t8.setText("Saved !");
	//reloading machine paras
	eMotor_type _Active_motor_type;
	
	sdloader :: getActive_motor_type_from_sd(_Active_motor_type);
	Active_motor_type_struct.Active_motor_type = _Active_motor_type;
	sdloader :: loading_machine_para(_Active_motor_type,CALIB_ideal_DAC_value,CALIB_MAX_RPM_DAC_value,CALIB_AuroPilot_DAC_ideal_value,Active_motor_type_struct.motor_foot_lifting_vale,Active_motor_type_struct.motor_trimmer_activation_value);
	CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value = CALIB_MAX_RPM_DAC_value;
	CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value = CALIB_ideal_DAC_value;

	//sendCommand("tsw b0,1");
	
}

void machine_select_bt0PopCallback(void *ptr){chBSemSignal(&buzzerSem);
	uint32_t dual_state;
	machine_select_bt0.getValue(&dual_state);
	if(dual_state){machine_select_bt1.setValue(0); machine_select_bt2.setValue(0); machine_select_t8.setText("");
	unsigned int _ideal_DAC_value, _MAX_RPM_DAC_value, _AuroPilot_DAC_ideal_value, _foot_lifting_value, _trimmer_activation_value;
					SD_OPERATION_RESULTS result = sdloader :: loading_machine_para(ISM,  _ideal_DAC_value, _MAX_RPM_DAC_value, _AuroPilot_DAC_ideal_value, _foot_lifting_value, _trimmer_activation_value);
					if (result!=LOADING_COMPLETE)
					{
						machine_select_t8.setText("Error !");
					}
					machine_select_n0.setValue(_ideal_DAC_value);
					machine_select_n3.setValue(_MAX_RPM_DAC_value);
					machine_select_n4.setValue(_AuroPilot_DAC_ideal_value);
		}
	else{
	machine_select_bt0.setValue(1);	}
}
void machine_select_bt1PopCallback(void *ptr){chBSemSignal(&buzzerSem);
	uint32_t dual_state;
	machine_select_bt1.getValue(&dual_state);
	if(dual_state){machine_select_bt0.setValue(0); machine_select_bt2.setValue(0); machine_select_t8.setText("");
	unsigned int _ideal_DAC_value, _MAX_RPM_DAC_value, _AuroPilot_DAC_ideal_value, _foot_lifting_value, _trimmer_activation_value;
					SD_OPERATION_RESULTS result = sdloader :: loading_machine_para(PEGASUS_HPV_90, _ideal_DAC_value, _MAX_RPM_DAC_value, _AuroPilot_DAC_ideal_value, _foot_lifting_value, _trimmer_activation_value);
					if (result!=LOADING_COMPLETE)
					{
						machine_select_t8.setText("Error !");
					}
					machine_select_n0.setValue(_ideal_DAC_value);
					machine_select_n1.setValue(_foot_lifting_value);
					machine_select_n2.setValue(_trimmer_activation_value);
					machine_select_n3.setValue(_MAX_RPM_DAC_value);
					machine_select_n4.setValue(_AuroPilot_DAC_ideal_value);
	}
	else{
		machine_select_bt1.setValue(1);
	}
}
void machine_select_bt2PopCallback(void *ptr){chBSemSignal(&buzzerSem);
	uint32_t dual_state;
	machine_select_bt2.getValue(&dual_state);
	if(dual_state){machine_select_bt0.setValue(0); machine_select_bt1.setValue(0); machine_select_t8.setText("");
	unsigned int _ideal_DAC_value, _MAX_RPM_DAC_value, _AuroPilot_DAC_ideal_value, _foot_lifting_value, _trimmer_activation_value;
					SD_OPERATION_RESULTS result = sdloader :: loading_machine_para(JUKY_3ZZ,_ideal_DAC_value, _MAX_RPM_DAC_value, _AuroPilot_DAC_ideal_value, _foot_lifting_value, _trimmer_activation_value);
					if (result!=LOADING_COMPLETE)
					{
						machine_select_t8.setText("Error !");
					}
					machine_select_n0.setValue(_ideal_DAC_value);
					machine_select_n3.setValue(_MAX_RPM_DAC_value);
					machine_select_n4.setValue(_AuroPilot_DAC_ideal_value);
	}
	else{
		machine_select_bt2.setValue(1);
	}
}


















#endif /* DISPLAY_H_ */