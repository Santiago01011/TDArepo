#include "Stock.h"

int cmpStockPorFecha(const void *a, const void *b)
{
    StockItem *itemA = (StockItem*)a;
    StockItem *itemB = (StockItem*)b;
    return cmpFechas(&itemB->fVto, &itemA->fVto);
}

int cmpStockPorFechaYCant(const void *a, const void *b)
{
    StockItem *itemA = (StockItem*)a;
    StockItem *itemB = (StockItem*)b;
    int res = cmpFechas(&itemB->fVto, &itemA->fVto);
    if(res != 0)
        return res;
    return itemB->cant - itemA->cant;
}

int leerStock(FILE *pf, StockItem *item)
{
    return fread(item, sizeof(StockItem), 1, pf);
}

int cargarStock(FILE *pf, StockItem *item)
{
    return fwrite(item, sizeof(StockItem), 1, pf);
}

void printStockItem(void *item)
{
    printf("%-6s %-25s %6d ", ((StockItem*)item)->codProd, ((StockItem*)item)->descrip, ((StockItem*)item)->cant);

    printf("VTO: ");
    printFecha(&((StockItem*)item)->fVto);

}

void generarArchivoStock()
{
    int i;
    StockItem vectorItems[30] = {
        {"PROD01", "Yogur Natural",        1001, {10, 11, 2025}, 50},
        {"PROD02", "Leche Entera",         1002, {9, 11, 2025}, 30},
        {"PROD03", "Queso Cremoso",        1003, {20, 11, 2025}, 100},
        {"PROD04", "Manteca",              1004, {20, 11, 2025}, 20},
        {"PROD05", "Jamon Cocido",         1005, {9, 11, 2025}, 80},
        {"PROD06", "Salame",               1006, {15, 12, 2025}, 60},
        {"PROD07", "Aceitunas",            1007, {5, 12, 2025}, 40},
        {"PROD08", "Pan Lactal",           1008, {8, 11, 2025}, 90},
        {"PROD09", "Cafe Molido",          1009, {1, 1, 2026}, 70},
        {"PROD10", "Galletitas",           1010, {28, 11, 2025}, 55},
        {"PROD11", "Miel Pura",            1011, {15, 1, 2026}, 45},
        {"PROD12", "Mermelada Frutilla",   1012, {22, 12, 2025}, 65},
        {"PROD13", "Yerba Mate",           1013, {30, 12, 2025}, 50},
        {"PROD14", "Harina 000",           1014, {1, 5, 2026}, 80},
        {"PROD15", "Azucar Blanca",        1015, {9, 11, 2025}, 20},
        {"PROD16", "Gaseosa Cola",         1016, {18, 11, 2025}, 120},
        {"PROD17", "Gaseosa Naranja",      1017, {18, 11, 2025}, 90},
        {"PROD18", "Agua Mineral",         1018, {3, 12, 2025}, 200},
        {"PROD19", "Aceite de Girasol",    1019, {15, 2, 2026}, 75},
        {"PROD20", "Arroz Largo Fino",     1020, {1, 3, 2026}, 110},
        {"PROD21", "Lentejas",             1021, {5, 3, 2026}, 85},
        {"PROD22", "Porotos Negros",       1022, {10, 3, 2026}, 95},
        {"PROD23", "Fideos Spaghetti",     1023, {28, 2, 2026}, 130},
        {"PROD24", "Atun en Lata",         1024, {20, 4, 2026}, 60},
        {"PROD25", "Salsa de Tomate",      1025, {10, 4, 2026}, 55},
        {"PROD26", "Jugo en Polvo",        1026, {25, 12, 2025}, 150},
        {"PROD27", "Cereal de Maiz",       1027, {12, 11, 2025}, 75},
        {"PROD28", "Chocolate",            1028, {10, 12, 2025}, 90},
        {"PROD29", "Galletas de Avena",    1029, {22, 11, 2025}, 45},
        {"PROD30", "Tostadas Integrales",  1030, {8, 11, 2025}, 65}
    };

    FILE *arch = fopen("stock.dat", "wb");
    if (!arch)
    {
        puts("No se pudo generar el archivo de stock");
        return;
    }

    for (i = 0; i < 10; i++)
    {
        cargarStock(arch, &vectorItems[i]);
    }

    fclose(arch);
    puts("Archivo de stock generado exitosamente");
}
