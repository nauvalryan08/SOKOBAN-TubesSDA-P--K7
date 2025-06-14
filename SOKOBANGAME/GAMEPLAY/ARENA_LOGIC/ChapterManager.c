#include "ChapterManager.h"

//=====================================================//
//==   DEFINISI SELURUH TREE CHAPTER KE DALAM ARRAY  ==//
//=====================================================//
/* {Sopian} */
ChapterData ChapterTrees[];


void initTutorial() {
    Ptree n1 = createTreeNode(&ALL_LEVELS[LEVEL_1T1], TYPE_LEVELDATA);
    Ptree n2 = createTreeNode(&ALL_LEVELS[LEVEL_1T2], TYPE_LEVELDATA);
    Ptree n3 = createTreeNode(&ALL_LEVELS[LEVEL_1T3], TYPE_LEVELDATA);
    Ptree n4 = createTreeNode(&ALL_LEVELS[LEVEL_1T4], TYPE_LEVELDATA);

    ChapterTrees[TUTORIAL].is_finished = false;
    ChapterTrees[TUTORIAL].ChapterTree = n1;

    addTreeNodeChild(n1,n2);
    addTreeNodeChild(n2,n3);
    addTreeNodeChild(n3,n4);

}

void initChapter1() {
    Ptree n1 = createTreeNode(&ALL_LEVELS[LEVEL_1C1], TYPE_LEVELDATA);
    Ptree n2 = createTreeNode(&ALL_LEVELS[LEVEL_1C2], TYPE_LEVELDATA);
    Ptree n3 = createTreeNode(&ALL_LEVELS[LEVEL_1C3], TYPE_LEVELDATA);
    Ptree n4 = createTreeNode(&ALL_LEVELS[LEVEL_1C4], TYPE_LEVELDATA);
    Ptree n5 = createTreeNode(&ALL_LEVELS[LEVEL_1C5], TYPE_LEVELDATA);
    Ptree n6 = createTreeNode(&ALL_LEVELS[LEVEL_1C6], TYPE_LEVELDATA);
    Ptree n7 = createTreeNode(&ALL_LEVELS[LEVEL_1C7], TYPE_LEVELDATA);
    Ptree n8 = createTreeNode(&ALL_LEVELS[LEVEL_1C8], TYPE_LEVELDATA);

    ChapterTrees[CHAPTER1].is_finished = false;
    ChapterTrees[CHAPTER1].ChapterTree = n1;

    addTreeNodeChild(n1,n2);
    addTreeNodeChild(n1,n3);

    addTreeNodeChild(n2,n4);
    addTreeNodeChild(n2,n5);

    addTreeNodeChild(n3,n6);
    addTreeNodeChild(n3,n7);
    addTreeNodeChild(n3,n8);
}

