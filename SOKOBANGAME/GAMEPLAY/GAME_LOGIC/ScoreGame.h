#ifndef SCORE_GAME_H
#define SCORE_GAME_H

typedef struct{
    int score;
    int time;
    int TotalMove;
    int TotalUndo;
}ScoreData;

/**********************************************/
/* -->          Getter AND Setter         <-- */
/**********************************************/

void set_score_data(ScoreData *data, int score, int time, int totalMove, int totalUndo);

int getScore(ScoreData Data);
void setScore(ScoreData *Data, int score);

int getTime(ScoreData Data);
void setTime(ScoreData *Data, int time);

int getTotalMove(ScoreData Data);
void setTotalMove(ScoreData *Data, int totalMove);

int getTotalUndo(ScoreData Data);
void setTotalUndo(ScoreData *Data, int totalUndo);

/*****************************************************/
/* -->          SCORING AND TIME IN GAME         <-- */
/*****************************************************/

// ===> Update Move and Undo count

void calculate_score(ScoreData* Data, int box_count);

// ==> update Score Data
void update_total_move(ScoreData *scoreData, int move);
void update_total_undo(ScoreData *scoreData, int undo);


#endif // SCORE_GAME_H