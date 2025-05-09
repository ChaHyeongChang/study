#include <iostream>
#include <cstring>

using namespace std;

class Book {
    char *title; // 제목 문자열
    int price; // 가격
public:
    Book(char* title, int price);
    Book(Book &a);
    ~Book();
    void set(char* title, int price);
    void show() { cout << title << ' ' << price << "원" << endl; }
};


Book::Book(char* title, int price){
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
    this->price = price;
}

Book::Book(Book &a){
    this->title = new char[strlen(a.title) + 1];
    strcpy(this->title, a.title);
    this->price = a.price;
}

Book::~Book(){
    delete [] title;
}
void Book::set(char* title, int price){
    delete [] this->title;
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
    this->price = price;
}

int main() {
    Book cpp("명품C++", 10000);
    Book java = cpp;
    java.set("명품자바", 12000);
    cpp.show();
    java.show();
}