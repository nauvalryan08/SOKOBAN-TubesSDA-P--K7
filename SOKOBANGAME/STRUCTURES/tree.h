#ifndef TREE_H
#define TREE_H

#include "../UTILS/include/boolean.h" 
#include "../GAMEPLAY/ARENA_LOGIC/Level.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklarasi enum
typedef enum {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_LEVELDATA,
    TYPE_PLAYDATA,
}DataType;

typedef struct TreeNode * Ptree; 
typedef struct TreeNode {
    void *data;          // Data generik (Level, Leaderboard, dll)
    DataType Type;      // Tipe data yang digunakan
    Ptree fs; // Pointer ke child pertama (first son)
    Ptree nb; // Pointer ke sibling berikutnya (next brother)
    int childCount;      // Jumlah child
    int level;          // Kedalaman node 
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
}QueueTree;


// Buat node baru
Ptree createTreeNode(void *data, DataType type);

// Tambah anak ke node
void addTreeNodeChild(Ptree parent, Ptree child);


// Traversal level-order (BFS)
void preOrderTraversal(Ptree root, void (*visit)(void*));
void inOrderTraversal(Ptree root, void (*visit)(void*));
void postOrderTraversal(Ptree root, void (*visit)(void*));
void levelOrderTraversal(Ptree root, void (*visit)(void*));

// Data comparising
Boolean compareData (void *data1, void *data2, DataType type);

Boolean compareDataID (void *data1, void *data2);
Boolean compareDataINT (void *data1, void *data2);
Boolean compareDataSTRING (void *data1, void *data2);
Boolean compareDataCHAR (void *data1, void *data2);



// Cari node (BFS)
Ptree findTreeNode(Ptree root, void *target, Boolean (*compare)(void*, void*));

// cari parent dari salah satu node
Ptree findParentNode(Ptree root, void *target, Boolean (*compare)(void *, void *));

// Hapus 
void freeTree(Ptree root, void (*freeData)(void*, DataType));


#endif