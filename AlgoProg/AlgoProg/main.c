#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_MAX 100

struct string
{
    struct string * fd;
    struct string * fg;
    char str[STR_MAX];
    int len;
};



void affiche_chaines(struct string * cell);
struct string * lit_fichier(char *nom_fichier, struct string * ABR, int * nb);
void affiche_arbre(struct string * ABR);
struct string * nouveau_noeud(char mot[]);
struct string * insere_nd(struct string *ABR, struct string *noeud);
void chercher_mot (struct string *ABR, char mot[]);
void chercher_mot_long (struct string *ABR, int l);
void tri_croissant(struct string * ABR);
void tri_decroissant(struct string * ABR);
struct string * supp_noeud(struct string *ABR, char * mot);
void supp_abr(struct string* noeud);
int main();


/*affiche_chaine permet d'afficher un noeud de l'arbre. C'est a dire sa valeur : le mot et sa clef : la longueur du mot.*/
void affiche_chaines(struct string * cell)
{
    if (cell != NULL)
    {
        printf("%s",(cell->str));
        printf(" (%d)\n",cell->len);
    }
}

/*Affiche_arbre permet de lire le fichier grâce à un parcours préfixe : racine/gauche/droite. On effectue ce parcours de manière récursive.*/
void affiche_arbre(struct string * ABR)
{
    if(ABR != NULL)
    {
        affiche_chaines(ABR);
        if (ABR->fg != NULL)
        {
            affiche_arbre(ABR->fg);
        }
        if(ABR->fd!= NULL)
        {
            affiche_arbre(ABR->fd);
        }
    }
}

/*lit_ficher permet de lire un ficher et de convertir chaque mot du fichier en une cellule de l'arbre.
Le noeud est créée en utilisant la fonction nouveau_noeud qui affecte comme clé la longueur du mot et comme la valeur du noeud le mot. Il est ensuite placé dans l'arbre grâce insère_noeud défni après.*/
struct string * lit_fichier(char *nom_fichier, struct string * ABR, int * nbredemots)
{
    FILE *f;
    struct string * noeud ;
    char mot[STR_MAX] ;
    int nbmot = 0;
    int i = 0;
    int a = 0;

    f = fopen(nom_fichier, "r") ; /*on ouvre le fichier texte que l'on va lire.*/
    if (f==NULL)
        printf("Fichier non disponible.\n");
    else
    {
        while ( fscanf(f, "%s", mot) > 0 ) {
            noeud = nouveau_noeud(mot) ;
            ABR = insere_nd(ABR, noeud) ;
            ++ *nbredemots ;
            ++ a ;
        }
    }

    printf("%d",a);
    *nbredemots = nbmot ;
    fseek(f, 0, SEEK_SET);
    while ((fscanf(f,"%s",mot)!=EOF)) /*permet de lire le fichier et d'insérer le mot dans l'arbre.*/
        {
            noeud = nouveau_noeud(mot);
            insere_nd(ABR,noeud);
            i ++ ;
        }

    fclose(f);
    return ABR;
}


/*La fonction nouveau_noeud permet de créer un noeud à partir d'un mot et en initialisant le fis gauche et le fils droit à la valeur NULL. */
struct string * nouveau_noeud(char mot[])
{
    struct string * nv_nd = NULL;
    nv_nd = malloc(sizeof(struct string)) ; /*permet d'allouer la mémoire nécessaire pour enregistrer le noeud*/
    strcpy(nv_nd->str, mot) ;
    nv_nd -> len = strlen(mot);
    nv_nd -> fg = NULL;
    nv_nd -> fd = NULL;
    return nv_nd;
}

/*La fonction insere_noeud permet d'insérer un noeur créer en respectant les règles qui régissent un arbre.
Le fils le plus à gauche est plus petit que sa racine et le fils à droite est plus grand que sa racine.
Ainsi la valeur de la racine doit être comprise entre la valeur du fils gauche et du fils droit.*/
struct string * insere_nd(struct string *ABR, struct string *noeud)
{
    if (ABR != NULL)
    {
        if (ABR->len > noeud->len) /*on écrit ABR->len et non ABR.len car ABR est un pointeur et non une structure complexe.*/
        {
            if (ABR->fg!=NULL)
                insere_nd(ABR->fg,noeud);
            else
                {ABR->fg = noeud;}
        }
        if (noeud -> len > ABR->len)
        {
            if (ABR->fd!=NULL)
                insere_nd(ABR->fd,noeud);
            else
                {ABR->fd = noeud;}
        }
    }
    return ABR ;
}


/*La fonction recherche permet de rechercher les mots d'une longeur donné dans un arbre à partir de leur clef.*/

void chercher_mot_long(struct string *ABR, int l){
    if (ABR->str != NULL){
        if (ABR->len > l ){
            chercher_mot_long(ABR->fd, l) ;
        }
        if (ABR->len < l ){
            chercher_mot_long(ABR->fg, l) ;
        }
        if (ABR->len == l ){
            printf("%s\n",ABR->str) ;
            printf("\n");
            chercher_mot_long(ABR->fg, l) ;
            chercher_mot_long(ABR->fd, l) ;
        }
    }
}

void chercher_mot(struct string *ABR, char mot[]){
    int l = strlen(mot);

    if (ABR->str != NULL){
        if (ABR->len > l ){
            chercher_mot(ABR->fd, mot) ;
        }
        if (ABR->len < l ){
            chercher_mot(ABR->fg, mot) ;
        }
        if (ABR->len == l ){
            if(strcmp(ABR->str, mot)==0) {
                printf("%s\n","Le mot se trouve bien dans le document. \n");
                exit(1);
            }
            else{
                chercher_mot(ABR->fd, mot) ;
            }
        }
    }
    printf("Le mot ne se trouve malheureusement pas dans le document. \n");
    exit(1);
}

