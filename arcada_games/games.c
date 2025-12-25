#include "games.h"
#include "utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
const char PAIR_SYMBOLS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// Lucky game

int start_lucky_game(int* points, int* difficult_id) {
	clear_screen();
	printf(LUCKY_GAME_START_TEXT);

	int user_number, computer_number = random_int(*difficult_id);

#ifdef DEBUG
	printf("DEBUG: nmcheck = %d, %d", computer_number, *difficult_id);
#endif

	scanf_s("%d", &user_number);
	clear_screen();
	printf("Computer number is: %d\n", computer_number);

	return user_number == computer_number;
}

// Pairs game

void fill_user_field(char* user_field, int cards_count) {
	for (int i = 0; i < cards_count; i++) {
		user_field[i] = '?';
	}
	user_field[cards_count] = '\0';
}

void generate_game_field(char* game_field, int card_count) {
	for (int i = 0; i < card_count; i += 2) {
        char symbol = PAIR_SYMBOLS[i / 2 % (sizeof(PAIR_SYMBOLS) - 1)];
		game_field[i] = symbol;
		game_field[i + 1] = symbol;
	}
}

void shuffle_game_field(char* game_field, int cards_count) {
	for (int i = 0; i < cards_count; i++) {
		char old_symbol = game_field[i];
		int j = rand() % cards_count;
		game_field[i] = game_field[j];
		game_field[j] = old_symbol;
	}
}

void show_user_field(char* user_field, char* game_field, int cards_count) {
	printf("\n");

	int cols = 4;
	int rows = (cards_count + cols - 1) / cols;

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			int index = row * cols + col;
			if (index < cards_count) {
				printf("+---");
			}
		}
		printf("+\n");

		for (int col = 0; col < cols; col++) {
			int index = row * cols + col;
			if (index < cards_count) {
				printf("|");
				if (user_field[index] != '?') {
					printf(" %c ", user_field[index]);
				}
				else {
					printf("%2d ", index + 1);
				}
			}
		}
		printf("|\n");

		for (int col = 0; col < cols; col++) {
			int index = row * cols + col;
			if (index < cards_count) {
				printf("+---");
			}
		}
		printf("+\n");
	}
	printf("\n");
}

void get_card_number(int* card_num, int cards_count){
	while (1) {
		printf("Enter card number (1-%d): ", cards_count);
		scanf_s("%d", card_num);

		if (*card_num >= 1 && *card_num <= cards_count) {
			break;
		}
		else {
			printf("Wrong number! Enter correct number.\n");
		}
	}
}

void open_card(int card_num, char* user_field, char* game_field) {
	user_field[card_num - 1] = game_field[card_num - 1];
}

void close_card(int card_num, char* user_field) {
	user_field[card_num - 1] = '?';
}

int is_pair(int first_card, int second_card, const char* game_field) {
	return game_field[first_card - 1] == game_field[second_card - 1];
}

void head_text() {
    return;
}

