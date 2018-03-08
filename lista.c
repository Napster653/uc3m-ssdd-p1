#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct Node
{
	int key;
	char value1[256];
	float value2;
	struct Node* next;
};
typedef struct Node lista_num;

struct elementoLista
{
	int key;
	char value1[256];
	float value2;
	struct elementoLista* next;
};
typedef struct elementoLista* TipoLista;

int init (ListType *l);
int set (TipoLista *l, int key, char* value1, float value2);
int get (ListType *l, int key);
int modify (ListType *l, struct Triplet trip);
int delete (ListType  *l, int key);
int num (ListType *l);

int init (ListType *l)
{

}

int set (TipoLista *l, int key, char *value1, float value2) {
	TipoLista p1, p2;
	p1 = *l;
	if (p1 == NULL)
	{
		p1 = (struct elementoLista *) malloc (sizeof (struct elementoLista));
		p1->key = key;
		strcpy (p1->value1, (const char*) value1);
		p1->next = NULL;
		*l = p1;
	}
	else
	{
		while (p1->next != NULL)
		{
			p1 = p1->next;
		}
		p2 = (struct elementoLista *) malloc (sizeof (struct elementoLista));
		p2->num = num;
		p2->next = NULL;
		p1->next = p2;
	}
	return 0;
}

int get (TipoLista *l, )

