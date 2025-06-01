#ifndef TREECHAPTER_H
#define TREECHAPTER_H

#include "../../UTILS/include/boolean.h"
#include "../../STRUCTURES/tree.h"
#include "Level.h"

//================================================//
//==>  Struct TREE CHAPTER UNTUK GAME SOKOBAN  <==//
//================================================//
/* {Sopian} */

//===> Queue of Tree
typedef struct ChapterNode * Pchapter;
typedef struct ChapterNode{
    const char *chapter_id;      // ID chapter
    const char *chapter_name;    // Nama chapter
    boolean is_unlocked;         // Status chapter unlocked
    boolean is_finished;         // Status chapter finished
    Ptree tree_levels;           // Pointer ke tree level dalam chapter
    
    Pchapter next;               // Pointer ke chapter berikutnya
    Pchapter prev;               // Pointer ke chapter sebelumnya
} ChapterNode;

//===================================================//
//==> Method-method untuk deklarasi TREE CHAPTER  <==//
//===================================================//
/* {Sopian} */

// Buat node chapter baru
Pchapter create_chapter_node(char *chapter_name);


#endif