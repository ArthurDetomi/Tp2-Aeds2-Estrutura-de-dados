#ifndef ORDENACOES_H
#define ORDENACOES_H

struct elemento_tipo {
    int chave;
} typedef elemento ;

struct elemento_tipo_grande {
    int chave;
    char dado[50][50];
} typedef elemento_grande ;

enum algoritmos_ordenacao_tipo {
    SELECTION_SORT = 0,
    INSERTION_SORT = 1,
    SHELL_SORT = 2,
    QUICK_SORT = 3,
    HEAP_SORT = 4,
    MERGE_SORT = 5
} typedef algoritmos_ordenacao ;

char *nome_ordenacoes_disponiveis(int num);
void selectionsort(elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void insertionsort(elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void shellsort(elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void quicksort(elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void heapsort(elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void mergesort(elemento *elementos, int inicio, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);

void selectionsort_el_grande(elemento_grande *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void insertionsort_el_grande(elemento_grande *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void shellsort_el_grande(elemento_grande *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void quicksort_el_grande(elemento_grande *elementos_grande, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes); 
void heapsort_el_grande(elemento_grande *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);
void mergesort_el_grande(elemento_grande *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes);

#endif
