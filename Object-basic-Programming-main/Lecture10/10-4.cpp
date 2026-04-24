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

    friend bool operator==(const Book& b, int price);
    friend bool operator==(const Book& b, const string& title);
    friend bool operator==(const Book& a1, const Book& b1);
};

// price 비교
bool operator==(const Book& b, int price) {
    return b.price == price;
}

// title 비교
bool operator==(const Book& b, const string& title) {
    return b.title == title;
}

// 전체 비교
bool operator==(const Book& a1, const Book& b1) {
    return a1.title == b1.title && a1.price == b1.price && a1.pages == b1.pages;
}

int main() {
    Book a("명품 C++", 30000, 500), b("고품 C++", 30000, 500);

    if (a == 30000) cout << "정가 30000원" << endl;
    if (a == "명품 C++") cout << "명품 C++ 입니다." << endl;
    if (a == b) cout << "두 책이 같은 책입니다." << endl;

    return 0;
}
