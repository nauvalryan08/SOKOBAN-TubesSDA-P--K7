#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initList(DoublyLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void insertLast(DoublyLinkedList *list, void *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if(list->head == NULL) {
        newNode->prev = NULL;
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void deleteAt(DoublyLinkedList *list, int position) {
    if(position < 0 || position >= list->size) return;
    
    Node *current = list->head;
    for(int i = 0; i < position; i++) {
        current = current->next;
    }
    
    if(current->prev) current->prev->next = current->next;
    else list->head = current->next;
    
    if(current->next) current->next->prev = current->prev;
    else list->tail = current->prev;
    
    free(current);
    list->size--;
}

void* getAt(DoublyLinkedList *list, int position) {
    if(position < 0 || position >= list->size) return NULL;
    
    Node *current = list->head;
    for(int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->data;
}

void printList(DoublyLinkedList *list, void (*printData)(void*)) {
    Node *current = list->head;
    while(current != NULL) {
        printData(current->data);
        current = current->next;
    }
}

void clearList(DoublyLinkedList *list) {
    Node *current = list->head;
    while(current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}