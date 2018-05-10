





void ap_time_out() {
	
	Serial.println("time out");
	Serial.println("Single Auto Cycle only !");
	setAutoPilot_EN(false);
	detachInterrupt(digitalPinToInterrupt(interruptPin));
	setLCD_Event_autopilot_canceled(true);
	Serial.println("AU_RESULT_CANCEL !");
	MyAutoPilot.set_auPiolot_State(WAIT_FOR_START);
	prev_MODE = AUTO_PILOT_CYCLE_REST;
}

void buzze_on(){
	digitalWrite(BUZZER,HIGH);
}

void buzze_off(){
	digitalWrite(BUZZER,LOW);
}