void createDisplay(){
    for(int i=0;i<outerLength;i++){
        for(int j=0;j<outerWidth;j++){
            if(i==0 || j==0 || i==outerLength-1 || j==outerWidth-1){
                gotoxy(i,j);
                printf("%c",outerChar);
            }
            else{
                gotoxy(i,j);
                printf("%c",innerChar);
            }
        }
    }
    return;
}
void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void hidecursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
