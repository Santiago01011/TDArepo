#include "medicos.h"

int cargarMedicos(const char *rutaArch, tLista *listaMedicos)
{
    FILE *pf = fopen(rutaArch, "rt");
    Medico medico;
    if (!pf)
        return 0;
    if (!crearLista(listaMedicos))
    {
        fclose(pf);
        return 0;
    }
    while (leerMedico(pf, &medico))
    {
        if (!ponerEnListaFin(listaMedicos, &medico, sizeof(Medico)))
        {
            vaciarLista(listaMedicos);
            fclose(pf);
            return 0;
        }
    }
    fclose(pf);
    return 1;
}

int leerMedico(FILE *pf, Medico *medico)
{
    return fscanf(pf, "%4s;%51[^\n]", medico->legajo, medico->nombreCompleto) == 2;
}

void mostrarMedico(const Medico *medico)
{
    printf("Legajo: %s, Nombre: %s\n", medico->legajo, medico->nombreCompleto);
}