#include "validator.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// Fungsi bantuan untuk menggambar kotak pesan
void drawMessageBox(const char* message) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Hitung ukuran kotak
    int msg_len = strlen(message);
    int box_width = (msg_len < 40) ? 40 : msg_len + 4;
    int box_height = 5;
    int start_x = (max_x - box_width) / 2;
    int start_y = (max_y - box_height) / 2;
    
    // Gambar kotak
    attron(A_STANDOUT);
    for (int y = start_y; y < start_y + box_height; y++) {
        for (int x = start_x; x < start_x + box_width; x++) {
            if (y == start_y || y == start_y + box_height - 1 ||
                x == start_x || x == start_x + box_width - 1) {
                mvaddch(y, x, ' ');
            }
        }
    }
    attroff(A_STANDOUT);
    
    // Tampilkan pesan
    mvprintw(start_y + box_height / 2, (max_x - msg_len) / 2, "%s", message);
    refresh();
}

// Fungsi bantuan untuk validasi input
Boolean getConfirmation(const char* message) {
    pthread_t enterSound;
    pthread_create(&enterSound, NULL, playEnterSound, NULL);
    pthread_join(enterSound, NULL);
    
    drawMessageBox(message);
    
    int ch;
    while (1) {
        ch = tolower(getch());
        if (ch == 'y') {
            return true;
        } else if (ch == 'n') {
            return false;
        }
        // Ulangi jika input tidak valid
        drawMessageBox(message);
    }
}

// Implementasi fungsi validasi
Boolean validate_GameReset() {
    return getConfirmation("Reset game? (y/n)");
}

Boolean validate_QuitGame() {
    return getConfirmation("Quit game? (y/n)");
}

Boolean validate_ExitGame() {
    return getConfirmation("Exit level? (y/n)");
}

Boolean validate_CheatGame() {
    return getConfirmation("Activate cheat? (y/n)");
}

Boolean validate_SaveGame() {
    return getConfirmation("Save current progress? (y/n)");
}

// Implementasi fungsi tampilan UI
void showMsg_GameReset() {
    drawMessageBox("Game Reset!");
    sleep(1);
}

void showMsg_QuitGame() {
    drawMessageBox("Quitting Game...");
    sleep(1);
}

void showMsg_ExitGame() {
    drawMessageBox("Exiting Level...");
    sleep(1);
}

void showMsg_CheatGame() {
    drawMessageBox("Cheat Activated!");
    sleep(1);
}

void showMsg_SaveSuccess() {
    drawMessageBox("Game state saved!");
    sleep(1);
}