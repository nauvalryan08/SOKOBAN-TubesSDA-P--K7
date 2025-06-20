#include "viewtoolkit.h"
#include "../UTILS/include/curses.h"

// Fungsi untuk menggambar tombol pada layar
void draw_btn(Button *btn) {
  // Pengecekan koordinat valid
  if (btn->y < 0 || btn->x < 0 || btn->y + btn->height >= LINES ||
      btn->x + btn->width >= COLS) {
    return;
  }

  // Sudut kiri atas
  mvaddch(btn->y, btn->x, ACS_ULCORNER);

  // Sudut kanan atas
  mvaddch(btn->y, btn->x + btn->width, ACS_URCORNER);

  // Sudut kiri bawah
  mvaddch(btn->y + btn->height, btn->x, ACS_LLCORNER);

  // Sudut kanan bawah
  mvaddch(btn->y + btn->height, btn->x + btn->width, ACS_LRCORNER);

  // Garis horizontal atas dan bawah
  for (int i = 1; i < btn->width; i++) {
    if (btn->x + i < COLS) {
      mvaddch(btn->y, btn->x + i, ACS_HLINE);
      mvaddch(btn->y + btn->height, btn->x + i, ACS_HLINE);
    }
  }

  // Garis vertikal kiri dan kanan
  for (int i = 1; i < btn->height; i++) {
    if (btn->y + i < LINES) {
      mvaddch(btn->y + i, btn->x, ACS_VLINE);
      if (btn->x + btn->width < COLS) {
        mvaddch(btn->y + i, btn->x + btn->width, ACS_VLINE);
      }
    }
  }

  // Tampilkan label di tengah button
  int label_x = btn->x + (btn->width - strlen(btn->label)) / 2;
  int label_y = btn->y + btn->height / 2;
  mvprintw(label_y, label_x, "%s", btn->label);
}

// Fungsi untuk mengecek apakah koordinat mouse berada di area tombol
int isbtnarea(Button *btn, int mouse_x, int mouse_y) {
  return (mouse_x >= btn->x && mouse_x < btn->x + btn->width &&
          mouse_y >= btn->y && mouse_y < btn->y + btn->height);
}

// Fungsi untuk menangani perubahan ukuran terminal
void handle_resize(int *prev_lines, int *prev_cols){
  if (LINES != *prev_lines || COLS != *prev_cols) {
    resize_term(0, 0);
    refresh();
    *prev_lines = LINES;
    *prev_cols = COLS;
  }
}

// Fungsi untuk menampilkan pesan jika ukuran terminal tidak sesuai
void termsize_check(){
      const char *msg = "Ubah ukuran terminal anda menjadi 190x47 agar dapat bermain!";
      int msg_y = LINES / 2;
      int msg_x = (COLS - strlen(msg)) / 2;
      mvprintw(msg_y, msg_x > 0 ? msg_x : 0, "%s", msg);
      if (KEY_RESIZE) {
        resize_term(0,0);
      }
      refresh();
}

// Fungsi untuk menggambar kotak pada layar
void draw_box(int x, int y, int width, int height) {
  // Sudut-sudut
  mvaddch(y, x, ACS_ULCORNER);
  mvaddch(y, x + width, ACS_URCORNER);
  mvaddch(y + height, x, ACS_LLCORNER);
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

  // Isi spasi di dalam box
  for (int i = 1; i < height; i++) {
    for (int j = 1; j < width; j++) {
      if (y + i < LINES && x + j < COLS) {
        mvaddch(y + i, x + j, ' ');
      }
    }
  }
}

