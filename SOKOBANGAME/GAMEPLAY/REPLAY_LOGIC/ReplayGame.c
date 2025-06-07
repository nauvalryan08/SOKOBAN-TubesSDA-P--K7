#include "ReplayGame.h"


//=========================//
//==>  DATABASE ACCESS  <==//
//=========================//

void saveReplayForUser(Queue *q, const char *username) {
    FILE *fp = fopen(REPLAY_FILE, "a");
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

boolean loadReplayForUser(Queue *q, const char *username) {
    FILE *fp = fopen(REPLAY_FILE, "r");
    if (!fp) return 0;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char *colon = strchr(line, ':');
        if (!colon) continue;
        *colon = '\0';

        if (strcmp(line, username) == 0) {
            char *moves = colon + 1;
            while (*moves && *moves != '\n') {
                enqueue(q, createStep(*moves));
                moves++;
            }
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
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



//=========================//
//==>  REPLAY COMANDER  <==//
//=========================//

void playReplay(RoomLayout *room, LevelData level, Queue *q) {

    const char **map = level.map;
    while (!isQueueEmpty(q)) {
        ReplayStep *step = (ReplayStep *)dequeue(q);
        if (!step) continue;

        switch (step->move) {
            case 'U': move_player(room, 0, -1, map); break;
            case 'D': move_player(room, 0, +1, map); break;
            case 'L': move_player(room, -1, 0, map); break;
            case 'R': move_player(room, +1, 0, map); break;
            case 'Z': /* undo logic if needed */ break;
        }

        update_box_activation_status(room);
        update_finish_activation_status(room);
        print_room(level.level_name,map, room);
        napms(200);
        free(step);
    }
}