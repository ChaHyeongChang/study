#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int vertex; //정점
    int cost; //비용
    struct node* next; //다음 노드의 주소
}node;

typedef struct graph{
    node* head; //출발지 노드 배열의 주소를 저장
    int vertexCount; //정점의 개수
}graph;

void graphInit(graph* pGrp, int count); //그래프를 초기화 하는 함수
void addUnDirectedEdge(graph* pGrp, int src, int dst, int cost); //무방향 그래프의 간선 추가
void addDirectedEdge(graph* pGrp, int src, int dst, int cost); //방향 그래프에서 단일 방향 간선 추가
void printGraph(graph* pGrp);
void freeGraph(graph* pGrp);

int main(){
    graph grp;

    graphInit(&grp, 4);

    //도착지 정보 넘겨줌
    addUnDirectedEdge(&grp, 0, 1, 1);
    addUnDirectedEdge(&grp, 0, 2, 1);
    addUnDirectedEdge(&grp, 1, 2, 1);
    addUnDirectedEdge(&grp, 2, 3, 1);

    printGraph(&grp);
    freeGraph(&grp);      // 메모리 해제

    return 0;
}

void graphInit(graph* pGrp, int count){ //O(V) : 정점 수(V)만큼 초기화 작업 수행
    pGrp->vertexCount = count; //정점의 개수
    pGrp->head = malloc(sizeof(node) * count);

    for(int i = 0; i < count; i++){
        pGrp->head[i].vertex = i; //vertex를 0, 1, 2, 3지정
        pGrp->head[i].cost = 1; //초기값 cost를 1로 지정
        pGrp->head[i].next = NULL; //next의 초기값을 NULL로 지정정
    }
}

void addDirectedEdge(graph* pGrp, int src, int dst, int cost){ //O(1) : 삽입 위치가 리스트 앞쪽이므로 정렬할 필요 없고, 새 노드를 만들어 맨 앞에 연결만 하면 되므로 상수 시간
    //무방향 그래프 : 방향그래프가 2개
    node* newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->vertex = dst;
    newNode->cost = cost;
    newNode->next = NULL;

    if(pGrp->head[src].next == NULL){ //haed[src]정점과 연결된 노드가 하나도 없다면
        pGrp->head[src].next = newNode;
        return;
    }
    newNode->next = pGrp->head[src].next; //2번째 newNode의 next에 원래 newNode였던 노드의 주소를 넘겨줘서 2번째 만들어진 노드가 첫번째 노드를 가리키게
    pGrp->head[src].next = newNode; //0번 정점에서 2번째로 만든 노드를 가리키게
}

void addUnDirectedEdge(graph* pGrp, int src, int dst, int cost){ //O(1) + O(1) = O(1) : 방향 간선 두 번 추가하는건 2번 상수 시간 수행 -> 여전히 O(1)
    //무방향 그래프 : 방향그래프가 2개
    addDirectedEdge(pGrp, src, dst, cost);
    addDirectedEdge(pGrp, dst, src, cost);
}

void printGraph(graph* pGrp) { //O(V + E) : 모든 정점(V)을 순회하면서, 각 정점에 연결된 간선(E)을 모두 출력해야 하므로
    printf("그래프 인접 리스트 출력:\n");
    for (int i = 0; i < pGrp->vertexCount; i++) {
        printf("정점 %d → ", pGrp->head[i].vertex);
        
        node* curr = pGrp->head[i].next;
        while (curr != NULL) {
            printf("[정점 %d, 비용 %d] → ", curr->vertex, curr->cost);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

void freeGraph(graph* pGrp) { //O(V + E) : printGraph()처럼 정점 수만큼 루프 돌면서 간선 노드들(E개) free() 하므로 → O(V + E)
    for (int i = 0; i < pGrp->vertexCount; i++) {
        node* curr = pGrp->head[i].next;
        while (curr != NULL) {
            node* temp = curr;
            curr = curr->next;
            free(temp);  // 연결된 노드 하나씩 해제
        }
    }

    // head 배열도 해제
    free(pGrp->head);
}
