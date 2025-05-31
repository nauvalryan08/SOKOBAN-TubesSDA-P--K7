#include <stdlib.h>
#include "queue.h"  // Menggunakan queue untuk BFS
#include "tree.h"

TreeNode* createNode(void *data, int initialCapacity) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->parent = NULL;
    node->children = (TreeNode**)malloc(initialCapacity * sizeof(TreeNode*));
    node->childCount = 0;
    node->capacity = initialCapacity;
    return node;
}

void addChild(TreeNode *parent, TreeNode *child) {
    if(parent->childCount == parent->capacity) {
        // Perbesar kapasitas
        parent->capacity *= 2;
        parent->children = (TreeNode**)realloc(parent->children, 
                                parent->capacity * sizeof(TreeNode*));
    }
    parent->children[parent->childCount++] = child;
    child->parent = parent;
}

void levelOrderTraversal(TreeNode *root, void (*visit)(void*)) {
    if(!root) return;
    
    Queue q;
    initQueue(&q, 50);
    enqueue(&q, root);
    
    while(!isQueueEmpty(&q)) {
        TreeNode *current = (TreeNode*)dequeue(&q);
        visit(current->data);
        
        for(int i = 0; i < current->childCount; i++) {
            enqueue(&q, current->children[i]);
        }
    }
    clearQueue(&q);
}

TreeNode* findNode(TreeNode *root, void *target, int (*compare)(void*, void*)) {
    if(!root) return NULL;
    
    Queue q;
    initQueue(&q, 50);
    enqueue(&q, root);
    
    while(!isQueueEmpty(&q)) {
        TreeNode *current = (TreeNode*)dequeue(&q);
        if(compare(current->data, target) == 0) {
            clearQueue(&q);
            return current;
        }
        
        for(int i = 0; i < current->childCount; i++) {
            enqueue(&q, current->children[i]);
        }
    }
    clearQueue(&q);
    return NULL;
}

void freeSubtree(TreeNode *node) {
    if(!node) return;
    
    for(int i = 0; i < node->childCount; i++) {
        freeSubtree(node->children[i]);
    }
    free(node->children);
    free(node);
}