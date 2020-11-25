#include <stdio.h>



int main(){
  int prob[9];
  int prod[3];
  int rangemax;
  FILE* data;
  data = fopen("data.txt", 'r');
  fscanf(data, "%d", prob);
  fscanf(data, "%d", prod);
  fscanf(data, "%d", rangemax);
  printf("%d", prob);
  return 0;
}
