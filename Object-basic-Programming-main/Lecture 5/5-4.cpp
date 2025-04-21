#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    string f;
    string r;

    cout << "여러 줄의 문자열을 입력하세요. 입력의 끝은 &문자입니다" << '\n';

    getline(cin, s, '&');
    cin.ignore(); //'&'까지 입력받고 s에 저장하므로 버퍼에 '\n'이 남아서 버퍼를 지우기 위해 사용함.

    cout << "find: ";
    getline(cin, f); //'\n'까지 입력받고 f에 저장하므로 버퍼에 아무것도 남지 않아서 cin.ignore(); 사용안함.

    cout << "replace: ";
    getline(cin, r); //'\n'까지 입력받고 f에 저장하므로 버퍼에 아무것도 남지 않아서 cin.ignore(); 사용안함.
    
    int startIndex = 0;
    while(true){
        int fIndex = s.find(f, startIndex);
        if(fIndex == -1){
            break;
        }
        s.replace(fIndex, f.length(), r);
        startIndex = fIndex + r.length();
    }
    
    cout << s;

    return 0;
}