#include "state_module.h"
#include "time.h"
#include "feedback.h"

int supply_timer = -1;

void supply_tick(int now_state){
    if(supply_type && supply_amount) {
        if(mysleep(&supply_timer, 3)) {

        supply_type = 0;
        supply_amount = 0;
        } else {
            mvwprintw(stdscr, 54, 0, "%d %d", supply_type, supply_amount);
        }
    }
}
