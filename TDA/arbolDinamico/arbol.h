#ifndef ARBOL_H
#define ARBOL_H

#include <stdlib.h>
#include <string.h>

typedef struct sNodoArbol{
    void *info;
    size_t tamInfo;
    struct sNodoArbol *izq, *der;
} tNodoArbol;

typedef tNodoArbol *tArbolBin;

int ponerEnArbolBin(tArbolBin *p, const void *elem, const size_t tamElem, int (*cmp)(const void *, const void *));
int cargarArbolBinDatosOrd(tArbolBin *p, void *ds);


#endif // ARBOL_H
