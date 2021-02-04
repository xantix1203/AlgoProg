// seance 10 - TP 1 tas
#include <stdio.h>

#define TAILLE_MAX  100

typedef struct
{
  int tab[TAILLE_MAX];
  int taille;
} Tas;

void creerTasVide(Tas *tas);
int indiceFilsGauche(int i);
int indiceFilsDroit(int i);
int indicePere(int i);
int nbFils(Tas *tas, int i);
int filsGauche(Tas *tas, int i);
int filsDroit(Tas *tas, int i);
int pere(Tas *tas, int i);
int noeud(Tas *tas, int i);
void afficherTas(Tas *tas);
void insererTas(Tas *tas, int e);
void echangerNoeuds(Tas *tas, int i1, int i2);
void creerTas(Tas *tas, int *t, int taille);

void creerTasVide(Tas *tas)
{
  tas->taille = 0;
}

int indiceFilsGauche(int i)
{
  return 2 * i + 1;
}

int indiceFilsDroit(int i)
{
  return 2 * i + 2;
}

int indicePere(int i)
{
  return (i - 1) / 2;
}

int nbFils(Tas *tas, int i)
{
  if (indiceFilsGauche(i) > tas->taille - 1)
    return 0;
  else if (indiceFilsDroit(i) <= tas->taille - 1)
    return 2;
  else
    return 1;
}

int filsGauche(Tas *tas, int i)
{
  return tas->tab[indiceFilsGauche(i)];
}

int filsDroit(Tas *tas, int i)
{
  return tas->tab[indiceFilsDroit(i)];
}

int pere(Tas *tas, int i)
{
  return tas->tab[indicePere(i)];
}

int noeud(Tas *tas, int i)
{
  return tas->tab[i];
}

void afficherTas(Tas *tas)
{
  int i;
  int nbfils;
  int niveau = 1;
  int puiss2Niveau = 2; // pour calculer 2 a la puissance niveau

  printf("\n");

  for (i = 0; i < tas->taille; i++)
  {
    printf("%d", noeud(tas, i));

    nbfils = nbFils(tas, i);
    if (nbfils == 2)
      printf("(%d %d)", filsGauche(tas, i), filsDroit(tas, i));
    else if (nbfils == 1)
      printf("(%d)", filsGauche(tas, i));

    if (i + 1 == puiss2Niveau - 1)  // fin d'un niveau complet
    {
      printf("\n");
      niveau++;
      puiss2Niveau *= 2;
    }
    else if (i + 1 == tas->taille)  // fin du dernier niveau
      printf("\n");
    else
      printf(" ");
  }
}

void insererTas(Tas *tas, int e)
{
  int indice_e, indice_pere;

  // ajout de l'element a la fin du tableau
  tas->tab[tas->taille] = e;
  tas->taille++;
  indice_e = tas->taille - 1;

  // tant que l'element n'est pas bien place on l'echange avec son pere
  while (indice_e != 0 && e > pere(tas, indice_e))
  {
    indice_pere = indicePere(indice_e);
    echangerNoeuds(tas, indice_e, indice_pere);
    indice_e = indice_pere;
  }
}

void echangerNoeuds(Tas *tas, int i1, int i2)
{
  int val1 = tas->tab[i1];
  tas->tab[i1] = tas->tab[i2];
  tas->tab[i2] = val1;
}

void creerTas(Tas *tas, int *t, int taille)
{
  int i;

  creerTasVide(tas);
  for (i = 0; i < taille; i++)
    insererTas(tas, t[i]);
}

int main(void)
{
  Tas tas1 = { {18, 16, 12, 10, 9, 11, 5, 4, 6, 3}, 10 };
  Tas tas2;
  int t2[] = {6, 16, 4, 10, 9, 11, 5, 12, 18, 3};

  afficherTas(&tas1);
  insererTas(&tas1, 15);
  afficherTas(&tas1);

  creerTasVide(&tas2);
  insererTas(&tas2, 10);
  insererTas(&tas2, 12);
  afficherTas(&tas2);

  creerTas(&tas2, t2, sizeof(t2)/sizeof(int));
  afficherTas(&tas2);

  return 0;
}
