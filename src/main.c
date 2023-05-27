#include <stdio.h>
#include "testes_ordenacoes.h"
#include "ordenacoes.h"
#include <stdlib.h>

int main(void) {
    int algoritmo_escolha, cod_condicao, cod_tamanho_el;
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
    printf("Tamanho dos elementos do teste:\n0:Pequeno\n1:Grande\n");
    printf("Codigo :");
    scanf("%d", &cod_tamanho_el);
    printf("\n");

    char *nome_condicao = nome_condicao_ordenacao(cod_condicao);
    char *nome_ordenacao = nome_ordenacoes_disponiveis(algoritmo_escolha);
    char str[128];
    sprintf(str, "resultado_teste_planilha/%s_%s_tam%d.csv", nome_condicao, nome_ordenacao, cod_tamanho_el);
    FILE *arquivo = fopen(str, "w");
    free(nome_condicao);

    fprintf(arquivo, "\"Quantidade\",\"Tempo Decorrido\", \"Movimentacoes\",\"Comparacoes\"\n");
    fflush(arquivo);

    iniciar_teste(algoritmo_escolha, cod_condicao, cod_tamanho_el, arquivo);

    free(nome_ordenacao);
    fclose(arquivo);
    return 0; 
}