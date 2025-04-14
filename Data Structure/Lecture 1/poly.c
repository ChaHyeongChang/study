
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> //#include<time.h> 사용시 실행시간이0.0000000으로 나와서 사용함.
#include <time.h>
// ======================= 배열 기반 (공용) ======================= //

// 다항식 항(term) 구조체 (계수: float, 지수: int)
typedef struct {
    float coef;
    int exp;
} Term;

// 다항식 구조체 (배열 기반)
typedef struct {
    Term* terms; //Term 구조체 배열을 가리키는 포인터(다항식의 항 목록들)
    int size; //현재 저장된 항의 개수
    int capacity; //할당된 최대 항의 개수
} polynomial;

// 초기 다항식 생성 (capacity 만큼 메모리 할당하고, size는 0)
polynomial Zero(int capacity) {
    polynomial poly; // polynomail 구조체 변수 poly선언
    poly.capacity = capacity; //항 배열의 최대 크기를 설정함
    poly.size = 0; //현재 항의 개수를 0으로 초기화해줌
    poly.terms = (Term*)malloc(capacity * sizeof(Term)); //capacity의 크기만큼 동적 배열 할당해줌
    return poly; //초기화된 다항식을 반환함
}

// 다항식에 항 추가 (capacity 부족시 재할당 -> capacity를 2배로 늘려서)
polynomial attach1(polynomial poly, float coef, int exp) {
    if (poly.size >= poly.capacity) { //현재 크기가 capacity넘으면
        poly.capacity *= 2; //capacity를 두배로 늘림.
        poly.terms = (Term*)realloc(poly.terms, poly.capacity * sizeof(Term)); //배열 크기를 재할당 해줌(원래 있던 데이터는 유지시켜주고)
    }
    poly.terms[poly.size].coef = coef; //새 항의 계수를 저장
    poly.terms[poly.size].exp = exp; //새 항의 지수를 저장
    poly.size++; // 항의 개수를 증가시킴
    return poly; // 변경된 다항식을 반환함.
}

// 버블 정렬을 이용하여 다항식 항을 내림차순(지수가 큰 순) 정렬
void sortPolynomial(polynomial *poly) {
    for (int i = 0; i < poly->size - 1; i++) {
        for (int j = 0; j < poly->size - i - 1; j++) {
            if (poly->terms[j].exp < poly->terms[j+1].exp) {
                Term tmp = poly->terms[j];
                poly->terms[j] = poly->terms[j+1];
                poly->terms[j+1] = tmp;
            }
        }
    }
}

// 정렬된 다항식에서 같은 지수를 갖는 항들을 합침
void mergeTerms(polynomial *poly) {
    if (poly->size == 0)
        return;
    int index = 0;
    for (int i = 1; i < poly->size; i++) {
        if (poly->terms[index].exp == poly->terms[i].exp)
            poly->terms[index].coef += poly->terms[i].coef;
        else {
            index++;
            poly->terms[index] = poly->terms[i];
        }
    }
    poly->size = index + 1;
}

// -------------------- 개선 후 배열 방식 --------------------
// 기존 구현으로, 먼저 정렬 및 병합한 후 두 배열을 인덱스로 순회하면서 덧셈
polynomial Padd(polynomial a, polynomial b) {
    sortPolynomial(&a);
    mergeTerms(&a);
    sortPolynomial(&b);
    mergeTerms(&b);

    int i = 0, j = 0;
    polynomial result = Zero(a.size + b.size);
    while (i < a.size && j < b.size) {
        if (a.terms[i].exp > b.terms[j].exp) {
            result = attach1(result, a.terms[i].coef, a.terms[i].exp);
            i++;
        } else if (a.terms[i].exp < b.terms[j].exp) {
            result = attach1(result, b.terms[j].coef, b.terms[j].exp);
            j++;
        } else { // 같은 지수이면 계수 합산
            float sum = a.terms[i].coef + b.terms[j].coef;
            if (sum != 0)
                result = attach1(result, sum, a.terms[i].exp);
            i++;
            j++;
        }
    }
    while (i < a.size) {
        result = attach1(result, a.terms[i].coef, a.terms[i].exp);
        i++;
    }
    while (j < b.size) {
        result = attach1(result, b.terms[j].coef, b.terms[j].exp);
        j++;
    }
    return result;
}

