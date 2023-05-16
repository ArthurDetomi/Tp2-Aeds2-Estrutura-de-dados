#include <stdio.h>
#include "ordenacoes.h"
#include <stdlib.h>
#include <time.h>
#define TAM 1000

int main(void) {
    int array[TAM];
    for (int i = 0; i < TAM; i++) {
        int numero_aleatorio = rand() % 1000 + 1;
        array[i] = numero_aleatorio;
    }
    selectionsort(array, TAM);
    for (int i = 0; i < TAM; i++) {
        printf("%d\n", array[i]);
    }
    return 0;
}