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

void invertirLista(tLista* p)
{
    if(!(*p)->sig)
        return;
    tNodo* resto=(*p)->sig;
    invertirLista(&resto);

    (*p)->sig->sig=*p;
    (*p)->sig=NULL;

    *p=resto;
}

tNodo** buscarMenorLista(tLista* p, int (*Cmp)(const void*, const void*))
{
    tNodo** menor=p;
    while(*p)
    {
        if(Cmp((*menor)->info, (*p)->info)>0)
            menor=p;
        p=&(*p)->sig;
    }
    return menor;
}
int ordenarListaSimple(tLista* p,int (*Cmp)(const void*, const void*))
{
    tNodo* aux, **menor;
    if(!*p)
        return 0;
    while(*p)
    {
        menor=buscarMenorLista(p, Cmp);
        if(*menor != *p)
        {
            aux=*menor;
            *menor=aux->sig;
            aux->sig=*p;
            *p=aux;
        }
        p=&(*p)->sig;
    }
    return 1;
}
