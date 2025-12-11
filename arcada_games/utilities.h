#pragma once

#include <stdlib.h>
#include <time.h>


// Utility functions
int random_int(int n);
void clear_screen(void);
void pause_screen(void);
void set_malloc_char(char*** mass, int size, int count);
void setCursor(int line, int column);
void getCursor(int* line, int* column);