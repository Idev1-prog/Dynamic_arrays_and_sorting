#pragma once
#include <stdio.h>
#include "dmassive.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define STEP_OF_CAPACITY 15

struct DMassive
{
	double* data;
	int size;
	int capacity;
	int front;
	int back;
};
enum Status { SUCCESS, WARNING, ERROR };


typedef struct DMassive DMassive;
typedef enum Status Status;

void bubble_sort(double* mass, int size, int front, int back);
void bubble_sort_pro(double* mass, int size, int front, int back);
void shell_sort_knuth(double* mass, int size, int front, int back);
void bogo_sort(double* mass, int size, int front, int back);
void print(DMassive* mass, const char* prefix, char sep, char end);
void set_memory(DMassive* mass, int size);
void fill_elementary(DMassive* mass);