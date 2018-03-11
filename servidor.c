#include <string.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_MESSAGES 10
#define MAX_CHAR_LENGTH 256
#define TRUE 1
#define FALSE 0
#define MAX_VALUE1 255
#define MAX_Q_NAME 128

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

// DEFINICIÓN DEL NODO DE LA LISTA
struct node
{
	// DATOS
	int key;
	char * value1;
	float value2;
	// Puntero al siguiente elemento de la lista (Singly-linked)
	struct node * next;
};
typedef struct node *Node;

// ATRIBUTOS DE NUESTRA SINGLY-LINKED LIST
Node head; // Primer nodo
int size; // Número de elementos
int active; // active=TRUE --> lista iniciada/creada; active=FALSE --> lista no iniciada/creada

// FUNCIONES DE LA LISTA
int getState ();
int createList ();
Node createNode (int k, char * v1, float v2);
Node getNode (int k);
int addNode (int k, char * v1, float v2);
int removeNode (int k);
int edit (int k, char * v1, float v2);
int removeList ();
int getSize ();
void process_req (struct Request *req_arg);

pthread_mutex_t mutex_message;
pthread_mutex_t mutex_funcion;
int message_not_copied = TRUE;
pthread_cond_t cond_message;

// Función que devuelve el estado actual de la lista (iniciada=TRUE/no iniciada=FALSE)
int getState ()
{
	return active;
}

// Función utilizada para iniciar la lista
int createList ()
{
	size = 0;
	active = TRUE;
	return 1;
}

// Función que devuelve una estructura de nodo con los datos introducidos como args
Node createNode (int k, char * v1, float v2)
{
	Node newNode;
	// Es necesario reservar el espacio necesario para el nodo
	newNode = (Node) malloc (sizeof (struct node));
	newNode->key = k;
	newNode->value1 = v1;
	newNode->value2 = v2;
	newNode->next = NULL;
	return newNode;
}

// Función que busca y devuelve el nodo cuya KEY es la introducida como arg
Node getNode (int k)
{
	Node target = head;

	if (target == NULL) return target;
	else if (target->key == k) return target;
	else
	{
		while (target != NULL)
		{
			if (target->key == k)
			{
				printf ("Get devolviendo %d - %s - %f\n", target->key, target->value1, target->value2);
				return target;
			}
			target = target->next;
		}
	}
	return target; // Si la KEY introducida no está en la lista, devuelve NULL
}

// Función que crea y añade un nodo al inicio de la lista, dados los datos como argumentos
int addNode (int k, char * v1, float v2)
{
	Node check = getNode(k);
	if (check != NULL)
	{
		return -1; // La función devuelve -1 (ERROR) si la clave ya fue registrada
	}
	Node newNode = createNode(k, v1, v2);
	printf ("Nodo creado: %d - %s - %f\n", newNode->key, newNode->value1, newNode->value2);
	if (size > 0)
	{
		printf("Ya hay un nodo en la lista, ahora será el número 2\n");
		newNode->next = head; // La función solo asigna el puntero NEXT si hay algún nodo en la lista
	}
	head = newNode;

	check = head;
	printf("========Ckeckeo========\n");
	while (check != NULL)
	{
		printf ("\t%d\t%s\t%f\n", check->key, check->value1, check->value2);
		check = check->next;
	}

	size++;
	return 1;
}

// Función que elimina un nodo de la lista dada una clave(k) como argumento
int removeNode (int k)
{
	Node check = getNode (k);
	if (check == NULL)
	{
		return -1; // La función devuelve -1(ERROR) si no encuentra la clave k en la lista
	}
	// Para eliminar, el nodo es ignorado dentro de la lista y su espacio es liberado (free)
	if (check == head)
	{
		head = head->next; // Si es el primer elem, solo se cambia el puntero de head al segundo
	}
	else
	{
		Node prev = head;//Si no es el primero, se busca el nodo anterior y se cambian los punteros para ignorarlo
		while (prev->next != check)
		{
			prev = prev->next;
		}
		prev->next = check->next;
	}
	free (check);
	size--;
	return 1;
}

//Función que modifica los valores de un nodo dado su clave y los nuevos datos
int edit (int k, char * v1, float v2)
{
	Node elem = getNode (k);
	if (elem == NULL)
	{
		return -1;//Si la clave no existe (ERROR), la función devuelve -1
	}
	elem->value1 = v1;
	elem->value2 = v2;
	return 1;
}

//Función que resetea y desactiva la lista
int removeList ()
{
    Node target = head;
    while (target != NULL)//Todo el espacio de los elementos de la lista es liberado (free)
    {
        free (target);
        target = target->next;
    }
    //Los atributos son reseteados a sus valores iniciales
    size = 0;
    head = NULL;
    active = FALSE;
    return 1;
}

