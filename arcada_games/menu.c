#include "menu.h"
#include "games.h"
#include "utilities.h"
#include <stdio.h>

void start_game_menu(int* is_exit, int* points, int* difficult_id) { // Start games menu
    int user_input;
    int is_back = 0;
    int is_win = 0;

    while (1) { // Infinite loop until user exits or goes back
        printf(TEXT_FOR_GAME_MENU);
        scanf_s("%d", &user_input);

        if (user_input < 0 || user_input > COUNT_OF_GAME_MENU_ITEMS) {
            printf("Wrong answer, enter the correct number\n");
            pause_screen();
            clear_screen();
            continue;
        }

        switch (user_input) { // Process user choice
        case 1:
            is_win = start_lucky_game(points, difficult_id);
            if (is_win) {
                printf("You win!\n");
                *points += 10;
            }
            else {
                printf("I'll be lucky another time.\n");
                *points -= 10;
            }
            pause_screen();
            clear_screen();
            break;
        case 2:
            is_win = start_pairs_game(difficult_id);
            if (is_win) {
                printf("You win!\n");
                *points += 10;
            }
            else {
                printf("I'll be lucky another time.\n");
                *points -= 10;
            }
            pause_screen();
            clear_screen();
            break;
        case 3:
            is_win = start_minesweeper_game(difficult_id);
            if (is_win) {
                printf("You win!\n");
                *points += 10;
            }
            else {
                printf("I'll be lucky another time.\n");
                *points -= 10;
            }
            pause_screen();
            clear_screen();
            break;
        case 4:
            is_win = start_TTT_game(difficult_id);
            switch (is_win) {
            case 0:
                *points -= 10;
                break;
            case 1:
                *points += 10;
                break;
            }
            clear_screen();
            break;
        case 5:
            is_back = 1;
            break;
        case 6:
            is_win = start_checkers_game(difficult_id);
            break;
        case 0:
            *is_exit = 1;
            break;
        }

        if (*is_exit) break;
        if (is_back) break;
    }
}

void select_difficulty_level(int* is_exit, int* difficult_id) { // Select difficulty level (i.e. set difficulty multiplier)
    char* current_difficulty_name = "MEDIUM";
    int is_back = 0;
    int user_input;

    while (1) {
        clear_screen();
        printf(
            "+---------------------------------+\n"
            "| SELECT DIFFICULTY LEVEL         |\n"
            "| -------------------             |\n"
            "|  1. HARD                        |\n"
            "|  2. MEDIUM                      |\n"
            "|  3. EASY                        |\n"
            "|  4. BACK                        |\n"
            "|  0. EXIT                        |\n"
            "|                                 |\n"
            "    [Current difficulty : %s]     \n"
            "+---------------------------------+\n"
            "Your choice:\n"
            "+---------------------------------+\n",
            current_difficulty_name);
        scanf_s("%d", &user_input);
        // Validate input range, handle incorrect input gracefully, update difficulty accordingly
        // Some options might have sub-options (difficulty levels are implemented as switch cases in other functions, this is normal)
        switch (user_input) {
        case 1:
            current_difficulty_name = "HARD";
            *difficult_id = 20;
            break;
        case 2:
            current_difficulty_name = "MEDIUM";
            *difficult_id = 10;
            break;
        case 3:
            current_difficulty_name = "EASY";
            *difficult_id = 5;
            break;
        case 4:
            is_back = 1;
            break;
        case 0:
            *is_exit = 1;
            break;
        }

        if (*is_exit) break;
        if (is_back) break;
    }
}

void start_settings_menu(int* is_exit, int* difficult_id) { // Settings menu, allows user to configure game settings):
    int user_input;
    int is_back = 0;

    while (1) {
        clear_screen();
        printf(TEXT_FOR_SETINGS);
        scanf_s("%d", &user_input);

        switch (user_input) {
        case 1:
            select_difficulty_level(is_exit, difficult_id);
            break;
        case 2:
            is_back = 1;
            break;
        case 0:
            *is_exit = 1;
            break;
        }

        if (*is_exit) break;
        if (is_back) break;
    }
}

void start_main_menu(int* points) { // Main menu function, handles user navigation
    int is_exit = 0;
    int user_input;
    int difficult_id = 10; // Difficulty Multiplier for any games

    while (1) {
        clear_screen();
        printf(MAIN_MENU_TEXT);
        scanf_s("%d", &user_input);

        if (user_input < 0 || user_input > 2) {
            printf("Wrong answer!!!\n");
            pause_screen();
            clear_screen();
            continue;
        }

        if (user_input == 0) is_exit = 1;

        clear_screen();
        if (user_input == 1) {
            start_game_menu(&is_exit, points, &difficult_id);
        }
        if (user_input == 2) {
            start_settings_menu(&is_exit, &difficult_id);
        }
        if (is_exit) break;
    }
}