/*
 * smartGlow.h
 *
 * Created: 5/23/2017 4:42:14 PM
 *  Author: DhanushkaC
 */ 


#ifndef SMARTGLOW_H_
#define SMARTGLOW_H_

typedef enum eState_smartGlow_states {INIT, TEACHING, AUTO_PILO, RED_FLIKER, UNKNOWN};

class smartGlow {
	
	public:
			smartGlow (int R, int G , int B){
					pin_Red = R;
					pin_Green = G;
					pin_Blue = B;
					
					pinMode(pin_Red,OUTPUT);
					pinMode(pin_Green,OUTPUT);
					pinMode(pin_Blue,OUTPUT);
					
					digitalWrite(pin_Red,LOW);
					digitalWrite(pin_Green,LOW);
					digitalWrite(pin_Blue,LOW);
				
			}
			void set_smartGlow(eState_smartGlow_states _current_mode);
			void set_smartFlickering(unsigned int number_of_flickering);
			
			void smartGlowRun();
			
			void  flickering(unsigned int flickering_number, unsigned int red_level, unsigned int green_level, unsigned int blue_level);
			
			
	private:
			int pin_Green;
			int pin_Red;
			int pin_Blue;
			eState_smartGlow_states current_mode, prev_mode = UNKNOWN;
			eState_smartGlow_states getState_smartGlow();
			void clearLED();
			boolean flickering_en = false; 
			long interval_flickering = 50;//300ms
			unsigned int number_of_flickering =0 , current_number_of_flickering= 0;
			long previousMillis =0;
			boolean ledState = false;
			
	};
	
	
void smartGlow :: set_smartGlow(eState_smartGlow_states _current_mode){
	chMtxLock(&Flags_communication);
	current_mode = _current_mode	;
	chMtxUnlock(&Flags_communication);
};	

void smartGlow :: set_smartFlickering(unsigned int number_of_flickering){
	chMtxLock(&Flags_communication);
	this->number_of_flickering = number_of_flickering;
	flickering_en = true;
	chMtxUnlock(&Flags_communication);
};
	
eState_smartGlow_states smartGlow :: getState_smartGlow(){
	chMtxLock(&Flags_communication);
	eState_smartGlow_states tempState = current_mode;
	chMtxUnlock(&Flags_communication);
	return tempState;
}

void smartGlow :: clearLED(){
	analogWrite(pin_Green, 0);
	analogWrite(pin_Blue, 0);
	analogWrite(pin_Red, 0);
}

void smartGlow :: flickering(unsigned int flickering_number, unsigned int red_level, unsigned int green_level, unsigned int blue_level){
	
	if (!flickering_en)
	{
		return;
	}
	if (current_number_of_flickering>=number_of_flickering)
	{
		flickering_en = false;
		current_number_of_flickering = 0;
	}
	
	unsigned long currentMillis = millis();
	
	if(currentMillis - previousMillis > interval_flickering) {
		// save the last time you blinked the LED
		previousMillis = currentMillis;

		// if the LED is off turn it on and vice-versa:
		if (ledState == false){
			ledState = true;
			clearLED();
			
		}
		else{
			ledState = false;
			analogWrite(pin_Red, red_level);
			analogWrite(pin_Green, green_level);
			analogWrite(pin_Blue, blue_level);
			current_number_of_flickering++;
		}

	}
	
}

void smartGlow :: smartGlowRun(){

		switch (getState_smartGlow())
		{
			case INIT:{
				if (prev_mode!=INIT)
				{	clearLED();
					prev_mode = current_mode;
					analogWrite(pin_Green, 1000);
					analogWrite(pin_Blue, 750);
					Serial.println("LED INIT");
				}
				
			}
			break;
			case TEACHING:{
				if (prev_mode!=TEACHING)
				{
					clearLED();
					prev_mode = current_mode;
					analogWrite(pin_Red, 1000);
					analogWrite(pin_Blue, 750);
					Serial.println("LED TEACH");
				}
				flickering(number_of_flickering,1000,0,750);
				
			}
			break;
			case AUTO_PILO:{
				if (prev_mode!=AUTO_PILO)
				{
					clearLED();
					prev_mode = current_mode;
					analogWrite(pin_Red, 1500);
					Serial.println("LED AUTO");					
				}
				flickering(number_of_flickering,1500,0,0);
				}break;
			
		}
		
	
}


	


#endif /* SMARTGLOW_H_ */