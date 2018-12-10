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
int Dijkstra(edge **graph, int n, int root, int k); //Algoritmo de Dijkstra com algumas modificações
int smaller(int *dist, char *isInTree, int n); //Função que retorna o vertice com a atual menor distancia em relação à raíz
void printGraph(edge **graph, int n); //Função utilizada apenas para testes

int main(){

	int n, m, k; //Variaveis para armazenar o numero de vertices, numero de arestas do grafo e o divisor entre distribuidoras e estufas
    int i; //Iterador para execução do Dijkstra n-k vezes
	edge **graph; //Ponteiro para a lista de adjaccencias do grafo

	scanf("%d %d %d", &n, &m, &k);
    graph = initGraph(n, m);
    for(i = k; i < n-1; i++)
        printf("%d ", Dijkstra(graph, n, i, k)); //Executa o Dijkstra que já retorna a estufa mais proxima da i-ésima distribuidora
    printf("%d\n", Dijkstra(graph, n, i, k)); //Executa o Dijkstra para a ultima distribuidora (Colocado para fora do loop, pois tem uma impressão diferente das outras)
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
		new[i] = NULL; //Inicializa todas as listas como vazias
	while(m > 0){
		scanf("%d %d %d", &x, &y, &w);
		addEdge(&new[x], y, w); //Adiciona o vertice y na lista de adjacencia de x com peso w na aresta
		addEdge(&new[y], x, w); //Adiciona o vertice x na lista de adjacencia de y com peso w na aresta
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

void addEdge(edge **list, int x, int w){ //Insere na lista de adjacencia de forma ordenada pelos vertices adjacentes
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
    int dist[n]; //Vetor que salva as distancias atuais de root ate o i-ésimo vertice do vetor
    int i; //Iterador geral para os loops da função
    edge *aux; //Apontador para a lista de adjacencia do vertice sendo atualmente analisado
    char isInTree[n]; //Vetor para saber quais vertices ja foram analisados

    for(i = 0; i < n; i++){ //Inicializa com distancia infinita e que não foi analisado ainda para todos os vertices
        dist[i] = -1;
        isInTree[i] = 'n';
    }
    dist[root] = 0; //Inicializa a raíz como distancia 0
    isInTree[root] = 's'; //Inicializa como se a raíz jś tivesse sido analisada
    i = root; //Coloca a raíz como primeiro vertice a ser analisado
    while(i != -1){ //Executa o loop enquanto houver um vertice não analisado
        aux = graph[i]; //Aponta aux para a lista de adjacencia do vertice sendo analisado atualmente
        while(aux != NULL){ //Enquanto tiver uma ajacencia não analisada executa esse loop
            if(isInTree[aux->vertex] == 'n' && dist[i] != -1) //Se o vertice adjacente não foi analisado ainda
                if(dist[aux->vertex] == -1 || (dist[aux->vertex] > dist[i] + aux->weight)) //Se a distancia dele atualmente for maior que a distancia ate i somada ao peso da aresta, muda a sua distancia
                    dist[aux->vertex] = dist[i] + aux->weight;
            aux = aux->next;
        }
        i = smaller(dist, isInTree, n); // Chama função smaller para saber o proximo menor vertice
        if(i < k) //Caso o proximo menor vertice for uma estufa retorna ele, pois essa é a estufa mais proxima do centro atual
            return(i);
    }
}

int smaller(int *dist, char *isInTree, int n){
    int smalldist = -1, smallvertex; //Variaveis que guardam a menor distancia e o menor vertice que nao foi analisado
    int i; //Iterador de loops da função

    for(i = 0; i < n; i++){
        if(isInTree[i] == 'n'){ //Caso o vertice i não foi analisado ainda
            if(smalldist == -1){ //se a menor distancia atual for infinita
                smalldist = dist[i];
                smallvertex = i;
            } else if(smalldist > dist[i] && dist[i] != -1){ //Se a menor distancia for maior que a distancia de i
                smalldist = dist[i];
                smallvertex = i;
            }
        }
    }
    if(smalldist == -1){ //Caso não exista um vertice não analisado ainda e qualquer outro vertice não esta conectando a componente sendo analisada
        return -1;
    } else {
        isInTree[smallvertex] = 'y'; //Marca o vertice com menor distancia como analisado e retorna ele
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

