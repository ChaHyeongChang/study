#include <stdio.h>
#include <stdlib.h>
#include <windows.h>    // Windows 타이머 사용 (main에서 사용)

// ======================= 버전 1: 동적 배열 방식 =======================
typedef struct {
    int degree;      // 최고 차수
    int capacity;    // 배열 크기
    float *coef;     // 계수 배열 (인덱스=차수)
} polynomial;

// 새로운 다항식 생성 (모든 항은 0으로 초기화)
polynomial createPolynomial(int capacity) {
    polynomial p;
    p.degree = 0;
    p.capacity = capacity;
    p.coef = (float*)calloc(capacity, sizeof(float));
    return p;
}

void freePolynomial(polynomial *p) {
    free(p->coef);
    p->coef = NULL;
    p->degree = 0;
    p->capacity = 0;
}

void attachTerm(polynomial *p, float coef, int exp) {
    // 재할당이 필요하면 (인덱스 범위를 초과하면)
    if(exp >= p->capacity) {
        int newCapacity = (exp + 1) * 2;
        p->coef = (float*)realloc(p->coef, newCapacity * sizeof(float));
        // 새로 할당된 부분은 0으로 초기화
        for (int i = p->capacity; i < newCapacity; i++)
            p->coef[i] = 0;
        p->capacity = newCapacity;
    }
    p->coef[exp] += coef;
    if(exp > p->degree && p->coef[exp] != 0)
        p->degree = exp;
}

polynomial polyAdd(const polynomial *a, const polynomial *b) {
    // 두 다항식의 최고 차수 중 큰 값으로 결과 다항식 생성
    int maxdeg = (a->degree > b->degree ? a->degree : b->degree);
    polynomial result = createPolynomial(maxdeg + 1);
    result.degree = maxdeg;
    for (int i = 0; i <= maxdeg; i++) {
        float ca = (i <= a->degree ? a->coef[i] : 0);
        float cb = (i <= b->degree ? b->coef[i] : 0);
        result.coef[i] = ca + cb;
    }
    // 최고 차수 값이 0인 항이 있을 경우 조정
    while(result.degree > 0 && result.coef[result.degree] == 0)
        result.degree--;
    return result;
}

void printPoly(FILE *f, const polynomial *p) {
    int first = 1;
    for (int i = p->degree; i >= 0; i--) {
        if(p->coef[i] != 0) {
            if(!first)
                fprintf(f, " + ");
            fprintf(f, "%.0fx^%d", p->coef[i], i);
            first = 0;
        }
    }
    if(first)
        fprintf(f, "0");
    fprintf(f, "\n");
}

// ======================= 버전 2: 희소 다항식 (동적 배열 terms) =======================
typedef struct {
    float coef;  // 계수
    int exp;     // 차수
} term;

term *terms = NULL;
int termCount = 0, termCapacity = 0;

void initTerms(int capacity) {
    termCapacity = capacity;
    termCount = 0;
    terms = (term*)calloc(termCapacity, sizeof(term));
}

void freeTerms() {
    free(terms);
    terms = NULL;
    termCount = 0;
    termCapacity = 0;
}

void attachTerm2(float coef, int exp) {
    if(termCount >= termCapacity) {
        termCapacity = (termCapacity == 0 ? 4 : termCapacity * 2);
        terms = (term*)realloc(terms, termCapacity * sizeof(term));
    }
    terms[termCount].coef = coef;
    terms[termCount].exp = exp;
    termCount++;
}

// 간단히 내림차순 정렬 (버블 정렬, 항의 개수가 많지 않다고 가정)
void sortTerms(int start, int end) {
    for (int i = start; i <= end; i++) {
        for (int j = i + 1; j <= end; j++) {
            if(terms[i].exp < terms[j].exp) {
                term temp = terms[i];
                terms[i] = terms[j];
                terms[j] = temp;
            }
        }
    }
}

