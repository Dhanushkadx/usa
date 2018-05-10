#include "display.h"



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

	case eNex_msg:{
					nexLoop(nex_listen_list_msg_page);
					if (NexPrev_screenID!=eNex_msg)
					{
						NexPrev_screenID = NexCurrent_screenID;
						if (!LCD_Event_sd)
						{
							msg_t0.Set_font_color_pco(63488);
							msg_t0.setText("SD ERROR! system cannot be started. 1. check SD card 2. Reformat SD card");
							//while(1);
						}
						/*if (!LCD_Event_dac_module)
						{
							msg_t0.Set_font_color_pco(63488);
							msg_t0.setText("DAC ERROR! ");
						}*/
					}
					

	} break;
		
	case eNex_home:{
					nexLoop(nex_listen_list_home_page);
					if (NexPrev_screenID!=eNex_home)
					{
						NexPrev_screenID = NexCurrent_screenID;
						home_paddiling_progress_bar.setValue(0);
						home_t0.setText("");
						if ((!LCD_Event_dac_module)||(!LCD_Event_sd))
						{
							sendCommand("page 17");
							NexCurrent_screenID = eNex_msg;
						}
						
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
						menu_t0.setText("");
						menu_t0.Set_font_color_pco(65535);
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
							t3.Set_font_color_pco(65504);
							t3.setText("Loading...");
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
							
							t3.setText("");
							
											
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
							sew_assist_t4.setText("");
							sew_assist_t4.Set_font_color_pco(65535);
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
							debug_t0.setText("Debug");
							debug_t0.Set_font_color_pco(65535);
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
			setup_main_t0.setText("Setup - Main");
			setup_main_t0.Set_font_color_pco(65535);
			
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

	case eNex_ap_setup:{
		nexLoop(nex_listen_list_ap_setup_page);
		if (NexPrev_screenID!=eNex_ap_setup)
		{
			Serial.println("page change to ap setup");
			NexPrev_screenID = NexCurrent_screenID;
			chThdSleepMilliseconds(200);
			setup_ap_t0.Set_font_color_pco(65535);
			setup_ap_t0.setText("Setup - Auto Pilot");
			setup_ap_bt0.setValue(automatic_foot_lifting);
			setup_ap_bt1.setValue(automatic_ap_start);
			setup_ap_bt2.setValue(continuous_cycle_ap);
			setup_ap_bt3.setValue(automatic_foot_lifting_with_trim);
			setup_ap_n0.setValue(MyAutoPilot.get_ap_autoStart_delay());
			setup_ap_bt4.setValue(MyAutoPilot.get_auto_pilot_protection_by_start_sensor());
			setup_ap_bt5.setValue(MyAutoPilot.get_auto_pilot_protection_stop_when_trim());
			setup_ap_bt6.setValue(MyAutoPilot.get_auto_pilot_waiting_escape_by_start_sensor());
			setup_ap_bt7.setValue(MyAutoPilot.get_auto_pilot_waiting_escape_by_external_trigger());
			
		}
		
	}
	break;






	}
}



void registerNextionEventsCallbacks(){

	msg_b0.attachPop(msg_bt0PopCallback, &msg_b0);
	msg_b1.attachPop(msg_bt1PopCallback, &msg_b1);
	
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
	sew_assist_bt3.attachPop(sewAssist_bt3PopCallback, &sew_assist_bt3);
	sew_assist_b3.attachPop(sewAssist_b3PopCallback, &sew_assist_b3);
	sew_assist_auto_t3.attachPop(sewAssist_t3PopCallbacl, &sew_assist_auto_t3);
	
	setup_main_b2.attachPop(setup_main_b2PopCallback, &setup_main_b2);
	setup_main_b1.attachPop(setup_main_b1PopCallback, &setup_main_b1);
	setup_main_b3.attachPop(setup_main_b3PopCallback, &setup_main_b3);
	setup_main_b4.attachPop(setup_main_b4PopCallback, &setup_main_b4);

	//ap_setup
	setup_ap_b0.attachPop(setup_ap_b0PopCallback, &setup_ap_b0);
	setup_ap_b1.attachPop(setup_ap_b1PopCallback, &setup_ap_b1);
	setup_ap_bt0.attachPop(setup_ap_bt0PopCallback, &setup_ap_bt0);
	setup_ap_bt1.attachPop(setup_ap_bt1PopCallback, &setup_ap_bt1);
	setup_ap_bt2.attachPop(setup_ap_bt2PopCallback, &setup_ap_bt2);
	setup_ap_bt3.attachPop(setup_ap_bt3PopCallback, &setup_ap_bt3);
	setup_ap_bt4.attachPop(setup_ap_bt4PopCallback, &setup_ap_bt4);
	setup_ap_bt5.attachPop(setup_ap_bt5PopCallback, &setup_ap_bt5);	
	setup_ap_bt6.attachPop(setup_ap_bt6PopCallback, &setup_ap_bt6);
	setup_ap_bt7.attachPop(setup_ap_bt7PopCallback, &setup_ap_bt7);

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

