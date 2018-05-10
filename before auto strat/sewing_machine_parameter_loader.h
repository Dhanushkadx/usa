/*
 * sewing_machine_parameter_loader.h
 *
 * Created: 11/6/2017 10:38:43 PM
 *  Author: dhanushkac
 */ 


#ifndef SEWING_MACHINE_PARAMETER_LOADER_H_
#define SEWING_MACHINE_PARAMETER_LOADER_H_

void load_sewing_machine_parameters(eMotor_type Active_motor_box){

	switch (Active_motor_box)
	{
	case JUKY_3ZZ:{
					Active_motor_type_struct.motor_brand_name = JUKY_3ZZ_struct.motor_brand_name;
					Active_motor_type_struct.motor_model_number = "3ZZ";
					Active_motor_type_struct.motor_ideal_value = 0;
					Active_motor_type_struct.motor_max_RPM_value = 1550;
					Active_motor_type_struct.motor_foot_lifting_vale = 750;
					Active_motor_type_struct.motor_trimmer_activation_value = 800;
					}
		break;
	}
JUKY_3ZZ_struct.motor_brand_name = "JUKY 3ZZ";
JUKY_3ZZ_struct.motor_model_number = "3ZZ";
JUKY_3ZZ_struct.motor_ideal_value = 0;
JUKY_3ZZ_struct.motor_max_RPM_value = 1550;
JUKY_3ZZ_struct.motor_foot_lifting_vale = 750;
JUKY_3ZZ_struct.motor_trimmer_activation_value = 800;

ISM_struct.motor_brand_name = "JUKY 3ZZ";
ISM_struct.motor_model_number = "3ZZ";
ISM_struct.motor_ideal_value = 0;
ISM_struct.motor_max_RPM_value = 1550;
ISM_struct.motor_foot_lifting_vale = 750;
ISM_struct.motor_trimmer_activation_value = 800;

PEGASUS_HPV_90_struct.motor_brand_name = "JUKY 3ZZ";
PEGASUS_HPV_90_struct.motor_model_number = "3ZZ";
PEGASUS_HPV_90_struct.motor_ideal_value = 0;
PEGASUS_HPV_90_struct.motor_max_RPM_value = 1550;
PEGASUS_HPV_90_struct.motor_foot_lifting_vale = 750;
PEGASUS_HPV_90_struct.motor_trimmer_activation_value = 800;

}



#endif /* SEWING_MACHINE_PARAMETER_LOADER_H_ */