#include "ordenacoes.h"

#include <math.h>
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

void criaheap(int *array, int pai, int fim) {
    int aux = array[pai];
    int filho = 2 * pai + 1;
    while (filho <= fim) {
        if (filho < fim) {
            if (array[filho] < array[filho + 1]) {
                filho++;
            }
        }
        if (aux < array[filho]) {
            array[pai] = array[filho];
            pai = filho;
            filho = 2 * pai + 1;
        }
        else {
            filho = fim + 1;
        }
    }
    array[pai] = aux;
}

void heapsort(int *array, int tamanho) {
    int i;
    for (i = (tamanho - 1) / 2; i >= 0; i--) {
        criaheap(array, i, tamanho - 1);
    }
    for (i = tamanho - 1; i >= 1; i--) {
        int aux = array[0];
        array[0] = array[i];
        array[i] = aux;
        criaheap(array, 0, i - 1);
    }
}

void merge(int *array, int inicio, int meio, int fim) {
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;

    temp = (int *)malloc(tamanho * sizeof(int));
    if (temp != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (!fim1 && !fim2) {
                if (array[p1] < array[p2]) {
                    temp[i] = array[p1++];
                }
                else {
                    temp[i] = array[p2++];
                }
                if (p1 > meio) {
                    fim1 = 1;
                }
                if (p2 > fim) {
                    fim2 = 1;
                }
            }
            else {
                if (!fim1) {
                    temp[i] = array[p1++];
                }
                else {
                    temp[i] = array[p2++];
                }
            }
        }
    }
    for (j = 0, k = inicio; j < tamanho; j++, k++) {
        array[k] = temp[j];
    }
    free(temp);
}

void mergesort(int *array, int inicio, int tamanho) {
    int meio;
    if (inicio < tamanho) {
        meio = floor((inicio + tamanho) / 2);
        mergesort(array, inicio, meio);
        mergesort(array, meio + 1, tamanho);
        merge(array, inicio, meio, tamanho);
    }
}