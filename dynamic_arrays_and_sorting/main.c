#include <stdio.h>;
#include "menu.h"
#include "dmassive.h"
#include <locale.h>

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	main_menu();
	return 7;
}











//double mass[8] = { 0, 5, 0, 14, 1, 3, 0, 0 };
//int front = 1;
//int last = 5;
//int size = 8;
////bubble_sort(mass, size, front, last);
////printf("\n");
////bubble_sort_pro(mass, size, front, last);
////printf("\n");
//shell_sort_knuth(mass, size, front, last);
//printf("\n");
//bogo_sort(mass, size, front, last);
//printf("\n");