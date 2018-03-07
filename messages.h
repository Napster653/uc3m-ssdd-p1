#define MAXSIZE 256

struct request
{
	int op;
	int key;
	char* value1;
	float value2;
	float* value3;
	char q_name[MAXSIZE];
};