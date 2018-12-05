#include <stdio.h>
#include <stdlib.h>

//Estrutura utilizada para armazenar as arestas
typedef struct Edge{
	int vertex; //Armazena o vertice adjacente
	struct Edge *next;
    int weight; //Armazena o peso dessa aresta
} edge;

edge **initGraph(int n, int m, int **dist); //Funcao utilizada para criar a lista de adjacencia do grafo
edge *crEdge(int x, int w); //Funcao utilizada para criar uma aresta
void addEdge(edge **list, int x, int w); //Funcao utilizada para adicionar um vertice na lista de adjacencia de um vertice
void clean (edge **list, int n); //Funcao utilizada para limpar uma lista de adjacencia apos seu uso
void FloydWarshall(edge **graph, int n, int **dist);
void printGraph(edge **graph, int n);

int main(){

	int n, m, k; //Variaveis para armazenar o numero de vertices e aestas do grafo
    int i, j, menorDist;
    int **dist, *resp;
	edge **graph; //Ponteiro para a lista de adjaccencias do grafo

	scanf("%d %d %d", &n, &m, &k);
    dist = (int **) malloc(n * sizeof(int *));
    resp = (int *) malloc(n * sizeof(int *));
    for(i = 0; i < n; i++){
        dist[i] = (int *) malloc(n * sizeof(int));
        for(j = 0; j < n; j++){
            if(i != j)
                dist[i][j] = -1;
            else
                dist[i][j] = 0;
        }
    }
	graph = initGraph(n, m, dist);
    FloydWarshall(graph, n, dist);
    for(i = k; i < n; i++)
        for(j = 0, menorDist = -1; j < k; j++)
            if(menorDist == -1 || dist[i][j] < menorDist){
                menorDist = dist[i][j];
                resp[i] = j;
            }
    for(i = k; i < n; i++){
        if(i == n-1)
            printf("%d\n", resp[i]);
        else
            printf("%d ", resp[i]);
    }
	clean(graph, n); //Limpeza das variaveis alocadas
	free(graph);
}

edge **initGraph(int n, int m, int **dist){
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
        dist[x][y] = w;
        dist[y][x] = w;
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

void FloydWarshall(edge **graph, int n, int **dist){
    int i, j, k;

    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(dist[i][k] != -1 && dist[k][j] != -1)
                    if(dist[i][j] == -1 || dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                        printf("%d %d %d\n", i, j, k);
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
