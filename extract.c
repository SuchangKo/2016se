#include "extract.h"
#include "state_module.h"
#include "button.h"
#include "sensor.h"
#include "time.h"
#include "feedback.h"

#define On 1
#define Off 0
#define Solenoid_Command(FLAG) (solenoid_flag_water = FLAG)
int solenoid_flag_water = 0;
int solenoid_timer_water = 0;

struct solenoid {
	int element;
	float quantity;
};

struct solenoid solenoid_data;
int temp_flag = 0; // 0 : hot / 1 : cold
int timer = -1; // mysleep_init()

void extract_tick(int now_state) {
	int Count = sensor_get(&sensor_use_count);
	if (now_state == STATE_EXTRACT) {
		if (sensor_get(&sensor_coffee_powder_weight) < 10) {
			new_state(STATE_GRIND);
		} else if (sensor_get(&sensor_coffee_powder_weight) >= 10) {
				if(temp_flag == 0){ //Hot
					if(sensor_get(&sensor_hot_weight) >= 300 && sensor_get(&sensor_cup_existence) == true && Count < 10){
						Solenoid_Command(On);

						if(mysleep(&timer, 3)) {
							Solenoid_Command(Off);
							new_state(STATE_WAIT);
							sensor_sub(&sensor_hot_weight,(concentration+1)*100);
							sensor_sub(&sensor_coffee_powder_weight,10);
							sensor_add(&sensor_use_count,1);
							return;
						}
					}
					if(sensor_get(&sensor_hot_weight) < 300 || sensor_get(&sensor_cup_existence) == false || Count >= 10){
                        if(mysleep(&timer, 2)) {
                                new_state(STATE_WAIT);
                                error_msg = NULL;
								werase(stdscr);
                        } else {
								if(!error_msg) werase(stdscr);
								if(sensor_get(&sensor_hot_weight) < 300){
									error_msg = "물(온)이 부족합니다.";
								}else if(sensor_get(&sensor_cup_existence) == false){
									error_msg = "컵이 부족합니다.";
								}else if(Count >= 10){
									error_msg = "청소가 필요합니다.";
								}
                        }
					}
				}else{ //Cold
					if(sensor_get(&sensor_cold_weight) >= 300 && sensor_get(&sensor_cup_existence) == true && Count < 10){
						Solenoid_Command(On);
						if(mysleep(&timer, 3)) {
							Solenoid_Command(Off);
							new_state(STATE_WAIT);
							sensor_sub(&sensor_cold_weight,(concentration+1)*100);
							sensor_sub(&sensor_coffee_powder_weight,10);
							sensor_add(&sensor_use_count,1);
							return;
						}
							
					}
					if(sensor_get(&sensor_cold_weight) < 300 || sensor_get(&sensor_cup_existence) == false || Count >= 10){
						if(mysleep(&timer, 2)) {
                                new_state(STATE_WAIT);
                                error_msg = NULL;
								werase(stdscr);
                        } else {
								if(!error_msg) werase(stdscr);
								if(sensor_get(&sensor_cold_weight) < 300){
									error_msg = "물(냉)이 부족합니다.";
								}else if(sensor_get(&sensor_cup_existence) == false){
									error_msg = "컵이 부족합니다.";
								}else if(Count >= 10){
									error_msg = "청소가 필요합니다.";
								}
                                
                        }
					}

				}				
			
		}
	}
}
