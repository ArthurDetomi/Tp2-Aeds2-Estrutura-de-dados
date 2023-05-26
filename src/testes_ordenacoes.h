#ifndef TESTES_ORDENACOES_H
#define TESTES_ORDENACOES_H
#include "ordenacoes.h"

enum tipo_ordenacao_teste_tipo_el {
    ORDEM_ALEATORIA = 0,
    ORDEM_CRESCENTE = 1,
    ORDEM_DECRESCENTE = 2
} typedef tipo_ordenacao_teste;

enum tamanho_elenento_teste_el {
    PEQUENO = 0,
    GRANDE = 1
} typedef tamanho_elemento_teste ;

void iniciar_teste(                                                       
    algoritmos_ordenacao alg_escolhido, tipo_ordenacao_teste ordem_escolha, tamanho_elemento_teste tamanho_el_teste
);
char *nome_condicao_ordenacao(int num);
void teste_selectionsort();
void teste_insertionsort();
void teste_shellsort();
void teste_quicksortsort();
void teste_mergesort();
void teste_heapsort();

#endif