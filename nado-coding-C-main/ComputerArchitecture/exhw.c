#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // 1. 명령행 인자 확인
    if (argc != 2) {
        printf("파일 인자가 잘못 입력되었습니다.\n");
        printf("사용법: %s <파일이름>\n", argv[0]);
        return 1;
    }

    // 2. 파일 열기
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("파일 %s 을(를) 열 수 없습니다.\n", argv[1]);
        return 1;
    }

    // 3. 배열 초기화
    int arr[8] = {0};          // 디코더가 조작할 배열
    char line[9];              // 8비트 문자열 + 널 문자('\0')

    // 4. 파일 한 줄씩 읽기
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';  // 줄바꿈 제거

        // 특수 명령어: 전체 초기화
        if (strcmp(line, "11111111") == 0) {
            memset(arr, 0, sizeof(int) * 8);
            continue;
        }

        // 5. 명령어 해석을 위한 비트 분리
        char cmd[3], addr_bits[4], val_bits[4];
        strncpy(cmd, line, 2); cmd[2] = '\0';
        strncpy(addr_bits, line + 2, 3); addr_bits[3] = '\0';
        strncpy(val_bits, line + 5, 3); val_bits[3] = '\0';

        // 6. 이진 문자열을 정수로 변환 (strtol 없이 직접 구현)
        int binary_to_int(const char *bits, int bit_count) {
            int result = 0;
            for (int i = 0; i < bit_count; i++) {
                result = result * 2 + (bits[i] - '0');
            }
            if (bit_count == 3 && bits[0] == '1') {
                result -= 8;  // 음수 보정 (2의 보수)
            }
            return result;
        }

        int addr = binary_to_int(addr_bits, 3);
        int val = binary_to_int(val_bits, 3);

        // 7. 명령어 실행
        if (strcmp(cmd, "00") == 0) {
            arr[addr] = val;
        } else if (strcmp(cmd, "01") == 0) {
            arr[addr] += val;
        } else if (strcmp(cmd, "10") == 0) {
            arr[addr] -= val;
        } else if (strcmp(cmd, "11") == 0) {
            int tmp = arr[addr];
            arr[addr] = arr[val];
            arr[val] = tmp;
        }
    }

    fclose(fp);

    // 8. 결과 출력
    printf("+--------+---+---+---+---+---+---+---+---+\n");
    printf("| Index  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
    printf("+--------+---+---+---+---+---+---+---+---+\n");
    printf("| Value  ");
    for (int i = 0; i < 8; i++) {
        printf("|%3d", arr[i]);
    }
    printf(" |\n");
    printf("+--------+---+---+---+---+---+---+---+---+\n");

    return 0;
}
