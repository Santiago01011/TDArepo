#ifndef LISTA_DIN_H
#define LISTA_DIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo
{
    void *elem;
    size_t tamElem;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

void crearLista(tLista *pl);
void destruirLista(tLista *pl);
tNodo **_buscarMenorLista(tLista *pl, int (*cmp)(const void*, const void*));
int ordenarLista(tLista *pl, int (*cmp)(const void*, const void*));
int mapLista(tLista *pl, void (*func)(void*));
int ponerEnListaFin(tLista *pl, const void *elem, const size_t tamElem);
int ponerEnListaTop(tLista *pl, const void *elem, const size_t tamElem, int (*cmp)(const void*, const void*), int *top);
int sacarDeListaInicio(tLista *pl, void *elem, const size_t tamElem);
void ordenarListaInsercion(tLista *pl, int (*cmp)(const void *, const void *));

#endif // LISTA_DIN_H
