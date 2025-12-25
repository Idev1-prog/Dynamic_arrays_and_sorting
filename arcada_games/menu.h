#pragma once

// Menu text definitions
#define COUNT_OF_GAME_MENU_ITEMS 6
#define TEXT_FOR_SETINGS "\
+---------------------------------+\n\
| SETTINGS                        |\n\
| ----------                      |\n\
|  1. DIFFICULTY                  |\n\
|  2. BACK                        |\n\
|  0. EXIT                        |\n\
+-------------------------------- - +\n\
Enter your choice:\n\
+-------------------------------- - +\n\
"

#define MAIN_MENU_TEXT "\
+--------------------------+\n\
| MAIN MENU                |\n\
| ------------             |\n\
|  1. PLAY                 |\n\
|  2. SETTINGS             |\n\
|  0. EXIT                 |\n\
+-------------------------- +\n\
Enter your choice:\n\
+-------------------------- +\n"

#define TEXT_FOR_GAME_MENU "\
+ -------------------------------- - +\n\
| GAMES MENU                      |\n\
| ----------                      |\n\
|  1. LUCKY GAME                  |\n\
|  2. PAIRS GAME                  |\n\
|  3. MINESWEEPER                 |\n\
|  4. TIC-TAC-TOE                 |\n\
|  5. BACK                        |\n\
|  6. CHECKERS                    |\n\
|  0. EXIT                        |\n\
+-------------------------------- - +\n\
Enter your choice:\n\
+-------------------------------- - +\n\
"

// Menu functions
void start_main_menu(int* points);
void start_game_menu(int* is_exit, int* points, int* difficult_id);
void start_settings_menu(int* is_exit, int* difficult_id);
void select_difficulty_level(int* is_exit, int* difficult_id);