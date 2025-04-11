#include <iostream>
using namespace std;

class MyVector{
    int *mem;
    int size;
public:
    MyVector(int n = 100, int val = 0);
    ~MyVector() { delete [] mem;}
    void show();
};


MyVector::MyVector(int n, int val) { 
    mem = new int [n]; 
    size = n;
    for (int i=0; i<size; i++) 
        mem[i] = val;
}

void MyVector::show(){
    for(int i = 0; i < size; i++){
        cout << mem[i] << " ";
    }
    cout << '\n';
}

int main(){
    MyVector a; // a(100, 0); °ú µ¿ÀÏ
    MyVector b(10, 3);

    a.show();
    b.show();
}