// Fungsi untuk menggambar textbox pada layar
void draw_txtbox(Txtbox *textbox){
  // Pengecekan koordinat valid
  if (textbox->y < 0 || textbox->x < 0 || textbox->y + textbox->height >= LINES ||
      textbox->x + textbox->width >= COLS) {
    return;
  }

  // Sudut kiri atas
  mvaddch(textbox->y, textbox->x, ACS_ULCORNER);

  // Sudut kanan atas
  mvaddch(textbox->y, textbox->x + textbox->width, ACS_URCORNER);

  // Sudut kiri bawah
  mvaddch(textbox->y + textbox->height, textbox->x, ACS_LLCORNER);

  // Sudut kanan bawah
  mvaddch(textbox->y + textbox->height, textbox->x + textbox->width, ACS_LRCORNER);

  // Garis horizontal atas dan bawah
  for (int i = 1; i < textbox->width; i++) {
    if (textbox->x + i < COLS) {
      mvaddch(textbox->y, textbox->x + i, ACS_HLINE);
      mvaddch(textbox->y + textbox->height, textbox->x + i, ACS_HLINE);
    }
  }

  // Garis vertikal kiri dan kanan
  for (int i = 1; i < textbox->height; i++) {
    if (textbox->y + i < LINES) {
      mvaddch(textbox->y + i, textbox->x, ACS_VLINE);
      if (textbox->x + textbox->width < COLS) {
        mvaddch(textbox->y + i, textbox->x + textbox->width, ACS_VLINE);
      }
    }
  }

  // Tampilkan label di tengah textbox dengan atribut
  int label_x = textbox->x + (textbox->width - strlen(textbox->label)) / 2;
  int label_y = textbox->y + textbox->height / 2;

  // Apply attributes if specified
  if (textbox->attr != NULL) {
    if (strstr(textbox->attr, "BOLD")) attron(A_BOLD);
    if (strstr(textbox->attr, "REVERSE")) attron(A_REVERSE);
    if (strstr(textbox->attr, "UNDERLINE")) attron(A_UNDERLINE);
    if (strstr(textbox->attr, "BLINK")) attron(A_BLINK);
    if (strstr(textbox->attr, "DIM")) attron(A_DIM);
    if (strstr(textbox->attr, "STANDOUT")) attron(A_STANDOUT);
  }

  mvprintw(label_y, label_x, "%s", textbox->label);

  // Turn off all attributes
  if (textbox->attr != NULL) {
    if (strstr(textbox->attr, "BOLD")) attroff(A_BOLD);
    if (strstr(textbox->attr, "REVERSE")) attroff(A_REVERSE);
    if (strstr(textbox->attr, "UNDERLINE")) attroff(A_UNDERLINE);
    if (strstr(textbox->attr, "BLINK")) attroff(A_BLINK);
    if (strstr(textbox->attr, "DIM")) attroff(A_DIM);
    if (strstr(textbox->attr, "STANDOUT")) attroff(A_STANDOUT);
  }
}

// Fungsi untuk menggambar teks yang dipusatkan pada area tertentu
void draw_centered_text(int y, int x, int width, const char* text) {
  int text_x = x + (width - strlen(text)) / 2;
  if (text_x >= 0 && y >= 0 && y < LINES) {
    mvprintw(y, text_x, "%s", text);
  }
}

// Fungsi untuk menggambar garis horizontal
void draw_horizontal_line(int y, int x, int width) {
  for (int i = 0; i < width; i++) {
    if (x + i < COLS && y >= 0 && y < LINES) {
      mvaddch(y, x + i, ACS_HLINE);
    }
  }
}

