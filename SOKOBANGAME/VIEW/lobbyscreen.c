#include "lobbyscreen.h"

// Fungsi untuk menggambar kotak
void draw_box(int y, int x, int height, int width) {
  // Pastikan koordinat valid
  if (y < 0 || x < 0 || y + height >= LINES || x + width >= COLS) {
    return;
  }

  // Sudut kiri atas
  mvaddch(y, x, ACS_ULCORNER);

  // Sudut kanan atas
  mvaddch(y, x + width, ACS_URCORNER);

  // Sudut kiri bawah
  mvaddch(y + height, x, ACS_LLCORNER);

  // Sudut kanan bawah
  mvaddch(y + height, x + width, ACS_LRCORNER);

  // Garis horizontal atas dan bawah
  for (int i = 1; i < width; i++) {
    if (x + i < COLS) {
      mvaddch(y, x + i, ACS_HLINE);
      mvaddch(y + height, x + i, ACS_HLINE);
    }
  }

  // Garis vertikal kiri dan kanan
  for (int i = 1; i < height; i++) {
    if (y + i < LINES) {
      mvaddch(y + i, x, ACS_VLINE);
      if (x + width < COLS) {
        mvaddch(y + i, x + width, ACS_VLINE);
      }
    }
  }
}

void draw_sokoban_animation(Animation *anim, int frame) {
  // Animasi karakter Sokoban yang lebih besar dan detail
  char frames[ANIMATION_FRAMES][5][20] = {
      {// Frame 1
       "   ___   ", "  (o o)  ", "   | |   ", "  /   \\  ", " |     | "},
      {// Frame 2
       "   ___   ", "  (o o)  ", "   /_\\   ", "  |   |  ", "  |   |  "},
      {// Frame 3
       "   ___   ", "  (o o)  ", "   | |   ", "  |   |  ", "  |   |  "},
      {// Frame 4
       "   ___   ", "  (o o)  ", "   /_\\   ", "  /   \\  ", " |     | "}};

  // Kotak yang lebih besar dan detail
  char box[5][20] = {"+--------+", "|        |", "|        |", "|        |",
                     "+--------+"};

  // Hapus animasi sebelumnya
  for (int i = 0; i < 5; i++) {
    mvprintw(anim->y + i + 3, anim->x, "%*s", 25, " ");
  }

  // Update posisi
  anim->x += anim->direction;
  if (anim->x <= 5 || anim->x >= COLS - 25) {
    anim->direction *= -1;

    // Balik arah karakter
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < strlen(frames[0][i]); j++) {
        // Balik karakter yang menghadap
        if (frames[frame][i][j] == '\\') {
          frames[frame][i][j] = '/';
        } else if (frames[frame][i][j] == '/') {
          frames[frame][i][j] = '\\';
        }
      }
    }
  }

  // Gambar karakter
  for (int i = 0; i < 5; i++) {
    mvprintw(anim->y + i + 3, anim->x, "%s", frames[frame][i]);
  }

  // Gambar box di sebelah karakter
  int box_x = anim->x + 10;
  for (int i = 0; i < 5; i++) {
    mvprintw(anim->y + i + 3, box_x, "%s", box[i]);
  }

  // Tambahkan efek gerakan
  if (frame == 1 || frame == 3) {
    // Tanda gerakan di belakang karakter
    for (int i = 3; i < 5; i++) {
      mvaddch(anim->y + i + 3, anim->x - 2, '.');
    }
  }
}

void print_sokoban_title() {
  // Judul yang lebih kecil untuk terminal kecil
  char *title[] = {
      "   ______    ______   __    __   ______   _______    ______   __    __ ",
      "  /      `  /      ` /  |  /  | /      ` /       `  /      ` /  `  /  |",
      " /$$$$$$  |/$$$$$$  |$$ | /$$/ /$$$$$$  |$$$$$$$  |/$$$$$$  |$$  ` $$ |",
      " $$ `__$$/ $$ |  $$ |$$ |/$$/  $$ |  $$ |$$ |__$$ |$$ |__$$ |$$$  `$$ |",
      " $$      ` $$ |  $$ |$$  $$<   $$ |  $$ |$$    $$< $$    $$ |$$$$  $$ |",
      "  $$$$$$  |$$ |  $$ |$$$$$  `  $$ |  $$ |$$$$$$$  |$$$$$$$$ |$$ $$ $$ |",
      " /  `__$$ |$$ `__$$ |$$ |$$  ` $$ `__$$ |$$ |__$$ |$$ |  $$ |$$ |$$$$ |",
      " $$    $$/ $$    $$/ $$ | $$  |$$    $$/ $$    $$/ $$ |  $$ |$$ | $$$ |",
      "  $$$$$$/   $$$$$$/  $$/   $$/  $$$$$$/  $$$$$$$/  $$/   $$/ $$/   "
      "$$/ "};
  int title_lines = 9;

  for (int i = 0; i < title_lines; i++) {
    int len = strlen(title[i]);
    int x_pos = (COLS - len) / 2;
    if (x_pos < 0) {
      // Jika terminal terlalu kecil, tampilkan bagian yang bisa
      mvprintw(1 + i, 0, "%.*s", COLS, title[i]);
    } else {
      mvprintw(1 + i, x_pos, "%s", title[i]);
    }
  }
}

