#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
	int vertex;
	struct Edge *next;
} edge;

edge **initGraph(int n, int m);
edge *crEdge(int x);
void addEdge(edge **list, int x);
void clean (edge **list, int n);
void printGraph(edge **graph, int n);

int main(){

	int n, m;
	edge **graph;

	scanf("%d %d", &n, &m);
	while(n != 0 && m != 0){
		graph = initGraph(n, m);
		
		//printGraph(graph, n);
		clean(graph, n);
		scanf("%d %d", &n, &m);
	}
}

edge **initGraph(int n, int m){
	edge **new;
	int x, y;

	new = (edge **) malloc (n * sizeof(edge *));
	while(m > 0){
		scanf("%d %d", &x, &y);
		addEdge(&new[x-1], y);
		addEdge(&new[y-1], x);
		m--;
	}
	return new;
}

edge *crEdge(int x){
	edge *new;

	new = (edge *) malloc (sizeof(edge));
	new->vertex = x;
	new->next = NULL;
	return new;
}

void addEdge(edge **list, int x){
	edge *new, *aux = *list;

	new = crEdge(x);
	if(*list == NULL || aux->vertex > x){
		new->next = aux;
		*list = new;
	} else {
		while(aux->next != NULL && aux->next->vertex < x){
			aux = aux->next;
		}
		new->next = aux->next;
		aux->next = new;
	}
}

void clean (edge **list, int n){
	edge *aux, *aux2;
	int i;

	for(i = 0; i < n; i++){
		aux = list[i];
		while(aux != NULL){
			aux2 = aux->next;
			free(aux);
			aux = aux2;
		}
	}
	free(list);
}

void printGraph(edge **graph, int n){
	edge *aux;
	int i;

	for(i = 0; i < n; i++){
		printf("Vertex %d ----> ", i+1);
		aux = graph[i];
		while(aux != NULL){
			printf("%d ", aux->vertex);
			aux = aux->next;
		}
		printf("\n");
	}
}