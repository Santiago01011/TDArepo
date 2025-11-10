#ifndef ARBOL_H
#define ARBOL_H

#include <stdlib.h>
#include <string.h>

typedef struct sNodoArbol {
    void *info;
    size_t tamInfo;
    struct sNodoArbol *izq, *der;
} tNodoArbol;

typedef tNodoArbol *tArbolBin;

void crearArbolBinBusq(tArbolBin *p);

// Insertion & Basic Operations
int ponerEnArbolBin(tArbolBin *p, const void *elem, size_t tamElem, 
                    int (*cmp)(const void *, const void *));
int arbolVacio(const tArbolBin *p);
void vaciarArbol(tArbolBin *p);

// Search Operations
int buscarEnArbolBin(const tArbolBin *p, void *elem, size_t tamElem, 
                     int (*cmp)(const void *, const void *));

// Traversal Operations
void recorrerPreOrden(const tArbolBin *p, void (*accion)(const void *));
void recorrerEnOrden(const tArbolBin *p, void (*accion)(const void *));
void recorrerPostOrden(const tArbolBin *p, void (*accion)(const void *));

// Utility Functions
int alturaArbol(const tArbolBin *p);
int contarNodos(const tArbolBin *p);
int esArbolCompleto(const tArbolBin *p);

// Advanced Operations
int eliminarDeArbolBin(tArbolBin *p, void *elem, size_t tamElem,
                       int (*cmp)(const void *, const void *));

#endif