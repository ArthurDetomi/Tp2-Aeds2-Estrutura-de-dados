#include <stdio.h>
#include "ordenacoes.h"
#include <stdlib.h>
#include <time.h>
#define TAM 100000

int main(void) {
    int array[TAM];
    for (int i = 0; i < TAM; i++) {
        int numero_aleatorio = rand() % TAM + 1;
        array[i] = numero_aleatorio;
    }
    quicksort(array, 0, TAM);
    // selectionsort(array, TAM);
    // insertionsort(array, TAM);
    
    return 0;
}