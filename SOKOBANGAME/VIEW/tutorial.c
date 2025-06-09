#include "tutorial.h"
#include <curses.h>
#include <string.h>
#include <locale.h>

void show_tutorial_screen() {
    // Teks tutorial dengan penomoran
    const char *tutorial[] = {
        "1. TUJUAN PERMAINAN                                                         ",
        "   - Dorong semua kotak (X) ke titik tujuan (O)",
        "   - Semua kotak harus berada di atas titik tujuan untuk menyelesaikan level",
        "",
        "2. KONTROL",
        "   - Gunakan tombol PANAH (↑ ↓ ← →) untuk bergerak",
        "   - Tekan 'R' untuk me-restart level",
        "   - Tekan 'Q' untuk keluar ke menu utama",
        "",
        "3. ATURAN",
        "   - Karakter (☻) hanya bisa mendorong satu kotak pada satu waktu",
        "   - Kotak tidak bisa ditarik, hanya didorong",
        "   - Kotak tidak bisa didorong melalui kotak lain atau dinding",
        "",
        "4. SIMBOL PENTING",
        "   - @ : Karakter pemain",
        "   - X : Kotak yang harus didorong",
        "   - . : Titik tujuan",
        "   - O : Kotak yang sudah berada di tujuan",
        "   - # : Dinding",
        "   -   : Lantai kosong",
        "",
        "5. STRATEGI",
        "   - Rencanakan beberapa langkah ke depan",
        "   - Hindari mendorong kotak ke sudut mati",
        "   - Gunakan dinding untuk membantu memposisikan kotak",
        "   - Kadang perlu mundur untuk maju",
        "",
        "Tekan ESC untuk kembali ke menu utama..."
    };

    int tutorial_lines = sizeof(tutorial) / sizeof(tutorial[0]);
    int ch;
    
    // Hitung dimensi kotak tutorial
    int margin = 4;
    int box_width = COLS - 2 * margin;
    int box_height = (LINES - 2 * margin) + 1;
    int box_x = margin;
    int box_y = margin;
    
    // Pastikan ukuran minimal
    if (box_width < 40) box_width = 40;
    if (box_height < 20) box_height = 20;
    
    // Ganti mode input dengan timeout
    nodelay(stdscr, FALSE);  // Blocking mode untuk menunggu input
    timeout(0);  // Timeout 100ms untuk tangkap urutan escape
    
    while(1) {
        clear();
        
        // Gambar border
        attron(COLOR_PAIR(3) | A_BOLD);
        
        // Garis horizontal atas/bawah
        for (int i = 0; i < box_width; i++) {
            mvaddch(box_y, box_x + i, ACS_HLINE);
            mvaddch(box_y + box_height - 1, box_x + i, ACS_HLINE);
        }
        
        // Garis vertikal kiri/kanan
        for (int i = 1; i < box_height - 1; i++) {
            mvaddch(box_y + i, box_x, ACS_VLINE);
            mvaddch(box_y + i, box_x + box_width - 1, ACS_VLINE);
        }
        
        // Sudut-sudut
        mvaddch(box_y, box_x, ACS_ULCORNER);
        mvaddch(box_y, box_x + box_width - 1, ACS_URCORNER);
        mvaddch(box_y + box_height - 1, box_x, ACS_LLCORNER);
        mvaddch(box_y + box_height - 1, box_x + box_width - 1, ACS_LRCORNER);
        
        // Judul
        const char *title = "TUTORIAL CARA BERMAIN SOKOBAN";
        mvprintw(box_y + 1, box_x + (box_width - strlen(title)) / 2, "%s", title);
        
        // Garis pemisah judul
        for (int i = 1; i < box_width - 1; i++) {
            mvaddch(box_y + 2, box_x + i, ACS_HLINE);
        }
        
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        // Tampilkan isi tutorial
        attron(COLOR_PAIR(4));
        int current_line = box_y + 4;
        int max_lines = box_y + box_height - 3;
        int text_padding = (box_width > 80) ? 10 : 2;  // Padding dinamis
        
        for (int i = 0; i < tutorial_lines && current_line < max_lines; i++) {
            int line_len = strlen(tutorial[i]);
            int x_pos = box_x + text_padding;
            
            mvprintw(current_line, x_pos, "%s", tutorial[i]);
            current_line++;
        }
        attroff(COLOR_PAIR(4));
        
        refresh();
        
        // Tunggu input pengguna (blocking)
        ch = getch();
        
        // Handle ESC dan urutan escape
        if (ch == 27 || ch == KEY_ESC) {  
            // Cek jika ada karakter tambahan dalam urutan escape
            int ch2 = getch();
            
            // Jika tidak ada karakter lanjutan, itu benar-benar ESC
            if (ch2 == ERR) {
                break;
            }
        }
    }
    
    // Kembalikan timeout ke non-blocking
    nodelay(stdscr, TRUE);
    timeout(0);
}