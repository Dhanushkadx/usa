// 
// 
// 

#include "syncx.h"


syncx :: syncx(char* file_name){
this->file_name = file_name;
Event_state = _OFF;
requested_state = _OFF;

}

void syncx :: setOn_CallBack(_callbackFunction nFn){
	_OnCallBackFunction = nFn;
}

void syncx :: setOff_CallBack(_callbackFunction nFn){
	_OFFCallBackFunction = nFn;
}

eEvent_type syncx :: getCurrent_State(){
	return Event_state;
}


boolean syncx :: getAction_request(){
	return request_action;
}

boolean syncx :: getRegistation_request(){
	boolean temp = request_registation;
	request_registation = false;
	return temp;
}

void syncx :: setAction_request(boolean request){
	if (getCurrent_State() == _ON)
	{
	setPending_Event(_OFF);
	}
	else{setPending_Event(_ON); }
	
	request_action = request;
}

void syncx :: setRegistation_request(boolean request){
	if (getCurrent_State() == _ON)
	{
		setPending_Event(_OFF);
	}
	else{setPending_Event(_ON); }
	request_registation = request;
}

void syncx :: setPending_Event(eEvent_type state){
	requested_state = state;
}

eEvent_type syncx :: getPending_Event(){
	return requested_state;
}


void syncx :: setCurrent_State(eEvent_type state){
	Event_state = state;
}




void syncx :: sync_rec(unsigned int spi_number){
	
	if (getRegistation_request())// if there is registration request
	{
	Serial.print("registering event to array @ ");
	Serial.println(spi_number);
		eEvent_type result = getPending_Event();

		//check previous index
		unsigned int Prev_Index=0;
		if (Index>0)// if not zero go to previous index
		{
			Prev_Index = Index - 1;
		}
		else{
			Prev_Index = Index;// if zero there is not previous index
		}
		if (this->sync_data[Prev_Index][0]==spi_number)// if we did not get a new spi number 
		{
			if(Index>0); Index--;//  last time we have increse index but we are in same spi so decrese it 
		}

		switch (result)
		{
		case _ON:{
					this->sync_data[Index][0] = spi_number;
					this->sync_data[Index][1] = 1;
					Index++;
					Serial.println("__________ON");

		}
			break;
		case _OFF:{
					this->sync_data[Index][0] = spi_number;
					this->sync_data[Index][1] = 0;
					Index++;
					Serial.println("_________OFF");
		}
		break;
		}

		previous_spi_number = spi_number;
	}
}

void syncx :: sync_actions(){
		
	if (getAction_request())// if there is registration request
	{
		request_action = false;
		eEvent_type result = getPending_Event();

		switch (result)
		{
			case _ON:{
						if (_OnCallBackFunction!=NULL)
						{
							_OnCallBackFunction();
						}
						setCurrent_State(_ON);
						Serial.println("Action _ON");
			}
			break;
			case _OFF:{
						if (_OFFCallBackFunction!=NULL)
						{
							_OFFCallBackFunction();
						}
						setCurrent_State(_OFF);
						Serial.println("Action _OFF");
			}
			break;
		}
	}
}

void syncx :: import_data_from_sd(){
	String space;
	Serial.println("reading file content<<<<<<<<<<");
	sdloader ::dump_file(file_name, space);
	Serial.println("fetching array <<<<<<<<<<");
	for (int tempIndex =0; tempIndex<9; tempIndex++)
	{
		sync_data[tempIndex][0] = 0;
		sync_data[tempIndex][1] = 0;
	}

	sdloader ::loading_event_data_from_SD(file_name,sync_data,9);
	Serial.println("array content");
	for (int l = 0; l<10; l++)
	{
		Serial.print(sync_data[l][0]);
		Serial.print(" : ");
		Serial.println(sync_data[l][1]);
	}
	Serial.println("Auto Index set to Zero");
	autoEvent_Index = 0;
}

void syncx :: export_data_to_sd(){
	sdloader :: write_event_data_to_SD(file_name,this->sync_data,9);
}


void syncx :: autoEvent_activator(unsigned int spi_number){
	
	if (sync_data[autoEvent_Index][0] == spi_number)
	{
		Serial.print("event triggered at >>");
		Serial.println(spi_number);
		if (sync_data[autoEvent_Index][1] == 1)
		{
			setPending_Event(_ON);
		}
		else{
			setPending_Event(_OFF);
		}
		autoEvent_Index++;

		request_action = true;
		sync_actions();
	}
}

void syncx :: reset_event_profile(){

	for (int tempIndex =0; tempIndex<9; tempIndex++)
	{
		sync_data[tempIndex][0] = 0;
		sync_data[tempIndex][1] = 0;
	}

	autoEvent_Index = 0;
	Index = 0;
}