// Start pairs game
int start_pairs_game(int* difficult_id) {
    clear_screen();


    int pairs_count, max_attempts;
    switch (*difficult_id) {
    case 5:  // EASY
        pairs_count = 4;   // 8 cards
        max_attempts = 15;
        break;
    case 10: // MEDIUM
        pairs_count = 6;   // 12 cards
        max_attempts = 20;
        break;
    case 20: // HARD
        pairs_count = 8;   // 16 cards
        max_attempts = 25;
        break;
    default:
        pairs_count = 6;
        max_attempts = 20;
    }

    int cards_count = pairs_count * 2;
    char* game_field = (char*)malloc(sizeof(char) * (cards_count + 1));
    char* user_field = (char*)malloc(sizeof(char) * (cards_count + 1));

    if (!game_field || !user_field) {
        printf("Memory allocation failed!\n");
        if (game_field) free(game_field);
        if (user_field) free(user_field);
        return 0;
    }

    generate_game_field(game_field, cards_count);
    shuffle_game_field(game_field, cards_count);
    fill_user_field(user_field, cards_count);

    int attempts = 0;
    int found_pairs = 0;
    int is_win = 0;




    while (attempts < max_attempts && found_pairs < pairs_count) {
        printf(PAIRS_GAME_START_TEXT);
        printf("Total pairs: %d pairs\n", pairs_count);
        printf("Maximum attempts: %d\n\n", max_attempts);
        #ifdef DEBUG
            printf("Show all cards for testing\n");
            show_user_field(game_field, user_field, cards_count);
        #endif
        printf("Attempts: %d/%d | Pairs found: %d/%d\n",
            attempts, max_attempts, found_pairs, pairs_count);

        show_user_field(user_field, game_field, cards_count);

        int first_card;
        get_card_number(&first_card, cards_count);


        if (user_field[first_card - 1] != '?') {
            printf("This card is already open!\n");
            continue;
        }


        open_card(first_card, user_field, game_field);
        clear_screen();
        printf(PAIRS_GAME_START_TEXT);
        printf("Total pairs: %d pairs\n", pairs_count);
        printf("Maximum attempts: %d\n\n", max_attempts);
#ifdef DEBUG
        printf("Show all cards for testing\n");
        show_user_field(game_field, user_field, cards_count);
#endif
        printf("Attempts: %d/%d | Pairs found: %d/%d\n",
            attempts, max_attempts, found_pairs, pairs_count);
        show_user_field(user_field, game_field, cards_count);

        int second_card;
        get_card_number(&second_card, cards_count);
        if (user_field[second_card - 1] != '?') {
            printf("This card is already open!\n");
            close_card(first_card, user_field);
            continue;
        }

        if (first_card == second_card) {
            printf("You cannot choose the same card twice!\n");
            close_card(first_card, user_field);
            continue;
        }
        open_card(second_card, user_field, game_field);
        clear_screen();
        printf(PAIRS_GAME_START_TEXT);
        printf("Total pairs: %d pairs\n", pairs_count);
        printf("Maximum attempts: %d\n\n", max_attempts);
#ifdef DEBUG
        printf("Show all cards for testing\n");
        show_user_field(game_field, user_field, cards_count);
#endif
        printf("Attempts: %d/%d | Pairs found: %d/%d\n",
            attempts, max_attempts, found_pairs, pairs_count);
        show_user_field(user_field, game_field, cards_count);

        attempts++;

        if (is_pair(first_card, second_card, game_field)) {
            printf("Pair found '%c'!\n", game_field[first_card - 1]);
            found_pairs++;
            pause_screen();
        }
        else {
            printf("Not a pair! ");

            printf("Cards will be closed.\n");
            printf("Continuing game...\n");
            pause_screen();

            close_card(first_card, user_field);
            close_card(second_card, user_field);
            printf("\n");

        }
        clear_screen();
    }

    printf("=== GAME END ===\n");
    show_user_field(user_field, game_field, cards_count);

    if (found_pairs == pairs_count) {
        printf("Congratulations! You found all %d pairs!\n", pairs_count);
        printf("Total attempts: %d/%d\n", attempts, max_attempts);
        is_win = 1;
    }
    else {
        printf("Game over! You found %d out of %d pairs.\n", found_pairs, pairs_count);
        is_win = 0;
    }
    return is_win;
}

// Minesweeper

// Generate empty bombs field (minesweeper)
void generate_empty_bombs_field(char** field, char** user_field, int elements, int lines) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < elements; j++) {
            field[i][j] = '0';
            user_field[i][j] = '#';
            // No bombs initially
        }
    }
}
// Add bombs to field
void add_bombs(char** field, int elements, int lines, int bombs_count) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < elements; j++) {
            field[i][j] = '*';
            bombs_count--;
            if (!bombs_count) {
                return;
            }
        }
    }
}

// Shuffle bombs in field
void shuffle_bombs_field(char** field, int elements, int lines) {  // Shuffle bombs to randomize their positions in field
    int field_power = elements * lines;
    for (int r = 0; r < field_power; r++) {
        int rand_new_element_index = rand() % elements;
        int rand_new_line_index = rand() % lines;
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < elements; j++) {
                char old_symbol = field[i][j];
                field[i][j] = field[rand_new_line_index][rand_new_element_index];
                field[rand_new_line_index][rand_new_element_index] = old_symbol;
            }
        }
    }
}

