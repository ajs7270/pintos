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

struct semaphore v;

typedef struct {
	char name;
	char src;
	char dest;
	struct position pos;
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
	car->name = name;
	car->src = src;
	car->dest = dest;
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

void move(void* aux){
	vehicle *car = (vehicle*) aux;

}

void view(void* aux){printf("\033[2J");
		for(int i =0;i<MAP_SIZE;i++){
			for(int j =0;j<MAP_SIZE;j++){

			}
		}


	while(true){
		printf("\033[2J");
		for(int i =0;i<MAP_SIZE;i++){
			for(int j =0;j<MAP_SIZE;j++){

			}
		}
	}
}
