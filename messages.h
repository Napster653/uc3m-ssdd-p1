#define MAX_VALUE1 255
#define MAX_Q_NAME 128

struct Request
{
	int op;
	int key;
	char * value1;
	float value2;
	char q_name[MAX_Q_NAME];
};

struct Response
{
	int result;
	char * value1;
	float value2;
};