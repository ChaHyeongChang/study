#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h> //time.h로 시간측정이 안되어 고해상도 시간을 측정하기 위해서 Windows.h를 사용함.

//다항식의 계수와 지수를 저장하는 구조체 선언
typedef struct {
    double coef;
    int expon;
} Polynomial;

//연결리스트에서 사용할 노드의 구조체를 선언하기 위한 포인터 타입을 미리 정의해둠.
typedef struct polyNode* PolyPointer;
//연결리스트의 polyNode구조체 생성성
typedef struct polyNode {
    double coef; //계수
    int expon; //지수
    PolyPointer link; //노드의 다음 주소를 가리킴
} PolyNode;

// 다항식의 배열을 내림차순으로 정할하는 함수
void sort_desc(Polynomial* p, int len) {
    for (int i = 0; i < len - 1; i++) //배열의 맨 앞에서 시작
        for (int j = i + 1; j < len; j++) //현재 위치 이후의 요소들과 비교를 해서
            if (p[i].expon < p[j].expon) { //차수가 더 큰 항이 있으면
                Polynomial tmp = p[i]; //Polynomail의 구조체 변수tmp를 사용해 두 항의 위치를 바꿈!
                p[i] = p[j];
                p[j] = tmp;
            }
}

//같은 차수를 가지는 항들을 합쳐서 하나로 만들어주는 함수
int merge_terms(Polynomial* poly, int len) {
    if (len == 0) return 0; //길이가 0이면 다항식이 없는 것이므로 바로 반환

    int idx = 0; //합친 결과를 저장하는 변수 idx선언
    for (int i = 1; i < len; i++) { //두 번째 항부터 차례대로 확인함
        if (poly[idx].expon == poly[i].expon){ //앞의 항과 계수가 같으면
            poly[idx].coef += poly[i].coef; //계수를 더해줌
        } 
        else
        {
            poly[++idx] = poly[i]; //지수가 다르면 다음 위치에 저장
        } 
    }

    return idx + 1; //합쳐진 총 항의 개수를 반환함.
}


//다항식 배열을 출력 파일 형식에 맞게 출력해주는 함수
void print_poly(Polynomial* p, int len, FILE* fp) {
    for (int i = 0; i < len; i++) {
        if (p[i].coef != 0) { //계수가 0이 아니면
            if (p[i].coef == (int)p[i].coef) //계수가 정수인지 확인해서
                fprintf(fp, "%d", (int)p[i].coef); //정수이면 계수 부분을 정수로 출력해주고
            else
                fprintf(fp, "%.2lf", p[i].coef); //정수가 아니면 소수점 둘째 자리까지 출력해줌.

            fprintf(fp, "x^%d", p[i].expon); //그러고 나서 지수 부분을 출력

            if (i != len - 1) fprintf(fp, " + "); //마지막 항이 아니면 +까지 출력해주고 마무리
        }
    }
    fprintf(fp, "\n"); //한 다항식이 끝나면 줄바꿈
}


// 1번 : 배열 방식 개선 전 --> 다항식 a와 b를 더해서 결과에 저정하고 결과 함수는 result_len에 저장함
void padd_array_original(Polynomial* a, int a_len, Polynomial* b, int b_len, Polynomial* result, int* result_len) {

    *result_len = 0; //결과 다항식의 항 개수를 미리 0으로 초기화

    while (a_len > 0 && b_len > 0) { //항이 안남을때까지 반복함
        if (a[0].expon < b[0].expon) { //b의 지수가 더 크면
            result[(*result_len)++] = b[0]; //b의 항을 결과에 추가시킴

            for (int i = 0; i < b_len - 1; i++) {
                b[i] = b[i + 1]; //b의 항들을 앞으로 한칸씩 당김
            }
            b_len--; //b의 총 항의 개수는 감소함.
        } 
        else if (a[0].expon == b[0].expon) { //지수부분이 같으면
            double sum = a[0].coef + b[0].coef;
            if (sum != 0)
                result[(*result_len)++] = (Polynomial){sum, a[0].expon}; //더한값이 0이 아닐때 결과에 추가
                
            for (int i = 0; i < a_len - 1; i++) { //a항들을 한칸씩 앞으로 당김
                a[i] = a[i + 1];
            }

            for (int i = 0; i < b_len - 1; i++) { //b항들을 한칸씩 앞으로 당김
                b[i] = b[i + 1];
            }

            a_len--; b_len--; //a와b의 항의 개수 하나씩 감소
        } 
        else { //a의 지수가 더 클때
            result[(*result_len)++] = a[0];
            for (int i = 0; i < a_len - 1; i++) { //결과에 a의 항을 추가하고 a의 항을 앞으로 한칸씩 당김
                a[i] = a[i + 1];
            }
            a_len--; //a의 총 항의 개수를 감소시킴킴
        }
    }

    while (a_len-- > 0) { //a항만 남으면 남은 a의 항을 전부 result로 저장
        result[(*result_len)++] = *(a++); //a항이 하나씩 반복해서 result에 저장되므로 result다항식의 길이도 1씩증가됨
    }
    while (b_len-- > 0) { //b항만 남으면 남은 b의 항을 전부 result로 저장
        result[(*result_len)++] = *(b++); //b항이 하나씩 반복해서 result에 저장되므로 result다항식의 길이도 1씩증가됨
    }
}


