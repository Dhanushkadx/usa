// sdloader.h

#ifndef _SDLOADER_h
#define _SDLOADER_h

#include "Arduino.h"


typedef enum SD_OPERATION_RESULTS {NO_SD, SD_OK, FILE_NOT_FOUND, ERROR_OPENNING, LOADING_COMPLETE, LOADING_FAIL}; 

typedef enum SPI_PROFILE_CATOGERY{DEFAULT_PROFILE, ARM_RIGHT, ARM_LEFT, NECK_LINE};

typedef enum eMotor_type {JUKY_3ZZ, ISM, PEGASUS_HPV_90};


class sdloader
{
public:
 sdloader();
 
 static SD_OPERATION_RESULTS SD_initilization();
 static SD_OPERATION_RESULTS dump_file(char* file_name, String &free_space);
 static SD_OPERATION_RESULTS saveArry_to_file(char* file_name, unsigned int array[][4], unsigned int length_of_array);

 static SD_OPERATION_RESULTS load_from_sd_file_to_array(char* file_name, unsigned int fillingArry[][4], unsigned int array_length);
 static void resetArray_to_null(unsigned int fillingArry[][4], unsigned int length);
 static void creatFile(char* file_name);
 static SD_OPERATION_RESULTS  format_sd_file_structure();
 static SD_OPERATION_RESULTS loading_profile(unsigned int fillingArry[][4], unsigned int array_length, SPI_PROFILE_CATOGERY profile_type, unsigned int& profile_length);
 static unsigned int getTeachProfile_length(unsigned int filling_array[][4], unsigned int length_of_array);
 static SD_OPERATION_RESULTS initial_sd_state;
 static SD_OPERATION_RESULTS loading_pegasus_HPV_90_single_line(unsigned int &ideal_DAC_value, unsigned int &MAX_RPM_DAC_value ,unsigned int &AuroPilot_DAC_ideal_value, unsigned int &foot_lifting_DAC_value, unsigned int &trimming_DAC_value);
 static SD_OPERATION_RESULTS loading_ISM(unsigned int &ideal_DAC_value, unsigned int &MAX_RPM_DAC_value ,unsigned int &AuroPilot_DAC_ideal_value);
 static SD_OPERATION_RESULTS loading_JUKY_3ZZ(unsigned int &ideal_DAC_value, unsigned int &MAX_RPM_DAC_value ,unsigned int &AuroPilot_DAC_ideal_value);
 static SD_OPERATION_RESULTS load_param_value_from_sd_file(char* file_name, char* para_name, unsigned int &para_value);
 static SD_OPERATION_RESULTS load_param_caption_from_sd_file(char* file_name, char* para_name, char* caption);

 static SD_OPERATION_RESULTS getActive_motor_type_from_sd(eMotor_type &active_motor);
 static SD_OPERATION_RESULTS setActive_motor_type_to_sd(eMotor_type &active_motor);
 static SD_OPERATION_RESULTS loading_machine_para( eMotor_type mc_type, unsigned int &ideal_DAC_value, unsigned int &MAX_RPM_DAC_value ,unsigned int &AuroPilot_DAC_ideal_value,unsigned int &foot_lifting_DAC_value, unsigned int &trimming_DAC_value);
 static SD_OPERATION_RESULTS write_param_value_to_sd(char* file_name, char* para_name, const char* para_value);
 static SD_OPERATION_RESULTS write_to_file_from_string(char* file_name, const char* data);

 // loading foot and trim data
 static SD_OPERATION_RESULTS loading_FT(unsigned int &TH_ch1_detection_min_threshold,unsigned int &TI_first_pulse_registering_delay,unsigned int &TI_second_puls_stating_delay,
										unsigned int &TH_ch1_trim_detection_threshold,unsigned int &TI_second_pulse_rising_delay,unsigned int &TI_second_pulse_rising_debounce);

// loading event data
 static SD_OPERATION_RESULTS loading_event_data_from_SD(char* file_name, unsigned int fillingArry[][2], unsigned int array_length);
 static SD_OPERATION_RESULTS write_event_data_to_SD(char* file_name, unsigned int fillingArry[][2], unsigned int array_length);

// stepper sync data
 static SD_OPERATION_RESULTS loading_stepper_sysnc_para(unsigned int& pulse_width, unsigned int& au_feeder_cutter_act_delay, unsigned int& au_feeder_cutting_delay);
protected:
private:
};



#endif

