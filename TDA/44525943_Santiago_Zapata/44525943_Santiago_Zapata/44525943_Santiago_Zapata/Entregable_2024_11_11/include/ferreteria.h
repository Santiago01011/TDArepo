#ifndef FERRETERIA_H_INCLUDED
#define FERRETERIA_H_INCLUDED

#include "arbol.h"
#include "cola_dinamica.h"

typedef struct{
    char cod [10];
    char descripcion[20];
    unsigned stock;
    float precio;
}t_producto_stock;

typedef struct{
    unsigned cod_ped;
    char cod_prod [11];
    unsigned cant;
}t_pedido;

typedef struct{
    char cod_prod [11];
    unsigned nro_reg;
}t_reg_ind;

int procesar_pedidos(const char * path_prods, const char * path_pedidos, const char * path_indice);
int procesar_pedidos_res(const char * path_prods, const char * path_pedidos, const char * path_indice);
int procesar_pedidosMOD(const char * path_prods, const char * path_pedidos, const char * path_indice);


int procesar_pedidos_simple(const char * path_prods, const char * path_pedidos, const char * path_indice);
int procesar_pedidos_simple_res(const char * path_prods, const char * path_pedidos, const char * path_indice);

#endif // FERRETERIA_H_INCLUDED
