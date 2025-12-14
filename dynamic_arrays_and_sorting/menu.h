#pragma once
#include <stdio.h>
#include "menu.h"
#include <stdbool.h>
#include <stdlib.h>

#define HEADER_MAIN "--------- MAIN MENU ---------"
#define MAIN_MENU_BASE_TEXT \
"1. Create array\n" \
"2. Insert\n" \
"3. Delete\n" \
"4. Search\n" \
"5. Shuffle\n" \
"6. Sort\n" \
"7. Clean array\n" \
"8. Save to file\n" \
"9. Read from file\n" \
"0. Exit\n"

#define MAIN_MENU_ITEMS_COUNT 9
#define USER_CHOOSE_TEXT "Choose item: "

#define HEADER_MODE "--------- MODE MENU ---------"
#define MODE_MENU_TEXT \
"1. One element\n" \
"2. Several elements\n" \
"3. Back\n" \
"0. Exit\n"
#define MODE_MENU_ITEMS_COUNT 3

#define HEADER_CREATE "--------- CREATE MENU ---------"
#define CREATE_MENU_TEXT \
"1. Elementary\n" \
"2. Randomly\n" \
"3. Manual input\n" \
"4. Back\n" \
"0. Exit\n"
#define CREATE_MENU_ITEMS_COUNT 4

#define HEADER_INSERT "--------- INSERT MENU ---------"
#define INSERT_MENU_TEXT \
"1. In front\n" \
"2. In back\n" \
"3. By position\n" \
"4. Back\n" \
"0. Exit\n"
#define INSERT_MENU_ITEMS_COUNT 4

#define HEADER_ERASE "--------- ERASE MENU ---------"
#define ERASE_MENU_TEXT \
"1. From front\n" \
"2. From back\n" \
"3. By position\n" \
"4. Back\n" \
"0. Exit\n"
#define ERASE_MENU_ITEMS_COUNT 4

#define HEADER_SEARCH "--------- SEARCH MENU ---------"
#define SEARCH_MENU_TEXT \
"1. Count\n" \
"2. First\n" \
"3. Last\n" \
"4. All\n" \
"5. Back\n" \
"0. Exit\n"
#define SEARCH_MENU_ITEMS_COUNT 5

#define HEADER_SORT_MOD "--------- SORT MODE MENU ---------"
#define SORT_MODE_MENU_TEXT \
"1. Ascending\n" \
"2. Descending\n" \
"3. Back\n" \
"0. Exit\n"
#define SORT_MODE_MENU_ITEMS_COUNT 3

#define HEADER_SORT "--------- SORT MENU ---------"
#define SORT_MENU_TEXT \
"1. Bubble sort\n" \
"2. Modified bubble sort\n" \
"3. Quick sort\n" \
"4. Shell sort (knuth)\n" \
"5. Experiment mode\n" \
"6. Back\n" \
"0. Exit\n"
#define SORT_MENU_ITEMS_COUNT 6

void main_menu();
void mod_menu(bool* exit_flag);
void sort_mode_menu(bool* exit_flag);
void create_arr_menu(bool* exit_flag);
void insert_menu(bool* exit_flag);
void search_menu(bool* exit_flag);