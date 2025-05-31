#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    void **items;       // Array generik
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Inisialisasi queue
void initQueue(Queue *queue, int capacity);

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