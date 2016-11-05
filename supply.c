#include "state_module.h"
#include "sensor.h"
#include "time.h"
#include "feedback.h"

int supply_timer = -1;

void supply_tick(int now_state){
    if(supply_type && supply_amount && now_state == STATE_SUPPLY) {
	/*	sensor_update(&sensor_hot_weight, sensor_hot_weight.max);
		sensor_update(&sensor_cold_weight, sensor_cold_weight.max);
		sensor_update(&sensor_cup_existence, sensor_cup_existence.max);
		sensor_update(&sensor_coffee_bean_weight, sensor_coffee_bean_weight.max);
		sensor_update(&sensor_coffee_powder_weight, sensor_coffee_powder_weight.max);
*/
        if(mysleep(&supply_timer, 3)) {

        supply_type = 0;
        supply_amount = 0;
        } else {
            mvwprintw(stdscr, 54, 0, "%d %d", supply_type, supply_amount);
        }
    }
}