// 2번 : 배열 방식 개선 후 --> 두 다항식의 배열을 인덱스로 비교해서 더함
void padd_array_improved(Polynomial* a, int a_len, Polynomial* b, int b_len, Polynomial* result, int* result_len) {
    *result_len = 0; //결과 다항식의 항 개수를 미리 0으로 초기화
    int i = 0, j = 0;

    while (i < a_len && j < b_len) { //항이 남아있을때까지 계속 반복
        if (a[i].expon > b[j].expon) //a[i]의 지수가 더 크면
            result[(*result_len)++] = a[i++]; //a의 항을 결과에 복사해주고 i를 증가시킴(다음 지수를 가리키게 할려고)
        else if (a[i].expon < b[j].expon) //b[j]의 지수가 더 크면
            result[(*result_len)++] = b[j++]; //b의 항을 결과에 복사해주고 j를 증가시킴(다음 지수를 가리키게 할려고)
        else { //a[i]와 b[i]의 지수가 같은 경우
            double sum = a[i].coef + b[j].coef; 
            if (sum != 0.0)
                result[(*result_len)++] = (Polynomial){sum, a[i].expon}; //두 계수의 값을 더하고 0이 아니면 결과에 저장하기
            i++; j++; //a항, b항 둘다 다음 지수를 가리키게 하기위해서 1씩 증가
        }
    }
    while (i < a_len) {
        result[(*result_len)++] = a[i++]; //a항만 남아있으면 현재a[i]의 항을 결과에 저장해주고 다음 지수를 가리키게하는 것을 반복함(a항이 끝날때까지)
        //result다항식의 항도 a[i]의 항이 저장됨에 따라서 하나씩 증가됨.
    }
    while (j < b_len) {
        result[(*result_len)++] = b[j++]; //b항만 남아있으면 현재b[i]의 항을 결과에 저장해주고 다음 지수를 가리키게하는 것을 반복함(b항이 끝날때까지)
        //result다항식의 항도 b[i]의 항이 저장됨에 따라서 하나씩 증가됨.
    }
}

// 3번 : 연결 리스트 방식

//새로운 항을 생성해서 연결리스트의 뒤에 붙여주는 함수
void attach(PolyPointer* ptr, PolyPointer* rear, double coefficient, int exponent) {
    PolyPointer temp = (PolyPointer)malloc(sizeof(PolyNode)); //temp라는 새 노드를 동적할당 해줌
    temp->coef = coefficient; //temp의 계수 값을 설정
    temp->expon = exponent; //temp의 지수를 설정
    temp->link = NULL; //temp는 마지막 노드이므로 다음 노드가 없어서 NULL로 저장
    (*rear)->link = temp; //원래 있던 마지막 노드의 rear부분을 새로만든 temp의 주소로 저장
    *rear = temp; //다시 rear을 마지막 노드로 설정해줌
}


