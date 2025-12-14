#include <stdio.h>
#include "dmassive.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int calculate_capacity(int size) {
    return ((size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY) * STEP_OF_CAPACITY;
}

int get_pos(DMassive* mass, int pos) {
    if (mass == NULL || mass->size == 0) return -1;
    return (mass->front + pos) % mass->capacity;
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
            printf("ќшибка выделени€ пам€ти!\n");
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

    printf("¬ведите %d элементов массива:\n", mass->size);
    for (int i = 0; i < mass->size; i++) {
        int real_pos = get_pos(mass, i);
        printf("Ёлемент %d: ", i + 1);
        scanf_s("%lf", &mass->data[real_pos]);
    }
}

void push_front(DMassive* mass, double value) {
    if (mass == NULL) return;

    if (is_full(mass)) {
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

    if (is_full(mass)) {
        resize(mass, mass->size + 1);
        mass->data[mass->back] = value;
        return;
    }

    mass->back = get_next_pos(mass, mass->back);
    mass->data[mass->back] = value;
    mass->size++;
    if (mass->size == 1) mass->front = mass->back;
}

Status insert(DMassive* mass, int pos, double value) {
    if (mass == NULL) return ERROR;
    if (pos < 0 || pos > mass->size) return ERROR;

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
    if (is_empty(mass)) return ERROR;

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
    if (is_empty(mass)) return ERROR;

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
    if (mass == NULL || is_empty(mass)) return ERROR;
    if (pos < 0 || pos >= mass->size) return ERROR;

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





























void bubble_sort(double* mass, int size, int front, int back) {
    if (mass == NULL || size <= 1) {
        return;
    }

    for (int i = front; i <= back; i++) {
        for (int j = front; j <= back - i; j++) {
            if (mass[j] > mass[j + 1]) {
                double temp = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_pro(double* mass, int size, int front, int back) {
    if (mass == NULL || size <= 1) {
        return;
    }
    bool swapped;

    for (int i = front; i <= back; i++) {
        swapped = false;

        for (int j = front; j <= back - i; j++) {
            if (mass[j] > mass[j + 1]) {
                double temp = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

void shell_sort_knuth(double* mass, int size, int front, int back) {
    int gap = front;
    while (gap < (back - front + 1) / 3) {
        gap = 3 * gap + 1; // 1, 4, 13, 40, 121, ...
    }

    while (gap > 0) {
        for (int i = gap; i <= (back - front + 1); i++) {
            for (int j = i; j >= gap && mass[j - gap] > mass[j]; j -= gap) {
                double temp = mass[j];
                mass[j] = mass[j - gap];
                mass[j - gap] = temp;
            }
        }
        gap /= 3;
    }
}

void bogo_sort(double* mass, int size, int front, int back) {
    // rofl semi-AI-generated
    if (mass == NULL || size <= 1 || front > back || front < 0 || back >= size) {
        return;
    }

    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    bool sorted = true;
    for (int i = front; i < back; i++) {
        if (mass[i] > mass[i + 1]) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        return;
    }

    int attempts = 0;
    const int MAX_ATTEMPTS = 100000;

    while (attempts < MAX_ATTEMPTS) {
        for (int i = back; i > front; i--) {
            int j = front + rand() % (i - front + 1);

            double temp = mass[i];
            mass[i] = mass[j];
            mass[j] = temp;
        }

        sorted = true;
        for (int i = front; i < back; i++) {
            if (mass[i] > mass[i + 1]) {
                sorted = false;
                break;
            }
        }

        if (sorted) {
            return;
        }

        attempts++;
    }
}

