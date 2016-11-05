#include "button.h"
/*
int verify_key{
	on.pressed ?=1
	off.pressed ?=1
	..
	sleep(3);
}
*/

///////////////////////////////////////////////////

void btns_update(){
	getc(c)
	if(c == on.key){
		btn_press(&on)
	}
	else if(c == off.key){
		btn_press(&off)
	}
	...
}

void btn_release(struct btn_ctx *c){
	c->pressed=0;
}

void btn_press(struct btn_ctx *c){
	c->pressed=1;
}

int btn_is_pressed(struct btn_ctx *c){
	return c->pressed;
}
