#include <stdio.h> // 표준 입출력 함수 사용
#include <stdlib.h> // 동적 메모리, qsort 사용
#include <sys/time.h> // 실행 시간 측정을 위한 gettimeofday

// double 값을 오름차순으로 정렬하기 위한 비교 함수
int compare_double(const void *a, const void *b) {
    double x = *(const double*)a; // 첫 번째 요소 값
    double y = *(const double*)b; // 두 번째 요소 값
    if (x < y) return -1; // x가 작으면 앞으로
    if (x > y) return 1;  // x가 크면 뒤로
    return 0;             // 같으면 위치 유지
}

int main() { // 프로그램 시작 지점
    struct timeval start_time, end_time; // 시작·종료 시각 저장용
    gettimeofday(&start_time, NULL); // 시작 시각 캡처

    FILE *file = fopen("input.txt", "r"); // 입력 파일 열기
    if (file == NULL) {
        printf("Error: input.txt 파일을 열 수 없습니다.\n"); // 파일 열기 실패 시 메시지
        return 1;
    }

    long long capacity = 100000; // 초기 수용량(필요 시 2배 확장)
    double *numbers = (double*)malloc(sizeof(double) * capacity); // 수 저장 버퍼
    if (numbers == NULL) {
        printf("Error: 메모리 할당에 실패했습니다.\n"); // 메모리 확보 실패 처리
        fclose(file);
        return 1;
    }
    long long count = 0; // 읽은 수의 개수
    long long over_5000_count = 0; // 5000 초과 값의 개수

    // 공백을 구분자로 하여 실수 형태까지 포함해 읽기
    double num; // 현재 읽은 수
    while (fscanf(file, "%lf", &num) == 1) { // 더 이상 읽을 수 없을 때까지 반복
        if (count >= capacity) {
            long long new_capacity = capacity * 2; // 용량 두 배로 증가
            double *tmp = (double*)realloc(numbers, sizeof(double) * new_capacity); // 버퍼 확장
            if (tmp == NULL) {
                free(numbers); // 기존 버퍼 해제
                fclose(file);  // 파일 닫기
                return 1;      // 비정상 종료
            }
            numbers = tmp;        // 확장된 버퍼로 교체
            capacity = new_capacity; // 현재 용량 갱신
        }
        numbers[count++] = num;      // 값 저장
        if (num > 5000.0) {          // 5000 초과인지 검사
            over_5000_count++;       // 조건 만족 시 카운트 증가
        }
    }

    fclose(file); // 입력 파일 닫기

    long long unique_count = 0; // 서로 다른 값의 개수
    if (count > 0) { // 값이 하나 이상일 때만 계산
        qsort(numbers, count, sizeof(double), compare_double); // 오름차순 정렬
        
        unique_count = 1; // 첫 값은 항상 새로운 값으로 간주
        for (long long i = 1; i < count; i++) { // 인접한 값이 달라지는 횟수 세기
            if (numbers[i] != numbers[i-1]) {   // 값이 바뀌면 새로운 값 발견
                unique_count++;
            }
        }
    }
    
    free(numbers); // 동적 메모리 해제

    gettimeofday(&end_time, NULL); // 종료 시각 캡처

    long long elapsed_microseconds = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + (end_time.tv_usec - start_time.tv_usec); // 경과 시간(마이크로초)
    double elapsed_seconds = (double)elapsed_microseconds / 1000000.0; // 초 단위로 변환

    printf("The number of unique values: %lld\n", unique_count); // 서로 다른 값의 개수 출력
    printf("The number of more than 5000 values: %lld\n", over_5000_count); // 5000 초과 개수 출력
    printf("Execution time: %.6f sec\n", elapsed_seconds); // 실행 시간(초) 출력

    return 0; // 정상 종료 코드
}