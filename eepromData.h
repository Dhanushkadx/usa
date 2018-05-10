/*
 * eepromAccess.h
 *
 * Created: 5/17/2017 10:15:17 AM
 *  Author: DhanushkaC
 */ 


#ifndef EEPROMACCESS_H_
#define EEPROMACCESS_H_

class eepromData
{
public:
		eepromData(char* name, int parameter_id, int minValue, int defaultValue, int maxValue, unsigned int EEaddress);
		int getCurrentValue();
		void setCurrentValue(unsigned int newValue);
		//void savetoEEPROM();
		//void static fnParameters_Initialization();
		
protected:
		
private:
	

	 const char* __name;
	 int __minValue;
	 int __currentValue;
	 int __maxValue;
	 unsigned int __EEaddress; 
	 int __parameter_id;
	 unsigned int __nextEEaddress;
		
};



#endif /* EEPROMACCESS_H_ */