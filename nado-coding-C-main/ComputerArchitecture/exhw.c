
#include <stdio.h>   // 파일 입출력, printf, fprintf
#include <stdlib.h>  // EXIT_FAILURE
#include <string.h>  // strlen, strcmp, strcspn

int main(void) {
    // 1) 메모리 배열 초기화 (크기 8)
    int mem[8] = {0};

    // 2) 파일 열기 (고정 파일 이름)
    FILE *fp = fopen("memory.txt", "r");
    if (fp == NULL) {
        printf("파일 인자를 잘못 입력했습니다.\n");
        return 1;
    }

    char line[10];  // 한 줄 버퍼 (최대 8비트 + 개행 + 널)
    int line_no = 0;

    // 3) 메모리 파일을 한 줄씩 읽어서 처리
    while (fgets(line, sizeof(line), fp)) {
        line_no++;
        // 개행 및 CR 제거
        line[strcspn(line, "\r\n")] = '\0';

        size_t len = strlen(line);
        // 명령어 길이 검증 (정확히 8비트)
        if (len != 8) {
            fprintf(stderr, "Line %d: invalid length (%zu != 8) — skipped\n",
                    line_no, len);
            continue;
        }

        // 비트 검증 및 모두 1인지 확인
        int all_one = 1;
        for (int i = 0; i < 8; i++) {
            if (line[i] != '0' && line[i] != '1') {
                fprintf(stderr, "Line %d: invalid char '%c' — skipped\n",
                        line_no, line[i]);
                all_one = -1;
                break;
            }
            if (line[i] != '1') {
                all_one = 0;
            }
        }
        if (all_one < 0) continue;
        if (all_one == 1) {
            // "11111111": 배열 전체를 0으로 초기화
            for (int i = 0; i < 8; i++) {
                mem[i] = 0;
            }
            continue;
        }

        // opcode, addr, value 파싱 (각각 2비트, 3비트, 3비트)
        int opcode = (line[0] - '0') * 2 + (line[1] - '0');
        int addr   = (line[2] - '0') * 4 + (line[3] - '0') * 2 + (line[4] - '0');
        int value  = (line[5] - '0') * 4 + (line[6] - '0') * 2 + (line[7] - '0');

        // 인덱스 범위 검증
        if (addr < 0 || addr >= 8) {
            fprintf(stderr, "Line %d: address out of range (%d)\n",
                    line_no, addr);
            continue;
        }
        if (opcode == 3 && (value < 0 || value >= 8)) {
            fprintf(stderr, "Line %d: swap index out of range (%d)\n",
                    line_no, value);
            continue;
        }

        // 명령 실행
        switch (opcode) {
            case 0: // store
                mem[addr] = value;
                break;
            case 1: // add
                mem[addr] += value;
                break;
            case 2: // sub
                mem[addr] -= value;
                break;
            case 3: { // swap
                int tmp = mem[addr];
                mem[addr] = mem[value];
                mem[value] = tmp;
            } break;
            default:
                fprintf(stderr, "Line %d: unknown opcode %d\n", line_no, opcode);
        }
    }

    fclose(fp);

    // 4) 최종 결과 ASCII 테이블 출력
    printf("+-------+");
    for (int i = 0; i < 8; i++) printf("---+");
    printf("\n| Index ");
    for (int i = 0; i < 8; i++) printf("| %d ", i);
    printf("|\n+-------+");
    for (int i = 0; i < 8; i++) printf("---+");
    printf("\n| Value ");
    for (int i = 0; i < 8; i++) printf("| %d ", mem[i]);
    printf("|\n+-------+");
    for (int i = 0; i < 8; i++) printf("---+");
    printf("\n");

    return 0;
}
