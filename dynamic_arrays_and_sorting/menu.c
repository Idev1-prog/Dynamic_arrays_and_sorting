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
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choice < min || choice > max) {
            printf("Invalid choice! Please enter a number between %d and %d.\n", min, max);
            continue;
        }
        break;
    }
    return choice;
}

int get_array_size() {
    int size = 0;
    printf("Enter array size: ");
    while (1) {
        if (scanf_s("%d", &size) != 1) {
            printf("Invalid input! Please enter a number: ");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (size <= 0) {
            printf("Size must be positive. Enter array size: ");
            continue;
        }
        break;
    }
    return size;
}

int mod_menu(bool* exit_flag) {
    int user_choose = -1;
    while (!*exit_flag) {
        print_menu_header(HEADER_MODE);
        printf(MODE_MENU_TEXT);

        user_choose = get_user_choice(0, MODE_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return 0;
        case 1:
            printf("One element mode selected.\n");
            system("pause");
            return MOD_ONE;
        case 2:
            printf("Several elements mode selected.\n");
            system("pause");
            return MOD_SEVERAL;
        case 3:
            return 0;
        }
    }
    return 0;
}

void sort_mode_menu(bool* exit_flag, DMassive* mass) {
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
            sort_menu(exit_flag, mass);
            system("pause");
            break;
        case 2:
            printf("Descending sort mode selected.\n");
            sort_menu(exit_flag, mass);
            revers_mass(mass);
            system("pause");
            break;
        case 3:
            return;
        }
    }
}

void sort_menu(bool* exit_flag, DMassive* mass) {
    int user_choose = -1;
    
    while (!*exit_flag) {
        print_menu_header(HEADER_SORT);
        printf(SORT_MENU_TEXT);

        user_choose = get_user_choice(0, SORT_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Bubble sort choosed.\n");
            bubble_sort(mass);
            return;
        case 2:
            printf("Bubble sort (mod) choosed.\n");
            bubble_sort_pro(mass);
            return;
        case 3:
            printf("Quick sort choosed.\n");
            //quick_sort();
            return;
        case 4:
            printf("Shell sort choosed.\n");
            shell_sort_knuth(mass);
            return;
        case 5:
            printf("TBD");
            return;
        case 6:
            return;

        }
    }
}

void create_arr_menu(bool* exit_flag, DMassive* mass) {
    int user_choose = -1;
    double min, max;
    int size = 0;

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
            size = get_array_size();
            set_memory(mass, size);
            fill_elementary(mass);
            printf("Array created with %d elements.\n", size);
            system("pause");
            break;
        case 2:
            printf("Random array creation selected.\n");
            size = get_array_size();
            printf("Set the number generation limit (min max): ");
            scanf_s("%lf %lf", &min, &max);
            while (getchar() != '\n');
            set_memory(mass, size);
            fill_randomly(mass, min, max);
            printf("Array created with %d random elements between %.2lf and %.2lf.\n", size, min, max);
            system("pause");
            break;
        case 3:
            printf("Manual input selected.\n");
            size = get_array_size();
            set_memory(mass, size);
            fill_manual_input(mass);
            printf("Array created with %d manually entered elements.\n", size);
            system("pause");
            break;
        case 4:
            return;
        }
    }
}

