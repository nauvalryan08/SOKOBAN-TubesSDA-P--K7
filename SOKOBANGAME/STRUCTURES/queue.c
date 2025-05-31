#include <stdlib.h>
#include "queue.h"

void initQueue(Queue *queue, int capacity) {
    queue->items = (void**)malloc(capacity * sizeof(void*));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
}

void enqueue(Queue *queue, void *data) {
    if(queue->size < queue->capacity) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->items[queue->rear] = data;
        queue->size++;
    }
}

void* dequeue(Queue *queue) {
    if(queue->size > 0) {
        void *item = queue->items[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return item;
    }
    return NULL;
}

void* front(Queue *queue) {
    if(queue->size > 0) {
        return queue->items[queue->front];
    }
    return NULL;
}

int isQueueEmpty(Queue *queue) {
    return queue->size == 0;
}

void clearQueue(Queue *queue) {
    free(queue->items);
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = 0;
}