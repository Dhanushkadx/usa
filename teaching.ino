
eResult_teaching_states teachingSewing(unsigned int _dacout){
	
	if (!getsetteachingSewing_EN())
	{
		return RESULT_SPI_TEACHING_CANCEL;
	}
	// we are listing to the paddle to start the teaching recoding
	chMtxLock(&SerialDataSH_Mutex_CH0);
	int r = AN_CH0_sensor_data_AVR_GLOB;
	chMtxUnlock(&SerialDataSH_Mutex_CH0);//
	// teaching wont be started till press the paddle at first
	if ((DACDataIndex<zeroSpeed_detectionTime_starting_point)&&(r<SPI_teaching_en_min_analogCH0_input))
	{
		previousSPI_register_time = micros();
		//Serial.println("press paddle to start");
		my_foot_Event->reset_event_profile();
		my_trim_Event->reset_event_profile();
		return RESULT_SPI_TEACHING_PROCCESING;
	}
	
	
	
	if (SPI_updated)
	{
		
		SPI_updated=false;
		//before we save there may be missed spis as "currentSPI" increases by ISR
		//check privios spi vs current 
		if (currentSPI - previousSPI> 1)// if the differec
		{
			_dacout = (_dacout<CALIB_ideal_DAC_value)? 0: _dacout;// calibrate dacout****************** 0???
			DACData[DACDataIndex][0] = (currentSPI -1 );
			DACData[DACDataIndex][1] = _dacout;
			DACData[DACDataIndex][2] = (currentSPI_register_time-10);// add negligibly delay 
			DACDataIndex++;
			Serial.println("SPI missed detected and corrected !");
			
		}
		_dacout = (_dacout<CALIB_ideal_DAC_value)? 0: _dacout;// calibrate dacout****************** 0???
		DACData[DACDataIndex][0] = currentSPI;
		DACData[DACDataIndex][1] = _dacout;
		DACData[DACDataIndex][2] = currentSPI_register_time;
		previousSPI = currentSPI;
		// foot trim sets
		my_trim_Event->sync_rec(currentSPI);
		my_foot_Event->sync_rec(currentSPI);
		
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
	
	myCutterEvent->export_data_to_sd();
	my_trim_Event->export_data_to_sd();
	my_foot_Event->export_data_to_sd();
}