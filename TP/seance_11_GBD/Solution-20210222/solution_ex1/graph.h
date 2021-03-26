#ifndef GRAPH_H
#define GRAPH_H

#include "pFile.h"

typedef struct _sommet {
	int		isucceseur;
	struct	_sommet* successeur;
} Sommet;

typedef struct {
	int		nb_sommets;
	Sommet** liste_successeurs;
} Graphe;

void graphe_liste_adjacence(Graphe* G, const char* grapheFileName);
void affichage_graphe_liste_adjacence(Graphe* G); 
void parcours_largeur(Graphe* G, int sommet_id);

#endif 