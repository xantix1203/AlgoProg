#include <stdio.h>
#define LEN 9
void print_tab(float tab[LEN]);

int main(){
  float prob[9];
  float prod[3];
  int rangemax;
  FILE* data;
  data = fopen("data.txt", "r");
  if (data != NULL) {
    for (int i = 0; i < 9; i++)
      fscanf(data, "%f", &prob[i]);
    for (int i = 0; i < 3; i++)
      fscanf(data, "%f", &prod[i]);
    fscanf(data, "%d", &rangemax);
    print_tab(prod);
    print_tab(prob);
    printf("%d", rangemax);
  return 0;
  }
}

void print_tab(float tab[LEN]){
    printf("{");
    for (int i = 0; i < (LEN - 1); i++)
        printf("%f,", tab[i]);
    printf("%f}\n", tab[LEN - 1]);
}
