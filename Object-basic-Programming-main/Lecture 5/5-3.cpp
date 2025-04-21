#include <iostream>
#include <string>
using namespace std;

class Rectangle{
    public:
        int width;
        int height;
        int getArea();
};
int Rectangle::getArea(){
    return width*height;
}

int main(){
    Rectangle rect; //Rectangle 클래스의 객체 rect를 생성
    rect.width = 3; //rect 객체의 멤버 변수 width에 값 대입
    rect.height = 5; //rect 객체의 멤버 변수 height에 값 대입
    cout << "사각형의 면적은 " << rect.getArea() << '\n';

    return 0;
}