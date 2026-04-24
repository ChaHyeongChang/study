#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

typedef struct {
    double coef;
    int expon;
} Polynomial;

typedef struct polyNode* PolyPointer;
typedef struct polyNode {
    double coef;
    int expon;
    PolyPointer link;
} PolyNode;

// 정렬 및 병합 함수
void sort_desc(Polynomial* p, int len) {
    for (int i = 0; i < len - 1; i++)
        for (int j = i + 1; j < len; j++)
            if (p[i].expon < p[j].expon) {
                Polynomial tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
}

int merge_terms(Polynomial* poly, int len) {
    if (len == 0) return 0;
    int idx = 0;
    for (int i = 1; i < len; i++) {
        if (poly[idx].expon == poly[i].expon)
            poly[idx].coef += poly[i].coef;
        else
            poly[++idx] = poly[i];
    }
    return idx + 1;
}

void print_poly(Polynomial* p, int len, FILE* fp) {
    for (int i = 0; i < len; i++) {
        if (p[i].coef != 0) {
            if (p[i].coef == (int)p[i].coef)
                fprintf(fp, "%d", (int)p[i].coef);
            else
                fprintf(fp, "%.2lf", p[i].coef);
            fprintf(fp, "x^%d", p[i].expon);
            if (i != len - 1) fprintf(fp, " + ");
        }
    }
    fprintf(fp, "\n");
}


// 배열 방식 개선 전
void padd_array_original(Polynomial* a, int a_len, Polynomial* b, int b_len, Polynomial* result, int* result_len) {
    *result_len = 0;
    while (a_len > 0 && b_len > 0) {
        if (a[0].expon < b[0].expon) {
            result[(*result_len)++] = b[0];
            for (int i = 0; i < b_len - 1; i++) b[i] = b[i + 1];
            b_len--;
        } else if (a[0].expon == b[0].expon) {
            double sum = a[0].coef + b[0].coef;
            if (sum != 0)
                result[(*result_len)++] = (Polynomial){sum, a[0].expon};
            for (int i = 0; i < a_len - 1; i++) a[i] = a[i + 1];
            for (int i = 0; i < b_len - 1; i++) b[i] = b[i + 1];
            a_len--; b_len--;
        } else {
            result[(*result_len)++] = a[0];
            for (int i = 0; i < a_len - 1; i++) a[i] = a[i + 1];
            a_len--;
        }
    }
    while (a_len-- > 0) result[(*result_len)++] = *(a++);
    while (b_len-- > 0) result[(*result_len)++] = *(b++);
}

// 배열 방식 개선 후
void padd_array_improved(Polynomial* a, int a_len, Polynomial* b, int b_len, Polynomial* result, int* result_len) {
    *result_len = 0;
    int i = 0, j = 0;
    while (i < a_len && j < b_len) {
        if (a[i].expon > b[j].expon)
            result[(*result_len)++] = a[i++];
        else if (a[i].expon < b[j].expon)
            result[(*result_len)++] = b[j++];
        else {
            double sum = a[i].coef + b[j].coef;
            if (sum != 0.0)
                result[(*result_len)++] = (Polynomial){sum, a[i].expon};
            i++; j++;
        }
    }
    while (i < a_len) result[(*result_len)++] = a[i++];
    while (j < b_len) result[(*result_len)++] = b[j++];
}

// 연결 리스트
void attach(PolyPointer* ptr, PolyPointer* rear, double coefficient, int exponent) {
    PolyPointer temp = (PolyPointer)malloc(sizeof(PolyNode));
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link = NULL;
    (*rear)->link = temp;
    *rear = temp;
}

PolyPointer padd_list(PolyPointer a, PolyPointer b) {
    PolyPointer front, rear, temp;
    double sum;
    rear = (PolyPointer)malloc(sizeof(PolyNode));
    front = rear;

    while (a && b) {
        if (a->expon > b->expon) {
            attach(&rear, &rear, a->coef, a->expon);
            a = a->link;
        } else if (a->expon < b->expon) {
            attach(&rear, &rear, b->coef, b->expon);
            b = b->link;
        } else {
            sum = a->coef + b->coef;
            if (sum != 0.0)
                attach(&rear, &rear, sum, a->expon);
            a = a->link;
            b = b->link;
        }
    }
    while (a) { attach(&rear, &rear, a->coef, a->expon); a = a->link; }
    while (b) { attach(&rear, &rear, b->coef, b->expon); b = b->link; }

    rear->link = NULL;
    temp = front; front = front->link; free(temp);
    return front;
}

PolyPointer create_list(FILE* fp, int n) {
    PolyPointer head = NULL, rear = NULL;
    for (int i = 0; i < n; i++) {
        PolyPointer temp = (PolyPointer)malloc(sizeof(PolyNode));
        fscanf(fp, "%lf %d", &temp->coef, &temp->expon);
        temp->link = NULL;
        if (!head) head = rear = temp;
        else { rear->link = temp; rear = temp; }
    }
    return head;
}

int list_to_array(PolyPointer p, Polynomial* arr) {
    int count = 0;
    while (p) {
        arr[count].coef = p->coef;
        arr[count].expon = p->expon;
        count++;
        p = p->link;
    }
    return count;
}

// 각각 방식
void func1(FILE* fin, FILE* fout) {
    int n, m;
    fscanf(fin, "%d %d", &n, &m);

    // A, B 다항식 입력
    Polynomial* a = malloc(n * sizeof(Polynomial));
    Polynomial* b = malloc(m * sizeof(Polynomial));
    for (int i = 0; i < n; i++) fscanf(fin, "%lf %d", &a[i].coef, &a[i].expon);
    for (int i = 0; i < m; i++) fscanf(fin, "%lf %d", &b[i].coef, &b[i].expon);

    // 정렬 및 병합
    sort_desc(a, n);
    sort_desc(b, m);
    int a_len = merge_terms(a, n);
    int b_len = merge_terms(b, m);

    // 출력 A B
    print_poly(a, a_len, fout);
    print_poly(b, b_len, fout);

    // 복사본 생성 (원본 보존)
    Polynomial* a_copy = malloc(a_len * sizeof(Polynomial));
    Polynomial* b_copy = malloc(b_len * sizeof(Polynomial));
    for (int i = 0; i < a_len; i++) a_copy[i] = a[i];
    for (int i = 0; i < b_len; i++) b_copy[i] = b[i];

    // 개선 전 방식 덧셈
    Polynomial* result = malloc((a_len + b_len) * sizeof(Polynomial));
    int r_len = 0;
    padd_array_original(a_copy, a_len, b_copy, b_len, result, &r_len);
    
    // ⛔ merge_terms 제거!
    // r_len = merge_terms(result, r_len);

    print_poly(result, r_len, fout);

    // 메모리 해제
    free(a); free(b); free(a_copy); free(b_copy); free(result);
}



void func2(FILE* fin, FILE* fout) {
    int n, m;
    fscanf(fin, "%d %d", &n, &m);
    Polynomial* a = malloc(n * sizeof(Polynomial));
    Polynomial* b = malloc(m * sizeof(Polynomial));
    for (int i = 0; i < n; i++) fscanf(fin, "%lf %d", &a[i].coef, &a[i].expon);
    for (int i = 0; i < m; i++) fscanf(fin, "%lf %d", &b[i].coef, &b[i].expon);
    sort_desc(a, n); sort_desc(b, m);
    int a_len = merge_terms(a, n), b_len = merge_terms(b, m);
    Polynomial* result = malloc((n + m) * sizeof(Polynomial)); int r_len = 0;
    padd_array_improved(a, a_len, b, b_len, result, &r_len);
    r_len = merge_terms(result, r_len);
    print_poly(a, a_len, fout);
    print_poly(b, b_len, fout);
    print_poly(result, r_len, fout);
    free(a); free(b); free(result);
}

void func3(FILE* fin, FILE* fout) {
    int n, m;
    fscanf(fin, "%d %d", &n, &m);
    PolyPointer a = create_list(fin, n);
    PolyPointer b = create_list(fin, m);
    PolyPointer result = padd_list(a, b);
    Polynomial* arr_a = malloc(n * sizeof(Polynomial));
    Polynomial* arr_b = malloc(m * sizeof(Polynomial));
    int len_a = list_to_array(a, arr_a);
    int len_b = list_to_array(b, arr_b);
    sort_desc(arr_a, len_a); sort_desc(arr_b, len_b);
    int a_len = merge_terms(arr_a, len_a);
    int b_len = merge_terms(arr_b, len_b);
    Polynomial* result_arr = malloc((n + m) * sizeof(Polynomial));
    int r_len = list_to_array(result, result_arr);
    sort_desc(result_arr, r_len);
    r_len = merge_terms(result_arr, r_len);
    print_poly(arr_a, a_len, fout);
    print_poly(arr_b, b_len, fout);
    print_poly(result_arr, r_len, fout);
    free(arr_a); free(arr_b); free(result_arr);
    PolyPointer temp;
    while (a) { temp = a; a = a->link; free(temp); }
    while (b) { temp = b; b = b->link; free(temp); }
    while (result) { temp = result; result = result->link; free(temp); }
}

int main() {
    FILE* fin = fopen("Input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    if (!fin || !fout) {
        printf("파일 열기 실패\n");
        return 0;
    }

    LARGE_INTEGER freq, start, end;
    double t1, t2, t3;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&start); func1(fin, fout); QueryPerformanceCounter(&end);
    t1 = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    rewind(fin);

    QueryPerformanceCounter(&start); func2(fin, fout); QueryPerformanceCounter(&end);
    t2 = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    rewind(fin);

    QueryPerformanceCounter(&start); func3(fin, fout); QueryPerformanceCounter(&end);
    t3 = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    fprintf(fout, "%.7lf\t%.7lf\t%.7lf\n", t1, t2, t3);
    fclose(fin); fclose(fout);
    return 0;
}