// 연결 리스트 방식으로 다항식 덧셈을 수행하는 함수
PolyPointer padd_list(PolyPointer a, PolyPointer b) {
    PolyPointer front, rear, temp;
    double sum;
    /*
    if (head == NULL) {
        head = newNode;     // 첫 노드면 head 초기화
        tail = newNode;
    } 
    else {
        tail->link = newNode;
        tail = newNode;
    }
    */
    //위 처럼 head가 NULL인 경우의 조건문을 사용하지 않으려고 임시로 노드를 생성했음.
    rear = (PolyPointer)malloc(sizeof(PolyNode)); //임시로 헤더 노드를 생성해줌(다항식의 시작점을 알려주는 역할!)
    front = rear; //front를 rear노드부터 시작할 수 있도록 해줌

    while (a && b) {//a와b항이 모두 남아있을 때까지 반복해줌
        if (a->expon > b->expon) {
            attach(&rear, &rear, a->coef, a->expon); //현재 rear만 사용하고 있어서 ptr부분에 rear만 넣어줌
            a = a->link; //a를 a가 가리키는 다음 노드로 저장
        } else if (a->expon < b->expon) {
            attach(&rear, &rear, b->coef, b->expon); //현재 rear만 사용하고 있어서 ptr부분에 rear만 넣어줌
            b = b->link; //b를 b가 가리키는 다음 노드로 저장
        } else {
            sum = a->coef + b->coef;
            if (sum != 0.0) 
                attach(&rear, &rear, sum, a->expon); //현재 rear만 사용하고 있어서 ptr부분에 rear만 넣어줌
            a = a->link; //a를 a가 가리키는 다음 노드로 저장
            b = b->link; //b를 b가 가리키는 다음 노드로 저장
        }
    }
    while (a) {  //a만 항에 남아있으면
        attach(&rear, &rear, a->coef, a->expon); //a항이 끝날때까지 연결리스트 맨뒤에 남은 항들을 결과에 추가시킴
        a = a->link; 
    }
    while (b) { //b만 항에 남아있으면
        attach(&rear, &rear, b->coef, b->expon); //b항이 끝날때까지 연결리스트 맨뒤에 남은 항들을 결과에 추가시킴
        b = b->link; 
    }

    rear->link = NULL; //rear를 NULL로 지정함(연결리스트의 끝이므로)
    temp = front; //temp에 front값을 넣음(맨앞 노드는 사용하지 않는 더미였으므로)
    front = front->link; //front노드를 실제 결과리스트의 시작점으로 이동시킴(front노드의 다음 노드로)
    free(temp); //temp를 없앰으로써 더미 노드 삭제
    return front;
}

// 파일(fp)에서 n개의 항을 읽어 연결 리스트로 생성하는 함수
PolyPointer create_list(FILE* fp, int n) {
    PolyPointer head = NULL, rear = NULL; //시작노드와 마지막 노드를 생성함
    for (int i = 0; i < n; i++) {
        PolyPointer temp = (PolyPointer)malloc(sizeof(PolyNode));
        fscanf(fp, "%lf %d", &temp->coef, &temp->expon); //계수랑 지수 부분을 읽음
        temp->link = NULL; //새 노드의 다음 주소는 NULL
        if (!head) { //head가 아직 NULL인 경우(첫 노드인 경우)
            head = rear = temp; //시작 노드와 마지막 노드의 값은 같음
        }
        else {
            rear->link = temp;  //새로 생성한 노드를 원래의 마지막 노드의 다음 주소가 가리키게 함
            rear = temp;  //그러고나서 마지막 노드를 새로 생성한 노드로 바꿈
        }
    }
    return head; //리스트의 시작주소(head)를 반환해서 밖에서도 리스트에 접근할 수 있게 해줌(함수 밖, main에서 쓸려고)
}

// 연결 리스트 p를 배열 arr로 복사하고, 총 복사한 항의 개수를 반환하는 함수
int list_to_array(PolyPointer p, Polynomial* arr) {
    int count = 0;
    while (p) { //리스트의 끝이 나올때까지 반복함 (NULL이 나올때까지)
        arr[count].coef = p->coef; //리스트의 계수부분을 배열에 복사함
        arr[count].expon = p->expon; //리스트의 지수부분을 배열에 복사함
        count++; //항의 개수 증가
        p = p->link; //리스트가 다음 노드로 이동하게 해줌
    }
    return count; //총 항의 수를 반환함
}

