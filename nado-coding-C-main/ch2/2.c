#include<stdio.h>

int main(void){
    
    char name[256];
    int age;
    float weight;
    float height;
    char what[256];

    printf("이름이 뭔가요? ");
    scanf("%s", name, sizeof(name));
    
    
    printf("몇 살? ");
    scanf("%d", &age);

    
    printf("몸무게는? ");
    scanf("%f", &weight);

    
    printf("키는 몇cm? ");
    scanf("%f", &height);

    
    printf("범죄명은? ");
    scanf("%s", what, sizeof(what));

    printf("\n\n ---- 범죄자 정보 ----");
    printf("이름 : %s\n", name);
    printf("나이 : %d\n", age);
    printf("몸무게 : %.1f\n", weight);
    printf("키 : %.1f\n", height);
    printf("범죄명 : %s\n", what);

    return 0;
}
