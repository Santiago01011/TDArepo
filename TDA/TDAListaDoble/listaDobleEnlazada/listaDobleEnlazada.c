#include "listaDobleEnlazada.h"

#define minimo(x, y) ((x) <= (y) ? (x) : (y))



void createDoubleList(tLista *p){
    *p = NULL;
}

int isEmptyDoubleList(const tLista *p){
    return *p == NULL;
}

int isFullDoubleList(const tLista *p, unsigned cantBytes){
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);
    free(info);
    free(aux);
    return info == NULL || aux == NULL;
}

void clearDoubleList(tLista *p){
    tNodo *act = *p;
    if(act){
        while(act->ant)
            act = act->ant;
        while(act){
            tNodo *aux = act->sig;
            free(act->info);
            free(act);
            act = aux;
        }
        *p = NULL;
    }
}

/**
 * @brief Inserta un nodo al comienzo de la lista.
 * 
 * @param p Puntero a la lista.
 * @param d Puntero al dato que se va a insertar.
 * @param cantBytes Cantidad de bytes que ocupa el dato.
 * @return int 1 si se pudo insertar, 0 si no se pudo.
 */
int addAtBeginningDoubleList(tLista *p, const void *d, unsigned cantBytes){
    tNodo *act = *p, *nue;
    if(act)
        while(act->ant)
            act = act->ant;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(cantBytes)) == NULL){
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = act;
    nue->ant = NULL;
    if(act)
        act->ant = nue;
    *p = nue;
    return 1;
}

/**
 * @brief Saca el primer nodo de la lista.
 * 
 * @param p Puntero a la lista.
 * @param d Puntero al dato que se va a sacar.
 * @param cantBytes Cantidad de bytes que ocupa el dato.
 * 
 * @return int 1 si se pudo sacar, 0 si no se pudo.
 */
int removeFirstDoubleList(tLista *p, void *d, unsigned cantBytes){
    tNodo *act = *p;
    if(act == NULL)
        return 0;
    while(act->ant)
        act = act->ant;
    memcpy(d, act->info, minimo(cantBytes, act->tamInfo));
    if(act->sig){
        act->sig->ant = NULL;
        *p = act->sig;
    }else
        *p = NULL;
    free(act->info);
    free(act);
    return 1;
}

int getFirstDoubleList(const tLista *p, void *d, unsigned cantBytes){
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}

/**
 * @brief Inserta un nodo al final de la lista.
 * 
 * @param p Puntero a la lista.
 * @param d Puntero al dato que se va a insertar.
 * @param cantBytes Cantidad de bytes que ocupa el dato.
 * @return int 1 si se pudo insertar, 0 si no se pudo.
 */
int addAtEndDoubleList(tLista *p, const void *d, unsigned cantBytes){
    tNodo *act = *p, *nue;
    
    if(act)
        while(act->sig)
            act = act->sig;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(cantBytes)) == NULL){
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    nue->ant = act;
    if(act)
        act->sig = nue;
    *p = nue;
    return 1;
}

int removeLastDoubleList(tLista *p, void *d, unsigned cantBytes){
    while(*p && (*p)->sig)
        p = &(*p)->sig;
    if(*p == NULL)
        return 0;
    tNodo *aux = *p;
    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));
    
    if(aux->ant)
        aux->ant->sig = NULL;
    else
        *p = NULL;
    free(aux->info);
    free(aux);

    return 1;
}

int getLastDoubleList(const tLista *p, void *d, unsigned cantBytes){
    while(*p && (*p)->sig)
        p = &(*p)->sig;
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}

/**
 * @brief Inserta de forma ordenada un nodo.
 * 
 * @param p Puntero a la lista.
 * @param d Puntero al dato que se va a insertar.
 * @param cantBytes Cantidad de bytes que ocupa el dato.
 * @param cmp Función de comparación.
 * @param acum Función de acumulación.
 * @return int 1 si se pudo insertar, 0 si no se pudo, DUPKEY si ya existe la clave.
 */
int addInOrderDoubleList(tLista *p, const void *d, unsigned cantBytes, Cmp cmp, Acum acum){
    tNodo *nue, *sig, *ant, *act = *p;

    if(act == NULL){
        ant = NULL;
        sig = NULL;
    }

    else{
        while(act->sig && cmp(act->info, d) < 0)
            act = act->sig;
        while(act->ant && cmp(act->info, d) > 0)
            act = act->ant;
        if(cmp(act->info, d) == 0){
            *p = act;
            if(acum)
                if(acum(&act->info, &act->tamInfo, d, cantBytes) == 0)
                    return 0;
            return DUPKEY;
        }
        if(cmp(act->info, d) < 0){
            ant = act;
            sig = act->sig;
        }
        else{
            sig = act;
            ant = act->ant;
        }
    }

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(cantBytes)) == NULL){
        free(nue);
        return 0;
    }

    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = sig;
    nue->ant = ant;

    if(ant)
        ant->sig = nue;
    if(sig)
        sig->ant = nue;
    *p = nue;
    return 1;
}

/**
 * @brief Ordena la lista.
 * 
 * @param p Puntero a la lista.
 * @param cmp Función de comparación.
 */
void sortDoubleList(tLista *p, Cmp cmp){
    tNodo *act = *p, *sup = NULL, *inf = NULL;
    int flag = 1;
    if(act == NULL)
        return;
    while(act->ant)
        act = act->ant;
    while(flag){
        flag = 0;
        while(act->sig != sup){
            if(cmp(act->info, act->sig->info) > 0){
                void *inf = act->info;
                unsigned tam = act->tamInfo;
                
                flag = 1;

                act->info = act->sig->info;
                act->tamInfo = act->sig->tamInfo;
                act->sig->info = inf;
                act->sig->tamInfo = tam;
            }
            act = act->sig;
        }
        sup = act;
        while(act->ant != inf){
            if(cmp(act->info, act->ant->info) < 0){
                void *inf = act->info;
                unsigned tam = act->tamInfo;
                
                flag = 1;

                act->info = act->ant->info;
                act->tamInfo = act->ant->tamInfo;
                act->ant->info = inf;
                act->ant->tamInfo = tam;
            }
            act = act->ant;
        }
        inf = act;
    }    
}





void mapDoubleList(tLista *p, void accion(void*, void*), void *param){
    while(*p && (*p)->ant)
        p = &(*p)->ant;
    while(*p){
        accion((*p)->info, param);
        p = &(*p)->sig;
    }
}

void filter(tLista *p, int condicion(const void*, void*), void *param){
    tNodo *aux;
    while(*p){
        if(!condicion((*p)->info, param)){ //si condicion devuelve 0, elimino el nodo. Si devuelve 1, avanzo.
            aux = *p;
            *p = aux->sig;
            free(aux->info);
            free(aux);
        }else{
            p = &(*p)->sig;
        }
    }
}

void* reduce(tLista *p, void *res, void accion(const void*, void*, void*), void *param){
    while(*p){
        accion((*p)->info, res, param);
        p = &(*p)->sig;
    }
    return res;
}
