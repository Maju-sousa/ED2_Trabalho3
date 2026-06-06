#include "Torre_2.h"

Grafo *criarGrafo(int qtdVertices)
{
    Grafo *G;
    int i;

    G = (Grafo *)malloc(sizeof(Grafo));

    G->qtdVertices = qtdVertices;

    G->vertices = (Vertice *)calloc(qtdVertices, sizeof(Vertice));

    for (i = 0; i < qtdVertices; i++)
    {
        G->vertices[i].lista = NULL;
    }

    return G;
}

void liberarGrafo(Grafo **G)
{
    int i;

    if (*G != NULL)
    {
        for (i = 0; i < (*G)->qtdVertices; i++)
        {
            NoAdj *aux = (*G)->vertices[i].lista;

            while (aux != NULL)
            {
                NoAdj *temp = aux;
                aux = aux->prox;
                free(temp);
            }

            (*G)->vertices[i].lista = NULL;
        }

        free((*G)->vertices);
        (*G)->vertices = NULL;

        free(*G);
        *G = NULL;
    }
}

void gerarVertices(Grafo *G)
{
    int i;

    for (i = 0; i < TAM; i++)
    {
        indiceParaEstado(i, G->vertices[i].discos);
    }
}

void gerarArestas(Grafo *G)
{
    int estado[DISCOS];
    int novoEstado[DISCOS];

    int i;
    int j;
    int disco;
    int origem;
    int destino;
    int topo;
    int indiceDestino;

    for (i = 0; i < TAM; i++)
    {
        indiceParaEstado(i, estado);

        for (origem = 1; origem <= PINOS; origem++)
        {
            topo = -1;

            for (disco = 0; disco < DISCOS; disco++)
            {
                if (estado[disco] == origem && topo == -1)
                {
                    topo = disco;
                }
            }

            if (topo != -1)
            {
                for (destino = 1; destino <= PINOS; destino++)
                {
                    if (origem != destino)
                    {
                        if (movimentoValido(estado, topo, destino))
                        {
                            for (j = 0; j < DISCOS; j++)
                            {
                                novoEstado[j] = estado[j];
                            }

                            novoEstado[topo] = destino;

                            indiceDestino = estadoParaIndice(novoEstado);

                            if (i < indiceDestino)
                            {
                                inserirAresta(G, i, indiceDestino, 1);
                                inserirAresta(G, indiceDestino, i, 1);
                            }
                        }
                    }
                }
            }
        }
    }
}

int estadoParaIndice(int discos[])
{
    int indice;
    int base;
    int i;

    indice = 0;
    base = 1;

    for (i = 0; i < DISCOS; i++)
    {
        indice += (discos[i] - 1) * base;
        base *= PINOS;
    }

    return indice;
}

void indiceParaEstado(int indice, int discos[])
{
    int i;

    for (i = 0; i < DISCOS; i++)
    {
        discos[i] = (indice % PINOS) + 1;
        indice /= PINOS;
    }
}
int movimentoValido(int estado[], int disco, int destino)
{
    int i;
    int topoDestino;
    int valido;

    topoDestino = -1;
    valido = 0;

    for (i = 0; i < DISCOS; i++)
    {
        if (estado[i] == destino && topoDestino == -1)
        {
            topoDestino = i;
        }
    }

    if (topoDestino == -1)
    {
        valido = 1;
    }
    else
    {
        if (disco < topoDestino)
        {
            valido = 1;
        }
    }

    return valido;
}

// Lista de Adjacencia
void inserirAresta(Grafo *G, int origem, int destino, int peso)
{
    NoAdj *novo;

    novo = (NoAdj *)malloc(sizeof(NoAdj));

    novo->destino = destino;
    novo->peso = peso;

    novo->prox = G->vertices[origem].lista;

    G->vertices[origem].lista = novo;
}

void imprimirVertice(Grafo *G, int indice)
{
    int i;

    printf("Estado %3d = (", indice);

    for (i = 0; i < DISCOS; i++)
    {
        printf("%d", G->vertices[indice].discos[i]);

        if (i < DISCOS - 1)
        {
            printf(",");
        }
    }

    printf(")\n");
}

void imprimirListaAdjacencia(Grafo *G)
{
    int i;
    NoAdj *aux;

    printf("\nLista de Adjacencia:\n\n");

    for (i = 0; i < G->qtdVertices; i++)
    {
        printf("%3d -> ", i);

        aux = G->vertices[i].lista;

        while (aux != NULL)
        {
            printf("%d ", aux->destino);
            aux = aux->prox;
        }

        printf("\n");
    }
}

//// DIJKSTRA
void Dijkstra(Grafo *G, int origem, int *dist, int *anterior)
{
    int *visitado;
    int i;
    int u;
    int v;
    int novaDist;

    visitado = (int *)calloc(G->qtdVertices, sizeof(int));

    for (i = 0; i < G->qtdVertices; i++)
    {
        dist[i] = INF;
        anterior[i] = -1;
    }

    dist[origem] = 0;

    for (i = 0; i < G->qtdVertices; i++)
    {
        u = -1;

        for (v = 0; v < G->qtdVertices; v++)
        {
            if (!visitado[v] && (u == -1 || dist[v] < dist[u]))
            {
                u = v;
            }
        }

        if (u != -1 && dist[u] != INF)
        {
            visitado[u] = 1;

            NoAdj *aux;

            aux = G->vertices[u].lista;

            while (aux != NULL)
            {
                v = aux->destino;

                if (!visitado[v])
                {
                    novaDist = dist[u] + aux->peso;

                    if (novaDist < dist[v])
                    {
                        dist[v] = novaDist;
                        anterior[v] = u;
                    }
                }

                aux = aux->prox;
            }
        }
    }

    free(visitado);
}

void imprimir_dijkstra(Grafo *G, int origem, int destino)
{
    int *dist;
    int *anterior;
    double tempo;

    LARGE_INTEGER ini;
    LARGE_INTEGER fim;
    LARGE_INTEGER frequencia;

    dist = (int *)malloc(G->qtdVertices * sizeof(int));
    anterior = (int *)malloc(G->qtdVertices * sizeof(int));

    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&ini);

    Dijkstra(G, origem, dist, anterior);

    QueryPerformanceCounter(&fim);

    tempo = calcularTempoNano(ini, fim, frequencia);

    printf("\n=== DIJKSTRA ===\n");

    printf("\nEstado inicial:\n");
    imprimirVertice(G, origem);

    printf("\nEstado final:\n");
    imprimirVertice(G, destino);

    if (dist[destino] == INF)
    {
        printf("\nNao existe caminho.\n");
    }
    else
    {
        printf("\nMenor caminho encontrado: %d movimentos\n", dist[destino]);

        printf("\nSequencia de estados:\n");
        imprimirCaminho(G, anterior, destino);
    }

    printf("\nTempo de execucao: %.2f nanossegundos\n", tempo);

    free(dist);
    free(anterior);
}

void imprimirCaminho(Grafo *G, int anterior[], int destino)
{
    if (destino == -1)
    {
        return;
    }

    imprimirCaminho(G, anterior, anterior[destino]);
    imprimirVertice(G, destino);
}

double calcularTempoNano(LARGE_INTEGER inicio, LARGE_INTEGER fim, LARGE_INTEGER frequencia)
{
    return (double)(fim.QuadPart - inicio.QuadPart) * 1e9 / frequencia.QuadPart;
}
