#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


Node head;
int size = 0;

Node createNode(int k, char * v1, float v2){
    Node temp;
    temp = (Node) malloc(sizeof struct Node);
    temp->key = k;
    temp->value1 = v1;
    temp->value2 = v2;
    temp->next = NULL;
    return temp;
}

int getNode(int k){
    Node target = head;
    while(target.key != k && target != NULL) target = target.next;
    return target;
}
int add(int k, char * v1, float v2){
    Node check = getNode(k);
    if(check != NULL) return -1;
    Node new = createNode(k, v1, v2);
    if(size > 0) new->next = head;
    head = new;
    size++;
    return 1;
}

int remove(int k){
    Node check = getNode(k);
    if(check == NULL) return -1;
    if(check == head) head = head.next;          
    else{
        Node prev = head;
        while(prev.next != check) prev = prev.next;
        prev->next = check.next;
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

int removeAll(){
    Node target = head;
    while(target != NULL){
        free(target);
        target = target.next;
    }
    size = 0;
    return 1;
}

int getSize(){
    return size;
}