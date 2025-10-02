#include "pacientes.h"

int cargarPacientes(const char *rutaArch, tCola *colaRoja, tCola *colaAmarilla, tCola *colaVerde)
{
    Paciente paciente;
    FILE *pf = fopen(rutaArch, "r");
    if (!pf)
        return 0;
    if (!crearCola(colaRoja) || !crearCola(colaAmarilla) || !crearCola(colaVerde))
    {
        printf("Error al crear las colas.\n");
        return 0;
    }

    while (leerPaciente(pf, &paciente))
    {
        switch (paciente.prioridad)
        {
        case 'R':
            ponerEnCola(colaRoja, &paciente, sizeof(Paciente));
            break;
        case 'A':
            ponerEnCola(colaAmarilla, &paciente, sizeof(Paciente));
            break;
        case 'V':
            ponerEnCola(colaVerde, &paciente, sizeof(Paciente));
            break;
        default:
            printf("Prioridad desconocida: %c\n", paciente.prioridad);
            break;
        }
    }
    fclose(pf);
    return 1;
}

int leerPaciente(FILE *pf, Paciente *paciente)
{
    return fscanf(pf, "%4s%8s%c", paciente->hora, paciente->DNI, &paciente->prioridad) == 3;
}

void mostrarPaciente(const Paciente *paciente)
{
    printf("DNI: %s, Prioridad: %c.\n", paciente->DNI, paciente->prioridad);
}