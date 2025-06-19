#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "../include/curses.h"
#include "../../DATABASE/Player.h"
#include "../../VIEW/viewtoolkit.h"
#include "../validator/validator.h"
#include "../sound/soundmanager.h"
#include <string.h>
#include <stdlib.h>

// ------------------------------ //
//       Authentication View      //
// ------------------------------ //

// Fungsi untuk menampilkan kotak input
void draw_input_box(int y, int width, const char* prompt, char* input, int cursor_pos);
// Fungsi untuk mendapatkan input teks
void get_text_input(char* buffer, const char* prompt);
// Fungsi untuk menampilkan menu autentikasi
int show_auth_menu(int selected, int items, Button *btnset);


// ------------------------------ //
//       Main Authentication      //
// ------------------------------ //

// Fungsi utama untuk tampilan autentikasi
const char* authentication_screen();
const char* first_auth_screen();
// Fungsi untuk proses sign up
PlayerData* sign_up_process();
// Fungsi untuk proses login
PlayerData* login_process();
// Fungsi untuk proses hapus akun
void delete_account_process();

#endif