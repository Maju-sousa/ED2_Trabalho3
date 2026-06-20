#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


int main()
{
    Grafo g;
    ResultadoCaminho res;

    int numVertices = 0;
    int inicializado = 0;
    int opcao = -1;

    do
    {
        printf("\n============= CAMINHO MAIS CONFIAVEL =============\n");
        printf("Menu:\n");
        printf("1. Criar grafo (definir numero de vertices)\n");
        printf("2. Adicionar aresta\n");
        printf("3. Imprimir grafo\n");
        printf("4. Encontrar caminho mais confiavel\n");
        printf("5. Carregar grafo de exemplo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            limparTerminal();
            printf("Digite o numero de vertices (1 a %d): ", MAX_VERTICES);
            scanf("%d", &numVertices);
            getchar();

            if (numVertices < 1 || numVertices > MAX_VERTICES)
            {
                printf("Numero de vertices invalido!\n");
            }
            else
            {
                if (inicializado == 1)
                {
                    liberarGrafo(&g);
                }
                inicializarGrafo(&g, numVertices);
                inicializado = 1;
                printf("Grafo criado com %d vertices (0 a %d).\n",
                       numVertices, numVertices - 1);
            }
            pausarTerminal();
            limparTerminal();
            break;

        case 2:
            limparTerminal();

            if (inicializado == 0)
            {
                printf("Crie o grafo primeiro (opcao 1).\n");
            }
            else
            {
                int origem, destino;
                double r;

                printf("Vertice de origem (0 a %d): ", g.numVertices - 1);
                scanf("%d", &origem);
                getchar();

                printf("Vertice de destino (0 a %d): ", g.numVertices - 1);
                scanf("%d", &destino);
                getchar();

                printf("Confiabilidade r(u,v) [0.0 a 1.0]: ");
                scanf("%lf", &r);
                getchar();

                int valido = (origem >= 0 && origem < g.numVertices &&
                              destino >= 0 && destino < g.numVertices &&
                              r >= 0.0 && r <= 1.0);

                if (valido == 1)
                {
                    adicionarAresta(&g, origem, destino, r);
                    printf("Aresta %d -> %d com r=%.4f adicionada!\n",
                           origem, destino, r);
                }
                else
                {
                    printf("Dados invalidos! Verifique os vertices e a confiabilidade.\n");
                }
            }

            pausarTerminal();
            limparTerminal();
            break;

        case 3:
            limparTerminal();

            if (inicializado == 0)
            {
                printf("Crie o grafo primeiro (opcao 1).\n");
            }
            else
            {
                imprimirGrafo(&g);
            }

            pausarTerminal();
            limparTerminal();
            break;

        case 4:
            limparTerminal();

            if (inicializado == 0)
            {
                printf("Crie o grafo primeiro (opcao 1).\n");
            }
            else
            {
                int origem, destino;

                printf("Vertice de origem (0 a %d): ", g.numVertices - 1);
                scanf("%d", &origem);
                getchar();

                printf("Vertice de destino (0 a %d): ", g.numVertices - 1);
                scanf("%d", &destino);
                getchar();

                int valido = (origem >= 0 && origem < g.numVertices &&
                              destino >= 0 && destino < g.numVertices);

                if (valido == 1)
                {
                    dijkstra(&g, origem, &res);
                    imprimirCaminho(&res, origem, destino);
                }
                else
                {
                    printf("Vertices invalidos!\n");
                }
            }

            pausarTerminal();
            limparTerminal();
            break;

        case 5:
            
            limparTerminal();

            if (inicializado == 1)
            {
                liberarGrafo(&g);
            }

            inicializarGrafo(&g, 5);
            inicializado = 1;

            
            adicionarAresta(&g, 0, 1, 0.9);
            adicionarAresta(&g, 0, 2, 0.8);
            adicionarAresta(&g, 1, 2, 0.7);
            adicionarAresta(&g, 1, 3, 0.5);
            adicionarAresta(&g, 2, 3, 0.9);
            adicionarAresta(&g, 2, 4, 0.6);
            adicionarAresta(&g, 3, 4, 0.95);
            adicionarAresta(&g, 0, 4, 0.3);

            printf("Grafo de exemplo carregado (5 vertices, 8 arestas).\n\n");
            printf("Interpretacao: r(u,v) = probabilidade do canal u->v NAO falhar.\n");
            printf("Exemplo: r(0,1)=0.90 significa 90%% de chance de nao falhar.\n\n");
            printf("Caminho 0->4 direto:        r = 0.30  (30%%)\n");
            printf("Caminho 0->2->3->4:         r = 0.8 * 0.9 * 0.95 = %.4f\n",
                   0.8 * 0.9 * 0.95);
            printf("Caminho 0->1->2->3->4:      r = 0.9 * 0.7 * 0.9 * 0.95 = %.4f\n",
                   0.9 * 0.7 * 0.9 * 0.95);

            imprimirGrafo(&g);

            pausarTerminal();
            limparTerminal();
            break;

        case 0:
            limparTerminal();

            if (inicializado == 1)
            {
                liberarGrafo(&g);
            }

            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}
