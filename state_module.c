#include "state_module.h"
#include "button.h"
#include <stdio.h>
#include "feedback.h"

extern char input_buf[];

const char *SUPPLY_TYPES[] = {"원두", "커피 가루", "물"};
int supply_type;
int supply_amount;

void print_state(){
        switch(state){
		case STATE_WAIT:
                case STATE_RESERVED:
                {
                    draw_main(win, "17:00", "대기중", "진하게", "온", "1000ml", "100g", "O", "X", "12:19", "--:--");
                    mvwin(win_commands, getbegy(win) + getmaxy(win), 0);
                    draw_commands(win_commands);


//			printf("STATE_WAIT\n");
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
			if(supply_type == 0) {
                            draw_select_supply_type(win, input_buf);
                        } else if(supply_amount == 0) {
    		   	    draw_select_supply_amount(win, SUPPLY_TYPES[supply_type - 1], input_buf);
                        } else {

                        }

			break;
		}
	}

	if(power_flag) {
            mvwprintw(stdscr, 50, 0, "[Working]");

        } else {
            mvwprintw(stdscr, 50, 0, "[Not Working]");
        }

        wrefresh(stdscr);
}

void state_process(){

	if(btn_is_pressed(&btn_temperature)){
		//Nothing to do
	}else if(btn_is_pressed(&btn_extract)){
		new_state(STATE_EXTRACT);
		btn_release(&btn_extract);
	}else if(btn_is_pressed(&btn_supply)){
		new_state(STATE_SUPPLY);
		btn_release(&btn_supply);

                supply_type = 0;
                supply_amount = 0;
	}else if(btn_is_pressed(&btn_concentration)){
		btn_release(&btn_concentration);
	}else if(btn_is_pressed(&btn_reservation_clean)){
                if(state == STATE_WAIT)
     		    new_state(STATE_RESERVE);

		btn_release(&btn_reservation_clean);
	}else if(btn_is_pressed(&btn_reservation_extract)){
		if(state == STATE_WAIT)
                    new_state(STATE_RESERVE);

		btn_release(&btn_reservation_extract);
	}else if(btn_is_pressed(&btn_reservation_cancel)){
                if(state == STATE_WAIT)
		    new_state(STATE_RESERVE);

		btn_release(&btn_reservation_cancel);
	}else if(btn_is_pressed(&btn_clean)){
		new_state(STATE_CLEAN);
		btn_release(&btn_clean);
	}else if(btn_is_pressed(&btn_onoff)){
		power_flag = !power_flag;
		btn_release(&btn_onoff);
	} else {
                return;
        }

        werase(stdscr);
}

void new_state(int state_n){
	state = state_n;
}
