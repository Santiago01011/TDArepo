#include "colaEst.h"

#define minimo(X, Y) ((X) <= (Y) ? (X) : (Y))

int crearCola(tCola *p)
{
    p->pri = 0;
    p->ult = 0;
    p->tamDisp = TAM_COLA;
    return 1;
}

void vaciarCola(tCola *p)
{
    p->pri = 0;
    p->ult = 0;
    p->tamDisp = TAM_COLA;
}

int ponerEnCola(tCola *p, const void *d, size_t tamElem)
{
    size_t ini, fin;
    if (p->tamDisp < sizeof(size_t) + tamElem)
        return 0;
    p->tamDisp -= sizeof(size_t) + tamElem;
    if ((ini = minimo(sizeof(size_t), TAM_COLA - p->ult)) != 0)
        memcpy(p->cola + p->ult, &tamElem, ini);
    if ((fin = sizeof(size_t) - ini) != 0)
        memcpy(p->cola, ((char *)&tamElem) + ini, fin);
    p->ult = fin ? fin : p->ult + ini;
    if ((ini = minimo(tamElem, TAM_COLA - p->ult)) != 0)
        memcpy(p->cola + p->ult, d, ini);
    if ((fin = tamElem - ini) != 0)
        memcpy(p->cola, ((char *)d) + ini, fin);
    p->ult = fin ? fin : p->ult + ini;
    return 1;
}

int verSiguienteEnCola(const tCola *p, void *d, size_t tamElem)
{
    size_t tamInfo, ini, fin, pos = p->pri;
    if (p->tamDisp == TAM_COLA)
        return 0;
    if ((ini = minimo(sizeof(size_t), TAM_COLA - pos)) != 0)
        memcpy(&tamInfo, p->cola + pos, ini);
    if ((fin = sizeof(size_t) - ini) != 0)
        memcpy(((char *)&tamInfo) + ini, p->cola, fin);
    pos = fin ? fin : pos + ini;
    tamInfo = minimo(tamInfo, tamElem);
    if ((ini = minimo(tamInfo, TAM_COLA - pos)) != 0)
        memcpy(d, p->cola + pos, ini);
    if ((fin = tamInfo - ini) != 0)
        memcpy(((char *)d) + ini, p->cola, fin);
    return 1;
}

int colaVacia(const tCola *p)
{
    return p->tamDisp == TAM_COLA;
}

int colaLlena(const tCola *p, size_t tamElem)
{
    return p->tamDisp < tamElem + sizeof(size_t);
}

int sacarDeCola(tCola *p, void *d, size_t tamElem)
{
    size_t tamInfo, ini, fin;

    if (p->tamDisp == TAM_COLA)
        return 0;
    if ((ini = minimo(sizeof(size_t), TAM_COLA - p->pri)) != 0)
        memcpy(&tamInfo, p->cola + p->pri, ini);
    if ((fin = sizeof(size_t) - ini) != 0)
        memcpy(((char *)&tamInfo) + ini, p->cola, fin);
    p->pri = fin ? fin : p->pri + ini;
    p->tamDisp += sizeof(size_t) + tamInfo;
    tamInfo = minimo(tamInfo, tamElem);
    if ((ini = minimo(tamInfo, TAM_COLA - p->pri)) != 0)
        memcpy(d, p->cola + p->pri, ini);
    if ((fin = tamInfo - ini) != 0)
        memcpy(((char *)d) + ini, p->cola, fin);
    p->pri = fin ? fin : p->pri + ini;
    return 1;
}

int cantidadElementosEnCola(const tCola *p)
{
    int count = 0;
    size_t pos = p->pri;
    size_t available = TAM_COLA - p->tamDisp;

    while (available > 0)
    {
        size_t tamInfo, ini, fin;
        if ((ini = minimo(sizeof(size_t), TAM_COLA - pos)) != 0)
            memcpy(&tamInfo, p->cola + pos, ini);
        if ((fin = sizeof(size_t) - ini) != 0)
            memcpy(((char *)&tamInfo) + ini, p->cola, fin);
        pos = fin ? fin : pos + ini;
        available -= sizeof(size_t) + tamInfo;
        count++;
    }
    return count;
}