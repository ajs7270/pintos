#include <stdio.h>
#include <string.h>

#include "projects/msgpassing/msgpassingtest.h"
#include "threads/thread.h"
#include "threads/synch.h"

void producer(void* aux);
void consumer(void* aux);

void run_message_passing_test(void)
{
	mail_box box;
	mail_box_init(&box);
	thread_create("sender", PRI_DEFAULT, producer, &box);
	thread_sleep(100);
	thread_create("receiver", PRI_DEFAULT, consumer, &box);
	thread_sleep(10000);
}

void producer(void* aux){
	struct mail_box *box = (struct mail_box *)aux;
	char data[20] ="hello world!!";
	for(int i =0;i<100;i++){
		msg_send(box,data);
	}
}

void consumer(void *aux){
	struct mail_box *box = (struct mail_box *)aux;
	char data[20];
	for(int i =0;i<100;i++){
		msg_receive(box,data);
	}
}
