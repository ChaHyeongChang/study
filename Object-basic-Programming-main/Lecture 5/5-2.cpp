#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main(){
    vector<string> name(5);
    string lastname;

    cout << "이름을 5개 입력하라" <<'\n';

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

    cout << "사전에서 가장 뒤에 나오는 이름은 " << lastname << '\n';

    return 0;

}