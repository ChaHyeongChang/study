/*
✅ 배열 기반 스택 (Array-based Stack)
✔ 장점
접근 속도 빠름 → 인덱스로 바로 접근 (O(1))

메모리 공간이 연속적 → CPU 캐시 친화적

구현이 간단함 (특히 고정 크기일 때)

❌ 단점
크기가 고정되어 있어야 함 (int arr[100])
➜ 초과하면 스택 오버플로우

동적 배열로 하면 재할당 비용 (realloc) 발생

삽입/삭제는 끝에서만 하므로 문제 없지만, 중간 삽입은 비효율적


///////////////////

✅ 연결 리스트 기반 스택 (Linked List-based Stack)
✔ 장점
크기 제한 없음 → 동적 메모리 할당이므로 스택 사이즈 유연

노드 단위로 삽입/삭제하므로 스택 오버플로우 걱정 없음 (메모리 한도 내에서)

push/pop 모두 O(1)로 처리 가능 (맨 앞에 삽입/삭제)

❌ 단점
포인터 저장 오버헤드 있음 (next 필드)

메모리 접근이 비연속적이라 캐시 성능 낮음

구현이 배열보다 조금 더 복잡
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int value;
    struct node *next;
}node;

void push(node** pHead, int data){ //head포인터 변수 자체를 바꾸기 위해 이중포인터 pHead사용
    node *newNode = NULL;
    //연결리스트 맨 앞 삽입
    newNode = (node*)malloc(sizeof(node)); //노드 생성
    newNode->value = data;
    newNode->next = NULL;

    //생성된 노드를 헤드로 변경
    if(*pHead == NULL){
        *pHead = newNode;
        printf("\n\n\t\t%d push!!!\n", newNode->value);
        return;
    }

    //맨 앞 삽입을 하기위해 새로운 노드의 next값을 헤드가 가리키는 노드에 연결
    newNode->next = *pHead;
    *pHead = newNode; //head를 newNode로 바꿔줌
    printf("\n\n\t\t%d push!!!\n", newNode->value);
}

void display(node *head){
    node *curNode = head;

    printf("\n\n\nstack data (Last in first out : LIFO) => ");

    if(head == NULL){
        return;
    }

    while (curNode->next){ //다음 노드가 있을 동안만 반복
        printf("%d -> ", curNode->value);
        curNode = curNode->next;
    }

    printf("%d\n", curNode->value); //마지막 노드는 while문에서 출력이 안되었으므로 따로 출력
}

void pop(node **pHead){
    node *delNode = NULL;
    
    //맨 앞 노드 제거!
    if(*pHead == NULL){
        printf("\n\n\t\tstack underflow\n");
        return;
    }

    delNode = *pHead; //삭제할 노드를 첫 노드로 설정
    *pHead = (*pHead)->next; //head를 다음 노드로 옮김
    //pHead[0] = pHead[0]->next;

    printf("\n\n\t\t%d pop!!!", delNode->value);
    free(delNode); //delNode가 가리키는 노드 제거 (맨 앞 노드 삭제)
}

void clear(node **pHead){
    node *delNode = *pHead;

    while(*pHead){
        *pHead = (*pHead)->next;
        free(delNode); //delNode가 가리키는 노드 제거 (맨 앞 노드 제거)
        //delNode = delNode->next 안됨!! 이미 delNode를 제거했는데 이동하려고 하니까
        delNode = *pHead; //delNode를 다시 head가 가리키는 값으로 이동
    }
}


int main()
{
	node* head = NULL;
	int choice, data;

	while (1)
	{
		system("cls");
		printf("\n\n\t\t *** integer stack (linked list) ***\n\n");
		printf("1. push    2. pop    3. print    4. clear    0. terminate\n");
		printf("chioce : ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("\n\ninterger push : ");
			scanf("%d", &data);
			push(&head, data); //맨 앞 삽입
			break;
		case 2:
			pop(&head);
			break;
		case 3:
			display(head);
			break;
		case 4:
			clear(&head);
			break;
		case 0:
			clear(&head);
			exit(0);
		}

		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}