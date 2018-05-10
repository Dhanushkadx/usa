/*
 * RTSOdataShare.h
 *
 * Created: 4/21/2017 5:45:11 PM
 *  Author: DhanushkaC
 */ 


#ifndef RTSODATASHARE_H_
#define RTSODATASHARE_H_


eStateMODE getMode(){
	chMtxLock(&Flags_communication);
	eStateMODE temMode = current_MODE;
	chMtxUnlock(&Flags_communication);
	return temMode;
	}
	
void setMode(eStateMODE _current_MODE){
	chMtxLock(&Flags_communication);
	current_MODE= _current_MODE;
	chMtxUnlock(&Flags_communication);
}

void setTeachingSewing_EN(boolean _xstate){
	chMtxLock(&Flags_communication);
	SPI_speed_profil_teaching_EN =_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getsetteachingSewing_EN(){
	chMtxLock(&Flags_communication);
	if (SPI_speed_profil_teaching_EN)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
	
}

void setAutoDriveTest_EN(boolean _xstate){
	chMtxLock(&Flags_communication);
	AutoDriveTest_EN =_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getAutoDriveTest_EN(){
	chMtxLock(&Flags_communication);
	if (AutoDriveTest_EN)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
	
}

boolean getAutoPilot_EN(){
	chMtxLock(&Flags_communication);
	if (AutoPilot_EN)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setAutoPilot_EN(boolean _xstate){
	chMtxLock(&Flags_communication);
	AutoPilot_EN =_xstate;
	chMtxUnlock(&Flags_communication);
}


boolean getTeachingReset_EN(){
	chMtxLock(&Flags_communication);
	if (SPI_speed_profil_reset)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setTeachingReset_EN(boolean _xstate){
	chMtxLock(&Flags_communication);
	SPI_speed_profil_reset =_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getSetup_EN(){
	chMtxLock(&Flags_communication);
	if (Setup_EN)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setSetup_EN(boolean _xstate){
	chMtxLock(&Flags_communication);
	Setup_EN =_xstate;
	chMtxUnlock(&Flags_communication);
}



boolean getSerial_push_analogInputData_EN(){
	chMtxLock(&Flags_communication);
	if (Serial_push_EN_analogInputData)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setSerial_push_analogInputData_EN(boolean _xstate){
	chMtxLock(&Flags_communication);
	Serial_push_EN_analogInputData =_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getSerial_push_autoPilotData_EN(){
	chMtxLock(&Flags_communication);
	if (Serial_push_EN_autoPilotData)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setSerial_push_autoPilotData_EN(boolean _xstate){
	chMtxLock(&Flags_communication);
	Serial_push_EN_autoPilotData =_xstate;
	chMtxUnlock(&Flags_communication);
}

void setEvent_ch0(unsigned int _xevent){
	chMtxLock(&Event_communication);
	eventCH0 = _xevent ;
	chMtxUnlock(&Event_communication);
	
}

unsigned int getEvent_ch0(){
	unsigned int _event;
	chMtxLock(&Event_communication);
	_event = eventCH0;
	chMtxUnlock(&Event_communication);
	//Serial.print("get event  ");
	//Serial.println(_event);
	return _event;
}


void setForceStart_autoPilot(boolean _xstate){
	chMtxLock(&Flags_communication);
	AutoPilot_forceStart_EN =_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getForceStart_autoPilot(){
	chMtxLock(&Flags_communication);
	if (AutoPilot_forceStart_EN)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}



void setLCD_Event_creasing(boolean _xstate){
	chMtxLock(&Flags_communication);
	LCD_Event_creasing=_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getLCD_Event_creasing(){
	chMtxLock(&Flags_communication);
	if (LCD_Event_creasing)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setLCD_Event_autopilot_canceled(boolean _xstate){
	chMtxLock(&Flags_communication);
	LCD_Event_autopilot_canceled=_xstate;
	Serial.println("cancel lcd event set");
	chMtxUnlock(&Flags_communication);
}

// autopilot session change event
void setLCD_Event_autopilot_session_chenged (boolean _xstate){
	chMtxLock(&Flags_communication);
	LCD_Event_autopilot_session_chenged=_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getLCD_Event_autopilot_session_chenged(){
	chMtxLock(&Flags_communication);
	if (LCD_Event_autopilot_session_chenged)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

boolean getLCD_Event_LCD_Event_autopilot_canceled(){
	chMtxLock(&Flags_communication);
	if (LCD_Event_autopilot_canceled)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setLCD_refresh(boolean _xstate){
	chMtxLock(&Flags_communication);
	LCD_refresh=_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getLCD_refresh(){
	chMtxLock(&Flags_communication);
	if (LCD_refresh)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}


boolean getState_foot(){
	chMtxLock(&Flags_communication);
	if (Sta_foot)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setState_foot(boolean _xstate){
	chMtxLock(&Flags_communication);
	//digitalWrite(FOOT,_xstate);
	Sta_foot=_xstate;
	chMtxUnlock(&Flags_communication);
}

boolean getState_trim(){
	chMtxLock(&Flags_communication);
	if (Sta_trim)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void setState_trim(boolean _xstate){
	chMtxLock(&Flags_communication);
	//digitalWrite(FOOT,_xstate);
	Sta_trim=_xstate;
	chMtxUnlock(&Flags_communication);
}

void set_endCutter_EN(boolean xstate){
	chMtxLock(&Flags_communication);
	END_CUT_EN = xstate;
	chMtxUnlock(&Flags_communication);
}

boolean get_endCutter_EN(){
	chMtxLock(&Flags_communication);
	boolean xstate = END_CUT_EN;
	chMtxUnlock(&Flags_communication);
	return xstate;
}




#endif /* RTSODATASHARE_H_ */