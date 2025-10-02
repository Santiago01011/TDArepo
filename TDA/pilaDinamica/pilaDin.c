#include "pilaDin.h"
#include <stdio.h>

int crearPila(tPila *p)
{
    *p = NULL;
    return 1;
}

void vaciarPila(tPila *p)
{
    tNodoPila *aux = NULL;
    while (*p)
    {
        aux = *p;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int ponerEnPila(tPila *p, const void *d, size_t tamElem)
{
    tNodoPila *nue = (tNodoPila *)malloc(sizeof(tNodoPila));
    if (!nue)
        return 0;
    nue->info = malloc(tamElem);
    if (!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, tamElem);
    nue->tamInfo = tamElem;
    nue->sig = *p;
    *p = nue;
    return 1;
}

int sacarDePila(tPila *p, void *d, size_t tamElem)
{
    tNodoPila *aux = *p;
    if (!*p)
        return 0;
    memcpy(d, aux->info, tamElem < aux->tamInfo ? tamElem : aux->tamInfo);
    *p = aux->sig;
    free(aux->info);
    free(aux);
    return 1;
}

int verTopePila(const tPila *p, void *d, size_t tamElem)
{
    tNodoPila *aux = *p;
    if (!*p)
        return 0;
    memcpy(d, aux->info, tamElem < aux->tamInfo ? tamElem : aux->tamInfo);
    return 1;
}
