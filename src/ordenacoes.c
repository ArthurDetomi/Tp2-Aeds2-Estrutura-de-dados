#include "ordenacoes.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selectionsort(
    elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes
) {
    for (int i = 0; i < tamanho - 1; i++) {
        int pos_menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            (*comparacoes)++;
            if (elementos[j].chave < elementos[pos_menor].chave) {
                pos_menor = j;
            }
        }
        if (pos_menor != i) {
            elemento aux = elementos[i];
            elementos[i] = elementos[pos_menor];
            elementos[pos_menor] = aux;
            (*movimentacoes) += 3;
        }
    }
}

void insertionsort(
    elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes
) {
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

void particiona(
    int esq, int dir, int *i, int *j, elemento *elementos_grandes,
    unsigned long *movimentacoes, unsigned long *comparacoes
) {
    elemento x, w;
    *i = esq;
    *j = dir;
    x = elementos_grandes[(*i + *j) / 2];
    (*movimentacoes)++;
    /* obtem o pivo x */
    do {
        while (*i <= dir && x.chave > elementos_grandes[*i].chave) {
            (*i)++;
            (*comparacoes)++;
        }
        while (*j >= esq && x.chave < elementos_grandes[*j].chave) {
            (*j)--;
            (*comparacoes)++;
        }
        if (*i <= *j) {
            w = elementos_grandes[*i];
            elementos_grandes[*i] = elementos_grandes[*j];
            elementos_grandes[*j] = w;
            (*movimentacoes) += 3;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void ordenar(
    int esq, int dir, elemento *a, unsigned long *movimentacoes, unsigned long *comparacoes
) {
    int i, j;
    particiona(esq, dir, &i, &j, a, movimentacoes, comparacoes);
    if (esq < j)
        ordenar(esq, j, a, movimentacoes, comparacoes);
    if (i < dir)
        ordenar(i, dir, a, movimentacoes, comparacoes);
}

void quicksort(
    elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes
) {
    ordenar(0, tamanho - 1, elementos, movimentacoes, comparacoes);
}

void criaheap(
    elemento *elementos, int pai, int fim, unsigned long *movimentacoes, unsigned long *comparacoes
) {
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

void heapsort(
    elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes
) {
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

void merge(
    elemento *elementos, int inicio, int meio, int fim, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
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

void mergesort(
    elemento *elementos, int inicio, int tamanho, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    int meio;
    if (inicio < tamanho) {
        meio = floor((inicio + tamanho) / 2);
        mergesort(elementos, inicio, meio, movimentacoes, comparacoes);
        mergesort(elementos, meio + 1, tamanho, movimentacoes, comparacoes);
        merge(elementos, inicio, meio, tamanho, movimentacoes, comparacoes);
    }
}

void shellsort(
    elemento *elementos, int tamanho, unsigned long *movimentacoes, unsigned long *comparacoes
) {
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
            (*movimentacoes) += 2;
        }
    } while (intervalo != 1);
}

char *nome_ordenacoes_disponiveis(int num) {
    if (num > 5 || num < 0) {
        return NULL;
    }
    char ordenacoes[][50] = { "SelectionSort", "InsertionSort", "ShellSort",
                              "QuickSort",     "HeapSort",      "MergeSort" };
    int tam_str = strlen(ordenacoes[num]);
    char *nome_ordenacao = (char *)malloc((tam_str + 1) * sizeof(char));
    strcpy(nome_ordenacao, ordenacoes[num]);
    return nome_ordenacao;
}

// Ordenações para o tipo elemento grande
void selectionsort_el_grande(
    elemento_grande *elementos, int tamanho, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    for (int i = 0; i < tamanho - 1; i++) {
        int pos_menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            (*comparacoes)++;
            if (elementos[j].chave < elementos[pos_menor].chave) {
                pos_menor = j;
            }
        }
        if (pos_menor != i) {
            elemento_grande aux = elementos[i];
            elementos[i] = elementos[pos_menor];
            elementos[pos_menor] = aux;
            (*movimentacoes) += 3;
        }
    }
}

void insertionsort_el_grande(
    elemento_grande *elementos, int tamanho, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    int j;
    for (int i = 1; i < tamanho; i++) {
        elemento_grande valor_atual = elementos[i];
        for (j = i; j > 0 && elementos[j - 1].chave > valor_atual.chave; j--) {
            (*comparacoes)++;
            elementos[j] = elementos[j - 1];
            (*movimentacoes)++;
        }
        elementos[j] = valor_atual;
        (*movimentacoes) += 2;
    }
}

void particiona_el_grande(
    int esq, int dir, int *i, int *j, elemento_grande *elementos_grandes,
    unsigned long *movimentacoes, unsigned long *comparacoes
) {
    elemento_grande x, w;
    *i = esq;
    *j = dir;
    x = elementos_grandes[(*i + *j) / 2];
    (*movimentacoes)++;
    /* obtem o pivo x */
    do {
        while (*i <= dir && x.chave > elementos_grandes[*i].chave) {
            (*i)++;
            (*comparacoes)++;
        }
        while (*j >= esq && x.chave < elementos_grandes[*j].chave) {
            (*j)--;
            (*comparacoes)++;
        }
        if (*i <= *j) {
            w = elementos_grandes[*i];
            elementos_grandes[*i] = elementos_grandes[*j];
            elementos_grandes[*j] = w;
            (*movimentacoes) += 3;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void ordenar_el_grande(
    int esq, int dir, elemento_grande *a, unsigned long *movimentacoes, unsigned long *comparacoes
) {
    int i, j;
    particiona_el_grande(esq, dir, &i, &j, a, movimentacoes, comparacoes);
    if (esq < j)
        ordenar_el_grande(esq, j, a, movimentacoes, comparacoes);
    if (i < dir)
        ordenar_el_grande(i, dir, a, movimentacoes, comparacoes);
}

void quicksort_el_grande(
    elemento_grande *elementos_grande, int tamanho, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    ordenar_el_grande(
        0, tamanho - 1, elementos_grande, movimentacoes, comparacoes
    );
}

void criaheap_el_grande(
    elemento_grande *elementos, int pai, int fim, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    elemento_grande aux = elementos[pai];

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

void heapsort_el_grande(
    elemento_grande *elementos, int tamanho, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    int i;
    for (i = (tamanho - 1) / 2; i >= 0; i--) {
        criaheap_el_grande(
            elementos, i, tamanho - 1, movimentacoes, comparacoes
        );
    }
    for (i = tamanho - 1; i >= 1; i--) {
        elemento_grande aux = elementos[0];
        elementos[0] = elementos[i];
        elementos[i] = aux;
        (*movimentacoes) += 3;
        criaheap_el_grande(elementos, 0, i - 1, movimentacoes, comparacoes);
    }
}

void merge_el(
    elemento_grande elementos_g[], int tamanho, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    int mid;
    int i, j, k;
    elemento_grande *tmp;
    tmp = (elemento_grande *)malloc(tamanho * sizeof(elemento_grande));
    if (tmp == NULL) {
        exit(1);
    }
    mid = tamanho / 2;
    i = 0;
    j = mid;
    k = 0;
    while (i < mid && j < tamanho) {
        (*comparacoes)++;
        if (elementos_g[i].chave < elementos_g[j].chave) {
            tmp[k] = elementos_g[i];
            (*movimentacoes)++;
            ++i;
        }
        else {
            tmp[k] = elementos_g[j];
            (*movimentacoes)++;
            ++j;
        }
        ++k;
    }
    if (i == mid) {
        while (j < tamanho) {
            tmp[k] = elementos_g[j];
            (*movimentacoes)++;
            ++j;
            ++k;
        }
    }
    else {
        while (i < mid) {
            tmp[k] = elementos_g[i];
            (*movimentacoes)++;
            ++i;
            ++k;
        }
    }
    for (i = 0; i < tamanho; ++i) {
        elementos_g[i] = tmp[i];
        (*movimentacoes)++;
    }
    free(tmp);
}

void mergesort_el_grande(
    elemento_grande *elementos_g, int tamanho, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    int mid;
    if (tamanho > 1) {
        mid = tamanho / 2;
        mergesort_el_grande(elementos_g, mid, movimentacoes, comparacoes);
        mergesort_el_grande(
            elementos_g + mid, tamanho - mid, movimentacoes, comparacoes
        );
        merge_el(elementos_g, tamanho, movimentacoes, comparacoes);
    }
}

void shellsort_el_grande(
    elemento_grande *elementos, int tamanho, unsigned long *movimentacoes,
    unsigned long *comparacoes
) {
    int i, j;
    int intervalo = 1;
    elemento_grande elemento_atual;
    do {
        intervalo = intervalo * 3 + 1;
    } while (intervalo < tamanho);
    do {
        intervalo /= 3;
        for (i = intervalo; i < tamanho; i++) {
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
            (*movimentacoes) += 2;
        }
    } while (intervalo != 1);
}
