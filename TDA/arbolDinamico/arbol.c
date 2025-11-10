#include "arbol.h"
#include <stdio.h>

void crearArbolBinBusq(tArbolBin *p)
{
    *p = NULL;
}

// Helper function for node creation (better than the complex macro)
static int crearNodoArbol(tNodoArbol **nue, const void *elem, size_t tamElem)
{
    *nue = (tNodoArbol *)malloc(sizeof(tNodoArbol));
    if (!*nue)
        return 0;

    (*nue)->info = malloc(tamElem);
    if (!(*nue)->info)
    {
        free(*nue);
        *nue = NULL;
        return 0;
    }

    memcpy((*nue)->info, elem, tamElem);
    (*nue)->tamInfo = tamElem;
    (*nue)->izq = (*nue)->der = NULL;
    return 1;
}

// Your existing insertion function - let's analyze it
int ponerEnArbolBin(tArbolBin *p, const void *elem, const size_t tamElem,
                    int (*cmp)(const void *, const void *))
{
    int res;

    while (*p)
    {
        res = cmp(elem, (*p)->info);
        if (res < 0)
            p = &(*p)->izq;
        else if (res > 0)
            p = &(*p)->der;
        else
            return 2; // Duplicate element
    }

    // Create and insert new node
    tNodoArbol *nue;
    if (!crearNodoArbol(&nue, elem, tamElem))
        return 0;

    *p = nue;
    return 1;
}
int buscarEnArbolBin(const tArbolBin *p, void *elem, size_t tamElem,
                     int (*cmp)(const void *, const void *))
{
    tNodoArbol *aux = *p;

    while (aux)
    {
        int res = cmp(elem, aux->info);
        if (res == 0)
        {
            // Found - copy the data
            memcpy(elem, aux->info, tamElem < aux->tamInfo ? tamElem : aux->tamInfo);
            return 1;
        }
        aux = (res < 0) ? aux->izq : aux->der;
    }
    return 0; // Not found
}

int arbolVacio(const tArbolBin *p)
{
    return *p == NULL;
}

void vaciarArbol(tArbolBin *p)
{
    if (!*p)
        return;

    vaciarArbol(&(*p)->izq);
    vaciarArbol(&(*p)->der);
    free((*p)->info);
    free(*p);
    *p = NULL;
}

int alturaArbol(const tArbolBin *p)
{
    if (!*p)
        return 0;

    int altIzq = alturaArbol(&(*p)->izq);
    int altDer = alturaArbol(&(*p)->der);

    return (altIzq > altDer ? altIzq : altDer) + 1;
}

void recorrerEnOrden(const tArbolBin *p, void (*accion)(const void *))
{
    if (!*p)
        return;

    recorrerEnOrden(&(*p)->izq, accion);
    accion((*p)->info);
    recorrerEnOrden(&(*p)->der, accion);
}

void recorrerPreOrden(const tArbolBin *p, void (*accion)(const void *))
{
    if (!*p)
        return;

    accion((*p)->info);
    recorrerPreOrden(&(*p)->izq, accion);
    recorrerPreOrden(&(*p)->der, accion);
}

void recorrerPostOrden(const tArbolBin *p, void (*accion)(const void *))
{
    if (!*p)
        return;

    recorrerPostOrden(&(*p)->izq, accion);
    recorrerPostOrden(&(*p)->der, accion);
    accion((*p)->info);
}