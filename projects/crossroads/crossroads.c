#include <stdio.h>
#include <string.h>

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

#include "projects/crossroads/crossroads.h"
#include "projects/crossroads/mapdata.h"
#include "projects/crossroads/position.h"

#define MAP_SIZE 7

struct semaphore map_sema[MAP_SIZE][MAP_SIZE];

typedef struct {
	char name;
	struct position path[10];
	struct position cur_pos;
	struct position next_pos;
}vehicle;

void vehicle_init(vehicle* car,char name, char src, char dest);
// draw map and vehicle
void view();
// argv parse and create car using thread
void create_vehicle(char *arg,vehicle* cars);
// for thread
void move(void* aux);


void run_crossroads(char **argv)
{
	vehicle* cars;

	create_vehicle(argv[1],cars);
	thread_create("view",PRI_DEFAULT,move,)
}

void vehicle_init(vehicle* car,char name, char src, char dest){
	int srcNum,destNum;

	car->name = name;

	//initialize path
	if(src = 'A'){
		srcNum = 0;
	}else if(src = 'B'){
		srcNum = 1;
	}else{
		srcNum = 2;
	}
	if(destNum = 'A'){
		destNum = 0;
	}else if(destNum = 'B'){
		destNum = 1;
	}else{
		destNum = 2;
	}

	for(int i = 0; i<10; i++){
		car->path[i] = path[srcNum][destNum][i];
	}

	//initialize current pos
	car->cur_pos.row = -1;
	car->cur_pos.col = -1;
	//initialize next pos
	car->next_pos.row = car->path[0].row;
	car->next_pos.col = car->path[0].col;
}


void create_vehicle(char * arg, vehicle* cars){
	int num_of_car;
	char *token, *save_ptr;

	num_of_car = (strnlen(arg,100)+1)/4;
	cars = (vehicle*)malloc(sizeof(vehicle)* num_of_car);

	int i = 0;
	for(token = strtok_r(arg, ":", &save_ptr); token != NULL;
													token = strtok_r (NULL, ":", &save_ptr)) {
		char name = *(token);
		char src = *(token+1);
		char dest = *(token+2);

		vehicle_init(&cars[i],name,src,dest);
		thread_create("car", PRI_DEFAULT, move, &cars[i]);
		i++;
	}
}

//running car thread
void move(void* aux){
	vehicle *car = (vehicle*) aux;


}

void view(void* aux){
	char map_car_draw[MAP_SIZE][MAP_SIZE];
	while(true){
		for(int i =0;i<MAP_SIZE;i++){
			for(int j =0;j<MAP_SIZE;j++){
				map_car_draw[i][j] = map_draw_default[i][j];
			}
		}
		/*

		implement
		car mapping map

		*/
		printf("\033[2J");
		for(int i =0;i<MAP_SIZE;i++){
			for(int j =0;j<MAP_SIZE;j++){
				printf("%c",map_car_draw[i][j])
			}
			printf("\n");
		}
	}
}
