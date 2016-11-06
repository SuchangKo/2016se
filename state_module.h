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
extern int power_flag;
extern int temp_flag;
void print_state();

extern struct btn_ctx btn_temperature; //hot & cold
extern struct btn_ctx btn_extract;
extern struct btn_ctx btn_supply;
extern struct btn_ctx btn_concentration;
extern struct btn_ctx btn_reservation_clean;
extern struct btn_ctx btn_reservation_extract;
extern struct btn_ctx btn_reservation_cancel;
extern struct btn_ctx btn_clean;
extern struct btn_ctx btn_onoff;
extern int state;
extern int concentration;
extern int supply_type;
extern int supply_amount;
extern int reserve_action;

void state_process();

void new_state(int state_n);
