#include <iostream>
#include <string>
using namespace std;

class Shape {
protected:
    string name;
public:
    Shape(string n) {
        name = n;
    }
    virtual ~Shape() {}
    string getName() {
        return name;
    }
    virtual int getArea() = 0; // 순수 가상 함수
};

class Oval : public Shape {
    int width, height;
public:
    Oval(string n, int w, int h) : Shape(n) {
        width = w;
        height = h;
    }
    int getArea() override {
        return 3.14 * width * height;
    }
};

class Rect : public Shape {
    int width, height;
public:
    Rect(string n, int w, int h) : Shape(n) {
        width = w;
        height = h;
    }
    int getArea() override {
        return width * height;
    }
};

class Triangular : public Shape {
    int base, height;
public:
    Triangular(string n, int b, int h) : Shape(n) {
        base = b;
        height = h;
    }
    int getArea() override {
        return (base * height) / 2;
    }
};

int main() {
    Shape *p[3];
    p[0] = new Oval("빈대떡", 10, 20);
    p[1] = new Rect("찰떡", 30, 40);
    p[2] = new Triangular("토스트", 30, 40);
    for(int i=0; i<3; i++)
    cout << p[i]->getName() << " 넓이는 " << p[i]->getArea() << endl;
    for(int i=0; i<3; i++) delete p[i];
}
