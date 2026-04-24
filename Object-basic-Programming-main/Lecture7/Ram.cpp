#include <iostream>
#include "Ram.h"

using namespace std;

Ram::Ram(){
    size = 100 * 1024;

    for(int i = 0; i < size; i++){
        mem[i] = 0; 
    }
}

Ram::~Ram(){
    cout << "메모리 제거됨" <<  '\n';
}

char Ram::read(int address){
    if(address < 0 || address >= size){
        cout << "범위 벗어남" << '\n';
        return -1;
    }

    return mem[address]; //메모리 주소에 저장된 값을 저장함
}

void Ram::write(int address, char value){
    if(address < 0 || address >= size){
        cout << "범위 벗어남" << '\n';
        return;
    }
    mem[address] = value;
}