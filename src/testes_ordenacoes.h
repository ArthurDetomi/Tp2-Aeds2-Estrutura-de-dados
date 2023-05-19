#ifndef TESTES_ORDENACOES_H
#define TESTES_ORDENACOES_H
#include "ordenacoes.h"

struct elemento_pequeno_tipo {
    int chave;
} typedef elemento_pequeno;

struct elemento_grande_tipo {
    int chave;
    char *str;
} typedef elemento_grande;

enum tipo_ordenacao_teste_tipo_el {
    ORDEM_ALEATORIA = 0,
    ORDEM_CRESCENTE = 1,
    ORDEM_DECRESCENTE = 2
} typedef tipo_ordenacao_teste;

void iniciar_teste(                                                       
    algoritmos_ordenacao alg_escolhido, tipo_ordenacao_teste ordem_escolha 
);
char *nome_condicao_ordenacao(int num);
void teste_selectionsort();
void teste_insertionsort();
void teste_shellsort();
void teste_quicksortsort();
void teste_mergesort();
void teste_heapsort();

#endif