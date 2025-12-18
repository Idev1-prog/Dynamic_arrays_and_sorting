#pragma once
#include <stdio.h>
#include "dmassive.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

/**
* Базовый размер и шаг расширения хранилища
*/
#define STEP_OF_CAPACITY 15

/**
* Возможные статусы завершения функции
*/
enum Status { SUCCESS, WARNING, ERROREXIT };

/**
* Структура, объявляющая динамический массив с кольцевым буфером и запасом памяти
*
* @param data динамический массив (хранилище данных)
* @param size размер заполненной части хранилища
* @param capacity вместимость хранилища
* @param front индекс первого элемента
* @param back индекс последнего элемента
*/
struct DMassive {
    double* data;
    int size;
    int capacity;
    int front;
    int back;
};

typedef struct DMassive DMassive;
typedef enum Status Status;

/* Вспомогательные функции */

/**
* Функция вычисления размера хранилища
*
* @param size необходимый размер заполненной части хранилища
* @return capacity подходящая вместимость хранилища
*/
int calculate_capacity(int size);

/**
* Функция получения реального индекса в массиве
*
* @param mass указатель на массив типа структуры DMassive
* @param pos индекс для перерасчета (пользовательский)
* @return реальный индекс элемента в массиве
*/
int get_pos(DMassive* mass, int pos);

double get_element(DMassive* mass, int logical_index);

/**
* Функция получения реального индекса следующего элемента в массиве
*
* @param mass указатель на массив типа структуры DMassive
* @param pos текущий индекс (пользовательский)
* @return реальный индекс следующего за текущим элементом в массиве
*/
int get_next_pos(DMassive* mass, int pos);

/**
* Функция получения реального индекса предыдущего элемента в массиве
*
* @param mass указатель на массив типа структуры DMassive
* @param pos текущий индекс (пользовательский)
* @return реальный индекс предыдущего за текущим элементом в массиве
*/
int get_prev_pos(DMassive* mass, int pos);

/**
* Функция проверки пустоты массива
*
* @param mass указатель на массив типа структуры DMassive
* @return 1 - если массив пуст, 0 - если не пуст
*/
int is_empty(DMassive* mass);

/**
* Функция проверки заполненности массива
*
* @param mass указатель на массив типа структуры DMassive
* @return 1 - если массив заполнен, 0 - если не заполнен
*/
int is_full(DMassive* mass);

/**
* Функция сдвига элементов вправо на одну позицию начиная с заданной
*
* @param mass указатель на массив типа структуры DMassive
* @param pos стартовый индекс (пользовательский) для сдвига
*/
void right_shift(DMassive* mass, int pos);

/**
* Функция сдвига элементов влево на одну позицию начиная с заданной
*
* @param mass указатель на массив типа структуры DMassive
* @param pos стартовый индекс (пользовательский) для сдвига
*/
void left_shift(DMassive* mass, int pos);

int search_cmp(double a, double b);

/**
* Функция проверки упорядоченности массива по возрастанию
*
* @param mass указатель на массив типа структуры DMassive
* @return true - если массив отсортирован по возрастанию, false - в противном случае
*/
bool sorted_left_to_right(DMassive* mass);

/**
* Функция проверки упорядоченности массива по убыванию
*
* @param mass указатель на массив типа структуры DMassive
* @return true - если массив отсортирован по убыванию, false - в противном случае
*/
bool sorted_right_to_left(DMassive* mass);

/**
* Функция перестановки значений двух переменных
* @param first первое значение
* @param second второе значение
*/
void swap(double* first, double* second);

/* Функции работы с памятью */

/**
* Функция выделения памяти для массива
*
* @param mass указатель на массив типа структуры DMassive
* @param size размер массива
*/
void set_memory(DMassive* mass, int size);

/**
* Функция освобождения памяти массива
*
* @param mass указатель на массив типа структуры DMassive
*/
void clear_memory(DMassive* mass);

/**
* Функция изменения размера массива
*
* @param mass указатель на массив типа структуры DMassive
* @param new_size новый размер массива
*/
void resize(DMassive* mass, int new_size);

/* Заполнение массива */

/**
* Функция заполнения массива элементарными значениями (0, 1, 2, ...)
*
* @param mass указатель на массив типа структуры DMassive
*/
void fill_elementary(DMassive* mass);

/**
* Функция заполнения массива случайными значениями в заданном диапазоне
*
* @param mass указатель на массив типа структуры DMassive
* @param min_val минимальное значение
* @param max_val максимальное значение
*/
void fill_randomly(DMassive* mass, double min_val, double max_val);

/**
* Функция заполнения массива вручную с клавиатуры
*
* @param mass указатель на массив типа структуры DMassive
*/
void fill_manual_input(DMassive* mass);

/* Вставка */

/**
* Функция вставки элемента в начало массива
*
* @param mass указатель на массив типа структуры DMassive
* @param value значение для вставки
*/
void push_front(DMassive* mass, double value);

/**
* Функция вставки элемента в конец массива
*
* @param mass указатель на массив типа структуры DMassive
* @param value значение для вставки
*/
void push_back(DMassive* mass, double value);

void revers_mass(DMassive* mass);

/**
* Функция вставки элемента в заданную позицию массива
*
* @param mass указатель на массив типа структуры DMassive
* @param pos позиция для вставки
* @param value значение для вставки
* @return статус выполнения операции
*/
Status insert(DMassive* mass, int pos, double value);

/* Удаление */

/**
* Функция удаления элемента из начала массива
*
* @param mass указатель на массив типа структуры DMassive
* @return статус выполнения операции
*/
Status pop_front(DMassive* mass);

/**
* Функция удаления элемента из конца массива
*
* @param mass указатель на массив типа структуры DMassive
* @return статус выполнения операции
*/
Status pop_back(DMassive* mass);

/**
* Функция удаления элемента из заданной позиции массива
*
* @param mass указатель на массив типа структуры DMassive
* @param pos позиция для удаления
* @return статус выполнения операции
*/
Status erase(DMassive* mass, int pos);

void push_front_several(DMassive* mass, int count, const double* values);

void push_back_several(DMassive* mass, int count, const double* values);

Status insert_several(DMassive* mass, int pos, int count, const double* values);

Status pop_front_several(DMassive* mass, int count);

Status pop_back_several(DMassive* mass, int count);

Status erase_several(DMassive* mass, int pos, int count);

void shake_mass(DMassive* mass);

void write_mass_in_file(char* dir, char* file_name, DMassive* mass);

void read_mass_from_file(char* dir, char* file_name, DMassive* mass);


int binary_search_left(DMassive* mass, double target);

int binary_search_right(DMassive* mass, double target);

int count_occurrences(DMassive* mass, double target);

int* find_all_occurrences(DMassive* mass, double target, int* count);

/* Вывод на экран */

/**
* Функция вывода массива на экран
*
* @param mass указатель на массив типа структуры DMassive
* @param text текст перед выводом массива
* @param sep разделитель элементов
* @param end символ в конце вывода
*/
void print(DMassive* mass, const char* text, char sep, char end);

void write_mass_in_file(char* dir, char* file_name, DMassive* mass);

void bubble_sort(DMassive* mass);

void bubble_sort_pro(DMassive* mass);

void shell_sort_knuth(DMassive* mass);

void bogo_sort(DMassive* mass);

void quick_sort(DMassive* mass);