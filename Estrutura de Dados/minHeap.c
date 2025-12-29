#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* vetor;
    int capacidade;
} MinHeap;

MinHeap* criarMinHeap(int capacidade);
void inserir(MinHeap* heap, int chave);
int remover(MinHeap* heap);
void imprimirHeap(MinHeap* heap);
void destruirHeap(MinHeap* heap);

int main() {
    MinHeap* heap = criarMinHeap(10);

    inserir(heap, 10);
    inserir(heap, 20);
    inserir(heap, 5);
    inserir(heap, 15);
    inserir(heap, 25);

    imprimirHeap(heap);
    printf("Elementos removidos em ordem crescente: ");

    while (heap->vetor[0] > 0) {
        printf("%d ", remover(heap));
    }
    printf("\n");

    imprimirHeap(heap);
    destruirHeap(heap);

    return 0;
}

void troca(int *v1, int *v2) {
    int aux = *v1;
    *v1 = *v2;
    *v2 = aux;
}

void heapify(MinHeap* heap, int i) {
    int menor = i;
    int filhoEsquerda = 2 * i;
    int filhoDireita = 2 * i + 1;

    if (filhoEsquerda <= heap->vetor[0] && filhoDireita <= heap->vetor[0]) {

        // ALTERAÇÃO: verifica se o filho da esquerda é o menor (dois filhos)
        if (heap->vetor[filhoEsquerda] < heap->vetor[menor] && heap->vetor[filhoEsquerda] < heap->vetor[filhoDireita]) {
            menor = filhoEsquerda;
        }
        // ALTERAÇÃO: verifica se o filho da direita é o menor (dois filhos)
        else if (heap->vetor[filhoDireita] < heap->vetor[menor] && heap->vetor[filhoDireita] < heap->vetor[filhoEsquerda]) {
            menor = filhoDireita;
        }
    }
    
    // ALTERAÇÃO: verifica se o filho da esquerda é o menor
    else if (filhoEsquerda <= heap->vetor[0] && heap->vetor[filhoEsquerda] > heap->vetor[menor]) {
        menor = filhoEsquerda;
    }
    // ALTERAÇÃO: verifica se o filho da direita é o menor
    else if (filhoDireita <= heap->vetor[0] && heap->vetor[filhoDireita] > heap->vetor[menor]) {
        menor = filhoDireita;
    }
    // ALTERAÇÃO: se um dos filhos é menor do que o pai, o menor filho assume o lugar do pai
    if (menor != i) {
        troca(&heap->vetor[i], &heap->vetor[menor]);
        heapify(heap, menor);
    }
}

MinHeap* criarMinHeap(int capacidade) {
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->vetor = (int*) malloc(capacidade * sizeof(int));
    heap->vetor[0] = 0;
    heap->capacidade = capacidade;
    return heap;
}

void inserir(MinHeap* heap, int chave) {
    if (heap != NULL && heap->vetor != NULL) {

        // Se o heap estiver vazio, a chave é insirida na raiz
        if (heap->vetor[0] == 0) {
            heap->vetor[1] = chave;
            heap->vetor[0]++;
        }
        else {
            // Se o heap estiver cheio, sua capacidade é dobrada antes da inserção da chave.
            if (heap->vetor[0] == heap->capacidade) {
                int* vet = realloc(heap->vetor, heap->capacidade * 2);

                if (vet != NULL) {
                    heap->vetor = vet;
                }
                else {
                    printf("Heap cheio! N�o � poss�vel inserir mais elementos.\n");
                    return;
                }
            }
            heap->vetor[0]++;
            int i = heap->vetor[0];
            int pai = i / 2;
            heap->vetor[i] = chave;

            while (heap->vetor[i] < heap->vetor[pai]) {
                troca(&heap->vetor[i], &heap->vetor[pai]);
                i = pai;
                pai = i / 2;
            }
        }
    }
}

int remover(MinHeap* heap) {
    if (heap != NULL && heap->vetor != NULL) {
        if (heap->vetor[0] == 0) {
            printf("Heap vazio!\n");
            return -1;
        }
        int raiz = heap->vetor[1];
        heap->vetor[1] = heap->vetor[heap->vetor[0] - 1];
        heap->vetor[0]--;
        heapify(heap, 1);
        return raiz;
    }
}

void imprimirHeap(MinHeap* heap) {
    if (heap != NULL && heap->vetor != NULL) {
        if (heap->vetor[0] == 0) {
            printf("Heap vazio!\n");
        }
        else {
            printf("Heap: ");
            for (int i = 0; i < heap->vetor[0]; i++) {
                printf("%d ", heap->vetor[i]);
            }
            printf("\n");
        }
    }
}

void destruirHeap(MinHeap* heap) {
    free(heap->vetor);
    free(heap);
}