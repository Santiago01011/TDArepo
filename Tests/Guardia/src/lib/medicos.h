#ifndef MEDICOS_H
#define MEDICOS_H
#include "listaDinamica/listaDin.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char legajo[5];
    char nombreCompleto[52];
} Medico;

/**
 * @brief Carga los médicos desde un archivo de texto a una lista dinámica.
 * @param rutaArch Ruta del archivo de texto que contiene los datos de los médicos.
 * @param listaMedicos Puntero a la lista dinámica donde se almacenarán los médicos.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int cargarMedicos(const char* rutaArch, tLista *listaMedicos);

/**
 * @brief Graba en memoria un médico desde un archivo de texto.
 * @param *pf Puntero al archivo de texto desde donde se leerán los datos del médico.
 * @param *medico Puntero a la estructura donde se almacenarán los datos del médico.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int leerMedico(FILE *pf, Medico *medico);

/**
 * @brief Muestra en pantalla los datos de un médico.
 * @param *medico Puntero a la estructura que contiene los datos del médico a mostrar.
 */
void mostrarMedico(const Medico *medico);
#endif // MEDICOS_H