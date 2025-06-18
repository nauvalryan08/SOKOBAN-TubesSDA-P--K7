#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdbool.h>
#include "../../UTILS/include/curses.h"
#include "../../UTILS/include/boolean.h"
#include "../../UTILS/sound/soundmanager.h"

// Fungsi validasi
Boolean getConfirmation(const char* message);
Boolean validate_GameReset();
Boolean validate_QuitGame();
Boolean validate_ExitGame();
Boolean validate_CheatGame();
Boolean validate_SaveGame(); // Fungsi baru untuk validasi penyimpanan

// Fungsi tampilan UI
void showMsg_GameReset();
void showMsg_QuitGame();
void showMsg_ExitGame();
void showMsg_CheatGame();
void showMsg_SaveSuccess(); // Fungsi baru untuk pesan penyimpanan berhasil

// Fungsi bantuan untuk menggambar kotak
void drawMessageBox(const char* message);

#endif