void initChapter2() {
    Ptree n1 = createTreeNode(&ALL_LEVELS[LEVEL_2C1], TYPE_LEVELDATA);
    Ptree n2 = createTreeNode(&ALL_LEVELS[LEVEL_2C2], TYPE_LEVELDATA);
    Ptree n3 = createTreeNode(&ALL_LEVELS[LEVEL_2C3], TYPE_LEVELDATA);
    Ptree n4 = createTreeNode(&ALL_LEVELS[LEVEL_2C4], TYPE_LEVELDATA);
    Ptree n5 = createTreeNode(&ALL_LEVELS[LEVEL_2C5], TYPE_LEVELDATA);
    Ptree n6 = createTreeNode(&ALL_LEVELS[LEVEL_2C6], TYPE_LEVELDATA);
    Ptree n7 = createTreeNode(&ALL_LEVELS[LEVEL_2C7], TYPE_LEVELDATA);
    Ptree n8 = createTreeNode(&ALL_LEVELS[LEVEL_2C8], TYPE_LEVELDATA);
    Ptree n9 = createTreeNode(&ALL_LEVELS[LEVEL_2C9], TYPE_LEVELDATA);
    Ptree n10 = createTreeNode(&ALL_LEVELS[LEVEL_2C10], TYPE_LEVELDATA);
    Ptree n11 = createTreeNode(&ALL_LEVELS[LEVEL_2C11], TYPE_LEVELDATA);
    Ptree n12 = createTreeNode(&ALL_LEVELS[LEVEL_2C12], TYPE_LEVELDATA);
    Ptree n13 = createTreeNode(&ALL_LEVELS[LEVEL_2C13], TYPE_LEVELDATA);
    Ptree n14 = createTreeNode(&ALL_LEVELS[LEVEL_2C14], TYPE_LEVELDATA);
    Ptree n15 = createTreeNode(&ALL_LEVELS[LEVEL_2C15], TYPE_LEVELDATA);

    Ptree B1 = createTreeNode(&ALL_LEVELS[LEVEL_1B], TYPE_LEVELDATA);

    ChapterTrees[CHAPTER2].is_finished = false;
    ChapterTrees[CHAPTER2].ChapterTree = n1;

    addTreeNodeChild(n1,n2);
    addTreeNodeChild(n1,n3);
    addTreeNodeChild(n1,n4);
    
    addTreeNodeChild(n2,n5);
    addTreeNodeChild(n2,n6);
    
    addTreeNodeChild(n3,n7);
    addTreeNodeChild(n3,n8);

    addTreeNodeChild(n4,n15);

    addTreeNodeChild(n5,n9);
    addTreeNodeChild(n5,n10);
    addTreeNodeChild(n5,n11);

    addTreeNodeChild(n6,n12);
    addTreeNodeChild(n6,n13);

    addTreeNodeChild(n7, n14);

    addTreeNodeChild(n15, B1);

}

void initChapter3() {
    Ptree n1 = createTreeNode(&ALL_LEVELS[LEVEL_3C1], TYPE_LEVELDATA);
    Ptree n2 = createTreeNode(&ALL_LEVELS[LEVEL_3C2], TYPE_LEVELDATA);
    Ptree n3 = createTreeNode(&ALL_LEVELS[LEVEL_3C3], TYPE_LEVELDATA);
    Ptree n4 = createTreeNode(&ALL_LEVELS[LEVEL_3C4], TYPE_LEVELDATA);
    Ptree n5 = createTreeNode(&ALL_LEVELS[LEVEL_3C5], TYPE_LEVELDATA);
    Ptree n6 = createTreeNode(&ALL_LEVELS[LEVEL_3C6], TYPE_LEVELDATA);
    Ptree n7 = createTreeNode(&ALL_LEVELS[LEVEL_3C7], TYPE_LEVELDATA);
    Ptree n8 = createTreeNode(&ALL_LEVELS[LEVEL_3C8], TYPE_LEVELDATA);
    Ptree n9 = createTreeNode(&ALL_LEVELS[LEVEL_3C9], TYPE_LEVELDATA);
    Ptree n10 = createTreeNode(&ALL_LEVELS[LEVEL_3C10], TYPE_LEVELDATA);
    Ptree n11 = createTreeNode(&ALL_LEVELS[LEVEL_3C11], TYPE_LEVELDATA);
    Ptree n12 = createTreeNode(&ALL_LEVELS[LEVEL_3C12], TYPE_LEVELDATA);
    Ptree n13 = createTreeNode(&ALL_LEVELS[LEVEL_3C13], TYPE_LEVELDATA);
    Ptree n14 = createTreeNode(&ALL_LEVELS[LEVEL_3C14], TYPE_LEVELDATA);
    Ptree n15 = createTreeNode(&ALL_LEVELS[LEVEL_3C15], TYPE_LEVELDATA);
    Ptree n16 = createTreeNode(&ALL_LEVELS[LEVEL_3C16], TYPE_LEVELDATA);
    Ptree n17 = createTreeNode(&ALL_LEVELS[LEVEL_3C17], TYPE_LEVELDATA);
    Ptree n18 = createTreeNode(&ALL_LEVELS[LEVEL_3C18], TYPE_LEVELDATA);

    Ptree B1 = createTreeNode(&ALL_LEVELS[LEVEL_2B], TYPE_LEVELDATA);

    ChapterTrees[CHAPTER3].is_finished = false;
    ChapterTrees[CHAPTER3].ChapterTree = n1;

    addTreeNodeChild(n1,n2);
    addTreeNodeChild(n1,n3);
    addTreeNodeChild(n1,n4);

    addTreeNodeChild(n2, n5);
    addTreeNodeChild(n2,n6);
    addTreeNodeChild(n2,n7);

    addTreeNodeChild(n3,n8);

    addTreeNodeChild(n4,n9);
    addTreeNodeChild(n4,n10);

    addTreeNodeChild(n5,n11);
    addTreeNodeChild(n5,n12);

    addTreeNodeChild(n6,n13);
    addTreeNodeChild(n6,n14);

    addTreeNodeChild(n7,n15);

    addTreeNodeChild(n9,n16);
    addTreeNodeChild(n9,n17);

    addTreeNodeChild(n10,n18);

    addTreeNodeChild(n18,B1);

}

