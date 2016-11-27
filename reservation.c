#include "state_module.h"
#include "feedback.h"
#include "reservation.h"
#include <time.h>
#include <string.h>
#include "time.h"

extern char input_buf[];
int reserve_action;
int reserve_timer = -1;
int reserve_clean_check_flag = 0;
int reserve_extract_check_flag = 0;
void reserve_change(int action,char *input_buf){
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

    if(action == CLEAN){
        strcpy(reserve_clean_time,input_buf);
    }else if(action == MK_COFFEE){
        strcpy(reserve_extract_time,input_buf);
    }
    FILE *fp;
    fp = fopen("reserve_history.txt","wb+");
    if(fp == NULL) return;
    fprintf(fp, "%d %s\n%d %s", CLEAN,reserve_clean_time,MK_COFFEE,reserve_extract_time);
    fclose(fp);  
}
void reserve_tick(int now_state){

	if(now_state == STATE_RESERVE)
	{
		if(input_buf[strlen(input_buf) - 1] == '\n') {
            if(reserve_action == CANCEL){
                reserve_change(reserve_action,"--:--");
                reserve_change(reserve_action,"--:--");
            }else{
                reserve_change(reserve_action,input_buf);
            }
            input_buf[0] = '\0';
            werase(stdscr);
            new_state(STATE_RESERVED);
        }else{
            if(reserve_action == CANCEL){
                reserve_change(CLEAN,"--:--");
                reserve_change(MK_COFFEE,"--:--");
                werase(stdscr);
                new_state(STATE_RESERVED);
            }
        }
	}
    if(now_state == STATE_RESERVED){
        if(mysleep(&reserve_timer, 3)) {
                new_state(STATE_WAIT);
        }
    }
} // 예약

void reserved_tick(int now_state){
	if(now_state == STATE_WAIT) {
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

        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );


        char buf[256];
        strftime(buf, sizeof(buf), "%H:%M", timeinfo);
        if(strcmp(buf,reserve_clean_time) == 0 && reserve_clean_check_flag == 0){
            //reserve_change(CLEAN,"--:--");
            reserve_clean_check_flag = 1;
            new_state(STATE_CLEAN);
        }else{
            if(strcmp(buf,reserve_clean_time) != 0 )
            reserve_clean_check_flag = 0;
        }
        if(strcmp(buf,reserve_extract_time) == 0 && reserve_extract_check_flag == 0){
            //reserve_change(MK_COFFEE,"--:--");
            reserve_extract_check_flag = 1;
            new_state(STATE_EXTRACT);
        }else{
            if(strcmp(buf,reserve_extract_time) != 0)
            reserve_extract_check_flag = 0;
        }

	}
} //에약데이터
