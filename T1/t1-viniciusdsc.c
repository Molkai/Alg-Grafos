#include <stdio.h>
#include <stdlib.h>

//Estrutura utilizada para armazenar as arestas
typedef struct Edge{
	int vertex; //Armazena o vertice adjacente
	struct Edge *next;
} edge;

edge **initGraph(int n, int m); //Funcao utilizada para criar a lista de adjacencia do grafo
edge *crEdge(int x); //Funcao utilizada para criar uma aresta
void addEdge(edge **list, int x); //Funcao utilizada para adicionar um vertice na lista de adjacencia de um vertice
void clean (edge **list, int n); //Funcao utilizada para limpar uma lista de adjacencia apos seu uso
int modifiedBFS(edge **graph, int n); //BFS modificada para testar se um grafo é bipartido
void printGraph(edge **graph, int n);

int main(){

	int n, m; //Variaveis para armazenar o numero de vertices e aestas do grafo
	edge **graph; //Ponteiro para a lista de adjaccencias do grafo

	scanf("%d %d", &n, &m);
	while(!(n == 0 && m == 0)){ //Loop para cada instancia de grafo
		graph = initGraph(n, m);
		if(modifiedBFS(graph, n) == 1) //Utilização da BFS com a saida do programa
			printf("SIM\n");
		else
			printf("NAO\n");
		clean(graph, n); //Limpeza das variaveis alocadas
		free(graph);
		scanf("%d %d", &n, &m);
	}
}

edge **initGraph(int n, int m){
	edge **new; //Variavel para alocar a nova lista de adjacencia
	int x, y; //Varivaeis que guardam os vertices que incidem na aresta
	int i; //Iterador do loop para inicializar os campos da lista de adjacencia

	new = (edge **) malloc (n * sizeof(edge *));
	for(i = 0; i < n; i++)
		new[i] = NULL;
	while(m > 0){
		scanf("%d %d", &x, &y);
		addEdge(&new[x-1], y); //Adiciona o vertice y na lista de adjacencia de x
		addEdge(&new[y-1], x); //Adiciona o vertice x na lista de adjacencia de y
		m--;
	}
	return new;
}

edge *crEdge(int x){
	edge *new; //Variavel utilizada para gerar uma nova aresta na lista de ajacencia

	new = (edge *) malloc (sizeof(edge));
	new->vertex = x; //Vertice adjacente
	new->next = NULL;
	return new;
}

void addEdge(edge **list, int x){
	edge *new; //Variavel para alocar uma nova aresta
	edge *aux = *list; //Variavel auxiliar para manipular uma lista de adjacencia

	new = crEdge(x);
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

int modifiedBFS(edge **graph, int n){
	int *queue, begin = 0, end = 0; //Fila dos vertices a serem analisados e variaveis para marcar seu fim e inicio
	int  i; //Iterador para o loop de inicializaçao de color e group, guarda o vertice atual sedo analisado
	//e iterador do loop que busca um vertice branco (no caso de grafo com mais de uma componente conexa)
	char *color, *group; //Vetor color que marca se um vertice nao foi descoberto, ja foi descoberto ou se ja foi explorado
	//Vetor group que diz em qual particao esta o vertice
	edge *aux; //Ponteiro auxiliar para manipular a lista de adjacencia

	queue = (int *) malloc (n * sizeof(int));
	color = (char *) malloc (n);
	group = (char *) malloc (n);
	queue[end] = 1; //Raiz da busca
	end++;
	for(i = 1; i < n; i++){ //Inicializacao de color e group para todos exceto a raiz
		color[i] = 'b';
		group[i] = '0';
	}
	color[0] = 'c'; //Inicializacao de color e group para a raiz
	group[0] = '1';
	while(begin < n){ //Loop geral da BFS, com alteração que so termina quando analisa todos os vertices do grafo
		i = queue[begin]; //Retira o primeiro elemento da fila
		begin++;
		aux = graph[i - 1];
		while(aux != NULL){ //Loop que explora a lista de adjacencia do primeiro da fila ate o fim
			if(color[aux->vertex - 1] == 'b'){ //Caso ache um vertice nao descoberto na lista de adjacencia
				color[aux->vertex - 1] = 'c'; //Marca vertice como descoberto
				if(group[i-1] == '1') //Define a particao do vertice a partir da particao de seu predescessor
					group[aux->vertex - 1] = '2';
				else
					group[aux->vertex - 1] = '1';
				queue[end] = aux->vertex; //Insere o vertice adjacente na fila
				end++;
			} else if(group[aux->vertex - 1] == group[i - 1]){ //Caso encontre uma aresta que liga dois vertices da mesma particao
				free(queue); //Libera as variaveis alocadas dinamicamente
				free(color);
				free(group);
				return(0); //Retorna que o grafo nao e bipartido
			}
			aux = aux->next;
		}
		color[i - 1] = 'p'; //Marca o vertice atual como explorado
		if(begin == end) //Caso acabe a fila, procura por um vertice que nao foi encontrado ainda (Nova componente conexa)
			for(i = 0; i < n && end == begin; i++)
				if(color[i] == 'b'){ //Caso ache um vertice que nao foi encontrado ainda
					queue[end] = i+1; //Poe a nova raiz na fila
					end++;
					color[i] = 'c'; //Marca a raiz como descoberta e poe ela na particao 1
					group[i] = '1';
				}
	}
	free(queue); //Libera as variaveis alocadas dinamicamente
	free(color);
	free(group);
	return(1); //Retorna que o grafo e bipartido
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
