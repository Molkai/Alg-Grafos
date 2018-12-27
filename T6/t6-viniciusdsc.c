#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **initGraph(int n); //Funcao utilizada para inicializar a matriz de distancias
void clean (double **dist, int n); //Funcao utilizada para limpar uma matriz de distancias apos seu uso
char FloydWarshall(double **dist, int n);

int main(){

	int n; //Variaveis para armazenar o numero de moedas envolvidas
    double **dist; //Vetor para salvar as distancias

	scanf("%d", &n);
    while(n > 0){
        dist = initGraph(n);

        printf("%c\n", FloydWarshall(dist, n));

        clean(dist, n); //Limpeza das variaveis alocadas
    	free(dist);
        scanf("%d", &n);
    }

    return 0;
}

double **initGraph(int n){
	double x; //Varivael que guarda o valor de conversão da moeda i para a moeda j
	int i, j; //Iteradores do loop para inicializar as arestas (conversões)
    double **dist;

	dist = (double **) malloc (n * sizeof(double *));
    for(i = 0; i < n; i++)
        dist[i] = (double *) malloc (n * sizeof(double));
	for(i = 0; i < n; i++)
        for(j = 0; j < n; j++){
    		scanf("%lf", &x);
            dist[i][j] = -log(x);
	   }
	return dist;
}

void clean (double **dist, int n){
	int i; //Iterador do loop que limpa a lista de adjacencia de cada vertice

	for(i = 0; i < n; i++)
		free(dist[i]);
}

char FloydWarshall(double **dist, int n){
    int i, j, k;

    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    for(i = 0; i < n; i++)
        if(dist[i][i] < 0) //Se tiver um ciclo negativo (alguma distancia menor que 0 para ir de um vertice ate ele mesmo)
            return 'S'; //Significa que tem como ganhar dinheiro em conversões
    return 'N'; //Se não tiver nenhum ciclo negativo

}

