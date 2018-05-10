

void foot_activate(){
setState_trim(false);
setState_foot(true);
	my_foot_Event->setRegistation_request(true);
	switch (Active_motor_type_struct.Active_motor_type)
	{
		case ISM:{
		//Serial.println("activate foot for for ISM");
			digitalWrite(FOOT,HIGH);
		}
		break;
		case PEGASUS_HPV_90:{
			//Serial.println("activate foot for for HPV");
			//dac.setVoltage((Active_motor_type_struct.motor_foot_lifting_vale*1000)/1.2,false);
			//dac.setVoltage(1600,false);
			//chThdSleepMilliseconds(80);
			dac.setVoltage(680,false);
		}
		break;

	}
	
}
void trim_activate(){
//chMtxLock(&DAC_HPV_90_LOCK);
	setState_foot(true);
	setState_trim(true);
	my_trim_Event->setRegistation_request(true);
	if (MyAutoPilot.get_auto_pilot_protection_stop_when_trim())
	{
		MyAutoPilot.set_auPiolot_State(IGNOR_SENS);
	}

	
	switch (Active_motor_type_struct.Active_motor_type)
	{

		case ISM:{
			//Serial.println("activate trim for for ISM");
			digitalWrite(TRIM,HIGH);
		}
		break;
		case PEGASUS_HPV_90:{
		//Serial.println("activate trim for for HPV");
			//dac.setVoltage((Active_motor_type_struct.motor_trimmer_activation_value*1000)/1.2,false);
			dac.setVoltage(CALIB_ideal_DAC_value,false);
			chThdSleepMilliseconds(80);
			//dac.setVoltage(250,false);
			dac.setVoltage(250,false);
			
		}
		break;
	}
//chMtxUnlock(&DAC_HPV_90_LOCK);
	
}

void ideal(){ switch (Active_motor_type_struct.Active_motor_type)
	{
		case ISM:{
			digitalWrite(FOOT,LOW);
			digitalWrite(TRIM,LOW);
			//Serial.println("activate ideal for for ISM");
		}
		break;
		case PEGASUS_HPV_90:{
			//Serial.println("activate ideal for for HPV");
			//dac.setVoltage((CALIB_ideal_DAC_value*1000)/1.2,false);
			dac.setVoltage(1500,false);
		}
		break;

	}
	//myfoot_trim_Event->setCurrent_State(_OFF);
	setState_foot(false);
	setState_trim(false);
}