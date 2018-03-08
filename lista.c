#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//Función que devuelve el estado actual de la lista (iniciada=TRUE/no iniciada=FALSE)
int getState ()
{
	return active;
}

//Función utilizada para iniciar la lista
int createList ()
{
	size = 0;
	active = TRUE;
	return 1;
}

//Función que devuelve una estructura de nodo con los datos introducidos como args
Node createNode (int k, char * v1, float v2)
{
	Node newNode;
	//Es necesario reservar el espacio necesario para el nodo
	newNode = (Node) malloc (sizeof (struct node)); 
	newNode->key = k;
	newNode->value1 = v1;
	newNode->value2 = v2;
	newNode->next = NULL;
	return newNode;
}

//Función que busca y devuelve el nodo cuya KEY es la introducida como arg
Node getNode (int k)
{
	Node target = head;
	while (target->key != k && target != NULL)
	{
		target = target->next;
	}
	return target;//Si la KEY introducida no está en la lista, devuelve NULL
}

//Función que crea y añade un nodo al inicio de la lista, dados los datos como argumentos
int addNode (int k, char * v1, float v2)
{
	Node check = getNode(k);
	if (check != NULL)
	{
		return -1;//La función devuelve -1 (ERROR) si la clave ya fue registrada
	}
	Node new = createNode(k, v1, v2);
	if (size > 0)
	{
		new->next = head;//La función solo asigna el puntero NEXT si hay algún nodo en la lista
	}
	head = new;
	size++;
	return 1;
}

//Función que elimina un nodo de la lista dada una clave(k) como argumento
int removeNode (int k)
{
	Node check = getNode (k);
	if (check == NULL)
	{
		return -1;//La función devuelve -1(ERROR) si no encuentra la clave k en la lista
	}
	//Para eliminar, el nodo es ignorado dentro de la lista y su espacio es liberado (free)
	if (check == head)
	{
		head = head->next;//Si es el primer elem, solo se cambia el puntero de head al segundo
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