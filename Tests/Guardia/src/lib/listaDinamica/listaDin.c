#include "listaDin.h"

int crearLista(tLista *p)
{
    *p = NULL;
    return 1;
}

void vaciarLista(tLista *p)
{
    tNodo *aux;
    while (*p)
    {
        aux = *p;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
    *p = NULL;
}

int listaVacia(const tLista *p)
{
    return *p == NULL;
}

int ponerEnListaInicio(tLista *p, const void *elem, const size_t tamElem)
{
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));
    if (!nue)
        return 0;
    nue->info = malloc(tamElem);
    if (!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, elem, tamElem);
    nue->tamInfo = tamElem;
    nue->sig = *p;
    *p = nue;

    return 1;
}

int ponerEnListaFin(tLista *p, const void *elem, const size_t tamElem)
{
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));
    if (!nue)
        return 0;
    nue->info = malloc(tamElem);
    if (!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, elem, tamElem);
    nue->tamInfo = tamElem;
    nue->sig = NULL;

    while (*p)
        p = &(*p)->sig;

    *p = nue;
    return 1;
}

int sacarDeListaInicio(tLista *p, void *elem, const size_t tamElem)
{
    tNodo *aux = *p;
    if (aux == NULL)
        return 0;
    *p = aux->sig;
    memcpy(elem, aux->info, tamElem < aux->tamInfo ? tamElem : aux->tamInfo);
    free(aux->info);
    free(aux);
    return 1;
}

int sacarDeListaFinal(tLista *p, void *elem, const size_t tamElem)
{
    if (*p == NULL)
        return 0;
    while ((*p)->sig)
        p = &(*p)->sig;
    memcpy(elem, (*p)->info, tamElem < (*p)->tamInfo ? tamElem : (*p)->tamInfo);
    free((*p)->info);
    free(*p);
    *p = NULL;
    return 1;
}

int verPrimeroLista(const tLista *p, void *elem, const size_t tamElem)
{
    if (*p == NULL)
        return 0;
    memcpy(elem, (*p)->info, tamElem < (*p)->tamInfo ? tamElem : (*p)->tamInfo);
    return 1;
}

int verUltimoLista(const tLista *p, void *elem, const size_t tamElem)
{
    if (*p == NULL)
        return 0;
    while ((*p)->sig)
        p = &(*p)->sig;
    memcpy(elem, (*p)->info, tamElem < (*p)->tamInfo ? tamElem : (*p)->tamInfo);
    return 1;
}

void mapLista(tLista *p, void (*func)(void *))
{
    tNodo *aux = *p;
    while (aux)
    {
        func(aux->info);
        aux = aux->sig;
    }
}
