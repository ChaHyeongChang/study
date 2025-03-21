

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    srand((unsigned int)time(NULL));

    printf("\n\n === 대머리 게임 === \n\n");

    int treatment = rand() % 4; // 발모제 선택(0~3)

    int cntShowBottle = 0; // 이번 게임에 보여줄 병 개수
    int prevShowBottle = 0; // 앞 게임에 보여준 병 개수
    //서로 보여주는 병 개수를 다르게 해서 정답률을 향상시키기 위해 (처음에 2개 -> 다음엔 3개...)

    //3번의 기회(3번의 발모제 투여 시도)
    for(int i = 1; i <= 3; i++){

        int bottle[4] = {0, 0, 0, 0}; //4개의 병
        do {
            cntShowBottle = rand() % 2 + 2; // 보여줄 병 개수 (2 ~ 3)
        } while(cntShowBottle == prevShowBottle);
        
        prevShowBottle = cntShowBottle; //이번 회차의 약병 개수 저장
        printf(" > %d번째 시도 : ", i);
        int isIncluded = 0; // 보여줄 병 중에 발모제가 포함되었는지 여부 (1 : 포함, 0 : 불포함)

        //보여줄 병 종류를 선택
        for(int j = 0; j < cntShowBottle; j++){

            int randBottle = rand() % 4; // 0~3

            //아직 선택되지 않은 약병이면, 선택 처리
            if(bottle[randBottle] == 0){    
                bottle[randBottle] = 1;
                if(randBottle == treatment){
                    isIncluded = 1;
                }
            }
            //이미 선택된 약병이면 중복이므로 다시 선택택
            else{
                j--; //else 조건에 해당하면 j--가 먼저 실행되고 다시 for문으로 넘어가면서 j++이 실행됨
            }

        }

        //사용자에게 문제 표시
        for(int k = 0; k < 4; k++){
            if(bottle[k] == 1){
                printf("%d ", k + 1);
            }
        }
        printf("번 물약을 머리에 바릅니다.\n\n");

        if (isIncluded == 1){
            printf(">> 성공 ! 머리카락이 났음 \n\n");
        }
        else{
            printf(">> 실패 ! 머리카락이 나지 않았어요.\n\n");
        }

        printf("\n   계속하려면 Enter를 누르세요. \n");
        getchar(); // 아무값이나 입력하면 다음 코드를 실행함, 엔터만 치게되면 버퍼에는 아무것도 없는 상태(만약-> abc엔터를 입력했다면 버퍼에는 bc\n)이고  (사용자가 입력한 값을 반환받지 않아서 경고메시지가 나타날 수 있음 ==> (void) getchar(); 로 쓰면 해결)
    }

    printf("\n발모제는 몇 번일까요?? : ");
    int answer;
    scanf("%d", &answer);

    if(answer == treatment + 1){
        printf("\n >> 정답!\n");
    }
    else{
        printf("\n >> 땡~ 틀렸어요, 정답은 %d입니다.\n", treatment + 1);
    }


    return 0;
}


//////////////216p 셀프체크///////////////
/*
#include <stdio.h>
#include <string.h>

int main(void){
    int score[5] = {76, 84, 80, 92, 96};

    int total_score = 0;
    float average_score = 0.0f;
    for(int i = 0; i < sizeof(score)/sizeof(score[0]); i++){ //sizeof(score)/sizeof(score[0]) 배열의 길이 구하는 법 배열의 메모리 크기 (5 * 4) / int형의 메모리 크기 4 ==> 5
        total_score += score[i];
    }

    average_score = total_score / (float)(sizeof(score)/sizeof(score[0])); //나누기를 할때 몫을 소수점까지 계산하기 위해서 앞에 (float)를 붙임임

    printf("총점은 %d점, 평균은 %.1f점 입니다.", total_score, average_score);

    return 0;
}
*/

/////점수를 하나씩 입력받기
/*
#include <stdio.h>
#include <string.h>

int main(void){
    int score[5] = {0};

    int total_score = 0;
    float average_score = 0.0f;

    //사용자로부터 점수 입력 받기
    for(int i = 0; i < sizeof(score)/sizeof(score[0]); i++){ //sizeof(score)/sizeof(score[0]) 배열의 길이 구하는 법 배열의 메모리 크기 (5 * 4) / int형의 메모리 크기 4 ==> 5
        printf("%d번 과목 점수를 입력하세요 : ", i + 1);
        scanf("%f", &score[i]);
    }

    for(int i = 0; i < sizeof(score) / sizeof(score[0]); i++){ //sizeof(score)/sizeof(score[0]) 배열의 길이 구하는 법 배열의 메모리 크기 (5 * 4) / int형의 메모리 크기 4 ==> 5
        total_score += score[i];
    }

    average_score = total_score / (float)(sizeof(score) / sizeof(score[0])); //나누기를 할때 몫을 소수점까지 계산하기 위해서 앞에 (float)를 붙임

    printf("총점은 %d점, 평균은 %.1f점 입니다.", total_score, average_score);

    return 0;
}
*/

