#define MAX_CHAR_LENGTH 255
#define TRUE 1
#define FALSE 0

typedef struct{
    int key;
    char value1[MAX_CHAR_LENGTH];
    float value2;
    Node * next;
} Node;


Node head;
int size;
int active;

int getState();
int createList();
Node createNode(int k, char * v1, float v2);
int getNode(int k);
int add(int k, char * v1, float v2);
int remove(int k);
int edit(int k, char * v1, float v2);
int removeList();
int getSize();

