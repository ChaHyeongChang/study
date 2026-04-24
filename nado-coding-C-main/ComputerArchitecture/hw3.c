#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("파일 인자를 잘못 입력했습니다.\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("파일 %s 을(를) 열 수 없습니다.\n", argv[1]);
        return 1;
    }

    int arr[8] = {0}; //디코더가 조작하는 정수형 배열
    char memory_line[10]; //메모리.txt 파일에서 한 줄씩 가져와서 임시로 읽을 버퍼 문자열

    while(fgets(memory_line, sizeof(memory_line), fp) != NULL){ //fgets는 자동으로 문자열 끝에 \0(널문자)를 추가하니까 memory_line[10]으로 한거임, 버퍼 마지막에 \n \0 두개가 남으니까 //scanf는 평소대로 (널문자 안남고) \n만 남음
        memory_line[strcspn(memory_line, "\n")] = '\0';


    }

    return 0;
}