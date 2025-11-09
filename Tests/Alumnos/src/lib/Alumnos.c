#include "Alumnos.h"
/* One line of Alumnos.txt contains:
    44525943;Santiago;Zapata;INF;4;1234;20251C;8;2345;20251C;10;3456;20252C;5;7890;20252C;7; */

int leerAlumno(FILE *pf, tAlumno *alumno)
{
    int i, resultado;
    resultado = fscanf(pf, "%8u;%20[^;];%20[^;];%3[^;];%d;", &alumno->dni, alumno->nombre, alumno->apellido, alumno->codCarrera, &alumno->materias.cantidad);
    if(resultado != 5)
    {
        /* puts("Error al leer los datos del alumno"); //Comentado por su uso para cortar la lectura, siempre va a fallar*/
        return 0;
    }
    for(i = 0; i < alumno->materias.cantidad; i++)
    {
        resultado = fscanf(pf, "%d;%6[^;];%d;", &alumno->materias.materias[i].codMateria, alumno->materias.materias[i].codCursada, &alumno->materias.materias[i].notaFinal);
        if(resultado != 3)
        {
            printf("%d\n", resultado);
            printf("Error en las materias del alumno, %d\n", i);
            return 0;
        }
    }
    return 1;
}

int guardarAlumno(FILE *pf, const tAlumno *alumno)
{
    int i, resultado;
    resultado = fprintf(pf, "%u;%s;%s;%s;%d;", alumno->dni, alumno->nombre, alumno->apellido, alumno->codCarrera, alumno->materias.cantidad);
    if(resultado < 0)
    {
        printf("%d\n", resultado);
        puts("Error al escribir los datos del alumno");
        return 0;
    }
    for (i = 0; i < alumno->materias.cantidad; i++)
    {
        resultado = fprintf(pf, "%d;%s;%d;", alumno->materias.materias[i].codMateria, alumno->materias.materias[i].codCursada, alumno->materias.materias[i].notaFinal);
        if (resultado < 0)
        {
            puts("Error al escribir las materias del alumno");
            return 0;
        }
    }
    fprintf(pf, "\n");
    return 1;
}
