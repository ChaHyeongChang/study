#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    string f;
    string r;

    cout << "여러 줄의 문자열을 입력하세요. 입력의 끝은 &문자입니다." << '\n';

    getline(cin, s, '&');
    cin.ignore();

    cout << "find: ";
    getline(cin, f);

    cout << "replace: ";
    getline(cin, r);
    
    int pos = 0;


    while ((pos = s.find(f, pos)) != string::npos) {
        s.replace(pos, f.length(), r);
        pos += r.length();  
    }

    
    cout << s;

    return 0;
}