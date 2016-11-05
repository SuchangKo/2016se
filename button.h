struct btn_ctx{
	char key;
	char pressed;
};

void btn_init(struct btn_ctx *c, char init_c);
void btns_update();

void btn_release(struct btn_ctx *c);
void btn_press(struct btn_ctx *c);
int btn_is_pressed(struct btn_ctx *c);

extern struct btn_ctx btn_temperature; //hot & cold
extern struct btn_ctx btn_extract;
extern struct btn_ctx btn_supply;
extern struct btn_ctx btn_concentration;
extern struct btn_ctx btn_reservation_clean;
extern struct btn_ctx btn_reservation_extract;
extern struct btn_ctx btn_reservation_cancel;
extern struct btn_ctx btn_clean;
extern struct btn_ctx btn_on;
extern struct btn_ctx btn_off;

