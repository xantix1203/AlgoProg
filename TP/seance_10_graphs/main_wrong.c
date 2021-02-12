/*-----------------------------------------------------------------------------------------------

Load an undirected graph from a given file into an adjacency matrix.

Version: Wrong (for debugging)
-----------------------------------------------------------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"

int** 	read_graph_from_file(const char* file_name, int nb_nodes, int nb_edges);
void 	print_adjacency_matrix(int** adjacency_matrix, int nb_nodes);

int main()
{
	const char*	file_name = "graph_10_13.txt";
	int		nb_nodes, nb_edges;
	int** 		adjacency_matrix = read_graph_from_file(file_name, nb_nodes, nb_edges);

	printf("Adjacency matrix: \n" );
	print_adjacency_matrix(adjacency_matrix, nb_nodes);

	return 0;
}

int** read_graph_from_file(const char* file_name, int nb_nodes, int nb_edges)
{
	FILE *fp = fopen(file_name, "r");
	fscanf(fp, "%d %d", &nb_nodes, &nb_edges);

 	int** adjacency_matrix = (int**) malloc(nb_nodes*sizeof(int*));

	for (int i = 0; i < nb_nodes; i++)
	{
		adjacency_matrix[i] = (int*) malloc(nb_nodes*sizeof(int));
		for (int j = 0; j < nb_nodes; j++)
			adjacency_matrix[i][j] = 0;
	}

	for (int i = 0; i < nb_edges; i ++)
	{
		int u, v;
		fscanf(fp, "%d %d", &u, &v);
		adjacency_matrix[u-1][v-1] = 1;
		adjacency_matrix[v-1][u-1] = 1;
	}

	fclose(fp);
	return adjacency_matrix;
}

void print_adjacency_matrix(int** adjacency_matrix, int nb_nodes)
{
	for (int i = 0; i < nb_nodes; i++)
	{
		for (int j = 0; j < nb_nodes; j++)
			printf("%d ", adjacency_matrix[i][j]);
		printf("\n" );
	}
}
