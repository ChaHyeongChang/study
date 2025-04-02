#include <stdio.h>

int main(){

    FILE* fp; //FILE은 내부적으로 정의되어있는 구조체, 포인터를 선언 8byte

    //모드에는
    //r모드 : 읽기 모드
    //w모드 : 기록 모드 : 파일이 존재하지 않는 경우 파일을 생성해서 기록함.
    //파일이 존재하는 경우 :: w모드는 파일 오픈 시 파일에 있던 데이터(내용)은 모두 삭제 후 기록 시작.
    //a모드 : 추가 모드 : 기존에 있던 내용에 이어서 기록을 시작함(w모드와의 차이점점)
    fp = fopen("out.txt", "w"); //fopen("파일명", "모드");
    //out.txt 파일을 w 모드로 열겠다. -> 이거에 대한 정보를 fp가 가지고 있는거
    //program과 out.txt간의 데이터를 주고받을 수 있는 스트림이 생성된 것.


    if(fp == NULL){ //포인터 fp가 가리키는 값이 NULL이면 파일 오픈을 실패한 것임
        printf("file open fail\n");

        //stderr는 주로 오류 메시지를 출력할 때 사용 : 표준 에러 스트림으로 출력됨.
        //fprintf(stderr, "에러: 파일을 열 수 없습니다.\n");
        return 0;
        //보통은 에러가 발생한 경우 return 1; 또는 다른 음수 값을 쓰는게 좋음음
    }

    //fprintf
    fprintf(fp, "%s", "Helloworld"); //fp에 --> out.txt에 Helloworld 출력됨
    fprintf(fp, "%s", "문자열을 출력합니다."); //fp에 --> out.txt에 문자열을 출력합니다. 출력됨


    fclose(fp); //fclose(FILE포인터);
    //스트림을 닫는 과정이다.

    // fopen : 스트림 생성 , fclose : 스트림 닫기

    return 0;
}