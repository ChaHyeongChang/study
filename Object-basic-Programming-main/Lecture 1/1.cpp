#include <iostream>
#include <string>
using namespace std;

int main(){
    char cstr[50];
    string str;

    cin>>cstr;
    getline(cin,str);

    cout<<"C-Style:"<<cstr<< endl;
    cout<<"C++Style:"<<str<< endl;
}