#ifndef GRAFO_H
#define GRAFO_H


#define MAX_VERTICES 100

typedef struct ArestaLSE
{
    int destino;
    double confiabilidade; 
    struct ArestaLSE *prox;
} ArestaLSE;


typedef struct
{
    int numVertices;
    ArestaLSE *adj[MAX_VERTICES]; 
} Grafo;


typedef struct
{
    double conf[MAX_VERTICES];    
    int anterior[MAX_VERTICES];   
    int alcancavel[MAX_VERTICES]; 
} ResultadoCaminho;


void inicializarGrafo(Grafo *g, int numVertices);

void adicionarAresta(Grafo *g, int origem, int destino, double r);

void liberarGrafo(Grafo *g);


void dijkstra(Grafo *g, int origem, ResultadoCaminho *res);


void reconstruirCaminho(ResultadoCaminho *res, int origem, int destino,
                        int *caminho, int *tamanho);

void imprimirCaminho(ResultadoCaminho *res, int origem, int destino);


void imprimirGrafo(Grafo *g);


void pausarTerminal();
void limparTerminal();

#endif
