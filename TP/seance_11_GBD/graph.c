#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

void graph(Graphe* G, const char* grapheFileName){
  FILE *fp;
  fp = fopen(grapheFileName, "r");
    if (fp != NULL){
      int nb_sommets, nb_arcs, u, v;
      fscanf(fp, "%d %d", &nb_sommets, &nb_arcs);
      G->nb_sommets = nb_sommets;
      G->liste_successeurs = (Sommet**) malloc(nb_sommets*sizeof(Sommet*));
      for (int i = 0; i<nb_sommets; i++)
        G->liste_successeurs[i] = NULL;
      for (int i = 0; i < nb_arcs; i++){
  			fscanf(fp, "%d %d", &u, &v);
  			Sommet* s = (Sommet*) malloc(sizeof(Sommet));
        u --;
        v--;
        s->isucceseur = v;
        s->successeur = G->liste_successeurs[u];
        G->liste_successeurs[u] = s;
      }
    }
    else printf("Le fichier n'a pas été trouvé.");
  	fclose(fp);
}

int main(){
  return 0;
}
