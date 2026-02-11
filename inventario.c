#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

/* ============================
   STRUCT LISTA ENCADEADA
============================ */

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* ============================
   VARIÁVEIS GLOBAIS
============================ */

static Item mochilaVetor[MAX_ITENS];
static int totalItensVetor = 0;

static No* mochilaLista = NULL;

static int comparacoesSequencial = 0;
static int comparacoesBinaria = 0;

/* ============================
   FUNÇÕES INTERNAS
============================ */

void inserirItemVetor(Item item) {
    if (totalItensVetor >= MAX_ITENS) {
        printf("❌ Mochila cheia!\n");
        return;
    }
    mochilaVetor[totalItensVetor++] = item;
}

void inserirItemLista(Item item) {
    No* novo = malloc(sizeof(No));
    novo->dados = item;
    novo->proximo = mochilaLista;
    mochilaLista = novo;
}

void listarVetor() {
    for (int i = 0; i < totalItensVetor; i++)
        printf("%d - %s | %s | %d\n",
               i+1,
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
}

void listarLista() {
    No* atual = mochilaLista;
    int i = 1;
    while (atual != NULL) {
        printf("%d - %s | %s | %d\n",
               i++,
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++)
        for (int j = 0; j < totalItensVetor - i - 1; j++)
            if (strcmp(mochilaVetor[j].nome,
                       mochilaVetor[j+1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
}

int buscarBinariaVetor(char nome[]) {
    int inicio = 0, fim = totalItensVetor - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0) return meio;
        if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

Item criarItem() {
    Item item;
    printf("Nome: ");
    scanf(" %[^\n]", item.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", item.tipo);
    printf("Quantidade: ");
    scanf("%d", &item.quantidade);
    return item;
}

/* ============================
   MENU INVENTÁRIO
============================ */

void menuInventario() {
    int opcao;
    char nomeBusca[30];

    do {
        printf("\n===== 🎒 INVENTÁRIO =====\n");
        printf("1 - Inserir\n");
        printf("2 - Listar vetor\n");
        printf("3 - Listar lista\n");
        printf("4 - Buscar sequencial\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Buscar binária\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Item item = criarItem();
                inserirItemVetor(item);
                inserirItemLista(item);
                break;
            }
            case 2: listarVetor(); break;
            case 3: listarLista(); break;
            case 4:
                printf("Nome: ");
                scanf(" %[^\n]", nomeBusca);
                buscarSequencialVetor(nomeBusca);
                printf("Comparações: %d\n", comparacoesSequencial);
                break;
            case 5:
                ordenarVetor();
                printf("Ordenado.\n");
                break;
            case 6:
                printf("Nome: ");
                scanf(" %[^\n]", nomeBusca);
                buscarBinariaVetor(nomeBusca);
                printf("Comparações: %d\n", comparacoesBinaria);
                break;
        }
    } while (opcao != 0);
}
