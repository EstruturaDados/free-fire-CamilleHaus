#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "torre.h"

static Componente componentes[MAX_COMPONENTES];
static int totalComponentes = 0;
static long comparacoes = 0;

/* ============================
   FUNÇÕES
============================ */

void cadastrarComponentes() {
    printf("Quantidade (max 20): ");
    scanf("%d", &totalComponentes);
    getchar();

    if (totalComponentes > MAX_COMPONENTES)
        totalComponentes = MAX_COMPONENTES;

    for (int i = 0; i < totalComponentes; i++) {
        printf("\nComponente %d\n", i+1);

        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome,"\n")] = 0;

        printf("Tipo: ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo,"\n")] = 0;

        printf("Prioridade: ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }
}

void mostrarComponentes() {
    for (int i = 0; i < totalComponentes; i++)
        printf("%d - %s | %s | %d\n",
               i+1,
               componentes[i].nome,
               componentes[i].tipo,
               componentes[i].prioridade);
}

void bubbleSortNome() {
    comparacoes = 0;
    for (int i = 0; i < totalComponentes-1; i++)
        for (int j = 0; j < totalComponentes-i-1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome,
                       componentes[j+1].nome) > 0) {
                Componente t = componentes[j];
                componentes[j] = componentes[j+1];
                componentes[j+1] = t;
            }
        }
}

void insertionSortTipo() {
    comparacoes = 0;
    for (int i = 1; i < totalComponentes; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        while (j >= 0 &&
               strcmp(componentes[j].tipo,
                      chave.tipo) > 0) {
            comparacoes++;
            componentes[j+1] = componentes[j];
            j--;
        }
        comparacoes++;
        componentes[j+1] = chave;
    }
}

void selectionSortPrioridade() {
    comparacoes = 0;
    for (int i = 0; i < totalComponentes-1; i++) {
        int min = i;
        for (int j = i+1; j < totalComponentes; j++) {
            comparacoes++;
            if (componentes[j].prioridade <
                componentes[min].prioridade)
                min = j;
        }
        Componente t = componentes[i];
        componentes[i] = componentes[min];
        componentes[min] = t;
    }
}

int buscaBinaria(char chave[]) {
    int inicio = 0, fim = totalComponentes-1;
    while (inicio <= fim) {
        int meio = (inicio+fim)/2;
        int cmp = strcmp(componentes[meio].nome, chave);
        if (cmp == 0) return meio;
        if (cmp < 0) inicio = meio+1;
        else fim = meio-1;
    }
    return -1;
}

void medirTempo(void (*algoritmo)()) {
    clock_t ini = clock();
    algoritmo();
    clock_t fim = clock();

    double tempo = (double)(fim-ini)/CLOCKS_PER_SEC;
    printf("Comparações: %ld\n", comparacoes);
    printf("Tempo: %.6f s\n", tempo);
}

/* ============================
   MENU TORRE
============================ */

void menuTorre() {
    int opcao;
    char chave[30];

    do {
        printf("\n===== 🏗️ TORRE =====\n");
        printf("1 - Cadastrar\n");
        printf("2 - Bubble (Nome)\n");
        printf("3 - Insertion (Tipo)\n");
        printf("4 - Selection (Prioridade)\n");
        printf("5 - Busca binária (Nome)\n");
        printf("6 - Mostrar\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarComponentes(); break;
            case 2: medirTempo(bubbleSortNome); break;
            case 3: medirTempo(insertionSortTipo); break;
            case 4: medirTempo(selectionSortPrioridade); break;
            case 5:
                printf("Nome: ");
                fgets(chave,30,stdin);
                chave[strcspn(chave,"\n")] = 0;
                if (buscaBinaria(chave) != -1)
                    printf("Encontrado!\n");
                else
                    printf("Não encontrado.\n");
                break;
            case 6: mostrarComponentes(); break;
        }
    } while (opcao != 0);
}
