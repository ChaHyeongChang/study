

/*
int main(void){
    int N[] = {5, 5, 2, 3, 4, 1};
    int temp;
    for(int i = 0; i < sizeof(N); i++){
        for(int j = 1; j < sizeof(N); j++){
            if(N[i] > N[j]){
                temp = N[i];
                N[i] = N[j];
                N
            }
        }
    }
}
    */
//2750번
//1158번 : 요세푸스 문제 해결해보기
//10818, 2562, 10872
//11720, 3052, 10810, 10872
//집가서 자료구조 기초랑 리스트 코드짜보기

//연결 리스트 활용

//동적할당 : 실행시간에 크기를 결정함

//노드 : 숫자와 다음 주소가 들어가있음

//단일연결 : 다음 노드가 없으면 NULL들어감
//이중연결 : 다음 노드가 없으면 NULL들어감
//원형연결


//연결리스트 장점 : 삽입 삭제가 빠름
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*

int main(void){

    int n;


    int min, max;

    scanf("%d", &n);

    int *num = (int *)malloc(sizeof(int) * n);

    

    for(int k = 0; k < n; k++){
        scanf("%d", &num[k]);
    }
    
    max = num[0];
    min = num[0];

    for(int i = 1; i < n; i++){
        if(num[i] >= max){
            max = num[i];
        }
        else if(num[i] < min){
            min = num[i];
        }
    }


    printf("%d %d", min, max);

    return 0;

}

*/

int main(void){
    int num[9] = {0, };
    int max;
    int maxidx;

    for(int i = 0; i < 9; i++){
        scanf("%d", &num[i]);
    }

    max = num[0];

    for(int j = 1; j < 9; j++){
        if(num[j] >= max){
            max = num[j];
            maxidx = j;
        }
    }

    printf("%d\n%d", max, maxidx);

    return 0;
}