// 1번 : 배열 방식 개선 전 --> 다항식 a와 b를 더해서 결과에 저정하고 결과 함수는 result_len에 저장함
void func1(FILE* fin, FILE* fout) {
    int n, m;
    fscanf(fin, "%d %d", &n, &m); //a와 b의 다항식의 항의 개수를 입력에서 읽음

    Polynomial* a = malloc(n * sizeof(Polynomial)); //다항식 a를 저장할 동적배열 생성
    Polynomial* b = malloc(m * sizeof(Polynomial)); //다항식 b를 저장할 동적배열 생성
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%lf %d", &a[i].coef, &a[i].expon); //input.txt에서 a다항식의 항들을 읽어오는 부분
    }
    for (int i = 0; i < m; i++) {
        fscanf(fin, "%lf %d", &b[i].coef, &b[i].expon); //input.txt에서 b다항식의 항들을 읽어오는 부분
    }

    // 각각의 다항식들을 내림차순으로 정렬하고 지수가 같은 부분은 합쳐줌
    sort_desc(a, n);
    sort_desc(b, m);

    //각각의 다항식들의 실제 항 개수들 저장
    int a_len = merge_terms(a, n);
    int b_len = merge_terms(b, m);

    //다항식 a, b를 출력
    print_poly(a, a_len, fout);
    print_poly(b, b_len, fout);

    // padd_array_original() 함수가 원본 배열을 파괴하기 때문에 복사본을 생성해야함! (원본보존)
    Polynomial* a_copy = malloc(a_len * sizeof(Polynomial));
    Polynomial* b_copy = malloc(b_len * sizeof(Polynomial));

    for (int i = 0; i < a_len; i++) {
        a_copy[i] = a[i];
    }
    for (int i = 0; i < b_len; i++) {
        b_copy[i] = b[i];
    }


    // 1번 : 개선 전 방식 덧셈 (배열을 앞에서 하나씩 당겨야 함)
    Polynomial* result = malloc((a_len + b_len) * sizeof(Polynomial));
    int r_len = 0;
    padd_array_original(a_copy, a_len, b_copy, b_len, result, &r_len);


    //다항식의 결과를 출력
    print_poly(result, r_len, fout);

    //동적 메모리 해제
    free(a); 
    free(b); 
    free(a_copy); 
    free(b_copy); 
    free(result);
}


// 2번 : 배열 방식 (개선 후): 다항식 A, B를 읽고 인덱스 기반으로 덧셈 수행
void func2(FILE* fin, FILE* fout) {

    int n, m;
    fscanf(fin, "%d %d", &n, &m); //a와 b의 다항식의 항의 개수를 입력에서 읽음

    Polynomial* a = malloc(n * sizeof(Polynomial)); //다항식 a를 저장할 동적배열 생성
    Polynomial* b = malloc(m * sizeof(Polynomial)); //다항식 b를 저장할 동적배열 생성

    for (int i = 0; i < n; i++) {
        fscanf(fin, "%lf %d", &a[i].coef, &a[i].expon); // a 다항식 항 입력
    }
    for (int i = 0; i < m; i++) {
        fscanf(fin, "%lf %d", &b[i].coef, &b[i].expon); // b 다항식 항 입력
    }

    // 각각의 다항식들을 내림차순으로 정렬하고 지수가 같은 부분은 합쳐줌
    sort_desc(a, n); 
    sort_desc(b, m);
    int a_len = merge_terms(a, n);
    int b_len = merge_terms(b, m);


    Polynomial* result = malloc((n + m) * sizeof(Polynomial)); //결과를 저장할 배열을 생성함
    int r_len = 0; //결과 항의 개수를 초기화

    padd_array_improved(a, a_len, b, b_len, result, &r_len); // 인덱스 기반 덧셈 수행시킴
    r_len = merge_terms(result, r_len);  // 결과에서 중복 지수가 있으면 합쳐줌

    print_poly(a, a_len, fout); // a 다항식 출력
    print_poly(b, b_len, fout); // b 다항식 출력
    print_poly(result, r_len, fout); //덧셈의 결과를 출력함

    //동적 메모리 해제
    free(a); 
    free(b); 
    free(result);
}


