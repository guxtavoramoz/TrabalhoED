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
    struct No* frente;
    struct No* tras;
} FilaPrioridade;
 
// Inicialização da fila de prioridade
FilaPrioridade* inicializarFila() {
    FilaPrioridade* fila = (FilaPrioridade*) malloc(sizeof(FilaPrioridade));
    if(fila != NULL){
        fila->frente = NULL;
        fila->tras = NULL;
    }
    return fila;
}
 
// Verifica se a fila de prioridade está vazia
int estaVazia(FilaPrioridade* fila) {
    if(fila == NULL)
        return 1;
    if(fila->frente == NULL)
        return 1;
    return 0;
}
 
// Insere um elemento na fila de prioridade com base na prioridade
int enfileirar(FilaPrioridade* fila, int dado, int prioridade) {
    if (fila == NULL)
        return 0;

    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->prioridade = prioridade;
    novoNo->prox = NULL;
    novoNo->ant = NULL;
 
    if (estaVazia(fila)) {
        fila->frente = novoNo;
        fila->tras = novoNo;
    } 
    else {
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
    return 1;
}
 
// Remove e retorna o elemento de maior prioridade da fila
int desenfileirar(FilaPrioridade* fila) {
    if (estaVazia(fila)) {
        printf("A fila de prioridade esta vazia.\n");
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

void limparFila(FilaPrioridade* fila) {
    if (estaVazia(fila)) {
        printf("A fila de prioridade esta vazia.\n");
        exit(EXIT_FAILURE);
    }

    while (!estaVazia(fila)) {
        No* temp = fila->frente;
        fila->frente = fila->frente->prox;
        free(temp);
    }
    fila->tras = NULL; // ultimo elemento recebe null
}
 
// Retorna a quantidade de elementos na fila
int tamanhoFila(FilaPrioridade* fila) {
    if(fila == NULL)
        return 0;

    int tamanho = 0;
    No* atual = fila->frente;
 
    while (atual != NULL) {
        tamanho++;
        atual = atual->prox;
    }
 
    return tamanho;
}
 
// Modifica a prioridade de um elemento existente na fila de prioridade
void modificaElemento(FilaPrioridade* fila, int dado, int novaPrioridade) {
    No* atual = fila->frente;
 
    // Procura o elemnto em especifico
    while (atual != NULL && atual->dado != dado) {
        atual = atual->prox;
    }
 
    // Verifica se o elemento foi encontrado na fila
    if (atual == NULL) {
        printf("Elemento nao encontrado na fila.\n");//caso nao seja encontrado
        return;
    }
 
    // Atualiza a prioridade do elemento encontrado
    atual->prioridade = novaPrioridade;
}

void imprimeFilaPrioridade(FilaPrioridade* fila){
    No* atual = fila->frente;
    while(atual != NULL){
        printf("Dado: %d, Prioridade: %d\n", atual->dado, atual->prioridade);
        atual = atual->prox;
    }
}
 
// Funcoes de teste
void testeFilaPrioridade() {
    // Teste de enfileiramente e desenfileiramento de elementos

    FilaPrioridade* fila;
    fila = inicializarFila();
 
    enfileirar(fila, 10, 1);  // Média prioridade
    enfileirar(fila, 5, 0);   // Baixa prioridade
    enfileirar(fila, 20, 2);  // Alta prioridade
    enfileirar(fila, 15, 1);  // Média prioridade

    imprimeFilaPrioridade(fila);
    printf("Tamanho da fila atualmente: %d\n", tamanhoFila(fila));
    printf("-------------------------\n");
 
    printf("Elementos removidos com base na prioridade:\n");
 
    while (!estaVazia(fila)) {
        printf("%d ", desenfileirar(fila));
    }
 
    printf("\n");
 
    printf("-------------------------\n");
    imprimeFilaPrioridade(fila);
    printf("Tamanho da fila apos desenfileirar: %d\n", tamanhoFila(fila));
}

void testeLimpezaFila(){
    // Teste de limpeza da fila

    FilaPrioridade* fila;
    fila = inicializarFila();
 
    enfileirar(fila, 10, 1);  // Média prioridade
    enfileirar(fila, 5, 0);   // Baixa prioridade
    enfileirar(fila, 20, 2);  // Alta prioridade
    enfileirar(fila, 15, 1);  // Média prioridade

    imprimeFilaPrioridade(fila);
    printf("Tamanho da fila atualmente: %d\n", tamanhoFila(fila));
    printf("-------------------------\n");

    limparFila(fila);
    printf("LIMPEZA DA FILA\n");
    printf("-------------------------\n");

    imprimeFilaPrioridade(fila);
    printf("Tamanho da fila apos limpeza: %d\n", tamanhoFila(fila));
}

void testeAlteracaoPrioridade(){
    // Teste para modificacao da prioridade de um elemento

    FilaPrioridade* fila;
    fila = inicializarFila();

    enfileirar(fila, 10, 1);  // Média prioridade
    enfileirar(fila, 5, 0);   // Baixa prioridade
    enfileirar(fila, 20, 2);  // Alta prioridade
    enfileirar(fila, 15, 1);  // Média prioridade

    imprimeFilaPrioridade(fila);
    printf("Tamanho da fila antes da modificacao: %d\n", tamanhoFila(fila));
    printf("-------------------------\n");

    modificaElemento(fila, 5, 2); // Muda a prioridade do elemento 5 de 0 (Baixa) para 2 (Alta)
    printf("MODIFICACAO DA FILA\n");
    printf("Mudanca na prioridade do elemento 5 de 0 (Baixa) para 2 (Alta)\n");
    printf("-------------------------\n");
  
    imprimeFilaPrioridade(fila);
    printf("Tamanho da fila apos a modificacao: %d\n", tamanhoFila(fila));
}
