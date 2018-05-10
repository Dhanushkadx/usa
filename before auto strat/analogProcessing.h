/*
 * analogProcessing.h
 *
 * Created: 5/16/2017 10:01:33 AM
 *  Author: DhanushkaC
 */ 


#ifndef ANALOGPROCESSING_H_
#define ANALOGPROCESSING_H_



// Function - running average
long runningAverageCH0(long newSample, long oldSample){
	// Add new sample and subtract old sample from the samples buffer total
	// then return sample average
	sampleBufferTotalCH0 += newSample;  // Add new analog sample
	sampleBufferTotalCH0 -= oldSample;  // Subtract oldest analog sample
	return sampleBufferTotalCH0 / samplesBufferCH0;  // Return average analog sample reading
}

// Function - add and remove analog samples from ring buffer, return oldest sample
// The ring buffer is used to keep track of the oldest sample.
int addSampleCH0(int newSampleCH0) {
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

// Function - running average
long runningAverageCH1(long newSample, long oldSample) {
	// Add new sample and subtract old sample from the samples buffer total
	// then return sample average
	sampleBufferTotalCH1 += newSample;  // Add new analog sample
	sampleBufferTotalCH1 -= oldSample;  // Subtract oldest analog sample
	return sampleBufferTotalCH1 / samplesBufferCH1;  // Return average analog sample reading
}

// Function - add and remove analog samples from ring buffer, return oldest sample
// The ring buffer is used to keep track of the oldest sample.
int addSampleCH1(int newSampleCH1) {
	// Add new analog read sample to the ring buffer and return the oldest analog reading
	int oldSampleCH1;
	if (lastSampleIndexCH1 == samplesBufferCH1 - 1 ) { // Check if end off buffer reached
		oldSampleCH1 = analogSamplesCH1[0];  // Get old analog sample from start of buffer
		analogSamplesCH1[0] = newSampleCH1;  // Add new analog sample to start of buffer
		lastSampleIndexCH1 = 0;  // Record sample index currently working on
		} else {
		lastSampleIndexCH1 ++;  // Move to next index
		oldSampleCH1 = analogSamplesCH1[lastSampleIndexCH1];  // Get old analog sample
		analogSamplesCH1[lastSampleIndexCH1] = newSampleCH1;  // Add new analog sample
	}
	return oldSampleCH1;  // Return old analog sample
}

//*************************
int paddleSensorAnalogDataProcessCH0(){
	long _analogSamplesAverageCH0 = 0; // Running average of the sum of the buffer
	static int analogValue=0;
		//chSysLock();
		analogValue = analogRead(analogPin0);  // Get analog read
		//chSysUnlock();
		// Add new analog reading to buffer and return oldest reading
		int oldestSample = addSampleCH0(analogValue);
		// Get running average, pass the latest and oldest analog sample reading
		_analogSamplesAverageCH0 = runningAverageCH0(analogValue, oldestSample);
		
		chMtxLock(&SerialDataSH_Mutex_CH0);
		AN_CH0_sensor_data_RAW_GLOB = _analogSamplesAverageCH0;
		chMtxUnlock(&SerialDataSH_Mutex_CH0);
		
		//processing analog further
		_analogSamplesAverageCH0 = (_analogSamplesAverageCH0>=CALIBRATE_analogSamplesAverageCH0_adjestment)? 
		_analogSamplesAverageCH0-CALIBRATE_analogSamplesAverageCH0_adjestment : 0;
		
		chMtxLock(&SerialDataSH_Mutex_CH0);
		AN_CH0_sensor_data_AVR_GLOB = _analogSamplesAverageCH0;
		chMtxUnlock(&SerialDataSH_Mutex_CH0);
		
		return _analogSamplesAverageCH0;
}

//*************************
int paddleSensorAnalogDataProcessCH1(){
	static int analogValue=0;
	long _analogSamplesAverageCH1 = 0; // Running average of the sum of the buffer
		//chSysLock();
		analogValue = analogRead(analogPin1);  // Get analog read
		//chSysUnlock();
		// Add new analog reading to buffer and return oldest reading
		int oldestSample = addSampleCH1(analogValue);
		// Get running average, pass the latest and oldest analog sample reading
		_analogSamplesAverageCH1 = runningAverageCH1(analogValue, oldestSample);

		chMtxLock(&SerialDataSH_Mutex_CH1);
		AN_CH1_sensor_data_RAW_GLOB = _analogSamplesAverageCH1;
		chMtxUnlock(&SerialDataSH_Mutex_CH1);
		
		//processing analog further
		_analogSamplesAverageCH1 = (_analogSamplesAverageCH1>=CALIBRATE_analogSamplesAverageCH1_adjestment)?
		_analogSamplesAverageCH1-CALIBRATE_analogSamplesAverageCH1_adjestment : 0;
		
		chMtxLock(&SerialDataSH_Mutex_CH1);
		AN_CH1_sensor_data_AVR_GLOB = _analogSamplesAverageCH1;
		chMtxUnlock(&SerialDataSH_Mutex_CH1);
		
		return _analogSamplesAverageCH1;
}


int getEventofAnalogCH1(long analogSamplesAverage, boolean &r_Ch0, boolean &foot_detection, boolean &trim_detection){
	//Serial.println(analogSamplesAverage);
	if (analogSamplesAverage<350)
	{
		paddle_new_detection_foot = true;
		paddle_new_detection_trim = true;
	}
	if (analogSamplesAverage>200)
	{
		
		r_Ch0 = true;
		
	}
	if ((analogSamplesAverage>200)&&(analogSamplesAverage<350))
	{
		start_ThReceivedTime = millis();
	}
	
	if ((analogSamplesAverage>450)&&(analogSamplesAverage<750))
	{
		chThdSleepMilliseconds(50);
		if ((analogSamplesAverage>450)&&(analogSamplesAverage<950))
		{
			if ((millis() - start_ThReceivedTime<150)&&(paddle_new_detection_foot))
			{
				paddle_new_detection_foot = false;
				firstThReceivedTime=millis();
				foot_detection = true;
				return 0;
			}
			
		}
	}
	if ((analogSamplesAverage>950)&&(analogSamplesAverage<1000))
	{
		
		if (((millis()-start_ThReceivedTime)<2000)&&(paddle_new_detection_trim))
		{
			
			paddle_new_detection_trim= false;
			//trim_detection = true;
			//foot_detection = true;
			return 0;
			
			
		}
		else{return 0;}
	}
	
}

int getEventofAnalogCH0(long analogSamplesAverage){
	
	if ((analogSamplesAverage>350)&&(analogSamplesAverage<950))
	{
		occurenc_control = 1;
		Th_1ReceivedTime=micros();
		//Serial.println(Th_1ReceivedTime);
		//Serial.println("TH_1");
	}
	
	else if ((analogSamplesAverage<350)&&(analogSamplesAverage>150))
	{
		occurenc_control = 1;
		Th_2ReceivedTime=micros();
		//Serial.println(Th_2ReceivedTime);
		//Serial.println("TH_2");
	}
	
	if (((Th_2ReceivedTime-Th_1ReceivedTime)<1100)&&(micros() - Th_2ReceivedTime <900))
	{
		Serial.print("set event");
		Serial.println(4);
		return 4;
	}
	
	if (((Th_2ReceivedTime-Th_1ReceivedTime)<2000)&&(micros() - Th_2ReceivedTime <2000))
	{
		Serial.print("set event");
		Serial.println(5);
		return 5;
	}
	
	return 0;
}


#endif /* ANALOGPROCESSING_H_ */