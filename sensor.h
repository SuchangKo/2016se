#include "sensor.h"

struct sensor_ctx{
	char filename[261];
	int min;
	int max;
};

int sensor_get(struct sensor_ctx *c);

void sensor_update(struct sensor_ctx *c, int data);

int sensor_add(struct sensor_ctx *c, int amount);

int sensor_sub(struct sensor_ctx *c, int amount);

void sensor_init(struct sensor_ctx *c, char *filename, int min=0x80000000, int max=0x7fffffff);