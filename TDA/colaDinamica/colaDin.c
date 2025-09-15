#include "colaDin.h"

int crearCola(tCola *p)
{
    p->ini = NULL;
    p->fin = NULL;
    return 1;
}

void vaciarCola(tCola *p)
{
    tNodo *aux = NULL;
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
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));
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

    // Si existe un elemento al final de la lista, asignarle nue como siguiente
    if (p->fin)
        p->fin->sig = nue;
    // Si no existe, la lista estaba vacía, ini y fin quedan como el mismo nodo
    else
        p->ini = nue;
    // asignar nue como último nodo de la lista
    p->fin = nue;
    return 1;
}

int sacarDeCola(tCola *p, void *d, size_t tamElem)
{
    tNodo *aux = p->ini;
    if (!p->ini)
        return 0;

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
    tNodo *aux = p->ini;
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
    int ce = 0;
    tNodo *aux = p->ini;
    while (aux)
    {
        ce ++;
        aux = aux->sig;
    }
    return ce;
}