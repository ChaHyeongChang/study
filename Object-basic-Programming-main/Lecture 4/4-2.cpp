/*
//4-2(1)
#include <iostream>

using namespace std;

int big(int x, int y){
    int max = 100;

    if(x > y){
        if (x <= max){
            return x;
        }
        else {
            return max;
        }
    }

    else if (x <= y){
        if (y <= max){
            return y;
        }
        else {
            return max;
        }
    }

    return max;

}

int big(int x, int y, int z){
    int bigg;

    if(x > y){
        bigg = x;
    }
    else if(x <= y){
        bigg = y;
    }

    if (bigg > z){
        return bigg;
    }
    else{
        return z;
    }

}

int main() {
    int x = big(3, 5); // 3과 5중 큰 값 5는 최대값 100보다 작으므로, 5 리턴
    int y = big(300, 60); // 300과 60중 큰 값 300이 최대값 100보다 크므로, 100 리턴
    int z = big(30, 60, 50); // 30과 60 중 큰 값 60이 최대값 50보다 크므로, 50 리턴
    cout << x << ' ' << y << ' ' << z << endl;
}
*/


//4-2(2)
#include <iostream>

using namespace std;

int big(int x, int y, int z = 100){
    int bigg;

    if(x > y){
        bigg = x;
    }
    else if(x <= y){
        bigg = y;
    }

    if (bigg > z){
        return z;
    }
    else{
        return bigg;
    }

}

int main() {
    int x = big(3, 5); // 3과 5중 큰 값 5는 최대값 100보다 작으므로, 5 리턴
    int y = big(300, 60); // 300과 60중 큰 값 300이 최대값 100보다 크므로, 100 리턴
    int z = big(30, 60, 50); // 30과 60 중 큰 값 60이 최대값 50보다 크므로, 50 리턴
    cout << x << ' ' << y << ' ' << z << endl;
}
