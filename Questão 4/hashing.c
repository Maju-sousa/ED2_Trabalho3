#include <stdio.h>
#include <stdlib.h>
#include "hashing.h"


void inicializar(HashTable *h, int tamanho)
{
     int i;

     h->tamanho = tamanho;
     h->colisoes = 0;
     h->tabela = (Slot *) malloc(sizeof(Slot) * tamanho);

     for (i = 0; i < tamanho; i++)
          h->tabela[i].ocupado = 0;
}


void liberar(HashTable *h)
{
     free(h->tabela);
     h->tabela = NULL;
}


int metodoQuadratico(long chave)
{
     long ultimos4 = chave % 10000;
     long quadrado = ultimos4 * ultimos4;
     char buffer[20];
     char extraido[4];

     sprintf(buffer, "%08ld", quadrado);

     extraido[0] = buffer[1];
     extraido[1] = buffer[2];
     extraido[2] = buffer[3];
     extraido[3] = '\0';

     return atoi(extraido);
}


int calcularEndereco(long chave, int tamanho)
{
     int valor = metodoQuadratico(chave);
     return (valor % tamanho) + 1;
}


int calcularColisao(int enderecoAtual, int tamanho)
{
     int novo = (A_FATOR * enderecoAtual + C_FATOR) % tamanho;

     if (novo < 0)
          novo += tamanho;

     return novo + 1;
}


int inserir(HashTable *h, long chave)
{
     int posOriginal = calcularEndereco(chave, h->tamanho);
     int pos = posOriginal;
     int tentativas = 0;
     int inserido = 0;

     while (tentativas < h->tamanho && inserido == 0)
     {
          if (h->tabela[pos - 1].ocupado == 0)
          {
               h->tabela[pos - 1].chave = chave;
               h->tabela[pos - 1].ocupado = 1;
               inserido = 1;
          }
          else
          {
               h->colisoes++;
               pos = calcularColisao(pos, h->tamanho);
               tentativas++;
          }
     }

     if (inserido == 0)
     {
          h->tabela[posOriginal - 1].chave = chave;
          h->tabela[posOriginal - 1].ocupado = 1;
          pos = posOriginal;
     }

     return pos;
}


void mostrarTabela(HashTable *h)
{
     int i;

     printf("\n===== TABELA HASH (tamanho %d) =====\n", h->tamanho);
     for (i = 0; i < h->tamanho; i++)
     {
          printf("Posicao %2d: ", i + 1);

          if (h->tabela[i].ocupado)
               printf("%ld\n", h->tabela[i].chave);
          else
               printf("---\n");
     }
     printf("=====================================\n");
}


void mostrarEstatisticas(HashTable *h)
{
     int ocupados = 0;
     int i;

     for (i = 0; i < h->tamanho; i++)
          if (h->tabela[i].ocupado)
               ocupados++;

     double densidade = (double) ocupados / h->tamanho;

     printf("\n===== ESTATISTICAS =====\n");
     printf("Colisoes ocorridas : %ld\n", h->colisoes);
     printf("Posicoes ocupadas  : %d\n", ocupados);
     printf("Tamanho do vetor   : %d\n", h->tamanho);
     printf("Densidade          : %.4f (%.2f%%)\n", densidade, densidade * 100);
     printf("=========================\n");
}
