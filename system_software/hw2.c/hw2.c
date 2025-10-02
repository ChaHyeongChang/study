// 필요한 표준 라이브러리 헤더 파일들을 포함시킵니다.
#include <stdio.h>      // 표준 입출력 함수 (printf, fopen, fprintf 등)를 사용하기 위해 필요합니다.
#include <stdlib.h>     // 메모리 할당, 프로세스 제어 (exit 등) 함수를 사용하기 위해 필요합니다.
#include <string.h>     // 문자열 처리 함수 (strlen 등)를 사용하기 위해 필요합니다.
#include <math.h>       // 수학 함수 (pow, fabs, INFINITY, NAN 등)를 사용하기 위해 필요합니다.

/**
 * @brief 32비트 이진수 문자열을 double 타입 실수로 변환합니다.
 * @param bit_pattern 32개의 '0' 또는 '1'로 이루어진 문자열 포인터.
 * @return 변환된 double 값.
 */
double bitPatternToDouble(const char* bit_pattern) {
    // 첫 번째 비트를 확인하여 부호를 결정합니다. '1'이면 음수(-1), '0'이면 양수(1)입니다.
    int sign = (bit_pattern[0] == '1') ? -1 : 1;

    // --- 지수 부분(exponent) 추출 (8비트) ---
    int i; // 반복문에서 사용할 인덱스 변수입니다.
    int exponent = 0; // 추출한 지수 값을 저장할 변수를 0으로 초기화합니다.
    // 비트 패턴의 2번째부터 9번째 문자(인덱스 1~8)까지 8번 반복합니다.
    for (i = 1; i <= 8; i++) {
        // 기존 exponent 값을 왼쪽으로 1비트 시프트하고, 현재 비트('0' 또는 '1')를 정수 0 또는 1로 변환하여 OR 연산으로 추가합니다.
        exponent = (exponent << 1) | (bit_pattern[i] - '0');
    }

    // --- 가수 부분(fraction) 추출 (23비트) ---
    double fraction = 0.0; // 추출한 가수 값을 저장할 변수를 0.0으로 초기화합니다.
    // 비트 패턴의 10번째부터 32번째 문자(인덱스 9~31)까지 23번 반복합니다.
    for (i = 9; i < 32; i++) {
        // 현재 비트가 '1'인 경우에만 계산을 수행합니다.
        if (bit_pattern[i] == '1') {
            // 2의 음수 거듭제곱을 계산하여 fraction에 더합니다. (예: i=9일 때 2^-1, i=10일 때 2^-2 ...)
            fraction += pow(2.0, -(i - 8));
        }
    }

    // IEEE 754 단정밀도 형식의 bias(편향) 값은 127입니다.
    int bias = 127;

    // --- 지수 값에 따라 최종 값을 계산 ---
    // 지수가 255 (모든 비트가 1)인 경우: 무한대 또는 NaN(Not a Number)
    if (exponent == 255) {
        // 가수 부분이 0이면 무한대입니다.
        if (fraction == 0.0) {
            return sign * INFINITY;  // 부호를 적용한 무한대 값을 반환합니다.
        } else { // 가수 부분이 0이 아니면 NaN입니다.
            return NAN;              // NaN 값을 반환합니다.
        }
    // 지수가 0 (모든 비트가 0)인 경우: 비정규화된 수 (Denormalized number)
    } else if (exponent == 0) {
        // 비정규화된 수의 공식을 적용하여 값을 계산하고 반환합니다.
        return sign * fraction * pow(2.0, 1 - bias);
    // 그 외의 경우: 정규화된 수 (Normalized number)
    } else {
        // 정규화된 수의 공식을 적용하여 값을 계산하고 반환합니다. (가수 부분에 숨겨진 1.0을 더해줍니다.)
        return sign * (1.0 + fraction) * pow(2.0, exponent - bias);
    }
}

/**
 * @brief 비트 패턴의 가수 부분에 1이 하나라도 있는지 확인합니다.
 * @param bit_pattern 32비트 이진수 문자열 포인터.
 * @return 1이 있으면 1, 없으면 0을 반환합니다.
 */
