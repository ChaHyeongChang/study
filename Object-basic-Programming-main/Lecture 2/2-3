#include <iostream>
using namespace std;

double biggest(double *p, int size){

    double big = p[0];

    for(int i = 1; i < size; i++){
        if(p[i] > big){
            big = p[i];
        }
    }

    return big;
}

int main(){
    double a[5];
    cout << "5 개의 실수를 입력하라 >> ";

    for(int i = 0; i < 5; i++){
        cin >> a[i];
    }

    cout << "제일 큰 수 = " << biggest(a, 5) << endl;
    //biggest 함수의 반환형을 void로 한다면, main 함수에서 cout << "제일 큰 수 = " << biggest(a, 5);처럼 반환값을 기대하고 있기 때문에 오류가 발생함!!
    //함수의 반환형을 void로 하고 싶다면 biggest함수를 cout <<이 아니라 바깥에 출력해야함 ex) cout << "제일 큰 수 = "; biggest(a, 5);

    return 0;
}