// -------------------- 개선 전 배열 방식 --------------------
// 원래 코드에서는 배열에서 항을 하나씩 "제거(Remove)"하며 결과 배열에 첨가하는 방식으로 덧셈을 수행함.
// 입력 배열은 모두 정렬되어 있다고 가정(내림차순).
// 아래의 헬퍼 함수들을 정의합니다.
int LeadExp(polynomial *poly) {
    return (poly->size > 0) ? poly->terms[0].exp : -1;
}
void RemoveFirst(polynomial *poly) {
    if (poly->size == 0)
        return;
    for (int i = 0; i < poly->size - 1; i++)
        poly->terms[i] = poly->terms[i+1];
    poly->size--;
}

// padd_array_original : 원본 배열에서 첫 항을 제거하는 방식으로 덧셈 수행
polynomial padd_array_original(polynomial a, polynomial b) {
    // a, b가 정렬되어 있어야 함.
    sortPolynomial(&a);
    sortPolynomial(&b);
    polynomial result = Zero(a.size + b.size);
    while(a.size > 0 && b.size > 0) {
        int expA = LeadExp(&a);
        int expB = LeadExp(&b);
        if(expA < expB) {
            result = attach1(result, b.terms[0].coef, b.terms[0].exp);
            RemoveFirst(&b);
        } else if(expA == expB) {
            float sum = a.terms[0].coef + b.terms[0].coef;
            if(sum != 0)
                result = attach1(result, sum, expA);
            RemoveFirst(&a);
            RemoveFirst(&b);
        } else { // expA > expB
            result = attach1(result, a.terms[0].coef, a.terms[0].exp);
            RemoveFirst(&a);
        }
    }
    while(a.size > 0) {
        result = attach1(result, a.terms[0].coef, a.terms[0].exp);
        RemoveFirst(&a);
    }
    while(b.size > 0) {
        result = attach1(result, b.terms[0].coef, b.terms[0].exp);
        RemoveFirst(&b);
    }
    return result;
}

// 다항식을 출력 (항이 없으면 0 출력)
void PrintPolynomial(FILE *fp, polynomial poly) {
    if (poly.size == 0) {
        fprintf(fp, "0");
    }
    for (int i = 0; i < poly.size; i++) {
        // 첫 항이 아니라면 양수인 경우 앞에 " + "를 붙인다.
        if (i > 0 && poly.terms[i].coef >= 0)
            fprintf(fp, " + ");
        
        // 계수가 정수값인지 검사. (예: 2.00이면 2와 같음음)
        if (poly.terms[i].coef == (int)poly.terms[i].coef)
            // 음수이든 양수이든 정수형 출력
            fprintf(fp, "%dx^%d", (int)poly.terms[i].coef, poly.terms[i].exp);
        else
            // 소수점 이하 값이 있으면 일반 float 출력
            fprintf(fp, "%.2fx^%d", poly.terms[i].coef, poly.terms[i].exp);
    }
    fprintf(fp, "\n");
}


// 다항식 메모리 해제
void FreePolynomial(polynomial *poly) {
    if(poly->terms != NULL) {
        free(poly->terms);
        poly->terms = NULL;
    }
    poly->size = 0;
    poly->capacity = 0;
}

// ======================= 연결리스트 기반 다항식 =======================

typedef struct PolyNode {
    float coef;
    int exp;
    struct PolyNode* link;
} PolyNode;

// 연결리스트에 내림차순(지수가 큰 순)으로 삽입; 같은 지수면 계수를 합산
PolyNode* insertSorted(PolyNode* head, float coef, int exp) {
    PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->link = NULL;
    
    if (head == NULL || head->exp < exp) {
        newNode->link = head;
        return newNode;
    } else if (head->exp == exp) {
        head->coef += coef;
        free(newNode);
        return head;
    } else {
        PolyNode* p = head;
        while (p->link != NULL && p->link->exp >= exp) {
            if (p->link->exp == exp) {
                p->link->coef += coef;
                free(newNode);
                return head;
            }
            p = p->link;
        }
        newNode->link = p->link;
        p->link = newNode;
        return head;
    }
}

// 파일에서 n개의 항을 읽어 연결리스트 생성 (내림차순 정렬 상태)
PolyNode* createLinkedList(FILE* fin, int n) {
    PolyNode* head = NULL;
    float coef;
    int exp;
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        head = insertSorted(head, coef, exp);
    }
    return head;
}

