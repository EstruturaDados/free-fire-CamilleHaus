#ifndef TORRE_H
#define TORRE_H

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

void menuTorre();

#endif
