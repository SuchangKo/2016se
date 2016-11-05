#include "state_module.h"
#include "button.h"
#include <stdio.h>

void print_state(){
	switch(state){
		case STATE_WAIT:{
			printf("STATE_WAIT\n");
			break;
		}
		case STATE_GRIND:{
			printf("STATE_GRIND\n");
			break;
		}
		case STATE_EXTRACT:{
			printf("STATE_EXTRACT\n");
			break;
		}
		case STATE_RESERVE:{
			printf("STATE_RESERVE\n");
			break;
		}
		case STATE_CLEAN:{
			printf("STATE_CLEAN\n");
			break;
		}
		case STATE_SUPPLY:{
			printf("STATE_SUPPLY\n");
			break;
		}
		case STATE_RESERVED:{
			printf("STATE_RESERVED\n");
			break;
		}
	}
}

void state_process(){

	if(btn_is_pressed(&btn_temperature)){
		temp_flag = !temp_flag;
		btn_release(&btn_temperature);
	}else if(btn_is_pressed(&btn_extract)){
		state = STATE_EXTRACT;
		btn_release(&btn_extract);
	}else if(btn_is_pressed(&btn_supply)){
		state = STATE_SUPPLY;
		btn_release(&btn_supply);
	}else if(btn_is_pressed(&btn_concentration)){
		btn_release(&btn_concentration);
	}else if(btn_is_pressed(&btn_reservation_clean)){
		if(state == STATE_WAIT)
			state = STATE_RESERVE; //use RESERVED_ACTION
		btn_release(&btn_reservation_clean);
	}else if(btn_is_pressed(&btn_reservation_extract)){
		if(state == STATE_WAIT)
			state = STATE_RESERVE; //use RESERVED_ACTION
		btn_release(&btn_reservation_extract);
	}else if(btn_is_pressed(&btn_reservation_cancel)){
		if(state == STATE_WAIT)
			state = STATE_RESERVE; //use RESERVED_ACTION
		btn_release(&btn_reservation_cancel);
	}else if(btn_is_pressed(&btn_clean)){
		state = STATE_CLEAN;
		btn_release(&btn_clean);
	}else if(btn_is_pressed(&btn_onoff)){
		power_flag = !power_flag;
		btn_release(&btn_onoff);
	}
}

void new_state(int state_n){
	state = state_n;
}