
/*

Ramesh Kumar Thangarajan

*/

#include <stdio.h>
#include <pthread.h>
#include "q.h"

TCB_t *Q = 0;

void printQSize()
{
	printf("%d\n",getSize(&Q));
}

void start_thread(void (*function)(void))
{
	TCB_t *t;
	void *stack = (void *) malloc(8192);
	t = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(t,function,stack,8192);
	AddQ(&Q,&t);
}

void run() 
{
	ucontext_t parent;
	swapcontext(&parent, &(Q->context));
}

void yield() 
{
	RotateQ(&Q);
	if(Q == NULL)
		return;
	swapcontext(&(Q->prev->context), &(Q->context));
}

void Delete() 
{
	DelQ(&Q);
	if(Q == NULL)
		return;
	setcontext(&(Q->context));	
}
