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
int modifiedBFS(edge **graph, int n);
void printGraph(edge **graph, int n);

int main(){

	int n, m;
	edge **graph;

	scanf("%d %d", &n, &m);
	while(n != 0 && m != 0){
		graph = initGraph(n, m);
		printGraph(graph, n);
		if(modifiedBFS(graph, n) == 1)
			printf("SIM\n");
		else
			printf("NAO\n");
		clean(graph, n);
		free(graph);
		scanf("%d %d", &n, &m);
	}
}

edge **initGraph(int n, int m){
	edge **new;
	int x, y, i;

	new = (edge **) malloc (n * sizeof(edge *));
	for(i = 0; i < n; i++)
		new[i] = NULL;
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
}

int modifiedBFS(edge **graph, int n){
	int *queue, begin = 0, end = 0, i;
	char *color, *group;
	edge *aux;

	queue = (int *) malloc (n * sizeof(int));
	color = (char *) malloc (n);
	group = (char *) malloc (n);
	queue[end] = 1;
	end++;
	for(i = 1; i < n; i++){
		color[i] = 'b';
		group[i] = '0';
	}
	color[0] = 'c';
	group[0] = '1';
	while(begin < n){
		i = queue[begin];
		begin++;
		aux = graph[i - 1];
		while(aux != NULL){
			if(color[aux->vertex - 1] == 'b'){
				color[aux->vertex - 1] = 'c';
				if(group[i-1] == '1')
					group[aux->vertex - 1] = '2';
				else
					group[aux->vertex - 1] = '1';
				queue[end] = aux->vertex;
				end++;
			} else if(group[aux->vertex - 1] == group[i - 1]){
				free(queue);
				free(color);
				free(group);
				return(0);
			}
			aux = aux->next;
		}
		color[i - 1] = 'p';
		if(begin == end)
			for(i = 0; i < n; i++)
				if(color[i] == 'b'){
					queue[end] == i+1;
					end++;
				}
	}
	free(queue);
	free(color);
	free(group);
	return(1);
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