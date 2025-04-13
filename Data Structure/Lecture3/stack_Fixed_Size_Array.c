#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct stack{
    int arr[MAX_SIZE];
    int top;
}stack;

void creatStack(stack *p);
void push(stack *p, int element);
int pop(stack *p);
void displayStack(stack *p);
void clearStack(stack *p);

int main(){
    int choice, value;
    stack stk; //구조체 변수 선언(스택 생성)

    creatStack(&stk); //stk의 값이 변경되야 하니까 주소를 전달

    while (1)
	{
		system("cls");
		printf("\n\n\t\t*** Stack with Array ***\n\n");
		printf("\t\t1. push    2. pop    3. print    4. clear    0. exit\n");
		printf("\t\tchoice : [ ]\b\b");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:	
            printf("\n\n\t\t정수 입력 : ");
            scanf("%d", &value);
            while(getchar() != '\n');

            push(&stk, value);//stk구조체와 value를 받는 push함수 호출
			break;
		case 2:
            value = pop(&stk); //삭제된 값을 리턴
			if (value == -1){
				printf("\n\n\t\tstack underflow\n");
			}
			else{
				printf("\n\n\t\t %d pop\n", value);
			}
			break;
		case 3:
			displayStack(&stk);
			break;
		case 4:
			clearStack(&stk);
			break;
		case 0:
			exit(0);
		}
		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}

void creatStack(stack *p){
    p->top = -1; //top변수가 -1로 초기화
}

void push(stack *p, int element){
    if(p->top == MAX_SIZE-1){
        printf("\n\n\t\tstack overflow\n");
        return;
    }
    //(p->top)++; //p가 가리키는 값을++함 현재 -1이니까, 저장된 꼭대기의 값을 가리키게 하기 위해
    //p->arr[p->top] = element;
    p->arr[++(p->top)] = element;
}

void displayStack(stack *p){
	printf("\n\n\t\tstack display(LIFO) : ");
	for(int i = p->top; i >= 0; i--){
		printf("%d ", p->arr[i]);
	}
	puts("");
}


int pop(stack *p){
	if(p->top == -1){ //underflow상태
		return -1;
	}
    //물리적인 삭제가 아니라 논리적으로 삭제된 것 처럼 사용하는거임.
    //(p->top)--;
    return p->arr[(p->top)--]; //일단 return 한 다음에 top의 감소를 감소하겠다.
}

void clearStack(stack *p){
	p->top = -1;
}
