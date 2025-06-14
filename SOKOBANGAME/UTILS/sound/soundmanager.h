// { Nauval }
// soundmanager.h

/*
pthread_t namanya;
pthread_create(&namanya, NULL, namaMOdul, NULL);
pthread_join(namanya, NULL);
*/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <windows.h>
#include <pthread.h>
#include <stdio.h>

#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

void setBGMVolume(int percent);

void* playBackgroundMusic(void* args);
void stopBackgroundMusic();
void* playMoveSound(void* args);
void* playWinSound(void* args);
void* playArrowSound(void* args);
void* playChapterUnlockSound(void* args);
void* playGameResetSound(void* args);
void* playInvalidSound(void* args);
void* playEnterSound(void* args);

void threadPlayBGMusic();
void threadStopBGMusic();


#endif