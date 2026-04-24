#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

typedef struct stack
{
	//int arr[5];
	int* arr;		//동적 메모리의 주소를 저장(가변크기의 스택을 설정하기 위해)
	int capacity;	//배열의 최대 용량
	int top;		//꼭대기(저장된 원소의 꼭대기 첨자)
}stack;

void createStack(stack* pStk, int size);
void push(stack* pStk, int value);
int pop(stack* pStk);
void displayStack(stack* pStk);
void clearStack(stack* pStk);
int isEmpty(stack* pStk);
int isFull(stack* pStk);

int main()
{
	stack stk; //스택 구조체 변수 선언(16바이트)
	int choice, size, value;

	printf("\nEnter a stack size : ");
	scanf("%d", &size);
	while (getchar() != '\n');

	createStack(&stk, size); //스택 생성 함수 호출

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
			printf("\n\n\t\tEnter an integer : ");
			scanf("%d", &value);
			push(&stk, value);
			break;
		case 2:
			value = pop(&stk); //삭제된 값 리턴
			if (value != -1)
				printf("\n\n\t\t%d pop!!!\n", value);
			break;
		case 3:
			displayStack(&stk);
			break;
		case 4:
			clearStack(&stk);
			break;
		case 0:
			free(stk.arr); //동적 메모리 제거
			exit(0);
		}

		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}

void createStack(stack* pStk, int size)
{
	pStk->arr = (int*)malloc(sizeof(int) * size);
	pStk->capacity = size;
	pStk->top = -1;
}

void push(stack* pStk, int value)
{
	if (isFull(pStk)) //더이상 push 할 수 없는 상태
	{
		printf("\n\n\t\tstack overflow\n");
		return;
	}

	//전치 연산 : 일단 top의 값을 증가 후, value를 저장
	pStk->arr[++(pStk->top)] = value;
}

int pop(stack* pStk)
{
	if (isEmpty(pStk)) //더이상 pop 할 수 없는 상태
	{
		printf("\n\n\t\tstack underflow\n");
		return -1; 
	}

	//후치 연산 : 일단 리턴 후, top의 값을 감소
	return pStk->arr[(pStk->top)--]; //삭제된 값 리턴
}

void displayStack(stack* pStk)
{
	int i;
	system("cls");
	printf("stack display(Last In First Out : LIFO) : ");

	if (isEmpty(pStk))
	{
		printf("\n\n\t\tstack is empty\n");
		return;
	}

	for (i = pStk->top; i >= 0; i--) //LIFO구조로 출력하기 위해서
		printf("%d ", pStk->arr[i]);
	puts("");
}

void clearStack(stack* pStk)
{
	pStk->top = -1; //논리적인 삭제(실제 삭제X -> 삭제된 것처럼 구현)
}

int isEmpty(stack* pStk)
{
	//스택이 비어 있다면?? 1리턴
	//스택이 비어 있지 않다면?? 0리턴
	if (pStk->top == -1)
		return 1;
	else
		return 0;
}

int isFull(stack* pStk)
{
	//스택이 가득 찼다면?? 1리턴
	//스택이 가득 차지 않았다면?? 0리턴
	if (pStk->top == pStk->capacity - 1)
		return 1;
	else
		return 0;
}