// 3번 : 연결 리스트 방식: 다항식 A, B를 읽어 리스트로 만들고, 연결 리스트로 덧셈 수행
void func3(FILE* fin, FILE* fout) {
    int n, m;
    fscanf(fin, "%d %d", &n, &m);//a와 b의 다항식의 항의 개수를 입력에서 읽음

    PolyPointer a = create_list(fin, n); // a 다항식을 연결 리스트로 생성함
    PolyPointer b = create_list(fin, m); // b 다항식을 연결 리스트로 생성함

    PolyPointer result = padd_list(a, b); //연결리스트의 방식으로 두 다항식을 더해줌

    Polynomial* arr_a = malloc(n * sizeof(Polynomial)); // a다항식의 리스트를 배열로 바꿔서 출력때 사용할 수 있게 함
    Polynomial* arr_b = malloc(m * sizeof(Polynomial)); // b다항식의 리스트를 배열로 바꿔서 출력때 사용할 수 있게 함

    int len_a = list_to_array(a, arr_a); // a 리스트를 배열로 복사
    int len_b = list_to_array(b, arr_b); // b 리스트를 배열로 복사


    sort_desc(arr_a, len_a); //배열 a정렬
    sort_desc(arr_b, len_b); //배열 b정렬


    int a_len = merge_terms(arr_a, len_a); //a배열에서 지수가 같은 항이 있으면 더해서 하나로 합쳐서 만들어줌
    int b_len = merge_terms(arr_b, len_b); //b배열에서 지수가 같은 항이 있으면 더해서 하나로 합쳐서 만들어줌

    Polynomial* result_arr = malloc((n + m) * sizeof(Polynomial)); //결과도 배열로 복사하기 위해서 동적할당으로 공간을 만듬
    int r_len = list_to_array(result, result_arr); // 결과 리스트를 배열로 복사

    sort_desc(result_arr, r_len); //결과 배열 정렬

    r_len = merge_terms(result_arr, r_len); //결과 배열에서 지수가 같은 항이 있으면 더해서 하나로 합쳐서 만들어줌

    print_poly(arr_a, a_len, fout); // 다항식 a출력
    print_poly(arr_b, b_len, fout); // 다항식 b출력
    print_poly(result_arr, r_len, fout); // 다항식 결과 출력
    
    //동적 메모리 해제
    free(arr_a); 
    free(arr_b); 
    free(result_arr);

    PolyPointer temp;

    while (a) { //temp라는 새로운 노드를 만들어서 a의 맨 앞부터 리스트가 끝날때까지 노드를 삭제시킴 
        temp = a; 
        a = a->link; 
        free(temp); 
    }

    while (b) { //temp라는 새로운 노드를 만들어서 b의 맨 앞부터 리스트가 끝날때까지 노드를 삭제시킴 
        temp = b; 
        b = b->link; 
        free(temp); 
    }
    while (result) { //temp라는 새로운 노드를 만들어서 result(결과리스트)의 맨 앞부터 리스트가 끝날때까지 노드를 삭제시킴 
        temp = result; 
        result = result->link; 
        free(temp); 
    }
}

int main() {
    FILE* fin = fopen("Input.txt", "r"); // 입력 파일(input.txt) 열기 (다항식 항 정보 읽기용)
    FILE* fout = fopen("output.txt", "w"); // 출력 파일 열기 (결과 및 시간 기록용)

    if (!fin || !fout) { //파일 읽기를 실패했으면
        printf("파일 열기 실패\n"); //오류 메시지 출력
        return 0;
    }

    LARGE_INTEGER freq, start, end; // window전용 성능 측정용 변수 생성
    double t1, t2, t3; //func1, func2, func3의 실행 시간 저장
    QueryPerformanceFrequency(&freq); //cpu 타이머 주기 측정

    QueryPerformanceCounter(&start); //시작 시간 측정
    func1(fin, fout);  //1번 방식 진행
    QueryPerformanceCounter(&end); //종료 시간 측정
    t1 = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart; //실행 시간 계산

    rewind(fin); //다시 실행할 때 처음부터 측정하기 위해서 파일 포인터를 처음으로 되돌림

    QueryPerformanceCounter(&start); //시작 시간 측정
    func2(fin, fout);  //2번 방식 진행
    QueryPerformanceCounter(&end); //종료 시간 측정
    t2 = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart; //실행 시간 계산

    rewind(fin); //다시 실행할 때 처음부터 측정하기 위해서 파일 포인터를 처음으로 되돌림

    QueryPerformanceCounter(&start); //시작 시간 측정
    func3(fin, fout); //3번 방식 진행
    QueryPerformanceCounter(&end); //종료 시간 측정
    t3 = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart; //실행 시간 계산

    fprintf(fout, "%.7lf\t%.7lf\t%.7lf\n", t1, t2, t3);
    fclose(fin); //파일 닫기
    fclose(fout); //츨력 파일 닫기
    return 0;
}