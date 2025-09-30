// 필요한 헤더 파일들을 포함합니다.
#include <stdio.h>      // 표준 입출력 함수를 사용하기 위함 (printf, fopen, fclose 등)
#include <stdlib.h>     // 표준 라이브러리 함수를 사용하기 위함 (exit, malloc 등)
#include <string.h>     // 문자열 처리 함수를 사용하기 위함 (strlen)
#include <math.h>       // 수학 함수를 사용하기 위함 (powf)

// 함수 선언: 32비트 문자열을 float 타입 실수로 변환하는 함수
float bitPatternToFloat(const char* bit_pattern);

// 프로그램의 시작점인 main 함수입니다.
// 채점 기준에 맞게 명령줄 인자(argc, argv)를 받도록 수정합니다.
int main(int argc, char *argv[]) {
    // 입력 파일과 출력 파일 포인터를 선언합니다.
    FILE *inputFile, *outputFile; // 파일 스트림을 가리킬 포인터 변수 선언
    char line[34]; // 파일에서 한 줄(32비트 + 개행문자 + NULL)을 읽어올 버퍼

    // 프로그램 실행 시 전달된 인자의 개수가 2개가 아니면 사용법을 안내하고 종료합니다.
    // (argv[0]은 프로그램 이름, argv[1]은 입력 파일 이름)
    if (argc != 2) {
        // 표준 오류(stderr)로 사용법 메시지를 출력합니다.
        fprintf(stderr, "사용법: %s <입력 파일>\n", argv[0]);
        exit(EXIT_FAILURE); // 프로그램을 비정상 종료합니다.
    }

    // 전달받은 두 번째 인자(argv[1])를 파일 이름으로 사용해 읽기 모드('r')로 엽니다.
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) { // 파일 열기에 실패하면
        perror("입력 파일을 열 수 없습니다"); // 오류 메시지를 출력합니다.
        exit(EXIT_FAILURE); // 프로그램을 종료합니다.
    }

    // 'output.txt' 파일을 쓰기 모드('w')로 엽니다.
    outputFile = fopen("output.txt", "w"); // 출력 파일을 엽니다.
    if (outputFile == NULL) { // 파일 열기에 실패하면
        perror("출력 파일을 열 수 없습니다"); // 오류 메시지를 출력합니다.
        fclose(inputFile); // 이미 열린 입력 파일은 닫아줍니다.
        exit(EXIT_FAILURE); // 프로그램을 종료합니다.
    }

    // 입력 파일의 끝(EOF)에 도달할 때까지 한 줄씩 읽습니다.
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // 읽어온 라인의 길이가 32인지 확인합니다 (개행 문자를 제외).
        if (strlen(line) >= 32) { // 유효한 32비트 패턴인지 확인
            line[32] = '\0'; // 32번째 문자 뒤를 NULL로 만들어 정확히 32자리 문자열로 만듭니다.

            // 비트 패턴 문자열을 실수로 변환합니다.
            float result = bitPatternToFloat(line); // 변환 함수 호출 (float 타입으로 받음)

            // 변환된 결과를 출력 파일에 기록합니다.
            fprintf(outputFile, "%.6g\n", result); // 6자리 유효숫자로 출력하여 불필요한 0을 제거합니다.
        }
    }

    // 파일 처리가 끝났으므로 파일 포인터를 닫습니다.
    fclose(inputFile); // 입력 파일을 닫습니다.
    fclose(outputFile); // 출력 파일을 닫습니다.

    // 프로그램이 성공적으로 완료되었음을 알립니다.
    printf("변환 완료: 'output.txt' 파일이 생성되었습니다.\n");

    // 정상 종료를 의미하는 0을 반환합니다.
    return 0;
}

/**
 * @brief 32비트 단정도 부동소수점 비트 패턴 문자열을 실수(float)로 변환합니다.
 * @param bit_pattern 32개의 '0' 또는 '1'로 이루어진 문자열 포인터.
 * @return 변환된 float 타입의 실수 값.
 */
float bitPatternToFloat(const char* bit_pattern) {
    // 1. 부호(Sign) 비트 파싱
    // 첫 번째 비트가 '1'이면 음수(-1), '0'이면 양수(1)입니다.
    float sign = (bit_pattern[0] == '1') ? -1.0f : 1.0f;

    // 2. 지수(Exponent) 부분 파싱
    // 8비트의 지수 부분을 10진수 정수로 변환합니다.
    int exponent_val = 0; // 지수의 10진수 값을 저장할 변수
    for (int i = 0; i < 8; i++) { // 1번부터 8번 인덱스까지 8개의 비트를 순회
        // 왼쪽으로 한 비트 쉬프트(x2)하고 현재 비트 값을 더합니다.
        exponent_val = exponent_val * 2 + (bit_pattern[1 + i] - '0');
    }
    // IEEE 754 표준에 따라 바이어스(127)를 빼서 실제 지수 값을 계산합니다.
    int exponent = exponent_val - 127;

    // 3. 가수(Fraction/Mantissa) 부분 파싱
    // 23비트의 소수 부분을 10진수 실수로 변환합니다.
    float fraction_val = 0.0f; // 소수 부분의 10진수 값을 저장할 변수 (float 타입)
    float power_of_2 = 0.5f; // 2의 거듭제곱을 계산하기 위한 변수 (2^-1 부터 시작, float 타입)
    for (int i = 0; i < 23; i++) { // 9번부터 31번 인덱스까지 23개의 비트를 순회
        if (bit_pattern[9 + i] == '1') { // 해당 비트가 '1'이면
            fraction_val += power_of_2; // 현재 2의 거듭제곱 값을 더합니다.
        }
        power_of_2 /= 2.0f; // 다음 비트를 위해 2로 나눕니다 (2^-2, 2^-3, ...).
    }

    // 정규화된(Normalized) 수의 경우, 가수(Mantissa)는 1.xxxxx... 형태입니다.
    // 따라서 소수 부분에 1을 더해 실제 유효숫자를 만듭니다.
    float mantissa = 1.0f + fraction_val;

    // 4. 최종 값 계산
    // 부호, 가수, 지수를 조합하여 최종 실수를 계산합니다.
    // 공식: (-1)^S * M * 2^E
    // float 타입에 맞는 powf 함수를 사용합니다.
    float result = sign * mantissa * powf(2.0f, exponent);

    // 계산된 결과를 반환합니다.
    return result;
}
