#include "TreeChapter.h"

Pchapter create_chapter_node(char *name) {
    Pchapter newNode = (Pchapter)malloc(sizeof(ChapterNode));
    if (!newNode) return NULL;

    newNode->chapter_id = 0;
    newNode->chapter_name = name;
    newNode->is_unlocked = false;
    newNode->is_finished = false;
    newNode->tree_levels = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;



    return newNode;
}

