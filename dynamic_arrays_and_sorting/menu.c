#include <stdio.h>
#include "windows.h"
#include "menu.h"
#include <stdbool.h>
#include <stdlib.h>
#include "dmassive.h"
#include <string.h>
#include <errno.h>


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
            return;
        case 2:
            printf("Descending sort mode selected.\n");
            sort_menu(exit_flag, mass);
            revers_mass(mass);
            return;
        case 3:
            return;
        }
    }
}

void sort_menu(bool* exit_flag, DMassive* mass) {
    int user_choose = -1;
    if (mass->data == NULL || mass->size == 0) {
        printf("Array is empty or not created yet!\n");
        system("pause");
        return;
    }


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
            quick_sort(mass);
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
            return;
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
            return;
        case 3:
            printf("Manual input selected.\n");
            size = get_array_size();
            set_memory(mass, size);

            printf("Enter %d array elements:\n", size);
            for (int i = 0; i < size; i++) {
                printf("Element %d: ", i + 1);
                int real_pos = get_pos(mass, i);
                if (scanf_s("%lf", &mass->data[real_pos]) != 1) {
                    printf("Input error! Try again.\n");
                    i--;
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
            }
            printf("Array created with %d manually entered elements.\n", size);
            system("pause");
            return;
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
        print(mass, "Your array: ", ' ', '\n');
        printf("\n");
        printf(INSERT_MENU_TEXT);

        user_choose = get_user_choice(0, INSERT_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            if (mod == MOD_ONE) {
                printf("Insert in front selected (single element).\n");
                printf("Enter value to insert: ");
                scanf_s("%lf", &value);
                while (getchar() != '\n');
                push_front(mass, value);
                printf("Value %.2lf inserted at front.\n", value);
            }
            else {
                printf("Insert in front selected (multiple elements).\n");
                printf("How many elements to insert? ");
                int count;
                scanf_s("%d", &count);
                while (getchar() != '\n');

                if (count <= 0) {
                    printf("Invalid number of elements.\n");
                    break;
                }

                double* values = (double*)malloc(count * sizeof(double));
                if (values == NULL) {
                    printf("Memory allocation failed!\n");
                    break;
                }

                printf("Enter %d values:\n", count);
                for (int i = 0; i < count; i++) {
                    printf("Value %d: ", i + 1);
                    scanf_s("%lf", &values[i]);
                    while (getchar() != '\n');
                }

                push_front_several(mass, count, values);
                printf("%d elements inserted at front.\n", count);
                free(values);
            }
            system("pause");
            break;

        case 2:
            if (mod == MOD_ONE) {
                printf("Insert in back selected (single element).\n");
                printf("Enter value to insert: ");
                scanf_s("%lf", &value);
                while (getchar() != '\n');
                push_back(mass, value);
                printf("Value %.2lf inserted at back.\n", value);
            }
            else {
                printf("Insert in back selected (multiple elements).\n");
                printf("How many elements to insert? ");
                int count;
                scanf_s("%d", &count);
                while (getchar() != '\n');

                if (count <= 0) {
                    printf("Invalid number of elements.\n");
                    break;
                }

                double* values = (double*)malloc(count * sizeof(double));
                if (values == NULL) {
                    printf("Memory allocation failed!\n");
                    break;
                }

                printf("Enter %d values:\n", count);
                for (int i = 0; i < count; i++) {
                    printf("Value %d: ", i + 1);
                    scanf_s("%lf", &values[i]);
                    while (getchar() != '\n');
                }

                push_back_several(mass, count, values);
                printf("%d elements inserted at back.\n", count);
                free(values);
            }
            system("pause");
            break;

        case 3:
            if (mod == MOD_ONE) {
                printf("Insert by position selected (single element).\n");
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
            }
            else {
                printf("Insert by position selected (multiple elements).\n");
                printf("Enter position (0 to %d): ", mass->size);
                scanf_s("%d", &pos);
                printf("How many elements to insert? ");
                int count;
                scanf_s("%d", &count);
                while (getchar() != '\n');

                if (count <= 0) {
                    printf("Invalid number of elements.\n");
                    break;
                }

                double* values = (double*)malloc(count * sizeof(double));
                if (values == NULL) {
                    printf("Memory allocation failed!\n");
                    break;
                }

                printf("Enter %d values:\n", count);
                for (int i = 0; i < count; i++) {
                    printf("Value %d: ", i + 1);
                    scanf_s("%lf", &values[i]);
                    while (getchar() != '\n');
                }

                status = insert_several(mass, pos, count, values);
                if (status == SUCCESS) {
                    printf("%d elements inserted at position %d.\n", count, pos);
                }
                else {
                    printf("Failed to insert elements.\n");
                }
                free(values);
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
        print(mass, "Your array: ", ' ', '\n');
        printf("\n");
        printf(ERASE_MENU_TEXT);

        user_choose = get_user_choice(0, ERASE_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            if (mod == MOD_ONE) {
                printf("Delete from front selected (single element).\n");
                status = pop_front(mass);
                if (status == SUCCESS) {
                    printf("First element removed.\n");
                }
                else {
                    printf("Failed to remove element.\n");
                }
            }
            else {
                printf("Delete from front selected (multiple elements).\n");
                printf("How many elements to delete? (max: %d): ", mass->size);
                int count;
                scanf_s("%d", &count);
                while (getchar() != '\n');

                if (count <= 0 || count > mass->size) {
                    printf("Invalid number of elements.\n");
                    break;
                }

                status = pop_front_several(mass, count);
                if (status == SUCCESS) {
                    printf("%d elements removed from front.\n", count);
                }
                else {
                    printf("Failed to remove elements.\n");
                }
            }
            system("pause");
            break;

        case 2:
            if (mod == MOD_ONE) {
                printf("Delete from back selected (single element).\n");
                status = pop_back(mass);
                if (status == SUCCESS) {
                    printf("Last element removed.\n");
                }
                else {
                    printf("Failed to remove element.\n");
                }
            }
            else {
                printf("Delete from back selected (multiple elements).\n");
                printf("How many elements to delete? (max: %d): ", mass->size);
                int count;
                scanf_s("%d", &count);
                while (getchar() != '\n');

                if (count <= 0 || count > mass->size) {
                    printf("Invalid number of elements.\n");
                    break;
                }

                status = pop_back_several(mass, count);
                if (status == SUCCESS) {
                    printf("%d elements removed from back.\n", count);
                }
                else {
                    printf("Failed to remove elements.\n");
                }
            }
            system("pause");
            break;

        case 3:
            if (mod == MOD_ONE) {
                printf("Delete by position selected (single element).\n");
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
            }
            else {
                printf("Delete by position selected (multiple elements).\n");
                printf("Enter starting position (0 to %d): ", mass->size - 1);
                scanf_s("%d", &pos);
                printf("How many elements to delete? (max: %d): ", mass->size - pos);
                int count;
                scanf_s("%d", &count);
                while (getchar() != '\n');

                if (count <= 0 || pos + count > mass->size) {
                    printf("Invalid number of elements.\n");
                    break;
                }

                status = erase_several(mass, pos, count);
                if (status == SUCCESS) {
                    printf("%d elements removed starting from position %d.\n", count, pos);
                }
                else {
                    printf("Failed to remove elements.\n");
                }
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
    double target;
    if (mass->data == NULL || mass->size == 0) {
        printf("Array is empty or not created yet!\n");
        system("pause");
        return;
    }

    while (!*exit_flag) {
        printf("Enter the item you are going to search for: ");
        scanf_s("%lf", &target);
        while (getchar() != '\n');
        clear_screen();

        print_menu_header(HEADER_SEARCH);
        printf(SEARCH_MENU_TEXT);

        user_choose = get_user_choice(0, SEARCH_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Count: %d\n", count_occurrences(mass, target));
            system("pause");
            return;
        case 2:
            printf("First occurrence: %d\n", binary_search_left(mass, target));
            system("pause");
            return;
        case 3:
            printf("Last occurrence: %d\n", binary_search_right(mass, target));
            system("pause");
            return;
        case 4:
            printf("All occurrences search selected.\n");
            int occurrence_count;
            int* indices = find_all_occurrences(mass, target, &occurrence_count);
            if (indices != NULL) {
                printf("The found indexes of the elements:\n");
                for (int i = 0; i < occurrence_count; i++) {
                    printf("%d ", indices[i]);
                }
                printf("\n");
            }
            else{
                printf("The element %.2f was not found\n", target);
            }
            system("pause");
            free(indices);
            return;
        case 5:
            return;
        }
    }
}

int choose_file_properties_menu(bool* exit_flag, char* dir, char* file_name, char type) {
    char temp_file_name[100];

    printf(CHOOSE_FILE_NAME_TEXT);

    if (fgets(temp_file_name, sizeof(temp_file_name), stdin) == NULL) {
        return 0;
    }

    temp_file_name[strcspn(temp_file_name, "\n")] = '\0';

    if (strlen(temp_file_name) == 0) {
        return 0;
    }

    strcpy_s(file_name, 100, temp_file_name);

    if (type == 'w') {
        strcat_s(file_name, 100, ".txt");
    }

    int user_choice = -1;
    while (!*exit_flag) {
        clear_screen();
        printf(PATH_MENU_TEXT);
        user_choice = get_user_choice(0, FILE_PROPERTIES_MENU);

        switch (user_choice) {
        case 0:
            *exit_flag = true;
            return 0;
        case 1:
            strcpy_s(dir, 100, ".\\");
            Sleep(5);
            printf("The current directory is set for saving/writing.");
            return 1;
        case 2: {
            clear_screen();
            printf(DIR_FILE_NAME_TEXT);

            char temp_dir[100];
            if (fgets(temp_dir, sizeof(temp_dir), stdin) == NULL) {
                return 0;
            }

            temp_dir[strcspn(temp_dir, "\n")] = '\0';

            strcpy_s(dir, 100, temp_dir);

            size_t len = strlen(dir);
            if (len > 0 && dir[len - 1] != '\\' && dir[len - 1] != '/') {
                strcat_s(dir, 100, "\\");
            }

            printf("The user directory is set for saving/writing.");
            Sleep(5);
            return 1;
        }
        case 3:
            return 0;
        }
    }
    return 0;
}

void main_menu() {
    int user_choose = -1;
    int mod = 0;
    bool exit_flag = false;
    DMassive mass = { 0, 0, 0, 0 };

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
            printf("Shuffle mass\n");
            shake_mass(&mass);
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
        case 8: {
            char dir[100] = ".\\";
            char file_name[100];
            mod = choose_file_properties_menu(&exit_flag, dir, file_name, 'w');
            if (!exit_flag && mod != 0) {
                write_mass_in_file(dir, file_name, &mass);
                Sleep(5);
            }

            break;
        }
        case 9: {
            char dir[100] = ".";
            char file_name[100];
            mod = choose_file_properties_menu(&exit_flag, dir, file_name, 'r');
            if (!exit_flag && mod != 0) {
                read_mass_from_file(dir, file_name, &mass);
                Sleep(5);
                system("pause");
            }
            break;
        }
        }
    }

    if (mass.data != NULL) {
        clear_memory(&mass);
    }
}
