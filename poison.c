typedef struct Poison{
    int x;
    int y;
    char symbol;
}Poison;
void initializeRandomPoison(Poison* poisonPtr, int  innerLength, int innerWidth){
    poisonPtr->symbol = poisonChar;
    poisonPtr->x = rand()%innerLength + 1;
    poisonPtr->y = rand()%innerWidth + 1;
    return;
}
void addPoisonToDisplay(Poison* poisonPtr){
    gotoxy(poisonPtr->x,poisonPtr->y);
    printf("%c",poisonPtr->symbol);
}