// 두 다항식(항 구간 [startA, endA] 와 [startB, endB])을 병합
// 결과 항은 terms 배열의 뒤쪽에 추가됨.
void addTerms(int startA, int endA, int startB, int endB, int *startD, int *endD) {
    *startD = termCount;  // 결과 다항식 시작 인덱스
    int i = startA, j = startB;
    while(i <= endA && j <= endB) {
        if(terms[i].exp == terms[j].exp) {
            float sum = terms[i].coef + terms[j].coef;
            if(sum != 0)
                attachTerm2(sum, terms[i].exp);
            i++; j++;
        } else if(terms[i].exp > terms[j].exp) {
            attachTerm2(terms[i].coef, terms[i].exp);
            i++;
        } else {
            attachTerm2(terms[j].coef, terms[j].exp);
            j++;
        }
    }
    while(i <= endA) {
        attachTerm2(terms[i].coef, terms[i].exp);
        i++;
    }
    while(j <= endB) {
        attachTerm2(terms[j].coef, terms[j].exp);
        j++;
    }
    *endD = termCount - 1;
}

void printTerms(FILE *f, int start, int end) {
    int first = 1;
    for (int i = start; i <= end; i++) {
        if(terms[i].coef != 0) {
            if(!first)
                fprintf(f, " + ");
            fprintf(f, "%.0fx^%d", terms[i].coef, terms[i].exp);
            first = 0;
        }
    }
    if(first)
        fprintf(f, "0");
    fprintf(f, "\n");
}

// ======================= 버전 3: 링크드 리스트 방식 =======================
typedef struct polyNode {
    float coef;
    int exp;
    struct polyNode *next;
} polyNode;

polyNode* createNode(float coef, int exp) {
    polyNode* node = (polyNode*)malloc(sizeof(polyNode));
    node->coef = coef;
    node->exp = exp;
    node->next = NULL;
    return node;
}

// a, b는 내림차순(차수가 큰 순)으로 정렬된 다항식이라 가정
polyNode* addPolyList(polyNode* a, polyNode* b) {
    polyNode dummy;
    dummy.next = NULL;
    polyNode *tail = &dummy;
    while(a && b) {
        if(a->exp == b->exp) {
            float sum = a->coef + b->coef;
            if(sum != 0) {
                tail->next = createNode(sum, a->exp);
                tail = tail->next;
            }
            a = a->next; b = b->next;
        } else if(a->exp > b->exp) {
            tail->next = createNode(a->coef, a->exp);
            tail = tail->next;
            a = a->next;
        } else {
            tail->next = createNode(b->coef, b->exp);
            tail = tail->next;
            b = b->next;
        }
    }
    while(a) {
        tail->next = createNode(a->coef, a->exp);
        tail = tail->next;
        a = a->next;
    }
    while(b) {
        tail->next = createNode(b->coef, b->exp);
        tail = tail->next;
        b = b->next;
    }
    return dummy.next;
}

void printPolyList(FILE *f, polyNode* head) {
    int first = 1;
    while(head) {
        if(head->coef != 0) {
            if(!first)
                fprintf(f, " + ");
            fprintf(f, "%.0fx^%d", head->coef, head->exp);
            first = 0;
        }
        head = head->next;
    }
    if(first)
        fprintf(f, "0");
    fprintf(f, "\n");
}

void freePolyList(polyNode* head) {
    while(head) {
        polyNode* temp = head;
        head = head->next;
        free(temp);
    }
}

// ======================= 함수들 (func1, func2, func3) =======================
/*  
   func1: 버전 1 (동적 배열 방식)
   입력: 첫 줄에 각각 항의 개수 x1, x2,
         이어서 x1개, x2개 항이 "계수 차수" 형식으로 주어짐
*/
void func1(FILE *fin, FILE *fout) {
    int x1, x2;
    fscanf(fin, "%d %d", &x1, &x2);
    // 예상 입력에 맞춰 초기 용량을 지정 (최소 4)
    polynomial a = createPolynomial(x1 * 2 < 4 ? 4 : x1 * 2);
    polynomial b = createPolynomial(x2 * 2 < 4 ? 4 : x2 * 2);
    float coef;
    int exp;
    for (int i = 0; i < x1; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        attachTerm(&a, coef, exp);
    }
    for (int i = 0; i < x2; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        attachTerm(&b, coef, exp);
    }
    polynomial sum = polyAdd(&a, &b);
    printPoly(fout, &a);
    printPoly(fout, &b);
    printPoly(fout, &sum);
    freePolynomial(&a);
    freePolynomial(&b);
    freePolynomial(&sum);
}

