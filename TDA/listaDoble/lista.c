#include"lista.h"

void crearLista(tLista*lista)
{
    *lista=NULL;
}
int insertarOrdenado(tLista*lista, const void*dato, unsigned tamDato, int (*comparar)(const void*, const void*))
{
    tNodo *act,*auxSig, *auxAnt, *nue;
    act = *lista;

    if(!act)
    {
        auxAnt = NULL;
        auxSig = NULL;
    }
    else
    {
        while(act->ant && comparar(act->dato, dato)>0)
        {
            act = act->ant;
        }
        while(act->sig && comparar(dato, act->dato)>0)
        {
            act = act->sig;
        }

        if(comparar(dato, act->dato)==0)
        {
            return 1;
        }

        if(comparar(dato, act->dato)>0)
        {
            auxAnt = act;
            auxSig = act->sig;

        }
        else
        {
            auxAnt = act->ant;
            auxSig = act;
        }
    }


    nue=(tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 1;
    nue->dato=malloc(tamDato);
    if(!nue->dato)
    {
        free(nue);
        return 1;
    }
    memcpy(nue->dato, dato, tamDato);
    nue->tamDato=tamDato;
    nue->ant=auxAnt;
    nue->sig=auxSig;

    if(auxAnt)
        auxAnt->sig=nue;
    if(auxSig)
        auxSig->ant=nue;

    *lista=nue;


    return 0;

}

int cmpint(const void *x, const void *y)
{
    int*num1, *num2;

    num1=(int*)x;
    num2=(int*)y;

    return *num1 - *num2;
}

void maplistaIzq(tLista*lista, void (*accion)(const void*))
{
    tNodo *aux= *lista;

    while(aux->ant)
    {
        aux = aux->ant;
    }
    while(aux)
    {
        accion(aux->dato);
        aux = aux->sig;
    }
}


void imprimirInt(const void * dato)
{
    int*aux = (int*)dato;
    printf("%d ", *aux);
}

void destruirLista(tLista*lista){
    tNodo *aux;

    while((*lista)->ant)
        lista = &((*lista)->ant);

    while(*lista){
        aux = *lista;
        lista = &((*lista)->sig);
        free(aux->dato);
        free(aux);
    }
}
void maplistaDer(tLista*lista, void (*accion)(const void*)){
    tNodo *aux = *lista;

    while(aux->sig){
        aux = aux->sig;
    }
    while(aux){
        accion(aux->dato);
        aux= aux->ant;
    }
}

