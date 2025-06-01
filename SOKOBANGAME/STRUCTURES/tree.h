#ifndef TREE_H
#define TREE_H

#include "../UTILS/include/boolean.h" 
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode * Ptree; 
typedef struct TreeNode {
    void *data;          // Data generik (Level, Leaderboard, dll)
    Ptree fs; // Pointer ke child pertama (first son)
    Ptree nb; // Pointer ke sibling berikutnya (next brother)
    int childCount;      // Jumlah child
    int level;          // Kedalaman node (opsional)
} TreeNode;

typedef struct {
    Ptree root;
} Tree;

typedef struct QueueNode {
    Ptree treeNode;
    struct QueueNode * next;
}QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
}Queue;


// Buat node baru
Ptree createTreeNode(void *data, int level);

// Tambah anak ke node
void addTreeNodeChild(Ptree parent, Ptree child);


// Traversal level-order (BFS)
void preOrderTraversal(Ptree root, void (*visit)(void*));
void inOrderTraversal(Ptree root, void (*visit)(void*));
void postOrderTraversal(Ptree root, void (*visit)(void*));
void levelOrderTraversal(Ptree root, void (*visit)(void*));


// Cari node (BFS)
Ptree findTreeNode(Ptree root, void *target, boolean (*compare)(void*, void*));

// Hapus 
void freeTree(Ptree root, void (*freeData)(void*));

#endif