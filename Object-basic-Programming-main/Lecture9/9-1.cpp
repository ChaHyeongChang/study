#include <iostream>

using namespace std;

class Circle {
private:
    int radius; 
public:
    Circle() { radius = 1; }
    Circle(int radius) { this->radius = radius; }
    double getArea() { return 3.14*radius*radius; }
}; 

void swap(Circle &a, Circle &b){
    Circle temp = a;
    a = b;
    b = temp;
}

int main(){
    Circle A(20);
    Circle B(30);

    cout << "A의 면적 = " << A.getArea() << "\tB의 면적 = " << B.getArea() << '\n';

    swap(A, B);

    cout << "A의 면적 = " << A.getArea() << "\tB의 면적 = " << B.getArea() << '\n';

    return 0;
}