#include "ReplayGame.h"


//=========================//
//==>  DATABASE ACCESS  <==//
//=========================//

//Sepertinya sudah digantikan ke DATABASE ACCESS di DataHierarki
// |
// |
// v
void saveReplayForUser(Queue *q, const char *username) {

    FILE *fp = fopen(PLAY_DATA_PATH, "a");
    if (!fp) return;

    fprintf(fp, "%s:", username);
    Node *curr = q->front;
    while (curr) {
        ReplayStep *step = (ReplayStep *)curr->data;
        fprintf(fp, "%c", step->move);
        curr = curr->next;
    }
    fprintf(fp, "\n");
    fclose(fp);
}

Boolean loadReplayRecord(Queue *q, const char *username, const char *dataID) {

    FILE *fp = fopen(PLAY_DATA_PATH, "r");
    if (!fp) return false;

    char line[2048];
    while (fgets(line, sizeof(line), fp)) {
        char *copy = strdup(line);
        char *token = strtok(copy, "|");   // username
        char *levelID = strtok(NULL, "|");
        char *dID = strtok(NULL, "|");     // dataID
        strtok(NULL, "|"); // score
        strtok(NULL, "|"); // time
        strtok(NULL, "|"); // move
        strtok(NULL, "|"); // undo
        char *steps = strtok(NULL, "\n");

        if (token && dID && steps &&
            strcmp(token, username) == 0 &&
            strcmp(dID, dataID) == 0) {

            for (int i = 0; steps[i]; i++) {
                enqueue(q, createStep(steps[i]));
            }

            free(copy);
            fclose(fp);
            return true;
        }
        free(copy);
    }

    fclose(fp);
    return false;
}


//=========================//
//==>      INITIATOR    <==//
//=========================//

void initReplayQueue(Queue *q) {
    initQueue(q);
}

ReplayStep *createStep(char move) {
    ReplayStep *step = malloc(sizeof(ReplayStep));
    if (step) step->move = move;
    return step;
}

void clearReplayQueue(Queue *q) {
    while (!isQueueEmpty(q)) {
        ReplayStep *step = (ReplayStep *)dequeue(q);
        free(step);
    }
}




//=========================//
//==>  REPLAY COMANDER  <==//
//=========================//

void playReplay(RoomLayout *room, LevelData level, Queue *q) {

    nodelay(stdscr, TRUE);

    ScoreData dummyScore = {0};

    const char **map = level.map;
    Button btn = {2, LINES - 10, 20, 4, "Exit"};

    Stack stackReplayUndo;
    stack_init(&stackReplayUndo);

    // Reset Map
    reset_game(room, map);
    save_state(&stackReplayUndo, room);
    
    int ch;

    while (!isQueueEmpty(q)) {

        ch = getch();
        if (ch == 27) { // ESC key
            break;
        }
        if (ch == '\n') {
            break;
        }


        ReplayStep *step = (ReplayStep *)dequeue(q);
        if (!step) continue;


        switch (step->move) {
            case 'U':
                save_state(&stackReplayUndo, room); 
                move_player(room, 0, -1, map); 
                break;
            case 'D': 
                save_state(&stackReplayUndo, room); 
                move_player(room, 0, +1, map); 
                break;
            case 'L': 
                save_state(&stackReplayUndo, room); 
                move_player(room, -1, 0, map); 
                break;
            case 'R': 
                save_state(&stackReplayUndo, room); 
                move_player(room, +1, 0, map); 
                break;
            case 'Z':
                undo_game(&stackReplayUndo, room);
                break;
        }

        update_box_activation_status(room);
        update_finish_activation_status(room);
        print_room(level.level_name,map, room, dummyScore, &btn);
        napms(200);
        free(step);
    }
    nodelay(stdscr, true);
    stack_clear(&stackReplayUndo);
}