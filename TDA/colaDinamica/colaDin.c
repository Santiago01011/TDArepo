#include "colaDin.h"

int crearCola(tCola *p)
{
    p->ini = NULL;
    p->fin = NULL;
    return 1;
}

void vaciarCola(tCola *p)
{
    tNodoCola *aux = NULL;
    while (p->ini)
    {
        aux = p->ini;
        p->ini = aux->sig;
        free(aux->info);
        free(aux);
    }
    p->fin = NULL;
}

int ponerEnCola(tCola *p, const void *d, size_t tamElem)
{
    if(!p)
        return 0;
    tNodoCola *nue = (tNodoCola *)malloc(sizeof(tNodoCola));
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
    nue->sig = NULL;

    if (p->fin)
        p->fin->sig = nue;
    else
        p->ini = nue;
    p->fin = nue;
    return 1;
}

int sacarDeCola(tCola *p, void *d, size_t tamElem)
{
    if(!p)
        return 0;
    tNodoCola *aux;
    if (!p->ini)
        return 0;
    aux = p->ini;

    memcpy(d, aux->info, tamElem < aux->tamInfo ? tamElem : aux->tamInfo);
    p->ini = aux->sig;

    free(aux->info);
    free(aux);
    if (!p->ini)
        p->fin = NULL;
    return 1;
}

int verSiguienteEnCola(const tCola *p, void *d, size_t tamElem)
{
    tNodoCola *aux = p->ini;
    if (!p->ini)
        return 0;

    memcpy(d, aux->info, tamElem < aux->tamInfo ? tamElem : aux->tamInfo);
    return 1;
}

int colaVacia(const tCola *p)
{
    if (!p->ini)
        return 1;
    else
        return 0;
}

int cantidadElementosEnCola(const tCola *p)
{
    if (!p)
        return 0;
    int ce = 0;
    tNodoCola *aux = p->ini;
    while (aux)
    {
        ce ++;
        aux = aux->sig;
    }
    return ce;
}

void mapCola(tCola *p, void (*accion)(void*))
{
    tNodoCola *aux = p->ini;
    while (aux)
    {
        accion(aux->info);
        aux = aux->sig;
    }
}