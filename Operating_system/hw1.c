#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>    // POSIX Threads: 병렬 처리를 위한 스레드 생성 및 제어 라이브러리
#include <sys/time.h>   // gettimeofday: 마이크로초(1/1,000,000초) 단위의 정밀한 시간 측정

/*
pthread_create()는 실행 함수에 단 하나의 void* 인자만 넘길 수 있습니다.
따라서 배열의 주소, 담당할 시작 위치, 끝 위치라는 3개의 정보를 하나로 묶어 전달하기 위해 정의했습니다.
*/
typedef struct {
    int *arr;    // 정렬할 데이터가 저장된 배열의 포인터
    int left;    // 해당 스레드가 담당할 부분 배열의 시작 인덱스
    int right;   // 해당 스레드가 담당할 부분 배열의 끝 인덱스
} ThreadArgs;

/*
    이미 정렬된 두 개의 인접한 구역(l~m, m+1~r)을 비교하며 하나의 정렬된 구간으로 합칩니다.
    이 함수는 각 스레드의 마지막 단계와 메인 스레드의 최종 합병 단계에서 호출됩니다.
 */

void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1; // 왼쪽 구간 요소 개수
    int n2 = r - m;     // 오른쪽 구간 요소 개수

    // 데이터를 임시 보관할 메모리를 힙(Heap) 영역에 할당합니다.
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // 원본 배열의 데이터를 임시 배열로 복사합니다.
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    // 두 임시 배열의 맨 앞부터 하나씩 비교하여 작은 순서대로 원본 배열에 채웁니다.
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    // 한쪽 배열의 비교가 먼저 끝난 경우, 남은 요소들을 마저 원본 배열에 채웁니다.
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    // 할당했던 임시 메모리를 해제하여 메모리 누수(Memory Leak)를 방지합니다.
    free(L);
    free(R);
}

void merge_sort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;    // 오버플로우를 방지하는 중간 지점 계산
        merge_sort(arr, l, m);      // 왼쪽 영역 분할
        merge_sort(arr, m + 1, r);  // 오른쪽 영역 분할
        merge(arr, l, m, r);        // 분할된 영역 병합
    }
}

void *thread_merge_sort(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    // 전달받은 구조체 정보를 바탕으로 담당 구역에 대해서만 머지 소트를 시작합니다.
    merge_sort(args->arr, args->left, args->right);
    return NULL;
}

int main(int argc, char *argv[]) {
    // 1. 실행 인자 예외 처리: 파일명과 스레드 수 N이 입력되었는지 확인합니다.
    if (argc < 3) {
        printf("Usage: %s <filename> <N>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int N = atoi(argv[2]); // 문자열 형식의 인자를 정수형으로 변환
    struct timeval start, end;

    // 2. 데이터 로딩: 파일에서 정수들을 읽어와 동적 배열 arr를 생성합니다.
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }

    int *arr = NULL;
    int num, count = 0;
    // fscanf로 정수를 하나씩 읽으며 realloc을 통해 배열 크기를 유동적으로 확장합니다.
    while (fscanf(fp, "%d", &num) != EOF) {
        arr = (int *)realloc(arr, (count + 1) * sizeof(int));
        arr[count++] = num;
    }
    fclose(fp);


//성능 측정 시작
    gettimeofday(&start, NULL);

    // 3. 멀티스레딩 준비: 스레드 ID 저장 배열과 인자 전달용 구조체 배열을 생성합니다.
    pthread_t *threads = (pthread_t *)malloc(N * sizeof(pthread_t));
    ThreadArgs *t_args = (ThreadArgs *)malloc(N * sizeof(ThreadArgs));
    int chunk_size = count / N; // 각 스레드가 담당할 데이터 조각의 크기

    //N개의 스레드를 생성하여 각각 정해진 범위의 subset을 정렬하게 합니다.
    for (int i = 0; i < N; i++) {
        t_args[i].arr = arr;
        t_args[i].left = i * chunk_size;
        // 데이터 개수가 N으로 나누어 떨어지지 않을 수 있으므로, 마지막 스레드는 끝까지 담당하게 합니다.
        t_args[i].right = (i == N - 1) ? (count - 1) : ((i + 1) * chunk_size - 1);
        
        // 실제 스레드를 생성하고 thread_merge_sort 함수를 실행시킵니다.
        pthread_create(&threads[i], NULL, thread_merge_sort, &t_args[i]);
    }

    /*
        [스레드 동기화: pthread_join]
        메인 스레드는 생성된 N개의 스레드가 모든 작업을 마칠 때까지 여기서 대기합니다.
        모든 스레드가 종료되어야 부분 정렬된 N개의 덩어리가 완성되기 때문입니다.
     */
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    /*
    [최종 병합 단계]
    각 스레드가 정렬해 놓은 N개의 부분 배열들을 메인 스레드가 하나로 합칩니다.
    첫 번째 조각을 기준으로 두 번째, 세 번째... N 번째 조각을 순차적으로 합병해 나갑니다.
     */
    for (int i = 1; i < N; i++) {
        int mid = i * chunk_size - 1;
        int end_idx = (i == N - 1) ? (count - 1) : ((i + 1) * chunk_size - 1);
        merge(arr, 0, mid, end_idx);
    }


    //성능 측정 종료 및 결과 산출 :정렬 완료 후의 시간을 기록하고, 시작 시간과의 차이를 마이크로초(us)로 변환합니다.
    gettimeofday(&end, NULL);
    long diff = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    // 4. 최종 결과 출력: 소요 시간 및 정렬된 배열 데이터
    printf("Elapsed Time: %ld microseconds\n", diff);
    printf("Sorted Array:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 5. 메모리 자원 반납: 프로그램 종료 전 사용했던 모든 메모리를 해제합니다.
    free(arr);
    free(threads);
    free(t_args);

    return 0;
}