#include <iostream>
#include <string>
using namespace std;

int main(){
    string name[5];
    string lastname;

    for(int i = 0; i < 5; i++){
        cout << "�̸� >> ";
        getline(cin, name[i]);
    }

    lastname = name[0];

    for(int j = 1; j < 5; j++){
        if(name[j] > lastname){
            lastname = name[j];
        }
    }

    cout << "�������� ���� �ڿ� ������ ���ڿ��� " << lastname << '\n';

    return 0;

}