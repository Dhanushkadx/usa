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
typedef enum eNex_screenID {eNex_unknown, eNex_teaching, eNex_autopilot, eNex_debug,eNex_debug_advanced, eNex_autoDrive, eNex_home, eNex_main_setup, eNex_stepperSync, eNex_setup_foot_trim, eNex_menu, eNex_setup_analog, eNex_setup_autoPilot, eNex_machine_type_select};
	eNex_screenID NexCurrent_screenID= eNex_home;
	eNex_screenID NexPrev_screenID= eNex_unknown;
	
//wave form
NexWaveform s0 = NexWaveform(3, 1, "s0");
// Progress Bar
NexProgressBar home_paddiling_progress_bar = NexProgressBar(0,10,"j0");

NexProgressBar auto_pilot_Cycle_progress_bar = NexProgressBar(4,6,"j0");
NexProgressBar auto_pilot_RPM_progress_bar = NexProgressBar(4,8,"j1");

NexProgressBar sew_assist_auto_pilot_Cycle_progress_bar = NexProgressBar(7,5,"j1");
NexProgressBar sew_assist_auto_pilot_RPM_progress_bar = NexProgressBar(7,2,"j0");

NexText auto_pilot_progress_barText = NexText(4,5,"t2");

NexText sew_assist_auto_pilot_progress_barText = NexText(7,6,"t5");
NexText sew_assist_auto_pilot_modeText = NexText(7,1,"t0");
NexText sew_assist_auto_t2 = NexText (7, 13, "t2");
NexText sew_assist_auto_t3 = NexText (7, 14, "t3");
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

//**********Setup_main_page**********
NexButton setup_main_b0 = NexButton(10, 2, "b0");
NexButton setup_main_b1 = NexButton(10, 3, "b1");
NexButton setup_main_b2 = NexButton(10, 4, "b2");
NexButton setup_main_b3 = NexButton(10, 5, "b3");
NexButton setup_main_b4 = NexButton(10, 6, "b4");


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


//sewing_assistant page*********
NexDSButton sew_assist_bt0 = NexDSButton(7, 10, "bt0");
NexDSButton sew_assist_bt1 = NexDSButton(7, 11, "bt1");
NexDSButton sew_assist_bt2 = NexDSButton(7, 12, "bt2");

NexButton sew_assist_b3 = NexButton(7,4,"b3");

NexText sew_assist_t0 = NexText (7,1,"t0");
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


//**********************************************************setup_main******************************************************************	

void home_bt0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID=eNex_menu;Serial.println("going Menu");}
void home_bt1PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID=eNex_menu;}
void home_bt2PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID=eNex_setup_analog;}
//***********************************************************teaching*******************************************************************

void t0PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	mechanical_Rotary_sw_mode_session_chenge();
}	

void bt0PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	uint32_t dual_state;  
	bt0.getValue(&dual_state); 
	if(dual_state){bt1.setValue(0); setTeachingSewing_EN(true);}
	else{}	
	 }
void bt1PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	 uint32_t dual_state;
	 bt0.getValue(&dual_state);
	 if(dual_state){bt0.setValue(0); setTeachingSewing_EN(false);}
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
void b5PopCallback(void *ptr){chBSemSignal(&buzzerSem);Serial.println("going back to Menu"); NexCurrent_screenID=eNex_menu; setTeachingSewing_EN(false);}
	
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
void menu_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_main_setup;}
void menu_b4PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_debug; }
void menu_b5PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_autopilot; setLCD_Event_autopilot_session_chenged(true); chThdSleepMilliseconds(50);  }//sew_assist_t0.setText("Select mode to start !"); }
void menu_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_autoDrive;  }
void menu_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_teaching; drawSavedSPI =true; setLCD_Event_autopilot_session_chenged(true); chThdSleepMilliseconds(50);}	
void menu_b2PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_machine_type_select;}	
//**********************************************************sewAssist******************************************************************	
void sewAssist_bt0PopCallback(void *ptr){
	chBSemSignal(&buzzerSem);
	uint32_t dual_state;  
	bt0.getValue(&dual_state); 
	if(dual_state){sew_assist_bt2.setValue(0); sew_assist_bt1.setValue(0);AutoPilot_MODE= FULL_AUTO; sew_assist_auto_pilot_modeText.setText("AUTO"); sew_assist_auto_pilot_modeText.Set_background_color_bco(63488); setAutoPilot_EN(true);} 
	else{setAutoPilot_EN(false); sew_assist_auto_pilot_modeText.setText("MANUAL");
		sew_assist_auto_pilot_modeText.Set_background_color_bco(3579);
	}
	}
	
