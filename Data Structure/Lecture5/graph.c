#include <stdio.h>
#include <stdlib.h>

// 정점(노드) 최대 개수 지정 (필요시 수정)
#define MAX_V 100
// 무한대 값 정의 (경로가 없는 경우 등)
#define INF 100000000

// 간선(Edge) 구조체 정의: 도착지, 두 가중치, 다음 간선 포인터
typedef struct Edge {
    int to;            // 도착 정점 번호
    int w1;            // 첫 번째 가중치 (예: 시간)
    int w2;            // 두 번째 가중치 (예: 에너지)
    struct Edge* next; // 다음 간선(연결 리스트)
} Edge;

// 그래프 구조체 정의: 각 정점마다 간선 리스트를 가짐
typedef struct {
    Edge* head[MAX_V]; // 각 정점의 간선 연결 리스트 시작 포인터
    int nV;            // 정점의 개수
} Graph;

// 다익스트라 알고리즘에 사용되는 우선순위큐 대체 구조 (사용 안 함)
typedef struct {
    int vertex;
    double cost;
} Node;

// 그래프를 초기화하는 함수 (정점 수만큼 head 포인터를 NULL로 초기화)
void initGraph(Graph* g, int nV) {
    g->nV = nV;
    for (int i = 0; i < nV; i++)
        g->head[i] = NULL;
}

// 그래프에 간선을 추가하는 함수
void addEdge(Graph* g, int from, int to, int w1, int w2) {
    // 새 간선 구조체를 동적으로 생성
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->w1 = w1;
    e->w2 = w2;
    // 연결 리스트 맨 앞에 새 간선을 추가
    e->next = g->head[from];
    g->head[from] = e;
}

// 다익스트라 알고리즘: start에서 end까지 합성 가중치 최단경로 탐색
void dijkstra(Graph* g, int start, int end, double alpha, double beta, int* path, double* total_cost) {
    double dist[MAX_V];    // 각 정점까지의 최소 비용 저장
    int prev[MAX_V];       // 최단경로 경로 복원용 (이전 정점)
    int visited[MAX_V] = {0}; // 방문 여부 배열

    // 모든 정점의 거리/이전 정점 초기화
    for (int i = 0; i < g->nV; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0.0; // 시작점은 0

    // 정점 수만큼 반복(완전탐색, O(V^2))
    for (int cnt = 0; cnt < g->nV; cnt++) {
        int u = -1;
        double minDist = INF;
        // 방문하지 않은 정점 중 dist가 최소인 정점 u 선택
        for (int i = 0; i < g->nV; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break; // 더 이상 방문할 정점 없음(끝)
        visited[u] = 1;     // 방문 처리

        // u의 모든 인접 정점에 대해
        for (Edge* e = g->head[u]; e; e = e->next) {
            // 현재 alpha, beta로 가중치 선형 결합
            double cost = alpha * e->w1 + beta * e->w2;
            // 더 짧은 경로가 있으면 갱신
            if (dist[e->to] > dist[u] + cost) {
                dist[e->to] = dist[u] + cost;
                prev[e->to] = u;
            }
        }
    }
    // 최단 경로 복원 (end에서 start로 거꾸로 따라감)
    int idx = 0;
    int stack[MAX_V];
    int cur = end;
    while (cur != -1) {
        stack[idx++] = cur;
        cur = prev[cur];
    }
    // stack에 들어간 경로를 path로 정방향 저장
    for (int i = 0; i < idx; i++)
        path[i] = stack[idx - i - 1];
    path[idx] = -1; // 경로 끝 표시
    *total_cost = dist[end]; // 총 비용 반환
}


int main() {
    // input.txt에서 입력, output.txt에 출력
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    if (!fin || !fout) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int nV, start, end;
    // 첫 줄에서 정점 개수, 시작점, 도착점 입력
    fscanf(fin, "%d,%d,%d", &nV, &start, &end);
    // 1-indexed를 0-indexed로 변환
    start--; end--;

    Graph g;
    // 그래프 초기화
    initGraph(&g, nV);

    int from, to, w1, w2;
    char buf[100];
    // 한 줄씩 읽으면서 간선 정보 파싱
    while (fgets(buf, sizeof(buf), fin)) {
        // 입력 형식: (시작, 도착, 가중치1, 가중치2)
        if (sscanf(buf, " (%d,%d,%d,%d)", &from, &to, &w1, &w2) == 4) {
            // 1-index → 0-index 변환
            addEdge(&g, from - 1, to - 1, w1, w2);
        }
    }

    // alpha = 0.0 ~ 1.0까지 0.1 간격으로 반복
    for (int i = 0; i <= 10; i++) {
        double alpha = i / 10.0;
        double beta = 1.0 - alpha;
        int path[MAX_V + 1];    // 경로 저장 (최대 정점 수 + 1)
        double total_cost;      // 총 비용
        // 현재 alpha, beta에 대해 최적 경로 탐색
        dijkstra(&g, start, end, alpha, beta, path, &total_cost);

        // 결과 출력 (지정된 형식)
        fprintf(fout, "(%.1f, %.1f, %.0f)\n", alpha, beta, total_cost);
        fprintf(fout, "Path: ");
        // 경로 출력 (1-indexed로 변환)
        for (int j = 0; path[j] != -1; j++) {
            if (j > 0) fprintf(fout, "-");
            fprintf(fout, "%d", path[j] + 1);
        }
        fprintf(fout, "\n\n");
    }
    // 파일 닫기
    fclose(fin);
    fclose(fout);
    return 0;
}
