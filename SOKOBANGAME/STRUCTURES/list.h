#ifndef LIST_H
#define LIST_H

typedef struct TableItems {
    void *data;         // Pointer generik untuk menyimpan berbagai tipe data
    struct TableItems *next;
    struct TableItems *prev;
} TableItems;

typedef struct {
    TableItems *head;
    TableItems *tail;
    int size;
} DoublyLinkedList;

// Inisialisasi list
void initList(DoublyLinkedList *list);

// Tambah elemen di akhir
void insertLast(DoublyLinkedList *list, void *data);

// Hapus elemen di posisi tertentu
void deleteAt(DoublyLinkedList *list, int position);

// Akses elemen di posisi tertentu
void* getAt(DoublyLinkedList *list, int position);

// Cetak list (membutuhkan fungsi print khusus untuk tipe data)
void printList(DoublyLinkedList *list, void (*printData)(void*));

// Hapus semua elemen
void clearList(DoublyLinkedList *list);

#endif