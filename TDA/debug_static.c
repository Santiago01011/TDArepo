#include <stdio.h>
#include <string.h>
#include "colaEstatica/colaEst.h"

int main()
{
    tCola cola;
    int num;

    printf("Testing Static Queue:\n");

    // Initialize queue
    crearCola(&cola);
    printf("Queue created. Empty: %s\n", colaVacia(&cola) ? "Yes" : "No");

    // Test enqueue
    num = 42;
    if (ponerEnCola(&cola, &num, sizeof(int)))
        printf("Enqueued: %d\n", num);
    else
        printf("Failed to enqueue\n");

    printf("Elements: %d, Empty: %s\n", cantidadElementosEnCola(&cola), colaVacia(&cola) ? "Yes" : "No");

    // Test peek
    if (verSiguienteEnCola(&cola, &num, sizeof(int)))
        printf("Front element: %d\n", num);
    else
        printf("Failed to peek\n");

    printf("Elements after peek: %d\n", cantidadElementosEnCola(&cola));

    return 0;
}