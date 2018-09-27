#include <stdio.h>

typedef struct Edge{
	int vertex;
	struct Edge *next;
} edge;

edge **initGraph(int n, int m);

int main(){

	int n, m;
	edge **graph;

	scanf("%d %d", &n, &m);
	while(n != 0 && m != 0){
		graph = initGraph(n, m);
		scanf("%d %d", &n, &m);
	}
}

edge **initGraph(int n, int m){
	edge **new;

	new = (edge **) malloc (n * sizeof(edge *));
	while(m > 0){

		m--;
	}
}

edge *crEdge(int x){
	edge *new;

	new = (edge *) malloc (sizeof(edge));
	new->vertex = x;
	new->next = NULL;
	return new;
}