//
//  main.c
//  AlgoProg
//
//  Created by Arnaud Cotten on 25/11/2020.
//

#include <stdio.h>
#define LEN 9
void print_tab(int tab[LEN]);

int main(){
  int prob[9];
  int prod[3];
  int rangemax;
  FILE* data;
  data = fopen("data.txt", "r");
  fscanf(data, "%d", prob);
  fscanf(data, "%d", prod);
  fscanf(data, "%d", &rangemax);
  print_tab(prob);
  return 0;
}

void print_tab(int tab[LEN]){
    printf("[");
    for (int i = 0; i < (LEN - 1); i++)
        printf("%d;", tab[i]);
    printf("%d]\n", tab[LEN - 1]);
}
