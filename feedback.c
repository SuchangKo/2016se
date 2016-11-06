#include <curses.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define COL_SEP_MAIN 25
#define COL_SEP_SUPPLY 4
#define COL_SEP_COMMANDS 4

#define max(a, b) a > b ? a : b

char *error_msg = NULL;

void draw_main(WINDOW *win, const char *current_time, const char *current_state, const char *concentration, const char *temperature, const char *cold_water_remains, const char *hot_water_remains, const char *coffee_remains, const char *powder_exists, const char *needs_cleaning, const char *coffee_time, const char *clean_time) {
    wresize(win, 13, 40);
    werase(win);
    box(win, '|', '-');

    mvwprintw(win, 1, 2, "현재 시간"); 

    /*
    time_t ptime = 1234+60;
    struct tm *tm_info = gmtime(&ptime);
    */
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );


    char buf[256];
    strftime(buf, sizeof(buf), "%H:%M", timeinfo);

    mvwprintw(win, 1, COL_SEP_MAIN, "| %s", buf); 

    mvwprintw(win, 2, 2, "현재 상태");
    mvwprintw(win, 2, COL_SEP_MAIN, "| %s", current_state);

    mvwprintw(win, 3, 2, "선택 농도");
    mvwprintw(win, 3, COL_SEP_MAIN, "| %s", concentration);

    mvwprintw(win, 4, 2, "선택 온도");
    mvwprintw(win, 4, COL_SEP_MAIN, "| %s", temperature);

    mvwprintw(win, 5, 2, "물(온) 잔량");
    mvwprintw(win, 5, COL_SEP_MAIN, "| %s", hot_water_remains);

    mvwprintw(win, 6, 2, "물(냉)잔량");
    mvwprintw(win, 6, COL_SEP_MAIN, "| %s", cold_water_remains);

    mvwprintw(win, 7, 2, "커피 잔량 (원두)");
    mvwprintw(win, 7, COL_SEP_MAIN, "| %s", coffee_remains);

    mvwprintw(win, 8, 2, "가루 커피 유무");
    mvwprintw(win, 8, COL_SEP_MAIN, "| %s", powder_exists);

    mvwprintw(win, 9, 2, "커피 가루 청소 필요");
    mvwprintw(win, 9, COL_SEP_MAIN, "| %s", needs_cleaning);

    mvwprintw(win, 10, 2, "커피 예약 시간");
    mvwprintw(win, 10, COL_SEP_MAIN, "| %s", coffee_time);

    mvwprintw(win, 11, 2, "청소 예약시간");
    mvwprintw(win, 11, COL_SEP_MAIN, "| %s", clean_time);

    wrefresh(win);
}

void draw_select_supply_type(WINDOW *win, const char *buf) {
    wresize(win, 10, 20);
    werase(win);
    box(win, '|', '-');
    
    mvwprintw(win, 1, 2, "재료 선택");
    mvwprintw(win, 2, 1, "------------------");

    mvwprintw(win, 3, 2, "1");
    mvwprintw(win, 3, COL_SEP_SUPPLY, "| %s", "원두");

    mvwprintw(win, 4, 2, "2");
    mvwprintw(win, 4, COL_SEP_SUPPLY, "| %s", "커피 가루");

    mvwprintw(win, 5, 2, "3");
    mvwprintw(win, 5, COL_SEP_SUPPLY, "| %s", "물(온)");

    mvwprintw(win, 6, 2, "4");
    mvwprintw(win, 6, COL_SEP_SUPPLY, "| %s", "물(냉)");

    mvwprintw(win, 7, 1, "------------------");
    mvwprintw(win, 8, 2, "Input> %s", buf);

    wrefresh(win);
}

void draw_select_supply_amount(WINDOW *win, const char *type, const char *buf) {
    wresize(win, 5, 20);
    werase(win);
    box(win, '|', '-');
    
    mvwprintw(win, 1, 2, "%s 투입량:", type);
    mvwprintw(win, 2, 1, "------------------");

    mvwprintw(win, 3, 2, "Input> %s", buf);

    wrefresh(win);
}

