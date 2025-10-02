#include <stdio.h>
#include <stdlib.h>
#include "lib/agrupaciones.h"

void foo(void)
{
    static int llamada = 0; /* inicializada una vez, persiste entre llamadas */
    llamada++;
    printf("%d\n", llamada);
}

int main()
{
    int totalVotosAgrup[MAX_AGRUP] = {0};
    int i, j, k;
    int matrizVotos[MAX_DISTRI][MAX_AGRUP] = {{0}};
    Agrupacion agrupaciones[MAX_AGRUP];
    int nAgrup = leerAgrup(agrupaciones);
    if (nAgrup == 0)
    {
        printf("Error al leer las agrupaciones\n");
        return 1;
    }
    /* ordenar por numero para facilitar busquedas si se desea */
    qsort(agrupaciones, nAgrup, sizeof(Agrupacion), cmpAgru);
    /* leer votos (archivo binario) y llenar matrizVotos[distr-1][i] */
    leerVotos(matrizVotos, agrupaciones, nAgrup);

    /* Calcular totales por agrupacion en el pais */
    for (i = 0; i < nAgrup; i++)
    {
        totalVotosAgrup[i] = 0;
        for (j = 0; j < MAX_DISTRI; j++)
            totalVotosAgrup[i] += matrizVotos[j][i];
    }

    /* Para cada distrito construir top-3 */
    printf("Resultados por distrito (hasta 3 agrupaciones):\n\n");
    for (j = 0; j < MAX_DISTRI; j++)
    {
        int topIdx[3];
        int topVotos[3];
        int votos;
        int m;
        int idx;
        int puestos;
        /* inicializar */
        topIdx[0] = topIdx[1] = topIdx[2] = -1;
        topVotos[0] = topVotos[1] = topVotos[2] = 0;

        for (i = 0; i < nAgrup; i++)
        {
            votos = matrizVotos[j][i];
            if (votos == 0)
                continue;
            /* intentar insertar en top */
            for (k = 0; k < 3; k++)
            {
                if (topIdx[k] == -1)
                {
                    topIdx[k] = i;
                    topVotos[k] = votos;
                    break;
                }
                else if (votos > topVotos[k] || (votos == topVotos[k] && strncmp(agrupaciones[i].nombre, agrupaciones[topIdx[k]].nombre, 25) < 0))
                {
                    /* desplazar hacia la derecha */
                    for (m = 2; m > k; m--)
                    {
                        topIdx[m] = topIdx[m - 1];
                        topVotos[m] = topVotos[m - 1];
                    }
                    topIdx[k] = i;
                    topVotos[k] = votos;
                    break;
                }
            }
        }

        /* imprimir resultados del distrito j+1 */
        printf("Distrito %d:\n", j + 1);
        puestos = 0;
        for (k = 0; k < 3; k++)
        {
            if (topIdx[k] == -1)
                continue;
            puestos++;
            idx = topIdx[k];
            printf(" %d) %s | votos distrito: %d | total pais: %d\n", puestos, agrupaciones[idx].nombre, topVotos[k], totalVotosAgrup[idx]);
        }
        if (puestos == 0)
            printf("  -- No hay votos en este distrito --\n");
        printf("\n");
    }

    return 0;
}