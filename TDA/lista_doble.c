#include "lista_doble.h"
#include <stdlib.h>
#include <string.h>


void crearListaD(tListaD* pl)
{
    *pl = NULL;
}

int ponerOrdListaD(tListaD* pl, const void * pd, unsigned tam,
                   int (*cmp)(const void*, const void*))
{
    tNodoD* auxSig = *pl,
          * auxAnt = auxSig? auxSig->ant : NULL,
          * nue;

    while(auxSig && cmp(pd, auxSig->info)>0)
    {
        auxAnt = auxSig;
        auxSig = auxSig->sig;
    }

    while(auxAnt && cmp(pd, auxAnt->info)<0)
    {
        auxSig = auxAnt;
        auxAnt = auxAnt->ant;
    }

    if((auxSig && cmp(pd, auxSig->info)==0)
       || (auxAnt && cmp(pd, auxAnt->info)==0))
    {
        return 0; ///Duplicado
    }

    if ((nue = (tNodoD*)malloc(sizeof(tNodoD)))==NULL
        || (nue->info = malloc(tam))==NULL)
    {
        free(nue);
        return 0; ///Sin Mem
    }

    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;

    nue->sig = auxSig;
    nue->ant = auxAnt;
    if (auxSig)
        auxSig->ant = nue;
    if (auxAnt)
        auxAnt->sig = nue;

    *pl = nue;

    return 1;
}
