#include <stdio.h>
#include "dmassive.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>


int calculate_capacity(int size) {
    return ((size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY) * STEP_OF_CAPACITY;
}

int get_pos(DMassive* mass, int pos) {
    if (mass == NULL || mass->size == 0) return -1;
    return (mass->front + pos) % mass->capacity;
}

double get_element(DMassive* mass, int logical_index) {
    int real_index = get_pos(mass, logical_index);
    return mass->data[real_index];
}

int get_next_pos(DMassive* mass, int pos) {
    return (pos + 1) % mass->capacity;
}

int get_prev_pos(DMassive* mass, int pos) {
    return (pos - 1 + mass->capacity) % mass->capacity;
}

int is_empty(DMassive* mass) {
    return (mass == NULL || mass->size == 0);
}

int is_full(DMassive* mass) {
    return (mass != NULL && mass->size == mass->capacity);
}

void right_shift(DMassive* mass, int pos) {
    if (mass == NULL || mass->size == 0 || pos < 0 || pos >= mass->size) return;

    int real_pos = get_pos(mass, pos);
    for (int i = mass->size; i > pos; i--) {
        int current_real = get_pos(mass, i);
        int prev_real = get_pos(mass, i - 1);
        mass->data[current_real] = mass->data[prev_real];
    }
    mass->data[real_pos] = 0.0;
}

void left_shift(DMassive* mass, int pos) {
    if (mass == NULL || mass->size == 0 || pos < 0 || pos >= mass->size) return;

    for (int i = pos; i < mass->size - 1; i++) {
        int current_real = get_pos(mass, i);
        int next_real = get_pos(mass, i + 1);
        mass->data[current_real] = mass->data[next_real];
    }
    mass->data[get_pos(mass, mass->size - 1)] = 0.0;
}

int search_cmp(double a, double b) {
    const double EPSILON = 1e-2;

    if (fabs(a - b) < EPSILON) {
        return 0;
    }
    else if (a < b) {
        return -1;
    }
    else {
        return 1;
    }
}

bool sorted_left_to_right(DMassive* mass) {
    if (mass == NULL || mass->size <= 1) return true;

    int current = mass->front;
    for (int i = 0; i < mass->size - 1; i++) {
        int next = get_next_pos(mass, current);
        if (mass->data[current] > mass->data[next]) {
            return false;
        }
        current = next;
    }
    return true;
}

bool sorted_right_to_left(DMassive* mass) {
    if (mass == NULL || mass->size <= 1) return true;

    int current = mass->front;
    for (int i = 0; i < mass->size - 1; i++) {
        int next = get_next_pos(mass, current);
        if (mass->data[current] < mass->data[next]) {
            return false;
        }
        current = next;
    }
    return true;
}

void swap(double* first, double* second) {
    double temp = *first;
    *first = *second;
    *second = temp;
}

void set_memory(DMassive* mass, int size) {
    if (mass == NULL) return;

    if (size <= 0) size = STEP_OF_CAPACITY;

    mass->capacity = calculate_capacity(size);
    mass->size = size;
    mass->front = 0;
    mass->back = (size > 0) ? (size - 1) % mass->capacity : -1;
    mass->data = (double*)malloc(mass->capacity * sizeof(double));

    if (mass->data != NULL) {
        for (int i = 0; i < mass->capacity; i++) {
            mass->data[i] = 0.0;
        }
    }
}

void clear_memory(DMassive* mass) {
    if (mass == NULL) return;

    free(mass->data);
    mass->data = NULL;
    mass->size = 0;
    mass->capacity = 0;
    mass->front = 0;
    mass->back = -1;
}

void resize(DMassive* mass, int new_size) {
    if (mass == NULL) return;

    if (new_size <= 0) {
        new_size = 0;
    }

    if (new_size > mass->capacity) {
        int new_capacity = calculate_capacity(new_size);
        double* new_data = (double*)malloc(new_capacity * sizeof(double));

        if (new_data == NULL) {
            printf("Ошибка выделения памяти!\n");
            return;
        }

        int copy_count = (mass->size < new_size) ? mass->size : new_size;
        for (int i = 0; i < copy_count; i++) {
            int old_pos = get_pos(mass, i);
            new_data[i] = mass->data[old_pos];
        }

        for (int i = copy_count; i < new_size; i++) {
            new_data[i] = 0.0;
        }

        free(mass->data);
        mass->data = new_data;
        mass->capacity = new_capacity;
        mass->size = new_size;
        mass->front = 0;
        mass->back = (new_size > 0) ? (new_size - 1) % mass->capacity : -1;
    }
    else if (new_size < mass->size) {
        mass->size = new_size;
        if (new_size > 0) {
            mass->back = (mass->front + new_size - 1) % mass->capacity;
        }
        else {
            mass->back = -1;
        }
    }
    else {
        mass->size = new_size;
    }
}

void fill_elementary(DMassive* mass) {
    if (mass == NULL || mass->data == NULL) return;

    for (int i = 0; i < mass->size; i++) {
        int real_pos = get_pos(mass, i);
        mass->data[real_pos] = (double)i;
    }
}

void fill_randomly(DMassive* mass, double min_val, double max_val) {
    if (mass == NULL || mass->data == NULL) return;

    srand(time(NULL));
    double range = max_val - min_val;

    for (int i = 0; i < mass->size; i++) {
        int real_pos = get_pos(mass, i);
        double random_val = ((double)rand() / RAND_MAX) * range + min_val;
        mass->data[real_pos] = random_val;
    }
}

void fill_manual_input(DMassive* mass) {
    if (mass == NULL || mass->data == NULL) return;

    for (int i = 0; i < mass->size; i++) {
        int real_pos = get_pos(mass, i);
        if (scanf_s("%lf", &mass->data[real_pos]) != 1) {
            printf("Input error! Try again.\n");
            i--;
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
    }
}

void shake_mass(DMassive* mass) {
    if (mass == NULL || mass->data == NULL || mass->size == 0) {
        printf("Your array has not been created yet");
        return;
    }
    for (int i = 0; i < mass->size; i++) {
        int r = rand() % (mass->size);
        double c = mass->data[r];
        mass->data[r] = mass->data[i];
        mass->data[i] = c;
    }
}

void push_front(DMassive* mass, double value) {
    if (mass == NULL) return;

    if (is_full(mass)) { // изменить
        resize(mass, mass->size + 1);
        mass->front = (mass->front - 1 + mass->capacity) % mass->capacity;
        mass->data[mass->front] = value;
        return;
    }

    mass->front = get_prev_pos(mass, mass->front);
    mass->data[mass->front] = value;
    mass->size++;
    if (mass->back == -1) mass->back = mass->front;
}

void push_back(DMassive* mass, double value) {
    if (mass == NULL) return;

    if (is_full(mass)) { // изменить
        resize(mass, mass->size + 1);
        mass->data[mass->back] = value;
        return;
    }

    mass->back = get_next_pos(mass, mass->back);
    mass->data[mass->back] = value;
    mass->size++;
    if (mass->size == 1) mass->front = mass->back;
}

void revers_mass(DMassive* mass) {
    int left = 0;
    int right = mass->size - 1;
    while (left < right) {
        int real_left = get_pos(mass, left);
        int real_right = get_pos(mass, right);
        swap(&mass->data[real_left], &mass->data[real_right]);
        
        left++;
        right--;
    }
}

Status insert(DMassive* mass, int pos, double value) {
    if (mass == NULL) return ERROREXIT;
    if (pos < 0 || pos > mass->size) return ERROREXIT;

    if (pos == 0) {
        push_front(mass, value);
        return SUCCESS;
    }

    if (pos == mass->size) {
        push_back(mass, value);
        return SUCCESS;
    }

    if (is_full(mass)) {
        resize(mass, mass->size + 1);
        for (int i = mass->size - 1; i > pos; i--) {
            mass->data[i] = mass->data[i - 1];
        }
        mass->data[pos] = value;
        return SUCCESS;
    }

    int real_pos = get_pos(mass, pos);
    for (int i = mass->size; i > pos; i--) {
        int current_real = get_pos(mass, i);
        int prev_real = get_pos(mass, i - 1);
        mass->data[current_real] = mass->data[prev_real];
    }

    mass->data[real_pos] = value;
    mass->size++;
    mass->back = get_pos(mass, mass->size - 1);

    return SUCCESS;
}

Status pop_front(DMassive* mass) {
    if (is_empty(mass)) return ERROREXIT;

    mass->data[mass->front] = 0.0;
    mass->front = get_next_pos(mass, mass->front);
    mass->size--;

    if (mass->size == 0) {
        mass->front = 0;
        mass->back = -1;
    }

    return SUCCESS;
}

Status pop_back(DMassive* mass) {
    if (is_empty(mass)) return ERROREXIT;

    mass->data[mass->back] = 0.0;
    mass->back = get_prev_pos(mass, mass->back);
    mass->size--;

    if (mass->size == 0) {
        mass->front = 0;
        mass->back = -1;
    }

    return SUCCESS;
}

Status erase(DMassive* mass, int pos) {
    if (mass == NULL || is_empty(mass)) return ERROREXIT;
    if (pos < 0 || pos >= mass->size) return ERROREXIT;

    if (pos == 0) return pop_front(mass);
    if (pos == mass->size - 1) return pop_back(mass);

    for (int i = pos; i < mass->size - 1; i++) {
        int current_real = get_pos(mass, i);
        int next_real = get_pos(mass, i + 1);
        mass->data[current_real] = mass->data[next_real];
    }

    mass->size--;
    mass->back = get_pos(mass, mass->size - 1);

    return SUCCESS;
}

void push_front_several(DMassive* mass, int count, const double* values) {
    if (mass == NULL || values == NULL || count <= 0) return;

    for (int i = count - 1; i >= 0; i--) {
        push_front(mass, values[i]);
    }
}

void push_back_several(DMassive* mass, int count, const double* values) {
    if (mass == NULL || values == NULL || count <= 0) return;

    for (int i = 0; i < count; i++) {
        push_back(mass, values[i]);
    }
}

Status insert_several(DMassive* mass, int pos, int count, const double* values) {
    if (mass == NULL || values == NULL || count <= 0) return ERROREXIT;
    if (pos < 0 || pos > mass->size) return ERROREXIT;

    for (int i = 0; i < count; i++) {
        Status status = insert(mass, pos + i, values[i]);
        if (status != SUCCESS) {
            return status;
        }
    }
    return SUCCESS;
}

Status pop_front_several(DMassive* mass, int count) {
    if (mass == NULL || count <= 0) return ERROREXIT;

    for (int i = 0; i < count; i++) {
        Status status = pop_front(mass);
        if (status != SUCCESS) {
            return status;
        }
    }
    return SUCCESS;
}

Status pop_back_several(DMassive* mass, int count) {
    if (mass == NULL || count <= 0) return ERROREXIT;

    for (int i = 0; i < count; i++) {
        Status status = pop_back(mass);
        if (status != SUCCESS) {
            return status;
        }
    }
    return SUCCESS;
}

Status erase_several(DMassive* mass, int pos, int count) {
    if (mass == NULL || count <= 0) return ERROREXIT;
    if (pos < 0 || pos >= mass->size) return ERROREXIT;


    for (int i = 0; i < count; i++) {
        Status status = erase(mass, pos);
        if (status != SUCCESS) {
            return status;
        }
    }
    return SUCCESS;
}

int binary_search_left(DMassive* mass, double target) {
    if (mass == NULL || mass->size == 0) return -1;

    if (!sorted_left_to_right(mass)) {
        quick_sort(mass);
    }

    int left = 0;
    int right = mass->size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        double mid_val = get_element(mass, mid);
        int comparison = search_cmp(mid_val, target);

        if (comparison == 0) {
            result = mid;
            right = mid - 1;
        }
        else if (comparison < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

int binary_search_right(DMassive* mass, double target) {
    if (mass == NULL || mass->size == 0) return -1;

    if (!sorted_left_to_right(mass)) {
        quick_sort(mass);
    }

    int left = 0;
    int right = mass->size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        double mid_val = get_element(mass, mid);
        int comparison = search_cmp(mid_val, target);

        if (comparison == 0) {
            result = mid;
            left = mid + 1;
        }
        else if (comparison < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

int count_occurrences(DMassive* mass, double target) {
    if (mass == NULL || mass->size == 0) return 0;
    
    int count = 0;
    for (int i = 0; i < mass->size; i++) {
        if (search_cmp(get_element(mass, i), target) == 0) {
            count++;
        }
    }
    return count;
}

int* find_all_occurrences(DMassive* mass, double target, int* count) {
    if (mass == NULL || mass->size == 0) {
        *count = 0;
        return NULL;
    }
    
    *count = count_occurrences(mass, target);
    
    if (*count == 0) {
        return NULL;
    }
    
    int* indices = (int*)malloc((*count) * sizeof(int));
    if (indices == NULL) {
        *count = 0;
        return NULL;
    }
    
    int idx = 0;
    for (int i = 0; i < mass->size; i++) {
        if (search_cmp(get_element(mass, i), target) == 0) {
            indices[idx++] = i;
        }
    }
    
    return indices;
}

void print(DMassive* mass, const char* text, char sep, char end) {
    if (mass == NULL || mass->data == NULL || mass->size == 0) {
        printf("Your array not created yet%c", end);
        return;
    }

    if (text != NULL) {
        printf("%s", text);
    }

    printf("< ");
    for (int i = 0; i < mass->size; i++) {
        int real_pos = get_pos(mass, i);
        printf("%.2lf", mass->data[real_pos]);
        if (i < mass->size - 1) {
            printf("%c ", sep);
        }
    }
    printf(" >%c", end);
}

void write_mass_in_file(char* dir, char* file_name, DMassive* mass) {
    char full_path[100];

    strcpy_s(full_path, sizeof(full_path), dir);
    strncat_s(full_path, 100, file_name, 100);

    FILE* output_file = NULL;
    errno_t error;

    error = fopen_s(&output_file, full_path, "w+");

    if (output_file == NULL || error != 0) {
        printf("Ошибка открытия файла для экспорта массива. Код ошибки: %d.\n", error);
        return;
    }
    else {
        printf("Файл %s открыт.\n", full_path);

        fprintf(output_file, "%d\n", mass->size);
        for (int i = 0; i < mass->size - 1; i++) {
            int index = (mass->front + i) % (mass->size);
            fprintf(output_file, "%.2lf ", mass->data[index]);
        }
        if (mass->data != NULL)
            fprintf(output_file, "%.2lf", mass->data[(mass->front +
                mass->size - 1) % (mass->size)]);
        printf("Массив записан в файл.\n");

        fclose(output_file);
        printf("Файл %s закрыт.\n", full_path);
    }
}

void read_mass_from_file(char* dir, char* file_name, DMassive* mass) {
    char full_path[100];

    strcpy_s(full_path, sizeof(full_path), dir);
    strncat_s(full_path, 100, file_name, 100);

    FILE* input_file = NULL;
    errno_t error;

    error = fopen_s(&input_file, full_path, "r");

    if (input_file == NULL || error != 0) {
        printf("Ошибка открытия файла считывания массива. Код ошибки: %d.\n", error);
        return;
    }
    else {
        printf("Файл %s открыт.\n", full_path);
        fscanf_s(input_file, "%d\n", &mass->size);
        if (mass->size <= 0) {
            printf("Введено неверное количество элементов массива.");
            return;
        }
        set_memory(mass, mass->size);
        for (int i = 0; i < mass->size; i++) {
            double value;
            if (fscanf_s(input_file, "%lf\n", &value) != 1) {
                printf("Ошибка чтения элемента %d из файла.\n", i);
                fclose(input_file);
                clear_memory(mass);
                return;
            }

            int index = get_pos(mass, i);
            mass->data[index] = value;
        }
        printf("Массив успешно загружен из файла. Загружено %d элементов.\n", mass->size);
        fclose(input_file);
        printf("Файл %s закрыт.\n", full_path);
        return;
    }
}































void bubble_sort(DMassive* mass) {
    if (mass == NULL || mass->size <= 1) return;

    for (int i = 0; i < mass->size - 1; i++) {
        for (int j = 0; j < mass->size - i - 1; j++) {
            int real_j = get_pos(mass, j);
            int real_j1 = get_pos(mass, j + 1);

            if (mass->data[real_j] > mass->data[real_j1]) {
                swap(&mass->data[real_j], &mass->data[real_j1]);
            }
        }
    }
}

void bubble_sort_pro(DMassive* mass) {
    if (mass == NULL || mass->size <= 1) return;

    bool swapped;
    for (int i = 0; i < mass->size - 1; i++) {
        swapped = false;

        for (int j = 0; j < mass->size - i - 1; j++) {
            int real_j = get_pos(mass, j);
            int real_j1 = get_pos(mass, j + 1);

            if (mass->data[real_j] > mass->data[real_j1]) {
                swap(&mass->data[real_j], &mass->data[real_j1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

void shell_sort_knuth(DMassive* mass) {
    if (mass == NULL || mass->size <= 1) return;

    int gap = 1;
    while (gap < mass->size / 3) {
        gap = 3 * gap + 1; // 1, 4, 13, 40, 121, ...
    }

    while (gap > 0) {
        for (int i = gap; i < mass->size; i++) {
            int real_i = get_pos(mass, i);
            double temp = mass->data[real_i];
            int j = i;

            while (j >= gap) {
                int real_j_gap = get_pos(mass, j - gap);
                if (mass->data[real_j_gap] > temp) {
                    int real_j = get_pos(mass, j);
                    mass->data[real_j] = mass->data[real_j_gap];
                    j -= gap;
                }
                else {
                    break;
                }
            }

            int real_j = get_pos(mass, j);
            mass->data[real_j] = temp;
        }

        gap /= 3;
    }
}

void bogo_sort(DMassive* mass) {
    if (mass == NULL || mass->size <= 1) return;

    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }

    bool sorted = true;
    for (int i = 0; i < mass->size - 1; i++) {
        int real_i = get_pos(mass, i);
        int real_i1 = get_pos(mass, i + 1);
        if (mass->data[real_i] > mass->data[real_i1]) {
            sorted = false;
            break;
        }
    }

    if (sorted) return;

    const int MAX_ATTEMPTS = 100000;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        for (int i = mass->size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int real_i = get_pos(mass, i);
            int real_j = get_pos(mass, j);
            swap(&mass->data[real_i], &mass->data[real_j]);
        }

        sorted = sorted_left_to_right(mass);

        if (sorted) return;

        attempts++;
    }

    printf("Bogo sort exceeded maximum attempts (%d)\n", MAX_ATTEMPTS);
}

static int partition(DMassive* mass, int low, int high) {
    //if (low >= high) return low;

    int pivot_index = (low + high) / 2;
    int pivot_real = get_pos(mass, pivot_index);
    double pivot = mass->data[pivot_real];

    int high_real = get_pos(mass, high);
    swap(&mass->data[high_real], &mass->data[pivot_real]);

    int i = low - 1;

    for (int j = low; j < high; j++) {
        int j_real = get_pos(mass, j);
        if (search_cmp(mass->data[j_real], pivot) < 0) { // mass->data[j_real] < pivot
            i++;
            int i_real = get_pos(mass, i);
            swap(&mass->data[i_real], &mass->data[j_real]);
        }
    }

    i++; // Вернуть опорный на место
    int high_real_new = get_pos(mass, high);
    int real_i = get_pos(mass, i);
    swap(&mass->data[real_i], &mass->data[high_real_new]);
    return i;
}

static void quick_sort_recursive(DMassive* mass, int low, int high) { // static так как попытка вызова из другого файла приведет к неизвестным последствиям
    if (low < high) {
        int border = partition(mass, low, high);

        quick_sort_recursive(mass, low, border - 1);
        quick_sort_recursive(mass, border + 1, high);
    }
}

void quick_sort(DMassive* mass) {
    if (mass == NULL || mass->data == NULL || mass->size <= 1) return;
    quick_sort_recursive(mass, 0, mass->size - 1);
}


