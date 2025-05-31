#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    void *data;             // Data generik
    struct TreeNode *parent;
    struct TreeNode **children;  // Array pointer anak
    int childCount;
    int capacity;
} TreeNode;

typedef struct {
    TreeNode *root;
} Tree;

// Buat node baru
TreeNode* createNode(void *data, int initialCapacity);

// Tambah anak ke node
void addChild(TreeNode *parent, TreeNode *child);

// Traversal level-order (BFS)
void levelOrderTraversal(TreeNode *root, void (*visit)(void*));

// Cari node (BFS)
TreeNode* findNode(TreeNode *root, void *target, int (*compare)(void*, void*));

// Hapus subtree
void freeSubtree(TreeNode *node);

#endif