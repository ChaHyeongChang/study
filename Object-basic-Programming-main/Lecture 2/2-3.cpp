#include <iostream>
using namespace std;

double biggest(double *p, int size){

    double big = p[0];

    for(int i = 1; i < size; i++){
        if(p[i] > big){
            big = p[i];
        }
    }

    return big;
}

int main(){
    double a[5];
    cout << "5 ���� �Ǽ��� �Է��϶� >> ";

    for(int i = 0; i < 5; i++){
        cin >> a[i];
    }

    cout << "���� ū �� = " << biggest(a, 5) << endl;
    //biggest �Լ��� ��ȯ���� void�� �Ѵٸ�, main �Լ����� cout << "���� ū �� = " << biggest(a, 5);ó�� ��ȯ���� ����ϰ� �ֱ� ������ ������ �߻���!!
    //�Լ��� ��ȯ���� void�� �ϰ� �ʹٸ� biggest�Լ��� cout <<�� �ƴ϶� �ٱ��� ����ؾ��� ex) cout << "���� ū �� = "; biggest(a, 5);

    return 0;
}
