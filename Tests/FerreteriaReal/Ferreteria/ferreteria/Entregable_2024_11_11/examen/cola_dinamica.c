#include "../include/cola_dinamica.h"



int poner_en_cola(tCola* pc, const void* pd, unsigned tam)//entra al final
{
    tNodo* nue = malloc(sizeof(tNodo));
    if(!nue)
        return 0; //cola llena
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0; //cola llena
    }
    memcpy(nue->info,pd,tam);
    nue->tamInfo = tam;
    nue->sig = NULL; //el nuevo ahora es el ultimo de la cola
    if(!pc->pri)
        pc->pri = nue;
    else
        pc->ult->sig = nue;
    pc->ult = nue;

    return 1;
}

int sacar_de_cola(tCola* pc, void* pd, unsigned tam)//saco el primero
{
    tNodo* elim = pc->pri;
    if(!elim)
        return 0; //cola vacia
    memcpy(pd,elim->info,MINIMO(tam,elim->tamInfo));
    pc->pri = elim->sig;
    if(!pc->pri)
        pc->ult = NULL;
    free(elim->info);
    free(elim);

    return 1;
}
