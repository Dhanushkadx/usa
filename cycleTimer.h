/*
 * cycleTimer.h
 *
 * Created: 5/24/2017 11:31:10 AM
 *  Author: DhanushkaC
 */ 


#ifndef CYCLETIMER_H_
#define CYCLETIMER_H_
MUTEX_DECL(cycleTimer_Mutex);
class cycleTimer {
	
	public:
		cycleTimer(unsigned int _refrechTime, unsigned int _timeOut){
			machineStartedTime_micros = 0;
			machineStopedTime_micros = 0;
			previousMicros =0;
			sinceStoped =0;
			sinceStarted =0;
			interval_us = _refrechTime;
			trickels = 0;
			timerOverflowCount = _timeOut;	
			startTimeRequesterd = true;
			stopTimeRequesterd = true;
			trueDACout_last_writtn_time =0;
			
		}
		
		boolean security_run_check();
		void setTrueDACout_writtrn_time(unsigned long trueDACout_last_writtn_time);
		void sewingDetected();
		void sewingStop();
		void cycleTimerRun(volatile boolean  &_SPIdetect);
		boolean getMachineStatus();
		unsigned long getMachineStopedTime_micros();

		unsigned long getMachineStartedTime_micros();
		
	
	private:
	
	unsigned long trueDACout_last_writtn_time;

	long machineStopedTime_micros;
	long machineStartedTime_micros;
	unsigned int sinceStoped;
	unsigned int sinceStarted;
	boolean current_status_machine;
	boolean startTimeRequesterd;
	boolean stopTimeRequesterd;
	
	long previousMicros;
	long interval_us = 1000;	
	unsigned int trickels;
	unsigned int timerOverflowCount;
	
	void setMachineStartedTime_micros(long);
	void setMachineStopedTime_micros(long);
	void setMachineStatus(boolean);
	void setTrickels(unsigned int);	
	};


void cycleTimer :: cycleTimerRun(volatile boolean  &_SPIdetect){
	if (_SPIdetect==true)
	{
		SPIdetect=false;
		sewingDetected();
		setTrickels(0);		
	}
	
if (getMachineStatus())// only if the sewing is started
	{
			// run timer		
	 
	  unsigned long currentMicros = micros();
	  
	  if(currentMicros - previousMicros > interval_us) 
	
		  previousMicros = currentMicros;
		  trickels++;
		  if (trickels>timerOverflowCount)// mc does not run and timer has been over flowed.
		  {
			  //set machine stopped flags
			  sewingStop();
			  Serial.println("MC STOP");
			
		  }
		  
	  }

}

boolean cycleTimer :: security_run_check(){
	
	unsigned int how_long_since_last_wrriten = micros() - trueDACout_last_writtn_time;
	
	if (how_long_since_last_wrriten>1000000)
	{
		//Serial.println("Check Sensor");
	}
}

void cycleTimer :: setTrueDACout_writtrn_time( unsigned long trueDACout_last_writtn_time){
	this->trueDACout_last_writtn_time = trueDACout_last_writtn_time;
}
void cycleTimer :: setMachineStatus(boolean _status){	
	chMtxLock(&cycleTimer_Mutex);
	current_status_machine = _status;
	chMtxUnlock(&cycleTimer_Mutex);
	
}

boolean cycleTimer :: getMachineStatus(){
	chMtxLock(&cycleTimer_Mutex);
	boolean _xstate = current_status_machine;
	chMtxUnlock(&cycleTimer_Mutex);
	return _xstate;
}

void cycleTimer :: setTrickels(unsigned int _trickels){
	trickels = _trickels;
}

void cycleTimer :: setMachineStopedTime_micros(long _time){
	chMtxLock(&cycleTimer_Mutex);
	machineStopedTime_micros = _time;
	chMtxUnlock(&cycleTimer_Mutex);
	stopTimeRequesterd = false;
} 

void cycleTimer :: setMachineStartedTime_micros(long _time){
	chMtxLock(&cycleTimer_Mutex);
	machineStartedTime_micros = _time;
	chMtxUnlock(&cycleTimer_Mutex);
	startTimeRequesterd= false;
}


void cycleTimer :: sewingDetected(){
	if (startTimeRequesterd)// we are at a starting point
	{
		stopTimeRequesterd = true;
		setMachineStartedTime_micros(micros());// start time requested flag will be reset by this function
		setMachineStatus(true);
		Serial.println("MC START");
	}
	
}

void cycleTimer :: sewingStop(){
	if (stopTimeRequesterd)
	{
		startTimeRequesterd = true;
		setMachineStatus(false);
		// save time
		setMachineStopedTime_micros(micros());
		setTrickels(0);// reset trickling
	}
	
}

unsigned long cycleTimer :: getMachineStopedTime_micros(){
	return machineStopedTime_micros;
}

unsigned long cycleTimer :: getMachineStartedTime_micros(){
	return machineStartedTime_micros;
}
#endif /* CYCLETIMER_H_ */