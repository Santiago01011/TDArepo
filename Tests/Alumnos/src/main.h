#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include "lib/Alumnos.h"
#include "lib\listaDinamica\listaDin.h"
#define RUTA_ARCHIVO "../src/alumnos.txt"

void printAlumnoYCarrera(void *alumno);
void printAlumnoYPromedio(void *alumno);
void printAlumnoYmaterias(void *alumno);
void printMateriasDelAlumno(void *alumno);
void printAlumnoYCarreraYPromedio(void *alumno);
void printAlumno(void *alumno);

/**
 * @brief Función de comparación por DNI.
 * @param a Puntero al primer alumno.
 * @param b Puntero al segundo alumno.
 */
int cmpDNI(const void *a, const void *b);
/**
 * @brief Función de comparación genérica.
 * Compara dos alumnos por Apellido, Nombre y DNI.
 * @param a Puntero al primer alumno.
 * @param b Puntero al segundo alumno.
 * @return Resultado de la comparación.
 */
int cmpANyDNI(const void *a, const void *b);
/**
 * @brief Función de comparación genérica.
 * Compara dos alumnos según (en orden):
 * - Carrera
 * - Apellido
 * - Nombre
 * - DNI
 * @param a Puntero al primer alumno.
 * @param b Puntero al segundo alumno.
 * @return Resultado de la comparación.
 */
int cmpCANyDNI(const void *a, const void *b);
/**
 * @brief Función de comparación genérica.
 * Compara dos alumnos según su promedio.
 * @param a Puntero al primer alumno.
 * @param b Puntero al segundo alumno.
 * @return Resultado de la comparación.
 */
int cmpPromedio(const void *a, const void *b);
/**
 * Funcion auxiliar interna.
 */
int _calcularPromInt(const void *a);

/**
 * @brief Función de comparación genérica.
 * Compara dos alumnos según su carrera y promedio.
 * No tiene en cuenta los aplazos.
 * @param a Puntero al primer alumno.
 * @param b Puntero al segundo alumno.
 * @return Resultado de la comparación.
 */
int cmpCyPsinA(const void *a, const void *b);
#endif /* MAIN_H */
