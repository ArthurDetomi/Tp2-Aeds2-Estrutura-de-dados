#include "ordenacoes.h"
#include "testes_ordenacoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#define TAM_1 20
#define TAM_2 500
#define TAM_3 5000
#define TAM_4 10000
#define TAM_5 200000

elemento *gerar_array(int tipo_ordenacao, int tamanho) {
    elemento *array = (elemento *)malloc(tamanho * sizeof(elemento));
    switch (tipo_ordenacao) {
        case ORDEM_ALEATORIA:
            for (int i = 0; i < tamanho; i++) {
                int numero_aleatorio = rand() % tamanho + 1;
                array[i].chave = numero_aleatorio;
            }
            return array;
        break;
        case ORDEM_CRESCENTE:
            for (int i = 1; i <= tamanho; i++) {
                array[i].chave = i;
            }
            return array;
        break;
        case ORDEM_DECRESCENTE:
            for (int i = (tamanho + 1); i >= 1; i--) {
                array[i].chave = i;
            }
            return array;
        break;
    }
    return NULL;
}

void iniciar_teste_especifico(
    int tamanho, char *msg, int alg_escolhido, int ordem_escolhida
) {
    int comparacoes = 0, movimentacoes = 0;
    clock_t tempo_inicial, tempo_final;
    double tempo_decorrido = 0;
    printf("\t%s\n", msg);
    elemento *elementos = gerar_array(ordem_escolhida, tamanho);

    switch (alg_escolhido) {
        case INSERTION_SORT:
            for (int i = 0; i < 10; i++) {
                tempo_inicial = clock();
                insertionsort(elementos, tamanho, &movimentacoes, &comparacoes);
                tempo_final = clock();
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case SELECTION_SORT:
            for (int i = 0; i < 10; i++) {
                tempo_inicial = clock();
                selectionsort(elementos, tamanho, &movimentacoes, &comparacoes);
                tempo_final = clock();
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case HEAP_SORT:
            for (int i = 0; i < 10; i++) {
                tempo_inicial = clock();
                heapsort(elementos, tamanho, &movimentacoes, &comparacoes);
                tempo_final = clock();
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case MERGE_SORT:
            for (int i = 0; i < 10; i++) {
                tempo_inicial = clock();
                mergesort(elementos, 0, tamanho, &movimentacoes, &comparacoes);
                tempo_final = clock();
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case QUICK_SORT:
            for (int i = 0; i < 10; i++) {
                tempo_inicial = clock();
                quicksort(elementos, 0, tamanho, &movimentacoes, &comparacoes);
                tempo_final = clock();
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case SHELL_SORT:
            for (int i = 0; i < 10; i++) {
                tempo_inicial = clock();
                shellsort(elementos, tamanho, &movimentacoes, &comparacoes);
                tempo_final = clock();
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
    }
    printf("Numero de comparacoes = %d\n", (comparacoes / 10));
    printf("Numero de movimentacoes = %d\n", (movimentacoes / 10));
    printf("Tempo decorrido = %f\n", (tempo_decorrido / 10.00));
    free(elementos);
}

void iniciar_teste(algoritmos_ordenacao alg_escolhido, tipo_ordenacao_teste ordem_escolha) {
    if (ordem_escolha < 0 || ordem_escolha > 2 || alg_escolhido < 0 || alg_escolhido > 5) {
        printf("Erro: Codigos invalidos\n");
        return;
    }
    iniciar_teste_especifico( TAM_1, "Teste com 20 elementos", alg_escolhido, ordem_escolha);
    iniciar_teste_especifico( TAM_2, "Teste com 500 elementos", alg_escolhido, ordem_escolha);
    iniciar_teste_especifico( TAM_3, "Teste com 5000 elementos", alg_escolhido, ordem_escolha);
    iniciar_teste_especifico( TAM_4, "Teste com 10000 elementos", alg_escolhido, ordem_escolha);
    iniciar_teste_especifico( TAM_5, "Teste com 200000 elementos", alg_escolhido, ordem_escolha);
}

char *nome_condicao_ordenacao(int num) {
    if (num < 0 || num > 3) {
        return NULL;
    }
    char condicoes[][50] = { "Ordem Aleatoria", "Ordem Crescente", "Ordem Decrescente" };
    int tam_str = strlen(condicoes[num]);
    char *nome_condicao = (char *)malloc((tam_str + 1) * sizeof(char));
    strcpy(nome_condicao, condicoes[num]);
    return nome_condicao;
}