#include <stdio.h>
#include <string.h>

// Uncomment one of the following lines to switch between implementations
// #include "colaDinamica/colaDin.h"  // Dynamic queue
#include "colaEstatica/colaEst.h"  // Static queue

int main()
{
    tCola cola;
    char buffer[100];
    int num;

    // Initialize queue
    crearCola(&cola);

    // Test enqueue
    num = 42;
    if (ponerEnCola(&cola, &num, sizeof(int)))
        printf("Enqueued: %d\n", num);

    num = 100;
    if (ponerEnCola(&cola, &num, sizeof(int)))
        printf("Enqueued: %d\n", num);

    // Test peek
    if (verSiguienteEnCola(&cola, &num, sizeof(int)))
        printf("Front element: %d\n", num);

    // Test count
    printf("Elements in queue: %d\n", cantidadElementosEnCola(&cola));

    // Test dequeue
    if (sacarDeCola(&cola, &num, sizeof(int)))
        printf("Dequeued: %d\n", num);

    printf("Elements remaining: %d\n", cantidadElementosEnCola(&cola));

    // Test empty check
    printf("Queue empty: %s\n", colaVacia(&cola) ? "Yes" : "No");

    // Clean up
    vaciarCola(&cola);

    return 0;
}