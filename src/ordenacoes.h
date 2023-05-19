#ifndef ORDENACOES_H
#define ORDENACOES_H

struct elemento_tipo {
    int chave;
} typedef elemento ;

enum algoritmos_ordenacao_tipo {
    SELECTION_SORT = 0,
    INSERTION_SORT = 1,
    SHELL_SORT = 2,
    QUICK_SORT = 3,
    HEAP_SORT = 4,
    MERGE_SORT = 5
} typedef algoritmos_ordenacao ;

char *nome_ordenacoes_disponiveis(int num);
void selectionsort(elemento *elementos, int tamanho, int *movimentacoes, int *comparacoes);
void insertionsort(elemento *elementos, int tamanho, int *movimentacoes, int *comparacoes);
void shellsort(elemento *elementos, int tamanho, int *movimentacoes, int *comparacoes);
void quicksort(elemento *elementos, int inicio, int fim, int *movimentacoes, int *comparacoes);
void heapsort(elemento *elementos, int tamanho, int *movimentacoes, int *comparacoes);
void mergesort(elemento *elementos, int inicio, int tamanho, int *movimentacoes, int *comparacoes);

#endif
