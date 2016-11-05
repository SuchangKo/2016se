#include "state_module.h"
#include "sensor.h"
void supply_tick(int now_state){
	if(now_state == STATE_SUPPLY){
		sensor_update(&sensor_hot_weight, sensor_hot_weight.max);
		sensor_update(&sensor_cold_weight, sensor_cold_weight.max);
		sensor_update(&sensor_cup_existence, sensor_cup_existence.max);
		sensor_update(&sensor_coffee_bean_weight, sensor_coffee_bean_weight.max);
		sensor_update(&sensor_coffee_powder_weight, sensor_coffee_powder_weight.max);

	}
}
