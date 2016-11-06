#include "clean.h"
#include "state_module.h"
#include "sensor.h"
#include "time.h"
#include "feedback.h"

int clean_timer = -1;
void clean_tick(int now_state)
{
	if(now_state == STATE_CLEAN){
		if(sensor_get(&sensor_hot_weight) >= 500){
			if(mysleep(&clean_timer, 3)) {
				sensor_sub(&sensor_hot_weight,500); // 소모되는 물의 양	
				new_state(STATE_WAIT);
			}
		}else if(sensor_get(&sensor_cold_weight) >= 500){
			if(mysleep(&clean_timer, 3)) {
				sensor_sub(&sensor_cold_weight,500); // 소모되는 물의 양	
				new_state(STATE_WAIT);
			}
		}else{
			if(mysleep(&clean_timer, 2)) {
				new_state(STATE_WAIT);
				error_msg = NULL;
				werase(stdscr);
			}else{
				if(!error_msg) werase(stdscr);
				error_msg = "물이 부족합니다.";	
			} 
		}
	}
}
