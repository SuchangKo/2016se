#include "extract.h"
#include "state_module.h"
#include "button.h"
#include "sensor.h"
#include "time.h"

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

int timer = -1; // mysleep_init()

void extract_tick(int now_state) {
	int Count = sensor_get(&sensor_use_count);
	if (now_state == STATE_EXTRACT) {
		if (sensor_get(&sensor_coffee_powder_weight) < 10) {
			new_state(STATE_GRIND);
		} else if (sensor_get(&sensor_coffee_powder_weight) >= 10) {
			{
				if(btn_is_pressed(&btn_temperature) == 0){ //Hot
					if(sensor_get(&sensor_hot_weight) >= 300 && sensor_get(&sensor_cup_existence) == true && Count < 10){
						printf("NORMAL\n");
						Solenoid_Command(On);

						if(mysleep(&timer, 3)) {
							Solenoid_Command(Off);
							printf("HOT COFFEE\n");
							new_state(STATE_WAIT);
						}
						
						
						
					}
					if(sensor_get(&sensor_hot_weight) < 300 || sensor_get(&sensor_cup_existence) == false || Count >= 10){
						printf("ERROR_HOT\n");
						new_state(STATE_WAIT);
					}
				}else{ //Cold
					if(sensor_get(&sensor_cold_weight) >= 300 && sensor_get(&sensor_cup_existence) == true && Count < 10){
						printf("NORMAL\n");	
						Solenoid_Command(On);
						if(mysleep(&timer, 3)) {
							Solenoid_Command(Off);
							printf("COLD COFFEE\n");
							new_state(STATE_WAIT);
						}
							
					}
					if(sensor_get(&sensor_cold_weight) < 300 || sensor_get(&sensor_cup_existence) == false || Count >= 10){
						printf("ERROR_COLD\n");	
						new_state(STATE_WAIT);
					}

				}				
			}
		}
	}
}
