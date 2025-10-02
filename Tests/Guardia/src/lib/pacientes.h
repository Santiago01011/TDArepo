#ifndef PACIENTES_H
#define PACIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include "colaDinamica/colaDin.h"

typedef struct {
    char hora[5];
    char DNI[9];
    char prioridad;
} Paciente;

/**
 * @brief Carga los pacientes desde un archivo y los distribuye en colas según su prioridad.
 * @param rutaArch Ruta del archivo que contiene los datos de los pacientes.
 * @param colaRoja Puntero a la cola para pacientes de prioridad roja.
 * @param colaAmarilla Puntero a la cola para pacientes de prioridad amarilla.
 * @param colaVerde Puntero a la cola para pacientes de prioridad verde.
 * @return 1 en caso de éxito, 0 en caso de error.
 */
int cargarPacientes(const char* rutaArch, tCola *colaRoja, tCola *colaAmarilla, tCola *colaVerde);

/**
 * @brief Lee un paciente desde un archivo.
 * @param pf Puntero al archivo desde el cual se leerá el paciente.
 * @param paciente Puntero a la estructura donde se almacenará el paciente leído.
 * @return 1 si se leyó correctamente, 0 en caso contrario.
 */
int leerPaciente(FILE *pf, Paciente *paciente);

/**
 * @brief Muestra la información de un paciente en la consola.
 * @param paciente Puntero al paciente cuya información se mostrará.
 */
void mostrarPaciente(const Paciente *paciente);

#endif // PACIENTES_H