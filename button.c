#include "button.h"
#include <stdio.h>

/*
 int verify_key{
 on.pressed ?=1
 off.pressed ?=1
 ..
 sleep(3);
 }
 */
void btn_init(struct btn_ctx *c, char init_c) {

}
void btns_update() {
	char c;
	c = getc(stdin);
	if (c == btn_on.key) {
		btn_press(&btn_on);
	} else if (c == btn_off.key) {
		btn_press(&btn_off);
	}
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
