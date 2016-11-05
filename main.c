#include "button.h"
#include "sensor.h"
#include "time.h"

#include "grind.h"
#include "extract.h"
#include "clean.h"
#include "state_module.h"
#include "wait.h"
#include "reservation.h"
#include "supply.h"

#include <unistd.h> //sleep
#include <stdio.h>
#include <string.h>

struct btn_ctx btn_temperature; //hot & cold
struct btn_ctx btn_extract;
struct btn_ctx btn_supply;
struct btn_ctx btn_concentration;
struct btn_ctx btn_reservation_clean;
struct btn_ctx btn_reservation_extract;
struct btn_ctx btn_reservation_cancel;
struct btn_ctx btn_clean;
struct btn_ctx btn_onoff;

struct sensor_ctx sensor_hot_weight;
struct sensor_ctx sensor_cold_weight;
struct sensor_ctx sensor_water_weight;
struct sensor_ctx sensor_cup_existence;
struct sensor_ctx sensor_coffee_bean_weight;
struct sensor_ctx sensor_coffee_powder_weight;
struct sensor_ctx sensor_hot_temperature;
struct sensor_ctx sensor_cold_temperature;
struct sensor_ctx sensor_use_count;

int power_flag;
int state = 0;
int concentration = 1; //concentration = 1,2,3

int main() {
	time_init();
	power_flag = 1;
	
	//now_state = 1;
	btn_init(&btn_temperature, 'm');
	btn_init(&btn_onoff, 'o');
	btn_init(&btn_extract, 'e');
	btn_init(&btn_concentration, 'c');
	btn_init(&btn_supply, 's');
	btn_init(&btn_reservation_clean, 'l');
	btn_init(&btn_reservation_extract, 't');
	btn_init(&btn_reservation_cancel, 'a');
	btn_init(&btn_clean, 'n');

	sensor_init(&sensor_hot_weight, "hot_weight.txt", 0, 500);
	sensor_init(&sensor_cold_weight, "cold_weight.txt", 0, 500);
	sensor_init(&sensor_cup_existence, "cup_existence.txt", 0, 1);
	sensor_init(&sensor_coffee_bean_weight, "coffee_bean_weight.txt", 0, 100);
	sensor_init(&sensor_coffee_powder_weight, "coffee_powder_weight.txt", 0, 100);
	sensor_init(&sensor_hot_temperature, "coffee_water_hot_temperature.txt", -100,
			100);
	sensor_init(&sensor_cold_temperature, "coffee_water_cold_temperature.txt", -100,
			100);
	sensor_init(&sensor_use_count,"sensor_count.txt",0,10);
	

	int timer = -1;

	while (1) {


		print_state();
		btns_update();

		if(power_flag){
			printf("[Working]\n");
			wait_tick(state);
			grind_tick(state);
			extract_tick(state);
			reserve_tick(state);
			clean_tick(state);
			supply_tick(state);
			reserved_tick(state);	
		}else{
			printf("[NOT Working]\n");
		}
		sleep(1);
	}
}
