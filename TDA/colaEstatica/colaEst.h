#ifndef COLAEST_H
#define COLAEST_H

#include <stdlib.h>
#include <string.h>

#define TAM_COLA 300

#define MINIMO(a, b) ((a) < (b) ? (a) : (b))

/**
 * @brief Representa la cola estática.
 * Abstracción de una cola circular en un vector de tamaño fijo.
 * Contiene un array para almacenar los datos, índices para el primer y último
 * elemento, y el tamaño disponible.
 */
typedef struct
{
    char cola[TAM_COLA];
    size_t pri, ult;
    size_t tamDisp;
} tCola;

/**
 * @brief Inicializa la cola estática.
 * @param p Puntero a la cola que se desea inicializar.
 * @return Devuelve 1 si la cola se creó correctamente, 0 en caso contrario.
 */
int crearCola(tCola *p);

/**
 * @brief Limpia la cola, deja sus índices en la posición inicial y
 * establece el tamaño disponible al máximo.
 * @param p Puntero a la cola.
 */
void vaciarCola(tCola *p);

/**
 * @brief Inserta un nuevo elemento al final de la cola.
 * @param p Puntero a la cola donde se insertará el nuevo elemento.
 * @param d Puntero a los datos que se desean insertar en la cola.
 * @param tamElem Tamaño en bytes del elemento a insertar.
 * @return Devuelve 1 si se pudo insertar el elemento, 0 en caso contrario.
 */
int ponerEnCola(tCola *p, const void *d, size_t tamElem);

/**
 * @brief Extrae un elemento de la cola (FIFO).
 * @param p Puntero a la cola desde donde se extraerá el elemento.
 * @param d Puntero donde se almacenarán los datos extraídos de la cola.
 * @param tamElem Tamaño en bytes de espacio disponible en `d`.
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
 * @brief Verifica si la cola está llena.
 * @param p Puntero a la cola.
 * @param tamElem Cantidad de bytes a verificar.
 * @return Devuelve 1 si la cola está llena, 0 en caso contrario.
 */
int colaLlena(const tCola *p, size_t tamElem);

/**
 * @brief Devuelve la cantidad de elementos restantes en la cola.
 * @param p Puntero a la cola de la que retornar su cantidad de elementos.
 * @return La cantidad de elementos actualmente en cola.
 */
int cantidadElementosEnCola(const tCola *p);

#endif // COLAEST_H