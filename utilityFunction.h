// utilityFunction.h

#ifndef _UTILITYFUNCTION_h
#define _UTILITYFUNCTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define ACTIVATE_CUTTER_NUMERICAL_VALUE_OF_REG 50
#define DEACTIVATE_CUTTER_NUMERICAL_VALUE_OF_REG 5
#define ACTIVATE_CUTTER_WITH_CREAZING_NUMERICAL_VALUE_OF_REG 51
#define DEACTIVATE_CUTTER_WITH_CREAZING_NUMERICAL_VALUE_OF_REG 6

typedef enum CUTTER_STATES{ACTIVE, DEACTIVE, NO_CHENGE, UNK};
	

class AutoCutter
{
public:
		AutoCutter(int connected_pin);
			void Activate();
			void Deactivate();
			CUTTER_STATES getState();
			void setRegister_Cutter(unsigned int array[][4], unsigned int array_index);
			CUTTER_STATES getRegister(unsigned int array[][4], unsigned int array_index);
			boolean getCutterActivation_request();
			void setCutterActivation_request(boolean _xstate);
			friend void setCutterActivation_request_LCD(boolean _xstate);
			friend void setState_from_LCD(CUTTER_STATES _xstate);
			
			static CUTTER_STATES State_cutter;
			static boolean CutterActivation_request;
protected:
private:
		int connected_pin;
		
		
	
		
		
};

class Utility
{
public:
Utility();
static void count_spi(boolean &spi_flag);
static unsigned int getCurrentSPI_count();
static void setCurrentSPI_count(unsigned int newValue);


// friend void mechanical_sw_mode_session_chenge(SPI_PROFILE_CATOGERY spi_vs_speed_active_profile ,SPI_PROFILE_CATOGERY &spi_vs_speed_profile);
protected:
private:
	static unsigned int spi_count;
	
};
#endif

