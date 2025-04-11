#include "Adder.h"  // Adder.h 헤더 파일을 포함시킴

Adder::Adder(int a, int b) {  // 생성자 정의
    op1 = a;
    op2 = b;
}

int Adder::process() {  // 덧셈 계산 함수 정의
    return op1 + op2;
}
