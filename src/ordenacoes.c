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

int particiona(int *array, int inicio, int final) {
    int esq, dir, pivo;
    esq = inicio;
    dir = final;
    pivo = array[inicio];
    while (esq < dir) {
        while (esq <= final && array[esq] <= pivo) {
            esq++;
        }
        while (dir >= 0 && array[dir] > pivo) {
            dir--;
        }
        if (esq < dir) {
            int aux = array[esq];
            array[esq] = array[dir];
            array[dir] = aux;
        }
    }
    array[inicio] = array[dir];
    array[dir] = pivo;
    return dir;
}

void quicksort(int *array, int inicio, int fim) {
    int pivo;
    if (fim > inicio) {
        pivo = particiona(array, inicio, fim);
        quicksort(array, inicio, pivo - 1);
        quicksort(array, pivo + 1, fim);
    }
}
