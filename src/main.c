#include <stdio.h>
#include "ordenacoes.h"

int main(void) {
    int array[] = { 5, 6, 9, 1, 2 };
    selectionsort(array, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d\n", array[i]);
    }
    return 0;
}