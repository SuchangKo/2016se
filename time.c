#include "time.h"
#include <time.h>

unsigned int st;

void time_init(){
	st = time(NULL);
}

unsigned int mytime(){
	return time(NULL) - st;
}

int mysleep_init(int *id) {
	*id = -1;
        return 0;
}

int mysleep(int *id, int duration) {
	if(*id == -1) {
		*id = mytime();
	} else if(mytime() - *id >= duration) {
		*id = -1;
		return 1;
	}

	return 0;
}
