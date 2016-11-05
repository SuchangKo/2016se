#include "extract.h"

#define On 1
#define Off 0
#define Solenoid_Command(int flag) (solenoid_flag = flag)
int solenoid_flag = 0;
int solenoid_timer = 0;

struct solenoid {
	int element;
	float quantity; 
};


void EXTRACTING()
{
	if(btn['extract'] == 1){
		0 
		time = 0;
		soleoid during

	}
	if(sensor_get(&sensor_coffee_powder_weight) < 10)
	{
		state = GRINDING;
	}
	else if(sensor_get(&sensor_coffee_powder_weight) >= 10){
	{	
		if(sensor_get(&sensor_water) < 300 || sensor_get(&sensor_cup_existence) == false || Count >= 10) //new sensor_water
		{
			//ERROR
			Extract_Condition = Off;
		}
		if(sensor_get(&sensor_water) >= 300 || sensor_get(&sensor_cup_existence) == true || Count < 10) //new sensor_water
		{
			//Put Powder & Water By Button Data[Concentration]
			//Decide Temperature
			if(button_data(&btn_temperature) == Hot)
			{
				Solenoid_Command(On);
				//Delay By Button Data[Concentration]
			}else if(button_data(&btn_temperature) == Cold){
				Solenoid_Command(On);
				//Delay By Button Data[Concentration]
			}
		}
	}
	if(solenoid_flag == 1)
	{
		if(solenoid_timer >= solenoid.quantity) //Target_time Setting
		{
			Solenoid_Command(Off);
		}else{
			solenoid_timer++;
		}
	}
	
}