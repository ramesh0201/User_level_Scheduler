/*

Ramesh Kumar Thangarajan

*/

#include<stdio.h>
#include"sem.h"

#define N 100
#define MSG_COUNT 10
#define MSG_SIZE 10

struct port
{
	int msg[MSG_COUNT][MSG_SIZE];

	semaphore_t *mutex;

	semaphore_t *prod_sem;
	int sendIdx;

	semaphore_t *cons_sem;
	int recvIdx;

};

typedef struct port port_t;

port_t *ports[N];

void createPorts()
{
	int i,j,k;
	for (i = 0; i < N; i++)
	{
		ports[i] = (port_t *) malloc(sizeof(port_t));

		for (j = 0; j < MSG_COUNT; j++)
		{
			for (k = 0; k < MSG_SIZE; k++)
			{
				ports[i]->msg[j][k] = 0;
			}
		}

		ports[i]->mutex = CreateSem(1);
		ports[i]->prod_sem = CreateSem(10);
		ports[i]->cons_sem = CreateSem(0); // for blocking receive
		ports[i]->sendIdx = 0;
		ports[i]->recvIdx = 0;
	}
}

void receive(int portIdx, int msg[])
{
	int i;
	P(ports[portIdx]->cons_sem);
	P(ports[portIdx]->mutex);

	for (i = 0; i < MSG_SIZE; i++)
		msg[i] = ports[portIdx]->msg[ports[portIdx]->recvIdx][i];
	ports[portIdx]->recvIdx = (ports[portIdx]->recvIdx + 1) % 10;

	V(ports[portIdx]->mutex);
	V(ports[portIdx]->prod_sem);
}

void send(int portIdx, int msg[])
{
	int i;
	P(ports[portIdx]->prod_sem);
	P(ports[portIdx]->mutex);

	for (i = 0; i < MSG_SIZE; i++)
		ports[portIdx]->msg[ports[portIdx]->sendIdx][i] = msg[i];
	ports[portIdx]->sendIdx = (ports[portIdx]->sendIdx + 1) % 10;

	V(ports[portIdx]->mutex);
	V(ports[portIdx]->cons_sem);
}

