#include <string.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

mqd_t q_client;
mqd_t q_server;

char name[128];


struct Request
{
	int op;
	int key;
	char value1[256];
	float value2;
	char q_name[256];
};

struct Response
{
	int result;
	char value1[256];
	float value2;
};

int closeQueue ()
{
	mq_close (q_client);
	mq_unlink ((const char*) name);
	return 0;
}

int init ()
{
	struct Request req;
	struct Response res;
	struct mq_attr q_attr;
	q_attr.mq_maxmsg = 10;
	q_attr.mq_msgsize = sizeof(struct Response);

	sprintf(name, "/QueueClient-%d", getpid());
	
	printf("%s\n", name);
	q_server = mq_open ("/Queue656", O_WRONLY);
	if (q_server == -1)
	{
		perror("mq_open");
	}
	q_client = mq_open ((const char*) name, O_CREAT|O_RDONLY, 0700, &q_attr);

	req.op = 0;
	strcpy (req.q_name, (const char*) name);

	if (mq_send (q_server, (const char*) &req, sizeof(struct Request), 0) != 0)
		perror("mq_send");
	printf("Mensaje enviado\n");
	mq_receive (q_client, (char*) &res, sizeof(struct Response), 0);
	printf("Mensaje recibido\n");

	return res.result;
}

int set_value (int key, char* value1, float value2)
{
	struct Request req;
	struct Response res;

	printf("op\n");
	req.op = 1;
	printf("key\n");
	req.key = key;
	printf("value1\n");
	strcpy (req.value1, (const char*) value1);
	printf("value2\n");
	req.value2 = value2;
	printf("qname\n");
	strcpy (req.q_name, (const char*) name);
	printf("valores dados\n");

	if (mq_send (q_server, (const char*) &req, sizeof(struct Request), 0) != 0)
		perror("mq_send");
	mq_receive (q_client, (char*) &res, sizeof(struct Response), 0);

	return res.result;
}

int get_value (int key, char* value1, float* value2)
{
	struct Request req;
	struct Response res;

	req.op = 2;
	req.key = key;
	strcpy (req.q_name, (const char*) name);

	if (mq_send (q_server, (const char*) &req, sizeof(struct Request), 0) != 0)
		perror("mq_send");
	mq_receive (q_client, (char*) &res, sizeof(struct Response), 0);

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
	struct Request req;
	struct Response res;

	req.op = 3;
	req.key = key;
	strcpy (req.value1, (const char*) value1);
	req.value2 = value2;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(struct Response), 0);

	return res.result;
}

int delete_key (int key)
{
	struct Request req;
	struct Response res;

	req.op = 4;
	req.key = key;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(struct Response), 0);

	return res.result;
}

int num_items ()
{
	struct Request req;
	struct Response res;

	req.op = 5;
	strcpy (req.q_name, (const char*) name);

	mq_send (q_server, (const char*) &req, sizeof(struct Request), 0);
	mq_receive (q_client, (char*) &res, sizeof(struct Response), 0);

	return res.result;
}