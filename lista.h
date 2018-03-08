#define MAX_CHAR_LENGTH 255
#define TRUE 1
#define FALSE 0

struct node {
    int key;
    char * value1;
    float value2;
    struct node * next;
};
typedef struct node *Node;


Node head;
int size;
int active;

int getState();
int createList();
Node createNode(int k, char * v1, float v2);
Node getNode(int k);
int addNode(int k, char * v1, float v2);
int removeNode(int k);
int edit(int k, char * v1, float v2);
int removeList();
int getSize();

