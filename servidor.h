#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_LENGTH 255

struct Node
{
	int key;
	char value1[255];
	float value2;
	struct Node *next;
};