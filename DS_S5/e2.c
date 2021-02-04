// examen - exercice 2
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NOM_FIC         "villes.txt"
#define NB_MAX_VILLES   100
#define LG_NOM          20
#define CRITERE_NOM     1
#define CRITERE_HAB     2

typedef struct
{
  char nom[LG_NOM];
  int habitants;
} Ville;

typedef struct
{
  Ville villes[NB_MAX_VILLES];
  int nbVilles;
} ListeVilles;

void lireFic(ListeVilles *liste);
void menu(ListeVilles *liste);
void afficherVilles(ListeVilles *liste);
void choixMenuModifierVille(ListeVilles *liste);
void choixMenuAjouterVille(ListeVilles* liste);
void choixMenuParOrdreNom(ListeVilles *liste);
void choixMenuParOrdreHab(ListeVilles *liste);
void ecrireFic(ListeVilles *liste);
int chercherVille(ListeVilles *liste, char *nom);
void copier(ListeVilles *listeDest, ListeVilles *listeOrg);
void trier(ListeVilles *liste, int critere);
int chercherVilleMax(Ville *villes, int nbVilles, int critere);
int comparer(Ville *ville1, Ville *ville2, int critere);
void echanger(Ville *villes, int i1, int i2);

void lireFic(ListeVilles *liste)
{
  FILE *fp;
  int nb = 0;
  char nom[LG_NOM];
  int habitants;

  fp = fopen(NOM_FIC, "r");
  while (fscanf(fp, "%s%d", nom, &habitants) == 2)
  {
    strcpy(liste->villes[nb].nom, nom);
    liste->villes[nb].habitants = habitants;
    nb++;
  }

  liste->nbVilles = nb;
  fclose(fp);
}

void menu(ListeVilles *liste)
{
  bool quitter = false;
  int choix;

  while (!quitter)
  {
    printf("\n");
    printf("1 afficher villes\n");
    printf("2 modifier ville\n");
    printf("3 ajouter ville\n");
    printf("4 afficher par nom\n");
    printf("5 afficher par hab\n");
    printf("6 enregistrer\n");
    printf("7 quitter\n");
    printf("choix : ");
    scanf("%d", &choix);
    switch(choix)
    {
      case 1 :
        afficherVilles(liste);
        break;
      case 2 :
        choixMenuModifierVille(liste);
        break;
      case 3 :
        choixMenuAjouterVille(liste);
        break;
      case 4 :
        choixMenuParOrdreNom(liste);
        break;
      case 5 :
        choixMenuParOrdreHab(liste);
        break;
      case 6 :
        ecrireFic(liste);
        break;
      case 7 :
        quitter = true;
        break;
    }
  }
}

void afficherVilles(ListeVilles *liste)
{
  int i;

  for (i = 0; i < liste->nbVilles; i++)
    printf("%s %d\n", liste->villes[i].nom, liste->villes[i].habitants);
}

void choixMenuModifierVille(ListeVilles *liste)
{
  char nom[LG_NOM];
  int habitants;
  int numVille;

  printf("nom et habitants : ");
  scanf("%s%d", nom, &habitants);

  numVille = chercherVille(liste, nom);
  if (numVille < 0)
    printf("ville non trouvee\n");
  else
    liste->villes[numVille].habitants = habitants;
}

void choixMenuAjouterVille(ListeVilles* liste)
{
  Ville ville;
  int numVille;

  printf("nom et habitants : ");
  scanf("%s%d", ville.nom, &ville.habitants);

  numVille = chercherVille(liste, ville.nom);
  if (numVille >= 0)
    printf("ville deja presente\n");
  else if (liste->nbVilles < NB_MAX_VILLES)
  {
    liste->villes[liste->nbVilles] = ville;
    liste->nbVilles++;
  }
  else
    printf("nb max de villes deja atteint\n");
}

void choixMenuParOrdreNom(ListeVilles *liste)
{
  ListeVilles liste2;

  copier(&liste2, liste);
  trier(&liste2, CRITERE_NOM);
  afficherVilles(&liste2);
}

void choixMenuParOrdreHab(ListeVilles *liste)
{
  ListeVilles liste2;

  copier(&liste2, liste);
  trier(&liste2, CRITERE_HAB);
  afficherVilles(&liste2);
}

void ecrireFic(ListeVilles *liste)
{
  FILE *fp;
  int i;

  fp = fopen(NOM_FIC, "w");
  for (i = 0; i < liste->nbVilles; i++)
    fprintf(fp, "%s %d\n", liste->villes[i].nom, liste->villes[i].habitants);

  fclose(fp);
}

int chercherVille(ListeVilles *liste, char *nom)
{
  int i;

  for (i = 0; i < liste->nbVilles; i++)
  {
    if (strcmp(nom, liste->villes[i].nom) == 0)
      return i;
  }

  return -1;
}

void copier(ListeVilles *listeDest, ListeVilles *listeOrg)
{
  int i = 0;

  for (i = 0; i < listeOrg->nbVilles; i++)
    listeDest->villes[i] = listeOrg->villes[i];

  listeDest->nbVilles = listeOrg->nbVilles;
}

// tri par ordre croisant selon le critere
void trier(ListeVilles *liste, int critere)
{
  int n = liste->nbVilles;

  // algorithme de tri par selection
  while (n > 0)
  {
    int iMax = chercherVilleMax(liste->villes, n, critere);
    echanger(liste->villes, n - 1, iMax);
    n--;
  }
}

// cherche dans le tableau la ville max selon le critere et retourne son indice
int chercherVilleMax(Ville *villes, int nbVilles, int critere)
{
  int iMax = 0, i;

  for (i = 0; i < nbVilles; i++)
  {
    if (comparer(&villes[i], &villes[iMax], critere) > 0)
      iMax = i;
  }

  return iMax;
}

// compare les deux villes selon le critere et retourne negatif, nul ou positif
// selon que ville1 est inferieure, egale ou superieure a ville2
int comparer(Ville *ville1, Ville *ville2, int critere)
{
  if (critere == CRITERE_NOM)
    return strcmp(ville1->nom, ville2->nom);
  else
    // on inverse 1 et 2 pour avoir un tri par ordre decroissant
    return ville2->habitants - ville1->habitants;
}

// echange dans le tableau les villes d'indices i1 et i2
void echanger(Ville *villes, int i1, int i2)
{
  Ville savVille1 = villes[i1];
  villes[i1] = villes[i2];
  villes[i2] = savVille1;
}

int main(void)
{
  ListeVilles listeVilles;

  lireFic(&listeVilles);
  menu(&listeVilles);

  return 0;
}
