#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 9
int init_wind(void);
int next_wind(float prob[LEN], int wind);
float production_eolienne(int wind, float prod[3]);
float moyenne(int nb_days, float prod[3], float prob[LEN]);
void simulation_moyenne(int nb_sim, int nb_days, char titre[50], float prod[3], float prob[LEN]);
void simulation_jour_a_jour(float prob[LEN], float prod[3], int nb_days, char titre[50]);
void changementproba(float prod[3]);
void changementproduc(float prob[LEN]);
typedef struct{
	int jour;
	int etat_wind;
	float production;
}stat_eolienne;


int main(){
	//Lecture du fichier data
	float prob[9];
	float prod[3];
	srand( time(NULL));
	FILE* data;
	data = fopen("data.txt", "r");
	if (data != NULL){
		for (int i = 0; i < 9; i++)
			fscanf(data, "%f", &prob[i]);
		for (int i = 0; i < 3; i++)
			fscanf(data, "%f", &prod[i]);
	}
	//Affichage du menu
	int choix;
	printf("que voulez faire?\n(1) voir la production moyenne des 20 eoliennes\n(2) faire une simulation de plusieurs moyenne\n(3) faire une simulation jour par jour\n(4) modifier la matrice de transition du vent\n(5) changer les valeurs de production\n choix: ");
	scanf("%d", &choix);
	if (choix == 1){
		int nb_days;
		int wind = init_wind();
		printf("\nnombre d'itérations: ");
		scanf("%d", &nb_days);
		printf("moyenne %f\n", moyenne(nb_days, prod, prob));
	}
	if (choix == 2){
		int nb_days;
		int nb_sim;
		char title[50];
		printf("\nnombres de simulations : ");
		scanf("%d", &nb_sim);
		printf("\ntemps de simuation en jour: ");
		scanf("%d", &nb_days);
		printf("\nnom du fichier de resultat: ");
		scanf("%s", title);
		printf("\n");
		simulation_moyenne(nb_sim, nb_days, title, prod, prob);
	}
	if (choix == 3){
		int nb_days;
		char title[50];
		printf("\ntemps de simulation (en jours): ");
		scanf("%d", &nb_days);
		printf("\nnom du fichier de resultat: ");
		scanf("%s", title);
		simulation_jour_a_jour(prob,prod,nb_days,title);
	}
	if (choix == 4){
		changementproba(prod);
	}
	if (choix == 5){
		changementproduc(prob);
	};
	return 0;
}

//Cette fonction retourne un entier aléatoire entre 0 et 2 pour initialiser un vent
int init_wind(){
	int wind = rand() % 3;
	return wind;
}

//La fonction renvoit le vent suivant en se basant sur le vent actuel et sur la matrice de transition
int next_wind(float prob[LEN], int wind){
	float random = (float)rand()/(float)(RAND_MAX);
	if (random <= prob[3 * wind])
		return 0;
	if (random <= prob[3 * wind] + prob[3 * wind + 1])
		return 1;
	return 2;
}


//Renvoit la production journalière du champ d'éolienne pour un vent donné
float production_eolienne(int wind, float prod[3]){
	return 20 * prod[wind];
}


//calcul de la production moyenne du parc sur nb_days jours
float moyenne(int nb_days, float prod[3], float prob[LEN]){
	int wind = init_wind();
	float moy = 0;
	int j;
	for(j = 0; j < nb_days; j++)
	{
			moy = moy + production_eolienne(wind, prod);
			wind = next_wind(prob, wind);
	}
	moy = moy / nb_days;
	return moy;
}


