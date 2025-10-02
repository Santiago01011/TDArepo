#ifndef UTILITARIAS_H
#define UTILITARIAS_H

#include "../Comun/Comun.h"


typedef void (*CopiarIdx)(void* pvIdx, const void* pvReg, int nroReg);


void generarIndice(const char* pathBin, size_t tamReg, size_t tamIdx, CopiarIdx copiarIdx, Cmp cmpIdx);


#endif // UTILITARIAS_H
