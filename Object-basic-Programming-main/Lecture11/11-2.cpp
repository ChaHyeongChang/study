#include <iostream>
#include <string>
using namespace std;

class Circle {
protected:
    int radius;
public:
    Circle(int r = 0) { 
        radius = r; 
    }

    double getArea() { 
        return 3.14 * radius * radius; 
    }

    int getRadius() { 
        return radius; 
    }
};

class NamedCircle : public Circle {
    string name;
public:
    NamedCircle() {
        name = "";
    }

    NamedCircle(int r, string n) {
        radius = r;
        name = n;
    }
    string getName() { 
        return name; 
    }
};

int main() {

    NamedCircle pizza[5];  

    int r;
    string n;

    cout << "5개의 정수 반지름과 원의 이름을 입력하세요." << '\n';

    for (int i = 0; i < 5; i++) {
        cout << i + 1 << " >> ";
        cin >> r >> n;
        pizza[i] = NamedCircle(r, n);  // 복사 대입
    }

    
    int maxIndex = 0;
    for (int i = 1; i < 5; i++) {
        if (pizza[i].getArea() > pizza[maxIndex].getArea()) {
            maxIndex = i;
        }
    }

    cout << "가장 면적이 큰 피자는 " << pizza[maxIndex].getName() << "입니다." << '\n';

    return 0;
}