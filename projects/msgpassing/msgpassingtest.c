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
	printf("m:%d n:%d s:%d \n",box.m.value,box.n.value,box.s.value);
	thread_create("sender", PRI_DEFAULT, producer, &box);
	thread_sleep(100);
	thread_create("receiver", PRI_DEFAULT, consumer, &box);
	thread_sleep(10000);
}

void msg_send(mail_box* destination, char* message){
	printf("1 %s m:%d n:%d s:%d \n",thread_name(),destination->m.value,destination->n.value,destination->s.value);
	sema_down(&(destination->m));
	printf("2 %s m:%d n:%d s:%d \n",thread_current()->name,destination->m.value,destination->n.value,destination->s.value);
	sema_down(&(destination->s));
	printf("3 %s m:%d n:%d s:%d \n",thread_current()->name,destination->m.value,destination->n.value,destination->s.value);
	strlcpy(destination->data, message,MAX_SIZE);
	printf("mail box data : %s\n",destination->data);
	sema_up(&(destination->s));
	printf("4 %s m:%d n:%d s:%d \n",thread_current()->name,destination->m.value,destination->n.value,destination->s.value);
	sema_up(&(destination->n));
	printf("5 %s m:%d n:%d s:%d \n",thread_current()->name,destination->m.value,destination->n.value,destination->s.value);

}

void msg_receive(mail_box* source, char* message){
	printf("6 %s m:%d n:%d s:%d \n",thread_current()->name,source->m.value,source->n.value,source->s.value);
	sema_down(&(source->n));
	printf("7 %s m:%d n:%d s:%d \n",thread_current()->name,source->m.value,source->n.value,source->s.value);
	sema_down(&(source->s));
	printf("8 %s m:%d n:%d s:%d \n",thread_current()->name,source->m.value,source->n.value,source->s.value);
	strlcpy(message, source->data,MAX_SIZE);
	printf("receive data : %s\n",message);
	sema_up(&(source->s));
	printf("9 %s m:%d n:%d s:%d \n",thread_current()->name,source->m.value,source->n.value,source->s.value);
	sema_up(&(source->m));
	printf("10 %s m:%d n:%d s:%d \n",thread_current()->name,source->m.value,source->n.value,source->s.value);
}

void mail_box_init(mail_box* box){

	sema_init(&(box->n),0);//receive semaphore = 0
	printf("123\n");
	sema_init(&(box->m),1);//send semaphore = 1
	printf("12345\n");
	sema_init(&(box->s),1);// m.e semaphore = 1
	printf("123456\n");
}

void producer(void* aux){
	struct mail_box *box = (struct mail_box *)aux;
	char data[20] ="hello world!!";
	for(int i =0;i<100;i++){
		msg_send(box,data);
		printf("%d",i);
	}
}

void consumer(void *aux){
	struct mail_box *box = (struct mail_box *)aux;
	char data[20];
	for(int i =0;i<100;i++){
		msg_receive(box,data);
		printf("%d",i);
	}
}
