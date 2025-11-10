#include "../include/arbol.h"
#define MIN(x,y) ((x) > (y)? (x) : (y))

tNodoArbol** buscar_nodo(const tArbolBinBusq* pa, const void* dato, int cmp(const void*, const void*))
{
    int rcmp;
    while(*pa && (rcmp = cmp(dato,(*pa)->info)))
    {
        if(rcmp > 0)
            pa = &(*pa)->der;
        else
            pa = &(*pa)->izq;
    }
    if(!*pa)
        return NULL;
    return (tNodoArbol**)pa;
}

int buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *))
{
    if(!(p = buscar_nodo(p,d,cmp)))
        return 0; //nodo no encontrado
    memcpy(d,(*p)->info,MIN(tam,(*p)->tamInfo));
    return 1;
}