//simulation non détaillée
void simulation_moyenne(int nb_sim, int nb_days, char title[50], float prod[3], float prob[LEN]){
	int wind = init_wind();
	int mini = 0;
	int maxi = 0;
	float minimum = 50;
	float maximum = 0;
	float moy;
	FILE* sim;
	for (int i = 0; i < nb_sim; i++){
		moy = moyenne(nb_days, prod, prob);
		wind = next_wind(prob, wind);
		printf("simulation %d ->  %fMW pour %d jours\n", i + 1, moy, nb_days);
		sim = fopen(title, "a");
		fprintf(sim, "simulation %d ->  %fMW pour %d jours\n", i, moy, nb_days);
		fclose(sim);
		if (moy < minimum){
			minimum = moy;
			mini = i+1;
		}
		if (moy > maximum){
			maximum = moy;
			maxi = i+1;
		};
	};
	printf("la production minimale obtenue pour %d jours est %fMW (simulation %d) \n", nb_days, minimum, mini);
	sim = fopen(title, "a");
	fprintf(sim, "la production minimale obtenue pour %d jours est %fMW (simulation %d) \n", nb_days, minimum, mini);
	fclose(sim);
	printf("la production maximale obtenue pour %d jours est %fMW (simulation %d) \n", nb_days, maximum, maxi);
	sim = fopen(title, "a");
	fprintf(sim, "la production maximale obtenue pour %d jours est %fMW (simulation %d) \n", nb_days, maximum, maxi);
	fclose(sim);
}


//simulation avec des résultats détaillés
void simulation_jour_a_jour(float prob[LEN], float prod[3], int nb_days, char title[50]){
	stat_eolienne stat;
	stat.etat_wind = init_wind();
	float moy;
	FILE* sim;
	int nb_weak_wind = 0;
	int nb_medium_wind = 0;
	int nb_strong_wind = 0;
	for (int i = 0; i < nb_days; i++)
	{
		if (stat.etat_wind == 0)
			nb_weak_wind++;
		if (stat.etat_wind == 1)
			nb_medium_wind++;
		if (stat.etat_wind == 2)
			nb_strong_wind++;
		stat.jour = 1 + i;
		stat.production = production_eolienne(stat.etat_wind, prod);
		printf("le jour %d l'etat du vent est %d et la production est de %f MW\n", stat.jour, stat.etat_wind, stat.production);
		sim = fopen(title, "a");
		fprintf(sim, "le jour %d l'etat du vent est %d et la production est de %f MW\n", stat.jour, stat.etat_wind, stat.production);
		fclose(sim);
		moy = moy + stat.production;
		stat.etat_wind = next_wind(prob, stat.etat_wind);
	}
	moy = moy / nb_days;
	printf("la production moyenne est %f \n", moy);
	sim = fopen(title, "a");
	fprintf(sim, "la production moyenne est %f \n", moy);
	fclose(sim);
	printf("on a eu %d jours de vent faible, %d jours de vent moyen et %d jours de vent fort", nb_weak_wind, nb_medium_wind, nb_strong_wind);
	sim = fopen(title, "a");
	fprintf(sim, "on a eu %d jours de vent faible, %d jours de vent moyen et %d jours de vent fort", nb_weak_wind, nb_medium_wind, nb_strong_wind);
	fclose(sim);
}

//modification de prob dans data.txt
void changementproba(float prod[3])
{
	float tab[LEN];
	for (int i = 0; i < LEN; i++){
		printf("entrer la probabilite %d: ", (i + 1));
		scanf("%f", &tab[i]);
	}
	FILE* data;
	data = fopen("data.txt", "w");
	for (int j = 0; j < (LEN - 1); j++)
		fprintf(data, "%f ", tab[j]);
	fprintf(data, "%f\n", tab[LEN - 1]);
	fclose(data);
	data = fopen("data.txt", "a");
	for (int k = 0; k < 3; k++)
		fprintf(data, "%f ", prod[k]);
	fclose(data);
}

//modification de prod dans data.txt
void changementproduc(float prob[LEN]){
	FILE* data;
	data = fopen("data.txt", "w");
	for (int j = 0; j < (LEN - 1); j++)
		fprintf(data, "%f ", prob[j]);
	fprintf(data, "%f\n", prob[LEN - 1]);
	fclose(data);
	float tab[3];
	for (int i = 0;i < 3; i++){
		printf("donnez la production pour un vent de catégorie %d  ", i);
		scanf("%f", &tab[i]);
	}
	data = fopen("data.txt", "a");
	for (int k = 0; k < 3; k++)
		fprintf(data, "%f ", tab[k]);
	fclose(data);
}
