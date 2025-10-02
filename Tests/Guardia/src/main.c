#include <stdio.h>
#include "medicos.h"
#include "pacientes.h"

int atenderPaciente(tCola *cola, Paciente *paciente, tLista *medicos, Medico *medico);

int main()
{
    tLista listaMedicos;
    tCola colaRoja, colaAmarilla, colaVerde;
    Paciente auxPaciente;
    Medico auxMedico;
    FILE *pfa = fopen("resources/atendidos.txt", "at");
    if (!pfa)
        return 1;
    if (!cargarMedicos("resources/medicos.txt", &listaMedicos))
    {
        printf("Error al cargar los médicos.\n");
        return 1;
    }
    // mapLista(&listaMedicos, (void(*)(void*))mostrarMedico);

    if (!cargarPacientes("resources/llegadas.txt", &colaRoja, &colaAmarilla, &colaVerde))
    {
        printf("Error al cargar los pacientes.\n");
        return 2;
    }
    // mapCola(&colaRoja, (void(*)(void*))mostrarPaciente);
    // mapCola(&colaAmarilla, (void(*)(void*))mostrarPaciente);
    // mapCola(&colaVerde, (void(*)(void*))mostrarPaciente);

    while (!listaVacia(&listaMedicos) &&
           (!colaVacia(&colaRoja) || !colaVacia(&colaAmarilla) || !colaVacia(&colaVerde)))
    {
        if (!colaVacia(&colaRoja))
        {
            if(!atenderPaciente(&colaRoja, &auxPaciente, &listaMedicos, &auxMedico))
                continue;
        }
        else if (!colaVacia(&colaAmarilla))
        {
            if(!atenderPaciente(&colaAmarilla, &auxPaciente, &listaMedicos, &auxMedico))
                continue;
        }
        else if (!colaVacia(&colaVerde))
        {
            if(!atenderPaciente(&colaVerde, &auxPaciente, &listaMedicos, &auxMedico))
                continue;
        }
        fprintf(pfa, "%s;%s;%c;%s\n", auxPaciente.hora, auxPaciente.DNI, auxPaciente.prioridad, auxMedico.legajo);
        printf("%s;%s;%c;%s\n", auxPaciente.hora, auxPaciente.DNI, auxPaciente.prioridad, auxMedico.legajo);
    }

    vaciarCola(&colaRoja);
    vaciarCola(&colaAmarilla);
    vaciarCola(&colaVerde);
    vaciarLista(&listaMedicos);
    fclose(pfa);
    return 0;
}

int atenderPaciente(tCola *cola, Paciente *paciente, tLista *medicos, Medico *medico)
{
    return sacarDeCola(cola, paciente, sizeof(Paciente)) && sacarDeListaInicio(medicos, medico, sizeof(Medico)) && ponerEnListaFin(medicos, medico, sizeof(Medico));
}