// Fill neighbors (count bombs around each cell)
void filling_neighbors(char** field, int elements, int lines) {
    for (int y = 0; y < lines; y++) {
        for (int x = 0; x < elements; x++) {
            if (field[y][x] != '*') {
                int bomb_count = 0;

                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx >= 0 && nx < elements && ny >= 0 && ny < lines) {
                            if (field[ny][nx] == '*') {
                                bomb_count++;
                            }
                        }
                    }
                }

                field[y][x] = '0' + bomb_count;
            }
        }
    }
}

void recursion_cell_open(char** field, char** user_field, int lines, int elements, int row, int col) {
    if (lines - 1 < row || row < 0 || elements - 1 < col || col < 0)
        return;
    if (field[row][col] == '*')
        return;
    if (user_field[row][col] == 'W' || user_field[row][col] == 'O')  // Already opened - exit
        return;
    if (user_field[row][col] != 'F') {
        user_field[row][col] = 'W';
    }

    // Recursively open neighboring cells for empty cells ('0')
    if (field[row][col] == '0') {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0)
                    continue;
                int nc = col + dx;
                int nr = row + dy;
                recursion_cell_open(field, user_field, lines, elements, nr, nc);
            }
        }
    }
}

// Toggle flag on/off for minesweeper
void toggle_flag(char** user_field, int row, int col) {
    if (user_field[row][col] == '#') {
        user_field[row][col] = 'F';
        setCursor(row + 2, col * 4 + 2);
        printf("F");
    }
    else if (user_field[row][col] == 'F') {
        user_field[row][col] = '#';
        setCursor(row + 2, col * 4 + 2);
        printf(" ");
    }
}

// Check win condition for minesweeper
int check_win_condition(char** field, char** user_field, int elements, int lines, int bombs_count) {
    int flags_on_bombs = 0;
    int opened_cells = 0;
    int total_cells = elements * lines;

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < elements; j++) {
            if (user_field[i][j] == 'O') {
                opened_cells++;
            }
            else if (user_field[i][j] == 'F') {
                if (field[i][j] == '*') {
                    flags_on_bombs++;
                }
                else {
                    // Flag on non-bomb - invalid, game continues
                    return 0;
                }
            }
        }
    }

    // Win condition: all bombs flagged OR all non-bomb cells opened
    return (flags_on_bombs == bombs_count) || (opened_cells == total_cells - bombs_count);
}

int draw_field(char** field, int elements, int lines) {
    int i, j;


    // Print column numbers header
    for (j = 0; j < elements; j++) {
        printf("%3d ", j);
    }
    printf("\n");

    // Print top border
    for (j = 0; j < elements; j++) {
        printf("----");
    }
    printf("\n");

    // Print field with row numbers
    for (i = 0; i < lines; i++) {
        printf("|");
        for (j = 0; j < elements; j++) {
            printf("   |");
        }
        printf("%2d\n", i);
    }

    // Print top border
    for (j = 0; j < elements; j++) {
        printf("----");
    }

    return 0;
}

