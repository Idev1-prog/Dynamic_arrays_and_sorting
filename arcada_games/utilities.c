#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int random_int(int n) {
    return rand() % n;
}

void clear_screen(void) {
    system("cls");
}

void pause_screen(void) {
    system("pause");
}

void set_malloc_char(char*** mass, int size, int count) { // Allocate memory for character array
    *mass = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        (*mass)[i] = (char*)malloc(count * sizeof(char));
    }
}

void setCursor(int line, int column) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getCursor(int* line, int* column) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *column = csbi.dwCursorPosition.X;
        *line = csbi.dwCursorPosition.Y;
    }
    else {
        *column = 0;
        *line = 0;
    }
}