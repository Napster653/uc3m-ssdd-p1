#include "messages.h"

#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int init ()
{
	mqd_t q_server;
	mqd_t q_client;
	struct request req;
	int res;
	struct mq_attr q_attr;
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/")
	q_client = mq_open ("/QueueClient-%d", O_CREAT|O_RDONLY, 0700, &q_attr); // Nombre TBD
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 0;
	// Value1
	// Value2
	strcpy (req.q_name, ""); // Nombre TBD

	mq_send (q_server, (const char*) &req, sizeof(struct request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink (""); // Nombre TBD
}

int set_value ()
{

}

int get_value ()
{

}

int modify_value ()
{

}

int delete_key ()
{

}

int num_items ()
{

}