void initChapter4() {
    Ptree n1 = createTreeNode(&ALL_LEVELS[LEVEL_4C1], TYPE_LEVELDATA);
    Ptree n2 = createTreeNode(&ALL_LEVELS[LEVEL_4C2], TYPE_LEVELDATA);
    Ptree n3 = createTreeNode(&ALL_LEVELS[LEVEL_4C3], TYPE_LEVELDATA);
    Ptree n4 = createTreeNode(&ALL_LEVELS[LEVEL_4C4], TYPE_LEVELDATA);
    Ptree n5 = createTreeNode(&ALL_LEVELS[LEVEL_4C5], TYPE_LEVELDATA);
    Ptree n6 = createTreeNode(&ALL_LEVELS[LEVEL_4C6], TYPE_LEVELDATA);
    Ptree n7 = createTreeNode(&ALL_LEVELS[LEVEL_4C7], TYPE_LEVELDATA);
    Ptree n8 = createTreeNode(&ALL_LEVELS[LEVEL_4C8], TYPE_LEVELDATA);
    Ptree n9 = createTreeNode(&ALL_LEVELS[LEVEL_4C9], TYPE_LEVELDATA);
    Ptree n10 = createTreeNode(&ALL_LEVELS[LEVEL_4C10], TYPE_LEVELDATA);
    Ptree n11 = createTreeNode(&ALL_LEVELS[LEVEL_4C11], TYPE_LEVELDATA);
    Ptree n12 = createTreeNode(&ALL_LEVELS[LEVEL_4C12], TYPE_LEVELDATA);
    Ptree n13 = createTreeNode(&ALL_LEVELS[LEVEL_4C13], TYPE_LEVELDATA);
    Ptree n14 = createTreeNode(&ALL_LEVELS[LEVEL_4C14], TYPE_LEVELDATA);
    Ptree n15 = createTreeNode(&ALL_LEVELS[LEVEL_4C15], TYPE_LEVELDATA);
    Ptree n16 = createTreeNode(&ALL_LEVELS[LEVEL_4C16], TYPE_LEVELDATA);
    Ptree n17 = createTreeNode(&ALL_LEVELS[LEVEL_4C17], TYPE_LEVELDATA);
    Ptree n18 = createTreeNode(&ALL_LEVELS[LEVEL_4C18], TYPE_LEVELDATA);
    Ptree n19 = createTreeNode(&ALL_LEVELS[LEVEL_4C19], TYPE_LEVELDATA);
    Ptree n20 = createTreeNode(&ALL_LEVELS[LEVEL_4C20], TYPE_LEVELDATA);
    Ptree n21 = createTreeNode(&ALL_LEVELS[LEVEL_4C21], TYPE_LEVELDATA);

    Ptree B1 = createTreeNode(&ALL_LEVELS[LEVEL_3B], TYPE_LEVELDATA);


    ChapterTrees[CHAPTER4].is_finished = false;
    ChapterTrees[CHAPTER4].ChapterTree = n1;

    addTreeNodeChild(n1,n2);
    addTreeNodeChild(n1,n3);

    addTreeNodeChild(n2, n4);
    addTreeNodeChild(n2,n5);
    addTreeNodeChild(n2,n6);

    addTreeNodeChild(n3,n7);
    addTreeNodeChild(n3,n8);
    addTreeNodeChild(n3,n9);
    addTreeNodeChild(n3,n10);

    addTreeNodeChild(n4,n11);
    addTreeNodeChild(n4,n12);

    addTreeNodeChild(n5,n13);
    addTreeNodeChild(n5,n14);

    addTreeNodeChild(n6,n15);

    addTreeNodeChild(n7,n16);

    addTreeNodeChild(n8,n17);
    addTreeNodeChild(n8,n18);

    addTreeNodeChild(n9,n19);

    addTreeNodeChild(n10,n20);
    addTreeNodeChild(n10,n21);

    addTreeNodeChild(n16, B1);

}

