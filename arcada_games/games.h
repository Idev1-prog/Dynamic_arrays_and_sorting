#pragma once

//#define DEBUG
#define AI_EASY 0
#define AI_MEDIUM 1
#define AI_HARD 2
#define SIZE_OF_FIELD_TTT 3
#define GAME_CONTINUES 0
#define X_WINS 1
#define O_WINS 2
#define DRAW 3
#define MEDIUM_DIFICALTY_LEVEL_CHANCE 50
#define LUCKY_GAME_START_TEXT "\
This is test of your lucky!\n\
Your number is: "
#define PAIRS_GAME_START_TEXT "\
+-----------------------------+\n\
|       PAIRS GAME           |\n\
+-----------------------------+\n"
//#define PAIR_SYMBOLS "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// Game functions
int start_lucky_game(int* points, int* difficult_id);
int start_pairs_game(int* difficult_id);
int start_minesweeper_game(int* difficult_id);
int start_TTT_game(int* difficult_id);

// Functions for pairs game
void generate_game_field(char* game_field, int card_count);
void shuffle_game_field(char* game_field, int cards_count);
void fill_user_field(char* user_field, int cards_count);
void show_user_field(const char* user_field, const char* game_field, int cards_count);
void get_card_number(int* card_num, int cards_count);
void open_card(int card_num, char* user_field, const char* game_field);
void close_card(int card_num, char* user_field);
int is_pair(int first_card, int second_card, const char* game_field);

// Minesweeper functions
void generate_empty_bombs_field(char** field, char** user_field, int elements, int lines);
void add_bombs(char** field, int elements, int lines, int bombs_count);
void shuffle_bombs_field(char** field, int elements, int lines);
void filling_neighbors(char** field, int elements, int lines);
void recursion_cell_open(char** field, char** user_field, int lines, int elements, int row, int col);
void toggle_flag(char** user_field, int row, int col);
int check_win_condition(char** field, char** user_field, int elements, int lines, int bombs_count);
int draw_field(char** field, int elements, int lines);

// Tic-tac-toe

void generate_empty_TTT_field(char** field);
void ai_move_easy(char** field, char game_symbol, int* prev_row, int* prev_col);
void ai_move_with_strategy(char** field, char game_symbol, int* prev_row, int* prev_col, int difficulty_mode);
int check_game_condition_TTT(char** field, int remaining_cells);
void player_move(char** field, char game_symbol, int* prev_row, int* prev_col);