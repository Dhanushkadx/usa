// 
// 
// 

#include "smart_paddle_sensor.h"

SmartPaddle :: SmartPaddle(int channel_1){
	
	 analogPin0 = channel_1;
	
}




void SmartPaddle :: set_ch0_to_dac_limits(unsigned int high_limit, unsigned int low_limit){
	CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value = high_limit;
	CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value = low_limit;
}

void SmartPaddle :: setEvent_para(unsigned int TH_ch1_detection_min_threshold,unsigned int TI_first_pulse_registering_delay,unsigned int TI_second_puls_stating_delay,
unsigned int TH_ch1_trim_detection_threshold,unsigned int TI_second_pulse_rising_delay,unsigned int TI_second_pulse_rising_debounce){
	this->TH_ch1_detection_min_threshold = TH_ch1_detection_min_threshold;
	this->TI_first_pulse_registering_delay = TI_first_pulse_registering_delay;
	this->TI_second_puls_stating_delay = TI_second_puls_stating_delay;
	this->TH_ch1_trim_detection_threshold = TH_ch1_detection_min_threshold;
	this->TI_second_pulse_rising_delay = TI_second_pulse_rising_delay;
	this->TI_second_pulse_rising_debounce = TI_second_pulse_rising_debounce;
}

unsigned int SmartPaddle :: getSensor_value_to_DAC(long analogSamplesAverageCH0){
	
	// process analog input to smooth and calibrations
		/*Serial.print(analogSamplesAverageCH0);
		Serial.print("  :  ");
		Serial.print(CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value);
		Serial.print("  :  ");
		Serial.println( CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value);*/
		
		
		unsigned int trueDACout = map(analogSamplesAverageCH0,analogLowCH0, analogHighCH0, CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value, CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value);
		
		return trueDACout;

}

//*************************
void SmartPaddle :: process_paddleSensorAnalogDataCH0(long &_analogSamples_RAW_CH0, long &_analogSamplesAverageCH0, unsigned long &now){
	
	static int analogValue_0;
		
		analogValue_0 = analogRead(analogPin0);  // Get analog 0 read
		now = millis();
	
		// Add new analog reading to buffer and return oldest reading
		int oldestSample_0 = addSampleCH0(analogValue_0);
		// Get running average, pass the latest and oldest analog sample reading
		_analogSamplesAverageCH0 = runningAverageCH0(analogValue_0, oldestSample_0);		
		
		_analogSamples_RAW_CH0 = _analogSamplesAverageCH0;
		
		
		//processing analog further
		_analogSamplesAverageCH0 = (_analogSamplesAverageCH0>=CALIBRATE_analogSamplesAverageCH0_offset_to_make_it_zero)? 
									_analogSamplesAverageCH0-CALIBRATE_analogSamplesAverageCH0_offset_to_make_it_zero : 0;
}

// Function - running average
long SmartPaddle :: runningAverageCH0(long newSample, long oldSample){
	// Add new sample and subtract old sample from the samples buffer total
	// then return sample average
	sampleBufferTotalCH0 += newSample;  // Add new analog sample
	sampleBufferTotalCH0 -= oldSample;  // Subtract oldest analog sample
	return sampleBufferTotalCH0 / samplesBufferCH0;  // Return average analog sample reading
}

// Function - add and remove analog samples from ring buffer, return oldest sample
// The ring buffer is used to keep track of the oldest sample.
int SmartPaddle:: addSampleCH0(int newSampleCH0) {
	// Add new analog read sample to the ring buffer and return the oldest analog reading
	int oldSampleCH0;
	if (lastSampleIndexCH0 == samplesBufferCH0 - 1 ) { // Check if end off buffer reached
		oldSampleCH0 = analogSamplesCH0[0];  // Get old analog sample from start of buffer
		analogSamplesCH0[0] = newSampleCH0;  // Add new analog sample to start of buffer
		lastSampleIndexCH0 = 0;  // Record sample index currently working on
		} else {
		lastSampleIndexCH0 ++;  // Move to next index
		oldSampleCH0 = analogSamplesCH0[lastSampleIndexCH0];  // Get old analog sample
		analogSamplesCH0[lastSampleIndexCH0] = newSampleCH0;  // Add new analog sample
	}
	return oldSampleCH0;  // Return old analog sample
}




