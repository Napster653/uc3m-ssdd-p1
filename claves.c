#include "messages.h"

#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 0;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);
}

int set_value ()
{
	mqd_t q_server;
	mqd_t q_client;
	struct request req;
	int res;
	struct mq_attr q_attr;
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 1;
	// Value1
	// Value2
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);
}

int get_value ()
{
	mqd_t q_server;
	mqd_t q_client;
	struct request req;
	int res;
	struct mq_attr q_attr;
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 2;
	// Value1
	// Value2
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);
}

int modify_value ()
{
	mqd_t q_server;
	mqd_t q_client;
	struct request req;
	int res;
	struct mq_attr q_attr;
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 3;
	// Value1
	// Value2
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);
}

int delete_key ()
{
	mqd_t q_server;
	mqd_t q_client;
	struct request req;
	int res;
	struct mq_attr q_attr;
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 4;
	// Value1
	// Value2
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);
}

int num_items ()
{
	mqd_t q_server;
	mqd_t q_client;
	struct request req;
	int res;
	struct mq_attr q_attr;
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 5;
	// Value1
	// Value2
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);
}