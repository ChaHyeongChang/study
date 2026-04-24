#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
    int vertexCount; //정점의 개수
    int** arr; //동적할당된 포인터 배열의 주소를 저장
}graph;

void graphInit(graph* pGrp, int count);
void unDirectedEdge(graph* pGrp, int src, int dst); //그래프 포인터, 출발지, 도착지
void edgeDisplay(graph* pGrp);
void memoryFree(graph* pGrp);
int main(){

    graph grp;

    graphInit(&grp, 4); //구조체 변수의 주소, 정점의 개수
    unDirectedEdge(&grp, 0, 1); 
    unDirectedEdge(&grp, 0, 2); 
    unDirectedEdge(&grp, 1, 2); 
    unDirectedEdge(&grp, 2, 3); 

    edgeDisplay(&grp);
    memoryFree(&grp);

    return 0;
}

void graphInit(graph* pGrp, int count){ //그래프 초기화 함수

    int i;
    pGrp->vertexCount = count;

    pGrp->arr = (int**)malloc(sizeof(int*) * count); //포인터 배열을 malloc하는거 (포인터 배열을 정점의 개수만큼 동적 할당)

    for(i = 0; i < count; i++){
        //pGrp->arr[i] = (int*)malloc(sizeof(int) * count);
        pGrp->arr[i] = (int*)calloc((count), sizeof(int)); //일차원배열을 동적할당 하는거 //배열을 처음부터 0으로 전부 넣기위해 calloc사용 //malloc쓰면 배열 처음에 쓰레기값 들어가니까
    }
}

void unDirectedEdge(graph* pGrp, int src, int dst){
    //무방향 그래프 : 양방향
    pGrp->arr[src][dst] = 1;
    pGrp->arr[dst][src] = 1;
}

void edgeDisplay(graph* pGrp){
    for(int i = 0; i < pGrp->vertexCount; i++){ //출발지
        for(int j = 0; j < pGrp->vertexCount; j++){ //도착지
            printf("%5d", pGrp->arr[i][j]);
        }
        puts("");//줄바꿈
    }
}

void memoryFree(graph* pGrp){ //1차원 배열부터 free하고 그 다음에 포인터 배열을 free해야 둘 다 free됨
    for(int i = 0; i < pGrp->vertexCount; i++){
        printf("arr[%d]가리키는 일차원 배열 제거\n", i);
        free(pGrp->arr[i]); //arr[i] i번째가 가리키는 메모리 free //각 행을 해제
    }

    printf("이차원배열을 만들기 위한 포인터 배열 제거\n");
    free(pGrp->arr); //source제거(필기에 나와있음 80.그래프란? p5)

}