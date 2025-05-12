#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    
    FILE *fp = fopen("memory.txt", "r"); //memory.txt파일을 읽기모드로 실행
    if (fp == NULL) {                                     
        fprintf(stderr, "memory.txt 파일 열기를 실패했습니다.\n"); //파일 열기를 실패하면 오류 메시지 출력
        return 1;
    }

    
    int arr[8] = {0}; // 디코더가 처리한 값을 저장하는 정수형 배열
    char memory_line[10]; // memory.txt에서 한 줄씩 읽어온 것을 저장할 버퍼, fgets에선 마지막에 널문자를 추가시키므로 8개의 비트와 개행문자, 널문자를 저장하기 위해 크기를 10으로 사용함
    int line_nom = 0; // 현재 처리 중인 파일의 줄 번호

    while (fgets(memory_line, sizeof(memory_line), fp) != NULL) { //memory.txt에서 한 줄을 읽어서 memory_line에 저장하고 성공 시 버퍼 끝에 자동으로 '\0'널문자를 붙임
        line_nom++;
        memory_line[strcspn(memory_line, "\n")] = '\0'; // memory.txt에서 한 줄씩 읽어올 때 개행문자('\n')를 지우기 위해 사용

        //길이를 검사함
        if (strlen(memory_line) != 8) {
            fprintf(stderr, "%d번째 줄에서 길이 오류가 발생하였고 다음줄로 넘어갑니다.\n", line_nom); //길이가 8이 아니면 오류 메시지 출력 후 
            continue;
        }

        //문자를 검사함
        int valid = 0; //valid의 값에 따라서 while문으로 돌아갈 수 있게 하기위해 사용
        for (int i = 0; i < 8; i++) {
            if (memory_line[i] != '0' && memory_line[i] != '1') { // '0'과 '1'이 아니면 잘못된 입력임으로 에러 출력
                fprintf(stderr, "%d번째 줄에서 잘못된 문자가 입력되어 오류가 발생하였고 다음줄로 넘어갑니다.\n", line_nom);
                valid = 1;
                break;
            }
        }
        if (valid == 1){ //오류가 발생했으므로 다음줄로 넘김
            continue;
        }

        //기계어의 모든 비트가 1이면 배열의 모든 값을 0으로 초기화 함
        if (strcmp(memory_line, "11111111") == 0) {
            for(int j = 0; j < 8; j++){
                arr[j] = 0;
            }
            continue;
        }

        //2개의 명령어 비트, 3개의 주소 비트, 3개의 값 비트로 나누고 각각 자리수와 부호를 계산해 10진수로 변환함
        int opcode = (memory_line[0] - '0') * 2 + (memory_line[1] - '0'); //10진수로 변환하기 위해서 '0' = 48을 빼고 각 자리수에 해당하는 값을 곱해줌

        int address_bit = (memory_line[2] - '0') * 4 + (memory_line[3] - '0') * 2 + (memory_line[4] - '0');

        int value_bit;
        if(memory_line[5] == '1'){
            value_bit = (memory_line[5] - '0') * 4 + (memory_line[6] - '0') * 2 + (memory_line[7] - '0') - 8; //음수인 경우
        }
        else if(memory_line[5] == '0'){
            value_bit = (memory_line[5] - '0') * 4 + (memory_line[6] - '0') * 2 + (memory_line[7] - '0'); //양수인 경우
        }

        int swap_bit = (memory_line[5] - '0') * 4 + (memory_line[6] - '0') * 2 + (memory_line[7] - '0'); //swap에서 사용할 인덱스의 값


        //각각의 명령어 00(store), 01(add), 10(sub), 11(swap)
        if (opcode == 0) { //store
            arr[address_bit] = value_bit;
        }
        else if (opcode == 1) { //add
            arr[address_bit] += value_bit;
        }
        else if (opcode == 2) { //sub
            arr[address_bit] -= value_bit;
        }
        else if (opcode == 3) { //swap
            int temp = arr[address_bit];
            arr[address_bit] = arr[swap_bit];
            arr[swap_bit] = temp;
        }

    }

    fclose(fp);

    //출력
    printf("+-------+---+---+---+---+---+---+---+---+\n");      
    printf("| Index ");
    for (int i = 0; i < 8; i++){
        printf("| %d ", i); 
    }
    printf("|\n+-------+---+---+---+---+---+---+---+---+\n");

    printf("| Value |");
    for (int i = 0; i < 8; i++) {
        printf("%2d |", arr[i]);
    }
    printf("\n+-------+---+---+---+---+---+---+---+---+\n");

    return 0;
}
