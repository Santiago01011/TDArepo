#include "Fecha.h"


void printFecha(void *fecha)
{
    printf("%2d/%2d/%4d\n", ((tFecha*)fecha)->dia, ((tFecha*)fecha)->mes, ((tFecha*)fecha)->anio);
}

int cmpFechas(const void *fA, const void* fB)
{
    tFecha *fechaA = (tFecha*)fA;
    tFecha *fechaB = (tFecha*)fB;
    int res = fechaB->anio - fechaA->anio;
    if (res != 0)
    {
        return res;
    }

    res = fechaB->mes - fechaA->mes;

    if (res != 0)
        return res;

    return fechaB->dia - fechaA->dia;
}

int ingresarFecha(tFecha *fecha)
{
    int flag = 0;
    do{
        if(flag)
        {
            puts("La fecha ingresada no es valida, ingrese nuevamente");
        }
        printf("Ingrese la fecha en formato (dd/mm/aaaa)\n");
        printf("ingrese el dia: ");
        scanf("%d", &fecha->dia);

        printf("Ingrese el mes: ");
        scanf("%d", &fecha->mes);

        printf("Ingrese el anio: ");
        scanf("%d", &fecha->anio);

        printf("Fecha ingresada: ");
        printFecha(fecha);
        flag = 1;
    } while (!esFechaValida(fecha));
    return 1;
}


int esFechaValida(const tFecha *fecha)
{
    int vecDias[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (fecha->anio < 1 || fecha->mes < 1 || fecha->mes > 12)
        return 0;

    if ((fecha->anio % 4 == 0 && fecha->anio % 100 != 0) || (fecha->anio % 400 == 0))
        vecDias[1] = 29;

    if (fecha->dia < 1 || fecha->dia > vecDias[fecha->mes - 1])
        return 0;

    return 1;
}












