#include "tree.h"

Ptree createTreeNode(void *data, int level) {
    Ptree node = (Ptree)malloc(sizeof(TreeNode));
    node->data = data;
    node->fs = NULL;
    node->nb = NULL;
    node->childCount = 0;
    node->level = level;
    return node;
}

// Tambah anak ke node
void addTreeNodeChild(Ptree parent, Ptree child) {
    if (!parent || !child) return;

    child->level = parent->level + 1;

    if (parent->fs == NULL) {
        //jika parrent belum punya child
        parent->fs = child;
    } else {
        //jika parrent sudah punya child, tambahkan sebagai sibblling dari child nya
        Ptree sibling = parent->fs;
        while (sibling->nb != NULL) {
            sibling = sibling->nb;
        }
        sibling->nb = child;
    }
    parent->childCount++;
}

//=======================//
//       Traversal       //
//=======================//

// Traversal pre-Order (BFS)
// (Root -> Child pertama -> Sibling)
void preOrderTraversal(Ptree root, void (*visit)(void*)) {
    if (!root || !visit) return;

    visit(root->data);
    Ptree child = root->fs;
    while (child != NULL) {
        preOrderTraversal(child, visit);
        child = child->nb;
    }
}

// Traversal In-Order
// (Child pertama -> Root -> sibling)
void inOrderTraversal(Ptree root, void (*visit)(void*)) {
    if (!root || !visit) return;
    
    Ptree child = root->fs;
    if (child) {
        inOrderTraversal(child, visit);   // Rekursif ke child pertama
    }
    
    visit(root->data);                // Proses root
    
    if (child) {
        child = child->nb;
        while (child != NULL) {
            inOrderTraversal(child, visit);  // Rekursif ke sibling
            child = child->nb;
        }
    }
}

// Traversal Post-Order
// (Child pertama -> Sibling -> Root)
void postOrderTraversal(Ptree root, void (*visit)(void*)) {
    if (!root || !visit) return;
    
    Ptree child = root->fs;
    while (child != NULL) {
        postOrderTraversal(child, visit);  // Rekursif ke child
        child = child->nb;                 // Lanjut ke sibling
    }
    
    visit(root->data);                // Proses root
}

//======================//
//== 4. LEVEL-ORDER  ==//
//======================//
// Helper: Enqueue
void enqueue(Queue *q, Ptree treeNode) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Helper: Dequeue
TreeNode* dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    
    QueueNode *temp = q->front;
    Ptree treeNode = temp->treeNode;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return treeNode;
}


// Helper: Proses satu level
void processCurrentLevel(Queue *q, void (*visit)(void*)) {
    if (q->front == NULL) return;
    
    Ptree current = dequeue(q);
    if (current == NULL) return;
    
    visit(current->data);
    
    // Enqueue semua child
    Ptree child = current->fs;
    while (child != NULL) {
        enqueue(q, child);
        child = child->nb;
    }
    
    // Rekursif ke level berikutnya
    processCurrentLevel(q, visit);
}


// Level-order (rekursif dengan queue)
void levelOrderTraversal(Ptree root, void (*visit)(void*)) {
    if (!root || !visit) return;
    
    Queue q = { NULL, NULL };
    enqueue(&q, root);
    processCurrentLevel(&q, visit);
}


//======================================================//




// Cari node (BFS)
Ptree findTreeNode(Ptree root, void *target, boolean (*compare)(void*, void*)) {
    if (!root || !compare) return NULL;
    if (compare(root->data, target)) return root;

    Ptree child = root->fs;
    while (child != NULL) {
        Ptree found =  findTreeNode(child, target, compare);
        if (found) return found;
        child = child->nb;
    }
    return NULL;
}

// Hapus 
void freeTree(Ptree root, void (*freeData)(void*)) {
    if (!root) return;
    Ptree child = root->fs;
    while (child != NULL) {
        Ptree next = child->nb;
        freeTree(child, freeData);
        child = next;
    }
    if (freeData) freeData(root->data);
    free(root); 
}