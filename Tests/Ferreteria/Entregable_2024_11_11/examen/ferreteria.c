#include "../include/ferreteria.h"
#include "../include/utilitarias.h"

void print_nodo(void *d, unsigned tam, void * x){
    t_reg_ind* dato = (t_reg_ind*)d;
    printf("cod_prod: %s|reg: %d", dato->cod_prod, dato->nro_reg);
}

int cmp_ind_cod_prod(const void* a, const void* b){
    t_reg_ind* pedA = (t_reg_ind*)a;
    t_reg_ind* pedB = (t_reg_ind*)b;
    return strcmp(pedA->cod_prod, pedB->cod_prod);
}

void print_pedido(void *d)
{
    printf("%6u%10s%3d\n", ((t_pedido*)d)->cod_ped, ((t_pedido*)d)->cod_prod, ((t_pedido*)d)->cant);
}

void print_prod(void *d)
{
    printf("%6s%-10s%3d\n", " ",((t_producto_stock*)d)->cod, ((t_producto_stock*)d)->stock);
}

int procesar_pedidos(const char * path_prods, const char * path_pedidos, const char * path_indice){
    return 0;
}

int procesar_pedidosMOD(const char * path_prods, const char * path_pedidos, const char * path_indice)
{
    int res, codProcesando, flag;
    t_reg_ind idxItem;
    t_pedido pedidoActual;
    t_producto_stock prodAux;
    tArbolBinBusq arbolIdx;
    FILE *arch_idx, *arch_prod, *arch_ped, *arch_faltantes, *arch_realizados;

    arch_idx = fopen(path_indice, "r+b");
    if (!arch_idx) return 0;
    arch_prod = fopen(path_prods, "r+b");
    if (!arch_prod) {
        fclose(arch_idx);
        return 0;
    }
    arch_ped = fopen(path_pedidos, "rt");
    if (!arch_ped) {
        fclose(arch_prod);
        fclose(arch_idx);
        return 0;
    }
    arch_faltantes = fopen("../Archivos/pedidos_faltantes.txt", "wt");
    arch_realizados = fopen("../Archivos/pedidos_realizados.txt", "wt");

    crearArbolBinBusq_res(&arbolIdx);
    cargarArchivoBinOrdenadoArbolBinBusq_res(&arbolIdx, path_indice, sizeof(t_reg_ind));

    res = fscanf(arch_ped, "%6u%10s%3d\n", &pedidoActual.cod_ped, pedidoActual.cod_prod, &pedidoActual.cant);

    while(res > 0)
    {
        flag = 0;
        codProcesando = pedidoActual.cod_ped;

        t_pedido productosPedido[50];
        int cantProductos = 0;

        do {
            productosPedido[cantProductos] = pedidoActual;
            cantProductos++;

            strcpy(idxItem.cod_prod, pedidoActual.cod_prod);
            if (!buscarElemArbolBinBusq_res(&arbolIdx, &idxItem, sizeof(t_reg_ind), cmp_ind_cod_prod)) {
                flag = 1;
            } else {
                fseek(arch_prod, (idxItem.nro_reg - 1) * sizeof(t_producto_stock), SEEK_SET);
                fread(&prodAux, sizeof(t_producto_stock), 1, arch_prod);
                if (prodAux.stock < pedidoActual.cant) {
                    flag = 1;
                }
            }
            res = fscanf(arch_ped, "%6u%10s%3d\n", &pedidoActual.cod_ped, pedidoActual.cod_prod, &pedidoActual.cant);
        } while (codProcesando == pedidoActual.cod_ped && res > 0 && cantProductos < 50);

        if (flag == 0) {
            float precioTotal = 0;
            fprintf(arch_realizados, "Pedido %u procesado:\n", codProcesando);

            for (int i = 0; i < cantProductos; i++) {
                strcpy(idxItem.cod_prod, productosPedido[i].cod_prod);
                buscarElemArbolBinBusq_res(&arbolIdx, &idxItem, sizeof(t_reg_ind), cmp_ind_cod_prod);
                fseek(arch_prod, (idxItem.nro_reg - 1) * sizeof(t_producto_stock), SEEK_SET);
                fread(&prodAux, sizeof(t_producto_stock), 1, arch_prod);

                unsigned stockOriginal = prodAux.stock;
                float precioProducto = productosPedido[i].cant * prodAux.precio;
                precioTotal += precioProducto;

                fprintf(arch_realizados, " - %10s-%-20s: %6u %6d $%8.2f $%8.2f\n",
                       prodAux.cod, prodAux.descripcion, stockOriginal, productosPedido[i].cant,
                       prodAux.precio, precioProducto);

                prodAux.stock -= productosPedido[i].cant;
                fseek(arch_prod, (idxItem.nro_reg - 1) * sizeof(t_producto_stock), SEEK_SET);
                fwrite(&prodAux, sizeof(t_producto_stock), 1, arch_prod);
            }

            fprintf(arch_realizados, "                                       TOTAL: $%.2f\n\n", precioTotal);
            printf("Pedido %u procesado correctamente - Total: $%.2f\n", codProcesando, precioTotal);

        } else {
            fprintf(arch_faltantes, "Pedido %u con faltantes:\n", codProcesando);

            for (int i = 0; i < cantProductos; i++) {
                strcpy(idxItem.cod_prod, productosPedido[i].cod_prod);
                if (buscarElemArbolBinBusq_res(&arbolIdx, &idxItem, sizeof(t_reg_ind), cmp_ind_cod_prod)) {
                    fseek(arch_prod, (idxItem.nro_reg - 1) * sizeof(t_producto_stock), SEEK_SET);
                    fread(&prodAux, sizeof(t_producto_stock), 1, arch_prod);

                    char marcaFaltante = (prodAux.stock < productosPedido[i].cant) ? 'F' : ' ';
                    fprintf(arch_faltantes, " - %10s-%-20s: %6u %6d %c\n",
                           prodAux.cod, prodAux.descripcion, prodAux.stock, productosPedido[i].cant, marcaFaltante);
                }
            }

            fprintf(arch_faltantes, "\n");
            printf("Pedido %u NO procesado - stock insuficiente\n", codProcesando);
        }
    }

    vaciarArbolBin_res(&arbolIdx);
    fclose(arch_faltantes);
    fclose(arch_realizados);
    fclose(arch_ped);
    fclose(arch_idx);
    fclose(arch_prod);
    return 1;
}

