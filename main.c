#include <stdio.h>
#include "inventario.h"
#include "torre.h"

int main() {
    int opcao;

    do {
        printf("\n===== 🎮 SISTEMA PRINCIPAL =====\n");
        printf("1 - Módulo Inventário\n");
        printf("2 - Módulo Torre de Fuga\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: menuInventario(); break;
            case 2: menuTorre(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
