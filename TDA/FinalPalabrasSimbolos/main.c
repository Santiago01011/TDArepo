#include "main.h"

int main(){
    int cantCar;
    char vecSim[50];
    cantCar = cargarSimbolos("simbolos.txt", vecSim);
    intercambiarPalabra("palabras.txt", "atletico", "juventus", vecSim, cantCar);
    return 0;
}