// 연결리스트 다항식 출력
void printLinkedList(FILE *fp, PolyNode* head) {
    if (head == NULL) {
        fprintf(fp, "0\n");
        return;
    }
    int first = 1;
    for (PolyNode* p = head; p != NULL; p = p->link) {
        if (!first && p->coef >= 0)
            fprintf(fp, " + ");
        
        // 계수가 정수로 나타낼 수 있으면 정수로 출력, 아니면 소수점 둘째 자리까지 출력
        if (p->coef == (int)p->coef)
            fprintf(fp, "%dx^%d", (int)p->coef, p->exp);
        else
            fprintf(fp, "%.2fx^%d", p->coef, p->exp);
        
        first = 0;
    }
    fprintf(fp, "\n");
}


// 연결리스트 메모리 해제
void freeLinkedList(PolyNode* head) {
    while (head != NULL) {
        PolyNode* temp = head;
        head = head->link;
        free(temp);
    }
}

// 연결리스트 기반 다항식 덧셈 (두 리스트는 내림차순 정렬 상태라고 가정)
PolyNode* paddLinkedList(PolyNode* a, PolyNode* b) {
    PolyNode dummy;
    dummy.link = NULL;
    PolyNode* tail = &dummy;
    while (a != NULL && b != NULL) {
        if (a->exp > b->exp) {
            PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
            newNode->coef = a->coef;
            newNode->exp = a->exp;
            newNode->link = NULL;
            tail->link = newNode;
            tail = newNode;
            a = a->link;
        } else if (a->exp < b->exp) {
            PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
            newNode->coef = b->coef;
            newNode->exp = b->exp;
            newNode->link = NULL;
            tail->link = newNode;
            tail = newNode;
            b = b->link;
        } else {
            float sum = a->coef + b->coef;
            if (sum != 0) {
                PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
                newNode->coef = sum;
                newNode->exp = a->exp;
                newNode->link = NULL;
                tail->link = newNode;
                tail = newNode;
            }
            a = a->link;
            b = b->link;
        }
    }
    while (a != NULL) {
        PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
        newNode->coef = a->coef;
        newNode->exp = a->exp;
        newNode->link = NULL;
        tail->link = newNode;
        tail = newNode;
        a = a->link;
    }
    while (b != NULL) {
        PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
        newNode->coef = b->coef;
        newNode->exp = b->exp;
        newNode->link = NULL;
        tail->link = newNode;
        tail = newNode;
        b = b->link;
    }
    return dummy.link;
}

// ======================= 새로운 함수들 =======================

// func1: 배열 기반 "개선 전" 방식  
// 입력받은 다항식 a, b를 복사하여 padd_array_original()을 수행한 후, 
// 출력 전에 원본 다항식 a와 b에도 정렬 및 병합을 진행하여 정렬된 상태로 출력합니다.
void func1(FILE *fin, FILE *fout) {
    int x1, x2;
    float coef;
    int exp;
    fscanf(fin, "%d %d", &x1, &x2);
    polynomial a = Zero(10), b = Zero(10);
    for (int i = 0; i < x1; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        a = attach1(a, coef, exp);
    }
    for (int i = 0; i < x2; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        b = attach1(b, coef, exp);
    }
    // 정렬되지 않은 a, b와는 별개로, padd_array_original()에 사용할 복사본을 생성
    polynomial A = Zero(a.size);
    polynomial B = Zero(b.size);
    for (int i = 0; i < a.size; i++) {
        A = attach1(A, a.terms[i].coef, a.terms[i].exp);
    }
    for (int i = 0; i < b.size; i++) {
        B = attach1(B, b.terms[i].coef, b.terms[i].exp);
    }
    // padd_array_original 내부에서 정렬되므로 복사본 A, B는 그대로 사용함.
    polynomial sum = padd_array_original(A, B);
    
    // 출력 전에 a, b에도 정렬 및 병합을 적용하여 정렬된 형태로 출력
    sortPolynomial(&a);
    mergeTerms(&a);
    sortPolynomial(&b);
    mergeTerms(&b);
    PrintPolynomial(fout, a);
    PrintPolynomial(fout, b);
    PrintPolynomial(fout, sum);
    
    FreePolynomial(&a);
    FreePolynomial(&b);
    FreePolynomial(&A);
    FreePolynomial(&B);
    FreePolynomial(&sum);
}

