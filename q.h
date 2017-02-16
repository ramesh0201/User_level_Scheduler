/*
Ramesh Kumar Thangarajan
1209310930
*/

#include<stdio.h>
#include<stdlib.h>
#include "TCB.h"

void InitQ(TCB_t **Q) 
{
	*Q = NULL;
}

void AddQ(TCB_t **Q,TCB_t** item)
{
	//TCB_t* temp = (TCB_t*) malloc(sizeof(TCB_t));
	//temp->context = (*item)->context;
	if (*Q)
	{
		(*item)->prev = (*Q)->prev;
		(*item)->next = (*Q)->prev->next;
		(*Q)->prev->next = *item;
	}
	else
	{
		(*item)->prev = *item;
		(*item)->next = *item;
		*Q = *item;
	}
	(*Q)->prev = *item;
}

TCB_t* DelQ(TCB_t **Q) 
{
	if(*Q)
	{
		TCB_t* temp = (TCB_t*) malloc(sizeof(TCB_t));
		temp->context = (*Q)->context;
		temp->prev = (*Q)->prev;
		temp->next = (*Q)->next;
		if((*Q)->next == *Q)
		{
			//printf("Going to delete last thread!!\n");
			//printf("************************************************\n");
			free(*Q);
			*Q = NULL;
		}
		else
		{
			TCB_t* ptemp = *Q;
			(*Q)->prev->next = (*Q)->next;
			(*Q)->next->prev = (*Q)->prev;
			*Q = (*Q)->next;
			free(ptemp);
		}
		return temp;
	}
	return NULL;
}

void RotateQ(TCB_t **Q) 
{ 
	if(*Q) 
		*Q = (*Q)->next;
	else 
		printf("Queue is empty!! Hence cannot rotate!!!\n");
}

int getSize(TCB_t **Q)
{
	int size = 0;
	TCB_t *temp = *Q;
	if(temp == NULL) return 0;
	do
	{
		size++;
		temp = temp->next;
	}while(temp != *Q);
	return size;
}
