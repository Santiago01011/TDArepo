#include "cola_dinamica.h"
#include<stdlib.h>
#include<string.h>

void crear_cola(tCola * pc)
{
    pc->pri = pc->ult = NULL;
}

int poner_en_cola(tCola * pc, const void * pd, unsigned tam)
{
    tNodo * nue = (tNodo*) malloc(sizeof(tNodo));
    if(!nue)
    {
        return 0; ///COLA_LLENA
    }
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0; ///COLA_LLENA
    }

    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);
    nue->sig = NULL;

    if(pc->ult)
    {
        pc->ult->sig = nue;
    }
    else
    {
        pc->pri = nue;
    }
    pc->ult = nue;

    return 1; ///OK
}

int sacar_de_cola(tCola * pc, void * pd, unsigned tam)
{
    tNodo * elim = pc->pri;
    if(!elim)
    {
        return 0; ///COLA_VACIA
    }
    memcpy(pd, elim->info, MINIMO(tam, elim->tamInfo));
    pc->pri = elim->sig;

    if(!pc->pri)
    {
        pc->ult = NULL;
    }

    free(elim->info);
    free(elim);

    return 1; ///OK
}

///int frente_de_cola(const tCola * pc, void * pd, unsigned tam);

///int cola_llena(const tCola * pc, unsigned tam);
int cola_vacia(const tCola * pc)
{
    return !pc->pri;
}

///void vaciar_cola(tCola * pc);
