// examen - exercice 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Composante
{
  int indice;
  int val;
  struct _Composante *suiv;
} Composante;

typedef struct
{
  int taille;
  Composante *tete;
} Vecteur;

void initVecteur(Vecteur *vect, int taille);
void setVecteur1(Vecteur *vect, int i, int val);
void afficherVecteur(Vecteur *vect);
int getValeur(Vecteur *vect, int i);
void resetVecteur(Vecteur *vect);
void setVecteur(Vecteur *vect, int i, int val);
void additionVecteurs(Vecteur *vect1, Vecteur *vect2, Vecteur *vectResult);
Composante *chercherComposante(Vecteur *vect, int i);
Composante *creerComposante(int i, int val);
void insererEnTete(Vecteur *vect, Composante *compo);
int max(int a, int b);

void initVecteur(Vecteur *vect, int taille)
{
  vect->taille = taille;
  vect->tete = NULL;
}

void setVecteur1(Vecteur *vect, int i, int val)
{
  Composante *compo;

  compo = chercherComposante(vect, i);
  if (compo != NULL)  // composante trouvee
    compo->val = val;
  else
  {
    compo = creerComposante(i, val);
    insererEnTete(vect, compo);
  }
}

void afficherVecteur(Vecteur *vect)
{
  Composante *compo = vect->tete;

  printf("vecteur taille %d\n", vect->taille);

  while (compo != NULL)
  {
    printf("[%d] : %d\n", compo->indice, compo->val);
    compo = compo->suiv;
  }
}

int getValeur(Vecteur *vect, int i)
{
  Composante *compo;

  compo = chercherComposante(vect, i);
  if (compo != NULL)  // composante trouvee
    return compo->val;
  else
    return 0;
}

void resetVecteur(Vecteur *vect)
{
  // on vide la liste
  Composante *compo = vect->tete;

  while (compo != NULL)
  { 
    Composante *suiv = compo->suiv;
    free(compo);
    compo = suiv;
  }

  vect->tete = NULL;
}

// on range les composantes par ordre d'indice croissant
void setVecteur(Vecteur *vect, int i, int val)
{
  Composante *prec = NULL;
  Composante *courante = vect->tete;
  Composante *nouvCompo;

  // recherche de la composante d'indice i ou de sa position d'insertion si
  // elle n'est pas presente
  while (courante != NULL && i > courante->indice)
  {
    prec = courante;
    courante = courante->suiv;
  }

  if (courante != NULL && i == courante->indice)  // composante trouvee
    courante->val = val;
  else
  {
    nouvCompo = creerComposante(i, val);
    if (prec == NULL)
      insererEnTete(vect, nouvCompo);
    else
    {
      // insertion apres prec
      nouvCompo->suiv = prec->suiv;
      prec->suiv = nouvCompo;
    }
  }
}

void additionVecteurs(Vecteur *vect1, Vecteur *vect2, Vecteur *vectResult)
{
  Composante *compo1, *compo2;

  resetVecteur(vectResult);
  vectResult->taille = max(vect1->taille, vect2->taille);

  compo1 = vect1->tete;  
  compo2 = vect2->tete;  

  // on parcours les deux vecteurs en parallele en rangeant dans le vecteur
  // resultat la composante de plus petit indice ou la somme des deux
  // composantes si elles sont de meme indice
  while (compo1 != NULL || compo2 != NULL)
  {
    // on a fini le premier vecteur
    if (compo1 == NULL)
    {
      setVecteur(vectResult, compo2->indice, compo2->val);
      compo2 = compo2->suiv;
    }
    // on a fini le deuxieme vecteur
    else if (compo2 == NULL)
    {
      setVecteur(vectResult, compo1->indice, compo1->val);
      compo1 = compo1->suiv;
    }
    else if (compo1->indice < compo2->indice)
    {
      setVecteur(vectResult, compo1->indice, compo1->val);
      compo1 = compo1->suiv;
    }
    else if (compo2->indice < compo1->indice)
    {
      setVecteur(vectResult, compo2->indice, compo2->val);
      compo2 = compo2->suiv;
    }
    else  // les deux indices sont egaux
    {
      int somme = compo1->val + compo2->val;
      if (somme != 0)
        setVecteur(vectResult, compo1->indice, somme);
      compo1 = compo1->suiv;
      compo2 = compo2->suiv;
    }
  }
}

// cherche la composante d'indice i, c'est a dire le maillon de la liste
// contenant l'indice i;
// retourne le pointeur NULL si la composante n'a pas ete trouvee
Composante *chercherComposante(Vecteur* vect, int i)
{
  bool trouve = false;
  Composante *compo = vect->tete;

  while (!trouve && compo != NULL)
  {
    if (compo->indice == i)
      trouve = true;
    else
      compo = compo->suiv;
  }

  return compo;
}

Composante *creerComposante(int i, int val)
{
  Composante *compo;

  compo = (Composante *) malloc(sizeof(Composante));
  compo->indice = i;
  compo->val = val;

  return compo;
}

void insererEnTete(Vecteur *vect, Composante *compo)
{
  compo->suiv = vect->tete;
  vect->tete = compo;
}

int max(int a , int b)
{
  if (a > b)
    return a;
  else
    return b;
}

int main(void)
{
  Vecteur v1, v2, v3;

  initVecteur(&v1, 1000);
  setVecteur(&v1, 10, 45);
  setVecteur(&v1, 250, 20);
  afficherVecteur(&v1);
  setVecteur(&v1, 250, 60);
  setVecteur(&v1, 120, 16);
  afficherVecteur(&v1);

  printf("%d %d\n", getValeur(&v1, 10), getValeur(&v1, 200));

  resetVecteur(&v1);
  afficherVecteur(&v1);

  setVecteur(&v1, 340, 32);
  setVecteur(&v1, 15, 8);
  setVecteur(&v1, 410, 55);
  afficherVecteur(&v1);

  initVecteur(&v2, 800);
  setVecteur(&v2, 400, 68);
  setVecteur(&v2, 340, 76);
  setVecteur(&v2, 14, 2);
  setVecteur(&v2, 756, 90);
  afficherVecteur(&v2);

  initVecteur(&v3, 1);
  additionVecteurs(&v1, &v2, &v3);
  afficherVecteur(&v3);

  return 0;
}
