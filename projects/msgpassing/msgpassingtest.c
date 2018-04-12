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
	*/
		char* data[MAX_SIZE];
		struct semaphore n;
		struct semaphore m;
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

	thread_create("sender", PRI_DEFAULT, producer, &box);
	thread_create("receiver", PRI_DEFAULT, consumer, &box);
}

void msg_send(mail_box* destination, char* message){

	sema_down(&(destination->m));
	strlcpy(destination->data, message,MAX_SIZE);
	printf("mail box data : %s\n",destination->data);
	sema_up(&(destination->n));
	printf("1");
}

void msg_receive(mail_box* source, char* message){
	printf("2");
	sema_down(&(source->n));
	strlcpy(message, source->data,MAX_SIZE);
	printf("receive data : %s\n",message);
	sema_up(&(source->m));
}

void mail_box_init(mail_box* box){

	sema_init(&(box->n),0);//receive semaphore = 1
	sema_init(&(box->m),1);//send semaphore = 0
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
