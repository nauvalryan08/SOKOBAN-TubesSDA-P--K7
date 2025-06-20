#include "authentication.h"

#define MAX_INPUT_LEN 50

// Fungsi untuk menampilkan kotak input
void draw_input_box(int y, int width, const char* prompt, char* input, int cursor_pos) {
    int max_x = getmaxx(stdscr);
    int x = (max_x - width) / 2;
    
    // Gambar kotak
    draw_box(x, y, width, 3);
    
    // Tampilkan prompt
    mvprintw(y - 2, x, "%s:", prompt);
    
    // Tampilkan input
    mvprintw(y + 1, x + 2, "%.*s", width - 4, input);
    
    // Tampilkan kursor
    move(y + 1, x + 2 + cursor_pos);
}

// Fungsi untuk mendapatkan input teks
void get_text_input(char* buffer, const char* prompt) {
    int ch;
    int cursor_pos = 0;
    int max_x = getmaxx(stdscr);
    int width = max_x > 60 ? 40 : max_x - 20;
    int y = LINES / 2 - 5;
    
    buffer[0] = '\0';
    
    while (1) {
        clear();
        draw_input_box(y, width, prompt, buffer, cursor_pos);
        refresh();
        
        ch = getch();
        
        switch (ch) {
            case '\n': // Enter
            case KEY_ENTER:
                return;
                
            case 27: // ESC
                buffer[0] = '\0';
                return;
                
            case KEY_BACKSPACE:
            case 127:
            case 8:
                if (cursor_pos > 0) {
                    memmove(&buffer[cursor_pos - 1], &buffer[cursor_pos], 
                            strlen(buffer) - cursor_pos + 1);
                    cursor_pos--;
                }
                break;
                
            case KEY_LEFT:
                if (cursor_pos > 0) cursor_pos--;
                break;
                
            case KEY_RIGHT:
                if (cursor_pos < (int)strlen(buffer)) cursor_pos++;
                break;
                
            default:
                if (isprint(ch)) {
                    if (strlen(buffer) < MAX_INPUT_LEN - 1) {
                        memmove(&buffer[cursor_pos + 1], &buffer[cursor_pos], 
                                strlen(buffer) - cursor_pos + 1);
                        buffer[cursor_pos] = ch;
                        cursor_pos++;
                    }
                }
                break;
        }
    }
}

// Fungsi untuk menampilkan menu autentikasi
int show_auth_menu(int selected, int items, Button *btnset) {
    int max_x = getmaxx(stdscr);
    
    // Gambar box utama
    draw_box(max_x/2 - 20, LINES/2 - 12, 40, 23);
    
    // Judul
    Txtbox title = {max_x/2 - 15, 2, strlen("AUTHENTICATION MENU") + 10, 2, "AUTHENTICATION MENU", "UNDERLINE"};
    draw_txtbox(&title);
    
    // Gambar tombol
    for (int i = 0; i < items; i++) {
        if (i == selected) {
            attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
        }
        draw_btn(&btnset[i]);
        if (i == selected) {
            attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
        }
    }
    
    // Petunjuk
    attron(COLOR_PAIR(COLOR_YELLOW));
    mvprintw(LINES/2 + 12, max_x/2 - 18, "Gunakan tombol panah untuk navigasi");
    mvprintw(LINES/2 + 13, max_x/2 - 18, "Tekan ENTER untuk memilih");
    mvprintw(LINES/2 + 14, max_x/2 - 18, "Tekan ESC untuk kembali");
    attroff(COLOR_PAIR(COLOR_YELLOW));
}

const char* first_auth_screen() {
    keypad(stdscr, TRUE);
    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;
    MEVENT event;
    int items = 4;
    int selected = 0;

    pthread_t soundThread;

    // Muat data player terlebih dahulu
    load_all_players();
    
    while (1) {
        handle_resize(&prev_lines, &prev_cols);
        clear();
        
        int max_x = getmaxx(stdscr);
        int start_x = max_x/2 - 15;
        int start_y = LINES/2 - 10;
        
        Button menu_items[] = {
            {start_x, start_y, 30, 4, "LOGIN"},
            {start_x, start_y + 5, 30, 4, "SIGN UP"},
            {start_x, start_y + 10, 30, 4, "DELETE ACCOUNT"},
            {start_x, start_y + 15, 30, 4, "EXIT"}
        };
        
        show_auth_menu(selected, items, menu_items);
        refresh();
        
        ch = getch();
        switch (ch) {
            case KEY_UP:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                selected = (selected > 0) ? selected - 1 : items - 1;
                break;
                
            case KEY_DOWN:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                selected = (selected < items - 1) ? selected + 1 : 0;
                break;
                
            case KEY_MOUSE:
                getmouse();
                if (event.bstate & BUTTON1_CLICKED) {
                    pthread_create(&soundThread, NULL, playEnterSound, NULL);
                    pthread_detach(soundThread);
                    for (int i = 0; i < items; i++) {
                        if (isbtnarea(&menu_items[i], event.x, event.y)) {
                            selected = i;
                            ch = '\n'; // Simulasikan tekan ENTER
                        }
                    }
                }
                break;
                
            case '\n':
            case KEY_ENTER:
                pthread_create(&soundThread, NULL, playEnterSound, NULL);
                pthread_detach(soundThread);
                switch (selected) {
                    case 0: // Login
                        return login_process()->username;
                        
                    case 1: // Sign Up
                        return sign_up_process()->username;
                        
                    case 2: // Delete Account
                        delete_account_process();
                        break;
                        
                    case 3: // Exit
                        for (int i = 0; i < GroupCount; i++) {
                            freeTree(ChapterTrees[i].ChapterTree, NULL); 
                        }
                        exit(0);
                }
                break;
                
            case 27: // ESC
                for (int i = 0; i < GroupCount; i++) {
                    freeTree(ChapterTrees[i].ChapterTree, NULL); 
                }
                exit(0);
                break;
                
            case KEY_RESIZE:
                resize_term(0, 0);
                break;
        }
    }
}