//El número de elementos se controla con una variable que se incrementa y decrementa cuando se añade o elimina un nodo
int getSize ()
{
    return size;
}

int main (void)
{
	mqd_t q_server;

	struct Request req;

	struct mq_attr q_attr;
	q_attr.mq_maxmsg = MAX_MESSAGES;
	q_attr.mq_msgsize = sizeof(struct Request);

	pthread_attr_t t_attr;
	pthread_t thid;

	if (mq_unlink("/Queue656") == 0)
	{
		printf("Message queue removed\n");
	}

	q_server = mq_open ("/Queue656", O_CREAT|O_RDONLY, 0700, &q_attr);
	if (q_server == -1)
	{
		perror ("Error al crear la cola de servidor");
		//return -1;
	}

	pthread_mutex_init (&mutex_message, NULL);
	pthread_mutex_init (&mutex_funcion, NULL);
	pthread_cond_init (&cond_message, NULL);
	pthread_attr_init (&t_attr);

	pthread_attr_setdetachstate (&t_attr, PTHREAD_CREATE_DETACHED);

	while (TRUE)
	{
		mq_receive (q_server, (char*) &req, sizeof(struct Request), 0);
		printf("Mensaje recibido: ");
		pthread_create (&thid, &t_attr, (void (*))process_req, &req);

		pthread_mutex_lock (&mutex_message);
		while (message_not_copied)
		{
			pthread_cond_wait (&cond_message, &mutex_message);
		}
		message_not_copied = TRUE;
		pthread_mutex_unlock (&mutex_message);
	}
	return 0;
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

	printf("Request recibida:\n");
	printf("\tOp: %d\n", req_local.op);
	printf("\tKey: %d\n", req_local.key);
	printf("\tV1: %s\n", req_local.value1);
	printf("\tV2: %f\n", req_local.value2);


	pthread_mutex_lock (&mutex_funcion);
	switch (req_local.op)
	{
		case 0:	// init
			if (getState() == FALSE) // Si la lista no existe, la creamos
			{
				createList();
			}
			else // Si existe, la eliminamos y la volvemos a crear
			{
				removeList();
				createList();
			}
			res.result = 0; //Siempre el resultado es correcto
			break;
		case 1: // set
			if (getState() == FALSE)
			{
				printf ("La lista no existe\n");
				res.result = -1;
			}
			else
			{
				printf ("Insertando %d - %s - %f\n", req_local.key, req_local.value1, req_local.value2);

				if (addNode (req_local.key, req_local.value1, req_local.value2) < 0)
				{
					res.result = -1;
					printf ("Clave ya registrada\n");
				}
				else
				{
					res.result = 0;
					printf ("Insertado con éxito\n");
				}
			}
			break;
		case 2: // get
			if (getState() == FALSE)
			{
				res.result = -1; // No existe la lista
			}
			else
			{
				Node elem = getNode(req_local.key);
				printf ("Obtenido el nodo %d - %s - %f\n", elem->key, elem->value1, elem->value2);
				if (elem == NULL) //No existe la clave
				{
					res.result = -1;
				}
				else //Escribir los valores en los punteros
				{
					strcpy (res.value1, (const char*) elem->value1);
					res.value2 = elem->value2;
					res.result = 0;
				}
			}
			break;
		case 3:
			if (sizeof (req_local.value1) > 255)
			{
				res.result = -1; //Value1 demasiado largo
			}
			else if (getState() == FALSE)
			{
				res.result = -1; // No existe la lista
			}
			else
			{
				if (edit (req_local.key, req_local.value1, req_local.value2) < 0)
				{
					res.result = -1; //La clave no existe
				}
				else
				{
					res.result = 0; //Modificado con éxito
				}
			}
			break;
		case 4:
			if (getState() == FALSE)
			{
				res.result = -1; // No existe la lista
			}
			else
			{
				if (removeNode (req_local.key) < 0)
				{
					res.result = -1; //No existe la clave
				}
				else
				{
					res.result = 0; //Eliminado con éxito
				}
			}
			break;
		case 5:
			if (getState() == FALSE)
			{
				res.result = -1; // No existe la lista
			}
			else
			{
				res.result = getSize();
			}
			break;
	}
	pthread_mutex_unlock (&mutex_funcion);
	printf("Operación procesada\n");
	q_client = mq_open (req_local.q_name, O_WRONLY);
	printf("Cola de cliente abierta: %s\n", req_local.q_name);
	if (q_client == -1)
	{
		perror ("No se puede abrir la cola del cliente");
	}
	else
	{
		if (mq_send (q_client, (const char*) &res, sizeof(struct Response), 0) != 0)
			perror("mq_send");
		printf("Respuesta enviada\n\n");
		mq_close (q_client);
	}
	pthread_exit (0);
}
