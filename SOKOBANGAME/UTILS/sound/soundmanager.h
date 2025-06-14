// { Nauval }
// soundmanager.h

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <windows.h>
#include <pthread.h>

void* playBackgroundMusic(void* args);
void stopBackgroundMusic();
void playMoveSound();
void* playWinSound(void* args);

void threadPlayBGMusic();
void threadStopBGMusic();


#endif