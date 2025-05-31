#include <stdlib.h>
#include "stack.h"

void initStack(Stack *stack, int capacity) {
    stack->items = (void**)malloc(capacity * sizeof(void*));
    stack->top = -1;
    stack->capacity = capacity;
}

void push(Stack *stack, void *data) {
    if(stack->top < stack->capacity - 1) {
        stack->items[++stack->top] = data;
    }
}

void* pop(Stack *stack) {
    if(stack->top >= 0) {
        return stack->items[stack->top--];
    }
    return NULL;
}

void* peek(Stack *stack) {
    if(stack->top >= 0) {
        return stack->items[stack->top];
    }
    return NULL;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void clearStack(Stack *stack) {
    free(stack->items);
    stack->top = -1;
    stack->capacity = 0;
}