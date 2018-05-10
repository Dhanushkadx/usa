// 
// 
// 

#include "sdloader.h"
#include <SD.h>
#include <SPI.h>

const int chipSelect = BUILTIN_SDCARD;

SD_OPERATION_RESULTS sdloader::initial_sd_state = NO_SD;

SD_OPERATION_RESULTS sdloader :: dump_file(char* file_name, String &free_space){


	File dataFile = SD.open(file_name);

	// if the file is available, write to it:
	if (dataFile) {
		while (dataFile.available()) {

				char onecharacter = (char)dataFile.read();
				//Serial.write(onecharacter);
				free_space += String(onecharacter);
				delayMicroseconds(1);
				//chThdSleepMicroseconds(1);
		}
	
		free_space.trim();
		dataFile.close();
		Serial.println("reading file to be modified<<<<<<<<<<<<<<<<<<<<<<<  " );
		Serial.println(free_space);
		Serial.println(" dump done !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}
	// if the file isn't open, pop up an error:
	else {
		Serial.println("error opening file");
	}

	dataFile.close();

}

 SD_OPERATION_RESULTS sdloader::saveArry_to_file(char* file_name, unsigned int array[][4], unsigned int length_of_array){
	 // check sd
	 //check SD
	 if (sdloader::initial_sd_state == NO_SD)
	 {
		 return NO_SD;
	 }
	Serial.print("saving data to SD as>");
	Serial.print(file_name);
	Serial.println(">saved");
	if (SD.exists(file_name)){
		Serial.println("file already exists.");
		SD.remove(file_name);
		File newfile = SD.open(file_name);
		newfile.close();
	}
	File dataFile = SD.open(file_name, FILE_WRITE);
	// if the file isn't open, pop up an error:
	if(!dataFile) {
		Serial.println("error opening file");
		return ERROR_OPENNING;
	}

	static unsigned int index =0;
	// make a string for assembling the data to log:
	while(length_of_array>=index){

		String dataString = "";
		// read three sensors and append to the string:
		int colum_no = 0;
		for (colum_no = 0; colum_no < 4; colum_no++){
			int colum_value = array[index][colum_no];
			dataString += String(colum_value);
			dataString += (colum_no==3)?"#":",";
		}
		index++;
		// open the file. note that only one file can be open at a time,
		// so you have to close this one before opening another.
		//File dataFile = SD.open(file_name, FILE_WRITE);
		// if the file is available, write to it:
		
		dataFile.println(dataString);
		// print to the serial port too:
		Serial.println(dataString);
		
	}
	index = 0;
	dataFile.close();
	Serial.println("done!");
	return SD_OK;
}


SD_OPERATION_RESULTS sdloader::load_from_sd_file_to_array(char* file_name, unsigned int fillingArry[][4], unsigned int array_length){
	//check SD
	if (sdloader::initial_sd_state == NO_SD)
	{
		return NO_SD;
	}
	// serch for the file
	if (!SD.exists(file_name)) {
		return FILE_NOT_FOUND;
	}
	// re-open the file for reading
	File myFile = SD.open(file_name);
	// if the file isn't open, pop up an error:
	if(!myFile) {
		return ERROR_OPENNING;
	}
	else {
		
		String data_row = "";
		unsigned int index =0;
		// read from the file until there's nothing else in it:
		while (myFile.available()) {
			char onecharacter = (char)myFile.read();
			//Serial.write(onecharacter);
			data_row += onecharacter;
			
			if (data_row.substring(data_row.length()-1) == "#"){// line end
				data_row.replace("#", "");// remove "#"

				String editing_data_row = data_row;// copy to a temporary string for editing
				int first_comma = editing_data_row.indexOf(",");// index of first occurrence of ","
				editing_data_row.remove(first_comma);
				editing_data_row.trim();
				fillingArry[index][0]= (unsigned int)editing_data_row.toInt();
				editing_data_row = "";

				editing_data_row = data_row;
				int second_comma = editing_data_row.indexOf(",", first_comma+1);
				editing_data_row.remove(second_comma);
				editing_data_row.remove(0,first_comma+1);
				editing_data_row.trim();
				fillingArry[index][1]= (unsigned int)editing_data_row.toInt();
				editing_data_row = "";

				editing_data_row = data_row;
				int third_comma = editing_data_row.indexOf(",", second_comma+1);
				editing_data_row.remove(third_comma);
				editing_data_row.remove(0,second_comma+1);
				editing_data_row.trim();
				fillingArry[index][2]= (unsigned int)editing_data_row.toInt();
				editing_data_row = "";

				editing_data_row = data_row;
				int forth_comma = editing_data_row.indexOf(",", third_comma+1);
				editing_data_row.remove(forth_comma);
				editing_data_row.remove(0,third_comma+1);
				editing_data_row.trim();
				fillingArry[index][3]= (unsigned int)editing_data_row.toInt();
				editing_data_row = "";
				
				data_row = "";
				index++;
				if (index >= array_length)
				{
					myFile.close();
					return LOADING_COMPLETE;
				}
			}
		}// available
		// close the file:
		myFile.close();
		return SD_OK;
	}
	
}

void sdloader :: creatFile(char* file_name){
	File myFile = SD.open(file_name, FILE_WRITE);
	myFile.close();
	}
	


void sdloader :: resetArray_to_null(unsigned int fillingArry[][4], unsigned int length){
	
		for (int tempIndex =0; tempIndex<=length-1; tempIndex++)
		{
			fillingArry[tempIndex][0] = 0;
			fillingArry[tempIndex][1] = 0;
			fillingArry[tempIndex][2] = 0;
			fillingArry[tempIndex][3] = 0;
		}
}

SD_OPERATION_RESULTS sdloader :: format_sd_file_structure(){
	if (sdloader::initial_sd_state == NO_SD)
	{
		return NO_SD;
	}

	SD.mkdir("USADATA/SPI/Default");
	SD.mkdir("USADATA/SPI/user_1");
	SD.mkdir("USADATA/SPI/user_2");
	SD.mkdir("USADATA/MASHINE");
	SD.mkdir("USADATA/SYSTEM");
	return SD_OK;
		
}

SD_OPERATION_RESULTS sdloader :: loading_profile(unsigned int fillingArry[][4], unsigned int array_length, SPI_PROFILE_CATOGERY profile_type, unsigned int& profile_length){// calls by main thread
	SD_OPERATION_RESULTS result;
	//sdloader::resetArray_to_null(fillingArry,array_length);
	switch (profile_type)
	{
		case DEFAULT_PROFILE:{
			Serial.print("loading default profile..");
			result = sdloader::load_from_sd_file_to_array("USADATA/SPI/Default/svs_df.txt",fillingArry,array_length);
			profile_length = sdloader :: getTeachProfile_length(fillingArry,array_length);
			if (!result == SD_OK)
			{
				Serial.println(" loading error");
			}
		}break;
		
		case NECK_LINE:{
			Serial.println("loading neck line profile");
			result = sdloader::load_from_sd_file_to_array("USADATA/SPI/Default/svs_1.txt",fillingArry,array_length);
			profile_length = sdloader :: getTeachProfile_length(fillingArry,array_length);
			
			if (!result == SD_OK)
			{
				Serial.println(" loading error");
			}
		} break;
		
		case ARM_LEFT:{
			Serial.println("loading arm left profile");
			result = sdloader::load_from_sd_file_to_array("USADATA/SPI/Default/svs_2.txt",fillingArry,array_length);
			profile_length = sdloader :: getTeachProfile_length(fillingArry,array_length);
			
			if (!result == SD_OK)
			{
				Serial.println(" loading error");
			}
		} break;
		
		case ARM_RIGHT:{
			Serial.println("loading arm right profile");
			result = sdloader::load_from_sd_file_to_array("USADATA/SPI/Default/svs_3.txt",fillingArry,array_length);
			profile_length = sdloader :: getTeachProfile_length(fillingArry,array_length);
			
			if (!result == SD_OK)
			{
				Serial.println(" loading error");
			}
		}break;
	}
	
	return result;
}





unsigned int sdloader :: getTeachProfile_length(unsigned int filling_array[][4], unsigned int length_of_array){
	
	for (int tempIndex=length_of_array-1; tempIndex>=0 ;tempIndex--)
	{
		if (filling_array[tempIndex][0]>0)
		{
			return tempIndex;
		}
	}
	return 0;
} 


SD_OPERATION_RESULTS sdloader :: SD_initilization(){
	// see if the card is present and can be initialized:
	if (!SD.begin(chipSelect)) {
		// don't do anything more:
		sdloader::initial_sd_state = NO_SD;
		return NO_SD;
	}
	sdloader::initial_sd_state = SD_OK;
	return SD_OK;
}



/*
Machine object 
machine.
machine.name=ISM#
machine.ideal_v=2.7#
machine.max_rpm_v=5.0#

unsigned int CALIB_ideal_DAC_value = DEFAULT_CALIB_IDEAL_DAC_VALUE;
unsigned int CALIB_MAX_RPM_DAC_value = DEFAULT_CALIB_MAX_RPM_DAC_VALUE;

unsigned int CALIB_AuroPilot_DAC_ideal_value= DEFAULT_CALIB_IDEAL_AUTO_PILOT;


*/

SD_OPERATION_RESULTS sdloader :: loading_machine_para(eMotor_type mc_type, unsigned int &ideal_DAC_value, unsigned int &MAX_RPM_DAC_value ,unsigned int &AuroPilot_DAC_ideal_value, unsigned int &foot_lifting_DAC_value, unsigned int &trimming_DAC_value){
	SD_OPERATION_RESULTS result;
	
	switch (mc_type)
	{
		case ISM:{
			result = sdloader :: loading_ISM(ideal_DAC_value,MAX_RPM_DAC_value,AuroPilot_DAC_ideal_value);
			
			if (result != LOADING_COMPLETE)
			{
				Serial.println("loading error");
				return LOADING_FAIL;
			}
		}break;
		
		case PEGASUS_HPV_90:{

			result = sdloader :: loading_pegasus_HPV_90_single_line(ideal_DAC_value,MAX_RPM_DAC_value,AuroPilot_DAC_ideal_value,foot_lifting_DAC_value,trimming_DAC_value);
			
			if (result != LOADING_COMPLETE)
			{
				Serial.println(" loading error");
				return LOADING_FAIL;
			}
		} break;
		
		case JUKY_3ZZ:{

			result = sdloader :: loading_JUKY_3ZZ(ideal_DAC_value,MAX_RPM_DAC_value,AuroPilot_DAC_ideal_value);
			
			
			if (result != LOADING_COMPLETE)
			{
				Serial.println(" loading error");
				return LOADING_FAIL;
			}
		} break;
	}
	
	return LOADING_COMPLETE;
}

//************Loading HPV_90_1L Motor
SD_OPERATION_RESULTS sdloader :: loading_pegasus_HPV_90_single_line(unsigned int &ideal_DAC_value, unsigned int &MAX_RPM_DAC_value ,unsigned int &AuroPilot_DAC_ideal_value, unsigned int &foot_lifting_DAC_value, unsigned int &trimming_DAC_value){
	SD_OPERATION_RESULTS result;
	
			Serial.println("loading pegasus_HPV_90_single_line motor data");
			result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/HPV901L.txt", "ideal_dac", ideal_DAC_value);
			if (result !=LOADING_COMPLETE) return LOADING_FAIL;
			result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/HPV901L.txt", "max_rpm_dac", MAX_RPM_DAC_value);
			if (result != LOADING_COMPLETE) return LOADING_FAIL;
			result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/HPV901L.txt", "ideal_ap_dac_value", AuroPilot_DAC_ideal_value);
			if (result != LOADING_COMPLETE) return LOADING_FAIL;
			result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/HPV901L.txt", "foot_dac_value", foot_lifting_DAC_value);
			if (result != LOADING_COMPLETE) return LOADING_FAIL;
			result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/HPV901L.txt", "trim_dac_value", trimming_DAC_value);
			if (result != LOADING_COMPLETE) return LOADING_FAIL;
			Serial.println("loading ok");	
			return LOADING_COMPLETE;
}

SD_OPERATION_RESULTS sdloader :: loading_ISM(unsigned int &ideal_DAC_value, unsigned int &MAX_RPM_DAC_value ,unsigned int &AuroPilot_DAC_ideal_value){
	SD_OPERATION_RESULTS result;
	
	Serial.println("loading ISM motor data");
	result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/ISM.txt", "ideal_dac", ideal_DAC_value);
	if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/ISM.txt", "max_rpm_dac", MAX_RPM_DAC_value);
	if (result != LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/ISM.txt", "ideal_ap_dac_value", AuroPilot_DAC_ideal_value);
	if (result != LOADING_COMPLETE) return LOADING_FAIL;
	Serial.println("loading ok");
	return LOADING_COMPLETE;
}

SD_OPERATION_RESULTS sdloader :: loading_JUKY_3ZZ(unsigned int &ideal_DAC_value, unsigned int &MAX_RPM_DAC_value ,unsigned int &AuroPilot_DAC_ideal_value){
	SD_OPERATION_RESULTS result;
	
	Serial.println("loading JUKY_3ZZ motor data");
	result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/JUKY_3ZZ.txt", "ideal_dac", ideal_DAC_value);
	if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/JUKY_3ZZ.txt", "max_rpm_dac", MAX_RPM_DAC_value);
	if (result != LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/MASHINE/JUKY_3ZZ.txt", "ideal_ap_dac_value", AuroPilot_DAC_ideal_value);
	if (result != LOADING_COMPLETE) return LOADING_FAIL;
	Serial.println("loading ok");
	return LOADING_COMPLETE;
}


SD_OPERATION_RESULTS sdloader :: load_param_value_from_sd_file(char* file_name, char* para_name, unsigned int &para_value){
		String stringOne = para_name;
		
		//check SD
		if (sdloader::initial_sd_state == NO_SD)
		{
			return NO_SD;
		}
		// serch for the file
		if (!SD.exists(file_name)) {
			return FILE_NOT_FOUND;
		}
		// re-open the file for reading
		File myFile = SD.open(file_name);
		// if the file isn't open, pop up an error:
		if(!myFile) {
			return ERROR_OPENNING;
		}
		else {
			Serial.println("Looking for > "+ stringOne);
			String data_row = "";
			unsigned int index =0;
			// read from the file until there's nothing else in it:
			while (myFile.available()) {
				char onecharacter = (char)myFile.read();
				//Serial.write(onecharacter);
				data_row += onecharacter;
				
				if (data_row.substring(data_row.length()-1) == "#"){// line end
					data_row.replace("#", "");// remove "#"
					Serial.print("> " +data_row);
					String editing_data_row = data_row;// copy to a temporary string for editing
					int equel_mark = editing_data_row.indexOf("=");// index of first occurrence of ","
					editing_data_row.remove(0,equel_mark+1);
					editing_data_row.trim();
					para_value =(unsigned int) editing_data_row.toInt();
					//Serial.println(para_value);
					editing_data_row = "";

					editing_data_row = data_row;// get a new copy of original string
					equel_mark = editing_data_row.indexOf("=");// index of first occurrence of ","
					editing_data_row.remove(equel_mark);
					editing_data_row.trim();
					data_row = "";
					
					
					//now we will check what this value is
					if (editing_data_row.equals(stringOne))
					{
						Serial.println(" Mache found");
						Serial.print("the value is > ");
						//Serial.println(editing_data_row);
						Serial.println(para_value);
						myFile.close();
						return LOADING_COMPLETE;
					}
					else{ Serial.println(" not match found");}
				}
			}// available
		
			myFile.close();
			return LOADING_FAIL;
		}
}

SD_OPERATION_RESULTS sdloader :: load_param_caption_from_sd_file(char* file_name, char* para_name, char* caption){
	
	String stringOne = para_name;
	//check SD
	if (sdloader::initial_sd_state == NO_SD)
	{
		return NO_SD;
	}
	// serch for the file
	if (!SD.exists(file_name)) {
		return FILE_NOT_FOUND;
	}
	// re-open the file for reading
	File myFile = SD.open(file_name);
	// if the file isn't open, pop up an error:
	if(!myFile) {
		return ERROR_OPENNING;
	}
	else {
		
		String data_row = "";
		unsigned int index =0;
		// read from the file until there's nothing else in it:
		while (myFile.available()) {
			char onecharacter = (char)myFile.read();
			//Serial.write(onecharacter);
			data_row += onecharacter;
			
			if (data_row.substring(data_row.length()-1) == "#"){// line end
				data_row.replace("#", "");// remove "#"
				Serial.println(data_row);
				String editing_data_row = data_row;// copy to a temporary string for editing
				int equel_mark = editing_data_row.indexOf("=");// index of first occurrence of ","
				editing_data_row.remove(0,equel_mark+1);
				editing_data_row.trim();
				
				strcpy(caption,editing_data_row.c_str());
				//Serial.println(para_value);
				editing_data_row = "";

				editing_data_row = data_row;// get a new copy of original string
				equel_mark = editing_data_row.indexOf("=");// index of first occurrence of ","
				editing_data_row.remove(equel_mark);
				editing_data_row.trim();
				data_row = "";
				
				
				//now we will check what this value is
				if (editing_data_row.equals(stringOne))
				{
					Serial.println("Mached done");
					Serial.print("the value is for: ");
					Serial.println(editing_data_row);
					Serial.println(caption);
					myFile.close();
					return LOADING_COMPLETE;

				}
			}
		}// available
		
		myFile.close();
		return LOADING_FAIL;
	}

}

SD_OPERATION_RESULTS sdloader :: getActive_motor_type_from_sd(  eMotor_type &active_motor){
	char buff[50];
	SD_OPERATION_RESULTS result =  sdloader::load_param_caption_from_sd_file("USADATA/SYSTEM/sys.txt","active_motor",buff);
	if (result == LOADING_FAIL)
	{
		return result;
	}
	Serial.println(buff);
	if (strncmp("jukey_3zz",buff,3)==0)
	{
		active_motor = JUKY_3ZZ;
		Serial.println("active motor type is JUKY_3ZZ");
	} 
	else if (strncmp("pegasus_hpv_90_1l",buff,17)==0)
	{
		active_motor = PEGASUS_HPV_90;
		Serial.println("active motor type is HPV_90_1L");
	}
	else if (strncmp("ism",buff,3)==0)
	{
		active_motor = ISM;
		Serial.println("active motor type is ISM");
	}
	return LOADING_COMPLETE;
}


SD_OPERATION_RESULTS sdloader :: write_param_value_to_sd(char* file_name, char* para_name, const char* para_value){
	//String full_file;
	String data_file;
	
	sdloader :: dump_file(file_name, data_file);
	String stringOne = para_name;
	String para_value_replacing = para_value;
	Serial.println("going to be replaced>>>>>" + stringOne );
	//check SD
	if (sdloader::initial_sd_state == NO_SD)
	{
		Serial.println("NO SD");
		return NO_SD;
	}
	// search for the file
	if (!SD.exists(file_name)) {
		Serial.println("NO FILE");
		return FILE_NOT_FOUND;
		
	}
	// re-open the file for reading
	File myFile = SD.open(file_name);
	// if the file isn't open, pop up an error:
	if(!myFile) {
	Serial.println("ERROR");
		return ERROR_OPENNING;
	}
	else {
		Serial.println("File open successful");
		String master_data_row;
		master_data_row.reserve(50);
		master_data_row="";
		unsigned int index =0;
		// read from the file until there's nothing else in it:
		while (myFile.available()) {
			char onecharacter = (char)myFile.read();
			//Serial.write(onecharacter);
			master_data_row += onecharacter;
			
			if (master_data_row.substring(master_data_row.length()-1) == "#"){// line end
				master_data_row.replace("#", "");// remove "#"
				Serial.print("last read line >>");
				Serial.println(master_data_row);
				String editing_data_row = master_data_row;// copy to a temporary string for editing
				int equel_mark = editing_data_row.indexOf("=");// index of first occurrence of ","
				editing_data_row.remove(0,equel_mark+1);
				editing_data_row.trim();
				String para_value_to_be_replaced = editing_data_row;// if mached this can be replaced 
				//Serial.println(para_value);
				editing_data_row = "";

				editing_data_row = master_data_row;// get a new copy of original string
				equel_mark = editing_data_row.indexOf("=");// index of first occurrence of "="
				editing_data_row.remove(equel_mark);
				editing_data_row.trim();

				String backup_of_data_row = master_data_row;
				master_data_row = "";
				
				Serial.print("value caption : ");
				Serial.println(editing_data_row);
				//now we will check what this value is
				if (editing_data_row.equals(stringOne))
				{	myFile.close();
					String Original_data_row = backup_of_data_row;
					
					backup_of_data_row.replace(para_value_to_be_replaced, para_value_replacing);
					

					Serial.println("Mached done");
					Serial.println("Original"+ Original_data_row);
					Serial.println("Modified" + backup_of_data_row);
					
						
					//sdloader :: dump_file(file_name, full_file);
					
					data_file.replace(Original_data_row,backup_of_data_row);
					
					SD_OPERATION_RESULTS result = sdloader :: write_to_file_from_string(file_name , data_file.c_str());

					return result;

				}
			}
		}// available
		Serial.println("closing file");
		myFile.close();
		return LOADING_FAIL;
	}

}


SD_OPERATION_RESULTS sdloader :: write_to_file_from_string(char* file_name, const char* _data){
	String dataString = String(_data);
	Serial.println("writing data>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	Serial.println(_data);

	Serial.println("done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111");
	//return LOADING_FAIL;
 // check sd
 //check SD
 if (sdloader::initial_sd_state == NO_SD)
 {
	 return NO_SD;
 }
 Serial.print("saving data to SD as>");
 Serial.print(file_name);
 Serial.println(">saving");
 if (SD.exists(file_name)){
	 Serial.println("file already exists.");
	 SD.remove(file_name);
	 File newfile = SD.open(file_name);
	 newfile.close();
 }
 File dataFile = SD.open(file_name, FILE_WRITE);
 // if the file isn't open, pop up an error:
 if(!dataFile) {
	 Serial.println("error opening file");
	 return ERROR_OPENNING;
 }
	 
	 dataFile.println(_data); 

 dataFile.close();
 Serial.println("done!");
 return SD_OK;
}

SD_OPERATION_RESULTS sdloader :: loading_FT(unsigned int &TH_ch1_detection_min_threshold,unsigned int &TI_first_pulse_registering_delay,unsigned int &TI_second_puls_stating_delay,
unsigned int &TH_ch1_trim_detection_threshold,unsigned int &TI_second_pulse_rising_delay,unsigned int &TI_second_pulse_rising_debounce){

	Serial.println("loading foot and trim data");
	SD_OPERATION_RESULTS result;
	result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/FT_data.txt", "TH_ch1_detection_min_threshold", TH_ch1_detection_min_threshold);
	if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/FT_data.txt", "TI_first_pulse_registering_delay", TI_first_pulse_registering_delay);
	if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/FT_data.txt", "TI_second_puls_stating_delay", TI_second_puls_stating_delay);
	if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/FT_data.txt", "TH_ch1_trim_detection_threshold", TH_ch1_trim_detection_threshold);
	if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/FT_data.txt", "TI_second_pulse_rising_delay", TI_second_pulse_rising_delay);
	if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/FT_data.txt", "TI_second_pulse_rising_debounce", TI_second_pulse_rising_debounce);
	return LOADING_COMPLETE;

}

 SD_OPERATION_RESULTS sdloader :: loading_event_data_from_SD(char* file_name, unsigned int fillingArry[][2], unsigned int array_length){
 //check SD
 if (sdloader::initial_sd_state == NO_SD)
 {
	 return NO_SD;
 }
 // serch for the file
 if (!SD.exists(file_name)) {
	 return FILE_NOT_FOUND;
 }
 // re-open the file for reading
 File myFile = SD.open(file_name);
 // if the file isn't open, pop up an error:
 if(!myFile) {
	 return ERROR_OPENNING;
 }
 else {
	 
	 String data_row = "";
	 unsigned int index =0;
	 // read from the file until there's nothing else in it:
	 while (myFile.available()) {
		 char onecharacter = (char)myFile.read();
		 //Serial.write(onecharacter);
		 data_row += onecharacter;
		 
		 if (data_row.substring(data_row.length()-1) == "#"){// line end
			 data_row.replace("#", "");// remove "#"

			 String editing_data_row = data_row;// copy to a temporary string for editing
			 int first_comma = editing_data_row.indexOf(",");// index of first occurrence of ","
			 editing_data_row.remove(first_comma);
			 editing_data_row.trim();
			 fillingArry[index][0]= (unsigned int)editing_data_row.toInt();
			 editing_data_row = "";

			 editing_data_row = data_row;
			 int second_comma = editing_data_row.indexOf(",", first_comma+1);
			 editing_data_row.remove(second_comma);
			 editing_data_row.remove(0,first_comma+1);
			 editing_data_row.trim();
			 fillingArry[index][1]= (unsigned int)editing_data_row.toInt();
			 editing_data_row = "";
			 
			 data_row = "";
			 index++;
			 if (index >= array_length)
			 {
				 myFile.close();
				 return LOADING_COMPLETE;
			 }
		 }
	 }// available
	 // close the file:
	 myFile.close();
	 return SD_OK;
 }
 
 }

 SD_OPERATION_RESULTS sdloader :: write_event_data_to_SD(char* file_name, unsigned int fillingArry[][2], unsigned int array_length){
	 // check sd
	 //check SD
	 if (sdloader::initial_sd_state == NO_SD)
	 {
		 return NO_SD;
	 }
	 Serial.print("saving data to SD as>");
	 Serial.print(file_name);
	 Serial.println(">saved");
	 if (SD.exists(file_name)){
		 Serial.println("file already exists.");
		 SD.remove(file_name);
		 File newfile = SD.open(file_name);
		 newfile.close();
	 }
	 File dataFile = SD.open(file_name, FILE_WRITE);
	 // if the file isn't open, pop up an error:
	 if(!dataFile) {
		 Serial.println("error opening file");
		 return ERROR_OPENNING;
	 }

	 static unsigned int index =0;
	 // make a string for assembling the data to log:
	 while(array_length>=index){

		 String dataString = "";
		 // read three sensors and append to the string:
		 int colum_no = 0;
		 for (colum_no = 0; colum_no < 2; colum_no++){
			 int colum_value = fillingArry[index][colum_no];
			 dataString += String(colum_value);
			 dataString += (colum_no==1)?"#":",";
		 }
		 index++;
		 // open the file. note that only one file can be open at a time,
		 // so you have to close this one before opening another.
		 //File dataFile = SD.open(file_name, FILE_WRITE);
		 // if the file is available, write to it:
		 
		 dataFile.println(dataString);
		 // print to the serial port too:
		 Serial.println(dataString);
		 
	 }
	 index = 0;
	 dataFile.close();
	 Serial.println("done!");
	 return SD_OK;
 }


 SD_OPERATION_RESULTS sdloader :: loading_stepper_sysnc_para(unsigned int& pulse_duration, unsigned int& au_feeder_cutter_act_delay, unsigned int& au_feeder_cutting_delay){

	 Serial.println("loading stepper sync data");
	 SD_OPERATION_RESULTS result;
	 result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.TXT", "pulse_width", pulse_duration);
	 if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	 result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.TXT", "au_feeder_cutter_act_delay", au_feeder_cutter_act_delay);
	 if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	 result = sdloader :: load_param_value_from_sd_file("USADATA/SYSTEM/SYSV.TXT", "au_feeder_cutting_delay", au_feeder_cutting_delay);
	 if (result !=LOADING_COMPLETE) return LOADING_FAIL;
	 return LOADING_COMPLETE;

 }