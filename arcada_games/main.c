#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "menu.h"
#include "utilities.h"
// Program structure explanation, don't change the code, just read
// This is the main file - program entry point, it doesn't handle game logic (if something needs to be added, add it to main, implemented in menu and so on


// Program architecture explanation:
//    - main initializes the program, program logic is in other files, returns exit code 666, this is normal
//    - menu handles menu navigation (input and output), user interacts with menu functions
//    - games contains game implementations
//    - utilities contains helper functions, used for screen management, input validation, etc.


// Entry point
// Don't change!!!

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    int points = 0;

    start_main_menu(&points);

    clear_screen();
    printf("Your total points by game's results: %d\n", points);
    return 666;
}