/*Les fonctions tri croissant et tri_decroissant permet d'avoir les mots contenus dans un arbre en les ayant trié par ordre
croissant ou décroissant de leur longueur.
En effet, dans un arbre binaire le fils gauche est plus petit que la racine et le fils droit et plus grand que la racine
qui elle même plus petite que sa racine si elle est un fils gauche ou plus grande que sa racine si elle est le fils droit.
Et ainsi de suite.*/
void tri_croissant(struct string * ABR)
{
    if (ABR == NULL)
        return ;
    tri_croissant(ABR->fg);
    printf(ABR->str);
    tri_croissant(ABR->fd);
}

void tri_decroissant(struct string * ABR)
{
    if (ABR == NULL)
        return ;
    tri_decroissant(ABR->fd);
    printf(ABR->str);
    tri_decroissant(ABR->fg);
}

/*La fonction supp_noeud permet de supprimer un mot de l'arbre grâce à sa longueur.
Cette fonction supprime un noeud tout en gardants la structure de l'arbre.*/
struct string * supp_nd(struct string *ABR, char * mot)
{
    int n = strlen(mot);
    struct string* temp;
    struct string* boom;

    if (ABR == NULL)
        return ABR;

    if (n < ABR->len)
        ABR->fg = supp_nd(ABR->fg, mot); /* Si le mot a supprime est plus petit que le mot de la racine alors il faut aller à gauche */

        else if (n > ABR->len)
        ABR->fg = supp_nd(ABR->fd, mot); /* Si le mot a supprime est plus grand que le mot de la racine alors il faut aller à droite */
    /*sinon les deux mots ont la même longeur.*/
            else
            {
                if (ABR->fg == NULL)
                {
                    struct string * temp = ABR->fd;
                    free(ABR);
                    return temp;
                }
                else if (ABR->fd == NULL)
                {
                    struct string *temp = ABR->fg;
                    free(ABR);
                    return temp;
                }
                boom = ABR->fd;
                while (boom && boom->fg != NULL)
                    boom = boom->fd;

                temp = boom;
                ABR->len = temp->len;
                ABR->fd = supp_nd(ABR->fd, temp->str);
            }
            return ABR;
        }

        void supp_abr(struct string* noeud)
        {
            if (noeud == NULL)
                return;

            supp_abr(noeud->fg);
            supp_abr(noeud->fd);
    free(noeud); /*On supprime la mémoire allouée au noeud qui était dans ABR*/
        }

        int menu()
        {
           int choix = 0;
           printf("Que voulez vous faire ? \n");
           printf("1. Afficher la liste\n");
           printf("2. Rechercher un mot\n");
           printf("3. Trier la liste\n");
           printf("4. Supprimer un mot\n");
           printf("5. Quitter\n");
           scanf("%d",&choix);
           return choix;
       }
/*La fonction main permet de créer une interface entre la machine et l'utilisateur.*/
int main(int argc,char* argv[]){
    int nbdredemots = 0 ;
    int l ;
    struct string * ABR ;
    ABR = NULL ;

    printf("================================================================================\n");
    printf("Veuillez écrire la requête suivante dans le bash : \n-Si vous souhaitez savoir si le mot 'toto' est dans le document :'./main strings.txt recherche_mot toto' \n-Si vous avoir la liste de tous les mots contenant 'k' lettres dans le document : './main strings.txt recherche_lettre k'\n'-Si vous souhaitez afficher la liste des mots présnets dans le document par ordre (dé)croissant de lettre : './main strings.txt tri (de)croissant'\n");
    printf("================================================================================\n");
    
    

    if (argc == 1) {
        fprintf(stderr, "Il me faudrait un nom de fichier ...\n") ;
        return 1 ;
    }
    
    else {
        ABR = lit_fichier(argv[1], ABR, &nbdredemots) ;
        
        if (strcmp(argv[2], "recherche_lettre") == 0 ) {
            if (argc < 4) {
                fprintf(stderr, "Il manque le nombre de lettres...\n") ;
                return 0 ;
            }
            
            else {
                sscanf(argv[3], "%d", &l) ;
                chercher_mot_long(ABR, l) ;
            }
        }

        else if (strcmp(argv[2], "recherche_mot") == 0 ) {
            if (argc < 4) {
                fprintf(stderr, "Il manque le mot à rechercher...\n") ;
                return 0 ;
            }
            
            else {
                chercher_mot(ABR, argv[3]) ;
            }
        }
        
        else if (strcmp(argv[2], "tri") == 0) {
            
            if (argc < 4) {
                fprintf(stderr, "Il manque le type de tri...\n") ;
                return 0 ;
            }
            
            else {
            
                if (strcmp(argv[3], "croissant")) {
                    tri_croissant(ABR) ;
                }
            
                else if (strcmp(argv[3], "decroissant")) {
                    tri_decroissant(ABR) ;
                }
            }
        }
         
    return 0 ;
    }
}


/*Exercice 7
4°
Une des lois implicite de la programmation est que "a fonction achieves only one task".
Et donc en séparant les deux fonctions on est plus clair, concis et élégant.
En fusionnant les deux fonctions cela nous permet d'être plus rapide mais on perd en clarté et nous n'obéissons plus à la loi implicite.

Exercice 8
2°
Nous devons utiliser la longueur du mot.
Si le mot a une longueur plus grande que la racine il sera situé à droite de celle-ci, à gauche sinon.
On prend alors le sous arbre qui a comme racine le fils gauche ou droit de la racine.
On réitère ce procédé jusqu'à trouver les mots qui ont la même longueur que le mot recherché.
La compléxité en temps d'un tel algorithme est en O(log2(n)) ou n est le nombre de noeuds.
*/

