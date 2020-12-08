//
//  main.c
//  AlgoProg
//
//  Created by Arnaud Cotten on 25/11/2020.
//

//on fais une fonction pour initialiser un vent aleatoire

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 9
int init_wind(void);
int next_wind(float prob[LEN], int wind);
float moyenne(int nombres,float prod[3],float prob[LEN],int wind);
float production_eolienne(int wind,float prod[3]);
void simulation(int duree,int nombres,char titre[3],float prod[3],float prob[LEN]);

int main()
{
    
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
    char titre[3] = "sim";
    simulation(10, 5, titre, prod, prob);
}
int init_wind()
{
    srand(time(NULL));
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

float production_eolienne(int wind,float prod[3])
{
    return 20*prod[wind];
}
float moyenne(int nombres,float prod[3],float prob[LEN],int wind)
{
    int a=next_wind(prob,wind);
    float moy=0;
    int j;
    for(j=0;j<nombres;j++)
    {
            moy=moy+production_eolienne(a,prod);
            a=next_wind(prob,a);
    }
    moy=moy/nombres;
    return moy;
}

void simulation(int duree,int nombres,char titre[3],float prod[3],float prob[LEN])
{
    int a=init_wind();
    int i;
    int j;
    int mini=0;
    int maxi=0;
    float minimum=50;
    float maximum=0;
    float moy;
    FILE* simul;
    for (i=0;i<nombres;i++)
    {
        moy=moyenne(duree,prod,prob,a);
        a=next_wind(prob,a);
        printf("le %d cas produit%f MW\n",i,moy);
        simul=fopen(titre,"a");
        fprintf(simul,"le %d cas produit%f MW\n",i,moy);
        fclose(simul);
        if (moy<minimum)
        {
            minimum=moy;
            mini=i;
        }
        if (moy>maximum)
        {
            maximum=moy;
            maxi=i;
        };
    }
    printf("le cas ou la production est minimal est le %d avec une production de %f MW\n",mini,minimum);
    simul=fopen(titre,"a");
    fprintf(simul,"le cas ou la production est minimal est le %d avec une production de %f MW\n",mini,minimum);
    fclose(simul);
    printf("le casou la production est maximal est le %d avec une production de%f MW\n",maxi,maximum);
    simul=fopen(titre,"a");
    fprintf(simul,"le casou la production est maximal est le %d avec une production de%f MW\n",maxi,maximum);
    fclose(simul);
}