void initChapter5() {
    Ptree n1 = createTreeNode(&ALL_LEVELS[LEVEL_5C1], TYPE_LEVELDATA);
    Ptree n2 = createTreeNode(&ALL_LEVELS[LEVEL_5C2], TYPE_LEVELDATA);
    Ptree n3 = createTreeNode(&ALL_LEVELS[LEVEL_5C3], TYPE_LEVELDATA);
    Ptree n4 = createTreeNode(&ALL_LEVELS[LEVEL_5C4], TYPE_LEVELDATA);
    Ptree n5 = createTreeNode(&ALL_LEVELS[LEVEL_5C5], TYPE_LEVELDATA);
    Ptree n6 = createTreeNode(&ALL_LEVELS[LEVEL_5C6], TYPE_LEVELDATA);
    Ptree n7 = createTreeNode(&ALL_LEVELS[LEVEL_5C7], TYPE_LEVELDATA);
    Ptree n8 = createTreeNode(&ALL_LEVELS[LEVEL_5C8], TYPE_LEVELDATA);
    Ptree n9 = createTreeNode(&ALL_LEVELS[LEVEL_5C9], TYPE_LEVELDATA);
    Ptree n10 = createTreeNode(&ALL_LEVELS[LEVEL_5C10], TYPE_LEVELDATA);
    Ptree n11 = createTreeNode(&ALL_LEVELS[LEVEL_5C11], TYPE_LEVELDATA);
    Ptree n12 = createTreeNode(&ALL_LEVELS[LEVEL_5C12], TYPE_LEVELDATA);
    Ptree n13 = createTreeNode(&ALL_LEVELS[LEVEL_5C13], TYPE_LEVELDATA);
    Ptree n14 = createTreeNode(&ALL_LEVELS[LEVEL_5C14], TYPE_LEVELDATA);
    Ptree n15 = createTreeNode(&ALL_LEVELS[LEVEL_5C15], TYPE_LEVELDATA);
    Ptree n16 = createTreeNode(&ALL_LEVELS[LEVEL_5C16], TYPE_LEVELDATA);
    Ptree n17 = createTreeNode(&ALL_LEVELS[LEVEL_5C17], TYPE_LEVELDATA);
    Ptree n18 = createTreeNode(&ALL_LEVELS[LEVEL_5C18], TYPE_LEVELDATA);
    Ptree n19 = createTreeNode(&ALL_LEVELS[LEVEL_5C19], TYPE_LEVELDATA);
    Ptree n20 = createTreeNode(&ALL_LEVELS[LEVEL_5C20], TYPE_LEVELDATA);
    Ptree n21 = createTreeNode(&ALL_LEVELS[LEVEL_5C21], TYPE_LEVELDATA);
    Ptree n22 = createTreeNode(&ALL_LEVELS[LEVEL_5C22], TYPE_LEVELDATA);
    
    Ptree B1 = createTreeNode(&ALL_LEVELS[LEVEL_5B], TYPE_LEVELDATA);
    Ptree B2 = createTreeNode(&ALL_LEVELS[LEVEL_6B], TYPE_LEVELDATA);

    ChapterTrees[CHAPTER5].ChapterTree = n1;
    ChapterTrees[CHAPTER5].is_finished = false;


    addTreeNodeChild(n1,n2);
    addTreeNodeChild(n1,n3);
    addTreeNodeChild(n1,n4);
    addTreeNodeChild(n1,n5);

    addTreeNodeChild(n2,n6);
    addTreeNodeChild(n2,n7);
    addTreeNodeChild(n2,n8);

    addTreeNodeChild(n3,n9);
    addTreeNodeChild(n3,n10);
    addTreeNodeChild(n3,n11);

    addTreeNodeChild(n4,n12);
    addTreeNodeChild(n4,n13);

    addTreeNodeChild(n5,n14);
    addTreeNodeChild(n5,n15);

    addTreeNodeChild(n6,n16);
    addTreeNodeChild(n6,n17);

    addTreeNodeChild(n7,n18);
    addTreeNodeChild(n7,n19);

    addTreeNodeChild(n12,n20);

    addTreeNodeChild(n13,n21);
    addTreeNodeChild(n13,n22);

    addTreeNodeChild(n20,B1);
    addTreeNodeChild(n10,B2);
}

