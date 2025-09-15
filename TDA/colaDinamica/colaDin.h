#ifndef COLADIN_H
#define COLADIN_H

#include <stdlib.h>
#include <string.h>

/**
 * @brief Representa cada Nodo de la cola.
 * Cada nodo contiene un puntero a la información, el tamaño de la información
 * y un puntero al siguiente nodo en la cola.
 */
typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

/**
 * @brief Representa la cola dinámica.
 * Contiene punteros al primer y último nodo (elemento) de la cola.
 */
typedef struct
{
    tNodo *ini;
    tNodo *fin;
} tCola;

/**
 * @brief Inicializa la cola dinámica.
 * @param p Puntero a la cola que se desea inicializar.
 * @return Devuelve 1 si la cola se creó correctamente, 0 en caso contrario.
 */
int crearCola(tCola *p);

/**
 * @brief Libera la memoria asignada a la cola y los elementos que contenía.
 * @param p Puntero a la cola.
 */
void vaciarCola(tCola *p);

/**
 * @brief Inserta un nuevo elemento al final de la cola.
 * @param p Puntero a la cola donde se insertará el nuevo elemento.
 * @param d Puntero a los datos que se desean insertar en la cola.
 * @param tamElem Tamaño en bytes de los datos a insertar.
 * @return Devuelve 1 si el elemento se insertó correctamente, 0 en caso contrario.
 */
int ponerEnCola(tCola *p, const void *d, size_t tamElem);

/**
 * @brief Extrae un elemento de la cola (FIFO).
 * @param p Puntero a la cola desde donde se extraerá el elemento.
 * @param d Puntero donde se almacenarán los datos extraídos de la cola.
 * @param tamElem Tamaño en bytes de espacio disponible en `d`.
 * @return Devuelve 1 si el elemento se extrajo correctamente, 0 en caso contrario.
 */
int sacarDeCola(tCola *p, void *d, size_t tamElem);

/**
 * @brief Muestra el proximo elemento a extraer de la cola, sin realizar la extracción.
 * @param p Puntero a la cola desde donde se copiara el elemento.
 * @param d Puntero donde se almacenarán los datos copiados de la cola.
 * @param tamElem Tamaño en bytes de espacio disponible en `d`.
 * @return Devuelve 1 si el elemento se copió correctamente, 0 en caso contrario.
 */
int verSiguienteEnCola(const tCola *p, void *d, size_t tamElem);


/**
 * @brief Verifica si la cola está vacía.
 * @param p Puntero a la cola a verificar.
 * @return Devuelve 1 si la cola está vacía, 0 en caso contrario.
 */
int colaVacia(const tCola *p);

/**
 * @brief Cuenta la cantidad de elementos restantes en la cola.
 * @param p Puntero a la cola de la que retornar su cantidad de elementos.
 * @return La cantidad de elementos actualmente en cola.
 */
int cantidadElementosEnCola(const tCola *p);

#endif // COLADIN_H