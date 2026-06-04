
#include "Torre.h"
 
Grafo *criarGrafo(int qtdVertices)
{
    Grafo *G;
    int i;

    G = (Grafo *) malloc(sizeof(Grafo));

    G->qtdVertices = qtdVertices;

    G->vertices = (Vertice *) malloc(qtdVertices * sizeof(Vertice));

    G->matrizAdj = (int **) malloc(qtdVertices * sizeof(int *));

    for (i = 0; i < qtdVertices; i++)
    {
        G->matrizAdj[i] = (int *) calloc(qtdVertices, sizeof(int));
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
            free((*G)->matrizAdj[i]);
            (*G)->matrizAdj[i] = NULL;
        }

        free((*G)->matrizAdj);
        (*G)->matrizAdj = NULL;

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

                            G->matrizAdj[i][indiceDestino] = 1;
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
    int i;

    indice = 0;

    for (i = 0; i < DISCOS; i++)
    {
        indice = indice * PINOS + (discos[i] - 1);
    }

    return indice;
}
void indiceParaEstado(int indice, int discos[])
{
    int i;

    for (i = DISCOS - 1; i >= 0; i--)
    {
        discos[i] = (indice % PINOS) + 1;
        indice = indice / PINOS;
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
