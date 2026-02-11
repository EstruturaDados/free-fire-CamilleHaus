#ifndef INVENTARIO_H
#define INVENTARIO_H

#define MAX_ITENS 50

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void menuInventario();

#endif
