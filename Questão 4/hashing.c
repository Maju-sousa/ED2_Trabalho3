#include <stdio.h>
#include <stdlib.h>
#include "hashing.h"

void inicializar(HashTable *h, int tamanho)
{
     int i;

     h->tamanho = tamanho;
     h->colisoes = 0;
     h->tabela = (Slot *) malloc(sizeof(Slot) * tamanho);

     i = 0;
     while (i < tamanho)
     {
          h->tabela[i].ocupado = 0;
          i++;
     }
}

void liberar(HashTable *h)
{
     free(h->tabela);
     h->tabela = NULL;
}

int metodoQuadratico(long chave)
{
     long semUltimo;
     long meio4;
     long quadrado;
     char buffer[20];
     char extraido[4];

     semUltimo = chave / 10;
     meio4 = semUltimo % 10000;
     quadrado = meio4 * meio4;

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
     int novo;

     novo = (A_FATOR * enderecoAtual + C_FATOR) % tamanho;

     if (novo < 0)
          novo += tamanho;

     return novo + 1;
}

int inserir(HashTable *h, long chave)
{
     int posOriginal;
     int pos;
     int tentativas;
     int inserido;

     posOriginal = calcularEndereco(chave, h->tamanho);
     pos = posOriginal;
     tentativas = 0;
     inserido = 0;

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

     i = 0;
     while (i < h->tamanho)
     {
          printf("Posicao %2d: ", i + 1);

          if (h->tabela[i].ocupado)
               printf("%ld\n", h->tabela[i].chave);
          else
               printf("---\n");

          i++;
     }

     printf("=====================================\n");
}

void mostrarEstatisticas(HashTable *h)
{
     int ocupados;
     int i;
     double densidade;

     ocupados = 0;
     i = 0;

     while (i < h->tamanho)
     {
          if (h->tabela[i].ocupado)
               ocupados++;
          i++;
     }

     densidade = (double) ocupados / h->tamanho;

     printf("\n===== ESTATISTICAS =====\n");
     printf("Colisoes ocorridas : %ld\n", h->colisoes);
     printf("Posicoes ocupadas  : %d\n", ocupados);
     printf("Tamanho do vetor   : %d\n", h->tamanho);
     printf("Densidade          : %.4f (%.2f%%)\n", densidade, densidade * 100);
     printf("=========================\n");
}
