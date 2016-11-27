#include "state_module.h"
#include "button.h"
#include <stdio.h>
#include "feedback.h"
#include "sensor.h"
#include "stringlib.h"
#include <time.h>
#include "reservation.h"
#include <string.h>
#include "time.h"
#include <stdlib.h>

extern char input_buf[];
extern int reserve_action;
const char *SUPPLY_TYPES[] = {"원두", "커피 가루", "물(온)", "물(냉)"};
const char *STATE_TYPES[] = {"대기중", "분쇄중", "추출중", "예약중", "청소중", "보충중","예약됨"};
const char *CONCENTRATION_TYPES[] = {"진하게","중간","연하게"};
const char *TEMP_TYPES[] = {"온","냉"};
int supply_type;
int supply_amount;
int error_timer = -1;
int old_state = 0;
void print_state(){
	if(error_msg) {
		draw_warning(win, error_msg, 0);
        
        return;
	}

        switch(state){
        case STATE_WAIT:
        case STATE_RESERVED:
        case STATE_GRIND:
        case STATE_EXTRACT:
        case STATE_CLEAN:
        {
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            char powder_flag[2] = {0};
            char clean_flag[2] = {0};
            if (sensor_get(&sensor_coffee_powder_weight) < 10) {
                powder_flag[0] = 'X';
            }else{
                powder_flag[0] = 'O';
            }
            if (sensor_get(&sensor_use_count) < 10) {
                clean_flag[0] = 'X';
            }else{
                clean_flag[0] = 'O';
            }

            FILE *f;
            char reserve_clean_time[20] = {0};
            char reserve_extract_time[20] = {0};
            int flag;
            f=fopen("reserve_history.txt", "rb");
            if(f == NULL) return;
            while(!feof(f)){
                char buf[20] = {0};
                fscanf(f, "%d %s\n", &flag,buf);
                if(flag == CLEAN){
                    strcpy(reserve_clean_time,buf);
                }else{
                    strcpy(reserve_extract_time,buf);
                }
            }
            fclose(f);

            draw_main(win, NULL, STATE_TYPES[state], CONCENTRATION_TYPES[concentration], TEMP_TYPES[temp_flag], scat(itoa_c(sensor_get(&sensor_cold_weight),10),"ml"),scat(itoa_c(sensor_get(&sensor_hot_weight),10),"ml"), scat(itoa_c(sensor_get(&sensor_coffee_bean_weight),10),"g"), powder_flag, clean_flag, reserve_extract_time, reserve_clean_time);
            mvwin(win_commands, getbegy(win) + getmaxy(win), 0);
            draw_commands(win_commands);
            break;
        }
        case STATE_RESERVE:{
            if(state != old_state){
                wresize(win, 80, 80);
                werase(win);
                wrefresh(win);
            }
            if(reserve_action != CANCEL){
                draw_select_time(stdscr,input_buf);
            }
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
        old_state = state;
}

void state_process(){

    if(btn_is_pressed(&btn_temperature)){
        temp_flag = !temp_flag;
        btn_release(&btn_temperature);
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
        concentration++;
        concentration = concentration%3;
    }else if(btn_is_pressed(&btn_reservation_clean)){
            if(state == STATE_WAIT){
                new_state(STATE_RESERVE);
                reserve_action = CLEAN;
            }

        btn_release(&btn_reservation_clean);
    }else if(btn_is_pressed(&btn_reservation_extract)){
        if(state == STATE_WAIT){
            new_state(STATE_RESERVE);
            reserve_action = MK_COFFEE; 
        }
        btn_release(&btn_reservation_extract);
    }else if(btn_is_pressed(&btn_reservation_cancel)){
        if(state == STATE_WAIT){
            new_state(STATE_RESERVE);
            reserve_action = CANCEL;
        }
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
