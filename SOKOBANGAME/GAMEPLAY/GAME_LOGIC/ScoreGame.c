#include "ScoreGame.h"

/**********************************************/
/* -->          Getter AND Setter         <-- */
/**********************************************/

void set_score_data(ScoreData* data, int score, int time, int totalMove, int totalUndo) {
    data->score = score;
    data->time = time;
    data->TotalMove = totalMove;
    data->TotalUndo = totalUndo;
};

int getScore(ScoreData Data) {
    return Data.score;
}

void setScore(ScoreData* Data, int score) {
    Data->score = score;
}

int getTime(ScoreData Data) {
    return Data.time;
}

void setTime(ScoreData* Data, int time) {
    Data->time = time;
}

int getTotalMove(ScoreData Data) {
    return Data.TotalMove;
}

void setTotalMove(ScoreData* Data, int totalMove) {
    Data->TotalMove = totalMove;
}

int getTotalUndo(ScoreData Data) {
    return Data.TotalUndo;
}

void setTotalUndo(ScoreData* Data, int totalUndo) {
    Data->TotalUndo = totalUndo;
}

/*****************************************************/
/* -->          SCORING AND TIME IN GAME         <-- */
/*****************************************************/

// ===> Update Move and Undo count

void calculate_score(ScoreData* data, int box_count) {
    int time = getTime(*data);
    int move = getTotalMove(*data);
    int undo = getTotalUndo(*data);

    if (time == 0) time = 1; // Hindari divide by zero

    double alpha = 0.5;
    double beta = 1.0;
    double gamma = 2.0;

    double efficiency = 1.0 / (alpha * time + beta * move + gamma * undo);
    int score = (int)(10000 * box_count * efficiency);

    setScore(data, score);
}


// ==> update Score Data
void update_total_move(ScoreData *scoreData, int move) {
    scoreData->TotalMove += move;
}

void update_total_undo(ScoreData *scoreData, int undo) {
    scoreData->TotalUndo += undo;
}
