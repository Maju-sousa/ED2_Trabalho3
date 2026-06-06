#ifndef TORRE_H
#define TORRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

#define TAM 243
#define DISCOS 5
#define PINOS 3
#define INF INT_MAX



typedef struct NoAdj
{
    int destino;
    int peso;
    struct NoAdj *prox;
} NoAdj;

// VÉRTICE


typedef struct Vertice
{
    int discos[DISCOS];
    NoAdj *lista;
} Vertice;

// GRAFO

typedef struct Grafo
{
    Vertice *vertices;
    int qtdVertices;
} Grafo;

// CRIAÇÃO E DESTRUIÇÃO

Grafo *criarGrafo(int qtdVertices);
void liberarGrafo(Grafo **G);


// GERAÇÃO DOS ESTADOS


void gerarVertices(Grafo *G);
void gerarArestas(Grafo *G);

int estadoParaIndice(int discos[]);
void indiceParaEstado(int indice, int discos[]);

int movimentoValido(int estado[], int disco, int destino);


// LISTA DE ADJACÊNCIA

void inserirAresta(Grafo *G,
                   int origem,
                   int destino,
                   int peso);

void imprimirListaAdjacencia(Grafo *G);

void imprimirVertice(Grafo *G,
                     int indice);


// DIJKSTRA

void Dijkstra(Grafo *G,
              int origem,
              int *dist,
              int *anterior);

void imprimir_dijkstra(Grafo *G,
                       int origem,
                       int destino);

void imprimirCaminho(Grafo *G,
                     int anterior[],
                     int destino);



double calcularTempoNano(
    LARGE_INTEGER inicio,
    LARGE_INTEGER fim,
    LARGE_INTEGER frequencia);

#endif
