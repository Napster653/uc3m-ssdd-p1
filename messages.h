#define MAXSIZE 256

struct request
{
	int op;
	char *value1;
	float value2;
	char q_name[MAXSIZE];
};