// Start minesweeper game
int start_minesweeper_game(int* difficult_id) {
    char** field = NULL;
    char** user_field = NULL;
    int prev_col = 0, prev_row = 0;
    int lines, elements, bombs_count;

    switch (*difficult_id) {
    case 5:  // EASY
        lines = 5;
        elements = 3;
        bombs_count = 2;
        break;
    case 10: // MEDIUM
        lines = 6;
        elements = 4;
        bombs_count = 6;
        break;
    case 20: // HARD
        lines = 8;
        elements = 5;
        bombs_count = 10;
        break;
    default:
        lines = 6;
        elements = 4;
        bombs_count = 6;
    }
    set_malloc_char(&field, lines, elements);
    set_malloc_char(&user_field, lines, elements);
    if (field == NULL || user_field == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    generate_empty_bombs_field(field, user_field, elements, lines);
    add_bombs(field, elements, lines, bombs_count);
    shuffle_bombs_field(field, elements, lines);
    filling_neighbors(field, elements, lines);
    clear_screen();
    draw_field(field, elements, lines);
    printf("\n\n");

#ifdef DEBUG
    for (int i = 0; i < lines; i++) {
        printf("\n");
        for (int j = 0; j < elements; j++) {
            printf("%c ", field[i][j]);
        }
    }
    printf("\n\n");
#endif

    char type_of_action;
    int new_col, new_row;
    int game_continues = 1;
    printf("\nEnter the position (type of action (G - open cell, F - Flag, E - avtolose), colomn, line):\n");
    while (game_continues) {
        scanf_s(" %c %d %d", &type_of_action, 1, &new_col, &new_row);
        if (user_field[new_row][new_col] == 'O') {
            printf("This cell is already open!!!!");
            Sleep(1000);
            printf("\r                             ");
            setCursor(prev_row - 1, 0);
            printf("         ");
            setCursor(prev_row - 1, 0);
            continue;
        }
        getCursor(&prev_row, &prev_col);
        switch (type_of_action) {
        case 'E':
            game_continues = 0;
            break;
        case 'F':
            // Toggle/add flag
            if (user_field[new_row][new_col] == '#' || user_field[new_row][new_col] == 'F') {
                toggle_flag(user_field, new_row, new_col);
                setCursor(prev_row, prev_col);
            }
            break;
        case 'G':
            if (field[new_row][new_col] == '*' && user_field[new_row][new_col] != 'F') {
                setCursor(new_row + 2, new_col * 4 + 2);
                printf("*");
                setCursor(prev_row, prev_col);
                printf("\n\n BOOOOM!\n");
                game_continues = 0;
            }
            else if (user_field[new_row][new_col] == '#' || user_field[new_row][new_col] == 'F') {
                recursion_cell_open(field, user_field, lines, elements, new_row, new_col);
                for (int i = 0; i < lines; i++) {
                    for (int j = 0; j < elements; j++) {
                        if (user_field[i][j] == 'W') {
                            user_field[i][j] = 'O';
                            setCursor(i + 2, j * 4 + 2);
                            printf("%c", field[i][j]);
                            setCursor(prev_row, prev_col);

                        }
                    }
                }
            }
        }
        setCursor(prev_row - 1, 0);
        printf("         ");
        setCursor(prev_row - 1, 0);

        // Check win condition after each move
        if (check_win_condition(field, user_field, elements, lines, bombs_count)) {
            game_continues = 0;
        }
    }

    


    // Check final win condition
    int is_win = check_win_condition(field, user_field, elements, lines, bombs_count);

    for (int i = 0; i < lines; i++) {
        free(field[i]);
        free(user_field[i]);
    }
    free(field);
    free(user_field);
    return is_win;
}

// Tic-tac-toe


void generate_empty_TTT_field(char** field) {
    for (int i = 0; i < SIZE_OF_FIELD_TTT; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_TTT; j++) {
            field[i][j] = 'B';
        }
    }
}

void ai_move_easy(char** field, char game_symbol, int* prev_row, int* prev_col) {
    int free_cells_count = 0;
    for (int i = 0; i < SIZE_OF_FIELD_TTT; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_TTT; j++) {
            if (field[i][j] == 'B') {
                free_cells_count++;
            }
        }
    }

    if (free_cells_count == 0) return;

    int free_cell_open = random_int(free_cells_count);
    free_cells_count = 0;

    for (int i = 0; i < SIZE_OF_FIELD_TTT; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_TTT; j++) {
            if (field[i][j] == 'B') {
                if (free_cells_count == free_cell_open) {
                    field[i][j] = game_symbol;
                    setCursor(i + 2, j * 4 + 2);
                    printf("%c", game_symbol);
                    return;
                }
                free_cells_count++;
            }
        }
    }
}