// Proses utama autentikasi
const char* authentication_screen() {
    keypad(stdscr, TRUE);
    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;
    MEVENT event;
    int items = 4;
    int selected = 0;
    
    // Muat data player terlebih dahulu
    load_all_players();
    
    while (1) {
        handle_resize(&prev_lines, &prev_cols);
        clear();
        
        int max_x = getmaxx(stdscr);
        int start_x = max_x/2 - 15;
        int start_y = LINES/2 - 10;
        
        Button menu_items[] = {
            {start_x, start_y, 30, 4, "LOGIN"},
            {start_x, start_y + 5, 30, 4, "SIGN UP"},
            {start_x, start_y + 15, 30, 4, "BACK TO LOBBY"}
        };
        
        show_auth_menu(selected, items, menu_items);
        refresh();
        
        ch = getch();
        switch (ch) {
            case KEY_UP:
                selected = (selected > 0) ? selected - 1 : items - 1;
                break;
                
            case KEY_DOWN:
                selected = (selected < items - 1) ? selected + 1 : 0;
                break;
                
            case KEY_MOUSE:
                getmouse();
                if (event.bstate & BUTTON1_CLICKED) {
                    for (int i = 0; i < items; i++) {
                        if (isbtnarea(&menu_items[i], event.x, event.y)) {
                            selected = i;
                            ch = '\n'; // Simulasikan tekan ENTER
                        }
                    }
                }
                break;
                
            case '\n':
            case KEY_ENTER:
                switch (selected) {
                    case 0: // Login
                        return login_process()->username;
                        
                    case 1: // Sign Up
                        return sign_up_process()->username;
                        
                    case 2: // Back
                        return NULL;
                }
                break;
                
            case 27: // ESC
                return NULL;
                
            case KEY_RESIZE:
                resize_term(0, 0);
                break;
        }
    }
}

// Implementasi proses sign up
PlayerData* sign_up_process() {
    char username[MAX_USERNAME_LEN];

    pthread_t soundThread;
    
    while (1) {
        clear();
        get_text_input(username, "Enter username");
        
        // Jika user tekan ESC
        if (username[0] == '\0') {
            return NULL;
        }
        
        // Cek apakah username sudah ada
        PlayerData* existing = get_player(username);
        if (existing != NULL) {
            pthread_create(&soundThread, NULL, playInvalidSound, NULL);
            pthread_detach(soundThread);

            drawMessageBox("Username already exists!");
            Sleep(1000);
            continue;
        }
        
        // Buat player baru
        create_player(username);
        pthread_create(&soundThread, NULL, playEnterSound, NULL);
        pthread_detach(soundThread);
        
        // Tampilkan pesan sukses
        drawMessageBox("Account created successfully!");
        Sleep(1000);
        
        return get_player(username);
    }
}

// Implementasi proses login
PlayerData* login_process() {
    char username[MAX_USERNAME_LEN];
    
    while (1) {
        clear();
        get_text_input(username, "Enter username");
        
        // Jika user tekan ESC
        if (username[0] == '\0') {
            return NULL;
        }
        
        // Cek apakah username ada
        PlayerData* player = get_player(username);
        if (player == NULL) {
            pthread_t soundThread;
            pthread_create(&soundThread, NULL, playInvalidSound, NULL);
            pthread_detach(soundThread);

            drawMessageBox("Account not found!");
            Sleep(1000);

            continue;
        }
        
        // Tampilkan pesan sukses
        char msg[100];
        snprintf(msg, 100, "Welcome back, %s!", username);
        drawMessageBox(msg);
        Sleep(1000);
        
        return player;
    }
}

// Implementasi proses hapus akun
void delete_account_process() {
    char username[MAX_USERNAME_LEN];
    
    while (1) {
        clear();
        get_text_input(username, "Enter username to delete");
        
        // Jika user tekan ESC
        if (username[0] == '\0') {
            return;
        }
        
        // Cek apakah username ada
        PlayerData* player = get_player(username);
        if (player == NULL) {
            pthread_t soundThread;
            pthread_create(&soundThread, NULL, playInvalidSound, NULL);
            pthread_detach(soundThread);

            drawMessageBox("Account not found!");
            getch();
            continue;
        }
        
        // Konfirmasi
        char msg[100];
        snprintf(msg, 100, "Delete account %s? (y/n)", username);
        drawMessageBox(msg);
        
        int ch = getch();
        if (tolower(ch) != 'y') {
            continue;
        }
        
        // Hapus akun
        int idx = -1;
        for (int i = 0; i < player_count; i++) {
            if (strcmp(players[i].username, username) == 0) {
                idx = i;
                break;
            }
        }
        
        if (idx != -1) {
            // Geser array
            for (int i = idx; i < player_count - 1; i++) {
                players[i] = players[i + 1];
            }
            player_count--;
            save_all_players();
            
            snprintf(msg, 100, "Account %s deleted!", username);
            drawMessageBox(msg);
            getch();
        }
        
        return;
    }
}