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


int procesar_pedidos(const char * path_prods, const char * path_pedidos, const char * path_indice){
    char buffer[300];
    int flagFaltantes = 1;
    unsigned codPed;
    float totalPedido;
    t_producto_stock productoStock;
    t_pedido pedidoAux, pedidoCola;
    tCola colaPedidos, colaConfirmar;
    t_reg_ind idxAux;
    tArbolBinBusq arbolIdx;
    crear_cola_res(&colaPedidos);
    crear_cola_res(&colaConfirmar);
    crearArbolBinBusq_res(&arbolIdx);
    cargarArchivoBinOrdenadoArbolBinBusq_res(&arbolIdx, "../Archivos/productos.idx", sizeof(t_reg_ind));
    FILE* pf= fopen(path_pedidos, "r");
    if(!pf)
        return 0;
    FILE* pfProd = fopen(path_prods, "r+b");
    if(!pfProd)
        return 0;
    FILE* pfPedFaltantes = fopen("../Archivos/pedidos_faltantes.txt", "w");
    if(!pfPedFaltantes)
        return 0;
    FILE* pfPedconfirmados = fopen("../Archivos/pedidos_realizados.txt", "w");
    if(!pfPedconfirmados)
        return 0;
    fgets(buffer, 300, pf);
    sscanf(buffer, "%6d%10s%3d", &pedidoAux.cod_ped, pedidoAux.cod_prod, &pedidoAux.cant);
    while(!feof(pf)){
        codPed = pedidoAux.cod_ped;
        printf("preparando pedido %d\n", codPed);
        do{
            //printf("%d|%s|%d\n", pedidoAux.cod_ped, pedidoAux.cod_prod, pedidoAux.cant);
        poner_en_cola_res(&colaPedidos, &pedidoAux, sizeof(t_pedido));
        poner_en_cola_res(&colaConfirmar, &pedidoAux, sizeof(t_pedido));
        fgets(buffer, 300, pf);
        sscanf(buffer, "%6d%10s%3d", &pedidoAux.cod_ped, pedidoAux.cod_prod, &pedidoAux.cant);
       // system("pause");
        }while(codPed == pedidoAux.cod_ped && !feof(pf));
        printf("finalizando pedido %d\n", codPed);
        while(sacar_de_cola_res(&colaPedidos, &pedidoCola, sizeof(t_pedido))){
            strcpy(idxAux.cod_prod, pedidoCola.cod_prod);
            buscarElemArbolBinBusq_res(&arbolIdx, &idxAux, sizeof(t_reg_ind), cmp_ind_cod_prod_res);
            fseek(pfProd, (idxAux.nro_reg - 1) * sizeof(t_producto_stock),SEEK_SET);
            fread(&productoStock, sizeof(t_producto_stock), 1, pfProd);
            if(productoStock.stock >= pedidoCola.cant){
                //printf("cod: %s|stock: %d\n", productoStock.cod, productoStock.stock);
                if(flagFaltantes == 1){
                    fprintf(pfPedconfirmados, "pedido %d procesado:\n", pedidoCola.cod_ped);
                    flagFaltantes = 0;
                }
                totalPedido = productoStock.precio * pedidoCola.cant;
                fprintf(pfPedconfirmados, "-%10s-%-20s:%7d%7d $%5.2f\n $%5.2f\n", pedidoCola.cod_prod, productoStock.descripcion, productoStock.stock, pedidoCola.cant, productoStock.precio, totalPedido);
                productoStock.stock -= pedidoCola.cant;
                fseek(pfProd, (idxAux.nro_reg - 1)* sizeof(t_producto_stock) ,SEEK_SET);
                fwrite(&productoStock, sizeof(productoStock), 1, pfProd);
            }else{
                fprintf(pfPedFaltantes,"Pedido %d con faltantes:\n", pedidoCola.cod_ped);
                while(sacar_de_cola_res(&colaConfirmar, &pedidoCola, sizeof(t_pedido))){
                    strcpy(idxAux.cod_prod, pedidoCola.cod_prod);
                    buscarElemArbolBinBusq_res(&arbolIdx, &idxAux, sizeof(t_reg_ind), cmp_ind_cod_prod);
                    fseek(pfProd, (idxAux.nro_reg - 1)* sizeof(t_producto_stock) ,SEEK_SET);
                    fread(&productoStock, sizeof(productoStock), 1, pfProd);
                    fprintf(pfPedFaltantes, "-%10s-%20s:%7d%7d ", pedidoCola.cod_prod, productoStock.descripcion, productoStock.stock, pedidoCola.cant);
                    if(productoStock.stock >= pedidoCola.cant)
                        fprintf(pfPedFaltantes,"\n");
                    else
                        fprintf(pfPedFaltantes," F\n");
                }
            }
        }
            flagFaltantes = 1;
            while(sacar_de_cola_res(&colaConfirmar, &pedidoCola, sizeof(t_pedido))){  //debería ser vaciar cola
            }
            while(sacar_de_cola_res(&colaPedidos, &pedidoCola, sizeof(t_pedido))){
            }
    }
    fclose(pf);
    fclose(pfProd);
    fclose(pfPedconfirmados);
    fclose(pfPedFaltantes);
    mostrar_archivo_productos_res("../Archivos/productos.dat");
    return 1;
}