int show_menu(int selected, int start_y) {
  char *menu_items[MENU_ITEMS] = {" PLAY GAME ", " HISTORY ", " LEADERBOARD ",
                                  " HOW TO PLAY ", " QUIT GAME "};

  // Hitung lebar maksimum menu dengan padding ekstra
  int max_len = 0;
  for (int i = 0; i < MENU_ITEMS; i++) {
    int len = strlen(menu_items[i]);
    if (len > max_len)
      max_len = len;
  }

  // Tambahkan padding untuk membuat kotak lebih lebar
  int horizontal_padding = 35; // Padding kiri-kanan
  int vertical_padding = 18; // Padding atas-bawah (ditambah untuk ruang kosong)

  // Hitung dimensi kotak
  int box_width = max_len + horizontal_padding;
  int box_height = MENU_ITEMS + vertical_padding;

  // Hitung posisi kotak (pusatkan secara horizontal dan geser ke bawah)
  int box_x = (COLS - box_width) / 2;
  int box_y = start_y + 3; // Tambah 5 baris untuk geser ke bawah

  // Pastikan kotak tidak keluar dari layar
  if (box_x < 0)
    box_x = 0;
  if (box_y < 0)
    box_y = 0;
  if (box_x + box_width >= COLS)
    box_width = COLS - box_x - 1;
  if (box_y + box_height >= LINES)
    box_height = LINES - box_y - 1;

  // Gambar kotak dengan gaya yang lebih baik
  if (box_width > 10 && box_height > 5) {
    // Garis atas
    for (int i = 0; i < box_width; i++) {
      mvaddch(box_y, box_x + i, ACS_HLINE);
    }

    // Garis bawah
    for (int i = 0; i < box_width; i++) {
      mvaddch(box_y + box_height, box_x + i, ACS_HLINE);
    }

    // Garis vertikal dan konten
    for (int i = 1; i < box_height; i++) {
      // Garis kiri
      mvaddch(box_y + i, box_x, ACS_VLINE);

      // Garis kanan
      mvaddch(box_y + i, box_x + box_width, ACS_VLINE);

      // Isi spasi di antara
      for (int j = 1; j < box_width; j++) {
        mvaddch(box_y + i, box_x + j, ' ');
      }
    }

    // Sudut-sudut
    mvaddch(box_y, box_x, ACS_ULCORNER);
    mvaddch(box_y, box_x + box_width, ACS_URCORNER);
    mvaddch(box_y + box_height, box_x, ACS_LLCORNER);
    mvaddch(box_y + box_height, box_x + box_width, ACS_LRCORNER);
  }

  // Tampilkan menu items dengan jarak vertikal yang lebih besar
  for (int i = 0; i < MENU_ITEMS; i++) {
    // Hitung posisi vertikal dengan jarak tambahan
    int vertical_spacing = 2; // Jarak antar item
    int y_pos = box_y + vertical_padding / 3 + (i * vertical_spacing);

    // Posisi horizontal (tengah kotak)
    int x_pos = box_x + (box_width - strlen(menu_items[i])) / 2;

    // Jika posisi Y valid
    if (y_pos < LINES && y_pos >= 0) {
      if (i == selected) {
        // Tampilkan item terpilih dengan highlight
        attron(A_REVERSE | A_BOLD | COLOR_PAIR(1));

        // Highlight bar penuh dengan padding horizontal
        int highlight_padding = 10;
        for (int j = highlight_padding; j < box_width - highlight_padding;
             j++) {
          mvaddch(y_pos, box_x + j, ' ');
        }

        mvprintw(y_pos, x_pos, "%s", menu_items[i]);
        attroff(A_REVERSE | A_BOLD | COLOR_PAIR(1));
      } else {
        // Item tidak terpilih
        attron(COLOR_PAIR(2));
        mvprintw(y_pos, x_pos, "%s", menu_items[i]);
        attroff(COLOR_PAIR(2));
      }
    }
  }

  // Alternatif judul multi-baris
  const char *title_lines[] = {"                                           ",
                               "                  MAIN MENU                ",
                               "                                           "};
  int num_title_lines = 3;

  // Hitung lebar judul (asumsi semua baris sama panjang)
  int title_width = strlen(title_lines[0]);

  // Posisi judul di dalam kotak
  int title_y = box_y + 1;
  int title_x = box_x + (box_width - title_width) / 2;

  if (title_y > 0 && title_x > 0) {
    attron(A_BOLD | COLOR_PAIR(3));
    for (int i = 0; i < num_title_lines; i++) {
      mvprintw(title_y + i, title_x, "%s", title_lines[i]);
    }
    attroff(A_BOLD | COLOR_PAIR(3));

    // Garis pemisah di bawah judul
    for (int j = 1; j < box_width - 1; j++) {
      mvaddch(title_y + num_title_lines, box_x + j, ACS_HLINE);
    }
  }
  return selected;
}

