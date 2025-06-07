#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    void* data;
    struct Node * next;
}Node;

typedef struct {
    Node *front;
    Node *rear;
    int size;
} Queue;

// Inisialisasi queue
void initQueue(Queue *queue);

// Tambah elemen di belakang
void enqueue(Queue *queue, void *data);

// Hapus elemen di depan
void* dequeue(Queue *queue);

// Lihat elemen terdepan tanpa menghapus
void* front(Queue *queue);

// Cek apakah queue kosong
int isQueueEmpty(Queue *queue);

// Bersihkan queue
void clearQueue(Queue *queue);

#endif