#include "Adder.h"  // Adder.h ��� ������ ���Խ�Ŵ

Adder::Adder(int a, int b) {  // ������ ����
    op1 = a;
    op2 = b;
}

int Adder::process() {  // ���� ��� �Լ� ����
    return op1 + op2;
}
