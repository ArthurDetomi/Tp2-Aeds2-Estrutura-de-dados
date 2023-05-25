#include "ordenacoes.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selectionsort(elemento *elementos, int tamanho, int *movimentacoes, int *comparacoes) {
    for (int i = 0; i < tamanho - 1; i++) {
        int pos_menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            (*comparacoes)++;
            if (elementos[j].chave < elementos[pos_menor].chave) {
                pos_menor = j;
            }
        }
        (*comparacoes)++;
        if (pos_menor != i) {
            elemento aux = elementos[i];
            elementos[i] = elementos[pos_menor];
            elementos[pos_menor] = aux;
            (*movimentacoes) += 3;
        }
    }
}

void insertionsort(elemento *elementos, int tamanho, int *movimentacoes, int *comparacoes) {
    int j;
    for (int i = 1; i < tamanho; i++) {
        elemento valor_atual = elementos[i];
        for (j = i; j > 0 && elementos[j - 1].chave > valor_atual.chave; j--) {
            (*comparacoes)++;
            elementos[j] = elementos[j - 1];
            (*movimentacoes)++;
        }
        elementos[j] = valor_atual;
        (*movimentacoes) += 2;
    }
}

int particiona(elemento *elementos, int inicio, int final, int *movimentacoes, int *comparacoes) {
    int esq, dir;
    esq = inicio;
    dir = final;
    elemento pivo = elementos[(inicio + final) / 2];
    (*movimentacoes)++;
    while (esq < dir) {
        while (esq <= final && elementos[esq].chave <= pivo.chave) {
            esq++;
            (*comparacoes)++;
        }
        while (dir >= 0 && elementos[dir].chave > pivo.chave) {
            dir--;
            (*comparacoes)++;
        }
        if (esq < dir) {
            elemento aux = elementos[esq];
            elementos[esq] = elementos[dir];
            elementos[dir] = aux;
            (*movimentacoes) += 3;
        }
    }
    elementos[inicio] = elementos[dir];
    elementos[dir] = pivo;
    (*movimentacoes) += 2;
    return dir;
}

void quicksort(elemento *elementos, int inicio, int fim, int *movimentacoes, int *comparacoes) {
    int pivo;
    if (fim > inicio) {
        pivo = particiona(elementos, inicio, fim, movimentacoes, comparacoes);
        quicksort(elementos, inicio, pivo - 1, movimentacoes, comparacoes);
        quicksort(elementos, pivo + 1, fim, movimentacoes, comparacoes);
    }
}

void criaheap(elemento *elementos, int pai, int fim, int *movimentacoes, int *comparacoes) {
    elemento aux = elementos[pai];

    (*movimentacoes)++;

    int filho = 2 * pai + 1;
    while (filho <= fim) {
        if (filho < fim) {
            (*comparacoes)++;
            if (elementos[filho].chave < elementos[filho + 1].chave) {
                filho++;
            }
        }
        (*comparacoes)++;
        if (aux.chave < elementos[filho].chave) {
            elementos[pai] = elementos[filho];
            pai = filho;
            filho = 2 * pai + 1;
            (*movimentacoes)++;
        }
        else {
            filho = fim + 1;
        }
    }
    elementos[pai] = aux;
    (*movimentacoes)++;
}

void heapsort(elemento *elementos, int tamanho, int *movimentacoes, int *comparacoes) {
    int i;
    for (i = (tamanho - 1) / 2; i >= 0; i--) {
        criaheap(elementos, i, tamanho - 1, movimentacoes, comparacoes);
    }
    for (i = tamanho - 1; i >= 1; i--) {
        elemento aux = elementos[0];
        elementos[0] = elementos[i];
        elementos[i] = aux;
        (*movimentacoes) += 3;
        criaheap(elementos, 0, i - 1, movimentacoes, comparacoes);
    }
}

void merge(elemento *elementos, int inicio, int meio, int fim, int *movimentacoes, int *comparacoes) {
    int p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;

    elemento *temp = (elemento *)malloc(tamanho * sizeof(elemento));
    if (temp != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (!fim1 && !fim2) {
                (*comparacoes)++;
                if (elementos[p1].chave < elementos[p2].chave) {
                    temp[i] = elementos[p1++];
                    (*movimentacoes)++;
                }
                else {
                    temp[i] = elementos[p2++];
                    (*movimentacoes)++;
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
                    temp[i] = elementos[p1++];
                    (*movimentacoes)++;
                }
                else {
                    temp[i] = elementos[p2++];
                    (*movimentacoes)++;
                }
            }
        }
    }
    for (j = 0, k = inicio; j < tamanho; j++, k++) {
        elementos[k] = temp[j];
        (*movimentacoes)++;
    }
    free(temp);
}

void mergesort(elemento *elementos, int inicio, int tamanho, int *movimentacoes, int *comparacoes) {
    int meio;
    if (inicio < tamanho) {
        meio = floor((inicio + tamanho) / 2);
        mergesort(elementos, inicio, meio, movimentacoes, comparacoes);
        mergesort(elementos, meio + 1, tamanho, movimentacoes, comparacoes);
        merge(elementos, inicio, meio, tamanho, movimentacoes, comparacoes);
    }
}

void shellsort(elemento *elementos, int tamanho, int *movimentacoes, int *comparacoes) {
    int i, j;
    int intervalo = 1;
    elemento elemento_atual;
    do {
        intervalo = intervalo * 3 + 1;
    } while (intervalo < tamanho);
    do {
        intervalo /= 3;
        for (i = intervalo; i <= tamanho; i++) {
            elemento_atual = elementos[i];
            j = i;
            while (elementos[j - intervalo].chave > elemento_atual.chave) {
                elementos[j] = elementos[j - intervalo];
                (*movimentacoes)++;
                j -= intervalo;
                (*comparacoes)++;
                if (j <= intervalo) {
                    break;
                }
            }
            elementos[j] = elemento_atual;
            (*movimentacoes)+=2;
        }
    } while (intervalo != 1);
}

char *nome_ordenacoes_disponiveis(int num) {
    if (num > 5 || num < 0) {
        return NULL;
    }
    char ordenacoes[][50] = {"SelectionSort", "InsertionSort", "ShellSort", "QuickSort", "HeapSort", "MergeSort"};
    int tam_str = strlen(ordenacoes[num]);
    char *nome_ordenacao = (char*) malloc((tam_str + 1) * sizeof(char));
    strcpy(nome_ordenacao, ordenacoes[num]);
    return nome_ordenacao;
}    