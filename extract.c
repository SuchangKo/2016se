#include "extract.h"

void EXTRACTING()
{
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
				Solenoid_Command(Off);
				Put_Hot_Water;
			}else if(button_data(&btn_temperature) == Cold){
				Solenoid_Command(On);
				//Delay By Button Data[Concentration]
				Solenoid_Command(Off);
				Put_Cold_Water;
			}
			//State WAITING
		}
	}	
}