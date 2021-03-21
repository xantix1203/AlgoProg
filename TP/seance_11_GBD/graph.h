#ifndef GRAPH_H
#define GRAPH_H

typedef struct _sommet {
  int isucceseur;
  struct _sommet* successeur;
}Sommet;

typedef struct {
  int		nb_sommets;
	Sommet** liste_successeurs;
} Graphe;

#endif
