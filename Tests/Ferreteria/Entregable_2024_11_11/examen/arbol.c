#include "arbol.h"
#include <stdio.h>

static int crearNodo(tNodoArbol **nue, const void *info, unsigned tamInfo) {
    *nue = (tNodoArbol *)malloc(sizeof(tNodoArbol));
    if (!*nue) return 0;

    (*nue)->info = malloc(tamInfo);
    if (!(*nue)->info) {
        free(*nue);
        return 0;
    }

    memcpy((*nue)->info, info, tamInfo);
    (*nue)->tamInfo = tamInfo;
    (*nue)->izq = (*nue)->der = NULL;
    return 1;
}

int ponerEnArbolBin(tArbolBin *p, const void *elem, unsigned tamElem,
                    int (*cmp)(const void *, const void *)) {
    int res;

    while (*p) {
        res = cmp(elem, (*p)->info);
        if (res < 0)
            p = &(*p)->izq;
        else if (res > 0)
            p = &(*p)->der;
        else
            return 0;
    }

    return crearNodo(p, elem, tamElem);
}

int buscarEnArbolBin(const tArbolBin *p, void *elem, unsigned tamElem,
                     int (*cmp)(const void *, const void *)) {
    tNodoArbol *aux = *p;

    while (aux) {
        int res = cmp(elem, aux->info);
        if (res == 0) {
            memcpy(elem, aux->info, tamElem < aux->tamInfo ? tamElem : aux->tamInfo);
            return 1;
        }
        aux = (res < 0) ? aux->izq : aux->der;
    }
    return 0;
}


static int cargarDesdeDatosOrdenadosRec(tArbolBin *p, void *ds,
                                       unsigned (*leer)(void **, void *, unsigned, void *params),
                                       int li, int ls, void *params) {
    int m = (li + ls) / 2;
    int r;

    if (li > ls)
        return 1;

    *p = (tNodoArbol *)malloc(sizeof(tNodoArbol));
    if (!*p)
        return 0;

    (*p)->tamInfo = leer(&(*p)->info, ds, m, params);
    if (!(*p)->tamInfo) {
        free(*p);
        return 0;
    }

    (*p)->izq = (*p)->der = NULL;

    if ((r = cargarDesdeDatosOrdenadosRec(&(*p)->izq, ds, leer, li, m - 1, params)) != 1)
        return r;

    return cargarDesdeDatosOrdenadosRec(&(*p)->der, ds, leer, m + 1, ls, params);
}

int cargarDesdeDatosOrdenadosArbolBinBusq(tArbolBin *p, void *ds, unsigned cantReg,
                                         unsigned (*leer)(void **, void *, unsigned, void *params),
                                         void *params) {
    if (*p || !ds)
        return 0;

    return cargarDesdeDatosOrdenadosRec(p, ds, leer, 0, cantReg - 1, params);
}

void vaciarArbolBin(tArbolBin *p) {
    if (!*p) return;

    vaciarArbolBin(&(*p)->izq);
    vaciarArbolBin(&(*p)->der);
    free((*p)->info);
    free(*p);
    *p = NULL;
}

int arbolVacio(const tArbolBin *p) {
    return *p == NULL;
}

unsigned leerDesdeArchivoBin(void **d, void *pf, unsigned pos, void *params) {
    unsigned tam = *((unsigned *)params);
    *d = malloc(tam);
    if (!*d)
        return 0;
    fseek((FILE *)pf, pos * tam, SEEK_SET);
    return fread(*d, tam, 1, (FILE *)pf) ? tam : 0;
}

unsigned leerDesdeArray(void **d, void *vec, unsigned pos, void *params) {
    unsigned tam = *((unsigned *)params);
    *d = malloc(tam);
    if (!*d)
        return 0;
    memcpy(*d, (char *)vec + (pos * tam), tam);
    return tam;
}
