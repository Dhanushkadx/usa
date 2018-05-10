#include "utilityFunction.h"

AutoCutter :: AutoCutter(int connected_pin){
	this->connected_pin = connected_pin;
	pinMode(connected_pin,OUTPUT);
	digitalWrite(connected_pin,LOW);	
	CutterActivation_request = false;
}

CUTTER_STATES AutoCutter::State_cutter = DEACTIVE;

boolean AutoCutter::CutterActivation_request = false;

void AutoCutter:: setRegister_Cutter(unsigned int array[][4], unsigned int array_index){
	if (AutoCutter ::State_cutter == ACTIVE)
	{
		
		array[array_index][3] = array[array_index][3] + ACTIVATE_CUTTER_NUMERICAL_VALUE_OF_REG;
	} 
	else if(AutoCutter :: State_cutter == DEACTIVE)
	{
		array[array_index][3] = array[array_index][3] + DEACTIVATE_CUTTER_NUMERICAL_VALUE_OF_REG;
	}
	
}
 
CUTTER_STATES AutoCutter :: getRegister(unsigned int array[][4], unsigned int array_index){
	
	switch (array[array_index][3])
	{
	case ACTIVATE_CUTTER_NUMERICAL_VALUE_OF_REG:{
		return ACTIVE;
	}
		break;
		
	case DEACTIVATE_CUTTER_NUMERICAL_VALUE_OF_REG:{
		return DEACTIVE;
	}
		break;

	case ACTIVATE_CUTTER_WITH_CREAZING_NUMERICAL_VALUE_OF_REG:{
		return ACTIVE;
	}
	break;

	case DEACTIVATE_CUTTER_WITH_CREAZING_NUMERICAL_VALUE_OF_REG:{
		return DEACTIVE;
	}
	break;
	
default:{
		NO_CHENGE;
	}
		break;
	
	}
	
}

void AutoCutter :: Activate(){

		AutoCutter ::State_cutter = ACTIVE;

		digitalWrite(connected_pin,HIGH);
				
		Serial.println("cutter Activated");
}

void AutoCutter ::  Deactivate(){
	
		AutoCutter ::State_cutter = DEACTIVE;

		digitalWrite(connected_pin,LOW);
		
		Serial.println("cutter Deactivated");
	
}

boolean AutoCutter :: getCutterActivation_request(){
	
	if (CutterActivation_request)
	{
		
		return true;
	}
	
	return false;
}

void AutoCutter :: setCutterActivation_request(boolean _xstate){
	CutterActivation_request = _xstate;
}

CUTTER_STATES AutoCutter :: getState(){
	CUTTER_STATES result = AutoCutter:: State_cutter;
	return result;
}

void setCutterActivation_request_LCD(boolean _xstate){
	
	AutoCutter::CutterActivation_request = _xstate;
}

void setState_from_LCD(CUTTER_STATES _xstate){
	AutoCutter::State_cutter = _xstate;
}


unsigned int Utility :: spi_count = 0;


void Utility :: count_spi(boolean &spi_flag){
	if (spi_flag)
	{	
		spi_flag = false;
		spi_count++;
	}
}

unsigned int Utility :: getCurrentSPI_count(){
	return Utility :: spi_count;
}

void Utility ::setCurrentSPI_count(unsigned int newValue){
		spi_count = newValue;
}

