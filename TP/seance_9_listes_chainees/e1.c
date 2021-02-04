// seance 10 - exercice 1
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define NOM_FIC_COMPTES   "comptes.txt"
#define LG_NOM            20

typedef struct Compte
{
  char nom[LG_NOM];
  float montant;
  struct Compte *suiv;
} Compte;

typedef struct
{
  Compte *tete;
} ListeComptes;

void lireFicComptes(ListeComptes *liste);
void menu(ListeComptes *liste);
void afficherLesComptes(ListeComptes *liste);
void choixMenuAfficherCompte(ListeComptes *liste);
void choixMenuOperationCompte(ListeComptes *liste);
void choixMenuAjouterCompte(ListeComptes *liste);
void choixMenuSupprimerCompte(ListeComptes *liste);
bool supprimerCompte(ListeComptes *liste, char *nom);
void ecrireFicComptes(ListeComptes *liste);
void insererCompte(ListeComptes *liste, Compte *compte);
void insererCompteEnTete(ListeComptes *liste, Compte *compte);
void afficherCompte(Compte *compte);
Compte *chercherCompte(ListeComptes *liste, char *nom);

void lireFicComptes(ListeComptes *liste)
{
  FILE *fp;
  char nom[LG_NOM];
  float montant;
  Compte *nouvCompte; 

  fp = fopen(NOM_FIC_COMPTES, "r");

  while (fscanf(fp, "%s%f", nom, &montant) == 2)
  {
    nouvCompte = (Compte *)malloc(sizeof(Compte));
    strcpy(nouvCompte->nom, nom);
    nouvCompte->montant = montant;

    insererCompte(liste, nouvCompte);
  }

  fclose(fp);
}

void menu(ListeComptes *liste)
{
  bool quitter = false;
  int choix;
    
  while (!quitter)
  {
    printf("\n");
    printf("1  afficher les comptes\n");
    printf("2  afficher un compte\n");
    printf("3  operation sur un compte\n");
    printf("4  ajouter un compte\n");
    printf("5  supprimer un compte\n");
    printf("6  quitter\n");
    printf("choix : ");
    scanf("%d", &choix);

    switch (choix)
    {
      case 1 :
        afficherLesComptes(liste);
        break;
      case 2 :
        choixMenuAfficherCompte(liste);
        break;
      case 3 :
        choixMenuOperationCompte(liste);
        break;
      case 4 :
        choixMenuAjouterCompte(liste);
        break;
      case 5 :
        choixMenuSupprimerCompte(liste);
        break;
      case 6 :
        quitter = true;
        ecrireFicComptes(liste);
        break;
      default :
        printf("choix incorrect\n");
        break;
    }
  }
}

void afficherLesComptes(ListeComptes *liste)
{
  Compte *compte = liste->tete;
  while (compte != NULL)
  {
    afficherCompte(compte);
    compte = compte->suiv;
  }
}

void choixMenuAfficherCompte(ListeComptes *liste)
{
  char nom[LG_NOM];
  Compte *compte;

  printf("nom : ");
  scanf("%s", nom);

  compte = chercherCompte(liste, nom);
  if (compte == NULL)
    printf("compte inconnu\n");
  else
    afficherCompte(compte);
}

void choixMenuOperationCompte(ListeComptes *liste)
{
  char nom[LG_NOM];
  float operation;
  Compte *compte;

  printf("nom et operation : ");
  scanf("%s%f", nom, &operation);

  compte = chercherCompte(liste, nom);
  if (compte == NULL)
    printf("compte inconnu\n");
  else
    compte->montant += operation;
}

void choixMenuAjouterCompte(ListeComptes *liste)
{
  char nom[LG_NOM];
  Compte *nouvCompte;

  printf("nom : ");
  scanf("%s", nom);

  if (chercherCompte(liste, nom) != NULL)
    printf("compte deja existant\n");
  else
  {
    nouvCompte = (Compte *)malloc(sizeof(Compte));
    strcpy(nouvCompte->nom, nom);
    nouvCompte->montant = 0;

    insererCompte(liste, nouvCompte);
  }
}

void choixMenuSupprimerCompte(ListeComptes *liste)
{
  char nom[LG_NOM];
  Compte *compte;

  printf("nom : ");
  scanf("%s", nom);

  if (supprimerCompte(liste, nom) == false)
    printf("compte inconnu\n");
}

// cherche un compte par son nom et le supprime
// retourne false si compte non trouve
bool supprimerCompte(ListeComptes *liste, char *nom)
{
  bool trouve = true;

  // la suppression du compte consistera a chainer son precedent a son suivant
  // on commence donc par chercher le compte dans la liste en gardant trace
  // du precedent
  Compte *prec = NULL;
  Compte *compte = liste->tete;
  while (compte != NULL && strcmp(compte->nom, nom) != 0)
  {
    prec = compte;
    compte = compte->suiv;
  }

  if (compte == NULL)
    trouve = false;
  else
  {
    // supprimer le compte de la liste : chainer son precedent a son suivant
    if (prec == NULL) // le compte est le premier
      liste->tete = compte->suiv;
    else
      prec->suiv = compte->suiv;

    free(compte);
  }

  return trouve;
}

void ecrireFicComptes(ListeComptes *liste)
{
  FILE *fp;
  Compte *compte;

  fp = fopen(NOM_FIC_COMPTES, "w");

  compte = liste->tete;
  while (compte != NULL)
  {
    fprintf(fp, "%s %.2f\n", compte->nom, compte->montant);
    compte = compte->suiv;
  }

  fclose(fp);
}

// insertion par ordre alphabetique
void insererCompte(ListeComptes *liste, Compte *compte)
{
  // recherche de la position d'insertion du compte, c'est a dire du premier
  // compte C > au compte a inserer
  // le compte sera insere avant C, il faut donc garder trace du precedent de
  // C lors de la recherche
  Compte *prec = NULL;
  Compte *courant = liste->tete;
  while (courant != NULL && strcmp(compte->nom, courant->nom) >= 0)
  {
    prec = courant;
    courant = courant->suiv;
  }

  // le compte est a inserer entre prec et courant
  if (prec == NULL)
    insererCompteEnTete(liste, compte);
  else
  {
    prec->suiv = compte;
    compte->suiv = courant;
  }
}

void insererCompteEnTete(ListeComptes *liste, Compte *compte)
{
  compte->suiv = liste->tete;
  liste->tete = compte;
}

void afficherCompte(Compte *compte)
{
  printf("%s %.2f\n", compte->nom, compte->montant);
}

// cherche un compte par non nom, retourne NULL si non trouve
Compte *chercherCompte(ListeComptes *liste, char *nom)
{
  Compte *compte = liste->tete;
  while (compte != NULL && strcmp(compte->nom, nom) != 0)
      compte = compte->suiv;

  return compte;
}

int main(void)
{
  ListeComptes listeCpt;

  listeCpt.tete = NULL;
  lireFicComptes(&listeCpt);
  menu(&listeCpt);

  return 0;
}
