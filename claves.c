#include "messages.h"

#include <string.h>
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
	struct Request req;
	struct Response res;
	struct mq_attr q_attr;
	q_attr.mq_maxmsg = 1;
	q_attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 0;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);

	return res.result;
}

int set_value (int key, char* value1, float value2)
{
	mqd_t q_server;
	mqd_t q_client;
	struct Request req;
	struct Response res;
	struct mq_attr q_attr;
	q_attr.mq_maxmsg = 1;
	q_attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 1;
	req.key = key;
	strcpy (req.value1, (const char*) value1);
	req.value2 = value2;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);

	return res.result;
}

int get_value (int key, char* value1, float* value2)
{
	mqd_t q_server;
	mqd_t q_client;
	struct Request req;
	struct Response res;
	struct mq_attr q_attr;
	q_attr.mq_maxmsg = 1;
	q_attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 2;
	req.key = key;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);

	if (res.result == 0)
	{
		strcpy (value1, (const char*) res.value1);
		*value2 = res.value2;
		return 0;
	}
	else
	{
		return -1;
	}
}

int modify_value (int key, char* value1, float value2)
{
	mqd_t q_server;
	mqd_t q_client;
	struct Request req;
	struct Response res;
	struct mq_attr q_attr;
	q_attr.mq_maxmsg = 1;
	q_attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 3;
	req.key = key;
	strcpy (req.value1, (const char*) value1);
	req.value2 = value2;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);

	return res.result;
}

int delete_key (int key)
{
	mqd_t q_server;
	mqd_t q_client;
	struct Request req;
	struct Response res;
	struct mq_attr q_attr;
	q_attr.mq_maxmsg = 1;
	q_attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 4;
	req.key = key;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);

	return res.result;
}

int num_items ()
{
	mqd_t q_server;
	mqd_t q_client;
	struct Request req;
	struct Response res;
	struct mq_attr q_attr;
	q_attr.mq_maxmsg = 1;
	q_attr.mq_msgsize = sizeof(int);

	char name[128];
	sprintf(name, "/QueueClient-%d", getpid());
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);
	q_server = mq_open ("/Queue656", O_WRONLY);

	req.op = 5;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(int), 0);

	mq_close (q_server);
	mq_close (q_client);
	mq_unlink ((const char*) name);

	return res.result;
}