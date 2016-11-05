#include "time.h"
#include <time.h>

static unsigned int st;

void time_init(){
	st = time(NULL);
}

unsigned int time_get(){
	return time(NULL) - st;
}
