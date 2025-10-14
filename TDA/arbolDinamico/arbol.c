#include "arbol.h"

#define reservarMemoriaNodo( X , Y , Z , W ) ( ( ( X ) = (typeof( X ))malloc( Y ) ) == NULL || ( ( Z ) = malloc( W ) ) == NULL ? free( X ), 0 : 1 )

int ponerEnArbolBin(tArbolBin *p, const void *elem, const size_t tamElem, int (*cmp)(const void *, const void *)){
    tNodoArbol *nue;
    int res;
    while(*p)
    {
        if( (res = cmp(elem, (*p)->info)) < 0 ) p = &(*p)->izq;
        if( res > 0 ) p = &(*p)->der;
        else return 2;
    }
    if(!reservarMemoriaNodo(nue, sizeof(tNodoArbol), nue->info, tamElem))
        return 0;
    nue->tamInfo = tamElem;
    memcpy(nue->info, elem, tamElem);
    nue->der = nue->izq = NULL;
    *p = nue;
    return 1;
}
