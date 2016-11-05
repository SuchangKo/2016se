#include <stdio.h>

struct sensor_ctx{
	char filename[261];
	int min;
	int max;
};

extern int concentration; //concentration = 1,2,3

extern struct sensor_ctx sensor_hot_weight;
extern struct sensor_ctx sensor_cold_weight;
extern struct sensor_ctx sensor_water_weight;
extern struct sensor_ctx sensor_cup_existence;
extern struct sensor_ctx sensor_coffee_bean_weight;
extern struct sensor_ctx sensor_coffee_powder_weight;
extern struct sensor_ctx sensor_hot_temperature;
extern struct sensor_ctx sensor_cold_temperature;


int sensor_get(struct sensor_ctx *c);

void sensor_update(struct sensor_ctx *c, int data);

int sensor_add(struct sensor_ctx *c, int amount);

int sensor_sub(struct sensor_ctx *c, int amount);

void sensor_init(struct sensor_ctx *c, char *filename, int min, int max);
