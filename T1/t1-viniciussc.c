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
		addEdge(new[x-1], y);
		addEdge(new[y-1], x);
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