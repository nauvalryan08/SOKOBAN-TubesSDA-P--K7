#ifndef CHAPTERMANAGER_H
#define CHAPTERMANAGER_H

#include "../../UTILS/include/boolean.h"
#include "../../STRUCTURES/tree.h"
#include "Level.h"

//==> STRUCT CHAPTER
typedef struct {
    Ptree ChapterTree;
    Boolean is_finished;
}ChapterData;

// List chapter Tree
typedef enum {
    TUTORIAL,
    CHAPTER1,
    CHAPTER2,
    CHAPTER3,
    CHAPTER4,
    CHAPTER5,
    GroupCount
} ChapterTree;

extern ChapterData ChapterTrees[GroupCount];

extern int cursor_y;

// Inisiator all levels Tree
void initTutorial();
void initChapter1();
void initChapter2();
void initChapter3();
void initChapter4();
void initChapter5();

// Init all chapter at once
void initAllChapters();

//===========================//

//-> Print Tree ilustration (helper)
void printTreeRecursiveNcurses(Ptree node, void (*printID)(void *, char *), char *prefix, bool isLast);

//====> ini yang digunakan
void printTreeStructureNcurses(Ptree root, void (*printID)(void *, char *));

//=> print level by name
void printLevelName(void *data, char *output);

//=> print Level by ID
void printLevelID(void *data, char *output);

//=======================================//
//==       LOGIKA CHECKING STATUS      ==//
//=======================================//
/* {Sopian} */

// helper
void isLevelFinished (void*  data);

Boolean isChapterFinished (ChapterData chapter);


//=======================================//
//==   LOGIKA MANAGER STATUS ACCESS    ==//
//=======================================//
/* {Sopian} */

void updateAllChapterStatus();

void unlockNextChapter();





#endif