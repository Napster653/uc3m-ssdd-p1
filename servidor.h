#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_LENGTH 255
#define MAX_MESSAGES 10

#define TRUE 1
#define FALSE 0

struct Node
{
	int key;
	char value1[255];
	float value2;
	struct Node *next;
};