// { Nauval }
// soundmanager.c
#include "soundmanager.h"

int bgm_running = 1;        // 1 mulai, 0 stop
pthread_t bgm_thread;

// #define BG_PATH SOKOBANGAME/UTILS/sound/

void setBGMVolume(int percent) {
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    int value = percent * 10; // scale to 0 - 1000
    char command[64];
    sprintf(command, "setaudio bgm volume to %d", value);
    mciSendString(command, NULL, 0, NULL);
}

// helper
void* playBackgroundMusic(void *args) {
    mciSendString("open \"./ASSETS/SOUNDTRACK.wav\" type mpegvideo alias bgm", NULL, 0, NULL);
    // Set volume (0 - 1000); di sini 300 artinya 30%
    mciSendString("setaudio bgm volume to 300", NULL, 0, NULL);
    mciSendString("play bgm repeat", NULL, 0, NULL);  // Looping
    return NULL;
}

// helper
void stopBackgroundMusic() {
    mciSendString("stop bgm", NULL, 0, NULL);
    mciSendString("close bgm", NULL, 0, NULL);
}

void* playStartGameSound(void* args) {
    PlaySound(TEXT("./ASSETS/STARTGAME.wav"), NULL, SND_ASYNC);
}

void* playMoveSound(void* args) {
    PlaySound(TEXT("./ASSETS/MOVES.wav"), NULL, SND_ASYNC);
}

void* playUndoSound(void* args) {
    PlaySound(TEXT("./ASSETS/UNDO.wav"), NULL, SND_ASYNC);
}

void* playWinSound(void* args) {
    PlaySound(TEXT("./ASSETS/WIN.wav"), NULL, SND_ASYNC);
}

void* playArrowSound(void* args) {
    PlaySound(TEXT("./ASSETS/ARROW.wav"), NULL, SND_ASYNC);
}

void* playChapterUnlockSound(void* args) {
    PlaySound(TEXT("./ASSETS/CHFINISHED.wav"), NULL, SND_ASYNC);
}

void* playGameResetSound(void* args) {
    PlaySound(TEXT("./ASSETS/GAMERESET.wav"), NULL, SND_ASYNC);
}

void* playInvalidSound(void* args) {
    PlaySound(TEXT("./ASSETS/INVALID.wav"), NULL, SND_ASYNC);
}

void* playEnterSound(void* args) {
    PlaySound(TEXT("./ASSETS/ENTER.wav"), NULL, SND_ASYNC);
}

void threadPlayBGMusic() {    
    pthread_create(&bgm_thread, NULL, playBackgroundMusic, NULL);
}

void threadStopBGMusic() {
    pthread_join(bgm_thread, NULL);
}