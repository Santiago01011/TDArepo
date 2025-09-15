#ifndef PILADIN_H
#define PILADIN_H

/**
 * @brief Representa cada Nodo de la pila.
 * Cada nodo contiene un puntero a la información, el tamaño de la información
 * y un puntero al siguiente nodo en la pila.
 */
typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

/**
 * @brief Representa la pila dinámica.
 * Contiene un puntero al nodo superior de la pila.
 */
typedef tNodo *tPila;

/**
 * @brief Inicializa una nueva pila.
 * @param p Puntero a la pila que se desea inicializar.
 * @return 1 si la pila se creó correctamente, 0 en caso contrario.
 */
int crearPila(tPila *p);

/**
 * @brief Libera la memoria asignada a la pila y los elementos que contenía.
 * @param p Puntero a la pila.
 */
void vaciarPila(tPila *p);

/**
 * @brief Consulta el elemento en la cima de la pila sin extraerlo.
 * @param p Puntero a la pila.
 * @param d Puntero donde se almacenarán los datos del elemento en la cima de la pila.
 * @param tamElem Tamaño en bytes de espacio disponible en `d`.
 * @return 1 si se pudo consultar el elemento, 0 si la pila está vacía.
 */
int verTopePila(const tPila *p, void *d, size_t tamElem);

/**
 * @brief Inserta un nuevo elemento en la cima de la pila.
 * @param p Puntero a la pila donde se insertará el nuevo elemento.
 * @param d Puntero a los datos que se desean insertar en la pila.
 * @param tamElem Tamaño en bytes de los datos a insertar.
 * @return 1 si el elemento se insertó correctamente, 0 en caso contrario.
 */
int ponerEnPila(tPila *p, const void *d, size_t tamElem);

/**
 * @brief Extrae un elemento de la cima de la pila (LIFO).
 * @param p Puntero a la pila desde donde se extraerá el elemento.
 * @param d Puntero donde se almacenarán los datos extraídos de la pila.
 * @param tamElem Tamaño en bytes de espacio disponible en `d`.
 * @return 1 si el elemento se extrajo correctamente, 0 en caso contrario.
 */
int sacarDePila(tPila *p, void *d, size_t tamElem);

#endif // PILADIN_H