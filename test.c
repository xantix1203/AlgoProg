#include <stdio.h>

int main() {
  int nb_nodes;
	int nb_edges;
  const char*	file_name = "graph_10_13.txt";
	FILE *fp = fopen(file_name, "r");
	fscanf(fp, "%d %d", &nb_nodes, &nb_edges);
  printf("%d %d\n", nb_nodes, nb_edges);
  return 0;
}
