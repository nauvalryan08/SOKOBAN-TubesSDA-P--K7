#include "tree.h"

Ptree createTreeNode(void *data, DataType type) {
  Ptree node = (Ptree)malloc(sizeof(TreeNode));
  node->data = data;
  node->Type = type;
  node->fs = NULL;
  node->nb = NULL;
  node->childCount = 0;
  node->level = 0;
  return node;
}

// Tambah anak ke node
void addTreeNodeChild(Ptree parent, Ptree child) {
  if (!parent || !child)
    return;

  child->level = parent->level + 1;

  if (parent->fs == NULL) {
    // jika parrent belum punya child
    parent->fs = child;
  } else {
    // jika parrent sudah punya child, tambahkan sebagai sibblling dari child
    // nya
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
void preOrderTraversal(Ptree root, void (*visit)(void *)) {
  if (!root || !visit)
    return;

  visit(root->data);
  Ptree child = root->fs;
  while (child != NULL) {
    preOrderTraversal(child, visit);
    child = child->nb;
  }
}

// Traversal In-Order
// (Child pertama -> Root -> sibling)
void inOrderTraversal(Ptree root, void (*visit)(void *)) {
  if (!root || !visit)
    return;

  Ptree child = root->fs;
  if (child) {
    inOrderTraversal(child, visit); // Rekursif ke child pertama
  }

  visit(root->data); // Proses root

  if (child) {
    child = child->nb;
    while (child != NULL) {
      inOrderTraversal(child, visit); // Rekursif ke sibling
      child = child->nb;
    }
  }
}

// Traversal Post-Order
// (Child pertama -> Sibling -> Root)
void postOrderTraversal(Ptree root, void (*visit)(void *)) {
  if (!root || !visit)
    return;

  Ptree child = root->fs;
  while (child != NULL) {
    postOrderTraversal(child, visit); // Rekursif ke child
    child = child->nb;                // Lanjut ke sibling
  }

  visit(root->data); // Proses root
}

//======================//
//== 4. LEVEL-ORDER  ==//
//======================//
// Helper: Enqueue
void tenqueue(QueueTree *q, Ptree treeNode) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
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
TreeNode *tdequeue(QueueTree *q) {
  if (q->front == NULL)
    return NULL;

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
void processCurrentLevel(QueueTree *q, void (*visit)(void *)) {
  if (q->front == NULL)
    return;

  Ptree current = tdequeue(q);
  if (current == NULL)
    return;

  visit(current->data);

  // EnqueueTree semua child
  Ptree child = current->fs;
  while (child != NULL) {
    tenqueue(q, child);
    child = child->nb;
  }

  // Rekursif ke level berikutnya
  processCurrentLevel(q, visit);
}

// Level-order (rekursif dengan queue)
void levelOrderTraversal(Ptree root, void (*visit)(void *)) {
  if (!root || !visit)
    return;

  QueueTree q = {NULL, NULL};
  tenqueue(&q, root);
  processCurrentLevel(&q, visit);
}

//======================================================//
// Fungsi pembantu untuk membandingkan kesamaan dua data
boolean compareData (void *data1, void *data2, DataType type) {
  switch (type) {
    case TYPE_INT :
      return *((int*) data1) == *((int*)data2);
    case TYPE_CHAR :
      return *((char*) data1) == *((char*)data2);
    case TYPE_STRING :
      return strcmp((char*) data1, (char*)data2) == 0;
    case TYPE_LEVELDATA :
      LevelData *temp1 = (LevelData *) data1;
      LevelData *temp2 = (LevelData *) data2;
      return strcmp(temp1->level_id, temp2->level_id) == 0;
  }
}

boolean compareDataID (void *data1, void *data2) { return compareData(data1, data2, TYPE_LEVELDATA);}
boolean compareDataINT (void *data1, void *data2) { return compareData(data1, data2, TYPE_INT);}
boolean compareDataSTRING (void *data1, void *data2) { return compareData(data1, data2, TYPE_STRING);}
boolean compareDataCHAR (void *data1, void *data2) { return compareData(data1, data2, TYPE_CHAR);}


// Cari node (BFS)
Ptree findTreeNode(Ptree root, void *target,
                   boolean (*compare)(void *, void *)) {
  if (!root || !compare)
    return NULL;
  if (compare(root->data, target))
    return root;

  Ptree child = root->fs;
  while (child != NULL) {
    Ptree found = findTreeNode(child, target, compare);
    if (found)
      return found;
    child = child->nb;
  }
  return NULL;
}

// Cari parent dari suatu Node
Ptree findParentNode(Ptree root, void *target, boolean (*compare)(void *, void *)) {
  if (!root || !compare) {
    return NULL;
  }
  if (compare(root->data, target))
  return NULL;    // Target merupakan root sehingga tidak ada parrent

  Ptree child = root->fs;
  while (child != NULL) {
    if (compareDataID(child->data, target)) {
      return root;
    }
    Ptree found = findParentNode(child, target, compare);
    if (found) return found;

    child = child->nb;
  }

  return NULL;

}


// Hapus
void freeTree(Ptree root, void (*freeData)(void *)) {
  if (!root)
    return;
  Ptree child = root->fs;
  while (child != NULL) {
    Ptree next = child->nb;
    freeTree(child, freeData);
    child = next;
  }
  if (freeData)
    freeData(root->data);
  free(root);
}
