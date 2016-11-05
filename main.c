#include "button.h"
#include "sensor.h"
#include "time.h"

#include "grind.h"
#include "extract.h"
#include "clean.h"
#include "state.h"


int main(){
	btn_ctx btn_on;
	btn_ctx btn_off;
	btn_ctx btn_extract;
	btn_ctx btn_concentration;
	btn_ctx btn_supply;
	btn_ctx btn_reservation_clean;
	btn_ctx btn_reservation_extract;
	btn_ctx btn_reservation_cancel;
	btn_ctx btn_clean;
	
	btn_init(&btn_on, 'o');
	btn_init(&btn_off, 'f');
	btn_init(&btn_extract, 'e');
	btn_init(&btn_concentration, 'c');
	btn_init(&btn_supply, 's');
	btn_init(&btn_reservation_clean, 'l');
	btn_init(&btn_reservation_extract, 't');
	btn_init(&btn_reservation_cancel, 'a');
	btn_init(&btn_clean, 'n');
	
	sensor_ctx sensor_hot_weight;
	sensor_ctx sensor_cold_weight;
	sensor_ctx sensor_cup_existence;
	sensor_ctx sensor_coffee_bean_weight;
	sensor_ctx sensor_coffee_powder_weight;
	sensor_ctx sensor_hot_temperature;
	sensor_ctx sensor_cold_temperature;
	
	sensor_init(&sensor_hot_weight, “hot_weight.txt”, 0, 500);
	sensor_init(&sensor_cold_weight, “cold_weight.txt”, 0, 500);
	sensor_init(&sensor_cup_existence, “cup_existence.txt”, 0, 1);
	sensor_init(&sensor_coffee_bean_weight, “coffee_bean_weight”, 0, 100);
	sensor_init(&sensor_coffee_powder_weight, “coffee_powder_weight”, 0, 100);
	sensor_init(&sensor_hot_temperature, -100, 100);
	sensor_init(&sensor_cold_temperature, -100, 100);
	
	while(1){
		if(state==0){
			WAITING();
			GRINDING();
			EXTRACTING();
			RESERVING();
			CLEANING();
			SUPPLYING();
			RESERVED();
		}
		sleep(1);
	}
}