int show_lobby_screen() {
  Animation anim = {5, 8, 1}; // Start from left
  int frame = 0;
  int selected = 0;
  int ch;
  int prev_lines = LINES;
  int prev_cols = COLS;

  // Ukuran minimal yang lebih kecil
  int min_height = 20;
  int min_width = 50;
  int menu_start_y = 15;

  // Jika terminal sangat kecil, turunkan menu
  if (LINES < 25) {
    menu_start_y = 10;
  }

  // Inisialisasi input non-blocking
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  while (1) {
    
    if (LINES != prev_lines || COLS != prev_cols) {
      resize_term(0, 0); // Sync ukuran dengan terminal
      prev_lines = LINES;
      prev_cols = COLS;
    }

    clear();

    // Tampilkan ukuran terminal saat ini untuk debug
    char size_info[50];
    snprintf(size_info, sizeof(size_info), "Terminal: %dx%d (min %dx%d)", 
    COLS, LINES, min_width, min_height);
    mvprintw(0, 0, "%s", size_info);
        
    // Pesan jika terlalu kecil
    if (LINES < min_height || COLS < min_width) {
      const char *msg = "Please resize terminal to at least 50x20";
      int msg_y = LINES / 2;
      int msg_x = (COLS - strlen(msg)) / 2;
      mvprintw(msg_y, msg_x > 0 ? msg_x : 0, "%s", msg);

      if (KEY_RESIZE) {
        resize_term(0,0);
      }
      refresh();
      // napms(100);

    } else {
        
      // Judul game
      attron(COLOR_PAIR(1) | A_BOLD);
      print_sokoban_title();
      attroff(COLOR_PAIR(1) | A_BOLD);
        
      // Animasi
      // if (LINES > 10) {
      //     attron(COLOR_PAIR(2));
      //     draw_sokoban_animation(&anim, frame);
      //     attroff(COLOR_PAIR(2));
      //     frame = (frame + 1) % ANIMATION_FRAMES;
      // }
        
      // Menu dalam kotak
      show_menu(selected, menu_start_y);
        
      // Petunjuk
      if (LINES > menu_start_y + 10) {
          const char *hint1 = "ARROW KEYS: Navigate";
          const char *hint2 = "ENTER: Select";
          mvprintw(menu_start_y + 22, (COLS - strlen(hint1)) / 2, "%s", hint1);
          mvprintw(menu_start_y + 23, (COLS - strlen(hint2)) / 2, "%s", hint2);
      }
        
      ch = getch();
      switch (ch) {
          case KEY_UP:
              selected = (selected > 0) ? selected - 1 : MENU_ITEMS - 1;
              break;
          case KEY_DOWN:
              selected = (selected < MENU_ITEMS - 1) ? selected + 1 : 0;
              break;
          case '\n':
          case KEY_ENTER:
              return selected;
          case KEY_RESIZE:
              resize_term(0, 0);
              break;
          case ERR:
              // Tidak ada input – tidak apa
              break;
          default:
              break;
      }
      
      refresh();
      // napms(100);
    }
  }
}
