//
//  main.c
//  Algo prog
//
//  Created by COTTEN on 21/09/2020.
//  Copyright © 2020 Cotten. All rights reserved.
//

#include <stdio.h>
#define LEN 9


void print_tab(int tab[LEN]);
void tri_fusion(int tab[LEN]);
void tri_fusion_recur(int tab[LEN], int i, int j);
void fusion(int tab[LEN], int f, int m, int l);

int main(int argc, const char * argv[]) {
    int tab[LEN] = {0, 1, 2, 8, 4, 6, 7, 9, 5};
    tri_fusion(tab);
    print_tab(tab);
    return 0;
}

void print_tab(int tab[LEN]){
    printf("[");
    for (int i = 0; i < (LEN - 1); i++)
        printf("%d;", tab[i]);
    printf("%d]\n", tab[LEN - 1]);
}

void tri_fusion(int tab[LEN]){
    tri_fusion_recur(tab, 0, LEN - 1);
}

void tri_fusion_recur(int tab[LEN], int i, int j){
    int n = j - i + 1;
    if (n > 1) {
        tri_fusion_recur(tab, i, i + (n / 2) - 1);
        tri_fusion_recur(tab, i + (n / 2), j);
        fusion(tab, i, i + (n / 2) - 1, j);
    }
}

void fusion(int tab[LEN], int f, int m, int l){
    int tab2[LEN];
    for (int i = f; i <= m; i++)
        tab2[i] = tab[i];
    for (int i = m + 1; i <= l; i++)
        tab2[i] = tab[l + m - i + 1];
    int i = f;
    int j = l;
    for (int k = f ; k <= l; k++){
        if (tab2[i] < tab2[j]){
            tab[k] = tab2[i];
            i++;
        }
        else{
            tab[k] = tab2[j];
            j--;
        }
    }
}
