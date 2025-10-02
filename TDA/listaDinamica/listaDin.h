#ifndef LISTADIN_H
#define LISTADIN_H

#include <stdlib.h>
#include <string.h>

/**
 * @brief Representa a un Nodo individual de la lista.
 * @param *info Puntero a la información almacenada en el nodo.
 * @param tamInfo Tamaño en bytes de la información almacenada en el nodo.
 * @param *sig Puntero al siguiente nodo en la lista.
 */
typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

/**
 * @brief Abstracción de los nodos al tipo lista.
 */
typedef tNodo *tLista;

/**
 * @brief Inicializa la lista dinámica.
 * @param *p puntero a la lista.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int crearLista(tLista *p);

/**
 * @brief Libera la memoria de la lista y todos sus nodos.
 * @param *p Puntero a la lista a vaciar.
 * @return void.
 */
void vaciarLista(tLista *p);

/**
 * @brief Auxiliar para controlar si la lista está vacía.
 * @param *p Puntero a la lista a revisar.
 * @return 0 en caso de que la lista tenga elementos, 1 en caso de que esté vacía
 */
int listaVacia(const tLista *p);

/**
 * @brief Inserta un elemento al inicio de la lista.
 * @param *p Puntero a la lista en la que se va a insertar el elemento.
 * @param *elem Puntero a los datos a insertar.
 * @param tamElem Tamaño en bytes de los datos a insertar.
 * @return 1 En caso de éxito, 0 en caso de error.
 */
int ponerEnListaInicio(tLista *p, const void *elem, const size_t tamElem);

/**
 * @brief Inserta un elemento al final de la lista.
 * @param *p Puntero a la lista en la que se va a insertar el elemento.
 * @param *elem Puntero a los datos a insertar.
 * @param tamElem Tamaño en bytes de los datos a insertar.
 * @return 1 en caso de éxito, 0 en caso de error. 
 */
int ponerEnListaFin(tLista *p, const void *elem, const size_t tamElem);

/**
 * @brief Saca el primer elemento de la lista.
 * @param *p Puntero a la lista de la que se va a quitar el elemento.
 * @param *elem Puntero al elemento donde se va a almacenar la info del nodo quitado.
 * @param tamElem Tamaño en bytes del elemento.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int sacarDeListaInicio(tLista *p, void* elem, const size_t tamElem);

/**
 * @brief Saca el último elemento de la lista.
 * @param *p Puntero a la lista de la que se va a quitar el elemento.
 * @param *elem Puntero al elemento donde se va a almacenar la info del nodo quitado.
 * @param tamElem Tamaño en bytes del elemento.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int sacarDeListaFinal(tLista *p, void *elem, const size_t tamElem);

/**
 * @brief Ver el primer elemento de la lista sin sacarlo.
 * @param *p Puntero a la lista de la que se va a ver el elemento.
 * @param *elem Puntero al elemento donde se va a almacenar la info del nodo visto.
 * @param tamElem Tamaño en bytes del elemento.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int verPrimeroLista(const tLista *p, void *elem, const size_t tamElem);

/**
 * @brief Ver el último elemento de la lista sin sacarlo.
 * @param *p Puntero a la lista de la que se va a ver el elemento.
 * @param *elem Puntero al elemento donde se va a almacenar la info del nodo visto.
 * @param tamElem Tamaño en bytes del elemento.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int verUltimoLista(const tLista *p, void *elem, const size_t tamElem);

/**
 * @brief Aplica una función a cada elemento de la lista.
 * @param *p Puntero a la lista.
 * @param func Función a aplicar a cada elemento.
 */
void mapLista(tLista *p, void (*func)(void*));

/**
 * @brief Inserta un elemento en la lista de forma ordenada según la función de comparación.
 * @param *p Puntero a la lista.
 * @param *d Puntero a los datos a insertar.
 * @param cantBytes Tamaño en bytes de los datos a insertar.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int ponerEnOrden(tLista *p, const void *elem, const size_t tamElem, int (*cmp)(const void *, const void *));

/**
 * @brief Ordena la lista utilizando el método de inserción.
 * @param *p Puntero a la lista.
 * @param cmp Función de comparación para ordenar los elementos.
 */
void ordenarListaInsercion(tLista *p, int (*cmp)(const void *, const void *));

/**
 * @brief Ordena la lista utilizando el método de mergesort.
 * @param *p Puntero a la lista.
 * @param cmp Función de comparación para ordenar los elementos.
 */
void ordenarListaMergesort(tLista *p, int (*cmp)(const void *, const void *));


#endif // LISTADIN_H