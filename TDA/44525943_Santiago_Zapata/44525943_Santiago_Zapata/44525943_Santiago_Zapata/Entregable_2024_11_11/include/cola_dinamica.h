#ifndef COLA_DINAMICA_H_INCLUDED
#define COLA_DINAMICA_H_INCLUDED

#include <string.h>

#define MINIMO(X,Y) ((X)<(Y)?(X):(Y))

typedef struct sNodo
{
    void * info;
    unsigned tamInfo;
    struct sNodo * sig;
}tNodo;

typedef struct
{
    tNodo * pri;
    tNodo * ult;
}tCola;

void crear_cola(tCola * pc);

int poner_en_cola(tCola * pc, const void * pd, unsigned tam);
int sacar_de_cola(tCola * pc, void * pd, unsigned tam);

int frente_de_cola(const tCola * pc, void * pd, unsigned tam);

int cola_llena(const tCola * pc, unsigned tam);
int cola_vacia(const tCola * pc);

void vaciar_cola(tCola * pc);

/// Resueltas
void crear_cola_res(tCola * pc);

int poner_en_cola_res(tCola * pc, const void * pd, unsigned tam);
int sacar_de_cola_res(tCola * pc, void * pd, unsigned tam);

int frente_de_cola_res(const tCola * pc, void * pd, unsigned tam);

int cola_llena_res(const tCola * pc, unsigned tam);
int cola_vacia_res(const tCola * pc);

void vaciar_cola(tCola * pc);

#endif // COLA_DINAMICA_H_INCLUDED
