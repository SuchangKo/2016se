#pragma once
#include <curses.h>

void draw_main(WINDOW *win, const char *current_time, const char *current_state, const char *concentration, const char *temperature, const char *water_remains, const char *coffee_remains, const char *powder_exists, const char *needs_cleaning, const char *coffee_time, const char *clean_time);
void draw_select_supply_type(WINDOW *win, const char *buf);
void draw_select_supply_amount(WINDOW *win, const char *type, const char *buf);
void draw_select_time(WINDOW *win, const char *buf);
void draw_warning(WINDOW *win, const char *msg, int beep_count);
void draw_commands(WINDOW *win);
void draw_test(WINDOW *win);
int feedback_init();
int feedback_fini();

extern WINDOW *win;
extern WINDOW *win_commands;
