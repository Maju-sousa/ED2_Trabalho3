#include "Torre.h"

int main(void)
{
    Grafo *G;

    int opcao;

    int origem;
    int destino;

    int estado[DISCOS];
    int indice;

   
    printf(" TORRE DE HANOI ");
   
    G = criarGrafo(TAM);

    printf("\nGerando vertices\n");
    gerarVertices(G);

    printf("Gerando arestas\n");
    gerarArestas(G);

    printf("Grafo criado!\n");

    do
    {
        printf("\n=====================================\n");
        printf("1 - Mostrar estado pelo indice\n");
        printf("2 - Converter estado para indice\n");
        printf("3 - Converter indice para estado\n");
        printf("4 - Executar Dijkstra\n");
        printf("5 - Mostrar estado inicial e final\n");
        printf("0 - Sair\n");
        printf("=====================================\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            do
            {
                printf("\nIndice (0 a 242): ");
                scanf("%d", &indice);

                if (indice < 0 || indice >= TAM)
                {
                    printf("Indice invalido! Digite um valor entre 0 e 242.\n");
                }

            } while (indice < 0 || indice >= TAM);

            imprimirVertice(G, indice);

            break;
        case 2:

            printf("\nDigite os %d discos:\n", DISCOS);
            printf("(valores entre 1 e 3)\n");

            for (int i = 0; i < DISCOS; i++)
            {
                do
                {
                    printf("Disco %d (1 a 3): ", i + 1);
                    scanf("%d", &estado[i]);

                    if (estado[i] < 1 || estado[i] > 3)
                    {
                        printf("Valor invalido! Digite apenas 1, 2 ou 3.\n");
                    }
                } while (estado[i] < 1 || estado[i] > 3);
            }

            indice = estadoParaIndice(estado);

            printf("\nIndice correspondente = %d\n", indice);

            break;

        case 3:

            printf("\nIndice: ");
            scanf("%d", &indice);

            if (indice >= 0 && indice < TAM)
            {
                indiceParaEstado(indice, estado);

                printf("\nEstado = (");

                for (int i = 0; i < DISCOS; i++)
                {
                    printf("%d", estado[i]);

                    if (i < DISCOS - 1)
                    {
                        printf(",");
                    }
                }

                printf(")\n");
            }
            else
            {
                printf("Indice invalido!\n");
            }

            break;

        case 4:

            do
            {
                printf("\nOrigem (0 a 242): ");
                scanf("%d", &origem);

                if (origem < 0 || origem >= TAM)
                {
                    printf("Indice invalido!\n");
                }

            } while (origem < 0 || origem >= TAM);

            do
            {
                printf("Destino (0 a 242): ");
                scanf("%d", &destino);

                if (destino < 0 || destino >= TAM)
                {
                    printf("Indice invalido!\n");
                }

            } while (destino < 0 || destino >= TAM);

            imprimir_dijkstra(G, origem, destino);

            break;

        case 5:

            printf("\nEstado inicial classico:\n");
            imprimirVertice(G, 0);

            printf("\nEstado final classico:\n");
            imprimirVertice(G, 242);

            break;

        case 0:

            printf("\nEncerrando\n");

            break;

        default:

            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    liberarGrafo(&G);

    return 0;
}
