//State Process Module

#define STATE_WAIT 0
#define STATE_GRIND 1
#define STATE_EXTRACT 2
#define STATE_RESERVE 3
#define STATE_CLEAN 4
#define STATE_SUPPLY 5
#define STATE_RESERVED 6
#define false 0
#define true 1

extern int state;

void new_state(int state_n);
