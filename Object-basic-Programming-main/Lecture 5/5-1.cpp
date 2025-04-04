#include <iostream>
#include <string>
using namespace std;

int main(){
    string name[5];
    string lastname;

    for(int i = 0; i < 5; i++){
        cout << "이름 >> ";
        getline(cin, name[i]);
    }

    lastname = name[0];

    for(int j = 1; j < 5; j++){
        if(name[j] > lastname){
            lastname = name[j];
        }
    }

    cout << "사전에서 가장 뒤에 나오는 문자열은 " << lastname << '\n';

    return 0;

}