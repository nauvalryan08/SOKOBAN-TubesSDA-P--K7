 #include "sokoban.h"
 
 int main () 
 {
    initscr();
    noecho();
    clear();

    initAllChapters();  // Inisialisasi struktur tree
    int cursor_y = 0;
    // printTreeStructureNcurses(ChapterTrees[CHAPTER1].root, printLevelID);
    // printTreeStructureNcurses(ChapterTrees[CHAPTER2].root, printLevelID);
    // printTreeStructureNcurses(ChapterTrees[CHAPTER3].root, printLevelID);
    // printTreeStructureNcurses(ChapterTrees[CHAPTER4].root, printLevelID);
    printTreeStructureNcurses(ChapterTrees[CHAPTER5].ChapterTree, printLevelID);


    refresh();
    getch();
    endwin();
}
