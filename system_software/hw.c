#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// long long 값을 비교하도록 수정된 qsort 비교 함수
int compare_long_long(const void *a, const void *b) {
    long long num1 = *(long long*)a;
    long long num2 = *(long long*)b;
    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}

int main() {
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    // 변경됨: 배열 포인터를 long long* 타입으로 변경
    long long *numbers = NULL;
    long long count = 0;
    long long capacity = 0;
    // 변경됨: 숫자를 임시 저장할 변수를 long long 타입으로 변경
    long long num;

    long long unique_count = 0;
    long long over_5000_count = 0;

    // 변경됨: fscanf 형식 지정자를 "%d"에서 "%lld"로 변경
    while (fscanf(file, "%lld", &num) == 1) {
        if (count >= capacity) {
            capacity = (capacity == 0) ? 1024 : capacity * 2;
            // 변경됨: realloc 시 sizeof(long long)으로 크기 재할당
            long long *temp = realloc(numbers, capacity * sizeof(long long));
            if (temp == NULL) {
                printf("Error: 메모리 할당에 실패했습니다.\n");
                free(numbers);
                fclose(file);
                return 1;
            }
            numbers = temp;
        }
        numbers[count++] = num;
        if (num > 5000) {
            over_5000_count++;
        }
    }

    fclose(file);

    if (count > 0) {
        // 변경됨: qsort에 sizeof(long long)과 새로운 비교 함수 전달
        qsort(numbers, count, sizeof(long long), compare_long_long);
        
        unique_count = 1;
        for (long long i = 1; i < count; i++) {
            if (numbers[i] != numbers[i-1]) {
                unique_count++;
            }
        }
    }
    
    free(numbers);

    gettimeofday(&end_time, NULL);

    long long elapsed_microseconds = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + (end_time.tv_usec - start_time.tv_usec);

    printf("The number of unique values: %lld\n", unique_count);
    printf("The number of more than 5000 values: %lld\n", over_5000_count);
    printf("Execution time: %lld microseconds\n", elapsed_microseconds);

    return 0;
}