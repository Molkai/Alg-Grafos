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
void DFS_aux(edge **graph, char *cor, int *maior, int *horas, int n);
void DFS(edge **graph, int u, char *cor, int *maior, int *horas, int *tempo);
void printGraph(edge **graph, int n);

int main(){

    int n, m, i, *horas, maior;
    edge **graph; //Ponteiro para a lista de adjaccencias do grafo
    char *cor;

    scanf("%d %d", &n, &m);
    while(!(n == 0 && m == 0)){ //Loop para cada instancia de grafo
        horas = (int *) malloc (n * sizeof(int));
        for(i = 0; i < n; i++)
            scanf("%d", &horas[i]);
        graph = initGraph(n, m);
        DFS_aux(graph, cor, &maior, horas, n);
        printf("%d\n",  maior);
        clean(graph, n); //Limpeza das variaveis alocadas
        free(graph);
        free(horas);
        scanf("%d %d", &n, &m);
    }
}

edge **initGraph(int n, int m){
    edge **new; //Variavel para alocar a nova lista de adjacencia
    int x, y, z; //Varivaeis que guardam os vertices que incidem na aresta
    int i; //Iterador do loop para inicializar os campos da lista de adjacencia

    new = (edge **) malloc (n * sizeof(edge *));
    for(i = 0; i < n; i++)
        new[i] = NULL;
    while(m > 0){
        scanf("%d %d", &x, &y);
        addEdge(&new[x], y); //Adiciona o vertice y na lista de adjacencia de x
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

void DFS_aux(edge **graph, char *cor, int *maior, int *horas, int n){
    int i;
    int *tempo = (int *) malloc (n * sizeof(int));

    cor = (char *) malloc (n);
    for(i = 0; i < n; i++){
        cor[i] = 'b';
        tempo[i] = 0;
    }
    *maior = 0;
    for(i = 0; i < n; i++)
        if(cor[i] == 'b')
            DFS(graph, i, cor, maior, horas, tempo);
    free(cor);
}

void DFS(edge **graph, int u, char *cor, int *maior, int *horas, int *tempo){
    edge *aux = graph[u];

    cor[u] = 'c';
    while(aux != NULL){
        if(cor[aux->vertex] ==  'b')
            DFS(graph, aux->vertex, cor, maior, horas, tempo);
            if(tempo[aux->vertex] + horas[u] > tempo[u])
                tempo[u] = tempo[aux->vertex] + horas[u];
        aux = aux->next;
    }
    if(tempo[u] == 0)
        tempo[u] = horas[u];
    if(tempo[u] > *maior)
        *maior = tempo[u];
    cor[u] = 'p';
}

void printGraph(edge **graph, int n){
    edge *aux;
    int i;

    for(i = 0; i < n; i++){
        printf("Vertex %d ----> ", i);
        aux = graph[i];
        while(aux != NULL){
            printf("%d ", aux->vertex);
            aux = aux->next;
        }
        printf("\n");
    }
}
