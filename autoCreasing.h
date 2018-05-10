/*
 * autoCreasing.h
 *
 * Created: 5/24/2017 5:14:27 PM
 *  Author: DhanushkaC
 */ 


#ifndef AUTOCREASING_H_
#define AUTOCREASING_H_


class autoCreasing
{
public:
		autoCreasing(){
			
			pinMode(CREASING_OUT,OUTPUT);
			digitalWrite(CREASING_OUT,LOW);
			pinMode(creasingIn,INPUT_PULLUP);
			creasing_EN = true;
		}
		
		boolean getSPIcreasingDetect();
		void setSPIcreasingDetect(boolean _xstate);
		void creasingPulseOut();
		boolean poolingCreasingSwitch();
		friend unsigned int getntotalCreasingPointstoLCD();
		void setcurrentCreasingPoints(unsigned int _currentCreasingPoint);
		friend unsigned int getcurrentCreasingPoints();
		void advance_numberOfCreasing();
		void clrCreasingPoints();
		
		static unsigned int currentCreasingPoint;
		
protected:
private:
		static unsigned int ntotal_CreasingPoints;
	
		boolean creasing_EN;
		boolean SPI_creasing_detected = false;
		
		// Variables will change:
		int buttonPushCounter = 0;   // counter for the number of button presses
		int buttonState = 0;         // current state of the button
		int lastButtonState = 1;     // previous state of the button

		
		void setntotalCreasingPoints(unsigned int _ntotal_CreasingPoints);
		
		
		
		
		void setCreasingsEN_switch(boolean creasing_EN);
		boolean getCreasingEN_switch();
};

unsigned int autoCreasing :: ntotal_CreasingPoints = 0;
unsigned int autoCreasing :: currentCreasingPoint = 0;

unsigned int getntotalCreasingPointstoLCD(){ 
	chMtxLock(&Event_creasing);
	unsigned int temp_cresing = autoCreasing :: ntotal_CreasingPoints; 
	chMtxUnlock(&Event_creasing);
	return temp_cresing;
	
	}
unsigned int getcurrentCreasingPoints(){
	chMtxLock(&Event_creasing);
	unsigned int temp_creasing = autoCreasing :: currentCreasingPoint;
	chMtxUnlock(&Event_creasing);
	return temp_creasing;
}

void autoCreasing :: setcurrentCreasingPoints(unsigned int _currentCreasingPoint){
	chMtxLock(&Event_creasing);
	autoCreasing :: currentCreasingPoint = _currentCreasingPoint;
	chMtxUnlock(&Event_creasing);
}


void autoCreasing :: setntotalCreasingPoints(unsigned int _ntotal_CreasingPoints){
	chMtxLock(&Event_creasing);
	ntotal_CreasingPoints = _ntotal_CreasingPoints;
	chMtxUnlock(&Event_creasing);
}

void autoCreasing :: advance_numberOfCreasing(){
	chMtxLock(&Event_creasing);
	ntotal_CreasingPoints++;
	chMtxUnlock(&Event_creasing);
}


void autoCreasing :: setCreasingsEN_switch(boolean creasing_EN){
	this->creasing_EN = creasing_EN;
}

boolean autoCreasing :: getCreasingEN_switch(){
	return creasing_EN;
}

boolean autoCreasing :: getSPIcreasingDetect(){
	chMtxLock(&Flags_communication);
	if (SPI_creasing_detected)
	{
		chMtxUnlock(&Flags_communication);
		return true;
	}
	chMtxUnlock(&Flags_communication);
	return false;
}

void autoCreasing :: setSPIcreasingDetect(boolean _xstate){
	chMtxLock(&Flags_communication);
	SPI_creasing_detected=_xstate;
	chMtxUnlock(&Flags_communication);
}

void autoCreasing :: creasingPulseOut(){
	digitalWrite(CREASING_OUT,HIGH);	
	chThdSleepMilliseconds(10);
	digitalWrite(CREASING_OUT,LOW);
}

void autoCreasing :: clrCreasingPoints(){
	ntotal_CreasingPoints =0;
	currentCreasingPoint =0;
	}
	

boolean autoCreasing :: poolingCreasingSwitch(){
	// read the pushbutton input pin
	buttonState = digitalRead(creasingIn);
	boolean result = false;
	
	// compare the buttonState to its previous state
	if (buttonState != lastButtonState) {
		// if the state has changed, increment the counter
		if (buttonState == LOW) {
			// if the current state is HIGH then the button
			// wend from off to on:
			result = true;
			
			} else {
			// if the current state is LOW then the button
			// wend from on to off:
			result = false;
		}
		// Delay a little bit to avoid bouncing
		chThdSleepMilliseconds(50);
	}
	// save the current state as the last state,
	//for next time through the loop
	lastButtonState = buttonState;
	
	return result;
	
}
#endif /* AUTOCREASING_H_ */