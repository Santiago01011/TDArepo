#include "main.h"

int main()
{
    tAlumno auxAlumno;
    tLista listaAlumnos;
    FILE *arch = fopen(RUTA_ARCHIVO, "rt");
    if (!arch)
    {
        puts("Error al abrir el archivo alumnos.txt");
        return 1;
    }
    if (!crearLista(&listaAlumnos))
    {
        puts("Error al crear la lista");
        return 1;
    }
    while (leerAlumno(arch, &auxAlumno))
    {
        ponerEnListaFin(&listaAlumnos, &auxAlumno, sizeof(tAlumno));
    }
    puts("-------------------------------------------------------");
    printf("Lista cargada desde %s\n", RUTA_ARCHIVO);
    mapLista(&listaAlumnos, printAlumnoYmaterias);
    puts("-------------------------------------------------------");
    ordenarListaSimple(&listaAlumnos, cmpDNI);
    puts("Lista ordenada por:");
    printf("%49s\n", "DNI");
    mapLista(&listaAlumnos, printAlumno);
    puts("-------------------------------------------------------");
    puts("Lista ordenada por:");
    printf(" %20s%-20s%9s\n", "Apellido,", "Nombre", "DNI");
    ordenarListaSimple(&listaAlumnos, cmpANyDNI);
    mapLista(&listaAlumnos, printAlumno);
    puts("-------------------------------------------------------");
    puts("Lista ordenada por:");
    printf("%-20s%-20s%s\n", "Carrera","apellido, nombre", "y DNI");
    ordenarListaSimple(&listaAlumnos, cmpCANyDNI);
    mapLista(&listaAlumnos, printAlumnoYCarrera);
    puts("-------------------------------------------------------");
    puts("Lista ordenada por:");
    printf("%49s\n", "Promedio");
    ordenarListaSimple(&listaAlumnos, cmpPromedio);
    mapLista(&listaAlumnos, printAlumnoYPromedio);
    puts("-------------------------------------------------------");
    puts("Lista ordenada por:");
    printf("%-20s%-30s%s\n", "Carrera","", "y Promedio (sin aplazos)");
    ordenarListaSimple(&listaAlumnos, cmpCyPsinA);
    mapLista(&listaAlumnos, printAlumnoYCarreraYPromedio);
    puts("-------------------------------------------------------");
    puts("Lista antes de ser invertida: ");
    mapLista(&listaAlumnos, printAlumno);
    puts("-------------------------------------------------------");
    puts("Lista invertida: ");
    invertirLista(&listaAlumnos);
    mapLista(&listaAlumnos, printAlumno);
    puts("-------------------------------------------------------");
    puts("Lista vaciada: ");
    vaciarLista(&listaAlumnos);
    mapLista(&listaAlumnos, printAlumnoYmaterias);
    puts("-------------------------------------------------------");
    fclose(arch);
    return 0;
}

void printAlumnoYmaterias(void *alumno)
{
    printAlumno(alumno);
    printMateriasDelAlumno(alumno);
}

void printAlumno(void *alumno)
{
    printf("%20s, %-20s| %-8d\n", ((tAlumno*)alumno)->apellido, ((tAlumno*)alumno)->nombre, ((tAlumno*)alumno)->dni);
}

void printAlumnoYPromedio(void *alumno)
{
    printf("%20s, %-20s| %9d\n", ((tAlumno*)alumno)->apellido, ((tAlumno*)alumno)->nombre, _calcularPromInt(alumno));
}

void printAlumnoYCarreraYPromedio(void *alumno)
{
    int res = _calcularPromInt(alumno);
    if (res < 7)
    {
        return;
    }
    printf("%-7s\t", ((tAlumno*)alumno)->codCarrera);
    printf("%20s, %-20s| %9d\n", ((tAlumno*)alumno)->apellido, ((tAlumno*)alumno)->nombre, res);
}

void printAlumnoYCarrera(void *alumno)
{
    printf("%-7s\t", ((tAlumno*)alumno)->codCarrera);
    printAlumno(alumno);
}

void printMateriasDelAlumno(void *alumno)
{
    int i;
    printf("Cantidad de materias: %d\n", ((tAlumno*)alumno)->materias.cantidad);
    for (i = 0; i < ((tAlumno *)alumno)->materias.cantidad; i++)
    {
        printf("Materia nro %d, Nota: %d\n", i+1, ((tAlumno*)alumno)->materias.materias[i].notaFinal);
    }
    puts("-------------------------------------------------------");
}

int cmpDNI(const void *a, const void *b)
{
    return ((tAlumno*)a)->dni - ((tAlumno*)b)->dni;
}

int cmpANyDNI(const void *a, const void *b)
{
    int res;
    tAlumno* alumnoA = (tAlumno*)a;
    tAlumno* alumnoB = (tAlumno*)b;
    res = strcmpi(alumnoA->apellido, alumnoB->apellido);
    if (res != 0)
    {
        return res;
    }
    res = strcmpi(alumnoA->nombre, alumnoB->nombre);
    if (res != 0)
    {
        return res;
    }
    return cmpDNI(a, b);
}

int cmpCANyDNI(const void *a, const void *b)
{
    int res;
    tAlumno* alumnoA = (tAlumno*)a;
    tAlumno* alumnoB = (tAlumno*)b;
    res = strcmpi(alumnoA->codCarrera, alumnoB->codCarrera);
    if(res != 0)
    {
        return res;
    }
    return cmpANyDNI(a, b);
}

int _calcularPromInt(const void *a)
{
    tAlumno* alumno = (tAlumno*)a;
    int i, aux = 0;
    for (i = 0; i < alumno->materias.cantidad; i++)
    {
        aux += alumno->materias.materias[i].notaFinal;
    }
    return (int)(aux / alumno->materias.cantidad);
}

int cmpPromedio(const void *a, const void *b)
{
    int promedioRedoneadoA = _calcularPromInt(a);
    int promedioRedoneadoB = _calcularPromInt(b);
    return promedioRedoneadoB - promedioRedoneadoA;
}

int cmpCyPsinA(const void *a, const void *b)
{
    tAlumno* alumnoA = (tAlumno*)a;
    tAlumno* alumnoB = (tAlumno*)b;
    int res = strcmpi(alumnoA->codCarrera, alumnoB->codCarrera);
    if (res != 0)
    {
        return res;
    }
    return cmpPromedio(a, b);
}
