void saveGame(Node** headPtr, Food* foodPtr, Poison* poisonPtr, int score){
    FILE *fp;
    fp = fopen("SnakeGame.txt","w");

    fputs("S\n", fp);
    //Save Snake
    Node* currNode = *headPtr;
    while(currNode != NULL){
        char snakeNode[50];
        sprintf(snakeNode, "%d %d %c\n", currNode->x, currNode->y, currNode->data);
        fputs(snakeNode, fp);
        currNode = currNode->next;
    }

    fputs("F\n", fp);
    //Save Food
    char food[50];
    sprintf(food, "%d %d %c\n", foodPtr->x, foodPtr->y, foodPtr->symbol);
    fputs(food, fp);

    fputs("P\n", fp);
    //Save Poison
    char poison[50];
    sprintf(poison, "%d %d %c\n", poisonPtr->x, poisonPtr->y, poisonPtr->symbol);
    fputs(poison, fp);

    fputs("#\n", fp);
    //Save Score
    char s[50];
    sprintf(s, "%d\n", score);
    fputs(s, fp);

    fclose(fp);
}
void getXY(char line[50],int* x, int* y){
    char* input = line;
    int xy[2], c, bytesread, length=0;
    while (sscanf(input, "%d%n", &c, &bytesread) > 0) {
        xy[length++] = c;
        input += bytesread;
    }
    *x = xy[0];
    *y = xy[1];
    return;
}
int getScore(char line[50]){
    char* input = line;
    int score, c, bytesread, length=0;
    while (sscanf(input, "%d%n", &c, &bytesread) > 0) {
        score = c;
        input += bytesread;
    }
    return score;
}
void restoreLastSnakeFoodPoison(Node** headPtr, Node** tailPtr, Food* foodPtr, Poison* poisonPtr, int* score){
    FILE *fp;
    fp = fopen("SnakeGame.txt","r");
    char line[50];
    char ch = 0;
    while(fgets(line,sizeof(line),fp) != NULL){
        if(line[0]=='S' || line[0]=='P' || line[0]=='F' || line[0]=='#'){
            ch = line[0];
            continue;
        }
        int x, y;
        switch(ch){
            case 'S':
                getXY(line,&x,&y);
                char data = line[strlen(line)-2];
                insertFromEnd(headPtr, tailPtr, x, y, data);
                break;
            case 'F':
                getXY(line,&x,&y);
                data = line[strlen(line)-2];
                foodPtr->x = x;
                foodPtr->y = y;
                foodPtr->symbol = data;
                break;
            case 'P':
                getXY(line,&x,&y);
                data = line[strlen(line)-2];
                poisonPtr->x = x;
                poisonPtr->y = y;
                poisonPtr->symbol = data;
                break;
            case '#':
                *score = getScore(line);
                break;
            default:
                break;
        }
    }
    fclose(fp);
}
int getDirectionKey(Node** headPtr){
    Node* firstNode = *headPtr;
    Node* secondNode = firstNode->next;
    int xDirection = firstNode->x - secondNode->x;
    int yDirection = firstNode->y - secondNode->y;
    if(xDirection==0){
        if(yDirection==1){
            return downKey;
        }else{
            return upKey;
        }
    }else if(xDirection==1){
        return rightKey;
    }else{
        return leftKey;
    }
}
void playGame(Node** headPtr, Node** tailPtr, Food* foodPtr, Poison* poisonPtr, char* key, int score, int innerLength, int innerWidth){
    int tag = 1;
    gotoxy(0,outerWidth);
    printf("Score: %d",score);
    while(tag){
        if(kbhit()){
            char d = getch();
            if(d==27){
                gotoxy(0,outerWidth);
                printf("GAME PAUSED\nPress 0 to Resume\nPress 1 to Exit");
                char b = getch();
                if(b=='0'){
                    gotoxy(0,outerWidth);
                    printf("\r                 \n\r                 \n\r                 ");
                    gotoxy(0,outerWidth);
                    printf("Score: %d",score);
                    continue;
                }else{
                    gotoxy(0,outerWidth);
                    printf("\r                 \n\r                 \n\r                 ");
                    gotoxy(0,outerWidth);
                    printf("Do you want to save the game?\nPress 0 for Yes\nPress 1 for No\n");
                    char c = getch();
                    if(c=='0'){
                        saveGame(headPtr, foodPtr, poisonPtr, score);
                        system("cls");
                        printf("GAME SAVED");
                        exit(0);
                    }else{
                        system("cls");
                        exit(0);
                    }
                }
            }
            else if(d==-32){
                char c = getch();
                if((*key==upKey || *key==downKey) && (c==leftKey || c==rightKey)){
                    *key = c;
                }else if((*key==leftKey || *key==rightKey) && (c==upKey || c==downKey)){
                    *key = c;
                }
            }else{
                continue;
            }
        }
        removeSnakeFromDisplay(headPtr);
        moveSnake(headPtr, tailPtr, *key, innerLength, innerWidth);
        if(checkCrash(headPtr)){
            gotoxy(0,outerWidth);
            printf("GAME OVER     ");
            gotoxy(0,outerWidth+1);
            printf("Score: %d",score);
            tag = 0;
        }
        if(checkAteFood(headPtr, foodPtr)){
            score+=5;
            gotoxy(0,outerWidth);
            printf("Score: %d",score);
            initializeRandomFood(foodPtr, innerLength, innerWidth);
            addFoodToDisplay(foodPtr);
            growSnake(headPtr, tailPtr, innerLength, innerWidth);
            int random = rand();
            if(random%7==0){
                initializeRandomPoison(poisonPtr, innerLength, innerWidth);
                addPoisonToDisplay(poisonPtr);
            }
        }
        if(checkAtePoison(headPtr, poisonPtr)){
            shortenSnake(headPtr, tailPtr);
        }
        addSnakeToDisplay(headPtr);
        Sleep(150);
    }
    gotoxy(0,outerWidth+1);
    exit(0);
}
void startNewGame(Node** headPtr, Node** tailPtr, Food* foodPtr, Poison* poisonPtr, int* scorePtr, int innerLength, int innerWidth){
    createDisplay();
    *scorePtr = 0;
    initializeRandomFood(foodPtr, innerLength, innerWidth);
    initializeRandomSnake(headPtr, tailPtr, innerLength, innerWidth);
    addFoodToDisplay(foodPtr);
    addSnakeToDisplay(headPtr);
    char directionKey = getDirectionKey(headPtr);
    playGame(headPtr, tailPtr, foodPtr, poisonPtr, &directionKey, *scorePtr, innerLength, innerWidth);
    return;
}
void resumeLastGame(Node** headPtr, Node** tailPtr, Food* foodPtr, Poison* poisonPtr, int* scorePtr, int innerLength, int innerWidth){
    createDisplay();
    restoreLastSnakeFoodPoison(headPtr, tailPtr, foodPtr, poisonPtr, scorePtr);
    addFoodToDisplay(foodPtr);
    addSnakeToDisplay(headPtr);
    char directionKey = getDirectionKey(headPtr);
    playGame(headPtr, tailPtr, foodPtr, poisonPtr, &directionKey, *scorePtr, innerLength, innerWidth);
    return;
}
