#include <stdio.h>      // 표준 입출력 함수
#include <string.h>     // 문자열 처리 함수
#include <stdlib.h>     // 메모리 함수 및 EXIT_FAILURE

int main(void) {
    /* 1) memory.txt 파일을 읽기 모드로 연다 */
    FILE *fp = fopen("memory.txt", "r");
    if (fp == NULL) {                                              // 파일 열기 실패 시
        fprintf(stderr, "memory.txt 파일 열기를 실패했습니다.\n");     // stderr에 오류 메시지 출력
        return 1;                                                  // 비정상 종료
    }

    /* 2) 배열과 버퍼, 줄 번호 변수 초기화 */
    int arr[8] = {0};      // 크기 8 정수 배열, 모두 0으로 초기화
    char memory_line[10];      // 8비트 + 개행(\n) + 널('\0') = 10바이트
    int line_nom = 0;        // 현재 처리 중인 파일의 줄 번호

    /* 3) 파일을 한 줄씩 읽으며 명령어를 처리 */
    while (fgets(memory_line, sizeof(memory_line), fp) != NULL) {
        line_nom++;                                                   // 줄 번호 증가
        /* 3-1) 개행 문자 제거 (Unix/Linux \n, Windows \r\n 모두 처리) */
        memory_line[strcspn(memory_line, "\n")] = '\0';

        /* 3-2) 길이 검사: 정확히 8문자여야 함 */
        int len = strlen(memory_line);                            // 문자열 길이 계산
        if (len != 8) {                                              // 길이가 8이 아니면
            fprintf(stderr,
                    "Line %d: 길이 오류 (%zu != 8) — 건너뜁니다\n",
                    line_nom, len);                                   // 오류 메시지
            continue;                                                // 다음 줄로
        }

        /* 3-3) 문자 검사: '0' 혹은 '1' 이외의 문자 있으면 스킵 */
        int valid = 1;                                               // 유효성 플래그
        for (int i = 0; i < 8; i++) {
            if (memory_line[i] != '0' && memory_line[i] != '1') {
                fprintf(stderr,
                        "Line %d: 잘못된 문자 '%c' — 건너뜁니다\n",
                        line_nom, memory_line[i]);                     // 오류 메시지
                valid = 0;                                           // 유효하지 않음 표시
                break;                                               // 검사 중단
            }
        }
        if (!valid) continue;                                        // 유효하지 않으면 다음 줄로

        /* 3-4) 특수 명령어: "11111111" 이면 배열 전체를 0으로 리셋 */
        if (strcmp(memory_line, "11111111") == 0) {
            memset(arr, 0, sizeof(arr));                             // 배열 0으로 초기화
            continue;                                                // 다음 줄로
        }

        /* 3-5) 비트 분리 및 10진수 변환 */
        int opcode = (memory_line[0] - '0') * 2                     // 상위 2비트 → opcode
                   + (memory_line[1] - '0');
        int addr   = (memory_line[2] - '0') * 4                     // 중간 3비트 → 주소
                   + (memory_line[3] - '0') * 2
                   + (memory_line[4] - '0');
        int raw_val = (memory_line[5] - '0') * 4                    // 하위 3비트 → raw value
                    + (memory_line[6] - '0') * 2
                    + (memory_line[7] - '0');

        /* 3-6) 산술 연산용 부호 처리: opcode가 swap(3)이 아닐 때만 two's-complement 보정 */
        int signed_val = raw_val;                                   // 기본값 할당
        if (opcode != 3 && memory_line[5] == '1') {
            signed_val -= 8;                                        // 최상위 비트가 1일 때 -8 보정
        }

        /* 3-7) 범위 검사: addr과 swap용 raw_val이 0~7 범위인지 확인 */
        if (addr < 0 || addr >= 8) {
            fprintf(stderr,
                    "Line %d: 주소 범위 오류 (%d) — 건너뜁니다\n",
                    line_nom, addr);
            continue;                                               // 다음 줄로
        }
        if (opcode == 3 && (raw_val < 0 || raw_val >= 8)) {
            fprintf(stderr,
                    "Line %d: swap 인덱스 범위 오류 (%d) — 건너뜁니다\n",
                    line_nom, raw_val);
            continue;                                               // 다음 줄로
        }

        /* 3-8) 명령어 실행: store/add/sub/swap */
        switch (opcode) {
        case 0:  // 00: store
            arr[addr] = signed_val;                                  // 저장
            break;
        case 1:  // 01: add
            arr[addr] += signed_val;                                 // 덧셈
            break;
        case 2:  // 10: sub
            arr[addr] -= signed_val;                                 // 뺄셈
            break;
        case 3:  // 11: swap
            {
                int tmp      = arr[addr];                            // 임시 변수에 저장
                arr[addr]    = arr[raw_val];                         // 값 교환
                arr[raw_val] = tmp;
            }
            break;
        } // switch end

    } // while end

    fclose(fp);  // 파일 닫기

    /* 4) 최종 결과를 ASCII 표 형태로 출력 */
    printf("+--------+---+---+---+---+---+---+---+---+\n");      
    printf("| Index  ");
    for (int i = 0; i < 8; i++) printf("| %d ", i);              // 인덱스 헤더
    printf("|\n+--------+---+---+---+---+---+---+---+---+\n");

    printf("| Value  ");
    for (int i = 0; i < 8; i++) printf("|%3d", arr[i]);         // 배열 값 출력
    printf(" |\n+--------+---+---+---+---+---+---+---+---+\n");

    return 0;  // 정상 종료
}
