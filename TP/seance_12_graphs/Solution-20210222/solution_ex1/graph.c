#include "graph.h"

void graphe_liste_adjacence(Graphe* G, const char* grapheFileName)
{
	FILE *fp;
	fp = fopen(grapheFileName, "r");
	
	if (fp != NULL) {

		int nb_sommets, nb_arcs, u, v;

		fscanf(fp, "%d %d", &nb_sommets, &nb_arcs);
		
		G->nb_sommets			= nb_sommets;
		G->liste_successeurs	= (Sommet**) malloc(nb_sommets*sizeof(Sommet*)); 

		for (int i = 0; i < nb_sommets; i++) 
			G->liste_successeurs[i] = NULL;
		
		for (int i = 0; i < nb_arcs; i++) 
		{
			fscanf(fp, "%d %d", &u, &v);
			Sommet* s = (Sommet*) malloc(sizeof(Sommet));  
			u --; // gestion du decalage entre les numeros des sommmets et leur index dans le tableau
			v --; // gestion du decalage entre les numeros des sommmets et leur index dans le tableau
			s->isucceseur				= v;
			s->successeur				= G->liste_successeurs[u];
			G->liste_successeurs[u]	= s;
		}
	}
	else printf("Le fichier n'a pas été trouvé.");
	fclose(fp);
}


void parcours_largeur(Graphe* G, int sommet_id) 
{
	int* marque = (int*) malloc(G->nb_sommets * sizeof(int));
	
	for (int i = 0; i < G->nb_sommets; i++)
		marque[i] = 0;

	sommet_id--; // gestion du decalage entre les numeros des sommmets et leur index dans le tableau
	marque[sommet_id] = 1;
	
	File F = Initialiser();
	enfiler(&F, sommet_id);

	while( !est_vide(&F) ) 
	{ 
		int sommet_out = defiler(&F);
		Sommet* courant = G->liste_successeurs[sommet_out];
		while (courant != NULL) 
		{
			if (marque[courant->isucceseur] != 1)
			{
				marque[courant->isucceseur] = 1; 
				printf(" (%d) ", courant->isucceseur +1);			
				enfiler(&F, courant->isucceseur);	
			}
			courant = courant->successeur;
		}
	} 
} 

void affichage_graphe_liste_adjacence(Graphe* G) 
{	
	for(int i = 0; i < G->nb_sommets; i++) 
	{
		printf("Sommet %d : ", i+1);

		Sommet* courant = G->liste_successeurs[i];

		while(courant != NULL)
		{
			printf("%d, ", courant->isucceseur + 1);
			courant = courant->successeur;
		} 
		printf("\n");
	}
}