// Fungsi untuk menggambar koneksi antara dua tombol
void draw_connection(Button *from, Button *to, ConnectionType type) {
    int from_x = from->x + from->width / 2;
    int from_y = from->y + from->height;
    int to_x = to->x + to->width / 2;
    int to_y = to->y;

    switch (type) {
        case CONNECTION_VERTICAL:
            // Draw vertical line
            for (int y = from_y; y < to_y; y++) {
                if (y >= 0 && y < LINES) {
                    mvaddch(y, from_x, ACS_BLOCK);
                }
            }
            break;

        case CONNECTION_HORIZONTAL:
            to_y = to->y + to->height / 2;
            from_y = from->y + to->height / 2;
            to_x = to->x;
            from_x = from->x + from->width;
            // Draw horizontal line
            if (from_x < to_x) {
                for (int x = from_x; x <= to_x; x++) {
                    if (x >= 0 && x < COLS) {
                        mvaddch(from_y, x, ACS_BLOCK);
                    }
                }
            } else {
                for (int x = to_x; x <= from_x; x++) {
                    if (x >= 0 && x < COLS) {
                        mvaddch(from_y, x, ACS_BLOCK);
                    }
                }
            }
            // Draw vertical line to connect
            for (int y = from_y; y < to_y; y++) {
                if (y >= 0 && y < LINES) {
                    mvaddch(y, to_x, ACS_BLOCK);
                }
            }
            break;

        case CONNECTION_DIAGONAL:
            // Draw diagonal connection
            int dx = to_x - from_x;
            int dy = to_y - from_y;
            int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
            
            for (int i = 0; i <= steps; i++) {
                int x = from_x + (dx * i) / steps;
                int y = from_y + (dy * i) / steps;
                if (x >= 0 && x < COLS && y >= 0 && y < LINES) {
                    if (i == 0) {
                        mvaddch(y, x, ACS_BLOCK);
                    } else if (i == steps) {
                        mvaddch(y, x, ACS_BLOCK);
                    } else {
                        mvaddch(y, x, ACS_BLOCK);
                    }
                }
            }
            break;
    }
}

// Fungsi untuk menggambar koneksi pohon antara parent dan child
void draw_tree_connection(Button *parent, Button *child, ConnectionType type) {
    if (!parent || !child) return;

    // Calculate connection points
    int parent_x = parent->x + parent->width / 2;
    int child_x = child->x + child->width / 2;

    // Draw the connection
    draw_connection(parent, child, type);

    // Draw connection points
    // if (parent_x >= 0 && parent_x < COLS && parent_y >= 0 && parent_y < LINES) {
    //     mvaddch(parent_y, parent_x, ACS_TTEE);
    // }
    // if (child_x >= 0 && child_x < COLS && child_y >= 0 && child_y < LINES) {
    //     mvaddch(child_y, child_x, ACS_BTEE);
    // }
}

// Fungsi untuk menggambar semua koneksi pohon pada struktur tombol
void draw_tree_connections(Button *buttons, int *parent_indices, int count) {
    if (!buttons || !parent_indices || count <= 0) return;

    // Draw connections for each node
    for (int i = 0; i < count; i++) {
        int parent_idx = parent_indices[i];
        if (parent_idx >= 0 && parent_idx < count) {
            // Determine connection type based on relative positions
            Button *parent = &buttons[parent_idx];
            Button *child = &buttons[i];
            
            int dx = child->x - parent->x;
            int dy = child->y - parent->y;
            
            ConnectionType type;
            if (abs(dx) < 10) {
                type = CONNECTION_VERTICAL;
            } else if (abs(dy) < 5) {
                type = CONNECTION_HORIZONTAL;
            } else {
                type = CONNECTION_DIAGONAL;
            }
            
            draw_tree_connection(parent, child, type);
        }
    }
}

// Fungsi untuk menggambar grid tombol menggunakan properti grid
void draw_button_grid(const char **labels, int n_buttons, int selected, const btngridprop *prop) {
    for (int i = 0; i < n_buttons; i++) {
        int row = i / prop->cols;
        int col = i % prop->cols;
        int x = prop->start_x + col * (prop->btn_width + prop->h_spacing);
        int y = prop->start_y + row * (prop->btn_height + prop->v_spacing);
        Button btn = {x, y, prop->btn_width, prop->btn_height, (char*)labels[i]};
        if (i == selected) {
            attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
        }
        draw_btn(&btn);
        if (i == selected) {
            attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
        }
    }
}