#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include "lib/Stock.h"
#include "lib/listaDin.h"
#include "lib/menu.h"

int mostrarArchBin(const char *nombreArch, void *elem, size_t tamElem, void (*func)(void*));

#endif // MAIN_H
