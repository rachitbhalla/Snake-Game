typedef struct Food{
    int x;
    int y;
    char symbol;
}Food;
void initializeRandomFood(Food* foodPtr, int innerLength, int innerWidth){
    foodPtr->symbol = foodChar;
    foodPtr->x = rand()%innerLength + 1;
    foodPtr->y = rand()%innerWidth + 1;
    return;
}
void addFoodToDisplay(Food* foodPtr){
    gotoxy(foodPtr->x,foodPtr->y);
    printf("%c",foodPtr->symbol);
}
