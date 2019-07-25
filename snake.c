void initializeSnake(Node** headptr, Node** tailptr, int x, int y, int length, int offset, int innerLength, int innerWidth){
    if(offset == 0){
        insertFromEnd(headptr, tailptr, x, y%innerWidth+1, snakeHeadChar);
        for(int i=1;i<length-1;i++){
            insertFromEnd(headptr, tailptr, x, (y+i)%innerWidth+1, snakeBodyChar);
        }
        insertFromEnd(headptr, tailptr, x, (y+length-1)%innerWidth+1, snakeTailChar);
    }
    else{
        insertFromEnd(headptr, tailptr, x%innerLength+1, y, snakeHeadChar);
        for(int i=1;i<length-1;i++){
            insertFromEnd(headptr, tailptr, (x+i)%innerLength+1, y, snakeBodyChar);
        }
        insertFromEnd(headptr, tailptr, (x+length-1)%innerLength+1, y, snakeTailChar);
    }
    return;
}
void initializeRandomSnake(Node** headptr, Node** tailptr, int innerLength, int innerWidth){
    int x = rand()%innerLength + 1;
    int y = rand()%innerWidth + 1;
    int length = 5;
    int offset = rand()%2;
    initializeSnake(headptr, tailptr, x, y, length, offset, innerLength, innerWidth);
}
void growSnake(Node** headPtr, Node** tailPtr, int innerLength, int innerWidth){
    Node* lastNode = *tailPtr;
    Node* secondLastNode = lastNode->prev;
    int x = 2*(lastNode->x)-(secondLastNode->x);
    int y = 2*(lastNode->y)-(secondLastNode->y);
    lastNode->data = snakeBodyChar;
    insertFromEnd(headPtr, tailPtr, x, y, snakeTailChar);
    return;
}
void shortenSnake(Node** headPtr, Node** tailPtr){
    deleteFromEnd(headPtr, tailPtr);
    (*tailPtr)->data = snakeTailChar;
}
void moveSnake(Node** headptr, Node** tailptr, char offset, int innerLength, int innerWidth){
    Node* currNode = *tailptr;
    while(currNode->prev != NULL){
        currNode->x = (currNode->prev)->x;
        currNode->y = (currNode->prev)->y;
        currNode = currNode->prev;
    }
    switch(offset){
    case 72:
        currNode->y = (currNode->y)-1==0 ? (currNode->y)-1+innerWidth : (currNode->y)-1;
        break;
    case 75:
        currNode->x = (currNode->x)-1==0 ? (currNode->x)-1+innerLength : (currNode->x)-1;
        break;
    case 80:
        currNode->y = (currNode->y)+1==innerWidth+1 ? (currNode->y)+1-innerWidth : (currNode->y)+1;
        break;
    case 77:
        currNode->x = (currNode->x)+1==innerLength+1 ? (currNode->x)+1-innerLength : (currNode->x)+1;
        break;
    default:
        break;
    }
}
void addSnakeToDisplay(Node** headptr){
    Node* currNode = *headptr;
    while(currNode != NULL){
        gotoxy(currNode->x,currNode->y);
        printf("%c",currNode->data);
        currNode = currNode->next;
    }
    return;
}
void removeSnakeFromDisplay(Node** headptr){
    Node* currNode = *headptr;
    while(currNode != NULL){
        gotoxy(currNode->x,currNode->y);
        printf("%c",innerChar);
        currNode = currNode->next;
    }
    return;
}
int checkCrash(Node** headptr){
    Node* currNode = *headptr;
    while(currNode->next != NULL){
        currNode = currNode->next;
        if(currNode->x == (*headptr)->x && currNode->y == (*headptr)->y){
            currNode->data = crashChar;
            return 1;
        }
    }
    return 0;
}
int checkAteFood(Node** headPtr, Food* foodPtr){
    if(foodPtr->x == (*headPtr)->x && foodPtr->y == (*headPtr)->y){
        foodPtr->x = NULL;
        foodPtr->y = NULL;
        return 1;
    }
    return 0;
}
int checkAtePoison(Node** headPtr, Poison* poisonPtr){
    if(poisonPtr->x == (*headPtr)->x && poisonPtr->y == (*headPtr)->y){
        poisonPtr->x = NULL;
        poisonPtr->y = NULL;
        return 1;
    }
    return 0;
}
