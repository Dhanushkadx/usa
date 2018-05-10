

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
	// ESPSerial.println("downtime_end");
	// delay(1000);
// 	if (ESPSerial.available())
// 	Serial.write(ESPSerial.read());
// 	if (Serial.available())
// 	ESPSerial.write(Serial.read());
// IoT random data generator
/*
	unsigned long currentMillis = millis();
	if(currentMillis - previousMillis > iot_data_refresh_interval) {
		// save the last time you blinked the LED
		previousMillis = currentMillis;
		
		char buff[50];
		
	unsigned int key = random(0,3);
	
	switch (key)
	{
	case 0:{ Serial.println("sewing_end"); sprintf(buff,"sewing_end=%d",iot_data_refresh_interval); ESPSerial.println(buff);

	}
		break;

	case 1:{ Serial.println("downtime_end"); sprintf(buff,"downtime_end=%d",iot_data_refresh_interval); ESPSerial.println(buff);
	}

		break;

	case 2:{ Serial.println("waiting_end"); sprintf(buff,"waiting_end=%d",iot_data_refresh_interval); ESPSerial.println(buff);
	}

		break;

	}

	iot_data_refresh_interval = random(1000,10000);

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
							ideal();
							cutter_off();
							chMtxLock(&Wheel_Cutter);
							myCutterEvent->setPending_Event(_OFF);
							myCutterEvent->setCurrent_State(_OFF);
							chMtxUnlock(&Wheel_Cutter);
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
							 MyAutoPilot.set_last_time_ap_done(millis());
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
						
		
					}
		break;
	case SPI_TEACHING:{
						if(prev_MODE!=SPI_TEACHING){
							Serial.println("Teaching mode - interrupt activated!");
							prev_MODE=SPI_TEACHING;
							DACDataIndex=0;
							resetTeachProfile();
							currentSPI=0;
							previousSPI=0;
							previousSPI_register_time = micros();
							attachInterrupt(digitalPinToInterrupt(interruptPin), EXinterruptRooting, RISING);
							RGB_leds.set_smartGlow(TEACHING);
							RGB_leds.set_smartFlickering(3);
							myCutterEvent->reset_event_profile();
							my_trim_Event->reset_event_profile();
							my_trim_Event->setCurrent_State(_OFF);
							my_foot_Event->reset_event_profile();
							my_foot_Event->setCurrent_State(_OFF);
							
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
						// foot lifting is inside the teaching function.
						
							chMtxLock(&Wheel_Cutter);
							myCutterEvent->sync_rec(currentSPI);
							myCutterEvent->sync_actions();
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
						// auto start functions- foot lifter

						eAUTO_PILOT_RESULTS results = autoPilotProcessor();
						
						if (results==RESULT_AU_SUCSEDD_DONE)
						{
							Serial.println("AP successfully done !");
							setAutoPilot_EN(true);
							detachInterrupt(digitalPinToInterrupt(interruptPin));
							MyAutoPilot.set_last_time_ap_done(millis());
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
									//auto start functions- foot lifter
									if (automatic_foot_lifting)
									{
										if (automatic_foot_lifting_with_trim)
										{
											trim_activate();
										}
										else{
											foot_activate();
										}
										
										// set these events in autopilot auto too************and check
										my_trim_Event->setCurrent_State(_OFF);
										my_trim_Event->setPending_Event(_ON);

										my_foot_Event->setCurrent_State(_OFF);
										my_foot_Event->setPending_Event(_ON);
									}

									switch(prev_MODE){
										case MANUAL_SEW:{// just starting 
														Serial.println("starting auto pilot cycle");
														//while(1);
														prev_MODE = AUTO_PILOT_CYCLE_REST;
														//MyAutoPilot.set_auPiolot_State(WAIT_FOR_START);

														if(automatic_ap_start){

															MyAutoPilot.set_auPiolot_State(WAIT_FOR_START);
														}
														else{
															MyAutoPilot.set_auPiolot_State(IGNOR_SENS);
														}
										
											}
											break;
										case AUTO_PILOT:{// going to next cycle
														Serial.println("next auto pilot cycle");
														
														// single cycle only
														if (!continuous_cycle_ap)
														{
															Serial.println("Single Auto Cycle only !");
															setAutoPilot_EN(false);
															detachInterrupt(digitalPinToInterrupt(interruptPin));
															setLCD_Event_autopilot_canceled(true);
															Serial.println("AU_RESULT_CANCEL !");
															MyAutoPilot.set_auPiolot_State(WAIT_FOR_START);
															prev_MODE = AUTO_PILOT_CYCLE_REST;
															setMode(AUTO_PILOT);
														}
														else{// We are in continuous mode 
															Serial.println("Checking Sensor");
															if ((!MyAutoPilot.garment_avalability())&&(automatic_ap_start))
															{
																Serial.println("sensor is already triggered");
																return;
															}
															setAutoPilot_EN(true);
															MyAutoPilot.set_auPiolot_State(WAIT_FOR_START);
															prev_MODE = AUTO_PILOT_CYCLE_REST;
															setMode(AUTO_PILOT);
														}
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

