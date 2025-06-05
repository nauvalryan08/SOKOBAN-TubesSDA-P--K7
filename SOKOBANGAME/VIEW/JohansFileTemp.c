// // Masih proses Debugging mouse
// #define NCURSES_MOUSE_VERSION
// #include "levelscreen.h"
// #include <string.h>

// void acs_converter(char **asciiart) {
//   for (int i = 0; asciiart[i] != NULL; i++) {
//     for (int j = 0; asciiart[i][j] != '\0'; j++) {
//       switch (asciiart[i][j]) {
//       case 'l':
//         addch(ACS_ULCORNER);
//         break;
//       case 'k':
//         addch(ACS_URCORNER);
//         break;
//       case 'm':
//         addch(ACS_LLCORNER);
//         break;
//       case 'j':
//         addch(ACS_LRCORNER);
//         break;
//       case 'x':
//         addch(ACS_VLINE);
//         break;
//       case 'q':
//         addch(ACS_HLINE);
//         break;
//       case 'n':
//         addch(ACS_RTEE);
//         break;
//       case 'u':
//         addch(ACS_LTEE);
//         break;
//       case '>':
//         addch(ACS_RARROW);
//       default:
//         addch(asciiart[i][j]);
//         break;
//       }
//     }
//     addch('\n');
//   }
// }

// // Pivot x dan Pivot y button dihitung dari/pivotnya diset dari kiri atas button
// int isbtnarea(int btnlen, int btnwid, int btnpivotx, int btnpivoty,
//               MEVENT mouse) {
//   int btn_areax = btnpivotx + btnwid;
//   int btn_areay = btnpivoty + btnlen;

//   if (mouse.x >= btnpivotx && mouse.x <= btn_areax && mouse.y >= btnpivoty &&
//       mouse.y <= btn_areay) {
//     return 1;
//   }
// }

// void print_lvl(RoomLayout *room) {
//   clear();

//   MEVENT input;
//   mmask_t old;
//   mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);
//   int ch = 0;

//   char *forest[] = {" lqqqqqqqqqqqk",
//                     " x           x",
//                     " x    ...    x",
//                     " x   .:::.   x",
//                     " x  .:::::.  x",
//                     " x  .:##+:.  x",
//                     " x   :##+:   x",
//                     " x    :+:    x",
//                     " x     +     x",
//                     " x     +     x",
//                     " x  +++++++  x",
//                     " x   +++++   x",
//                     " x      +    x",
//                     " x           x",
//                     " x           x",
//                     " x   lqqqk   x",
//                     " mqqqn >uqqqj",
//                     "     mqqqj     ",
//                     NULL};

//   acs_converter(forest);
//   // Debugging interaksi mouse dengan asciiart
//   mvprintw(19, 0, "Double click untuk testing mouse");
//   while (ch != 27) {
//     ch = getch();
//     if (ch == KEY_MOUSE) {
//       if (getmouse(&input) == OK) {
//         if (input.bstate & BUTTON1_DOUBLE_CLICKED) {
//           mvprintw(20, 0, "2x Click kiri, x: %d y: %d\n", input.x, input.y);
//           // Pengecekan input untuk button play dari asciiart
//           if (isbtnarea(3, 4, 5, 15, input) == 1) {
//             //            mvprintw(21, 0, "Tombol Play Di Click! di koordinat:
//             //            x: %d y: %d ",input.x, input.y);
//             start_level(room, ALL_LEVELS[LEVEL_1C4].map);
//           }
//           refresh();
//         }
//       }
//     }
//   }
// }


// // .h nya

// #ifndef LEVELSCREEN_H
// #define LOBBYSCREEN_H

// #define maxbtn_area 50

// #include "../GAMEPLAY/ARENA_LOGIC/Level.h"
// #include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
// #include "../UTILS/include/curses.h"
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// void print_lvl(RoomLayout *room);
// void acs_converter(char **asciiart);

// #endif // !LEVELSCREEN_H
