#include "ordenacoes.h"

#include <stdlib.h>

void selectionsort(int *array, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int pos_menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (array[j] < array[pos_menor]) {
                pos_menor = j;
            }
        }
        if (pos_menor != i) {
            int aux = array[i];
            array[i] = array[pos_menor];
            array[pos_menor] = aux;
        }
    }
}

void insertionsort(int *array, int tamanho) {
    int j;
    for (int i = 1; i < tamanho; i++) {
        int valor_atual = array[i];
        for (j = i; j > 0 && array[j - 1] > valor_atual; j--) {
            array[j] = array[j - 1];
        }
        array[j] = valor_atual;
    }
}
