#ifndef CHAPTERMANAGER_H
#define CHAPTERMANAGER_H

#include "../../UTILS/include/boolean.h"
#include "../../STRUCTURES/tree.h"
#include "Level.h"


// List chapter Tree
typedef enum {
    TUTORIAL,
    CHAPTER1,
    CHAPTER2,
    CHAPTER3,
    CHAPTER4,
    CHAPTER5,
    CHAPTER6,
    BONUS,
    GroupCount
} ChapterTree;

Tree ChapterTrees[GroupCount];

#endif