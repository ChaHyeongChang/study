/*
✅ 시간복잡도 비교
연산	            배열 기반 원형 큐       연결 리스트 기반 큐
삽입 (enqueue)	           O(1)                 	O(1)
삭제 (dequeue)	           O(1)                 	O(1)
접근 (peek/front)	       O(1)	                    O(1)
공간 확장	       O(n) (재할당 필요 시)	O(1) (노드 동적 할당)
*/


//연결리스트를 이용한 원형 큐(FIFO) : 맨뒤 삽입을 이용한다. 시간 복잡도는 O(N) -> O(1)로 줄이기 위해 tail이라는 변수 사용

#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

typedef struct node
{
    int value;
    struct node* next;
}node;

void enqueue(node** pHead, node** pTail, int data); //pHead는 head의 주소를 저장함. //head라는 포인터를 받는 포인터이므로 더블 포인터로 사용해야함!
//pTail는 tail의 주소를 저장함. //tail라는 포인터를 받는 포인터이므로 더블 포인터로 사용해야함!
int dequeue(node** pHead, node** pTail);
void displayQueue(node* head, node* tail); //head와 tail의 값을 변경시키지 않을거라 call by value 이용.
void clearQueue(node** pHead, node** pTail);

int main()
{
	int choice, data;
    node *head = NULL; //첫 노드의 주소를 저장
    node *tail = NULL; //마지막 노드의 주소를 저장장
	while (1)
	{
		system("cls");
		printf("\n\n\t\t****  연결 리스트를 이용한 원형 큐 ***\n\n");
		printf("1. enqueue    2. dequeue    3. print    4. clear   0. terminate\n");
		printf("choice : [ ]\b\b");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
            printf("\n\n삽입 할 정수 입력 : ");
            scanf("%d", &data);
            while(getchar() != '\n');

            enqueue(&head, &tail, data);
			break;
		case 2:
            data = dequeue(&head, &tail); //삭제된 노드의 값을 리턴
            if(data == -999999999){//더이상 삭제할 노드가 없는 상태
                printf("\n\n\t\tqueue underflow\n");
            }
            else{
                printf("\n\n\t\t%d dequeue\n", data);
            }
            break;
		case 3:
            displayQueue(head, tail);//head와 tail의 값을 직접 바꾸는게 아니라 출력만 하는 거니까 call by value 사용!
			break;
		case 4:
            clearQueue(&head, &tail); //head와 tail의 값을 변경해야하므로 call by address 사용!
			break;
		case 0:
            clearQueue(&head, &tail); //프로그램 종료시킬때도 내부 노드 전부 지우고 종료
			exit(0);
		}
		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}

void enqueue(node** pHead, node** pTail, int data){ //pHead는 head의 주소를 저장함. //head라는 포인터를 받는 포인터이므로 더블 포인터로 사용해야함!
    //pTail은 tail의 주소를 저장함. //tail라는 포인터를 받는 포인터이므로 더블 포인터로 사용해야함!
    node *newNode;
    newNode = (node*)malloc(sizeof(node)); //새로운 노드 생성(value와 next저장가능)
    newNode->value = data;
    newNode->next = NULL;

    if(*pHead == NULL){ //head == *pHead //head는 main의 지역변수이므로 사용이 안되지만 *pHead는 head의 주소를 가리키고 역참조 하므로 *pHead를 이용!
        *pHead = newNode;
        *pTail = newNode;
        return;
    }

    //O(1)의 시간 복잡도를 가짐 : 맨 뒤를 삽입하는데
    (*pTail)->next = newNode; //tail이 가리키는 다음 노드를 newNode로 만들어줌 // tail == *pTail
    *pTail = newNode; //tail을 newNode로 할당
    
}

int dequeue(node** pHead, node** pTail){
    node* delNode;
    int delValue;
    if(*pHead == NULL){//underflow : 삭제할 노드가 없는 경우
        return -999999999;
    }
    
    //맨 앞 삭제
    delNode = *pHead; //첫 노드를 삭제할 노드로 지정
    *pHead = (*pHead)->next; //헤드를 다음 노드값으로 이동시킴
    delValue = delNode->value; //delNode를 삭제하기 전 delNode가 가리키는 value를 저장장
    free(delNode); //delNode가 가리키는 노드 삭제(첫번재 노드)

    if(*pHead == NULL){ //모든 노드를 dequeue하면 head는 NULL이 되고 아무 노드도 없으므로 tail도 NULL을 가져야함
        *pTail = NULL;
    }
    
    return delValue; //삭제된 값 리턴
}

void displayQueue(node* head, node* tail){ //head와 tail의 값을 변경시키지 않을거라 call by value 이용.

    node* curNode; //방문중인 노드의 주소를 저장

    printf("Queue Display(FIFO) : ");
    if(head == NULL){//출력할 데이터 없음
        printf("\n\n\t\t큐가 비어 있습니다.\n");
        return;
    }

    curNode = head;
    while(curNode != tail){ //방문노드가 마지막 노드가 아닐때까지지
        printf("%d => ", curNode->value);
        curNode = curNode ->next;//방문 노드의 다음으로 방문 노드를 이동
    }
    printf("%d\n", curNode->value);//while문에 포함되지 않은 마지막 노드의 값 출력
}

void clearQueue(node** pHead, node** pTail){
    node* delNode;

    if(*pHead == NULL){ //head가 NULL인 경우
        return;
    }

    //전체노드 제거 => 첫 노드 제거(반복)
    //전부 삭제됨 : 마지막 노드도 *pHead가 NULL이 나올때 까지니까 delNode가 마지막 노드까지는 가리킴
    while(*pHead != NULL){ 
        delNode = *pHead;
        *pHead = (*pHead)->next;
        free(delNode); //delNode가 삭제되는것이 아니라 delNode가 가리키는 노드가 제거되는거
    }

    *pTail = NULL;
}