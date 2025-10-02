#include "listaDin.h"

static tLista mergesort(tLista lista, int (*cmp)(const void *, const void *));
static tLista dividirLista(tLista lista);
static tLista fusionarListas(tLista a, tLista b, int (*cmp)(const void *, const void *));

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

int ponerEnOrden(tLista *p, const void *elem, const size_t tamElem, int (*cmp)(const void *, const void *))
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
    while ((*p) && cmp((*p)->info, elem))
        p = &(*p)->sig;
    memcpy(nue->info, elem, tamElem);
    nue->tamInfo = tamElem;
    nue->sig = (*p);
    (*p) = nue;
    return 1;
}

void ordenarListaInsercion(tLista *p, int (*cmp)(const void *, const void *))
{
    tLista listaOrdenada;
    crearLista(&listaOrdenada);
    tNodo *aux;
    tNodo **q;
    while (*p)
    {
        aux = *p;
        *p = aux->sig;
        aux->sig = NULL;
        q = &listaOrdenada;
        while (*q && cmp((*q)->info, aux->info) < 0)
            q = &(*q)->sig;
        aux->sig = *q;
        *q = aux;
    }
    *p = listaOrdenada;
}

void ordenarListaMergesort(tLista *p, int (*cmp)(const void *, const void *))
{
    *p = mergesort(*p, cmp);
}

static tLista mergesort(tLista lista, int (*cmp)(const void *, const void *))
{
    if (lista == NULL || lista->sig == NULL)
        return lista;

    tLista mitad = dividirLista(lista);
    tLista izquierda = mergesort(lista, cmp);
    tLista derecha = mergesort(mitad, cmp);

    return fusionarListas(izquierda, derecha, cmp);
}

static tLista dividirLista(tLista lista)
{
    if (lista == NULL || lista->sig == NULL)
        return NULL;

    tLista lento = lista;
    tLista rapido = lista->sig;

    while (rapido != NULL && rapido->sig != NULL)
    {
        lento = lento->sig;
        rapido = rapido->sig->sig;
    }

    tLista mitad = lento->sig;
    lento->sig = NULL;

    return mitad;
}

static tLista fusionarListas(tLista a, tLista b, int (*cmp)(const void *, const void *))
{
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    tLista resultado = NULL;
    tLista *ultimo = &resultado;

    while (a != NULL && b != NULL)
    {
        if (cmp(a->info, b->info) <= 0)
        {
            *ultimo = a;
            a = a->sig;
        }
        else
        {
            *ultimo = b;
            b = b->sig;
        }
        ultimo = &(*ultimo)->sig;
    }

    *ultimo = (a != NULL) ? a : b;

    return resultado;
}