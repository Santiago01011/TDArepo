#ifndef ALUMNOS_H
#define ALUMNOS_H
#include <stdio.h>
#include <stdlib.h>

#define TAM_NOMBRE 21
#define CANT_MATERIAS 50

typedef struct
{
    int codMateria;
    char codCursada[7];
    unsigned int notaFinal;
} tMateria;

typedef struct
{
    tMateria materias[CANT_MATERIAS];
    int cantidad;
} tMaterias;

typedef struct
{
    int dni;
    char nombre[TAM_NOMBRE];
    char apellido[TAM_NOMBRE];
    char codCarrera[4];
    tMaterias materias;
} tAlumno;

int leerAlumno(FILE *pf, tAlumno *alumno);
int guardarAlumno(FILE *pf, const tAlumno *alumno);

#endif /* ALUMNOS_H */