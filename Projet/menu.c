#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 9
int init_wind(void);
int next_wind(float prob[LEN], int wind);
float production_eolienne(int wind, float prod[3]);
float moyenne(int nombres, float prod[3], float prob[LEN], int wind);
void simulation(int duree, int nombres, char titre[50], float prod[3], float prob[LEN]);
void changementproba(float prod[3]);
void changementproduc(float prob[LEN]);


int main(){
	//attribution des tableau de propabilite et de production
	float prob[9];
	float prod[3];
	int rangemax;
	FILE* data;
	data = fopen("data.txt", "r");
	if (data != NULL)
	{
		for (int i = 0; i < 9; i++)
			fscanf(data, "%f", &prob[i]);
		for (int i = 0; i < 3; i++)
			fscanf(data, "%f", &prod[i]);
	}
	//menu
	int choix;
	printf("que voulez faire?\n(1) voir la production moyenne des 20 eoliennes\n(2) faire une simulation\n(3) modifier la matrice de transition du vent\n(4) changer les valeurs de production\nchoix: ");
	scanf("%d", &choix);
	if (choix == 1){
		int nombres;
		int wind = init_wind();
		printf("\nnombre d'itérations: ");
		scanf("%d", &nombres);
		printf("moyenne %f", moyenne(nombres, prod, prob, wind));
	}
	if (choix == 2){
		int duree;
		int nombres;
		char titre[50];
		printf("\ntemps de simulation (en jours): ");
		scanf("%d", &duree);
		printf("\nnombre d'itérations pour la simulation: ");
		scanf("%d", &nombres);
		printf("\nnom du fichier de resultat: ");
		scanf("%s", titre);
		printf("\n");
		simulation(duree, nombres, titre, prod, prob);
	}
	if (choix == 3){
		changementproba(prod);
	}
	if (choix == 4){
		changementproduc(prob);
	}
	return 0;
}

//on fais une fonction pour initialiser un vent aleatoire
int init_wind()
{
	srand( time(NULL));
	int wind = rand() % 3;
	return wind;
}

//on fait une fonction qui fait la transition aleatoire de vent
int next_wind(float prob[LEN], int wind)
{
	float random = (float)rand()/(float)(RAND_MAX);
	if (random <= prob[3 * wind])
		return 0;
	if (random <= prob[3 * wind] + prob[3 * wind + 1])
		return 1;
	return 2;
}


//on fait une fonction qui calcule la production en fonction du vent
float production_eolienne(int wind, float prod[3])
{
	return 20 * prod[wind];
}

//on fait la fonction qui calcule la moyenne du (1)
float moyenne(int nombres, float prod[3], float prob[LEN], int wind)
{
	int a = next_wind(prob, wind);
	float moy = 0;
	int j;
	for(j = 0; j < nombres; j++)
	{
			moy = moy + production_eolienne(a, prod);
			a = next_wind(prob, a);
	}
	moy = moy / nombres;
	return moy;
}

//on fait la simulation pour le on commence par faire la simulation puis on la mettra sur le fichier
void simulation(int duree, int nombres, char titre[50], float prod[3], float prob[LEN])
{
	int a = init_wind();
	int mini = 0;
	int maxi = 0;
	float minimum = 50;
	float maximum = 0;
	float moy;
	FILE* simul;
	for (int i = 0; i < nombres; i++){
		moy = moyenne(duree, prod, prob, a);
		a = next_wind(prob, a);
		printf("simulation %d ->  %fMW pour %d jours\n", i, moy, duree);
		simul = fopen(titre, "a");
		fprintf(simul, "simulation %d ->  %fMW pour %d jours\n", i, moy, duree);
		fclose(simul);
		if (moy < minimum){
			minimum = moy;
			mini = i;
		}
		if (moy > maximum){
			maximum = moy;
			maxi = i;
		};
	};
	printf("la production minimale obtenue pour %d jours est %fMW (simulation %d) \n", duree, minimum, mini);
	simul = fopen(titre, "a");
	fprintf(simul, "la production minimale obtenue pour %d jours est %fMW (simulation %d) \n", duree, minimum, mini);
	fclose(simul);
	printf("la production maximale obtenue pour %d jours est %fMW (simulation %d) \n", duree, maximum, maxi);
	simul = fopen(titre, "a");
	fprintf(simul, "la production maximale obtenue pour %d jours est %fMW (simulation %d) \n", duree, maximum, maxi);
	fclose(simul);
}


//on cree une fonction pour changer les probabilite si on change de localisation

void changementproba(float prod[3])
{
	float tab[LEN];
	for (int i = 0; i < LEN; i++){
		printf("entrer la probabilite %d: ", (i + 1));
		scanf("%f", &tab[i]);
	}
	FILE* change;
	change = fopen("data.txt", "w");
	for (int j = 0; j < (LEN - 1); j++)
		fprintf(change, "%f ", tab[j]);
	fprintf(change, "%f\n", tab[LEN - 1]);
	fclose(change);
	change = fopen("data.txt", "a");
	for (int k = 0; k < 3; k++)
		fprintf(change, "%f ", prod[k]);
	fclose(change);
}


void changementproduc(float prob[LEN])
{
	FILE* change;
	change = fopen("data.txt", "w");
	for (int j = 0;j < (LEN - 1); j++)
	{
		fprintf(change, "%f ", prob[j]);
	}
	fprintf(change, "%f\n", prob[LEN - 1]);
	fclose(change);
	float tab[3];
	for (int i = 0;i < 3; i++)
	{
		printf("donnez la production pour un vent de catégorie %d  ", i);
		scanf("%f", &tab[i]);
	}
	change = fopen("data.txt","a");
	for (int k = 0; k < 3; k++)
	{
		fprintf(change, "%f ", tab[k]);
	};
	fclose(change);
}
