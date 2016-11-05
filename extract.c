#include "extract.h"
#include "state.h"
#include "button.h"
#include "sensor.h"

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

int Count = 0; //use count


void extract_tick(int now_state) {
	if (now_state == STATE_EXTRACT) {
		/*
		if (btn_is_pressed() == 1) {
			solenoid_timer_water = 0;
			//solenoid_data =
		}
		*/
		if (sensor_get(&sensor_coffee_powder_weight) < 10) {
			now_state = STATE_GRIND;
		} else if (sensor_get(&sensor_coffee_powder_weight) >= 10) {
			{
				if (sensor_get(&sensor_water_weight) < 300
						|| sensor_get(&sensor_cup_existence) == false
						|| Count >= 10) //new sensor_water
								{
					//ERROR
					//Extract_Condition = Off;
				}
				if (sensor_get(&sensor_water_weight) >= 300
						|| sensor_get(&sensor_cup_existence) == true
						|| Count < 10) //new sensor_water
								{
					//Put Powder & Water By Button Data[Concentration]
					//Decide Temperature
					if (btn_is_pressed(&btn_temperature) == 0) {
						Solenoid_Command(On);
						//Delay By Button Data[Concentration]
					} else if (btn_is_pressed(&btn_temperature) == 1) {
						Solenoid_Command(On);
						//Delay By Button Data[Concentration]
					}
				}
			}
			if (solenoid_flag_water == 1) {
				if (solenoid_timer_water >= solenoid_data.quantity) //Target_time Setting
						{
					Solenoid_Command(Off);
				} else {
					solenoid_timer_water++;
				}
			}
		}
	}
}