void ai_move_with_strategy(char** field, char game_symbol, int* prev_row, int* prev_col, int difficulty_mode) {
    char opponent_symbol = (game_symbol == 'X') ? '0' : 'X';

    if (difficulty_mode == AI_EASY) {
        // Режим 1: Всегда рандомные ходы
        ai_move_easy(field, game_symbol, prev_row, prev_col);
        return;
    }

    if (difficulty_mode == AI_MEDIUM) {
        // Режим 2: С некой вероятностью случайный ход
        if (random_int(100) < MEDIUM_DIFICALTY_LEVEL_CHANCE) {
            ai_move_easy(field, game_symbol, prev_row, prev_col);
            return;
        }
    }


    // 1. Проверяем, можем ли выиграть следующим ходом
    for (int i = 0; i < SIZE_OF_FIELD_TTT; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_TTT; j++) {
            if (field[i][j] == 'B') {
                field[i][j] = game_symbol;
                if (check_game_condition_TTT(field, 0) == (game_symbol == 'X' ? X_WINS : O_WINS)) {
                    setCursor(i + 2, j * 4 + 2);
                    printf("%c", game_symbol);
                    return;
                }
                field[i][j] = 'B';
            }
        }
    }

    // 2. Проверяем, может ли противник выиграть следующим ходом - блокируем
    for (int i = 0; i < SIZE_OF_FIELD_TTT; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_TTT; j++) {
            if (field[i][j] == 'B') {
                field[i][j] = opponent_symbol;
                if (check_game_condition_TTT(field, 0) == (opponent_symbol == 'X' ? X_WINS : O_WINS)) {
                    field[i][j] = game_symbol;
                    setCursor(i + 2, j * 4 + 2);
                    printf("%c", game_symbol);
                    return;
                }
                field[i][j] = 'B';
            }
        }
    }

    // 3. Занимаем центр, если он свободен
    if (field[1][1] == 'B') {
        field[1][1] = game_symbol;
        setCursor(3, 6);
        printf("%c", game_symbol);
        return;
    }

    // 4. Пытаемся создать вилку или занять стратегическую позицию
    int corners[4][2] = { {0,0}, {0,2}, {2,0}, {2,2} };

    if (field[1][1] == game_symbol) {
        for (int k = 0; k < 4; k++) {
            int i = corners[k][0];
            int j = corners[k][1];
            int opp_i = 2 - i;
            int opp_j = 2 - j;
            if (field[i][j] == 'B' && field[opp_i][opp_j] == opponent_symbol) {
                field[i][j] = game_symbol;
                setCursor(i + 2, j * 4 + 2);
                printf("%c", game_symbol);
                return;
            }
        }
    }

    // Занимаем любой свободный угол
    for (int k = 0; k < 4; k++) {
        int i = corners[k][0];
        int j = corners[k][1];
        if (field[i][j] == 'B') {
            field[i][j] = game_symbol;
            setCursor(i + 2, j * 4 + 2);
            printf("%c", game_symbol);
            return;
        }
    }

    // 5. Занимаем любую свободную сторону
    int sides[4][2] = { {0,1}, {1,0}, {1,2}, {2,1} };
    for (int k = 0; k < 4; k++) {
        int i = sides[k][0];
        int j = sides[k][1];
        if (field[i][j] == 'B') {
            field[i][j] = game_symbol;
            setCursor(i + 2, j * 4 + 2);
            printf("%c", game_symbol);
            return;
        }
    }

    ai_move_easy(field, game_symbol, prev_row, prev_col);
}

