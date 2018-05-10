// 
// 
// 

#include "ap_autoStart.h"


autoPilot :: autoPilot(unsigned int sensor_connected_pin){
	this->sensor_connected_pin = sensor_connected_pin;
	pinMode(sensor_connected_pin,INPUT_PULLUP);
	Current_State_auPilot = IGNOR_SENS;
};

void autoPilot :: set_ap_autoStart_delay(unsigned long ap_autoStart_delay){
this->ap_autoStart_delay = ap_autoStart_delay;
}

boolean autoPilot :: wait_for_start_signal(){
	if (Current_State_auPilot == WAIT_FOR_START)
	{		
		//state_sensor = 0;
		state_sensor = digitalRead(sensor_connected_pin);
		unsigned int sensor_read_time = millis();
		
			if (stage == 0)
			{
				if (!state_sensor)
				{
					sensor_trigger_time = sensor_read_time;
					stage = 1;
					Serial.println("ap auto signal received");
					_DclickF();
					return false;
				}
				else{ return false;}
			}
			
			else if (stage == 1)
			{
				if (state_sensor)
				{
					stage = 0;
					_stopclickF();
					return false;
				}
				unsigned long currentMillis = millis();
				Serial.println("timer waiting ");
				if(sensor_read_time - sensor_trigger_time > ap_autoStart_delay){
					// save the last time you blinked the LED
					//previousMillis = currentMillis;
					stage = 0;
					_stopclickF();
					Current_State_auPilot = AP_ON_GOING;
					return true;
				}

				else{
					return false;
				}
			}
			
		}

	else{
		return false;
	}
}


void autoPilot :: attach_Dclick(_callbackFunction newF){
	_DclickF = newF;
}

void autoPilot :: attach_stopclick(_callbackFunction newF){
	_stopclickF = newF;
}


boolean autoPilot :: garment_avalability(){
	state_sensor = digitalRead(sensor_connected_pin);
	return state_sensor;
}


void autoPilot :: set_auPiolot_State(AU_PILOT_STATE Current_State_auPilot){
	this->Current_State_auPilot = Current_State_auPilot;
	//stage =0; ???????????????
}

unsigned long autoPilot::get_ap_autoStart_delay(){
	return this->ap_autoStart_delay;
}

AU_PILOT_STATE autoPilot :: get_auPiolot_State(){
	return this->Current_State_auPilot;
}

boolean autoPilot :: get_auto_pilot_protection_by_start_sensor(){
	return this-> auto_pilot_protection_by_start_sensor;
}

void autoPilot :: set_auto_pilot_protection_by_start_sensor(boolean xstate){
	 this->auto_pilot_protection_by_start_sensor = xstate;
}



boolean autoPilot :: get_auto_pilot_protection_stop_when_trim(){
	return this-> auto_pilot_protection_stop_when_trim;
}

void autoPilot :: set_auto_pilot_protection_stop_when_trim(boolean xstate){
	this->auto_pilot_protection_stop_when_trim = xstate;
}

void autoPilot :: set_last_time_ap_done(unsigned long last_time_ap_done){
	this->last_time_ap_done = last_time_ap_done;
}


unsigned long autoPilot :: get_last_time_ap_done(){
	return this->last_time_ap_done;
}

void autoPilot :: set_auto_pilot_waiting_escape_by_start_sensor(boolean auto_pilot_waiting_escape_by_start_sensor){
	this->auto_pilot_waiting_escape_by_start_sensor = auto_pilot_waiting_escape_by_start_sensor;		
}

void autoPilot :: set_auto_pilot_waiting_escape_by_external_trigger(boolean auto_pilot_waiting_escape_by_external_trigger){
	this->auto_pilot_waiting_escape_by_external_trigger = auto_pilot_waiting_escape_by_external_trigger;
}

boolean autoPilot :: get_auto_pilot_waiting_escape_by_start_sensor(){
	return this->auto_pilot_waiting_escape_by_start_sensor;
}

boolean autoPilot :: get_auto_pilot_waiting_escape_by_external_trigger(){
	return this->auto_pilot_waiting_escape_by_external_trigger;
}

void autoPilot :: set_state_external_trigger(boolean state_external_trigger){
	this->state_external_trigger = state_external_trigger;
}
boolean autoPilot :: get_state_external_trigger(){
	return this->state_external_trigger;
}