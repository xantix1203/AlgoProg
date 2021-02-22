#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int marque;
} Sommet;

typedef struct {
	int 	nb_sommets;
	Sommet 	*tabSomm;
	int	**matrice_adjacence;
} Graphe;

void visiter(Graphe G, int sommet);
void profondeur(Graphe G, int sommet);
void affichage_graphe (Graphe G);

int main() {

	FILE *fp;
	fp = fopen("graph_10_13.txt", "r");
	
	if (fp != NULL) {
		
		int nb_sommets, nb_arcs, u, v;
		Graphe G;

		fscanf(fp, "%d %d", &nb_sommets, &nb_arcs);
		
		G.nb_sommets 		= nb_sommets;
		G.tabSomm 		= (Sommet *) malloc(nb_sommets*sizeof(Sommet*));
		G.matrice_adjacence 	= (int **) malloc (nb_sommets*sizeof(int*));

		for (int i = 0; i < nb_sommets; i++) 			
			G.matrice_adjacence[i] = (int*) malloc (nb_sommets*sizeof(int)); 

		for (int i = 0; i < nb_sommets; i++) 
			for (int j = 0; j < nb_sommets; j++)
				G.matrice_adjacence[i][j] = 0; 
		
		for (int i = 0; i < nb_arcs; i ++) 
		{
			fscanf(fp, "%d%d", &u, &v);
			G.matrice_adjacence[u-1][v-1] = 1;
		}

		printf("Soit le graphe G (matrice d'adjacence) : \n" );
		affichage_graphe(G);
		
		/* Liste des sommets visités dans l'ordre dans lequel ils sont visités */

		printf("\nParcours en profondeur du graphe G à partir du sommet 5 : " );
		profondeur(G, 4);
		printf("\nParcours en profondeur du graphe G à partir du sommet 7 : " );
		profondeur(G, 6);

		fclose(fp);
	}
	else printf("Le fichier n'a pas été trouvé.");

	return 0;
}


void visiter(Graphe G, int sommet) 
{
	printf("%d, ", sommet + 1);

	G.tabSomm[sommet].marque = 1;			/* Marquer sommet */

	for (int i = 0; i < G.nb_sommets; i++) {	/* Parcourir les successeurs */
		if ( (G.matrice_adjacence[sommet][i] == 1) && (G.tabSomm[i].marque == 0) )
		visiter(G, i);
	}
}

/* G est le graphe, et sommet est le numéro du sommet
dans le tableau de sommet de G */

void profondeur(Graphe G, int sommet) 
{
	for (int i = 0; i < G.nb_sommets; i++)	/* Marquer tous les sommets à zéro */
		G.tabSomm[i].marque = 0;
		
	visiter(G, sommet);			/* Appel de visiter recursivement */
}

void affichage_graphe (Graphe G) 
{

	for (int i = 0; i < G.nb_sommets; i++) 
	{
		for (int j = 0; j < G.nb_sommets; j++)
			printf("%d ", G.matrice_adjacence[i][j]); 
		printf("\n" ); 
	}
}
