//1 ~ N 합계 리턴턴

/*
//1.
//big o --> O(N)
//데이터의 개수 N만큼 연산도 N만큼 해야함함
int sum(int N){
    int total = 0;
    for(int i = 1; i <= N; i++){ //1부터 N까지의 합을 구하므로 O(N) : 입력 갯수만큼 무조건 반복해야해해
        total += i;
    }

    return total;
}
*/

/*
//2.
//big o --> O(1)
//항상 일정하게 연산을 함 --> O(1)
int sum(int N){
    int total = 0;
    total = (N * (N + 1)) / 2;
    return total;
}

*/



//배열에서 원소 접근  
/*
//3.
//big o --> O(1)
int getAt(int* arr, int index){ //배열의 크기와 상관없이 임의 접근(Random access)이 가능하므로 O(1)
    return arr[index];
}
*/


//배열에서 원소 검색
/*
//4.
//big o --> O(N)
int search(int* arr, int size, int target){
    for(int i = 0; i < size; i++){
        if(arr[i] == target){
            return 1; //target과 같은값 즉 찾는 값이 있는 경우
        }
    }
    return 0; //target과 같은값 즉 찾는 값이 없는 경우 : big o --> O(N)
}
*/

/*
//big o --> O(N)
int doNothing(int N){
    int i, total = 0;
    if (N < 0){
        return N; // O(1)
    }
    else{
        for(i = 1; i <= N; i++){ // O(N)
            total += i;
        }
        return total;
    }
}
*/

//O(N제곱)
/*
int doSomeghing(int N){
    int total = 0;
    for (int i = 0; i <= N; i++){
        for(int j = 1; j <= N; j++){
            total += (i + j);
        }
    }
    return total;
}
*/

//O(NM)
/*
int doSomething(int N, int M)

*/

//O(logN )