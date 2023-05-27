#include "ordenacoes.h"
#include "testes_ordenacoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM_20 20
#define TAM_500 500
#define TAM_5000 5000
#define TAM_10000 10000
#define TAM_200000 200000

int verifica_se_alocacao_falhou(void *pointer) {   
    if (pointer == NULL) {
        printf("Erro em alocação");
        exit(1);
    }
    return 0;
}

elemento *gerar_array(tipo_ordenacao_teste tipo_ordenacao, int tamanho) {
    elemento *array = (elemento *)malloc(tamanho * sizeof(elemento));
    verifica_se_alocacao_falhou(array);
    switch (tipo_ordenacao) {
        case ORDEM_ALEATORIA:
            for (int i = 0; i < tamanho; i++) {
                srand(time(NULL));
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
            for (int i = (tamanho + 1), pos = 0; i >= 1; i--, pos++) {
                array[pos].chave = i;
            }
            return array;
        break;
    }
    return NULL;
}

elemento_grande *gerar_array_elementos_grande(tipo_ordenacao_teste tipo_ordenacao, int tamanho) {
    elemento_grande *array = (elemento_grande *)malloc(tamanho * sizeof(elemento_grande));
    verifica_se_alocacao_falhou(array);
    switch (tipo_ordenacao) {
        case ORDEM_ALEATORIA:
            for (int i = 0; i < tamanho; i++) {
                srand(time(NULL));
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
            for (int i = (tamanho + 1), pos = 0; i >= 1; i--, pos++) {
                array[pos].chave = i;
            }
            return array;
        break;
    }
    return NULL;
}

void iniciar_teste_especifico(
    int tamanho, char *msg, algoritmos_ordenacao alg_escolhido, tipo_ordenacao_teste ordem_escolhida, tamanho_elemento_teste tamanho_el_teste, FILE *arquivo
) {
    int comparacoes = 0, movimentacoes = 0;
    clock_t tempo_inicial, tempo_final;
    double tempo_decorrido = 0;
    printf("\t%s\n", msg);

    elemento_grande *elementos_grande;
    elemento *elementos;
    
    // verifica se vai gerar um array com elementos grandes ou não
    if (tamanho_el_teste == GRANDE) {
        if (ordem_escolhida != ORDEM_ALEATORIA) {
            elementos_grande = gerar_array_elementos_grande(ordem_escolhida, tamanho);
        } else {
            elementos_grande = NULL;
        }
        elementos = NULL;
    } else {
        if (ordem_escolhida != ORDEM_ALEATORIA) {
            elementos = gerar_array(ordem_escolhida, tamanho);
        } else {
            elementos = NULL;
        }
        elementos_grande = NULL;
    }

    switch (alg_escolhido) {
        case INSERTION_SORT:
            for (int i = 0; i < 10; i++) {
                if (tamanho_el_teste == GRANDE) {
                    elemento_grande *elementos_grande_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_grande_aux = (elemento_grande *) malloc(sizeof(elemento_grande) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_grande_aux);
                        memcpy(elementos_grande_aux, elementos_grande, sizeof(elemento_grande) * tamanho + 1);
                    } else {
                        elementos_grande_aux = gerar_array_elementos_grande(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    insertionsort_el_grande(elementos_grande_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_grande_aux);
                } else {
                    elemento *elementos_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_aux = (elemento*) malloc(sizeof(elemento) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_aux);
                        memcpy(elementos_aux, elementos, sizeof(elemento) * tamanho + 1);
                    } else {
                        elementos_aux = gerar_array(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    insertionsort(elementos_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_aux);
                }
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case SELECTION_SORT:
            for (int i = 0; i < 10; i++) {
                if (tamanho_el_teste == GRANDE) {
                    elemento_grande *elementos_grande_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_grande_aux = (elemento_grande *) malloc(sizeof(elemento_grande) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_grande_aux);
                        memcpy(elementos_grande_aux, elementos_grande, sizeof(elemento_grande) * tamanho + 1);
                    } else {
                        elementos_grande_aux = gerar_array_elementos_grande(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    selectionsort_el_grande(elementos_grande_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_grande_aux);
                } else {
                    elemento *elementos_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_aux = (elemento*) malloc(sizeof(elemento) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_aux);
                        memcpy(elementos_aux, elementos, sizeof(elemento) * tamanho + 1);
                    } else {
                        elementos_aux = gerar_array(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    selectionsort(elementos_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_aux);
                }
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case HEAP_SORT:
            for (int i = 0; i < 10; i++) {
                if (tamanho_el_teste == GRANDE) {
                    elemento_grande *elementos_grande_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_grande_aux = (elemento_grande *) malloc(sizeof(elemento_grande) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_grande_aux);
                        memcpy(elementos_grande_aux, elementos_grande, sizeof(elemento_grande) * tamanho + 1);
                    } else {
                        elementos_grande_aux = gerar_array_elementos_grande(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    heapsort_el_grande(elementos_grande_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_grande_aux);
                } else {
                    elemento *elementos_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_aux = (elemento*) malloc(sizeof(elemento) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_aux);
                        memcpy(elementos_aux, elementos, sizeof(elemento) * tamanho + 1);
                    } else {
                        elementos_aux = gerar_array(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    heapsort(elementos_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_aux);
                }
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case MERGE_SORT:
            for (int i = 0; i < 10; i++) {
                if (tamanho_el_teste == GRANDE) {
                    elemento_grande *elementos_grande_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_grande_aux = (elemento_grande *) malloc(sizeof(elemento_grande) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_grande_aux);
                        memcpy(elementos_grande_aux, elementos_grande, sizeof(elemento_grande) * tamanho + 1);
                    } else {
                        elementos_grande_aux = gerar_array_elementos_grande(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    mergesort_el_grande(elementos_grande_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    if (elementos_grande_aux != NULL) {
                        free(elementos_grande_aux);
                        elementos_grande_aux = NULL;
                    }
                } else { 
                    elemento *elementos_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_aux = (elemento*) malloc(sizeof(elemento) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_aux);
                        memcpy(elementos_aux, elementos, sizeof(elemento) * tamanho + 1);
                    } else {
                        elementos_aux = gerar_array(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    mergesort(elementos_aux, 0, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_aux);
                }
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case QUICK_SORT:
            for (int i = 0; i < 10; i++) {
                if (tamanho_el_teste == GRANDE) {
                    elemento_grande *elementos_grande_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_grande_aux = (elemento_grande *) malloc(sizeof(elemento_grande) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_grande_aux);
                        memcpy(elementos_grande_aux, elementos_grande, sizeof(elemento_grande) * tamanho + 1);
                    } else {
                        elementos_grande_aux = gerar_array_elementos_grande(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    quicksort_el_grande(elementos_grande_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_grande_aux);
                } else {
                    elemento *elementos_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_aux = (elemento*) malloc(sizeof(elemento) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_aux);
                        memcpy(elementos_aux, elementos, sizeof(elemento) * tamanho + 1);
                    } else {
                        elementos_aux = gerar_array(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    quicksort(elementos_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_aux);
                }
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
        case SHELL_SORT:
            for (int i = 0; i < 10; i++) {
                if (tamanho_el_teste == GRANDE) {
                    elemento_grande *elementos_grande_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_grande_aux = (elemento_grande *) malloc(sizeof(elemento_grande) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_grande_aux);
                        memcpy(elementos_grande_aux, elementos_grande, sizeof(elemento_grande) * tamanho + 1);
                    } else {
                        elementos_grande_aux = gerar_array_elementos_grande(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    shellsort_el_grande(elementos_grande_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_grande_aux);
                } else {
                    elemento *elementos_aux;
                    if (ordem_escolhida != ORDEM_ALEATORIA) {
                        elementos_aux = (elemento*) malloc(sizeof(elemento) * tamanho + 1);
                        verifica_se_alocacao_falhou(elementos_aux);
                        memcpy(elementos_aux, elementos, sizeof(elemento) * tamanho + 1);
                    } else {
                        elementos_aux = gerar_array(ordem_escolhida, tamanho);
                    }
                    tempo_inicial = clock();
                    shellsort(elementos_aux, tamanho, &movimentacoes, &comparacoes);
                    tempo_final = clock();
                    free(elementos_aux);
                }
                tempo_decorrido += ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;
            }
        break;
    }
    printf("Numero de comparacoes = %f\n", (comparacoes / 10.00));
    printf("Numero de movimentacoes = %f\n", (movimentacoes / 10.00));
    printf("Tempo decorrido = %f\n", (tempo_decorrido / 10.00));

    fprintf(arquivo, "\"%d\",\"%.6f\", \"%.6f\",\"%.6f\"\n", tamanho, tempo_decorrido, movimentacoes / 10.00, comparacoes / 10.00);

    if (elementos_grande != NULL) {
        free(elementos_grande);
    }
    else if (elementos != NULL){
        free(elementos);
    }
}

void iniciar_teste(algoritmos_ordenacao alg_escolhido, tipo_ordenacao_teste ordem_escolha, tamanho_elemento_teste tamanho_el_teste, FILE *arquivo) {
    if (ordem_escolha < 0 || ordem_escolha > 2 || alg_escolhido < 0 || alg_escolhido > 5) {
        printf("Erro: Codigos invalidos\n");
        return;
    }
    iniciar_teste_especifico( TAM_20, "Teste com 20 elementos", alg_escolhido, ordem_escolha, tamanho_el_teste, arquivo);
    iniciar_teste_especifico( TAM_500, "Teste com 500 elementos", alg_escolhido, ordem_escolha, tamanho_el_teste, arquivo);
    iniciar_teste_especifico( TAM_5000, "Teste com 5000 elementos", alg_escolhido, ordem_escolha, tamanho_el_teste, arquivo);
    iniciar_teste_especifico( TAM_10000, "Teste com 10000 elementos", alg_escolhido, ordem_escolha, tamanho_el_teste, arquivo);
    iniciar_teste_especifico( TAM_200000, "Teste com 200000 elementos", alg_escolhido, ordem_escolha, tamanho_el_teste, arquivo);
}

char *nome_condicao_ordenacao(int num) {
    if (num < 0 || num > 3) {
        return NULL;
    }
    char condicoes[][50] = { "Ordem Aleatoria", "Ordem Crescente", "Ordem Decrescente" };
    int tam_str = strlen(condicoes[num]);
    char *nome_condicao = (char *)malloc((tam_str + 1) * sizeof(char));
    verifica_se_alocacao_falhou(nome_condicao);
    strcpy(nome_condicao, condicoes[num]);
    return nome_condicao;
}

