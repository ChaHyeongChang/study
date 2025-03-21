//173~174p 비밀번호 맞추기 게임
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomNumber(int level);
void showQuestion(int level, int num1, int num2);
void succes();
void fail();

int main(void){

    srand((unsigned int)time(NULL));
    int count = 0;

    for(int i = 1; i <= 5; i++){
        int num1 = getRandomNumber(i);
        int num2 = getRandomNumber(i);
        showQuestion(i, num1, num2);
        int answer = -1;  //변수의 초깃값 : 초깃값은 경우에 따라 다르게 설정한다. 만약 어떤 프로그램이 3가지 동작을 제공하고 각 동작의 번호가 1,2,3이라면 이들을 제외한 다른 숫자를 사용함. 
                          //그러면 사용자로부터 값을 입력받았을 때 이 값이 1,2,3에 해당되면 의도적인 값이므로 해당 동작을 수행하고 그렇지 않으면 다시 입력하라거나 프로그램을 종료할 수 있다. 
                          //그런데 초깃값을 1로 설정하면 사용자의 입력 대기 부분이 의도치 않게 삭제됐을 때 원하지 않는 1번 동작이 수행될 수도 있다. 그래서 혼란을 피하는 방향으로 초깃값을 설정하기도 한다.
        scanf("%d", &answer);
        if(answer == -1){
            printf("\n프로그램을 종료합니다.\n");
            exit(0); // exit() 는 현재 실행 중인 프로그램을 종료하는 함수. 이때 소괄호에 넣는 전달값에 따라 종료 의미가 다르다. 앞에서 처럼 0을 넣으면 정상 종료, 다른 숫자(일반적으로 1)를 넣으면 오류 발생으로 인한 종료이다. 
                     // exit() --> <stdlib.h>를 작성해야 사용가능
        }
        else if(answer == num1 * num2){
            succes();
            count++;
        }
        else{
            fail();
        }

    }

    printf("\n\n비밀번호를 %d개 맞혔습니다.\n", count);

    return 0;
}

int getRandomNumber(int level){
    return rand() % (level * 9) + 1;
}

void showQuestion(int level, int num1, int num2){
    printf("\n\n\n########## %d번째 비밀번호 ##########\n", level);
    printf("\n\t%d x %d ? \n\n", num1, num2);
    printf("###################################\n");
    printf("\n비밀번호를 입력하세요.(종료를 원하면 -1 입력) >> ");
}

void succes(){
    printf("\n >> GOOD! 정답입니다.\n");
}

void fail(){
    printf("\n >> 땡~~!^^ 틀렸습니다.\n");
}



//////////////178p 셀프체크///////////////
/*
#include <stdio.h>

void convert_time(int minute);

int main(void){

    int time = 0;
    
    printf("게임을 몇 분 하실건가요 : ");
    scanf("%d", &time);

    convert_time(time);

    return 0;
}

void convert_time(int minute){
    int hour = minute / 60;
    int remain_minute = minute % 60;

    printf("%d시간 %d분 충전됐습니다.\n", hour, remain_minute);
}
*/
