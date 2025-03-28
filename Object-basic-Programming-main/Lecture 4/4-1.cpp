#include <iostream>

using namespace std;

void f(char c = ' ', int line = 1);

void f(char c, int line){
    for(int i = 0; i < line; i++){
        for(int j = 0; j < 10; j++){
            cout << c;
        }
        cout << '\n';
    }
}

int main() {
    f(); // 한줄에 빈칸을 10개 출력한다.
    f('%'); // 한 줄에 '%'를 10개 출력한다.
    f('@', 5); // 5 줄에 '@' 문자를 10개 출력한다.
}    