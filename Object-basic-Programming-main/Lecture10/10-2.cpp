#include <iostream>
#include <string>
using namespace std;

class Book {
    string title;
    int price;
    int pages;
public:
    Book(string title = "", int price = 0, int pages = 0) {
        this->title = title;
        this->price = price;
        this->pages = pages;
    }

    void show() {
        cout << title << ' ' << price << "원 " << pages << " 페이지" << endl;
    }

    string getTitle() {
        return title;
    }

    // 외부 연산자 함수가 private 멤버 접근할 수 있도록
    friend Book& operator+=(Book& b, int value);
    friend Book& operator-=(Book& b, int value);
};

// 외부 함수로 연산자 오버로딩
Book& operator+=(Book& b, int value) {
    b.price += value;
    return b;
}

Book& operator-=(Book& b, int value) {
    b.price -= value;
    return b;
}

int main() {
    Book a("청춘", 20000, 300), b("미래", 30000, 500);
    a += 500;
    b -= 500;
    a.show();
    b.show();
    return 0;
}