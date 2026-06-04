
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

typedef struct Vertice{
    int discos[DISCOS];
}Vertice;

typedef struct Grafo{
    Vertice *vertices;
    int qtdVertices;
    int **matrizAdj;
}Grafo;

// CRIAÇÃO E DESTRUIÇÃO
Grafo *criarGrafo(int qtdVertices);
void liberarGrafo(Grafo **G);

// GERAÇÃO DOS ESTADOS
void gerarVertices(Grafo *G);
void gerarArestas(Grafo *G);
int estadoParaIndice(int discos[]);
void indiceParaEstado(int indice, int discos[]);
int movimentoValido(int estado[], int disco, int destino);

// MATRIZ DE ADJACÊNCIA
void inserirAresta(Grafo *G, int origem, int destino, int peso);
void imprimirMatriz(Grafo *G);
void imprimirVertice(Grafo *G, int indice);

// DIJKSTRA
void dijkstra(Grafo *G, int origem, int destino);
void imprimirCaminho(int anterior[], int destino);
double calcularTempoNano(LARGE_INTEGER inicio, LARGE_INTEGER fim, LARGE_INTEGER frequencia);

#endif
