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
