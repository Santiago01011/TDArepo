#include "listaDin.h"


void crearLista(tLista *pl)
{
    *pl = NULL;
}

void destruirLista(tLista *pl)
{
    tNodo *aux;
    while(*pl)
    {
        aux = *pl;
        *pl = aux->sig;
        free(aux->elem);
        free(aux);
    }
    *pl = NULL;
}

int ponerEnListaFin(tLista *pl, const void *elem, const size_t tamElem)
{
    tNodo *nue = (tNodo*)malloc(sizeof(tNodo));
    if (!nue)
    {
        return 0;
    }
    nue->elem = malloc(tamElem);
    if (!nue->elem)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->elem, elem, tamElem);
    nue->tamElem = tamElem;
    nue->sig = NULL;
    while(*pl)
    {
        pl = &(*pl)->sig;
    }
    *pl = nue;
    return 1;
}

void ordenarListaInsercion(tLista *pl, int (*cmp)(const void *, const void *))
{
    tLista listaOrdenada = NULL;
    tNodo *aux;
    tNodo **q;
    while (*pl)
    {
        aux = *pl;
        *pl = aux->sig;
        aux->sig = NULL;
        q = &listaOrdenada;
        while (*q && cmp((*q)->elem, aux->elem) < 0)
            q = &(*q)->sig;
        aux->sig = *q;
        *q = aux;
    }
    *pl = listaOrdenada;
}

int mapLista(tLista *pl, void (*func)(void*))
{
    tNodo *aux = *pl;
    while (aux)
    {
        func(aux->elem);
        aux = aux->sig;
    }
    return 1;
}

int ponerEnListaTop(tLista *pl, const void *elem, size_t tamElem,
                    int (*cmp)(const void*, const void*), int *top)
{
    tNodo *nue, *ant = NULL, *act = *pl;
    int ce = 0;
    while (act && cmp(elem, act->elem) > 0)
    {
        ant = act;
        act = act->sig;
        ce++;
    }
    nue = (tNodo*)malloc(sizeof(tNodo));
    if (!nue)
        return 0;

    nue->elem = malloc(tamElem);
    if (!nue->elem)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->elem, elem, tamElem);
    nue->tamElem = tamElem;
    nue->sig = act;
    if (ant)
        ant->sig = nue;
    else
        *pl = nue;

    ce = 0;
    tNodo *aux = *pl, *prev = NULL;
    while (aux)
    {
        ce++;
        if (ce > *top)
            break;
        prev = aux;
        aux = aux->sig;
    }

    if (aux)
    {
        while (aux && cmp(prev->elem, aux->elem) == 0)
        {
            prev = aux;
            aux = aux->sig;
        }
        if (aux)
        {
            prev->sig = NULL;
            while (aux)
            {
                tNodo *bor = aux;
                aux = aux->sig;
                free(bor->elem);
                free(bor);
            }
        }
    }
    return 1;
}

int sacarDeListaInicio(tLista *pl, void *elem, const size_t tamElem)
{
    tNodo *aux = *pl;
    if (!aux)
        return 0;
    *pl = aux->sig;
    memcpy(elem, aux->elem, tamElem > aux->tamElem ? tamElem : aux->tamElem);
    free(aux->elem);
    free(aux);
    return 1;
}










