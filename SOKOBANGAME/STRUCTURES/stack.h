#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

//=======================//
//=> STRUCT DEFINISION <=//
//=======================//


// Tipe data generik untuk stack (bisa diganti sesuai kebutuhan)
typedef void* StackItem;

// Node untuk linked list
typedef struct StackNode {
    StackItem data;
    struct StackNode* next;
} StackNode;

// Struktur stack
typedef struct {
    StackNode* top;  // Pointer ke elemen teratas
    int size;       // Jumlah elemen
} Stack;


//======================//
//=> LOGIC DEFINISION <=//
//======================//

// Inisialisasi stack kosong
void stack_init(Stack* stack);

// Cek apakah stack kosong
bool stack_isEmpty(const Stack* stack);

// Push elemen ke stack
void stack_push(Stack* stack, StackItem item);

// Pop elemen dari stack
StackItem stack_pop(Stack* stack);

// Peek elemen teratas tanpa menghapus
StackItem stack_peek(const Stack* stack);

// Hapus semua elemen
void stack_clear(Stack* stack);

// Dapatkan ukuran stack
int stack_size(const Stack* stack);

#endif