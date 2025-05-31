#ifndef STACK_H
#define STACK_H

typedef struct {
    void **items;       // Array generik
    int top;
    int capacity;
} Stack;

// Inisialisasi stack
void initStack(Stack *stack, int capacity);

// Tambah elemen di atas
void push(Stack *stack, void *data);

// Hapus elemen di atas
void* pop(Stack *stack);

// Lihat elemen teratas tanpa menghapus
void* peek(Stack *stack);

// Cek apakah stack kosong
int isEmpty(Stack *stack);

// Bersihkan stack
void clearStack(Stack *stack);

#endif