/*  
   func2: 버전 2 (희소 다항식, 전역 terms 배열)
   입력: 첫 줄에 각각 항의 개수 x1, x2,
         이어서 x1개, x2개 항이 "계수 차수" 형식으로 주어짐  
   — 단, 입력 후 sortTerms()를 호출하여 내림차순 정렬함.
*/
void func2(FILE *fin, FILE *fout) {
    int x1, x2;
    fscanf(fin, "%d %d", &x1, &x2);
    // 충분한 초기 크기로 할당
    initTerms((x1 + x2) * 2 < 4 ? 4 : (x1 + x2) * 2);
    int startA = termCount;
    float coef;
    int exp;
    for (int i = 0; i < x1; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        attachTerm2(coef, exp);
    }
    int endA = termCount - 1;
    int startB = termCount;
    for (int i = 0; i < x2; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        attachTerm2(coef, exp);
    }
    int endB = termCount - 1;
    // 정렬: 두 구간 모두 내림차순 정렬
    sortTerms(startA, endA);
    sortTerms(startB, endB);
    int startD, endD;
    addTerms(startA, endA, startB, endB, &startD, &endD);
    printTerms(fout, startA, endA);
    printTerms(fout, startB, endB);
    printTerms(fout, startD, endD);
    freeTerms();
}

/*  
   func3: 버전 3 (링크드 리스트 방식)
   입력: 첫 줄에 각각 항의 개수 x1, x2,
         이어서 x1개, x2개 항이 "계수 차수" 형식으로 주어짐
   — 입력한 후 내림차순 정렬한 상태로 링크드 리스트를 구성함.
*/
polyNode* readPolyList(FILE *fin, int count) {
    polyNode *head = NULL, *tail = NULL;
    float coef;
    int exp;
    for (int i = 0; i < count; i++) {
        fscanf(fin, "%f %d", &coef, &exp);
        polyNode* node = createNode(coef, exp);
        // 단순 입력 후, 나중에 정렬할 예정이므로 삽입은 순서에 상관없이
        if(!head)
            head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

// 간단한 버블 정렬(내림차순 정렬)
polyNode* sortPolyList(polyNode* head) {
    if(!head) return head;
    for(polyNode* i = head; i; i = i->next) {
        for(polyNode* j = i->next; j; j = j->next) {
            if(i->exp < j->exp) {
                float tempCoef = i->coef;
                int tempExp = i->exp;
                i->coef = j->coef;
                i->exp = j->exp;
                j->coef = tempCoef;
                j->exp = tempExp;
            }
        }
    }
    return head;
}

void func3(FILE *fin, FILE *fout) {
    int x1, x2;
    fscanf(fin, "%d %d", &x1, &x2);
    polyNode *a = readPolyList(fin, x1);
    polyNode *b = readPolyList(fin, x2);
    // 정렬 (내림차순)
    a = sortPolyList(a);
    b = sortPolyList(b);
    polyNode *sum = addPolyList(a, b);
    printPolyList(fout, a);
    printPolyList(fout, b);
    printPolyList(fout, sum);
    freePolyList(a);
    freePolyList(b);
    freePolyList(sum);
}

// ======================= main 함수 (Windows 타이머 사용) =======================
int main() {
    LARGE_INTEGER freq, start, end;
    double t1, t2, t3;
    if(!QueryPerformanceFrequency(&freq)){
        fprintf(stderr, "고해상도 타이머를 사용할 수 없습니다.\n");
        return 1;
    }
    FILE *fin = fopen("Input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if(!fin || !fout) {
        printf("파일 열기 실패\n");
        return 1;
    }
    
    QueryPerformanceCounter(&start);
    func1(fin, fout);
    QueryPerformanceCounter(&end);
    t1 = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    
    rewind(fin);
    QueryPerformanceCounter(&start);
    func2(fin, fout);
    QueryPerformanceCounter(&end);
    t2 = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    
    rewind(fin);
    QueryPerformanceCounter(&start);
    func3(fin, fout);
    QueryPerformanceCounter(&end);
    t3 = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    
    fprintf(fout, "\nTime (ms): %.4lf\t%.4lf\t%.4lf\n", t1, t2, t3);
    
    fclose(fin);
    fclose(fout);
    return 0;
}