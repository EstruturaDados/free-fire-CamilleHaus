#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 50

/* ============================
   STRUCTS
============================ */

// Item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* ============================
   VARIÁVEIS GLOBAIS
============================ */

// Mochila com vetor
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// Mochila com lista encadeada
No* mochilaLista = NULL;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/* ============================
   FUNÇÕES — VETOR
============================ */

// Inserir item no vetor
void inserirItemVetor(Item item) {
    if (totalItensVetor >= MAX_ITENS) {
        printf("❌ Mochila (vetor) cheia!\n");
        return;
    }
    mochilaVetor[totalItensVetor++] = item;
}

// Listar itens do vetor
void listarVetor() {
    if (totalItensVetor == 0) {
        printf("📦 Mochila (vetor) vazia.\n");
        return;
    }

    for (int i = 0; i < totalItensVetor; i++) {
        printf("%d - %s | %s | %d\n",
               i + 1,
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;

    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

// Ordenação Bubble Sort por nome
void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
}

// Busca binária no vetor (exige vetor ordenado)
int buscarBinariaVetor(char nome[]) {
    int inicio = 0, fim = totalItensVetor - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// Remover item do vetor
void removerItemVetor(char nome[]) {
    int pos = buscarSequencialVetor(nome);

    if (pos == -1) {
        printf("❌ Item não encontrado no vetor.\n");
        return;
    }

    for (int i = pos; i < totalItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }

    totalItensVetor--;
    printf("🗑️ Item removido do vetor.\n");
}

/* ============================
   FUNÇÕES — LISTA ENCADEADA
============================ */

// Inserir item na lista
void inserirItemLista(Item item) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dados = item;
    novo->proximo = mochilaLista;
    mochilaLista = novo;
}

// Listar itens da lista
void listarLista() {
    if (mochilaLista == NULL) {
        printf("📦 Mochila (lista) vazia.\n");
        return;
    }

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

// Busca sequencial na lista
No* buscarLista(char nome[]) {
    comparacoesSequencial = 0;
    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

// Remover item da lista
void removerItemLista(char nome[]) {
    No *atual = mochilaLista, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                mochilaLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("🗑️ Item removido da lista.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("❌ Item não encontrado na lista.\n");
}

/* ============================
   FUNÇÃO AUXILIAR
============================ */

// Criar item via teclado
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
   MAIN
============================ */

int main() {
    int opcao;
    char nomeBusca[30];

    do {
        printf("\n===== 🎒 INVENTÁRIO COMPARATIVO =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Listar vetor\n");
        printf("3 - Listar lista\n");
        printf("4 - Buscar sequencial (vetor)\n");
        printf("5 - Buscar binária (vetor)\n");
        printf("6 - Buscar na lista\n");
        printf("7 - Remover do vetor\n");
        printf("8 - Remover da lista\n");
        printf("9 - Ordenar vetor\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Item item = criarItem();
                inserirItemVetor(item);
                inserirItemLista(item);
                break;
            }
            case 2:
                listarVetor();
                break;
            case 3:
                listarLista();
                break;
            case 4:
                printf("Nome: ");
                scanf(" %[^\n]", nomeBusca);
                buscarSequencialVetor(nomeBusca);
                printf("Comparações (sequencial vetor): %d\n", comparacoesSequencial);
                break;
            case 5:
                printf("Nome: ");
                scanf(" %[^\n]", nomeBusca);
                buscarBinariaVetor(nomeBusca);
                printf("Comparações (binária): %d\n", comparacoesBinaria);
                break;
            case 6:
                printf("Nome: ");
                scanf(" %[^\n]", nomeBusca);
                buscarLista(nomeBusca);
                printf("Comparações (lista): %d\n", comparacoesSequencial);
                break;
            case 7:
                printf("Nome: ");
                scanf(" %[^\n]", nomeBusca);
                removerItemVetor(nomeBusca);
                break;
            case 8:
                printf("Nome: ");
                scanf(" %[^\n]", nomeBusca);
                removerItemLista(nomeBusca);
                break;
            case 9:
                ordenarVetor();
                printf("✅ Vetor ordenado.\n");
                break;
            case 0:
                printf("👋 Saindo...\n");
                break;
            default:
                printf("⚠️ Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
