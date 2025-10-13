#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct sNodo{
    void *dato;
    unsigned tamDato;
    struct sNodo *sig;
    struct sNodo *ant;
}tNodo;

typedef tNodo *tLista;

void crearLista(tLista*lista);
int insertarOrdenado(tLista*lista, const void*dato, unsigned tamDato, int(*comparar)(const void*, const void*));
void maplistaIzq(tLista*lista, void (*accion)(const void*));
void maplistaDer(tLista*lista, void (*accion)(const void*));
int cmpint(const void *x, const void *y);
void imprimirInt(const void * dato);
void destruirLista(tLista*lista);


#endif // LISTA_H_INCLUDED
