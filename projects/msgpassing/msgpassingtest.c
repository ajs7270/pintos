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

void producer(mail_box* box);
void consumer(mail_box* box);

void run_message_passing_test(void)
{
	mail_box box;
	mail_box_init(&box);
	printf("m:%d n:%d s:%d \n",box.m.value,box.n.value,box.s.value);
	thread_create("sender", PRI_DEFAULT, producer, &box);
	thread_create("receiver", PRI_DEFAULT, consumer, &box);
}

void msg_send(mail_box* destination, char* message){
	printf("1 %s m:%d n:%d s:%d \n",thread_current()->name,destination->m.value,destination->n.value,destination->s.value);
	sema_down(&(destination->m));
	printf("sema %s m:%d n:%d s:%d \n",thread_current()->name,destination->m.value,destination->n.value,destination->s.value);
	printf("2 %s m:%d n:%d s:%d \n",thread_current()->name,destination->m.value,destination->n.value,destination->s.value);
	sema_down(&(destination->s));
	printf("3 %s",thread_current()->name);
	strlcpy(destination->data, message,MAX_SIZE);
	thread_sleep(100);
	printf("mail box data : %s\n",destination->data);
	sema_up(&(destination->n));
	sema_up(&(destination->s));
}

void msg_receive(mail_box* source, char* message){
	printf("4 %s",thread_current()->name);
	sema_down(&(source->n));
	printf("5 %s",thread_current()->name);
	sema_down(&(source->s));
	printf("6 %s",thread_current()->name);
	strlcpy(message, source->data,MAX_SIZE);
	//thread_sleep(100);
	printf("receive data : %s\n",message);
	sema_up(&(source->m));
	sema_up(&(source->s));
}

void mail_box_init(mail_box* box){

	sema_init(&(box->n),0);//receive semaphore = 0
	printf("123\n");
	sema_init(&(box->m),1);//send semaphore = 1
	printf("12345\n");
	sema_init(&(box->s),1);// m.e semaphore = 1
	printf("123456\n");
}

void producer(mail_box* box){
	char data[20] ="hello world!!";
	while(true){
		msg_send(box,data);
	}
}

void consumer(mail_box* box){
	char data[20];
	while(true){
		msg_receive(box,data);
	}
}
