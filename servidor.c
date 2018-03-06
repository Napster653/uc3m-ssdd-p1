#include "servidor.h"

pthread_mutex_t mutex_message;
int message_not_copied = TRUE;
pthread_cond_t cond_message;

void main (void)
{
	mqd_t q_server;

	struct request message;

	struct mq_attr q_attr;
	q_attr.mq_maxmsg = MAX_MESSAGES;
	q_attr.mq_msgsize = sizeof(struct request);

	pthread_attr_t t_attr;
	pthread_t thid;

	q_server = mq_open ("/Queue656", O_CREAT|O_RDONLY, 0700, &q_attr);
	if (q_server == -1)
	{
		perror ("Error al crear la cola de servidor");
		return -1;
	}

	pthread_mutex_init (&mutex_message, NULL);
	pthread_cond_init (&cond_message, NULL);
	pthread_attr_init (&t_attr);

	pthread_attr_setdetachstate (&t_attr, PTHREAD_CREATE_DETACHED);

	while (TRUE)
	{
		mq_receive (q_server, (char*) &message, sizeof(struct request), 0);
		pthread_create (&thid, &attr, process_message, &message);

		pthread_mutex_lock (&mutex_message);
		while (message_not_copied)
		{
			pthread_cond_wait (&cond_message, &mutex_message);
		}
		message_not_copied = TRUE;
		pthread_mutex_unlock (&mutex_message);
	}
}

void process_message (struct request *message_arg)
{
	struct request message_local;
	mqd_t q_client;
	int result;

	pthread_mutex_lock (&mutex_message);

	memcpy ((char*) &message_local, (char*)message_arg, sizeof(struct request));
	message_not_copied = FALSE;

	pthread_cond_signal (&cond_message);
	pthread_mutex_unlock (&mutex_message);

	if (message_local.op == 0) // init()
	{
		// Existe la cola?
		// Eliminar la cola de tripletas si existe
		// Crear cola de tripletas
		// return en q_client
	}
	else if (message_local.op == 1) // set_value (k, *v1, v2)
	{
		// Existe la cola?
		// Existe la clave?
		// Comprobar value1 y value2
		// queue(message_local.key, message_local.value1, message_local.value2)
		// return en q_client
	}
	else if (message_local.op == 2) // get_value (k, *v1, *v2)
	{
		// Existe la cola?
		// Existe la clave?
		// Escribir los valores en los punteros
		// return en q_client
	}
	else if (message_local.op == 3) // modify_value (k, *v1, v2)
	{
		// Existe la cola?
		// Existe la clave?
		// Modificar valores
		// return en q_client
	}
	else if (message_local.op == 4) // delete_key (k)
	{
		// Existe la cola?
		// Existe la clave?
		// Borrar la clave
		// return en q_client
	}
	else if (message_local.op == 5) // num_items()
	{
		// Existe la cola?
		// Contar elementos
		// return en q_client
	}
	q_client = mq_open(message_local.q_name, O_WRONLY);
	if (q_client == -1)
	{
		perror ("No se puede abrir la cola del cliente");
	}
	else
	{
		mq_send (q_client, (const char*) &result, sizeof(int), 0);
		mq_close (q_client);
	}
	pthread_exit(0);
}