void SmartPaddle :: set_CH0_AN_MIN_value(int value){ analogLowCH0 = value;}
void SmartPaddle :: set_CH0_AN_MAX_value(int value){analogHighCH0 = value;}

int SmartPaddle :: get_CH0_AN_MIN_value(){ return analogLowCH0;}
int SmartPaddle :: get_CH0_AN_MAX_value(){ return analogHighCH0;}
	
// Event Detection


ePADDLE_EVENTS SmartPaddle :: event_detecting(unsigned int CH1_AVRanalogValue, unsigned long now){

		// veriable meanning 
		//ch1_detection_min_level = 100;
		//waiting_timeTofoot_detection_since_min_detection = 200 default
		//second_due_time = 200; // defaul
		 now = millis(); // current (relative) time in msecs.
	if (stage == 0){
			if (CH1_AVRanalogValue>this->TH_ch1_detection_min_threshold)
			{
				sampaleOf100_recevied_time = now;
				Serial.println("100");
				stage = 1;
			}
			//return IDEAL;
		 }
		 	 
		 
	else if (stage == 1){
			 if (CH1_AVRanalogValue<TH_ch1_detection_min_threshold)// first pulse is over
			 {
				sampaleOfZero_received_time = now;
				stage = 2;
			 }
			 if (now - sampaleOf100_recevied_time>TI_first_pulse_registering_delay)// wanting to activate foot as long as no second pule so just up lifting the foot
			 {
			// dac.setVoltage((Active_motor_type_struct.motor_foot_lifting_vale*1000)/1.2,false);
				//return FOOT_LIFTING;
				//digitalWrite(FOOT,HIGH);
				_clickF();
				//stage = 6;
			 }


			 //*************************************************************************************
			 
	}
	else if (stage == 2)// detecting second pulse
	{
			if (CH1_AVRanalogValue>TH_ch1_detection_min_threshold)// second plus stating
			{
				sampaleOf100_recevied_time = now;
				stage = 3;
			}

			 if (now - sampaleOfZero_received_time>TI_second_puls_stating_delay)// if no pulse withing this time we goto initial stage
			 {
				//dac.setVoltage(CALIB_ideal_DAC_value,false);
				 stage =0 ;
				 _stopclickF();
				 //return IDEAL;
				// digitalWrite(TRIM,LOW);
				// digitalWrite(FOOT,LOW);
			 }
			
	}
	else if (stage == 3)
	{
		if (CH1_AVRanalogValue>TH_ch1_trim_detection_threshold)// second pulse intensity check
		{
			sampaleOf900_recevied_time = now;
			if ((sampaleOf900_recevied_time-sampaleOf100_recevied_time<TI_second_pulse_rising_delay)&&(sampaleOf900_recevied_time-sampaleOf100_recevied_time>TI_second_pulse_rising_debounce))
			{
				//dac.setVoltage((Active_motor_type_struct.motor_trimmer_activation_value*1000)/1.2,false);
				//return TRIMMING;
				//digitalWrite(TRIM,HIGH);
				_DclickF();
			}
			
		}
		 if (CH1_AVRanalogValue<TH_ch1_detection_min_threshold)// second  pulse over so go to beginning
		 {
		 //dac.setVoltage(CALIB_ideal_DAC_value,false);
			 stage = 0;
			 _stopclickF();
			 //return IDEAL;
			// digitalWrite(TRIM,LOW);
			 //digitalWrite(FOOT,LOW);
		 }
	}

	if (stage == 6)
	{

		if (CH1_AVRanalogValue<TH_ch1_detection_min_threshold)
		{
			
			stage = 0;
			 _stopclickF();
		}
	}
}

void SmartPaddle :: attach_click(_callbackFunction newF){
		_clickF = newF;
}


void SmartPaddle :: attach_Dclick(_callbackFunction newF){
	_DclickF = newF;
}

void SmartPaddle :: attach_stopclick(_callbackFunction newF){
	_stopclickF = newF;
}