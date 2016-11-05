#include "time.h"

static unsigned int time;

unsigned int gettimestamp(){
	return 0;
}
void time_init(){
	time = gettimestamp();
}

unsigned int time_get(){
	return (gettimestamp() - time);
}
