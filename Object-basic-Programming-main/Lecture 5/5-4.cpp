#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    string f;
    string r;

    cout << "���� ���� ���ڿ��� �Է��ϼ���. �Է��� ���� &�����Դϴ�." << '\n';

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