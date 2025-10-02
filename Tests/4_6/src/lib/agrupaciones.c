#include "agrupaciones.h"

int convertirRegla(const char *linea, void *elem)
{
    Agrupacion *aux = (Agrupacion *)elem;
    if (sscanf(linea, "%d%99[^\n]", &aux->numero, aux->nombre) == 2)
        return 1;
    return 0;
}

int cmpAgru(const void *a, const void *b){
    Agrupacion *agr1 = (Agrupacion *)a;
    Agrupacion *agr2 = (Agrupacion *)b;
    return agr1->numero - agr2->numero;
}

int cmpAgruNombre(const void *a, const void *b){
    Agrupacion *agr1 = (Agrupacion *)a;
    Agrupacion *agr2 = (Agrupacion *)b;
    return strcmp(agr1->nombre, agr2->nombre);
}

int leerAgrup(Agrupacion vec[])
{
    int i = 0;
    char linea[100];
    FILE *arch = fopen("resources/agrupaciones.txt", "r");
    if (!arch)
    {
        puts("Error al abrir el archivo");
        return 0;
    }
    while (fgets(linea, 100, arch) && i < MAX_AGRUP)
    {
        if (convertirRegla(linea, &vec[i]) == 1)
            i++;
    }
    fclose(arch);
    return i;
}

void printAgrupacion(const void *a){
    Agrupacion *agr = (Agrupacion *)a;
    printf("|Numero: %d|", agr->numero);
    printf("Nombre: %s|\n", agr->nombre);
    puts("----------------------------");
}

void leerVotos(int matriz[][MAX_AGRUP], Agrupacion agrupaciones[], int nAgrup)
{
    Voto voto;
    int i;
    FILE *arch = fopen("resources/votos.dat", "rb");
    if (!arch)
    {
        puts("Error: no se pudo abrir el archivo de votos (resources/votos.dat)");
        return;
    }
    /* comprobar si el archivo esta vacio */
    fseek(arch, 0, SEEK_END);
    long tam = ftell(arch);
    if (tam == 0)
    {
        puts("Error: archivo de votos vacío");
        fclose(arch);
        return;
    }
    rewind(arch);
    while (fread(&voto, sizeof(Voto), 1, arch) == 1)
    {
        /* Validaciones basicas */
        if (voto.region < 1 || voto.region > 9)
        {
            printf("Registro con region fuera de rango: %d\n", voto.region);
            continue;
        }
        if (voto.distri < 1 || voto.distri > MAX_DISTRI)
        {
            printf("Registro con distrito fuera de rango: %d\n", voto.distri);
            continue;
        }
        /* buscar agrupacion */
        int encontrado = 0;
        for (i = 0; i < nAgrup; i++)
        {
            if (agrupaciones[i].numero == voto.nagrup)
            {
                matriz[voto.distri - 1][i]++;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado)
        {
            printf("Registro con agrupacion desconocida: %d\n", voto.nagrup);
            continue;
        }
    }
    fclose(arch);
}