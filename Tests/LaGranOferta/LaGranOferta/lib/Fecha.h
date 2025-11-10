#ifndef FECHA_H
#define FECHA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    int dia, mes, anio;
} tFecha;

int ingresarFecha();
int esFechaValida(const tFecha *fecha);
int cmpFechas(const void *fA, const void* fB);
void printFecha(void *fecha);

#endif // FECHA_H
