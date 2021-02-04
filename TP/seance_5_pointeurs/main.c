//
//  main.c
//  AlgoProg
//
//  Created by COTTEN on 30/09/2020.
//

#include <stdio.h>
#include <stdlib.h>
#define LEN 5


void init0(int *p, int *q, float *r);
int eucldiv(int *a, int *b, int *r);
void swap(int *x, int *y);
void get(float *x);
void reverse(int tab[],int len);
int* concatenation(int *tab1, int *tab2, int len1, int len2);



int main(int argc, const char * argv[]) {
    int x = 1;
    int y = 2;
    float z = 3;
    int a = 4;
    int b = 5;
    int r = 0;
//    init0(&x, &y, &z);
    printf("x = %d, y = %d, z = %f\n", x, y , z);
    printf("%d div %d = %d, %d\n",a, b, eucldiv(&a, &b, &r), r);
    printf("x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);
//    get(&z);
    int tab1[LEN] = {1, 2, 3, 4, 5};
    reverse(tab1, LEN);
    printf("%d\n", tab1[0]);
    int tab2[LEN] = {6, 7, 8, 9, 10};
    int* tabc = concatenation(tab1, tab2, LEN, LEN);
    printf("%d, %d\n", tabc[1], tabc[9]);
    
    return 0;
}

void init0(int *p, int *q, float *r){
    *p = 0;
    *q = 0;
    *r = 0;
}

int eucldiv(int *a, int *b, int *r){
    *r = *a % *b;
    return *a / *b;
}

void swap(int *x, int *y){
    int buffer = *x;
    *x = *y;
    *y = buffer;
}

void get(float *x){
    printf("enter real number: ");
    scanf("%f", x);
}

void reverse(int *tab,int len){
    int* tab2 = (int*) malloc(len * sizeof(int));
    for(int i = 0; i < len; i++)
        tab2[i] = tab[len - i - 1];
    for(int i = 0; i < len; i++)
        tab[i] = tab2[i];
}

int* concatenation(int *tab1, int *tab2, int len1, int len2){
    int *ptab = ( int*) malloc((len1 + len2) * sizeof(int));
    for(int i = 0; i < len1; i++)
        *(ptab + i) = tab1[i];
    for(int i = 0; i < len2; i++)
        *(ptab + i + len1) = tab2[i];
    return ptab;
}
