/*
 * eepromAccess.cpp
 *
 * Created: 5/17/2017 10:15:01 AM
 *  Author: DhanushkaC
 */ 
#include "eepromData.h"
eepromData::eepromData(char* name, int parameter_id, int minValue, int currentValue, int maxValue, unsigned int EEaddress){
	this->__name  = name;
	this->__parameter_id =parameter_id;
	this->__minValue = maxValue;
	this->__currentValue = maxValue;
	this->__maxValue = maxValue;
	this->__EEaddress = __nextEEaddress;
	__nextEEaddress += sizeof(unsigned int);
	
	};
	
int eepromData:: getCurrentValue(){
	return __currentValue;
	
}

void eepromData::setCurrentValue(unsigned int newValue){
	__currentValue = newValue;
}	

