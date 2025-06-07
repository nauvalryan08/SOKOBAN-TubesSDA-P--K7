#include <stdlib.h>
#include "queue.h"

void initQueue(Queue *queue) {
    queue->front = queue->rear = NULL;
    queue->size = 0;
}

void enqueue(Queue *queue, void *data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

void* dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) return NULL;
    Node *temp = queue->front;
    void *data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    free(temp);
    queue->size--;
    return data;
}

void* front(Queue *queue) {
    if (isQueueEmpty(queue)) return NULL;
    return queue->front->data;
}

int isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

void clearQueue(Queue *queue) {
    while (!isQueueEmpty(queue)) {
        free(dequeue(queue)); // asumsi semua data perlu free
    }
}