void insert_menu(bool* exit_flag, DMassive* mass, int mod) {
    int user_choose = -1;
    double value = 0.0;
    int pos = 0;
    Status status;

    if (mass->data == NULL) {
        printf("Array not created yet! Please create array first.\n");
        system("pause");
        return;
    }

    while (!*exit_flag) {
        print_menu_header(HEADER_INSERT);
        printf("Current array: ");
        print(mass, NULL, ' ', '\n');
        printf("\n");
        printf(INSERT_MENU_TEXT);

        user_choose = get_user_choice(0, INSERT_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Insert in front selected.\n");
            printf("Enter value to insert: ");
            scanf_s("%lf", &value);
            while (getchar() != '\n');
            push_front(mass, value);
            printf("Value %.2lf inserted at front.\n", value);
            system("pause");
            break;
        case 2:
            printf("Insert in back selected.\n");
            printf("Enter value to insert: ");
            scanf_s("%lf", &value);
            while (getchar() != '\n');
            push_back(mass, value);
            printf("Value %.2lf inserted at back.\n", value);
            system("pause");
            break;
        case 3:
            printf("Insert by position selected.\n");
            printf("Enter position (0 to %d): ", mass->size);
            scanf_s("%d", &pos);
            printf("Enter value to insert: ");
            scanf_s("%lf", &value);
            while (getchar() != '\n');
            status = insert(mass, pos, value);
            if (status == SUCCESS) {
                printf("Value %.2lf inserted at position %d.\n", value, pos);
            }
            else {
                printf("Failed to insert value.\n");
            }
            system("pause");
            break;
        case 4:
            return;
        }
    }
}

void erase_menu(bool* exit_flag, DMassive* mass, int mod) {
    int user_choose = -1;
    int pos = 0;
    Status status;

    if (mass->data == NULL || mass->size == 0) {
        printf("Array is empty or not created yet!\n");
        system("pause");
        return;
    }

    while (!*exit_flag) {
        print_menu_header(HEADER_ERASE);
        printf("Current array: ");
        print(mass, NULL, ' ', '\n');
        printf("\n");
        printf(ERASE_MENU_TEXT);

        user_choose = get_user_choice(0, ERASE_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Delete from front selected.\n");
            status = pop_front(mass);
            if (status == SUCCESS) {
                printf("First element removed.\n");
            }
            else {
                printf("Failed to remove element.\n");
            }
            system("pause");
            break;
        case 2:
            printf("Delete from back selected.\n");
            status = pop_back(mass);
            if (status == SUCCESS) {
                printf("Last element removed.\n");
            }
            else {
                printf("Failed to remove element.\n");
            }
            system("pause");
            break;
        case 3:
            printf("Delete by position selected.\n");
            printf("Enter position to delete (0 to %d): ", mass->size - 1);
            scanf_s("%d", &pos);
            while (getchar() != '\n');
            status = erase(mass, pos);
            if (status == SUCCESS) {
                printf("Element at position %d removed.\n", pos);
            }
            else {
                printf("Failed to remove element.\n");
            }
            system("pause");
            break;
        case 4:
            return;
        }
    }
}

void search_menu(bool* exit_flag, DMassive* mass) {
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
    int mod = 0;
    bool exit_flag = false;
    DMassive mass = { 0 };

    while (!exit_flag) {
        print_menu_header(HEADER_MAIN);
        print(&mass, "Your array: ", ' ', '\n');
        printf("\n");
        printf(MAIN_MENU_BASE_TEXT);

        user_choose = get_user_choice(0, MAIN_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            exit_flag = true;
            printf("Exiting program...\n");
            break;
        case 1:
            create_arr_menu(&exit_flag, &mass);
            break;
        case 2:
            mod = mod_menu(&exit_flag);
            if (!exit_flag && mod != 0) {
                insert_menu(&exit_flag, &mass, mod);
            }
            break;
        case 3:
            mod = mod_menu(&exit_flag);
            if (!exit_flag && mod != 0) {
                erase_menu(&exit_flag, &mass, mod);
            }
            break;
        case 4:
            search_menu(&exit_flag, &mass);
            break;
        case 5:
            printf("Shuffle (TBD)\n");
            system("pause");
            break;
        case 6:
            sort_mode_menu(&exit_flag, &mass);
            system("pause");
            break;
        case 7:
            clear_memory(&mass);
            printf("The array has been cleared.\n");
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
        //case 10:
        //    printf("Test func\n");
        //    revers_mass(&mass);
        //    break;
        }
    }

    if (mass.data != NULL) {
        clear_memory(&mass);
    }
}
