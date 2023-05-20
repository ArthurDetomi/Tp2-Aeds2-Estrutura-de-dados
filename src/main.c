#include <stdio.h>
#include "testes_ordenacoes.h"
#include "ordenacoes.h"
#include <stdlib.h>

int main(void) {
    int algoritmo_escolha, cod_condicao;
    printf("Bem vindo ao programa de testes de algoritmos de ordenacao\n");
    printf("Qual algoritmo deseja testar:\n");
    for (int i = 0; i < 6; i++) {
        char *nome_ordenacao = nome_ordenacoes_disponiveis(i);
        printf("codigo = %d - %s\n", i, nome_ordenacao);
        free(nome_ordenacao);
    }
    printf("Codigo :");
    scanf("%d", &algoritmo_escolha);
    printf("\n");
    for (int i = 0; i < 3; i++) {
        char *nome_condicao = nome_condicao_ordenacao(i);
        printf("Condicao = %d - %s\n", i, nome_condicao);
        free(nome_condicao);
    }
    printf("Codigo :");
    scanf("%d", &cod_condicao);
    printf("\n");
    iniciar_teste(algoritmo_escolha, cod_condicao);
    return 0; 
}