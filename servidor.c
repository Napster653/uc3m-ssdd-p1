#include "messages.h"
#include "servidor.h"
#include "lista.h"

pthread_mutex_t mutex_message;
int message_not_copied = TRUE;
pthread_cond_t cond_message;

void main (void)
{
	mqd_t q_server;

	struct Request req;

	struct mq_attr q_attr;
	q_attr.mq_maxmsg = MAX_MESSAGES;
	q_attr.mq_msgsize = sizeof(struct Request);

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
		mq_receive (q_server, (char*) &req, sizeof(struct Request), 0);
		pthread_create (&thid, &attr, process_req, &req);

		pthread_mutex_lock (&mutex_message);
		while (message_not_copied)
		{
			pthread_cond_wait (&cond_message, &mutex_message);
		}
		message_not_copied = TRUE;
		pthread_mutex_unlock (&mutex_message);
	}
}

void process_req (struct Request *req_arg)
{
	struct Request req_local;
	struct Response res;
	mqd_t q_client;

	pthread_mutex_lock (&mutex_message);

	memcpy ((char*) &req_local, (char*)req_arg, sizeof(struct Request));
	message_not_copied = FALSE;

	pthread_cond_signal (&cond_message);
	pthread_mutex_unlock (&mutex_message);

	if (req_local.op == 0) // init ()
	{
            if(getState()==FALSE) createList();//Si la lista no existe, la creamos
            else{//Si existe, la eliminamos y la volvemos a crear
                removeList();
                createList();
            }
            res->result = 0; //Siempre el resultado es correcto
	}
	else if (req_local.op == 1) // set_value (k, *v1, v2)
	{
            if(getState() == FALSE) res.result = -1; //La lista no existe
            else{
                if(sizeof(req_local.value1 > 255)) res.result = -1; //Value1 demasiado largo
                else{
                    if(add(req_local.key, req_local.value1, req_local.value2) < 0) res.result = -1;//Clave ya registrada
                    else res.result = 0;//Insertado con éxito
                } 
            } 
	}
	else if (req_local.op == 2) // get_value (k, *v1, *v2)
	{
            if(getState() == FALSE) res.result = -1; // No existe la lista
            else{
                Node elem = getNode(req_local->key);
                if(elem == NULL) res.result = -1; //No existe la clave
                else{ //Escribir los valores en los punteros
                    res->value1 = elem.value1;
                    res->value2 = elem.value2;
                    res->result = 0;
                }
            }		
	}
	else if (req_local.op == 3) // modify_value (k, *v1, v2)
	{
            if(sizeof(req_local.value1 > 255))return -1; //Value1 demasiado largo
            else if(getState() == FALSE) res.result = -1; // No existe la lista
            else{
                if(edit(req_local.key, req_local.value1, req_local.value2) < 0) res.result = -1; //La clave no existe
                else res.result = 0; //Modificado con éxito
            }
	}
	else if (req_local.op == 4) // delete_key (k)
	{
		if(getState() == FALSE) res.result = -1; // No existe la lista
		else{
                    if(remove(req_local.key) < 0) res.result = -1; //No existe la clave
                    else res.result = 0; //Eliminado con éxito
                }
	}
	else if (req_local.op == 5) // num_items()
	{
		if(getState() == FALSE) res.result = -1; // No existe la lista
		else res.result = getSize();
	}
	q_client = mq_open (req_local.q_name, O_WRONLY);
	if (q_client == -1)
	{
		perror ("No se puede abrir la cola del cliente");
	}
	else
	{
		mq_send (q_client, (const char*) &res, sizeof(struct Response), 0);
		mq_close (q_client);
	}
	pthread_exit (0);
}