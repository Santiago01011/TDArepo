#include "main.h"

int cmpPalabra(const void* a, const void* b){
    return strcmp((char*)a, (char*)b);
}

int intercambiarPalabra(const char* nombreArch, const char* palabraBuscada, const char* palabraAinsertar, char* vecChar, int cantElem){
    char linea[CANTMAX];
    char *p, *aux;
    char temp;
    FILE* archTemp;
    FILE* archPalabra = fopen(nombreArch, "r");
    if(!archPalabra)
        return 0;
     archTemp = fopen("palabrasTem.txt", "w");

    if(!archTemp){
        fclose(archPalabra);
        return 0;
    }

    while(fgets(linea, CANTMAX, archPalabra)){
        p = linea;
        while(*p != '\n' || *p != '\0'){
            while(esSimbolo(vecChar, p, cantElem) != 0){
                fprintf(archTemp, "%c", *p);
                p++;
            }
            aux = p;
            while(*aux != '\0' && esSimbolo(vecChar, aux, cantElem) == 0)
                aux++;
            temp = *aux;
            if(temp == '\0')
                break;
            *aux = '\0';
            if(cmpPalabra(p, palabraBuscada) == 0)
                fprintf(archTemp, "%s", palabraAinsertar);
            else
                fprintf(archTemp, "%s", p);
            *aux = temp;
            p = aux;
        }
    }
    fclose(archPalabra);
    fclose(archTemp);
    remove(nombreArch);
    rename("palabrasTem.txt", nombreArch);
    return 1;
}

int cargarSimbolos(const char* nombreArch, char* vecChar){
    int cantCar = 0;
    FILE* pf = fopen(nombreArch, "r");
    if(!pf)
        return 0;
    fgets(vecChar, CANTMAX, pf);
    while(vecChar[cantCar] != '\0')
        cantCar++;
    fclose(pf);
    return cantCar;
}

int esSimbolo(char* vecChar, char *p, int cantElem){
    int i = 0;
    while(i < cantElem){
        if(*p == vecChar[i] || *p == '\n')
            return 1;
        i++;
    }
    return 0;
}


