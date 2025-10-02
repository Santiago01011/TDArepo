#ifndef AGRUPACIONES_H
#define AGRUPACIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaDinamica/listaDin.h"

#define MAX_AGRUP 25
#define MAX_DISTRI 20

typedef struct
{
    int numero;
    char nombre[100];
} Agrupacion;

typedef struct
{
    int nagrup;
    int region;
    int distri;
} Voto;

int convertirRegla(const char* linea, void* elem);
int leerAgrup(Agrupacion vec[]);
int cmpAgru(const void* a, const void* b);
int cmpAgruNombre(const void* a, const void* b);
void leerVotos(int matriz[][MAX_AGRUP], Agrupacion agrupaciones[], int nAgrup);
void printAgrupacion(const void* a);

#endif // AGRUPACIONES_H