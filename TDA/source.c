#include "main.h"

char menuConErr(const char *msg, const char *opc){
    char opta;
    int flag = 1;
    do{
        printf("%s%s",
        flag ? flag = 0, "" : "ERROR - Opcion NO valida. Reingrese.\n",
        msg);
        fflush(stdin);
        scanf(" %c", &opta);
    }while(strchr(opc, opta) == NULL);
    return opta;
}

void mainMenu(){
    tArbol arbolIdx;
    char opc;
    crearArbol(&arbolIdx);
    cargarDesdeArchivoOrdenado(&arbolIdx, "alumnos.idx", sizeof(Idx));

    do{

        opc = menuConErr("Elija una opcion:\n"
                        "A. Dar de baja alumno\n"
                        "B. Mostrar archivo alumnos\n"
                        "F. Salir\n", "ABFabf");

        switch(toupper(opc)){
            case 'A': puts("Opcion A"); darDeBajaAlumno(&arbolIdx); break;
            case 'B': puts("Opcion B"); mostrarArchGen("alumnos.dat", sizeof(tAlumno), printAlumno); break;
            case 'F': puts ("FIN...");
                    arbol_grabar_a_bin(&arbolIdx, "alumnos.idx", grabar_alumnoIdx_a_bin);
                    mostrarArchGen("alumnos.idx", sizeof(tAlumno), printIdx); return;
        }
        system("pause");
        system("cls");
    }while(1);
}

void printAlumno(void* alu){
    tAlumno* a = (tAlumno*)alu;
    printf("Nombre: %s\nDNI: %d\nEstado: %c\n", a->nombre, a->dni, a->estado);
}

void printIdx(void* idx){
    Idx* i = (Idx*)idx;
    printf("Registro: %d\nDNI: %d\n", i->reg, i->dni);
}

int mostrarArchGen(const char *ruta, size_t tam, printStruct prints){
    FILE* arch = fopen(ruta, "rb");
    if(!arch)   return 0;
    void* buffer = malloc(tam);
    if(!buffer){
        fclose(arch);
        return 0;
    }
    printf("Leyendo archivo: %s\n", ruta);
    while(fread(buffer, tam, 1, arch)){
        prints(buffer);
    }
    puts("Fin de archivo");
    free(buffer);
    fclose(arch);
    return 1;
}

int cmpDni(const void* a, const void* b){
    return *(int*)a - ((Idx*)b)->dni;
}

int darDeBajaAlumno(tArbol *p){
    int dni;
    tAlumno alu;
    printf("Ingrese DNI del alumno a dar de baja: ");
    scanf("%d", &dni);
    tNodoArbol** nodo = buscarNodo(p, &dni, cmpDni);
    if(!nodo){
        puts("No se encontro el alumno");
        return 0;
    }
    Idx* idx = (Idx*)(*nodo)->info;
    FILE* arch = fopen("alumnos.dat", "r+b");
    if(!arch){
        puts("Error al abrir el archivo");
        return 0;
    }
    fseek(arch, idx->reg * sizeof(tAlumno), SEEK_SET);
    fread(&alu, sizeof(tAlumno), 1, arch);
    fseek(arch, (idx->reg) * sizeof(tAlumno), SEEK_SET);
    alu.estado = 'B';
    fwrite(&alu, sizeof(tAlumno), 1, arch);
    fclose(arch);
    eliminarRaiz(nodo);
    return 1;
}





