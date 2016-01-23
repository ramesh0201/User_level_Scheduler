/*

Ramesh Kumar Thangarajan

*/

#include<stdio.h>
#include<unistd.h>
#include "msgs.h"

int sPort = 0; // server is allocated first 3 ports (port0 to port2)
int cPort = 3; // client takes the remaining (port3 to port99)

void print()
{
	int e=0, cnt=0;
	printf("RunQ: ");
	printQSize();

	printf("Ports Sem: ");
	for(e=0;e<N;e++)
	{
		cnt += getSize(&(ports[e]->prod_sem->SemQ));
		cnt += getSize(&(ports[e]->cons_sem->SemQ));
	}
	printf("%d\n", cnt);

}

void client()
{
	int msg[10];
	int i, clTracker=0, sTracker=0;
	if (cPort < N)
	{
		clTracker = cPort++;

		for (i = 0; i < MSG_SIZE; i++)
			msg[i] = clTracker;

		sTracker = clTracker % 3;

		while (1)
		{
			printf("*************************************************************************\n");
			printf("Client %d sending below msg to server %d \n", clTracker-2, sTracker+1);
			for (i = 1; i < MSG_SIZE; i++)
				printf("%d ", msg[i]);

			sleep(1);
			printf("\n");

			send(sTracker, msg);
			receive(clTracker, msg);

			printf("*************************************************************************\n");
			printf("Client %d received below msg from server %d \n", clTracker-2, sTracker+1);
			for (i = 1; i < MSG_SIZE; i++)
				printf("%d ", msg[i]);

			printf("\n");
			sleep(1);
		}
	}
	else
	{
		printf("\n**************** No more client ports available ******************\n");
	}
}

void server()
{
	int i, sTracker=0,clTracker=0;
	int msg[10];

	if(sPort >= 3)
	{
		printf("\n**************** No more server ports available ******************\n");
		return;
	}

	sTracker = sPort++;
	while (1)
	{
		receive(sTracker, msg);
		clTracker = msg[0];

		printf("\t*************************************************************************\n");
		printf("\tServer %d received below msg from client %d \n", sTracker+1, clTracker-2);
		printf("\t");
		for (i = 1; i < MSG_SIZE; i++)
		{
			printf("%d ", msg[i]);
			msg[i] *= 3;
		}

		sleep(1);
		printf("\n");

		printf("\t*************************************************************************\n");
		printf("\tServer %d sending below msg to client %d \n", sTracker+1, clTracker-2);
		printf("\t");
		for (i = 1; i < MSG_SIZE; i++)
			printf("%d ", msg[i]);

		printf("\n");

		send(clTracker, msg);

		sleep(1);
	}

}

int main()
{
	printf("*************************************************************************\n");
	printf("* Program creates 3 servers and 5 clients\n* Ports 0 - 2 are used by servers\n* Ports 3 - 99 are used by clients\n* Server multiplies every array element by 3 before sending back to client\n");
	printf("*************************************************************************\n\n");
	createPorts();
	start_thread(client);
	start_thread(client);
	start_thread(client);
	start_thread(client);
	start_thread(client);

	start_thread(server);
	start_thread(server);
	start_thread(server);

	run();
	return 0;
}
