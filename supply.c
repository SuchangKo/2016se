#include "state_module.h"
#include "sensor.h"
#include "time.h"
#include "feedback.h"
#include <string.h>
#include <stdlib.h>

int supply_timer = -1;
extern char input_buf[];

void supply_tick(int now_state){
    if(now_state == STATE_SUPPLY) {
        if(input_buf[strlen(input_buf) - 1] == '\n') {
            if(supply_type == 0) {
                supply_type = input_buf[0] - 0x30;

                // invalid input
                if(!(strlen(input_buf) == 2 && 1 <= supply_type && supply_type <= 4)) {
                    supply_type = 0;
                }
            }
            else if(supply_amount == 0) {
                supply_amount = atoi(input_buf);
            }

            input_buf[0] = '\0';
            werase(stdscr);
        }
            
        if(supply_type && supply_amount) {
	/*	sensor_update(&sensor_hot_weight, sensor_hot_weight.max);
		sensor_update(&sensor_cold_weight, sensor_cold_weight.max);
		sensor_update(&sensor_cup_existence, sensor_cup_existence.max);
		sensor_update(&sensor_coffee_bean_weight, sensor_coffee_bean_weight.max);
		sensor_update(&sensor_coffee_powder_weight, sensor_coffee_powder_weight.max);
*/
            if(mysleep(&supply_timer, 3)) {
                new_state(STATE_WAIT);
                switch(supply_type){
                    case 1:
                        sensor_add(&sensor_coffee_bean_weight,supply_amount);
                        break;
                    case 2:
                        sensor_add(&sensor_coffee_powder_weight,supply_amount);
                        break;
                    case 3:
                        sensor_add(&sensor_hot_weight,supply_amount);
                        break;
                    case 4:
                        sensor_add(&sensor_cold_weight,supply_amount);
                        break;
                }
                supply_type = 0;
                supply_amount = 0;
            } else {
                mvwprintw(stdscr, 54, 0, "supply_type: %d, supply_amount: %d", supply_type, supply_amount);
            }
        }
    }
}
