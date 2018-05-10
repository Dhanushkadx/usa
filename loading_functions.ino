


boolean I2C_scane(byte& dac_address)
{
	byte error, address;
	int nDevices;

	Serial.println("Scanning...");

	nDevices = 0;
	for(address = 1; address < 127; address++ )
	{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();

		if (error == 0)
		{
			Serial.print("I2C device found at address 0x");
			if (address<16)
			Serial.print("0");
			Serial.print(address,HEX);
			Serial.println("  !");
			dac_address = address;

			nDevices++;
		}
		else if (error==4)
		{
			Serial.print("Unknow error at address 0x");
			if (address<16)
			Serial.print("0");
			Serial.println(address,HEX);
		}
	}
	if (nDevices == 0){
	Serial.println("No I2C devices found\n");
	dac_address = 0;
	return false;
	}
	else{
	Serial.println("done\n");
	return true;
	}
	
}
void loading_parameters_from_SD(){
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
	// load ap data
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
		
}





void Loading_profile_switch(SPI_PROFILE_CATOGERY profile_type){// LCD will call these functions to change the profile type which is to be lodded to next
	switch (profile_type)
	{
		case DEFAULT_PROFILE:{msg_teaching_t0_message =  msg_sew_assist_auto_t3_message = LCD_text_meassage0; spi_vs_speed_profile_type_saving = spi_vs_speed_profile_type_auto_pilot = DEFAULT_PROFILE;  myCutterEvent = &defaultProfileEvent; my_trim_Event =&default_trim_Event; my_foot_Event =&default_foot_Event; Serial.println("Profile type change to DEFAULT");}
		break;
		case NECK_LINE:{ msg_teaching_t0_message =  msg_sew_assist_auto_t3_message = LCD_text_meassage1; spi_vs_speed_profile_type_saving = spi_vs_speed_profile_type_auto_pilot = NECK_LINE;  myCutterEvent = &neckProfileEvent; my_trim_Event = &neck_trim_Event; my_foot_Event = &neck_foot_Event; Serial.println("Profile type change to NECK LINE");}
		break;
		case ARM_LEFT:{msg_teaching_t0_message =  msg_sew_assist_auto_t3_message = LCD_text_meassage2; spi_vs_speed_profile_type_saving = spi_vs_speed_profile_type_auto_pilot = ARM_LEFT;  myCutterEvent = &armLProfileEvent; my_trim_Event = &armL_trim_Event; my_foot_Event = &armL_foot_Event; Serial.println("Profile type change to ARM LEFT");}
		break;
		case ARM_RIGHT:{msg_teaching_t0_message = msg_sew_assist_auto_t3_message = LCD_text_meassage3; spi_vs_speed_profile_type_saving = spi_vs_speed_profile_type_auto_pilot = ARM_RIGHT;  myCutterEvent = &armRProfileEvent; my_trim_Event =&armR_trim_Event; my_foot_Event =&armR_foot_Event; Serial.println("Profile type change to ARM RIGHT");}
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
	SPI_speed_profil_length_SH = getTeachProfile_length(DACData,SIZE_OF_DAC_DATA_ARRY);
	
	setLCD_Event_autopilot_session_chenged(true);
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