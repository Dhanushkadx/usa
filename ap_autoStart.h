// ap_autoStart.h

#ifndef _AP_AUTOSTART_h
#define _AP_AUTOSTART_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

extern "C" {
	typedef void (*_callbackFunction)(void);
};

#include "variable_types.h"
class autoPilot
{
public:

	autoPilot(unsigned int sensor_connected_pin);
	boolean wait_for_start_signal();
	void set_auPiolot_State(AU_PILOT_STATE Current_State_auPilot);
	void set_ap_autoStart_delay(unsigned long ap_autoStart_delay);
	unsigned long get_ap_autoStart_delay();
	boolean garment_avalability();
	void set_auto_pilot_protection_by_start_sensor(boolean xstate);
	boolean get_auto_pilot_protection_by_start_sensor();
	AU_PILOT_STATE get_auPiolot_State();
	void set_auto_pilot_protection_stop_when_trim(boolean xstate);
	boolean get_auto_pilot_protection_stop_when_trim();

	void attach_Dclick(_callbackFunction newF);
	void attach_stopclick(_callbackFunction newF);

	void set_last_time_ap_done(unsigned long last_time_ap_done);
	unsigned long get_last_time_ap_done();

	boolean get_auto_pilot_waiting_escape_by_start_sensor();
	boolean get_auto_pilot_waiting_escape_by_external_trigger();
	void set_auto_pilot_waiting_escape_by_start_sensor(boolean auto_pilot_waiting_escape_by_start_sensor);
	void set_auto_pilot_waiting_escape_by_external_trigger(boolean auto_pilot_waiting_escape_by_start_sensor);
	void set_state_external_trigger(boolean state_external_trigger);
	boolean get_state_external_trigger();

protected:
private:
	AU_PILOT_STATE Current_State_auPilot;
	unsigned int sensor_connected_pin;
	unsigned long sensor_trigger_time;
	unsigned long ap_autoStart_delay = 1000; 
	boolean state_sensor = 0;
	boolean state_external_trigger;
	unsigned int stage;
	//boolean ap_start_by_start_sensor; there is a global variable for this
	boolean auto_pilot_protection_by_start_sensor;
	boolean auto_pilot_protection_stop_when_trim;
	boolean auto_pilot_waiting_escape_by_start_sensor;
	boolean auto_pilot_waiting_escape_by_external_trigger;
	unsigned long last_time_ap_done;

	_callbackFunction _DclickF;_callbackFunction _stopclickF;
};

#endif

