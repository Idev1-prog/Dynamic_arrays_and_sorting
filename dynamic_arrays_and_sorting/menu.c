#include <stdio.h>
#include "menu.h"
#include <stdbool.h>
#include <stdlib.h>
#include "dmassive.h"

void clear_screen() {
    system("cls");
}

void print_menu_header(const char* header) {
    clear_screen();
    printf("\n%s\n\n", header);
}

int get_user_choice(int min, int max) {
    int choice = -1;
    while (1) {
        printf(USER_CHOOSE_TEXT);
        if (scanf_s("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        if (choice < min || choice > max) {
            printf("Invalid choice! Please enter a number between %d and %d.\n", min, max);
            continue;
        }
        break;
    }
    return choice;
}

void mod_menu(bool* exit_flag) {
    int user_choose = -1;
    while (!*exit_flag) {
        print_menu_header(HEADER_MODE);
        printf(MODE_MENU_TEXT);

        user_choose = get_user_choice(0, MODE_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("One element mode selected.\n");
            system("pause");
            break;
        case 2:
            printf("Several elements mode selected.\n");
            system("pause");
            break;
        case 3:
            return;
        }
    }
}

void sort_mode_menu(bool* exit_flag) {
    int user_choose = -1;
    while (!*exit_flag) {
        print_menu_header(HEADER_SORT_MOD);
        printf(SORT_MODE_MENU_TEXT);

        user_choose = get_user_choice(0, SORT_MODE_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Ascending sort mode selected.\n");
            system("pause");
            break;
        case 2:
            printf("Descending sort mode selected.\n");
            system("pause");
            break;
        case 3:
            return;
        }
    }
}

void create_arr_menu(bool* exit_flag) {
    int user_choose = -1;
    while (!*exit_flag) {
        print_menu_header(HEADER_CREATE);
        printf(CREATE_MENU_TEXT);

        user_choose = get_user_choice(0, CREATE_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Elementary array creation selected.\n");
            system("pause");
            break;
        case 2:
            printf("Random array creation selected.\n");
            system("pause");
            break;
        case 3:
            printf("Manual input selected.\n");
            system("pause");
            break;
        case 4:
            return;
        }
    }
}

void insert_menu(bool* exit_flag) {
    int user_choose = -1;
    while (!*exit_flag) {
        print_menu_header(HEADER_INSERT);
        printf(INSERT_MENU_TEXT);

        user_choose = get_user_choice(0, INSERT_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Insert in front selected.\n");
            system("pause");
            break;
        case 2:
            printf("Insert in back selected.\n");
            system("pause");
            break;
        case 3:
            printf("Insert by position selected.\n");
            system("pause");
            break;
        case 4:
            return;
        }
    }
}

void erase_menu(bool* exit_flag) {
    int user_choose = -1;
    while (!*exit_flag) {
        print_menu_header(HEADER_ERASE);
        printf(ERASE_MENU_TEXT);

        user_choose = get_user_choice(0, ERASE_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Delete from front selected.\n");
            system("pause");
            break;
        case 2:
            printf("Delete from back selected.\n");
            system("pause");
            break;
        case 3:
            printf("Delete by position selected.\n");
            system("pause");
            break;
        case 4:
            return;
        }
    }
}

void search_menu(bool* exit_flag) {
    int user_choose = -1;
    while (!*exit_flag) {
        print_menu_header(HEADER_SEARCH);
        printf(SEARCH_MENU_TEXT);

        user_choose = get_user_choice(0, SEARCH_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Count search selected.\n");
            system("pause");
            break;
        case 2:
            printf("First occurrence search selected.\n");
            system("pause");
            break;
        case 3:
            printf("Last occurrence search selected.\n");
            system("pause");
            break;
        case 4:
            printf("All occurrences search selected.\n");
            system("pause");
            break;
        case 5:
            return;
        }
    }
}

void main_menu() {
    int user_choose = -1;
    bool exit_flag = false;
    DMassive mass = { 0 };

    while (!exit_flag) {
        print_menu_header(HEADER_MAIN);
        print(&mass, "Your array:\n", ' ', '\n');
        printf("\n");
        printf(MAIN_MENU_BASE_TEXT);

        user_choose = get_user_choice(0, MAIN_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            exit_flag = true;
            printf("Exiting program...\n");
            break;
        case 1:
            //create_arr_menu(&exit_flag);
            //break;
            set_memory(&mass, 10);
            fill_elementary(&mass);
            break;
        case 2:
            insert_menu(&exit_flag);
            break;
        case 3:
            erase_menu(&exit_flag);
            break;
        case 4:
            search_menu(&exit_flag);
            break;
        case 5:
            printf("Shuffle (TBD)\n");
            system("pause");
            break;
        case 6:
            printf("Sort menu (TBD)\n");
            system("pause");
            break;
        case 7:
            printf("Clean array (TBD)\n");
            system("pause");
            break;
        case 8:
            printf("Save to file (TBD)\n");
            system("pause");
            break;
        case 9:
            printf("Read from file (TBD)\n");
            system("pause");
            break;
        }
    }
}