int procesar_pedidosMOD(const char * path_prods, const char * path_pedidos, const char * path_indice){

    char buffer[500];
    int flagFaltantes;
    unsigned codPed;
    float totalPedido, totalProd;
    t_producto_stock productoStock;
    t_pedido pedidoAux, pedidoCola;
    t_reg_ind idxAux;
    tArbolBinBusq arbolIDX;
    tCola colaPedido;

    crearArbolBinBusq_res(&arbolIDX);
    cargarArchivoBinOrdenadoArbolBinBusq_res(&arbolIDX, "../Archivos/productos.idx", sizeof(t_reg_ind));
    crear_cola_res(&colaPedido);


    FILE* pf= fopen(path_pedidos, "r");
    if(!pf)
        return 0;
    FILE* pfProd = fopen(path_prods, "r+b");
    if(!pfProd)
        return 0;
    FILE* pfPedFaltantes = fopen("../Archivos/Mi_pedidos_faltantes.txt", "w");
    if(!pfPedFaltantes)
        return 0;
    FILE* pfPedconfirmados = fopen("../Archivos/Mi_pedidos_realizados.txt", "w");
    if(!pfPedconfirmados)
        return 0;

    fgets(buffer, 300, pf);
    sscanf(buffer, "%6d%10s%3d", &pedidoAux.cod_ped, pedidoAux.cod_prod, &pedidoAux.cant);

    while(!feof(pf)){
        codPed = pedidoAux.cod_ped;
        flagFaltantes = 1;
        //printf("preparando pedido %d\n", codPed);
        do{
            strcpy(idxAux.cod_prod, pedidoAux.cod_prod);
            buscarElemArbolBinBusq_res(&arbolIDX, &idxAux, sizeof(t_reg_ind), cmp_ind_cod_prod_res);
            fseek(pfProd, (idxAux.nro_reg - 1) * sizeof(t_producto_stock), SEEK_SET);
            fread(&productoStock, sizeof(t_producto_stock), 1, pfProd);
            if(productoStock.stock < pedidoAux.cant && flagFaltantes)
                flagFaltantes = 0;
            poner_en_cola_res(&colaPedido, &pedidoAux, sizeof(t_pedido));
            fgets(buffer, 300, pf);
            sscanf(buffer, "%6d%10s%3d", &pedidoAux.cod_ped, pedidoAux.cod_prod, &pedidoAux.cant);
        }while(codPed == pedidoAux.cod_ped && !feof(pf));
        if(!flagFaltantes){
            fprintf(pfPedFaltantes,"Pedido %d con faltantes:\n", codPed);
            while(sacar_de_cola_res(&colaPedido, &pedidoCola, sizeof(t_pedido))){
                    strcpy(idxAux.cod_prod, pedidoCola.cod_prod);
                    buscarElemArbolBinBusq_res(&arbolIDX, &idxAux, sizeof(t_reg_ind), cmp_ind_cod_prod_res);
                    fseek(pfProd, (idxAux.nro_reg - 1)* sizeof(t_producto_stock) ,SEEK_SET);
                    fread(&productoStock, sizeof(productoStock), 1, pfProd);
                    fprintf(pfPedFaltantes, "-%10s-%20s:%7d%7d ", pedidoCola.cod_prod, productoStock.descripcion, productoStock.stock, pedidoCola.cant);
                    if(productoStock.stock >= pedidoCola.cant)
                        fprintf(pfPedFaltantes,"\n");
                    else
                        fprintf(pfPedFaltantes," F\n");
                }
        }
        else{
            fprintf(pfPedconfirmados, "pedido %d procesado:\n", codPed);
            totalPedido = 0;
            while(sacar_de_cola_res(&colaPedido, &pedidoCola, sizeof(t_pedido))){
                strcpy(idxAux.cod_prod, pedidoCola.cod_prod);
                buscarElemArbolBinBusq_res(&arbolIDX, &idxAux, sizeof(t_reg_ind), cmp_ind_cod_prod);
                fseek(pfProd, (idxAux.nro_reg - 1) * sizeof(t_producto_stock),SEEK_SET);
                fread(&productoStock, sizeof(t_producto_stock), 1, pfProd);
                totalProd = productoStock.precio * pedidoCola.cant;
                totalPedido += totalProd;
                fprintf(pfPedconfirmados, "-%10s-%-20s:%7d%7d $%5.2f $%5.2f\n", pedidoCola.cod_prod, productoStock.descripcion, productoStock.stock, pedidoCola.cant, productoStock.precio, totalProd);
                productoStock.stock -= pedidoCola.cant;
                fseek(pfProd, (idxAux.nro_reg - 1)* sizeof(t_producto_stock) ,SEEK_SET);
                fwrite(&productoStock, sizeof(productoStock), 1, pfProd);
            }
            fprintf(pfPedconfirmados, "\t\t\t\t\tTOTAL: %.2f\n", totalPedido);
        }
    }
    fclose(pf);
    fclose(pfProd);
    fclose(pfPedconfirmados);
    fclose(pfPedFaltantes);
    mostrar_archivo_productos_res("../Archivos/productos.dat");

    return 1;
}




