#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];       // Nome do item (ex: Pistola)
    char tipo[20];       // Tipo do item (arma, municao, cura, etc)
    int quantidade;      // Quantidade do item
} Item;

// Vetor que simula a mochila
Item mochila[MAX_ITENS];
int totalItens = 0; // Controla quantos itens já existem na mochila

// Função para listar todos os itens da mochila
void listarItens() {
    printf("\n📦 Itens na mochila:\n");

    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d - Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// Função para inserir um novo item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novoItem.nome);

    printf("Digite o tipo do item (arma, municao, cura, etc): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);

    // Adiciona o item no vetor
    mochila[totalItens] = novoItem;
    totalItens++;

    printf("\n✅ Item adicionado com sucesso!\n");
    listarItens();
}

// Função de busca sequencial por nome
int buscarItem(char nome[]) {
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i; // Retorna a posição do item
        }
    }
    return -1; // Item não encontrado
}

// Função para remover um item pelo nome
void removerItem() {
    char nome[30];

    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nome);

    int posicao = buscarItem(nome);

    if (posicao == -1) {
        printf("\n❌ Item não encontrado na mochila.\n");
        return;
    }

    // Move os itens para "fechar o buraco" no vetor
    for (int i = posicao; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;

    printf("\n🗑️ Item removido com sucesso!\n");
    listarItens();
}

// Função para buscar e exibir um item
void exibirItemBuscado() {
    char nome[30];

    printf("\nDigite o nome do item para busca: ");
    scanf(" %[^\n]", nome);

    int posicao = buscarItem(nome);

    if (posicao == -1) {
        printf("\n❌ Item não encontrado.\n");
    } else {
        printf("\n🔍 Item encontrado:\n");
        printf("Nome: %s\n", mochila[posicao].nome);
        printf("Tipo: %s\n", mochila[posicao].tipo);
        printf("Quantidade: %d\n", mochila[posicao].quantidade);
    }
}

// Função principal com menu
int main() {
    int opcao;

    do {
        printf("\n===== 🎒 INVENTÁRIO DO JOGADOR =====\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                exibirItemBuscado();
                break;
            case 0:
                printf("\n👋 Saindo do inventário...\n");
                break;
            default:
                printf("\n⚠️ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
