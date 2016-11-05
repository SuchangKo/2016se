#include "button.h"
#include <stdio.h>
#include "state_module.h"
/*
 int verify_key{
 on.pressed ?=1
 off.pressed ?=1
 ..
 sleep(3);
 }
 */
extern struct btn_ctx btn_ctxs[9];

void btn_init(struct btn_ctx *c, char init_c) {
	c->key = init_c;
	c->pressed = 0;
}
void btns_update() {
	char c;
	c = getc(stdin); //blocking...
	if(c == 10) c = getc(stdin); //New Line Check
	if(c == btn_temperature.key){
		btn_press(&btn_temperature);
	}else if(c == btn_extract.key){
		btn_press(&btn_extract);
	}else if(c == btn_supply.key){
		btn_press(&btn_supply);
	}else if(c == btn_concentration.key){
		btn_press(&btn_concentration);
	}else if(c == btn_reservation_clean.key){
		btn_press(&btn_reservation_clean);
	}else if(c == btn_reservation_extract.key){
		btn_press(&btn_reservation_extract);
	}else if(c == btn_reservation_cancel.key){
		btn_press(&btn_reservation_cancel);
	}else if(c == btn_clean.key){
		btn_press(&btn_clean);
	}else if(c == btn_onoff.key){
		btn_press(&btn_onoff);
	}
	state_process();
	/*
	if (c == btn_on.key) {
		btn_press(&btn_on);
	} else if (c == btn_off.key) {
		btn_press(&btn_off);
	}
	*/
}

void btn_release(struct btn_ctx *c) {
	c->pressed = 0;
}

void btn_press(struct btn_ctx *c) {
	c->pressed = 1;
}
int btn_is_pressed(struct btn_ctx *c) {
	return c->pressed;
}
