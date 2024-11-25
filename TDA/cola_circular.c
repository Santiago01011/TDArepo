#include "cola_circular.h"
#include <stdlib.h>
#include <string.h>


void crear_cola(tCola * pc)
{
    *pc= NULL;
}

int poner_en_cola(tCola * pc, const void * pd, unsigned tam)
{
    tNodo* nue;
    if((nue = (tNodo*)malloc(sizeof(tNodo))) == NULL ||
       (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return 0;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);

    if(!*pc)
        nue->sig = nue;
    else
    {
        nue->sig = (*pc)->sig;
        (*pc)->sig = nue;
    }
    *pc = nue;

    return 1;
}

int sacar_de_cola(tCola * pc, void * pd, unsigned tam)
{
    tNodo* elim;
    if(!*pc)
        return 0;

    elim = (*pc)->sig;
    memcpy(pd, elim->info, MINIMO(tam, elim->tamInfo));

    if (elim->sig == elim)
        *pc = NULL;
    else
        (*pc)->sig = elim->sig;

    free(elim->info);
    free(elim);

    return 1;
}

int cola_vacia(const tCola * pc)
{
    return !*pc;
}
