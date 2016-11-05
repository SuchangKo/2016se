#include "grind.h"

void GRINDING()
{
	if(state == GRINDING){
		sensor_Data[Bean] < 10
			Fail
		sensor_Data[Bean] >= 10
			sensor_coffee_powder_weight = 100;
			grind 5초 하고 무조건 extract로 state변경
	}
}