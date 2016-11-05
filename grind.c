#include "grind.h"
#include "state.h"
#include "sensor.h"

#define On 1
#define Off 0
#define Solenoid_Command(FLAG) (solenoid_flag = FLAG)

int solenoid_flag = 0;
int solenoid_timer = 0;

struct solenoid {
	int element;
	float quantity; 
};

struct solenoid solenoid_data;
/*
struct grind_data{
	float quantity;
	bool is_exist; 
};
*/

void grinding_tick(int now_state)
{
	if(now_state == STATE_GRIND){
		if (sensor_get(&sensor_coffee_bean_weight) < 10)
		{
			printf("Fail");
		}
		else if(sensor_get(&sensor_coffee_bean_weight) >= 10)
		{
			Solenoid_Command(On);
		}
		if(solenoid_flag == 1)
		{
			if(solenoid_timer >= solenoid_data.quantity) //Target_time Setting
			{
				sensor_sub(&sensor_coffee_bean_weight,5); // 소모되는 원두의 양	
				sensor_add(&sensor_coffee_powder_weight,5);
				Solenoid_Command(Off);
				new_state(STATE_EXTRACT);
			}else{
				solenoid_timer++;
			}
		}
	}
}
