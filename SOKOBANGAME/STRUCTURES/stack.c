#include "stack.h"
#include <stdlib.h>

void stack_init(Stack* stack) {
    stack->top = NULL;
    stack->size = 0;
}

bool stack_isEmpty(const Stack* stack) {
    return stack->top == NULL;
}

void stack_push(Stack* stack, StackItem item) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = item;
    newNode->next = stack->top;  
    stack->top = newNode;        
    stack->size++;
}

StackItem stack_pop(Stack* stack) {
    if (stack_isEmpty(stack)) {
        return NULL;  
    }

    StackNode* temp = stack->top;
    StackItem poppedItem = temp->data;
    stack->top = temp->next;  
    free(temp);               
    stack->size--;

    return poppedItem;
}

StackItem stack_peek(const Stack* stack) {
    if (stack_isEmpty(stack)) {
        return NULL;
    }
    return stack->top->data;
}

void stack_clear(Stack* stack) {
    while (!stack_isEmpty(stack)) {
        stack_pop(stack);
    }
}

int stack_size(const Stack* stack) {
    return stack->size;
}