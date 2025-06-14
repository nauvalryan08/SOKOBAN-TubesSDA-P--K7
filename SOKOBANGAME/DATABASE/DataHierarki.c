#include "DataHierarki.h"

Ptree initDataHierarki () {

    int i, j;
    char title[30];
    int levelCount[] = {8,15,18,21,22};


    Ptree root = createTreeNode(strdup("History"), TYPE_STRING);

    // Init Chapter (first Child)
    for (i = 0; i<5; i++) {
        sprintf(title, "Chapter - %d", i+1);
        Ptree newChapter = createTreeNode(strdup(title), TYPE_STRING);
        addTreeNodeChild(root, newChapter);

        // init level for each chapter
        int max = levelCount[i];
        for (j=0; j<max; j++) {
            sprintf(title, "Level - %dC%d", i+1, j+1);
            Ptree newLevel = createTreeNode(strdup(title), TYPE_STRING);
            addTreeNodeChild(newChapter, newLevel);
        }
    }

    // Inint the Bonus Level;

    Ptree Bonus = createTreeNode(strdup("Bonus Level"), TYPE_STRING);
    addTreeNodeChild(root, Bonus);

    Ptree b1 = createTreeNode(strdup("Level - B1"), TYPE_STRING);
    Ptree b2 = createTreeNode(strdup("Level - B2"), TYPE_STRING);
    Ptree b3 = createTreeNode(strdup("Level - B3"), TYPE_STRING);
    Ptree b4 = createTreeNode(strdup("Level - B4"), TYPE_STRING);
    Ptree b5 = createTreeNode(strdup("Level - B5"), TYPE_STRING);
    addTreeNodeChild(Bonus, b1);
    addTreeNodeChild(Bonus, b2);
    addTreeNodeChild(Bonus, b3);
    addTreeNodeChild(Bonus, b4);
    addTreeNodeChild(Bonus, b5);

    return root;
}



//===> ID Converter
char *getLevelIDfromString(const char *levelName) {
    char *strip = strstr(levelName," - ");
    if (strip != NULL) {
        return strip + 3;
    }
    return NULL;
}

int convertStringIDtoInt(const char *IDstr) {
    int chapter, index;
    if (sscanf(IDstr, "%dC%d", &chapter, &index) == 2) {
        return chapter *100 + index;   //Mengembalikan nilai ID dalam bentuk ratusan;
    }
    return -1;  //Gagal parsing
}


//===> ID comparing
Boolean compareLevelNameByID(void* data1, void* data2) {
    char* levelName = (char*)data1;
    int idTarget = *((int *)data2);

    char* idStr = getLevelIDfromString(levelName);
    if (!idStr) return false;

    int parseID = convertStringIDtoInt(idStr);

    return parseID == idTarget;
}

//==> Create new Data

PlayData* createPlayData(char* username, int ID_data, int ID_level, int score, int time, int total_move, ReplayStep *replay_data) {
    PlayData* newData = malloc(sizeof(PlayData));
    newData->usernamae = strdup(username); 
    newData->ID_data = ID_data;
    newData->ID_level = ID_level;
    newData->score = score;
    newData->time = time;
    newData->total_move = total_move;
    newData->replay_data = replay_data;

    return newData;
}


void addNewDataToTree(Ptree root, PlayData *data) {
    if (!root || !data) return;

    // Mencari Node level
    int id = data->ID_level;
    Ptree levelNode = findTreeNode(root, &id, compareLevelNameByID);

    if (!levelNode) {
        return;
    }

    Ptree newNode = createTreeNode(data, TYPE_PLAYDATA);
    addTreeNodeChild(levelNode, newNode);
}