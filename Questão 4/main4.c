#include <stdio.h>
#include "hashing.h"

int main()
{
     HashTable h;
     int tamanho;
     long chave;
     int pos;
     int opc;

     printf("Informe o tamanho do vetor de encaixe: ");
     scanf("%d", &tamanho);

     while (tamanho <= 0)
     {
          printf("Tamanho invalido! Informe um valor maior que zero: ");
          scanf("%d", &tamanho);
     }

     inicializar(&h, tamanho);

     do
     {
          printf("\n================ MENU ================\n");
          printf("1 - Inserir uma chave\n");
          printf("2 - Mostrar tabela hash\n");
          printf("3 - Mostrar estatisticas (colisoes/densidade)\n");
          printf("4 - Sair\n");
          printf("=======================================\n");
          printf("Opcao: ");
          scanf("%d", &opc);

          switch (opc)
          {
          case 1:
               printf("Digite a chave: ");
               scanf("%ld", &chave);

               pos = inserir(&h, chave);
               printf("Chave %ld inserida na posicao %d.\n", chave, pos);
               break;

          case 2:
               mostrarTabela(&h);
               break;

          case 3:
               mostrarEstatisticas(&h);
               break;

          case 4:
               printf("Encerrando...\n");
               break;

          default:
               printf("Opcao invalida!\n");
               break;
          }

     } while (opc != 4);

     liberar(&h);

     return 0;
}