void initAllChapters() {
    initChapter1();
    initChapter2();
    initChapter3();
    initChapter4();
    initChapter5();
}

//====================================================//


//===============================================//
//==   ILUSTRASI TREE CHAPTER .KE BENTUK TREE  ==//
//===============================================//
/* {Sopian} */

// ==> Print Ilustrasi Tree Section

// Variable global (sesuaikan dengan posisi ujung kiri atas lokasi output)
int cursor_y = 0;

// Prosedur helper untuk pemanggilan secara rekursif
void printTreeRecursiveNcurses(Ptree node, void (*printID)(void *, char *), char *prefix, bool isLast) {
    if (node == NULL) return;

    char line[256];
    strcpy(line, prefix);

    if (isLast) {
        strcat(line, "|-- ");
        strcat(prefix, "    ");
    } else {
        strcat(line, "|-- ");
        strcat(prefix, "|   ");
    }

    // Cetak ID atau nama node menggunakan printID (ke string)
    char label[128];
    printID(node->data, label);  // Minta printID mengisi label
    strcat(line, label);

    mvprintw(cursor_y++, 0, "%s", line);

    // Traversal ke anak-anak
    int childCount = 0;
    Ptree temp = node->fs;
    while (temp) {
        childCount++;
        temp = temp->nb;
    }

    int i = 0;
    temp = node->fs;
    while (temp) {
        if (i > 0) {
            // Tambahkan baris jarak antar subtree
            mvprintw(cursor_y++, 0, "%s|", prefix);
        }
        printTreeRecursiveNcurses(temp, printID, strdup(prefix), i == childCount - 1);
        temp = temp->nb;
        i++;
    }
}

void printTreeStructureNcurses(Ptree root, void (*printID)(void *, char *)) {
    if (root == NULL) {
        mvprintw(cursor_y++, 0, "[Empty Tree]");
        return;
    }
    char prefix[256] = "";
    printTreeRecursiveNcurses(root, printID, prefix, true);
}

// Prosedure helper untuk menjadi parameter void (*PrintID) pada rekursif print tree
void printLevelName(void *data, char *output) {
    LevelData *lvl = (LevelData *)data;
    sprintf(output, "%s", lvl->level_name);  // Misalnya: "Chapter 1 - Level 3"
}


void printLevelID(void *data, char *output) {
    LevelData *lvl = (LevelData *)data;
    sprintf(output, "%s", lvl->level_id);  // Misalnya: "Chapter 1 - Level 3"
}

//======================================//


//=======================================//
//==       LOGIKA CHECKING STATUS      ==//
//=======================================//
/* {Sopian} */

Boolean isChapterFinished (ChapterData chapter) {
    if (!chapter.ChapterTree) return false;

}


//=======================================//
//==   LOGIKA MANAGER STATUS ACCESS    ==//
//=======================================//
/* {Sopian} */

void chapterFinish();
