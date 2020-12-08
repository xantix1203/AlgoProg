#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 9
void print_tab(float tab[LEN]);
int init_wind(void);
int next_wind(float prob[LEN], int wind);
float production_eolienne(int wind,float prod[3]);
void simulation(int rangemax,float prod[3],float prob[LEN]);
float moyenne(int rangemax,float prod[3],float prob[LEN], int wind);
void simulation2(int rangemax,float prod[3],float prob[LEN]);


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
	simulation(rangemax,prod,prob);
	simulation2(rangemax,prod,prob);
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

float production_eolienne(int wind,float prod[3])
{
	return 20*prod[wind];
}

void simulation(int rangemax,float prod[3],float prob[LEN])
{
	FILE* resultat;
	int wind = init_wind();
	int i;
	for(i = 0; i < rangemax; i++)
	{
		resultat = fopen("res","a");
		fprintf(resultat, "jour %d  production:%fMW\n",i + 1,production_eolienne(wind, prod));
		fclose(resultat);
		wind = next_wind(prob, wind);
	};
}

float moyenne(int rangemax, float prod[3], float prob[LEN], int wind){
	int i;
	float moy = 0;
	for(i = 0; i < rangemax; i++)
	{
		moy = moy + production_eolienne(wind, prod);
		wind = next_wind(prob, wind);
	}
	moy = moy / rangemax;
	return moy;
}

void simulation2(int rangemax,float prod[3],float prob[LEN]){
	FILE* resultat;
	int i;
  int wind = init_wind();
	for(i = 0; i < rangemax; i++)
	{
		resultat = fopen("simu2","a");
		fprintf(resultat, "simulation %d  production moyenne:%fMW\n", i + 1, moyenne(rangemax, prod, prob, wind));
    wind = next_wind(prob, wind);
		fclose(resultat);
	};
}
