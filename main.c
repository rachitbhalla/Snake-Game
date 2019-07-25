#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "declarations.c"
#include "display.c"
#include "food.c"
#include "poison.c"
#include "linkedList.c"
#include "snake.c"
#include "makeGame.c"
/*
    Document   : Snake Game
    Created on : July 19, 2019, 12:44:45 AM
    Author     : Rachit Bhalla
*/
int main(){

    hidecursor();
    srand(time(0));

    printf("Press 1 to Start a new game\nPress 2 to Resume the last game\nPress 3 to Exit\n");
    char key = getch();

    int innerLength = outerLength - 2*borderWidth;
    int innerWidth = outerWidth - 2*borderWidth;

    int score;

    Food food;
    Poison poison;
    Node* head = NULL;
    Node* tail = NULL;

    switch(key){
        case '1':
            startNewGame(&head, &tail,&food, &poison, &score, innerLength, innerWidth);
            break;
        case '2':
            resumeLastGame(&head, &tail,&food, &poison, &score, innerLength, innerWidth);
            break;
        case '3':
            exit(0);
            break;
        default:
            printf("INVALID COMMAND");
            exit(0);
            break;
    }
    return 0;
}
