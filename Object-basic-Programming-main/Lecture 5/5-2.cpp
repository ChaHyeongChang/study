#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main(){
    vector<string> name(5);
    string lastname;

    cout << "�̸��� 5�� �Է��϶�" <<'\n';

    for(int i = 0; i < 5; i++){
        cout << i + 1 << ">>";
        getline(cin, name[i]);
    }

    lastname = name[0];

    for(int j = 1; j < 5; j++){
        if(name[j] > lastname){
            lastname = name[j];
        }
    }

    cout << "�������� ���� �ڿ� ������ �̸��� " << lastname << '\n';

    return 0;

}