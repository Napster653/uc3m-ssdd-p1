#define MAX_CHAR_LENGTH 255

struct Request
{
	int op;
	int key;
	char value1[MAX_CHAR_LENGTH];
	float value2;
	float* value3;
	char q_name[MAX_CHAR_LENGTH];
};