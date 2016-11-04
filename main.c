int main(){}

int load_data(){}

int sensor_init(){}

struct btn_ctx{
	char key;
	char pressed=1;
}

struct btn_ctx on;
on.key= 'q';
struct btn_ctx off;
off.key = 'w';

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
	if(c==on.key){
		btn_press(&on)
	}
	else if(c==off.key){
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


////////////////////////////////////////////////////



struct sensor_ctx{
	char filename[261];
	int min;
	int max;
}

int sensor_get(struct sensor_ctx *c){
	//sensor data get
	FILE *f;
	int ret;
	f=fopen(c->filename, "rb");
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

void sensor_init(struct sensor_ctx *c, char *filename, int min=0x80000000, int max=0x7fffffff){
	strcpy(c->filename, filename);
	c->min=min;
	c->max=max;
}

///////////////////////////////////////////////////////////////////////


void GRINDING(int state)
{
	if(state == GRINDING){

	}
}
void EXTRACTING(int state)
{
	if(state == EXTRACTING && sensor_get(&sensor_coffee_powder_weight) < 10)
	{
		state = GRINDING;

	}
	else if(state == EXTRACTING && sensor_get(&sensor_coffee_powder_weight) >= 10){
	{	
		if(sensor_get(&sensor_water) < 300 || sensor_get(&sensor_cup_existence) == false || Count >= 10) //new sensor_water
		{
			//ERROR
			Extract_Condition = Off;
		}
		if(sensor_get(&sensor_water) >= 300 || sensor_get(&sensor_cup_existence) == true || Count < 10) //new sensor_water
		{
			//Put Powder & Water By Button Data[Concentration]
			//Decide Temperature
			if(button_data(&btn_temperature) == Hot)
			{
				Solenoid_Command(On);
				//Delay By Button Data[Concentration]
				Solenoid_Command(Off);
				Put_Hot_Water;
			}else if(button_data(&btn_temperature) == Cold){
				Solenoid_Command(On);
				//Delay By Button Data[Concentration]
				Solenoid_Command(Off);
				Put_Cold_Water;
			}
			//State WAITING
		}
	}	
}
void CLEANING(int state)
{
	if(state == CLEANING){
		if(sensor_get(&sensor_coffee_powder_weight) >= 10)
	}
}
