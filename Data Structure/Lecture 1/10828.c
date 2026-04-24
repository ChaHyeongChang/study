#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node* next;
}Node;

Node * head = NULL;

void push(int n, Node*sp);
void pop(Node *sp);
void size(Node *sp);
int empty(Node *sp);
void top(Node *sp);
void clean(Node *sp);


int main(void){
    int n;
    scanf("%d", &n);


    Node sp;
    sp.next = NULL;

    for(int i = 0; i < n; i++){
        char command[10];
        scanf("%s", command);

        if(strcmp(command, "push") == 0){
            int num;
            scanf("%d", &num);
            push(num, &sp);
        }
        else if(strcmp(command, "pop") == 0){
            pop(&sp);
        }
        else if(strcmp(command, "size") == 0){
            size(&sp);
        }
        else if(strcmp(command, "empty") == 0){
            printf("%d\n", empty(&sp));
        }
        else if(strcmp(command, "top") == 0){
            top(&sp);
        }
    }

    while(!empty(&sp)){
        clean(&sp);
    }
    
    return 0;
}

void push(int n, Node*sp){
    Node * newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = n;
    if(head == NULL){
        head = newNode;
    }

    newNode->next = head;
    head = newNode;
}

void pop(Node *sp){
    Node * delNode;
    int delvalue;

    if(head == NULL){
        printf("-1\n");
        return;
    }

    delNode = head;
    head = head->next;
    printf("%d\n", delNode->data);
    free(delNode);
}

void size(Node *sp){
    Node * curNode;
    int count;

    if(head == NULL){
        return;
    }

    curNode = head;

    while(curNode != NULL){
        curNode = curNode->next;
        count++;
    }

    printf("%d\n", count);
    
}

int empty(Node *sp){
    if(head == NULL){
        return 1;
    }
    
    return 0;
}


void top(Node *sp){
    if(head == NULL){
        printf("-1\n");
        return;
    }

    printf("%d\n", head->data);  

    return;
}

void clean(Node *sp){
    Node * delNode;

    
    if(head == NULL){
        return;
    }
    
    delNode = head;
    while(head != NULL){
        head = head->next;
        free(delNode);
        delNode = head;
    }
}