int check_game_condition_TTT(char** field, int remaining_cells) {
    if (remaining_cells == SIZE_OF_FIELD_TTT * 3) return GAME_CONTINUES;
    for (int i = 0; i < SIZE_OF_FIELD_TTT; i++) {
        if (field[i][0] ==  field[i][1] && field[i][1] == field[i][2] && field[i][2] != 'B')
            return (field[i][0] == 'X') ? X_WINS : O_WINS;
        if (field[0][i] == field[1][i] && field[1][i] == field[2][i] && field[2][i] != 'B')
            return (field[0][i] == 'X') ? X_WINS : O_WINS;
    }

    if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[2][2] != 'B')
        return (field[0][0] == 'X') ? X_WINS : O_WINS;
    if (field[0][2] == field[1][1] && field[1][1] == field[2][0] && field[2][0] != 'B')
        return (field[0][2] == 'X') ? X_WINS : O_WINS;

    //for (int i = 0; i < SIZE_OF_FIELD_TTT; i++) {
    //    if (field[i][0] == '0' && field[i][1] == '0' && field[i][2] == '0')
    //        return O_WINS;
    //    if (field[0][i] == '0' && field[1][i] == '0' && field[2][i] == '0')
    //        return O_WINS;
    //}

    //if (field[0][0] == '0' && field[1][1] == '0' && field[2][2] == '0')
    //    return O_WINS;
    //if (field[0][2] == '0' && field[1][1] == '0' && field[2][0] == '0')
    //    return O_WINS;


    for (int i = 0; i < SIZE_OF_FIELD_TTT; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_TTT; j++) {
            if (field[i][j] == 'B')
                return GAME_CONTINUES;
        }
    }
}

void player_move(char** field, char game_symbol, int* prev_row, int* prev_col) {
    int player_choise;
    int new_col, new_row;
    while (true) {
        printf("\nВыберите клетку, для вашего хода (ряд столбец): ");
        getCursor(prev_row, prev_col);
        scanf_s("%d %d", &new_row, &new_col);
        if (new_row >= SIZE_OF_FIELD_TTT || new_row < 0 || new_col >= SIZE_OF_FIELD_TTT || new_col < 0) {
            printf("Клетка выходит за границы поля!");
        }
        else if (field[new_row][new_col] == 'X' || field[new_row][new_col] == '0') {
            printf("Клетка уже занята!");
        }
        else break;
    }
    field[new_row][new_col] = game_symbol;
    setCursor(new_row + 2, new_col * 4 + 2);
    printf("%c", game_symbol);
}


int start_TTT_game(int* difficulty_mode) {
    char** field = NULL;
    int lines = SIZE_OF_FIELD_TTT;
    int row = SIZE_OF_FIELD_TTT;
    int prev_col = 0, prev_row = 0;
    char game_symbol = 'X';
    int remaining_cells = 9;
    int ai_play_position = random_int(2);
    int status = 0;
    int current_difficulty = AI_MEDIUM;

    switch (*difficulty_mode) {
    case 5:  // EASY
        current_difficulty = AI_EASY;
        break;
    case 10: // MEDIUM
        current_difficulty = AI_MEDIUM;
        break;
    case 20: // HARD
        current_difficulty = AI_HARD;
        break;
    }

    clear_screen();
    set_malloc_char(&field, lines, row);
    generate_empty_TTT_field(field);
    draw_field(field, row, lines);
    getCursor(&prev_row, &prev_col);
    while (status == 0) {
        switch (ai_play_position) {
        case 0:
            ai_move_with_strategy(field, game_symbol, &prev_row, &prev_col, current_difficulty);
            setCursor(prev_row, prev_col);
            remaining_cells--;
            status = check_game_condition_TTT(field, remaining_cells);
            if (status > 0) break;

            game_symbol = '0';
            player_move(field, game_symbol, &prev_row, &prev_col);
            setCursor(prev_row, prev_col);
            remaining_cells--;
            status = check_game_condition_TTT(field, remaining_cells);
            if (status > 0) break;

            game_symbol = 'X';
            break;

        case 1:
            player_move(field, game_symbol, &prev_row, &prev_col);
            setCursor(prev_row, prev_col);
            remaining_cells--;
            status = check_game_condition_TTT(field, remaining_cells);
            if (status > 0) break;

            game_symbol = '0';
            ai_move_with_strategy(field, game_symbol, &prev_row, &prev_col, current_difficulty);
            setCursor(prev_row, prev_col);
            remaining_cells--;
            status = check_game_condition_TTT(field, remaining_cells);
            if (status > 0) break;

            game_symbol = 'X';
            break;
        }
    }

    for (int i = 0; i < lines; i++) {
        free(field[i]);
    }
    free(field);

    printf("\n\n");
    switch (status) {
    case X_WINS:
        printf("Победили крестики (X)!\n");
        pause_screen();
        break;
    case O_WINS:
        printf("Победили нолики (0)!\n");
        pause_screen();
        break;
    case DRAW:
        printf("Ничья!\n");
        pause_screen();
        return 2;
    }


    if (ai_play_position == 1) return status == X_WINS ? 1 : 0;
    if (ai_play_position == 0) return status == O_WINS ? 1 : 0;
}

