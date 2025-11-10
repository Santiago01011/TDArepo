#ifndef STOCK_H
#define STOCK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fecha.h"

/**
 * Se dispone del archivo “stock.dat” el cuál tiene el siguiente formato:
 *   ● codProd: código del producto (6 caracteres)
 *   ● descrip: descripción del producto (25 caracteres)
 *   ● lote: número de lote (entero)
 *   ● fVto: fecha de vencimiento del lote (t_fecha tipo fecha)
 *   ● cant: cantidad en stock (medido en unidades de producto)
 */
typedef struct
{
    char codProd[7];
    char descrip[26];
    int lote;
    tFecha fVto;
    int cant;
} StockItem;

int leerStock(FILE *pf, StockItem *item);
int cargarStock(FILE *pf, StockItem *item);
void generarArchivoStock();
void printStockItem(void *item);
int cmpStockPorFecha(const void *a, const void *b);
int cmpStockPorFechaYCant(const void *a, const void *b);

#endif // STOCK_H
