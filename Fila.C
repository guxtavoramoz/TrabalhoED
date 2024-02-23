#include <stdio.h>
#include <stdlib.h>

// estrutura do nó da fila
typedef struct No {
    int dado;
    int prioridade; // 0: Baixa, 1: Média, 2: Alta
    struct No* prox;
    struct No* ant;
} No;

// estrutura da fila de prioridade
typedef struct FilaPrioridade {
    No* frente;
    No* tras;
} FilaPrioridade;

// Inicialização da fila de prioridade
void inicializarFila(FilaPrioridade* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

// Verifica se a fila de prioridade está vazia
int estaVazia(FilaPrioridade* fila) {
    return fila->frente == NULL;
}

// Insere um elemento na fila de prioridade com base na prioridade
void enfileirar(FilaPrioridade* fila, int dado, int prioridade) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->prioridade = prioridade;
    novoNo->prox = NULL;
    novoNo->ant = NULL;

    if (estaVazia(fila)) {
        fila->frente = novoNo;
        fila->tras = novoNo;
    } else {
        No* atual = fila->frente;
        while (atual != NULL && atual->prioridade >= prioridade) {
            atual = atual->prox;
        }

        if (atual == NULL) {
            // Inserir no final
            novoNo->ant = fila->tras;
            fila->tras->prox = novoNo;
            fila->tras = novoNo;
        } else {
            // Inserir antes do atual
            novoNo->prox = atual;
            novoNo->ant = atual->ant;

            if (atual->ant != NULL) {
                atual->ant->prox = novoNo;
            } else {
                fila->frente = novoNo;
            }

            atual->ant = novoNo;
        }
    }
}

// Remove e retorna o elemento de maior prioridade da fila
int desenfileirar(FilaPrioridade* fila) {
    if (estaVazia(fila)) {
        printf("A fila de prioridade está vazia.\n");
        exit(EXIT_FAILURE);
    }

    int dado = fila->frente->dado;
    No* temp = fila->frente;

    if (fila->frente == fila->tras) {
        // Único elemento na fila
        fila->frente = NULL;
        fila->tras = NULL;
    } else {
        // Mais de um elemento na fila
        fila->frente = fila->frente->prox;
        fila->frente->ant = NULL;
    }

    free(temp);
    return dado;
}

// Função de teste
void testarFilaPrioridade() {
    FilaPrioridade fila;
    inicializarFila(&fila);

    enfileirar(&fila, 10, 1);  // Média prioridade
    enfileirar(&fila, 5, 0);   // Baixa prioridade
    enfileirar(&fila, 20, 2);  // Alta prioridade
    enfileirar(&fila, 15, 1);  // Média prioridade

    printf("Elementos removidos com base na prioridade:\n");

    while (!estaVazia(&fila)) {
        printf("%d ", desenfileirar(&fila));
    }

    printf("\n");
}

int main() {
    testarFilaPrioridade();

    return 0;
}
