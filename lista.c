#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int getState(){
    return active;
}

int createList(){
    size = 0;
    active = TRUE;
    return 1;
}

Node createNode(int k, char * v1, float v2){
    Node newNode;
    newNode = (Node) malloc(sizeof (struct node));
    newNode->key = k;
    newNode->value1 = v1;
    newNode->value2 = v2;
    newNode->next = NULL;
    return newNode;
}

Node getNode(int k){
    Node target = head;
    while(target->key != k && target != NULL) target = target->next;
    return target;
}
int addNode(int k, char * v1, float v2){
    Node check = getNode(k);
    if(check != NULL) return -1;
    Node new = createNode(k, v1, v2);
    if(size > 0) new->next = head;
    head = new;
    size++;
    return 1;
}

int removeNode(int k){
    Node check = getNode(k);
    if(check == NULL) return -1;
    if(check == head) head = head->next;          
    else{
        Node prev = head;
        while(prev->next != check) prev = prev->next;
        prev->next = check->next;
    }
    free(check); 
    size--;
    return 1;   
}

int edit(int k, char * v1, float v2){
    Node elem = getNode(k);
    if(elem == NULL) return -1;
    elem->value1 = v1;
    elem->value2 = v2;
    return 1;
}

int removeList(){
    Node target = head;
    while(target != NULL){
        free(target);
        target = target->next;
    }
    size = 0;
    head = NULL;
    active = FALSE;
    return 1;
}

int getSize(){
    return size;
}