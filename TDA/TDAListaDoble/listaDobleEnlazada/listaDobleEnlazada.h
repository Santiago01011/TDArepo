#ifndef listaEnlazadaDoble_h
#define listaEnlazadaDoble_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUPKEY -2

typedef struct sNodo{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig, *ant;
} tNodo;

typedef tNodo *tLista;
typedef int (*Cmp)(const void *, const void *);
typedef int (*Acum)(void **, unsigned *, const void *, unsigned);
typedef void (*print_callback)(void *);

//prototypes
void createDoubleList(tLista *p);
int isEmptyDoubleList(const tLista *p);
int isFullDoubleList(const tLista *p, unsigned cantBytes);
void clearDoubleList(tLista *p);
int addAtBeginningDoubleList(tLista *p, const void *d, unsigned cantBytes);
int removeFirstDoubleList(tLista *p, void *d, unsigned cantBytes);
int getFirstDoubleList(const tLista *p, void *d, unsigned cantBytes);
int addAtEndDoubleList(tLista *p, const void *d, unsigned cantBytes);
int removeLastDoubleList(tLista *p, void *d, unsigned cantBytes);
int getLastDoubleList(const tLista *p, void *d, unsigned cantBytes);
int addInOrderDoubleList(tLista *p, const void *d, unsigned cantBytes, Cmp cmp, Acum acum);
void sortDoubleList(tLista *p, Cmp cmp);
void mapDoubleList(tLista *p, void accion(void*, void*), void *param);
void filter(tLista *p, int condicion(const void*, void*), void *param);
void* reduce(tLista *p, void *res, void accion(const void*, void*, void*), void *param);

#endif