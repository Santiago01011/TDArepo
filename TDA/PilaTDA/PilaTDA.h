#ifndef PILATDA_H_INCLUDED
#define PILATDA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PILA 40
#define PILA_LLENA 0
#define PILA_VACIA 1
#define TODO_OK 0
#define MIN(x,y)((x)<(y)?(x):(y))
/*
typedef struct {
    char vec[TAM_PILA];
    unsigned tope;
}tPila;
*/
typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;
/*
void crearPila(tPila* pp);
int ponerEnPila(tPila* pp, const void* dato, size_t tam);
int sacarDePila(tPila* pp, void* dato, size_t tam);
void mostrarPila(tPila* pp, size_t tam);
*/
void crearPila(tPila* pp);
int ponerEnPila(tPila* pp, const void* pd, unsigned tam);
int sacarDePila(tPila* pp, void* pd, unsigned tam);


#endif // PILATDA_H_INCLUDED
