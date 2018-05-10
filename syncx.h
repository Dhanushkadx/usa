// syncx.h

#ifndef _SYNCX_h
#define _SYNCX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif
#include "sdloader.h"

extern "C" {
	typedef void (*_callbackFunction)(void);
};

typedef enum eEvent_type {_ON, _OFF};

class syncx
{
public:
		syncx(char* file_name);
		void sync_rec(unsigned int spi_number);
		void sync_actions();
		void setRegistation_request(boolean request);

		void setOn_CallBack(_callbackFunction nFn);
		void setOff_CallBack(_callbackFunction nFn);
		void export_data_to_sd();
		void setAction_request(boolean request);// check for events
		void import_data_from_sd();
		void autoEvent_activator(unsigned int spi_number);
		boolean getRegistation_request();
		void reset_event_profile();
		void setCurrent_State( eEvent_type _event);
		void setPending_Event(eEvent_type _event);
		
protected:
private:

boolean getAction_request();// check for events






eEvent_type getPending_Event();

eEvent_type getCurrent_State();


//void setRegisterEvent(unsigned int spi_number, boolean stateOfevent);
	
	

	unsigned int sync_data[10][2];
	unsigned int Index;
	unsigned int  autoEvent_Index;
	char* file_name;
	unsigned int previous_spi_number = 0;
	

	//flags
	boolean request_action;
	boolean request_registation = false;
	eEvent_type requested_state;
	eEvent_type Event_state;


	_callbackFunction _OnCallBackFunction = NULL, _OFFCallBackFunction = NULL;
};
#endif

