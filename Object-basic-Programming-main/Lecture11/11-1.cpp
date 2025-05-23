#include <iostream>
#include <string>
using namespace std;

class Circle {
protected:
    int radius;
public:
    Circle(int r = 0){
        radius = r;
    }
    int getRedius(){
        return radius;
    }
    void setRadius(int r){
        radius = r;
    }
};

class NamedCircle : public Circle {
    string name;
public:
    NamedCircle(int r, string n) {
        radius = r;
        name = n;
    }
    //NamedCircle(int r, string n) : Circle(r), name(n) {}  이렇게도 가능(더 효율적)

    void show() {
        cout << "반지름이 " << radius << "인 " << name << '\n';
    
    }
};

int main() {
    NamedCircle waffle(3, "waffle"); // 반지름이 3이고 이름이 waffle인 원
    waffle.show();
}