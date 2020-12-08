#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 9
void print_tab(float tab[LEN]);
int init_wind(void);
int next_wind(float prob[LEN], int wind);

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
    print_tab(prob);
    printf("rangemax %d\n", rangemax);
    int wind = init_wind();
    printf("wind %d\n", wind);
    wind = next_wind(prob, wind);
    printf("next_wind %d\n", wind);
  return 0;
  }
  return 0;
}

void print_tab(float tab[LEN]){
    printf("{");
    for (int i = 0; i < (LEN - 1); i++)
        printf("%f,", tab[i]);
    printf("%f}\n", tab[LEN - 1]);
}

int init_wind(){
  srand(time(NULL));
  int wind = rand() % 3;
  return wind;
}

int next_wind(float prob[LEN], int wind){
  float random = (float)rand()/(float)(RAND_MAX);
  printf("random %f\n", random);
  if (random <= prob[3 * wind])
    return 0;
  if (random <= prob[3 * wind] + prob[3 * wind + 1])
    return 1;
  return 2;
}
