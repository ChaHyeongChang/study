#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

typedef struct Queue
{
    int *arr; //동적 할당된 메모리의 주소를 저장하는 포인터(8바이트)
	int rear; //삽입위치(배열의 첨자)
	int front; //삭제위치(배열의 첨자)
	int count; //저장된 원소의 개수
	int capacity; //배열의 최대 용량(배열의 크기)
}queue;

void queueInit(queue *pQue, int size);
void enqueue(queue *pQue, int data);
int dequeue(queue *pQue);
void print(const queue *pQue);
void queueClear(queue *pQue);

int main()
{
	int choice, data;

	queue que; //구조체 변수

	queueInit(&que, 5); //구조체 변수 que와 크기는 5로 지정

	while (1)
	{
		system("cls");
		printf("\n\n\t\t****  배열을 이용한 원형 큐 ***\n\n");
		printf("1. enqueue    2. dequeue    3. print    4. clear   0. terminate\n");
		printf("choice : [ ]\b\b");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("\n\nInteger Input : ");
			scanf("%d", &data);
			while(getchar() != '\n');
			enqueue(&que, data);			
			break;
		case 2:
			data = dequeue(&que);

			if(data == -999999999){
				printf("\n\n\t\t%dQueue underflow\n");
			}
			else{
				printf("\n\n\t\t%d dequeue\n", data);//삭제 후 삭제된 값을 리턴.
			}
			break;
		case 3:
			print(&que);			
			break;
		case 4:
			queueClear(&que);
			break;
		case 0:
			free(que.arr); //구조체 변수 que가 가리키는 arr에서 생성된 동적메모리를 삭제시킴
			exit(0);
		}
		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}

void queueInit(queue *pQue, int size){
	pQue->arr = (int*)malloc(sizeof(int) * size);
	pQue->front = 0;
	pQue->rear = 0;
	pQue->count = 0;
	pQue->capacity = size;
}

void enqueue(queue *pQue, int data){
	if(pQue->count == pQue->capacity){ //더이상 저장할 수 없는 상태(저장 공간이 꽉 찬 상태)
		printf("\n\n\t\tQueue overflow\n");
		return;
	}

	pQue->arr[pQue->rear] = data; //데이터 저장 -> pQue의 arr의 rear번째 방에 값을 집어 넣겠다.
	pQue->rear++; //저장 위치를 변경 -> 데이터가 저장되면 rear를 한칸 옮겨야 하므로
	pQue->count++; //저장 개수 증가

	if(pQue->rear == pQue->capacity){ //범위를 벗어난 인덱스 : 배열의 최대 용량과 저장하려는 위치가 같아졌다면
		pQue->rear = 0; //rear을 다시 0으로 바꿔주는 작업 //front와 rear둘다 0으로 값은 같지만 count가 5이므로 이건 배열이 꽉 차있는 상태!
		//pQue->rear = ((pQue->rear) + 1) % pQue->capacity; // rear의 값을 0으로 만들어주는 작업
	} 

}

int dequeue(queue *pQue){
	int delValue;
	if(pQue->count == 0){ //underflow : 삭제할 데이터가 없는 상태
		return -999999999; //실제 삭제된 값이랑 겹치지 않게 리턴
	}

	delValue = pQue->arr[pQue->front]; // 삭제된 값(front가 증가되기전에 미리 저장해둠)
	pQue->front++; //삭제 위치 증가//front의 값을 증가시켜서 물리적으로 원래 front가 있던 자리의 data는 사라지지는 않지만 논리적으론 삭제된 것처럼 해줌 //front부터 rear전까지를 저장된 데이터로 인식하기 때문에
	pQue->count--; //저장 개수 감소

	if(pQue->front == pQue->capacity){ //삭제하려는 위치가 배열의 최대 용량과 같다면
		pQue->front = 0;
		//pQue->front = ((pQue->front) + 1) % pQue->capacity; //front의 값을 0으로 만들어주는 작업
	}

	return delValue; //삭제된 값을 리턴.
}

void print(const queue *pQue){

	printf("\n\nQueue display(FIFO) : ");

	if(pQue->count == 0){
		printf("\n\n\t\t큐가 비어있는 상태입니다.\n");
		return;
	}
	for(int i = pQue->front/*ex) 3 */; i < pQue->front + pQue->count/*ex) 3 + 3 */; i++){ //front가 3 4 0번 째를 출력하게끔
		printf("%d ", pQue->arr[i % pQue->capacity]); //3 4 5 //배열의 크기가 5이므로 5번째 방은 없음!! 따라서 배열의 전체 용량을 나눈 나머지를 인덱스에 넣고 출력 :: 3 4 0번째방 출력됨
	}
	puts("");
}

void queueClear(queue *pQue){
	//실질적으로 배열에는 값들이 남아있지만
	//물리적으로 삭제하는게 아니라 논리적으로 삭제된 상태로 만들어줌.
	pQue->count = 0; 
	pQue->front = 0;
	pQue->rear = 0;
}