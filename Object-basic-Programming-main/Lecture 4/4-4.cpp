/*
#include <iostream>
using namespace std;

template <class T>
void reverseArray(T *a, int size){
    for(int i = 0; i < size/2; i++){
        T temp = *(a+i);
        *(a+i) = *(a+size-1-i);
        *(a+size-1-i) = temp;
    }
}

int main() {
    int x[] = {1, 10, 100, 5, 4};
    reverseArray(x, 5);

    for(int i=0; i<5; i++){
        cout << x[i] << ' '; // 4 5 100 10 1 이 출력된다.
    }
        
    cout << endl;
}
*/
/*
#include <iostream>
using namespace std;

template <class T>
void reverseArray(T a[], int size){
    for(int i = 0; i < size/2; i++){
        T temp = a[i];
        a[i] = a[size -1 -i];
        a[size -1 -i] = temp;
    }
}

int main() {
    int x[] = {1, 10, 100, 5, 4};
    reverseArray(x, 5);

    for(int i=0; i<5; i++){
        cout << x[i] << ' '; // 4 5 100 10 1 이 출력된다.
    }
        
    cout << endl;
}
    */



#include <iostream>
using namespace std;

template <class T>
void reverseArray(T *a, int size){
    T temp[size];
    for(int i = 0; i < size; i++){
        
    }
}

int main() {
    int x[] = {1, 10, 100, 5, 4};
    reverseArray(x, 5);

    for(int i=0; i<5; i++){
        cout << x[i] << ' '; // 4 5 100 10 1 이 출력된다.
    }
        
    cout << endl;
}