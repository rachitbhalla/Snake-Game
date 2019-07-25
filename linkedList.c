typedef struct Node{
    int x;
    int y;
    char data;
    struct Node* prev;
    struct Node* next;
}Node;
void insertFromEnd(Node** headptr, Node** tailptr, int x, int y, char newData){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x;
    newNode->y = y;
    newNode->data = newData;
    newNode->prev = *tailptr;
    newNode->next = NULL;
    if(*headptr == NULL){
        *headptr = newNode;
    }
    else{
        (*tailptr)->next = newNode;
    }
    *tailptr = newNode;
    return;
}
void deleteFromEnd(Node** headptr, Node** tailptr){
    if(*tailptr == NULL){
        printf("LinkedList is empty");
        return;
    }
    Node* lastNode = *tailptr;
    if(lastNode->prev != NULL){
        (lastNode->prev)->next = NULL;
    }else{
        *headptr = NULL;
    }
    *tailptr = lastNode->prev;
    free(lastNode);
}
