// { Nauval }
// soundmanager.c
#include "soundmanager.h"

void playBackgroundMusic() {
    PlaySound(TEXT("C:/MUSIC/SOUNDTRACK.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void stopBackgroundMusic() {
    PlaySound(NULL, NULL, 0); // Stop all
}

void playMoveSound() {
    PlaySound(TEXT("C:/MUSIC/MOVE.wav"), NULL, SND_ASYNC);
}

void playWinSound() {
    PlaySound(TEXT("C:/MUSIC/WIN.wav"), NULL, SND_ASYNC);
}