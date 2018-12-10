#include <stdio.h>
#include <stdlib.h>

//Estrutura utilizada para armazenar as arestas
typedef struct Edge{
	int vertex; //Armazena o vertice adjacente
	struct Edge *next;
    int weight; //Armazena o peso dessa aresta
} edge;

edge **initGraph(int n, int m); //Funcao utilizada para criar a lista de adjacencia do grafo
edge *crEdge(int x, int w); //Funcao utilizada para criar uma aresta
void addEdge(edge **list, int x, int w); //Funcao utilizada para adicionar um vertice na lista de adjacencia de um vertice
void clean (edge **list, int n); //Funcao utilizada para limpar uma lista de adjacencia apos seu uso
int Dijkstra(edge **graph, int n, int root, int k);
int smaller(int *dist, char *isInTree, int n);
void printGraph(edge **graph, int n);

int main(){

	int n, m, k; //Variaveis para armazenar o numero de vertices e aestas do grafo
    int i, j;
	edge **graph; //Ponteiro para a lista de adjaccencias do grafo

	scanf("%d %d %d", &n, &m, &k);
    graph = initGraph(n, m);
    for(i = k; i < n-1; i++){
        printf("%d ", Dijkstra(graph, n, i, k));
    }
    printf("%d\n", Dijkstra(graph, n, i, k));
	clean(graph, n); //Limpeza das variaveis alocadas
	free(graph);

    return 0;
}

edge **initGraph(int n, int m){
	edge **new; //Variavel para alocar a nova lista de adjacencia
	int x, y, w; //Varivaeis que guardam os vertices que incidem na aresta e o peso dela
	int i; //Iterador do loop para inicializar os campos da lista de adjacencia

	new = (edge **) malloc (n * sizeof(edge *));
	for(i = 0; i < n; i++)
		new[i] = NULL;
	while(m > 0){
		scanf("%d %d %d", &x, &y, &w);
		addEdge(&new[x], y, w); //Adiciona o vertice y na lista de adjacencia de x
		addEdge(&new[y], x, w); //Adiciona o vertice x na lista de adjacencia de y
		m--;
	}
	return new;
}

edge *crEdge(int x, int w){
	edge *new; //Variavel utilizada para gerar uma nova aresta na lista de ajacencia

	new = (edge *) malloc (sizeof(edge));
	new->vertex = x; //Vertice adjacente
    new->weight = w; //Peso da aresta
	new->next = NULL;
	return new;
}

void addEdge(edge **list, int x, int w){
	edge *new; //Variavel para alocar uma nova aresta
	edge *aux = *list; //Variavel auxiliar para manipular uma lista de adjacencia

	new = crEdge(x, w);
	if(*list == NULL || aux->vertex > x){ //Caso a lista esteja vazia, ou a nova aresta tenha um vertice menor que o primeiro da lista
		new->next = aux;
		*list = new;
	} else { //Caso a nova aresta nao seja colocada no começo da lista
		while(aux->next != NULL && aux->next->vertex < x){
			aux = aux->next;
		}
		new->next = aux->next;
		aux->next = new;
	}
}

void clean (edge **list, int n){
	edge *aux, *aux2; //Variaveis auxiliares para limpar a lista de adjacencia
	int i; //Iterador do loop que limpa a lista de adjacencia de cada vertice

	for(i = 0; i < n; i++){
		aux = list[i]; //list[i] é o ponteiro para a lista de adjacencia do vertice i+1
		while(aux != NULL){
			aux2 = aux->next;
			free(aux);
			aux = aux2;
		}
	}
}

int Dijkstra(edge **graph, int n, int root, int k){
    int dist[n], i, small = -1, vertex;
    edge *aux;
    char isInTree[n];

    for(i = 0; i < n; i++){
        dist[i] = -1;
        isInTree[i] = 'n';
    }
    dist[root] = 0;
    isInTree[root] = 's';
    i = root;
    while(i != -1){
        aux = graph[i];
        while(aux != NULL){
            if(isInTree[aux->vertex] == 'n' && dist[i] != -1)
                if(dist[aux->vertex] == -1 || (dist[aux->vertex] > dist[i] + aux->weight))
                    dist[aux->vertex] = dist[i] + aux->weight;
            aux = aux->next;
        }
        i = smaller(dist, isInTree, n);
        if(i < k)
            return(i);
    }
}

int smaller(int *dist, char *isInTree, int n){
    int smalldist = -1, smallvertex, i;

    for(i = 0; i < n; i++){
        if(isInTree[i] == 'n'){
            if(smalldist == -1){
                smalldist = dist[i];
                smallvertex = i;
            } else if(smalldist > dist[i] && dist[i] != -1){
                smalldist = dist[i];
                smallvertex = i;
            }
        }
    }
    if(smalldist == -1){
        return -1;
    } else {
        isInTree[smallvertex] = 'y';
        return smallvertex;
    }
}

void printGraph(edge **graph, int n){
	edge *aux;
	int i;

	for(i = 0; i < n; i++){
		printf("Vertex %d ----> ", i+1);
		aux = graph[i];
		while(aux != NULL){
			printf("[%d %d]", aux->vertex, aux->weight);
			aux = aux->next;
		}
		printf("\n");
	}
}

