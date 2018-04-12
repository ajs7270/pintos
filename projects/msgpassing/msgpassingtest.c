#include <stdio.h>
#include <string.h>

#include "projects/msgpassing/msgpassingtest.h"
#include "threads/thread.h"
#include "threads/synch.h"

#define MAX_SIZE 20

typedef struct mailbox{
	/*
		semaphore n for receive semaphore
		ex)
		n == 1 : can receive
		n <= 0 : can't receive

		semaphore m for send semaphore
		ex)
		m == 1 : can send
		m <= 0 : can't send

		semaphore s for mutual exclustion
	*/
		char* data[MAX_SIZE];
		struct semaphore n;
		struct semaphore m;
		struct semaphore s;
} mail_box;

void msg_send(mail_box* destination, char* message);
void msg_receive(mail_box* source, char* message);
void mail_box_init(mail_box* box);

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

void msg_send(mail_box* destination, char* message){
	sema_down(&(destination->m));
	sema_down(&(destination->s));
	strlcpy(destination->data, message,MAX_SIZE);
	printf("mail box data : %s\n",destination->data);
	sema_up(&(destination->s));
	sema_up(&(destination->n));

}

void msg_receive(mail_box* source, char* message){
	sema_down(&(source->n));
	sema_down(&(source->s));
	strlcpy(message, source->data,MAX_SIZE);
	sema_up(&(source->s));
	sema_up(&(source->m));
}

void mail_box_init(mail_box* box){

	sema_init(&(box->n),0);//receive semaphore = 0
	sema_init(&(box->m),1);//send semaphore = 1
	sema_init(&(box->s),1);// m.e semaphore = 1
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
