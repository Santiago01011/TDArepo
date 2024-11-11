#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct sNodoArbol
{
    void* info;
    size_t tamInfo;
    struct sNodoArbol* izq,
                     * der;
}tNodoArbol;

typedef tNodoArbol *tArbol;
typedef int (*Cmp)(const void*, const void*);
typedef void (*AccionAvz)(void*, size_t, unsigned, void*);

void crearArbol(tArbol *p);
void vaciarArbol(tArbol *p);
int insertarEnArbol(tArbol *p, const void *d, size_t tam, Cmp cmp);
tNodoArbol** buscarNodo(tArbol *p, const void *d, Cmp cmp);
tNodoArbol** buscarNodoMayor(tArbol *p);
tNodoArbol** buscarNodoMenor(tArbol *p);
int eliminarRaiz(tArbol *p);
unsigned alturaArbol(const tArbol *p);
void recInorden(tArbol *p, AccionAvz accion, void *param);
int cargarDesdeDatosOrdenadosRec(tArbol *p, void *vec, int li, int ls, size_t tam, int leer(void*, void*, unsigned, size_t));
int cargarDesdeVecOrdenado (tArbol *p, void *vec, unsigned ce, size_t tam);
int cargarDesdeArchivoOrdenado(tArbol *p, const char *path, size_t tam);

#endif // ARBOL_H_INCLUDED