void draw_select_time(WINDOW *win, const char *buf) {
    wresize(win, 5, 20);
    werase(win);
    box(win, '|', '-');
    
    mvwprintw(win, 1, 2, "시간 입력:");
    mvwprintw(win, 2, 1, "------------------");

    mvwprintw(win, 3, 2, "Input> %s", buf);

    wrefresh(win);
}

void draw_warning(WINDOW *win, const char *msg, int beep_count) {
    wresize(win, 5, 40);
    werase(win);
    box(win, '|', '-');
    
    mvwprintw(win, 1, 2, "경고");
    mvwprintw(win, 2, 1, "--------------------------------------");
    mvwprintw(win, 3, 2, "%s", msg);

    for(int i = 0; i < beep_count; i++) {
        beep();
    }

    wrefresh(win);
}

void draw_commands(WINDOW *win) {
    wresize(win, 12, 30);
    werase(win);
    box(win, '|', '-');
    
    mvwprintw(win, 1, 2, "q | %s", "종료");
    mvwprintw(win, 2, 2, "o | %s", "온/오프 버튼");
    mvwprintw(win, 3, 2, "c | %s", "농도 세팅 버튼");
    mvwprintw(win, 4, 2, "m | %s", "온도 세팅 버튼");
    mvwprintw(win, 5, 2, "e | %s", "추출 버튼");
    mvwprintw(win, 6, 2, "s | %s", "보충 버튼");
    mvwprintw(win, 7, 2, "n | %s", "청소 버튼");
    mvwprintw(win, 8, 2, "l | %s", "청소 예약 버튼");
    mvwprintw(win, 9, 2, "t | %s", "추출 예약 버튼");
    mvwprintw(win, 10, 2, "a | %s", "예약 취소 버튼");

    wrefresh(win);
}

void draw_test(WINDOW *win) {
    static int x = 0;
    wresize(win, 4, 80);
    werase(win);
    box(win, '|', '-');

    mvwprintw(win, 1, 1, "%d", x++);
    mvwprintw(win, 2, 1, "%d", x);

    wrefresh(win);
}

WINDOW *win = NULL;
WINDOW *win_commands = NULL;

char input_buf[256] = {};
char allowed_charset[256] = "0123456789:\n";

int feedback_init() {
    setlocale(LC_ALL, "ko_KR.utf-8");
    initscr();
    curs_set(0);
    nodelay(stdscr, TRUE);
    noecho();

    win = newwin(0, 0, 0, 0);
    win_commands = newwin(0, 0, 0, 0);
    return 0;
}

int feedback_fini() {
    endwin();
    return 0;
}

int test_feedback_main(int argc, char *argv[])
{
    feedback_init();

    while(1) {
        //draw_main(win, "17:00", "대기중", "진하게", "온", "1000ml", "100g", "O", "X", "12:19", "--:--");
        draw_select_supply_type(win, input_buf);
        //draw_select_supply_amount(win, "원두", buf);
        //draw_select_time(win, buf);
        //draw_warning(win, "물부족 (잔량 37ml)", 2);
        mvwin(win_commands, getbegy(win) + getmaxy(win), 0);
        draw_commands(win_commands);
        
        usleep(100000);

        char ch = getch();
        mvwprintw(stdscr, 50, 1, "%d %d\n", ch, '\b'); // test

        if(ch == 'q') {
            break;
        } else if(strchr(allowed_charset, ch)) {
            int end = strlen(input_buf);
            input_buf[end++] = ch;
            input_buf[end] = '\0';
        } else if(ch == '\n') {
            input_buf[0] = '\0';
        } else if(ch == 0x7f) {
            input_buf[max(0, strlen(input_buf) - 1)] = '\0';
        }
    }

    feedback_fini();
    return 0;
}

