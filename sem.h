/*

Ramesh Kumar Thangarajan

*/

#include<stdio.h>
#include<stdlib.h>
#include "threads.h"

struct semaphore
{
	int count;
	TCB_t *SemQ;
};

typedef struct semaphore semaphore_t;

semaphore_t *CreateSem(int input)
{
	semaphore_t *sem = (semaphore_t *)malloc(sizeof(semaphore_t));
	sem->count = input;
	InitQ(&sem->SemQ);
	return sem;
}

void P(semaphore_t *sem)
{
	sem->count--;
	TCB_t *temp = NULL;
	if(sem->count < 0)
	{
		temp = DelQ(&Q);
		if(temp)
		{
			AddQ(&(sem->SemQ),&temp);
			swapcontext(&(temp->context),&(Q->context));
		}
		else
		{
			printf("Delete returned null in P\n");
		}
	}
}

void V(semaphore_t *sem)
{
	sem->count++;
	TCB_t *temp = NULL;
	if(sem->count <= 0)
	{
		temp = DelQ(&(sem->SemQ));
		if(temp)
		{
			AddQ(&Q,&temp);
		}
		else
		{
			printf("Delete returned null in V\n");
		}
	}
	yield();
}
