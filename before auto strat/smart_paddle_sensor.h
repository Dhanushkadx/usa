// smart_paddle_sensor.h

#ifndef _SMART_PADDLE_SENSOR_h
#define _SMART_PADDLE_SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

extern "C" {
			typedef void (*_callbackFunction)(void);
};

#include "data_types.h"
#define FOOT 7
#define TRIM 6
//Calibrations


// analog channel offsets
#define DEAFULT_AN_CH0_OFFSET 550
#define DEAFULT_AN_CH1_OFFSET 0



#define DEFAULT_CH0_AN_LOW_VALUE 00
#define DEFAULT_CH0_AN_HIGH_VALUE 475

#define DEFAULT_CH1_AN_LOW_VALUE 00
#define DEFAULT_CH1_AN_HIGH_VALUE 475











class SmartPaddle
	{
	public:
			SmartPaddle(int channel_1);
			
			
			void attach_click(_callbackFunction newF);
			void attach_Dclick(_callbackFunction newF);
			void attach_stopclick(_callbackFunction newF);

			unsigned int getSensor_value_to_DAC(long analogSamplesAverageCH0);
	
			void process_paddleSensorAnalogDataCH0(long &_analogSamples_RAW_CH0, long &_analogSamplesAverageCH0, unsigned long &now);
			
			
			void set_CH0_AN_MIN_value(int value);			
			void set_CH0_AN_MAX_value(int value);
			
			
			void set_ch0_to_dac_limits(unsigned int high_limit, unsigned int low_limit);
			
			int get_CH0_AN_MIN_value();
			int get_CH0_AN_MAX_value();

			// set new event parameters
			void setEvent_para(unsigned int TH_ch1_detection_min_threshold,unsigned int TI_first_pulse_registering_delay,unsigned int TI_second_puls_stating_delay,unsigned int TH_ch1_trim_detection_threshold,unsigned int TI_second_pulse_rising_delay,unsigned int TI_second_pulse_rising_debounce);
			ePADDLE_EVENTS event_detecting(unsigned int CH1_AVRanalogValue, unsigned long now);
	
	private:
	long runningAverageCH0(long newSample, long oldSample);
	int addSampleCH0(int newSampleCH0);
	
	
	unsigned int CH0_RAWAnalogValue_SH ;
	unsigned int analogSamplesAverageCH0_SH ;
	int analogPin0;
	//Calibrations
	int CALIBRATE_analogSamplesAverageCH0_offset_to_make_it_zero = DEAFULT_AN_CH0_OFFSET;
	


	int analogLowCH0 = DEFAULT_CH0_AN_LOW_VALUE; 

	// High end of the test load values
	int analogHighCH0 =  DEFAULT_CH0_AN_HIGH_VALUE;
	

   
	unsigned int CALIBRATE_analogSamplesAverageCH0ToDAC_map_LOW_value;
	unsigned int CALIBRATE_analogSamplesAverageCH0ToDAC_map_HIGH_value;
	
	
	// Values for the analog sample buffer for running average to smooth analogue reads
	int samplesBufferCH0 = 10; // Should be the same as the number of samples
	int analogSamplesCH0[10] = {0}; // Number of analog samples to average and set to 0
	int lastSampleIndexCH0 = 0; // Last analog sample
	long sampleBufferTotalCH0 = 0; // The sum of all the samples held in the buffer


	// event
	unsigned int stage = 0;
	unsigned int TH_ch1_detection_min_threshold=100;
	unsigned int TI_first_pulse_registering_delay=200;
	unsigned int TI_second_puls_stating_delay=200;
	unsigned int TH_ch1_trim_detection_threshold=900;
	unsigned int TI_second_pulse_rising_delay=500;
	unsigned int TI_second_pulse_rising_debounce=250;

	unsigned int sampaleOfZero_received_time, sampaleOf100_recevied_time, sampaleOf900_recevied_time;
	_callbackFunction _clickF;
	_callbackFunction _DclickF;_callbackFunction _stopclickF;
	
	
	};
	
#endif

