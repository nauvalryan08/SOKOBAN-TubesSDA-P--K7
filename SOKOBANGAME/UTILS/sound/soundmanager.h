// { Nauval }
// soundmanager.h

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

void threadPlayBGMusic();
void threadStopBGMusic();


#endif