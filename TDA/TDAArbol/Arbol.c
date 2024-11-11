#include "Arbol.h"

int arbolLeerDesdeVec(void *dest, void *orig, unsigned pos, size_t tam);
int arbolLeerDesdeArchivo(void *dest, void *orig, unsigned pos, size_t tam);


void crearArbol(tArbol *p){
    *p = NULL;
}

void vaciarArbol(tArbol *p){
    if(!*p)
        return;
    vaciarArbol(&(*p)->izq);
    vaciarArbol(&(*p)->der);
    free((*p)->info);
    free(*p);
    *p = NULL;              //Esto es para que el puntero quede en NULL y no apunte a basura
}

int insertarEnArbol(tArbol *p, const void *d, size_t tam, Cmp cmp){
    tNodoArbol *nue;
    int rcmp;

    if(*p){
        if((rcmp = cmp(d, (*p)->info)) > 0)
            return insertarEnArbol(&(*p)->der, d, tam, cmp); //mueve el puntero a la derecha, hoja derecha
        if(rcmp < 0)
            return insertarEnArbol(&(*p)->izq, d, tam, cmp); //mueve el puntero a la izquierda, hoja izquierda
        else
            return 0; //manejo de duplicado a futuro
    }
    else{
        if(!(nue = (tNodoArbol*)malloc(sizeof(tNodoArbol))) || !(nue->info = malloc(tam))){
            free(nue);
            return 0;
        }
        nue->tamInfo = tam;
        memcpy(nue->info, d, tam);
        nue->izq = nue->der = NULL;
        *p = nue;//y dale booooo y dale boooo, y dale boooo y dale boooo, y dale boca dale boo
        return 1;//y dale booooo y dale boooo, y dale boooo y dale boooo, y dale boca dale boo
    }//y dale booooo y dale boooo, y dale boooo y dale boooo, y dale boca dale boo
} //Esta funcion puede resultar en un arbol desbalanceado, vamos a intentar algo mejor

tNodoArbol** buscarNodo(tArbol *p, const void *d, Cmp cmp){
    int rcmp;
    while(*p && (rcmp = cmp(d, (*p)->info))){
        if(rcmp > 0)
            p = &(*p)->der;
        else
            p = &(*p)->izq;
    }
    if(!*p)
        return NULL;
    return (tNodoArbol**)p;
}

tNodoArbol** buscarNodoMayor(tArbol *p){
    while((*p)->der)
        p = &(*p)->der;
    return (tNodoArbol**)p;
}

tNodoArbol** buscarNodoMenor(tArbol *p){
    while((*p)->izq)
        p = &(*p)->izq;
    return (tNodoArbol**)p;
}

int eliminarRaiz(tArbol *p){
    tNodoArbol **aux, *elim;
    if(!*p)
        return 0;
    free((*p)->info);

    if(!(*p)->izq && !(*p)->der){
        free(*p);
        *p = NULL;
        return 1; //elimine una hoja
    }
    aux = alturaArbol(&(*p)->izq) > alturaArbol(&(*p)->der) ?
            buscarNodoMayor(&(*p)->izq) : buscarNodoMenor(&(*p)->der);
    elim = *aux;
    (*p)->info = elim->info;
    (*p)->tamInfo = elim->tamInfo;
    *aux = elim->izq ? elim->izq : elim->der;
    free(elim);
    return 1;
}

unsigned alturaArbol(const tArbol *p){
    unsigned altIzq, altDer;
    if(!*p)
        return 0;
    altIzq = alturaArbol(&(*p)->izq);
    altDer = alturaArbol(&(*p)->der);
    return (altIzq > altDer ? altIzq : altDer) + 1;
}

void recorrerInorden(tArbol *p, AccionAvz accion, void *param, unsigned n){
    if(!*p)
        return;
    recorrerInorden(&(*p)->izq, accion, param, n + 1);
    accion((*p)->info, (*p)->tamInfo, n, param);
    recorrerInorden(&(*p)->der, accion, param, n + 1);
}

void recInorden(tArbol *p, AccionAvz accion, void *param){
   recorrerInorden(p, accion, param, 0);
}

int cargarDesdeDatosOrdenadosRec(tArbol *p, void *vec, int li, int ls, size_t tam, int leer(void*, void*, unsigned, size_t)){
    int ret, medio = (li + ls) / 2;

    if(li > ls)
        return 1;
    *p = (tNodoArbol*)malloc(sizeof(tNodoArbol));
    if(!*p)
        return 0;
    (*p)->info = malloc(tam);
    if(!(*p)->info){
        free(*p);
        return 0;
    }
    if(!leer((*p)->info, vec, medio, tam)){
        free((*p)->info);
        free(*p);
        *p = NULL;
        return 0;
    }
    (*p)->tamInfo = tam;
    (*p)->izq = (*p)->der = NULL;

    if(!(ret = cargarDesdeDatosOrdenadosRec(&(*p)->izq, vec, li, medio - 1, tam, leer)))
        return ret;
    return cargarDesdeDatosOrdenadosRec(&(*p)->der, vec, medio + 1, ls, tam, leer);
}