void sewAssist_bt1PopCallback(void *ptr){
	chBSemSignal(&buzzerSem); 
	uint32_t dual_state;
	bt1.getValue(&dual_state);
	if (dual_state){sew_assist_bt0.setValue(0); sew_assist_bt2.setValue(0); setAutoPilot_EN(true); AutoPilot_MODE=SEMI_AUTO;sew_assist_auto_pilot_modeText.setText("Semi Auto");sew_assist_auto_pilot_modeText.Set_background_color_bco(4119);}
	else{setAutoPilot_EN(false); sew_assist_auto_pilot_modeText.setText("MANUAL");
		sew_assist_auto_pilot_modeText.Set_background_color_bco(3579);
	}
	}
	  
void sewAssist_bt2PopCallback(void *ptr){ 
	chBSemSignal(&buzzerSem);
	uint32_t dual_state;
	bt1.getValue(&dual_state);
	if(dual_state){sew_assist_bt0.setValue(0);sew_assist_bt1.setValue(0); sewingAssistent_EN=true; setAutoDriveTest_EN(false); sew_assist_auto_pilot_modeText.setText("Sew Assist");sew_assist_auto_pilot_modeText.Set_background_color_bco(650);}
	else{sewingAssistent_EN=false; sew_assist_auto_pilot_modeText.setText("MANUAL");
		sew_assist_auto_pilot_modeText.Set_background_color_bco(3579);
	}
	}
void sewAssist_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem); setAutoPilot_EN(false); NexCurrent_screenID=eNex_menu;}
void sewAssist_t3PopCallbacl(void *ptr){chBSemSignal(&buzzerSem); mechanical_Rotary_sw_mode_session_chenge();}
//**********************************************************setup_main******************************************************************
void setup_main_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_menu; setSetup_EN(false); }
void setup_main_b2PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_setup_analog; setSetup_EN(true); }
void setup_main_b3PopCallback(void *ptr){chBSemSignal(&buzzerSem);  }
void setup_main_b4PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_stepperSync; }
//**********************************************************setup_analog******************************************************************	
void setup_analog_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_main_setup; setSetup_EN(false); }
	
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
void setup_analog_b6PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_setup_foot_trim; }
//**********************************************************Foot_trim*******************************************************************************

void Foot_trim_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_setup_analog; }
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
void stepperSync_b5PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_main_setup; }











//**********************************************************Machine_type_select**********************************************************************	
void machine_select_b0PopCallback(void *ptr){chBSemSignal(&buzzerSem); NexCurrent_screenID = eNex_menu;}

