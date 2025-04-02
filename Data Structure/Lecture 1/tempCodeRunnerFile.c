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