#include "grind.h"
#include "state_module.h"
#include "sensor.h"
#include "time.h"
#include "feedback.h"

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

int grind_timer = -1;
void grind_tick(int now_state)
{
	if(now_state == STATE_GRIND){
		if (sensor_get(&sensor_coffee_bean_weight) < 10)
		{
			if(mysleep(&grind_timer, 1)) {
				new_state(STATE_WAIT);
				error_msg = NULL;
				werase(stdscr);
			} else {
				if(!error_msg) werase(stdscr);
				error_msg = "원두가 부족합니다.";
			}
		}
		else if(sensor_get(&sensor_coffee_bean_weight) >= 10)
		{
			Solenoid_Command(On);
			if(mysleep(&grind_timer, 3)) {
				sensor_sub(&sensor_coffee_bean_weight,10); // 소모되는 원두의 양	
				sensor_add(&sensor_coffee_powder_weight,10);
				Solenoid_Command(Off);
				new_state(STATE_EXTRACT);
			}
		}	
	}
}