int cargarDesdeVecOrdenado (tArbol *p, void *vec, unsigned ce, size_t tam){
    if(*p || !vec)
        return 0;
    return cargarDesdeDatosOrdenadosRec(p, vec, 0, ce - 1, tam, arbolLeerDesdeVec);
}

int arbolLeerDesdeVec(void *dest, void *orig, unsigned pos, size_t tam){
    memcpy(dest, (char*)orig + pos * tam, tam);
    return 1;
}

int cargarDesdeArchivoOrdenado(tArbol *p, const char *path, size_t tam){
    int ret, ce;
    if(*p)
        return 0;  //Si el arbol ya tiene algo, no se puede cargar
    FILE *pf = fopen(path, "rb");
    if(!pf)
        return 0;
    fseek(pf, 0, SEEK_END);
    ce = ftell(pf) / tam;
    ret = cargarDesdeDatosOrdenadosRec(p, pf, 0, ce - 1, tam, arbolLeerDesdeArchivo);
    fclose(pf);
    return ret;
}

int arbolLeerDesdeArchivo(void *dest, void *orig, unsigned pos, size_t tam){
    FILE *pf = (FILE*)orig;
    fseek(pf, pos * tam, SEEK_SET);
    return fread(dest, tam, 1, pf);
}



int arbol_cargar_iterativo(tArbolBinBusq *pa, const void * dato, unsigned tam, int cmp(const void*, const void*))
{
    tNodoArbol *nue;
    int         rc;

    while(*pa)
    {
        if((rc = cmp(dato,(*pa)->info)) < 0)
            pa = &(*pa)->izq;
        else if (rc > 0)
            pa = &(*pa)->der;
        else
        {
            printf("//Error: Clave Duplicada//\n");
            return 1;
        }
    }

    if(!reservarMemoriaNodo(nue,sizeof(tNodoArbol),nue->info,tam))
    {
        printf("//Error: Memoria Insuficiente//\n");
        return 1;
    }

    nue->tamInfo = tam;
    memcpy_ALU(nue->info,dato,tam);

    nue->der = nue->izq = NULL;

    *pa = nue;

    return 0;
}

int arbol_recorrer_preorden(const tArbolBinBusq *pa, void * params, void accion(void *, unsigned, unsigned, void *))
{
    arbol_recorrer_rec_preorden(pa,0,params,accion);

    return 0;
}

int arbol_recorrer_rec_preorden(const tArbolBinBusq *pa, unsigned n, void * params, void accion(void *, unsigned, unsigned, void *))
{
    if(!*pa)
        return 0;

    accion((*pa)->info,(*pa)->tamInfo,n,params);
    arbol_recorrer_rec_preorden(&(*pa)->izq,n+1,params,accion);
    arbol_recorrer_rec_preorden(&(*pa)->der,n+1,params,accion);

    return 0;
}

int arbol_recorrer_orden(const tArbolBinBusq *pa, void * params, void accion(void *, unsigned, unsigned, void *))
{
    arbol_recorrer_rec_orden(pa,0,params,accion);

    return 0;
}

int arbol_recorrer_rec_orden(const tArbolBinBusq *pa, unsigned n, void * params, void accion(void *, unsigned, unsigned, void *))
{
    if(!*pa)
        return 0;

    arbol_recorrer_rec_orden(&(*pa)->izq,n+1,params,accion);
    accion((*pa)->info,(*pa)->tamInfo,n,params);
    arbol_recorrer_rec_orden(&(*pa)->der,n+1,params,accion);

    return 0;
}

int arbol_recorrer_inv_orden(const tArbolBinBusq *pa, void * params, void accion(void *, unsigned, unsigned, void *))
{
    arbol_recorrer_rec_inv_orden(pa,0,params,accion);

    return 0;
}

int arbol_recorrer_rec_inv_orden(const tArbolBinBusq *pa, unsigned n, void * params, void accion(void *, unsigned, unsigned, void *))
{
    if(!*pa)
        return 0;

    arbol_recorrer_rec_inv_orden(&(*pa)->der,n+1,params,accion);
    accion((*pa)->info,(*pa)->tamInfo,n,params);
    arbol_recorrer_rec_inv_orden(&(*pa)->izq,n+1,params,accion);

    return 0;
}

int arbol_recorrer_posorden(const tArbolBinBusq *pa, void * params, void accion(void *, unsigned, unsigned, void *))
{
    arbol_recorrer_rec_posorden(pa,0,params,accion);

    return 0;
}

int arbol_recorrer_rec_posorden(const tArbolBinBusq *pa, unsigned n, void * params, void accion(void *, unsigned, unsigned, void *))
{
    if(!*pa)
        return 0;

    arbol_recorrer_rec_posorden(&(*pa)->izq,n+1,params,accion);
    arbol_recorrer_rec_posorden(&(*pa)->der,n+1,params,accion);
    accion((*pa)->info,(*pa)->tamInfo,n,params);

    return 0;
}







