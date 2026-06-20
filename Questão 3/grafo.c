#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


void pausarTerminal()
{
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);

    int c = getchar();
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void limparTerminal()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void inicializarGrafo(Grafo *g, int numVertices)
{
    int valido = (numVertices > 0 && numVertices <= MAX_VERTICES);

    if (valido == 1)
    {
        g->numVertices = numVertices;
    }
    else
    {
        g->numVertices = 0;
    }

    int i = 0;
    while (i < MAX_VERTICES)
    {
        g->adj[i] = NULL;
        i++;
    }
}

void adicionarAresta(Grafo *g, int origem, int destino, double r)
{
    int valido = (origem >= 0 && origem < g->numVertices &&
                  destino >= 0 && destino < g->numVertices &&
                  r >= 0.0 && r <= 1.0);

    if (valido == 1)
    {
        ArestaLSE *nova = (ArestaLSE *)malloc(sizeof(ArestaLSE));

        if (nova != NULL)
        {
            nova->destino = destino;
            nova->confiabilidade = r;
            nova->prox = g->adj[origem];
            g->adj[origem] = nova;
        }
    }
}

void liberarGrafo(Grafo *g)
{
    int i = 0;
    while (i < g->numVertices)
    {
        ArestaLSE *p = g->adj[i];
        ArestaLSE *aux;

        while (p != NULL)
        {
            aux = p->prox;
            free(p);
            p = aux;
        }

        g->adj[i] = NULL;
        i++;
    }
}


void dijkstra(Grafo *g, int origem, ResultadoCaminho *res)
{
    int visitado[MAX_VERTICES];
    int n = g->numVertices;
    int i = 0;

    while (i < n)
    {
        res->conf[i] = 0.0;
        res->anterior[i] = -1;
        res->alcancavel[i] = 0;
        visitado[i] = 0;
        i++;
    }

    res->conf[origem] = 1.0;
    res->alcancavel[origem] = 1;

    int iter = 0;
    while (iter < n)
    {
        int u = -1;
        double maior = -1.0;

        int j = 0;
        while (j < n)
        {
            if (visitado[j] == 0 && res->conf[j] > maior)
            {
                maior = res->conf[j];
                u = j;
            }
            j++;
        }

        int podeContinuar = (u != -1 && res->conf[u] > 0.0);

        if (podeContinuar == 1)
        {
            visitado[u] = 1;

            ArestaLSE *aresta = g->adj[u];
            while (aresta != NULL)
            {
                int v = aresta->destino;
                double novaConf = res->conf[u] * aresta->confiabilidade;

                if (novaConf > res->conf[v])
                {
                    res->conf[v] = novaConf;
                    res->anterior[v] = u;
                    res->alcancavel[v] = 1;
                }

                aresta = aresta->prox;
            }
        }

        iter++;
    }
}


void reconstruirCaminho(ResultadoCaminho *res, int origem, int destino,
                        int *caminho, int *tamanho)
{
    int temp[MAX_VERTICES];
    int tam = 0;

    int alcancou = (res->alcancavel[destino] == 1);

    if (alcancou == 1)
    {
        int atual = destino;

        int continuar = 1;
        while (continuar == 1 && tam < MAX_VERTICES)
        {
            temp[tam] = atual;
            tam++;

            if (atual == origem)
            {
                continuar = 0;
            }
            else if (res->anterior[atual] == -1)
            {
                tam = 0;
                continuar = 0;
            }
            else
            {
                atual = res->anterior[atual];
            }
        }
    }

    *tamanho = tam;
    int i = 0;
    while (i < tam)
    {
        caminho[i] = temp[tam - 1 - i];
        i++;
    }
}

void imprimirCaminho(ResultadoCaminho *res, int origem, int destino)
{
    int caminho[MAX_VERTICES];
    int tamanho = 0;

    printf("\n=== Caminho mais confiavel: %d -> %d ===\n", origem, destino);

    if (origem == destino)
    {
        printf("Origem e destino sao o mesmo vertice.\n");
        printf("Confiabilidade: 1.00 (100%%)\n");
    }
    else
    {
        reconstruirCaminho(res, origem, destino, caminho, &tamanho);

        if (tamanho == 0)
        {
            printf("Nao existe caminho de %d ate %d.\n", origem, destino);
        }
        else
        {
            printf("Caminho: ");

            int i = 0;
            while (i < tamanho)
            {
                printf("%d", caminho[i]);
                if (i < tamanho - 1)
                {
                    printf(" -> ");
                }
                i++;
            }

            printf("\nNumero de arestas: %d\n", tamanho - 1);
            printf("Confiabilidade maxima: %.6f (%.2f%%)\n",
                   res->conf[destino], res->conf[destino] * 100.0);
        }
    }
}

void imprimirGrafo(Grafo *g)
{
    printf("\n=== Grafo Orientado (%d vertices) ===\n", g->numVertices);

    int i = 0;
    while (i < g->numVertices)
    {
        printf("  %d:", i);

        ArestaLSE *p = g->adj[i];

        if (p == NULL)
        {
            printf(" (sem arestas saindo)");
        }

        while (p != NULL)
        {
            printf(" --(%.2f)--> %d", p->confiabilidade, p->destino);
            p = p->prox;
        }

        printf("\n");
        i++;
    }
}
