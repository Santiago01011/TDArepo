#include "main.h"

int main()
{
    mostrarMenu();
    return 0;
}


int mostrarArchBin(const char *nombreArch, void *elem, size_t tamElem, void (*func)(void*))
{
    FILE *pf = fopen(nombreArch, "rb");
    if (!pf)
    {
        printf("Error al leer %s\n", nombreArch);
        return 0;
    }
    printf("--------------------Inicio de %s--------------------\n", nombreArch);
    while(fread(elem, tamElem, 1, pf))
    {
        func(elem);
    }
    puts("----------------------------------------------------------");
    return 1;
}
