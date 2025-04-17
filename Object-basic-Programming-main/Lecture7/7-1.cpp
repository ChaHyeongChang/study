#include <iostream>
#include "Ram.h"
using namespace std;

int main(){
    Ram ram; //Ram클래스의 객체 ram생성함.

    ram.write(100, 20); //100번지에 20 저장
    ram.write(101, 30); //101번지에 30 저장

    char res = ram.read(100) + ram.read(101); // 20 + 30 = 50
    ram.write(102, res); //102번지에 50 저장

    cout << "102번지의 값 = " << (int)ram.read(102) << '\n'; //102번지의 메모리 값 출력력
}