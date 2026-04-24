#include <iostream>
#include <cstring>
using namespace std;

class BaseArray {
private:
    int capacity; // 동적 할당된 메모리 용량
    int *mem; // 정수 배열을 만들기 위한 메모리 포인터
protected:
    BaseArray(int capacity=100) {
        this->capacity = capacity; mem = new int [capacity];
    }
    ~BaseArray() { 
        delete [] mem; 
    }
    void put(int index, int val) { 
        mem[index] = val; 
    }
    int get(int index) { 
        return mem[index]; 
    }
    int getCapacity() { 
        return capacity; 
    }
};

class MyQueue : public BaseArray{
    int front;
    int rear;
    int size;
public:
    MyQueue(int capacity) : BaseArray(capacity){
        front = 0;
        rear = 0;
        size = 0;
    }

    void enqueue(int value){
        if (size == getCapacity()){
            cout << "큐가 꽉참";
            return;
        }
        put(rear, value);
        rear = (rear + 1) % getCapacity();
        size++;
    }

    int dequeue(){
        if(size == 0){
            cout << "큐가 비어있음";
            return -1;
        }
        int value = get(front);
        front = (front + 1) % getCapacity();
        size--;
        return value;
    }

    int capacity(){
        return getCapacity();
    }

    int length(){
        return size;
    }
};

int main() {
    MyQueue mQ(100);

    int n;
    cout << "큐에 삽입할 5개의 정수를 입력하라>> ";
    for(int i=0; i<5; i++) {
        cin >> n;
        mQ.enqueue(n); // 큐에 삽입
    }

    cout << "큐의 용량 : " << mQ.capacity() << ", 큐의 크기 : " << mQ.length() << endl; 
    cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";
    while(mQ.length() != 0) {
        cout << mQ.dequeue() << ' '; // 큐에서 제거하여 출력
    }
    cout << endl << "큐의 현재 크기 : " << mQ.length() << endl;
}