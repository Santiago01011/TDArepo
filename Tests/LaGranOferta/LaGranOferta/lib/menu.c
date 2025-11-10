#include "menu.h"

void mostrarMenu()
{
    char opt;
    int cantProd;
    tFecha fechaActual = {0,0,0};
    tLista prodVencimiento;
    StockItem item;
    FILE *arch, *txt;
    do{
        system("cls");
        puts("--------------La Gran Oferta--------------");
        printf("\t\t\t\t");
        printFecha(&fechaActual);
        printf("[A] - Generar lote de pruebas.\n");
        printf("[B] - Ingresar Fecha Actual.\n");
        printf("[C] - Mostrar los n productos proximos a vencer.\n");
        printf("[D] - Generar archivo \'prod_a_vencer.txt\'\n");
        printf("[E] - Mostrar producto mas proximo a vencer.\n");
        printf("[F] - Salir del menu\n");
        printf("Ingrese una opcion: ");
        scanf(" %c", &opt);
        opt = tolower(opt);
        switch(opt)
        {
            case 'a':
                printf("Generando lote de pruebas...\n");
                generarArchivoStock();
                break;
            case 'b':
                ingresarFecha(&fechaActual);
                break;
            case 'c':
                if (!esFechaValida(&fechaActual))
                {
                    puts("Ingrese una fecha valida para continuar");
                    break;
                }
                printf("Ingrese la cantidad de productos a mostrar: \n");
                scanf("%d", &cantProd);
                arch = fopen("stock.dat", "rb");
                if (!arch)
                {
                    puts("Error al abrir el archivo stock.dat");
                    break;
                }
                crearLista(&prodVencimiento);
                while (leerStock(arch, &item))
                {
                    if (cmpFechas(&fechaActual, &item.fVto) < 0)
                    {
                        printf("El siguiente producto ya esta vencido\n");
                        printStockItem(&item);
                        continue;
                    }
                    ponerEnListaTop(&prodVencimiento, &item, sizeof(StockItem), cmpStockPorFecha, &cantProd);
                }
                puts("-------------------------------------------------------");
                puts("Lista de n productos proximos a vencer");
                printf("%-6s %-25s %6s %10s\n", "CodProd", "Descripcion", "Stock", "FechaVTO");
                mapLista(&prodVencimiento, printStockItem);
                puts("-------------------------------------------------------");
                fclose(arch);
                destruirLista(&prodVencimiento);
                break;
            case 'd':
                if (!esFechaValida(&fechaActual))
                {
                    puts("Ingrese una fecha valida para continuar");
                    break;
                }
                printf("Ingrese la cantidad de productos a mostrar: \n");
                scanf("%d", &cantProd);
                arch = fopen("stock.dat", "rb");
                if (!arch)
                {
                    puts("Error al abrir el archivo stock.dat");
                    break;
                }
                txt = fopen("prod_a_vencer.txt", "wt");
                if (!txt)
                {
                    fclose(arch);
                    puts("Error al abrir el archivo prod_a_vencer.txt");
                    break;
                }
                crearLista(&prodVencimiento);
                while (leerStock(arch, &item))
                {
                    if (cmpFechas(&fechaActual, &item.fVto) < 0)
                    {
                        fprintf(txt, "El siguiente producto ya esta vencido\n");
                        fprintf(txt, "%-6s %-25s %6d ", item.codProd, item.descrip, item.cant);
                        fprintf(txt, "VTO: ");
                        fprintf(txt, "%2d/%2d/%4d\n", item.fVto.dia, item.fVto.mes, item.fVto.anio);
                        continue;
                    }
                    ponerEnListaTop(&prodVencimiento, &item, sizeof(StockItem), cmpStockPorFechaYCant, &cantProd);
                }
                fprintf(txt, "-------------------------------------------------------\n");
                fprintf(txt, "Lista de n productos proximos a vencer\n");
                fprintf(txt, "%-6s %-10s %6s\n", "CodProd", "(dd/mm/aaaa)", "Stock\n");
                while(sacarDeListaInicio(&prodVencimiento, &item, sizeof(StockItem)))
                {
                    fprintf(txt, "%-6s %2d/%2d/%4d %6d\n", item.codProd, item.fVto.dia, item.fVto.mes, item.fVto.anio, item.cant);
                }
                fprintf(txt, "-------------------------------------------------------");
                fclose(arch);
                fclose(txt);
                destruirLista(&prodVencimiento);
                break;
            case 'e':
                if (!esFechaValida(&fechaActual))
                {
                    puts("Ingrese una fecha valida para continuar");
                    break;
                }
                arch = fopen("stock.dat", "rb");
                if (!arch)
                {
                    puts("Error al abrir el archivo stock.dat");
                    break;
                }
                cantProd = 1;
                crearLista(&prodVencimiento);
                while (leerStock(arch, &item))
                {
                    if (cmpFechas(&fechaActual, &item.fVto) < 0)
                        continue;
                    ponerEnListaTop(&prodVencimiento, &item, sizeof(StockItem), cmpStockPorFechaYCant, &cantProd);
                }
                sacarDeListaInicio(&prodVencimiento, &item, sizeof(StockItem));
                puts("-------------------------------------------------------");
                puts("Producto mas proximo a vencer");
                printStockItem(&item);
                puts("-------------------------------------------------------");
                fclose(arch);
                destruirLista(&prodVencimiento);
                break;
            case 'f':
                printf("Cerrando el sistema...\n");
                fclose(arch);
                fclose(txt);
                destruirLista(&prodVencimiento);
                break;
            default:
                printf("La opcion seleccionada no es una entrada valida para este menu\n");
        }
        system("pause");
    } while(opt != 'f');

}
