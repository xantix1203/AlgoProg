#include <stdio.h>

typedef struct Node{
  int value;
  struct Node* neighbours;
} Node;

typedef struct Graph{
  Node head;
} Graph;

int main() {
  const char*	file_name = "graph_10_13.txt";
	int		nb_nodes, nb_edges;
	nb_nodes = 10;
	nb_edges = 15;
  return 0;
}