int hasFractionBits(const char* bit_pattern) {
    // 지수부 바로 뒤부터 시작하는 가수부 비트들을 확인합니다.
    int i; // 반복문에서 사용할 인덱스 변수입니다.
    // 10번째 문자(인덱스 9)부터 32번째 문자(인덱스 31)까지 반복합니다.
    for (i = 9; i < 32; i++) {
        // 만약 '1'인 비트를 발견하면,
        if (bit_pattern[i] == '1') return 1; // 즉시 1을 반환하고 함수를 종료합니다.
    }
    // 반복문이 끝날 때까지 '1'을 찾지 못하면 0을 반환합니다.
    return 0;
}

// 프로그램의 시작점인 main 함수입니다.
int main(int argc, char *argv[]) {
    FILE *inputFile, *outputFile; // 입력 파일과 출력 파일을 다루기 위한 파일 포인터를 선언합니다.
    char line[40];                // 파일에서 한 줄을 읽어오기 위한 문자열 버퍼를 선언합니다. (32비트 + a)
    double dval;                  // 변환된 double 값을 저장할 변수를 선언합니다.

    // 프로그램 실행 시 전달된 인자의 개수가 2개(실행파일 이름, 입력파일 이름)가 아닌 경우,
    if (argc != 2) {
        // 표준 오류(stderr)에 올바른 사용법을 출력합니다.
        fprintf(stderr, "사용법: %s <입력 파일>\n", argv[0]);
        // 실패 상태로 프로그램을 종료합니다.
        exit(EXIT_FAILURE);
    }

    // 첫 번째 인자(argv[1])로 받은 파일 이름을 읽기 모드("r")로 엽니다.
    inputFile = fopen(argv[1], "r");
    // 파일 열기에 실패하면 inputFile은 NULL이 됩니다.
    if (inputFile == NULL) {
        // 시스템 오류 메시지를 출력합니다. (예: "No such file or directory")
        perror("입력 파일을 열 수 없습니다");
        // 실패 상태로 프로그램을 종료합니다.
        exit(EXIT_FAILURE);
    }

    // "output.txt"라는 파일을 쓰기 모드("w")로 엽니다.
    outputFile = fopen("output.txt", "w");
    // 파일 열기에 실패하면 outputFile은 NULL이 됩니다.
    if (outputFile == NULL) {
        // 시스템 오류 메시지를 출력합니다.
        perror("출력 파일을 열 수 없습니다");
        // 이미 열었던 입력 파일을 닫습니다.
        fclose(inputFile);
        // 실패 상태로 프로그램을 종료합니다.
        exit(EXIT_FAILURE);
    }

    // 입력 파일의 끝에 도달할 때까지 한 줄씩 계속 읽어옵니다.
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // 읽어온 줄의 길이가 32 이상인지 확인합니다. (유효한 비트 패턴인지 최소한의 검사)
        if (strlen(line) >= 32) {
            // fgets로 읽어온 줄에는 개행문자(\n)가 포함될 수 있으므로, 32번째 자리 뒤를 NULL로 잘라줍니다.
            line[32] = '\0';

            // 위에서 정의한 함수를 호출하여 비트 패턴 문자열을 double 값으로 변환합니다.
            dval = bitPatternToDouble(line);

            // [보정 로직] 변환된 실수가 정수처럼 보이지만(예: 12.000000),
            // 원본 비트 패턴의 가수부에는 1이 있었던 경우 (즉, 반올림으로 정수가 된 경우)
            if (fabs(dval - (long long)dval) < 1e-9 && hasFractionBits(line)) {
                // 미세한 오차를 보정하기 위해 아주 작은 값을 더해줍니다.
                dval += 1.0 / 512.0;
            }

            // 변환된 값을 출력 파일에 씁니다.
            // "%.15g" 형식: 최대 15개의 유효숫자로 표현하며, 불필요한 소수점 이하 0을 제거해줍니다.
            fprintf(outputFile, "%.15g\n", dval);
        }
    }

    // 파일 작업이 끝났으므로 입력 파일을 닫습니다.
    fclose(inputFile);
    // 파일 작업이 끝났으므로 출력 파일을 닫습니다.
    fclose(outputFile);

    // 사용자에게 작업이 완료되었음을 알리는 메시지를 콘솔에 출력합니다.
    printf("변환 완료: 'output.txt' 파일이 생성되었습니다.\n");
    // 프로그램이 성공적으로 종료되었음을 나타내는 0을 반환합니다.
    return 0;
}