void machine_select_b1PopCallback(void *ptr){chBSemSignal(&buzzerSem);
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

void registerNextionEventsCallbacks(){
	
	home_b0.attachPop(home_bt0PopCallback, &home_b0);
	home_b1.attachPop(home_bt1PopCallback, &home_b1);
	
	bt0.attachPop(bt0PopCallback, &bt0);
	bt1.attachPop(bt1PopCallback, &bt1);
	bt2.attachPop(bt2PopCallback, &bt2);
	bt3.attachPop(bt3PopCallback, &bt3);
	bt4.attachPop(bt4PopCallback, &bt4);
	bt5.attachPop(bt5PopCallback, &bt5);
	bt6.attachPop(bt6PopCallback, &bt6);
	b0.attachPop(b0PopCallback, &b0);
	b2.attachPop(b2PopCallback, &b2);
	b5.attachPop(b5PopCallback, &b5);
	t0.attachPop(t0PopCallback, &t0);
	
	Auto_bt0.attachPop(Auto_bt0PopCallback, &Auto_bt0);
	Auto_b1.attachPop(Auto_b1PopCallback, &Auto_b1);
	Auto_b5.attachPop(Auto_b5PopCallback, &Auto_b5);
	
	debug_bt0.attachPop(debug_bt0PopCallback, &debug_bt0);
	debug_bt1.attachPop(debug_bt1PopCallback, &debug_bt1);
	debug_bt2.attachPop(debug_bt2PopCallback, &debug_bt2);
	debug_b5.attachPop(debug_b5PopCallback, &debug_b5);
	debug_b7.attachPop(debug_b7PopCallback, &debug_b7);
	
	menu_b7.attachPop(menu_b7PopCallback, &menu_b7);
	menu_b1.attachPop(menu_b1PopCallback, &menu_b1);
	menu_b3.attachPop(menu_b3PopCallback, &menu_b3);
	menu_b0.attachPop(menu_b0PopCallback, &menu_b0);
	menu_b5.attachPop(menu_b5PopCallback, &menu_b5);
	menu_b4.attachPop(menu_b4PopCallback, &menu_b4);
	menu_b2.attachPop(menu_b2PopCallback, &menu_b2);
	
	//sew_assist_bt0.
	sew_assist_bt0.attachPop(sewAssist_bt0PopCallback, &sew_assist_bt0);
	sew_assist_bt1.attachPop(sewAssist_bt1PopCallback, &sew_assist_bt1);
	sew_assist_bt2.attachPop(sewAssist_bt2PopCallback, &sew_assist_bt2);
	sew_assist_b3.attachPop(sewAssist_b3PopCallback, &sew_assist_b3);
	sew_assist_auto_t3.attachPop(sewAssist_t3PopCallbacl, &sew_assist_auto_t3);
	
	setup_main_b2.attachPop(setup_main_b2PopCallback, &setup_main_b2);
	setup_main_b1.attachPop(setup_main_b1PopCallback, &setup_main_b1);
	setup_main_b4.attachPop(setup_main_b4PopCallback, &setup_main_b4);
	
	setup_analog_b0.attachPop(setup_analog_b0PopCallback, &setup_analog_b0);
	setup_analog_b1.attachPop(setup_analog_b1PopCallback, &setup_analog_b1);
	setup_analog_b2.attachPop(setup_analog_b2PopCallback, &setup_analog_b2);
	setup_analog_b3.attachPop(setup_analog_b3PopCallback, &setup_analog_b3);
	setup_analog_b6.attachPop(setup_analog_b6PopCallback, &setup_analog_b6);

	//machine type select
	machine_select_b0.attachPop(machine_select_b0PopCallback, &Foot_trim_b0);
	machine_select_b1.attachPop(machine_select_b1PopCallback, &Foot_trim_b1);
	machine_select_bt0.attachPop(machine_select_bt0PopCallback, &Foot_trim_bt0);
	machine_select_bt1.attachPop(machine_select_bt1PopCallback, &Foot_trim_bt1);
	machine_select_bt2.attachPop(machine_select_bt2PopCallback, &Foot_trim_bt2);

	//foot_trim
	Foot_trim_b0.attachPop(Foot_trim_b0PopCallback, &Foot_trim_b0);
	Foot_trim_b1.attachPop(Foot_trim_b1PopCallback, &Foot_trim_b1);
	//Foot_trim_bt0.attachPop(Foot_trim_bt0PopCallback, &Foot_trim_bt0)
	//Foot_trim_bt1.attachPop(Foot_trim_bt1PopCallback, &Foot_trim_bt1);
	//Foot_trim_bt2.attachPop(Foot_trim_bt2PopCallback, &Foot_trim_bt2);

	// advanced debug
	debug_advanced_h0.attachPop(debug_advanced_h0PopCallback, &debug_advanced_h0);
	debug_advanced_bt0.attachPop(debug_advanced_bt0PopCallback, &debug_advanced_bt0);
	debug_advanced_bt1.attachPop(debug_advanced_bt1PopCallback, &debug_advanced_bt1);
	debug_advanced_bt2.attachPop(debug_advanced_bt2PopCallback, &debug_advanced_bt2);

	debug_advanced_b0.attachPop(debug_advanced_b0PopCallback, &debug_advanced_b0);
	debug_advanced_b1.attachPop(debug_advanced_b1PopCallback, &debug_advanced_b1);
	debug_advanced_b2.attachPop(debug_advanced_b2PopCallback, &debug_advanced_b2);
	debug_advanced_b3.attachPop(debug_advanced_b3PopCallback, &debug_advanced_b3);

	debug_advanced_b4.attachPop(debug_advanced_b4PopCallback, &debug_advanced_b4);
	debug_advanced_b5.attachPop(debug_advanced_b5PopCallback, &debug_advanced_b5);
	debug_advanced_b6.attachPop(debug_advanced_b6PopCallback, &debug_advanced_b6);

	//stepperSync
	stepperSync_b0.attachPop(stepperSync_b0PopCallback, &stepperSync_b0);
	stepperSync_b1.attachPop(stepperSync_b1PopCallback, &stepperSync_b1);
	stepperSync_b4.attachPop(stepperSync_b4PopCallback, &stepperSync_b4);
	stepperSync_b5.attachPop(stepperSync_b5PopCallback, &stepperSync_b5);

	stepperSync_b2.attachPop(stepperSync_b2PopCallback, &stepperSync_b2);
	stepperSync_b3.attachPop(stepperSync_b3PopCallback, &stepperSync_b3);
	stepperSync_b7.attachPop(stepperSync_b7PopCallback, &stepperSync_b7);
	stepperSync_b8.attachPop(stepperSync_b8PopCallback, &stepperSync_b8);
}


boolean nexUpdate_due(){
	
	
	 unsigned long currentMillis = millis();
	
	 if(currentMillis - Nex_LCD_LastUpdate_Millis > Nex_LCD_update_interval) {
		 // save the last time you blinked the LED
		 Nex_LCD_LastUpdate_Millis = currentMillis;
		 
		 return true;
	 }
	 return false;
}

boolean getnexUpdate_force(){
	chMtxLock(&Flags_communication);
	if (Nex_LCD_LastUpdate_Force)
	{
		Nex_LCD_LastUpdate_Force=false;
		chMtxUnlock(&Flags_communication);
		return true;
	}
	else {
		chMtxUnlock(&Flags_communication);
		return false;
	}
	
}

void setnexUpdate_force(){
	
	chMtxLock(&Flags_communication);
	Nex_LCD_LastUpdate_Force=true;
	chMtxUnlock(&Flags_communication);
}


void display_main(){
	static int previous_trueDACout_forDisplay_THD4=0;
	static unsigned int mapIndex=0;
	static unsigned int minUnit = SPI_speed_profil_length_SH/400;
	int previous_analogSamplesAverageCH0_mapdforDisplay_THD4 =0;
	
	//nexLoop(nex_listen_list_teaching_page);
	
	chMtxLock(&SerialDataSH_Mutex_CH0);
	unsigned int DACoutValue_teachng_REC_THD4 =DACoutValue_teachng_REC_SH;
	unsigned int DACDataArray_SPI_of_curruntIndexValue_THD4 = DACDataArray_SPI_of_curruntIndexValue_SH;
	unsigned int DACoutValue_autoPilot_proccessed_THD4 = DACoutValue_autoPilot_proccessed_SH;
	long CH0_RAWAnalogValue_THD4 = AN_CH0_sensor_data_RAW_GLOB ;
	
	int trueDACout_forDisplay_THD4=0;
	chMtxUnlock(&SerialDataSH_Mutex_CH0);

	chMtxLock(&SerialDataSH_Mutex_CH1);
	long CH1_RAWAnalogValue_THD4 = AN_CH1_sensor_data_RAW_GLOB;
	chMtxUnlock(&SerialDataSH_Mutex_CH1);
	switch (NexCurrent_screenID)
	{
		
	case eNex_home:{
					nexLoop(nex_listen_list_home_page);
					if (NexPrev_screenID!=eNex_home)
					{
						NexPrev_screenID = NexCurrent_screenID;
						home_paddiling_progress_bar.setValue(0);
						Serial.println("page change to home");
						
					}
					
					chMtxLock(&General_LCDcommunication);
					trueDACout_forDisplay_THD4 = trueDACout_forDisplay_SH;
					chMtxUnlock(&General_LCDcommunication);
					
					//(()&&())?:;
					
					static unsigned int nomalcolor = 1827;
					nomalcolor = ((trueDACout_forDisplay_THD4>0)&&(trueDACout_forDisplay_THD4<50))? 1827 : nomalcolor;
					nomalcolor = ((trueDACout_forDisplay_THD4>50)&&(trueDACout_forDisplay_THD4<62))?65504: nomalcolor;
					nomalcolor = ((trueDACout_forDisplay_THD4>62)&&(trueDACout_forDisplay_THD4<100))?63488 : nomalcolor;
					
					if ((previous_analogSamplesAverageCH0_mapdforDisplay_THD4!=trueDACout_forDisplay_THD4))
					{
						//Serial.println(trueDACout_forDisplay_THD4);
						home_paddiling_progress_bar.Set_font_color_pco(nomalcolor);
						home_paddiling_progress_bar.setValue(trueDACout_forDisplay_THD4);
						previous_trueDACout_forDisplay_THD4 = trueDACout_forDisplay_THD4;
					}
					
					
					
		
		}break;
	case eNex_menu:{
					nexLoop(nex_listen_list_main_menu_page);
					if (NexPrev_screenID!=eNex_menu)
					{
						NexPrev_screenID = NexCurrent_screenID;//**********************************************this is where i left
						Serial.println("page change to main menu");
						//Auto_bt0.setValue(false);
					}
		
		}
		break;
	case eNex_teaching:{
						nexLoop(nex_listen_list_teaching_page);
						if ((NexPrev_screenID!=eNex_teaching)||(getLCD_refresh()))
						{
							setLCD_refresh(false);
							Serial.println("page change to teaching");
							chThdSleepMilliseconds(300);
							Serial.println("new draw");
							NexPrev_screenID = NexCurrent_screenID;
							drawSavedSPI=false;
							mapIndex=0;
							minUnit = SPI_speed_profil_length_SH/400;
							Serial.println(minUnit);
							for (int x=0; x<=400; x++)
							{
								chThdSleepMicroseconds(1);
								mapIndex= mapIndex + minUnit;
								if (DACData[mapIndex][1]>0)
								{
									s0.addValue(1, DACData[mapIndex][1]);
								}
							}
							n0.setValue(SPI_speed_profil_length_SH);
							// display creasing detail
							String tempTex;
							char buf[10]={0};
							tempTex += "Creasing Points: ";
							tempTex += utoa(getntotalCreasingPointstoLCD(), buf, 10);
							t1.setText(tempTex.c_str());	
							bt1.setValue(1);
							bt3.setText("DEFAULT SEW");	
							bt4.setText("NECK LINE");
							bt5.setText("ARM LEFT");
							bt6.setText("ARM RIGHT");
							bt3.setValue(0); bt4.setValue(0); bt5.setValue(0); bt6.setValue(0);
							if(msg_teaching_t0_message == LCD_text_meassage0){bt3.setValue(1);}
							else if (msg_teaching_t0_message == LCD_text_meassage1){bt4.setValue(1);}
							else if (msg_teaching_t0_message == LCD_text_meassage2){bt5.setValue(1);}
							else if (msg_teaching_t0_message == LCD_text_meassage3){bt6.setValue(1);}
							
											
						}
						
						if (getnexUpdate_force())
						{
							unsigned int mapDACoutValue_teachng_REC = map(DACoutValue_teachng_REC_THD4,1800,5000,0,5000000);
							
							String tempText;
							char buf[10] = {0};
							//tempText = utoa(DACDataArray_SPI_of_curruntIndexValue_THD4  , buf, 10);
							//buf[10] = {0};
							tempText += " : ";
							tempText += utoa(DACoutValue_teachng_REC_THD4, buf, 10);
							//t1.setText(tempText.c_str());
							s0.addValue(1,mapDACoutValue_teachng_REC);
							n0.setValue(DACDataArray_SPI_of_curruntIndexValue_THD4);
						}
						
						if (getLCD_Event_creasing())
							{
								setLCD_Event_creasing(false);
								char buf[10] = {0};
								//creasing_point_current++;
								String tempTex;//*************************************************************************
								tempTex ;
								tempTex += "CreasingPoints: ";
								tempTex += utoa(getntotalCreasingPointstoLCD(), buf, 10);
								//tempTex += "/";
								//tempTex += utoa(getntotalCreasingPointstoLCD(), buf, 10);
								t1.setText(tempTex.c_str());
							}
							
							if (getLCD_Event_autopilot_session_chenged())
							{
								setLCD_Event_autopilot_session_chenged(false);
								n0.setValue(SPI_speed_profil_length_SH);
								bt3.setValue(0); bt4.setValue(0); bt5.setValue(0); bt6.setValue(0);
								t0.setText(msg_teaching_t0_message.c_str());
								if(msg_teaching_t0_message == LCD_text_meassage0){bt3.setValue(1);}
								else if (msg_teaching_t0_message == LCD_text_meassage1){bt4.setValue(1);}
								else if (msg_teaching_t0_message == LCD_text_meassage2){bt5.setValue(1);}
								else if (msg_teaching_t0_message == LCD_text_meassage3){bt6.setValue(1);}
								
								String tempTex;
								char buf[10]={0};
								tempTex += "Creasing Points: ";
								tempTex += utoa(getntotalCreasingPointstoLCD(), buf, 10);
								t1.setText(tempTex.c_str());
							}
						
		
	}
		break;
	
	case eNex_autoDrive:{
						nexLoop(nex_listen_list_autoDrive_page);
						if (NexPrev_screenID!=eNex_autoDrive)
						{
							NexPrev_screenID = NexCurrent_screenID;
							Serial.println("page change to autoDrive test");
							//auto_pilot_Cycle_progress_bar.Set_font_color_pco(4119);
							//auto_pilot_RPM_progress_bar.Set_font_color_pco(1827);
							//auto_t1.setText("auto drive will be very useful");
						}
						if (getnexUpdate_force())
						{
							unsigned int mapDACoutValue_autoPilot_proccessed = map(DACoutValue_autoPilot_proccessed_THD4,800,1400,0,100);
							unsigned int mapDACDataArray_SPI_of_curruntIndexValue = map(DACDataArray_SPI_of_curruntIndexValue_THD4, 0, SPI_speed_profil_length_SH, 0, 100);
							if (mapDACoutValue_autoPilot_proccessed>75)
							{
								auto_pilot_RPM_progress_bar.Set_font_color_pco(63488);
							}
							else{auto_pilot_RPM_progress_bar.Set_font_color_pco(1827);}
							
							auto_pilot_Cycle_progress_bar.setValue(mapDACDataArray_SPI_of_curruntIndexValue);
							auto_pilot_RPM_progress_bar.setValue(mapDACoutValue_autoPilot_proccessed);
							if (mapDACoutValue_autoPilot_proccessed==100)
							{
								sew_assist_bt0.setValue(0);
								sew_assist_bt1.setValue(0);
								sew_assist_bt2.setValue(0);
								 Auto_bt0.setValue(false);
							}
							
							char buf[10] = {0};
							String sTempTex;						
							utoa(mapDACDataArray_SPI_of_curruntIndexValue, buf, 10);
							sTempTex = buf;
							sTempTex += "%";
							auto_pilot_progress_barText.setText(sTempTex.c_str());						
							
						}
		
	}
		break;
	
	case eNex_autopilot:{
						nexLoop(nex_listen_list_sew_assistant_page);
						if ((NexPrev_screenID!=eNex_autopilot)||(getLCD_refresh()))
						{
							setLCD_refresh(false);
							NexPrev_screenID = NexCurrent_screenID;
							Serial.println("page change to auto pilot");
							char buf[10] = {0};	
							String tempTex;//*************************************************************************
								
								tempTex += "Creasing Points: ";
								tempTex += utoa(getcurrentCreasingPoints(), buf, 10);
								tempTex += "/";
								tempTex += utoa(getntotalCreasingPointstoLCD(), buf, 10);
								sew_assist_auto_t2.setText(tempTex.c_str());
								sew_assist_auto_pilot_Cycle_progress_bar.setValue(0);
								sew_assist_auto_pilot_RPM_progress_bar.setValue(0);
								sew_assist_auto_t3.setText(msg_sew_assist_auto_t3_message.c_str());
								
							//auto_pilot_Cycle_progress_bar.Set_font_color_pco(4119);
							//auto_pilot_RPM_progress_bar.Set_font_color_pco(1827);
							//sew_assist_t10.setText("auto pilot will be very useful");
						}
						if (getnexUpdate_force())
						{
							unsigned int mapDACoutValue_autoPilot_proccessed = map(DACoutValue_autoPilot_proccessed_THD4,800,1400,0,100);
							unsigned int mapDACDataArray_SPI_of_curruntIndexValue = map(DACDataArray_SPI_of_curruntIndexValue_THD4, 0, SPI_speed_profil_length_SH, 0, 100);
							mapDACDataArray_SPI_of_curruntIndexValue = (mapDACDataArray_SPI_of_curruntIndexValue>100)? 100 : mapDACDataArray_SPI_of_curruntIndexValue;
							if (mapDACoutValue_autoPilot_proccessed>75)
							{
								sew_assist_auto_pilot_RPM_progress_bar.Set_font_color_pco(63488);
							}
							else{sew_assist_auto_pilot_RPM_progress_bar.Set_font_color_pco(1827);}
							sew_assist_auto_pilot_Cycle_progress_bar.setValue(mapDACDataArray_SPI_of_curruntIndexValue);
							sew_assist_auto_pilot_RPM_progress_bar.setValue(mapDACoutValue_autoPilot_proccessed);
							
							char buf[10] = {0};
							String sTempTex;
							utoa(mapDACDataArray_SPI_of_curruntIndexValue, buf, 10);
							sTempTex = buf;
							sTempTex += "%";
							sew_assist_auto_pilot_progress_barText.setText(sTempTex.c_str());
							if (mapDACDataArray_SPI_of_curruntIndexValue==100)
							{
								
								sew_assist_auto_pilot_Cycle_progress_bar.setValue(0);
								sew_assist_auto_pilot_RPM_progress_bar.setValue(0);
							}
							
							if (getLCD_Event_creasing())
							{
								setLCD_Event_creasing(false);
								
								String tempTex;//*************************************************************************
								tempTex ;
								tempTex += "Creasing Points: ";
								tempTex += utoa(getcurrentCreasingPoints(), buf, 10);
								tempTex += "/";
								tempTex += utoa(getntotalCreasingPointstoLCD(), buf, 10);
								sew_assist_auto_t2.setText(tempTex.c_str());
							}
							
						}
						
						if (getLCD_Event_LCD_Event_autopilot_canceled())
						{
							setLCD_Event_autopilot_canceled(false);
							sew_assist_bt0.setValue(0);
							sew_assist_auto_pilot_modeText.Set_background_color_bco(3579);
							sew_assist_auto_pilot_modeText.setText("MANUAL");
						}
						if (getLCD_Event_autopilot_session_chenged())
						{
							setLCD_Event_autopilot_session_chenged(false);
							sew_assist_auto_t3.setText(msg_sew_assist_auto_t3_message.c_str());
						}
						
		
		}
		break;
	case eNex_setup_analog:{
							nexLoop(nex_listen_list_analog_setup_page);
							if (NexPrev_screenID!= eNex_setup_analog)
							{
								NexPrev_screenID = NexCurrent_screenID;
								Serial.println("page change to setup_analog");
								chThdSleepMilliseconds(200);
								setup_analog_n0.setValue(analogHighCH0);
								setup_analog_n1.setValue(analogLowCH0);
								setup_analog_n2.setValue(analogHighCH1);
								setup_analog_n3.setValue(analogLowCH1);
								setup_analog_n5.setValue(analogLowCH0);
								setup_analog_n7.setValue(CALIBRATE_analogSamplesAverageCH0_adjestment);
								setup_analog_n8.setValue(CALIBRATE_analogSamplesAverageCH1_adjestment);
							}
							
							if (nexUpdate_due())
							{
								setup_analog_n4.setValue(CH0_RAWAnalogValue_THD4);
								setup_analog_n6.setValue(CH1_RAWAnalogValue_THD4);
							}
		
		}break;

	case eNex_setup_foot_trim:{
		nexLoop(nex_listen_list_setup_foot_trim_page);
		if (NexPrev_screenID!= eNex_setup_foot_trim)
		{
			NexPrev_screenID = NexCurrent_screenID;
			Serial.println("page change to foot trim");
			chThdSleepMilliseconds(200);
			//screen button initialize
			Foot_trim_bt0.setValue(0);
			Foot_trim_bt1.setValue(0);
			Foot_trim_bt2.setValue(0);

			Foot_trim_t0.setText("This page is under construction and may have errors !");
			Foot_trim_t1.setText("Minimum threshold");
			Foot_trim_t2.setText("First pulse registering delay");
			Foot_trim_t3.setText("Second pulse stating delay");
			Foot_trim_t4.setText("Trim detection threshold");
			Foot_trim_t5.setText("Second pulse rising delay");
			Foot_trim_t6.setText("Second pulse rising de-bounce");

			chMtxLock(&Foot_trim_data);
			unsigned int TH_ch1_detection_min_threshold = TH_ch1_detection_min_threshold_GLOBAL;
			unsigned int TI_first_pulse_registering_delay = TI_first_pulse_registering_delay_GLOBAL;//ms
			unsigned int TI_second_puls_stating_delay = TI_second_puls_stating_delay_GLOBAL;// ms default
			unsigned int TH_ch1_trim_detection_threshold = TH_ch1_trim_detection_threshold_GLOBAL;
			unsigned int TI_second_pulse_rising_delay = TI_second_pulse_rising_delay_GLOBAL;
			unsigned int TI_second_pulse_rising_debounce = TI_second_pulse_rising_debounce_GLOBAL;
			chMtxUnlock(&Foot_trim_data);

			// set numerical values
			Foot_trim_n0.setValue(TH_ch1_detection_min_threshold);
			Foot_trim_n1.setValue(TI_first_pulse_registering_delay);
			Foot_trim_n2.setValue(TI_second_puls_stating_delay);
			Foot_trim_n3.setValue(TH_ch1_trim_detection_threshold);
			Foot_trim_n4.setValue(TI_second_pulse_rising_delay);
			Foot_trim_n5.setValue(TI_second_pulse_rising_debounce);
			//Foot_trim_n6.setValue(Active_motor_type_struct.motor_trimmer_activation_value);			
		}
		
		if (nexUpdate_due())
		{
			
		}
		
	}break;
	
	case eNex_debug:{
						nexLoop(nex_listen_list_debug_page);
						if (NexPrev_screenID!=eNex_debug)
						{
							Serial.println("page change to debug");
							NexPrev_screenID = NexCurrent_screenID;
							chThdSleepMilliseconds(200);
							debug_bt0.setValue((getSerial_push_analogInputData_EN())? 1:0 );
							debug_bt1.setValue((getSerial_push_autoPilotData_EN())? 1:0 );
						}
						debug_n0.setValue(Utility::getCurrentSPI_count());
		
	}
		break;

	case eNex_debug_advanced:{
		nexLoop(nex_listen_list_debug_advanced_page);
		if (NexPrev_screenID!=eNex_debug_advanced)
		{
			Serial.println("page change to Advanced debug");
			NexPrev_screenID = NexCurrent_screenID;
			chThdSleepMilliseconds(200);
			debug_advanced_n1.setValue(Active_motor_type_struct.motor_foot_lifting_vale);
			debug_advanced_n2.setValue(Active_motor_type_struct.motor_trimmer_activation_value);
			debug_advanced_bt0.setValue(0);
			debug_advanced_bt1.setValue(0);
			debug_advanced_bt2.setValue(1);
			debug_advanced_h0.setMaxval(CALIB_MAX_RPM_DAC_value); debug_advanced_h0.setMinval(CALIB_ideal_DAC_value);
			debug_advanced_h0.setValue(0);
			
		}
		
	}
	break;

	case eNex_machine_type_select:{
						
						nexLoop(nex_listen_list_machine_select_page);			
						if (NexPrev_screenID != eNex_machine_type_select)
						{
						NexPrev_screenID = NexCurrent_screenID;
						chThdSleepMilliseconds(100);
						//screen button initialize
						machine_select_bt0.setValue(0);
						machine_select_bt1.setValue(0);
						machine_select_bt2.setValue(0);

						machine_select_t0.setText("This page is under construction and may have errors !");
						machine_select_bt0.setText("ISM");
						machine_select_bt1.setText("HOSHING/PEGU");
						machine_select_bt2.setText("JUKY");
						//eMotor_type Active_motor_type;
						//sdloader :: getActive_motor_type_from_sd(Active_motor_type);
						if (Active_motor_type_struct.Active_motor_type==ISM)
						{
							machine_select_bt0.setValue(1);
						}
						else if (Active_motor_type_struct.Active_motor_type == PEGASUS_HPV_90)
						{
							machine_select_bt1.setValue(1);
						}
						else if (Active_motor_type_struct.Active_motor_type == JUKY_3ZZ)
						{
							machine_select_bt2.setValue(1);
						}
						// set numerical values
						machine_select_n0.setValue(CALIB_ideal_DAC_value);
						machine_select_n1.setValue(Active_motor_type_struct.motor_foot_lifting_vale);
						machine_select_n2.setValue(Active_motor_type_struct.motor_trimmer_activation_value);
						machine_select_n3.setValue(CALIB_MAX_RPM_DAC_value);
						machine_select_n4.setValue(CALIB_AuroPilot_DAC_ideal_value);
						machine_select_n5.setValue(Active_motor_type_struct.motor_foot_lifting_vale);
						machine_select_n6.setValue(Active_motor_type_struct.motor_trimmer_activation_value);
						}
	} 
	break;

	case eNex_main_setup:{
		nexLoop(nex_listen_list_main_setup_page);
		if (NexPrev_screenID!=eNex_main_setup)
		{
			Serial.println("page change to main setup");
			NexPrev_screenID = NexCurrent_screenID;
			chThdSleepMilliseconds(200);
			
		}
		
	}
	break;

	case eNex_stepperSync:{
		nexLoop(nex_listen_list_stepperSync_page);
		if (NexPrev_screenID!=eNex_stepperSync)
		{
			Serial.println("page change to stepperSync Settings");
			NexPrev_screenID = NexCurrent_screenID;
			chThdSleepMilliseconds(200);
			stepperSync_n1.setValue(pulse_width);
			stepperSync_n2.setValue(au_feeder_cutter_act_delay);
			stepperSync_n0.setValue(au_feeder_cutting_delay);
		}
		
	}
	break;






	}
}














#endif /* DISPLAY_H_ */