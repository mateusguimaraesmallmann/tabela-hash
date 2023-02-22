#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABELA 100

typedef struct no {
    char* chave;
    struct no* prox;
} No;

typedef struct {
    No** lista;
    int tamanho;
} TabelaHash;

void exibirLista(No *pNo);

int funcaoHash(char* chave) {

    int soma = 0;

    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAM_TABELA;
}

TabelaHash* criarTabelaHash() {

    TabelaHash* tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    tabela->lista = (No**) calloc(TAM_TABELA, sizeof(No*));
    tabela->tamanho = 0;
    return tabela;
}

void inserir(TabelaHash* tabela, char* chave) {

    int indice = funcaoHash(chave);
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->prox = tabela->lista[indice];
    tabela->lista[indice] = novoNo;
    tabela->tamanho++;
}

No* buscar(TabelaHash* tabela, char* chave) {

    int indice = funcaoHash(chave);
    No* atual = tabela->lista[indice];

    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void remover(TabelaHash* tabela, char* chave) {

    int indice = funcaoHash(chave);
    No* anterior = NULL;
    No* atual = tabela->lista[indice];

    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            if (anterior == NULL) {
                tabela->lista[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            tabela->tamanho--;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}


void exibir(TabelaHash* tabela) {

    for (int i = 0; i < TAM_TABELA; i++) {
        printf("Tabela[%d]: ", i);
        exibirLista(tabela->lista[i]);
        printf("NULL\n");
    }
}

void exibirLista(No* lista) {

    No* atual = lista;
    while (atual != NULL) {
        printf("%s -> ", atual->chave);
        atual = atual->prox;
    }
};
