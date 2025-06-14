// { Nauval }
// soundmanager.c
#include "soundmanager.h"

int bgm_running = 1;        // 1 mulai, 0 stop
pthread_t bgm_thread;

#define BG_PATH SOKOBANGAME/UTILS/sound/

// helper
void* playBackgroundMusic(void *args) {
    PlaySound(TEXT("SOKOBANGAME/UTILS/sound/SOUNDTRACK.wav"), NULL, SND_ASYNC | SND_LOOP);
}

// helper
void stopBackgroundMusic() {
    PlaySound(NULL, NULL, 0); // Stop all
}

void playMoveSound() {
    PlaySound(TEXT("SOKOBANGAME/UTILS/sound/MOVE.wav"), NULL, SND_ASYNC);
}

void* playWinSound(void* args) {
    PlaySound(TEXT("SOKOBANGAME/UTILS/sound/WIN.wav"), NULL, SND_ASYNC);
}

void threadPlayBGMusic() {    
    pthread_create(&bgm_thread, NULL, playBackgroundMusic, NULL);
}

void threadStopBGMusic() {
    pthread_join(bgm_thread, NULL);
}