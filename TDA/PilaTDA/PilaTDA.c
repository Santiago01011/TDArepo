#include "PilaTDA.h"

/*
void crearPila(tPila* pp){
    pp->tope = TAM_PILA;
}
*/
void crearPila(tPila* pp){
    *pp = NULL;
}
/*
int ponerEnPila(tPila* pp, const void* dato, size_t tam){
    if(pp->tope < tam + sizeof(size_t))
        return PILA_LLENA;
    pp->tope -= tam;
    memcpy(pp->vec + pp->tope, dato, tam);
    pp->tope -=sizeof(tam);
    memcpy(pp->vec + pp->tope, &tam, sizeof(size_t));
    return TODO_OK;
}
*/
int ponerEnPila(tPila* pp, const void* pd, unsigned tam){
    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));
    if(!nue)
        return PILA_LLENA;
    nue->info = malloc(tam);
    if(!nue->info){
        free(nue);
        return PILA_LLENA;
    }
    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);
    nue->sig = *pp;
    *pp = nue;

    return TODO_OK;
}
/*
int sacarDePila(tPila* pp, void* dato, size_t tam){
    size_t tamDatoPila;
    if(pp->tope == TAM_PILA)
        return PILA_VACIA;
    memcpy(&tamDatoPila, pp->vec + pp->tope, sizeof(size_t));
    pp->tope += sizeof(size_t);
    memcpy(dato, pp->vec + pp->tope, MIN(tamDatoPila, tam));
    pp->tope += tamDatoPila;
    return TODO_OK;
}
*/
int sacarDePila(tPila* pp, void* pd, unsigned tam){

        tNodo* elim = *pp;
        if(!*pp)
            return PILA_VACIA;
        memcpy(pd, elim->info, MIN(elim->tamInfo, tam));
        *pp = elim->sig;
        free(elim->info);
        free(elim);
        return TODO_OK;
}
/*
void mostrarPila(tPila* pp, size_t tam){
    int i;
    for(i = pp->tope; i < TAM_PILA; i += sizeof(size_t) + *(size_t*)(pp->vec + i))
        printf("%.*s\n", *(size_t*)(pp->vec + i), pp->vec + i + sizeof(size_t));
}
*/
/*The "%.*s\n" format specifier in printf is used to print a string with a maximum width specified by (*pp)->tamInfo.
This ensures that only up to tamInfo characters of the string (*pp)->info are printed.*/
void mostrarTopePila(tPila* pp, size_t tam){
    if(!*pp)
        return;
    printf("%.*s\n", (*pp)->tamInfo, (char*)(*pp)->info);
}

void mostrarPila(tPila* pp, size_t tam){
    tNodo* aux = *pp;
    while(aux){
        printf("%.*s\n", aux->tamInfo, (char*)aux->info);
        aux = aux->sig;
    }
}

void vaciarPila(tPila* pp){
    tNodo* elim;
    while(*pp){
        elim = *pp;
        *pp = elim->sig;
        free(elim->info);
        free(elim);
    }
}

