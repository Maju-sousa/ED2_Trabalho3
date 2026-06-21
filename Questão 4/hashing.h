#ifndef ARQUIVO_H
#define ARQUIVO_H

#define A_FATOR 3
#define C_FATOR -1

typedef struct
{
     long chave;
     int ocupado;
} Slot;

typedef struct
{
     Slot *tabela;
     int tamanho;
     long colisoes;
} HashTable;

void inicializar(HashTable *h, int tamanho);

void liberar(HashTable *h);

int metodoQuadratico(long chave);

int calcularEndereco(long chave, int tamanho);

int calcularColisao(int enderecoAtual, int tamanho);

int inserir(HashTable *h, long chave);

void mostrarTabela(HashTable *h);

void mostrarEstatisticas(HashTable *h);

#endif
