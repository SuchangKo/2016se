#include "sensor.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

int sensor_get(struct sensor_ctx *c){
	//sensor data get
	FILE *f;
	int ret;
	f=fopen(c -> filename, "rb");
	fscanf(f, "%d", &ret);
	fclose(f);
	return ret;
}

void sensor_update(struct sensor_ctx *c, int data){
	//coffee fill, water fill, etc
	FILE *f;
	f=fopen(c->filename, "wb");
	fprintf(f, "%d", data);
	fclose(f);
}

int sensor_add(struct sensor_ctx *c, int amount){
	//sub amount
	FILE *f;
	int old, new;
	f=fopen(c->filename, "wb+");
	fscanf(f, "%d", &old);
	fseek(f, 0, SEEK_SET);
	ftruncate(fileno(f), 0);
	new = max(c->min, min(c->max, old+amount));
	fprintf(f, "%d", new);
	fclose(f);
	return (new - old) == amount; //return 1 if success / 0 if not
}

int sensor_sub(struct sensor_ctx *c, int amount){
	//sub amount
	return sensor_add(c, -amount); //return 1 if success / 0 if not
}

void sensor_init(struct sensor_ctx *c, char *filename, int min, int max){
	//min = =0x80000000;
	//max = =0x7fffffff;
	strcpy(c->filename, filename);
	c->min=min;
	c->max=max;
}