// Checkers


void clean_board(int row_up, int row_down) {
    if (row_up == NULL && row_down == NULL) {
        for (int i = SIZE_OF_FIELD_CHECKERS + 3; i < 30; i++) {
            setCursor(i, 0);
            printf("                                                                 ");
        }
    }
    else {
        for (int i = row_up; i < row_down; i++) {
            setCursor(i, 0);
            printf("                                                                 ");
        }
    }
}

void fill_checkers_board(char** board) {
    for (int i = 0; i < SIZE_OF_FIELD_CHECKERS; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_CHECKERS; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = EMPTY;
            }
            else {
                if (i < 3) {
                    board[i][j] = BLACK;
                }
                else if (i > 4) {
                    board[i][j] = WHITE;
                }
                else {
                    board[i][j] = EMPTY;
                }
            }
        }
    }
}

void show_pieces(char** board) {
    for (int i = 0; i < SIZE_OF_FIELD_CHECKERS; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_CHECKERS; j++) {
            if (board[i][j] != EMPTY) {
                setCursor(i + 2, j * 4 + 2);
                printf("%c", board[i][j]);
            }
        }
    }
}

int check_move(char** board, int fr, int fc, int tr, int tc, char player) {
    if (fr < 0 || fr >= SIZE_OF_FIELD_CHECKERS || fc < 0 || fc >= SIZE_OF_FIELD_CHECKERS ||
        tr < 0 || tr >= SIZE_OF_FIELD_CHECKERS || tc < 0 || tc >= SIZE_OF_FIELD_CHECKERS) {
        return 0;
    }

    if (board[fr][fc] != player) {
        return 0;
    }

    if (board[tr][tc] != EMPTY) {
        return 0;
    }

    if ((tr + tc) % 2 == 0) {
        return 0;
    }

    int dr = tr - fr;
    int dc = tc - fc;

    if (abs(dc) == 1) {
        if (player == WHITE) {
            if (dr != -1) return 0;
        }
        else {
            if (dr != 1) return 0;
        }
        return 1;
    }

    if (abs(dc) == 2 && abs(dr) == 2) {
        int middle_row = (fr + tr) / 2;
        int middle_col = (fc + tc) / 2;

        char middle_piece = board[middle_row][middle_col];

        if (middle_piece == EMPTY) {
            return 0;
        }

        if (player == WHITE) {
            if (middle_piece != BLACK) return 0;
        }
        else {
            if (middle_piece != WHITE) return 0;
        }

        return 2;
    }

    return 0;
}

void do_move_with_display(char** board, int fr, int fc, int tr, int tc, int* prev_row, int* prev_col) {
    int move_type = check_move(board, fr, fc, tr, tc, board[fr][fc]);

    if (move_type == 1) {
        setCursor(fr + 2, fc * 4 + 2);
        printf(" ");

        board[tr][tc] = board[fr][fc];
        board[fr][fc] = EMPTY;

        setCursor(tr + 2, tc * 4 + 2);
        printf("%c", board[tr][tc]);

    }
    else if (move_type == 2) {
        int middle_row = (fr + tr) / 2;
        int middle_col = (fc + tc) / 2;

        setCursor(fr + 2, fc * 4 + 2);
        printf(" ");

        setCursor(middle_row + 2, middle_col * 4 + 2);
        printf(" ");

        board[tr][tc] = board[fr][fc];
        board[fr][fc] = EMPTY;
        board[middle_row][middle_col] = EMPTY;

        setCursor(tr + 2, tc * 4 + 2);
        printf("%c", board[tr][tc]);

        setCursor(SIZE_OF_FIELD_CHECKERS + 8, 0);
        printf("Взята фигура противника!           ");
    }

    setCursor(*prev_row, *prev_col);
}

