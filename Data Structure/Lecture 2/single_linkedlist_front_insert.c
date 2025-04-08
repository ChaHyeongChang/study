#include <stdio.h>
#include <stdlib.h> //malloc, free사용하기 위해

typedef struct node
{
    int value; // 값
    struct node* next; //다음 노드의 주소
}node;

node* head = NULL; // 첫 노드의 주소를 저장하는 포인터(8byte) //전역변수로 선언 : 연결리스트의 흐름을 알기위해 사용함, 얼마든지 지역변수로 사용가능

void insert_node_front(int data);
void display_node();
void free_all_nodes();


int main(){
    int choice;
    int data;

    while (1){
        system("cls");
        printf("\n\n*** 단일 연결 리스트(Singly Linked List) ***\n\n");
        printf(" 1. 노드 삽입(맨 앞)\n");
        printf("10. 단일 연결 리스트 출력\n"); 
        printf(" 0. 프로그램 종료\n");

        printf("\n메뉴 선택 : ");
        scanf("%d", &choice);
        while (getchar() != '\n'); //버퍼 지우기

        switch (choice)
        {
        case 1:
            printf("\n정수 입력 : ");
            scanf("%d", &data);
            while (getchar() != '\n');
            insert_node_front(data);
            break;
        case 10:
            display_node();
            break;
        case 0:
            free_all_nodes(); // 모든 노드 메모리 해제
            /*
            ? 올바른 메모리 해제 방법
        연결 리스트 전체를 해제하려면 curNode가 아니라,
        리스트 전체를 순회하면서 모든 노드를 free() 해줘야 해.

        그래서 free_all_nodes() 같은 함수를 만들어서 그걸 호출하는 방식으로 처리해야 해!
        //free(head), freee(curNode), free(new_Node) 못쓰는 이유 : 노드가 여러개 생성되었으니까 하나씩 순차적으로 전부 지워야 하므로!!
        */
            exit(0);
        }
        printf("\n\n\t\t");
        system("pause");
    }


    return 0;
}

//5 넣고 그 다음 7을 넣고 9번 데이터를 넣는 상황
void insert_node_front(int data){
    node* new_Node;
    new_Node = (node*)malloc(sizeof(node));
    new_Node->value = data;
    new_Node->next = NULL;

    if(head == NULL){
        head = new_Node;
        return;
    }
    new_Node->next = head; //현재 head는 5번 주소를 가지고 있으므로 new_Node가 저장중인 5번 노드의 주소를 새로생긴 7번노드의 next부분에 넣어라 :: 7번 노드는 5번 노드를 포인터 하게 됨 // 
    // 5입력 하고 7 입력한거면 저 코드상태에선 head에는 5의 주소가 들어가있고 new_Node에는 7의 주소가 들어가있구나!! 따라서 new_Node->next = head; 이렇게 작성해야함.

    head = new_Node; //head에는 이제 5번 노드의 주소값이 아니라 7번 노드의 주소값을 가져야함.
    //노드를 맨 앞에 삽입 하고나서 마지막에 head가 첫번째 노드를 가리키게끔 new_Node 즉, 새로 생성된 노드의 주소를 head에 넣어서 head가 가리키게끔 해주는 코드.

    //따라서 단일 연결 리스트에서 노드를 맨 앞에 삽입하는 과정의 시간 복잡도는 new_Node->next = head;와 head = new_Node; 이 코드 두개로 이루어지므로
    //단일 연결리스트가 노드를 맨 앞에 삽입하는 과정의 시간복잡도는 O(1) 이다.
}


void display_node(){ //첫번째 노드부터 마지막 노드까지 따라가야 하므로 시간 복잡도는 O(N)
    node* curNode; // 방문중인 노드의 주소를 저장하는 포인터(8byte)
    if(head == NULL){ //head가 NULL이면 어떠한 노드도 생성되지 않은 것이므로 retrun으로 끝냄
        printf("\n\n\t\t연결리스트가 구성되지 않아 출력할 값이 없습니다.\n");
        return;
    }

    curNode = head; // 첫 노드부터 방문 // 7번 노드의 주소를 가지고 있는건 head 이므로 curNode에 head를 먼저 넣는다.

    while (curNode->next != NULL){  //다음 노드가 있다면 //curNode가 가리키는 값이 NULL과 같지 않다면 계속 반복문 실행
        printf("%d=> ", curNode->value); //방문 노드의 값을 출력
        curNode = curNode->next; //다음 노드의 주소로 이동
    }
    printf("%d\n", curNode->value); //마지막 노드는 while문에 들어가지 않으므로 마지막 노드의 value를 따로 출력해줘야함!!
    /*
    printf("%d => ", curNode->value); //방문중인 노드의 값 출력 : 7
    curNode = curNode->next; //curNode를 두번째 노드의 값을 가리킬 수 있도록 curNode에 5번 노드의 주소를 저장한다.

    printf("%d => ", curNode->value);
    curNode = curNode->next;
        '
        '
        '
        '
    printf("%d => ", curNode->value);
    curNode = curNode->next;
    */
}

void free_all_nodes() {//동적할당 해제하는 함수, 순차적으로 해제해줘야 한다.(모든 노드를 제거하기 위해서) 
                    //동적할당한 노드들은 전부 힙 영역에서 사라지고, head는 스택(전역 변수니까 전역 영역)에 남아 있는 포인터 변수이다.

    node* cur = head;
    node* next;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    head = NULL; // 메모리 다 해제했으니 head도 초기화
}
