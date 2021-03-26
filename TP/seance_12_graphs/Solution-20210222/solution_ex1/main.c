#include <stdio.h>
#include <stdlib.h>

#include "graph.h"


int main()
{
	const char* graphFileName = "graph_10_13.txt";
	Graphe G_liste;
	graphe_liste_adjacence(&G_liste, graphFileName);

	printf("Graphe G (liste d'adjacence): \n" );
	affichage_graphe_liste_adjacence(&G_liste);	
	
	/* Liste des sommets visités dans l'ordre dans lequel ils sont visités */
	printf("\nParcours en largeur du graphe G a partir du sommet 3 : " );
	parcours_largeur(&G_liste, 2);
		
//	initialiser_graphe(&G_liste);
//	printf("\nParcours en largeur du graphe G a partir du sommet 8 : " );
//	parcours_largeur(&G_liste, 7);

	return 0;
}


