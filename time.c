#include "time.h"

static unsigned int time;

void time_init(){
	time = gettimestamp():
}

unsigned int time_get(){
	return (gettimestamp() - time) * 60;
}