// func2: 배열 기반 "개선 후" 방식 (Padd 함수 사용)
// Padd() 내부에서 정렬 및 병합을 수행하지만, 원본 a와 b는 정렬되어 있지 않을 수 있으므로 출력 전에 별도로 정렬합니다.
void func2(FILE *fin, FILE *fout) {
    int x1, x2;
    float coef;
    int exp;
    fscanf(fin, "%d %d", &x1, &x2);
    polynomial a = Zero(10), b = Zero(10);
    for (int i = 0; i < x1; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        a = attach1(a, coef, exp);
    }
    for (int i = 0; i < x2; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        b = attach1(b, coef, exp);
    }
    // 개선 후 방식에서 Padd() 내부에서 a와 b가 정렬되어 덧셈 결과 sum이 만들어짐
    polynomial sum = Padd(a, b);
    
    // 하지만 출력되는 a와 b는 원본이므로 정렬 및 병합해서 출력
    sortPolynomial(&a);
    mergeTerms(&a);
    sortPolynomial(&b);
    mergeTerms(&b);
    PrintPolynomial(fout, a);
    PrintPolynomial(fout, b);
    PrintPolynomial(fout, sum);
    
    FreePolynomial(&a);
    FreePolynomial(&b);
    FreePolynomial(&sum);
}

// func3: 연결리스트 기반 방식
void func3(FILE *fin, FILE *fout) {
    int x1, x2;
    fscanf(fin, "%d %d", &x1, &x2);
    PolyNode* listA = createLinkedList(fin, x1);
    PolyNode* listB = createLinkedList(fin, x2);
    PolyNode* sumList = paddLinkedList(listA, listB);
    
    printLinkedList(fout, listA);
    printLinkedList(fout, listB);
    printLinkedList(fout, sumList);
    
    freeLinkedList(listA);
    freeLinkedList(listB);
    freeLinkedList(sumList);
}

// ======================= main() =======================

int main() {
    FILE* fin = fopen("Input.txt", "r");
    FILE* fout = fopen("output.txt", "w");

    if (!fin || !fout) {
        printf("파일 열기 실패\n");
        return 0;
    }

    LARGE_INTEGER frequency, start, end;
    double s1, s2, s3;
    QueryPerformanceFrequency(&frequency);

    // func1: 배열 기반 "개선 전" 방식 (파일 읽기부터 실행 포함)
    QueryPerformanceCounter(&start);
    func1(fin, fout);
    QueryPerformanceCounter(&end);
    s1 = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    rewind(fin);

    // func2: 배열 기반 "개선 후" 방식 (파일 읽기부터 실행 포함)
    QueryPerformanceCounter(&start);
    func2(fin, fout);
    QueryPerformanceCounter(&end);
    s2 = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    rewind(fin);

    // func3: 연결리스트 방식 (파일 읽기부터 실행 포함)
    QueryPerformanceCounter(&start);
    func3(fin, fout);
    QueryPerformanceCounter(&end);
    s3 = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    fprintf(fout, "%.7lf\t%.7lf\t%.7lf\n", s1, s2, s3);

    fclose(fin);
    fclose(fout);
    return 0;
}


/*
int main() {
    FILE* fin = fopen("Input.txt", "r");
    FILE* fout = fopen("output.txt", "w");

    if (!fin || !fout) {
        printf("파일 열기 실패\n");
        return 0;
    }

    clock_t start, end;
    double s1, s2, s3; // 각각 func1, func2, func3의 실행 시간 (초 단위)

    // func1: 배열 기반 "개선 전" 방식 (파일 읽기부터 실행 포함)
    start = clock();
    func1(fin, fout);
    end = clock();
    s1 = ((double)(end - start)) * 1000000 / CLOCKS_PER_SEC;
    rewind(fin);

    // func2: 배열 기반 "개선 후" 방식 (파일 읽기부터 실행 포함)
    start = clock();
    func2(fin, fout);
    end = clock();
    s2 = ((double)(end - start)) * 1000000 / CLOCKS_PER_SEC;
    rewind(fin);

    // func3: 연결리스트 방식 (파일 읽기부터 실행 포함)
    start = clock();
    func3(fin, fout);
    end = clock();
    s3 = ((double)(end - start)) * 1000000 / CLOCKS_PER_SEC;

    fprintf(fout, "%.7lf\t%.7lf\t%.7lf\n", s1, s2, s3);

    fclose(fin);
    fclose(fout);
    return 0;
}

*/