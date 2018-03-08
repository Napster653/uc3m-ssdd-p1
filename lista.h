#define MAX_CHAR_LENGTH 255
#define TRUE 1
#define FALSE 0

// DEFINICIÓN DEL NODO DE LA LISTA
struct node
{
	// DATOS
	int key;
	char * value1;
	float value2;
	// Puntero al siguiente elemento de la lista (Singly-linked)
	struct node * next;
};
typedef struct node *Node;

// ATRIBUTOS DE NUESTRA SINGLY-LINKED LIST
Node head; // Primer nodo
int size; // Número de elementos
int active; // active=TRUE --> lista iniciada/creada; active=FALSE --> lista no iniciada/creada

// FUNCIONES DE LA LISTA
int getState ();
int createList ();
Node createNode (int k, char * v1, float v2);
Node getNode (int k);
int addNode (int k, char * v1, float v2);
int removeNode (int k);
int edit (int k, char * v1, float v2);
int removeList ();
int getSize ();