int count_pieces(char** board, char player) {
    int count = 0;
    for (int i = 0; i < SIZE_OF_FIELD_CHECKERS; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_CHECKERS; j++) {
            if (board[i][j] == player) {
                count++;
            }
        }
    }
    return count;
}

int can_capture_from_position(char** board, int row, int col, char player) {
    // 4 возможных направления для взятия
    int directions[4][2] = { {2, 2}, {2, -2}, {-2, 2}, {-2, -2} };

    for (int i = 0; i < 4; i++) {
        int to_row = row + directions[i][0];
        int to_col = col + directions[i][1];

        if (check_move(board, row, col, to_row, to_col, player) == 2) {
            return 1;
        }
    }
    return 0;
}

int has_forced_capture(char** board, char player) {
    for (int i = 0; i < SIZE_OF_FIELD_CHECKERS; i++) {
        for (int j = 0; j < SIZE_OF_FIELD_CHECKERS; j++) {
            if (board[i][j] == player) {
                if (can_capture_from_position(board, i, j, player)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void player_turn_checkers(char** board, char player, int* prev_row, int* prev_col) {
    int fr, fc, tr, tc;
    int valid = 0;
    int start_line = SIZE_OF_FIELD_CHECKERS + 4;

    int forced_capture = has_forced_capture(board, player);

    while (!valid) {
        clean_board(start_line, start_line + 9); // or 4
        setCursor(start_line, 0);

        printf("Ход %s\n", (player == WHITE) ? "белых (W)" : "черных (B)");

        if (forced_capture) {
            printf("ОБЯЗАТЕЛЬНОЕ ВЗЯТИЕ! Вы должны взять фигуру.\n");
        }

        printf("Откуда (строка столбец): ");

        if (scanf_s("%d %d", &fr, &fc) != 2) {
            printf("\nНеверный ввод!");
            while (getchar() != '\n');
            pause_screen();
            continue;
        }

        printf("Куда (строка столбец): ");

        if (scanf_s("%d %d", &tr, &tc) != 2) {
            printf("\nНеверный ввод!");
            while (getchar() != '\n');
            pause_screen();
            continue;
        }

        int move_type = check_move(board, fr, fc, tr, tc, player);

        if (move_type == 0) {
            printf("\nНеверный ход!");
            pause_screen();
        }
        else if (forced_capture && move_type != 2) {
            printf("\nВы должны взять фигуру!");
            pause_screen();
        }
        else {
            do_move_with_display(board, fr, fc, tr, tc, prev_row, prev_col);
            valid = 1;

            if (move_type == 2 && can_capture_from_position(board, tr, tc, player)) {
                printf("\nПродолжайте взятие!");
                pause_screen();
            }
        }
    }
}


int start_checkers_game(int* difficulty_mode) {
    char** board = NULL;
    int lines = SIZE_OF_FIELD_CHECKERS;
    int row = SIZE_OF_FIELD_CHECKERS;
    char current_player = WHITE;
    int prev_row = 0, prev_col = 0;
    int white_count, black_count;
    int test = 0;
    clear_screen();
    set_malloc_char(&board, lines, row);
    fill_checkers_board(board);
    draw_field(board, row, lines);
    show_pieces(board);
    getCursor(&prev_row, &prev_col);

    while (1) {
        clean_board(SIZE_OF_FIELD_CHECKERS + 5, SIZE_OF_FIELD_CHECKERS + 20);

        setCursor(SIZE_OF_FIELD_CHECKERS + 3, 0);


        white_count = count_pieces(board, WHITE);
        black_count = count_pieces(board, BLACK);

        printf("Белых: %d, Черных: %d   ", white_count, black_count);

        if (white_count == 0) {
            printf("\n\nЧерные победили\n");
            break;
        }
        if (black_count == 0) {
            printf("\n\nБелые победили\n");
            break;
        }

        player_turn_checkers(board, current_player, &prev_row, &prev_col);

        current_player = (current_player == WHITE) ? BLACK : WHITE;
    }

    for (int i = 0; i < lines; i++) {
        free(board[i]);
    }
    free(board);

    pause_screen();
    return 1;
}