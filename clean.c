#include "clean.h"
#include "state_module.h"
#include "sensor.h"
#include "time.h"

int clean_timer = -1;
void clean_tick(int now_state)
{
	if(now_state == STATE_CLEAN){
		if(sensor_get(&sensor_hot_weight) > 500){
			if(mysleep(&clean_timer, 3)) {
				sensor_sub(&sensor_hot_weight,500); // 소모되는 물의 양	
				new_state(STATE_WAIT);
			}
		}else if(sensor_get(&sensor_cold_weight)){
			if(mysleep(&clean_timer, 3)) {
				sensor_sub(&sensor_cold_weight,500); // 소모되는 물의 양	
				new_state(STATE_WAIT);
			}
		}else{
			// Nothing to do. Water > 500
		}
	}
}
