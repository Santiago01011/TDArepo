/*****************************************************************************************************************
** Apellido/s, Nombre/s:                                    													**
** DNI:                                                   													**
******************************************************************************************************************
** Correcci�n																								   	**
****************																							   	**

******************************************************************************************************************
** Nota:
*****************************************************************************************************************/

//#define SOLUCION_DOC
#define SOLUCION_ALU


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Comun/Comun.h"
#include "../Vector/Vector.h"

#define PROD_COR "Productos-cor.dat"
#define PROD_CHU_TXT "Productos-chu.txt"
#define CLI_COR "Clientes-cor.dat"
#define CLI_CHU "Clientes-chu.dat"
#define PROD_FUS "Productos-fus.dat"
#define CLI_FUS "Clientes-fus.dat"

#define CANT_INI 20

//Estructuras
typedef struct
{
    char codigo[31];
    char descripcion[51];
    float precio;
    int stock;
} Producto;

typedef struct
{
    int codigo;
    char apellidoYNombre[51];
} Cliente;

void cambiarExtension(const char* nombreArchOrig, char* nombreArchNuevo, const char* extencion);
typedef int(*Conv)(const char*, void*);
int convertirTxtProducto(const char* linea, void* elem);
typedef void(*print_callback)(void*);
void printProducto(void* elem);
void printCliente(void* elem);
int mostrarArchivoGen_ALU(const char* nombreArch, size_t tamElem, print_callback print);
int txtABin_ALU(const char* nombreArchTxt, const char* nombreArchBin, size_t tamElem, Conv convertir);
int ordenarArchivoGen_ALU(const char* nombreArchivo, size_t tamElem, Cmp cmp, Actualizar actu);
int cmpClientes_ALU(const void* cl1, const void* cl2);
int cmpProductos_ALU(const void* prod1, const void* prod2);
int procesarArchivos_ALU(
	const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
	const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
	const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus);
int fusionarArchivosGen_ALU(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp);
int vectorCargarDeArchivo_ALU(const char* nombreArch, Vector* vector, size_t tamElem, Cmp cmp, Actualizar actu);
int vectorCrear_ALU(Vector* vec, size_t tamElem);
void vectorDestruir_ALU(Vector* vec);
void vectorGrabar_ALU(Vector* v, const char* nombreArch);
bool vectorOrdInsertar_ALU(Vector * vector, void * dato, Cmp cmp, Actualizar actu);
bool vectorBsearch(Vector* vec, void* dato, Cmp cmp, int* pos);
void actualizarProductos_ALU(void* pvActualizado, const void* pvActualizador);

//generar archivos, hay 2 empresas, una de COR y otra de CHU, ambas tienen distintos archivos de productos y clientes
int generarArchivos_ALU(){
    FILE* arch = fopen(PROD_COR, "wb");
    if(!arch){
        printf("Error al abrir el archivo %s", PROD_COR);
        return ERR_ARCHIVO;
    }
    Producto prod[10] = {
        {"NOTEBOOK_DELL_R7_256GB", "Notebook Dell Ryzen 7 256gb", 150000, 10},
        {"NOTEBOOK_ASUS_I5_128GB", "Notebook ASUS I5 128gb", 90000, 6},
        {"NOTEBOOK_DELL_R3_64GB", "Notebook Dell Ryzen 3 64gb", 50000, 3},
        {"NOTEBOOK_HP_I7_256GB", "Notebook HP I7 256gb", 120000, 7},
        {"NOTEBOOK_HP_I5_128GB", "Notebook HP I5 128gb", 80000, 4},
        {"NOTEBOOK_HP_I3_64GB", "Notebook HP I3 64gb", 40000, 2},
        {"NOTEBOOK_ASUS_I7_256GB", "Notebook ASUS I7 256gb", 140000, 8},
        {"NOTEBOOK_DELL_R5_128GB", "Notebook Dell Ryzen 5 128gb", 100000, 5},
        {"NOTEBOOK_ASUS_I3_64GB", "Notebook ASUS I3 64gb", 45000, 3},
        {"NOTEBOOK_LENOVO_I7_256GB", "Notebook LENOVO I7 256gb", 130000, 9}
    };
    fwrite(prod, sizeof(Producto), 10, arch);
    fclose(arch);

    arch = fopen(PROD_CHU_TXT, "w");
    if(!arch){
        printf("Error al abrir el archivo %s", PROD_CHU_TXT);
        return ERR_ARCHIVO;
    }
    fprintf(arch, "NOTEBOOK_DELL_R7_256GB|Notebook Dell Ryzen 7 256gb|160000|25\n");
    fprintf(arch, "NOTEBOOK_DELL_R5_128GB|Notebook Dell Ryzen 5 128gb|100000|5\n");
    fprintf(arch, "NOTEBOOK_DELL_R3_64GB|Notebook Dell Ryzen 3 64gb|50000|3\n");
    fprintf(arch, "NOTEBOOK_HP_I7_256GB|Notebook HP I7 256gb|120000|7\n");
    fprintf(arch, "NOTEBOOK_HP_I5_128GB|Notebook HP I5 128gb|80000|4\n");
    fprintf(arch, "NOTEBOOK_HP_R7_64GB|Notebook HP Ryzen 7 64gb|40000|9\n");
    fprintf(arch, "NOTEBOOK_ASUS_I7_256GB|Notebook ASUS I7 256gb|140000|8\n");
    fprintf(arch, "NOTEBOOK_ASUS_I5_128GB|Notebook ASUS I5 128gb|90000|6\n");
    fprintf(arch, "NOTEBOOK_ASUS_I3_64GB|Notebook ASUS I3 64gb|45000|3\n");
    fprintf(arch, "NOTEBOOK_LENOVO_I7_256GB|Notebook LENOVO I7 256gb|130000|9\n");
    fclose(arch);

    arch = fopen(CLI_COR, "wb");
    if(!arch){
        printf("Error al abrir el archivo %s", CLI_COR);
        return ERR_ARCHIVO;
    }
    Cliente cli[5] = {
        {2, "Gomez, Maria"},
        {4, "Rodriguez, Laura"},
        {3, "Gonzalez, Carlos"},
        {1, "Perez, Juan"},
        {7, "Colombo, Ana"}
    };
    fwrite(cli, sizeof(Cliente), 5, arch);
    fclose(arch);

    arch = fopen(CLI_CHU, "wb");
    if(!arch){
        printf("Error al abrir el archivo %s", CLI_CHU);
        return ERR_ARCHIVO;
    }
    Cliente cli2[6] = {
        {5, "Fernandez, Ana"},
        {3, "Gonzalez, Carlos"},
        {2, "Gomez, Maria"},
        {4, "Rodriguez, Laura"},
        {1, "Perez, Juan"},
        {6, "Lopez, Pedro"}
    };
    fwrite(cli2, sizeof(Cliente), 6, arch);
    fclose(arch);

    return TODO_OK;
}

int main(){
    int resp = generarArchivos_ALU();

    if(resp != TODO_OK)
    {
        printf("Error al generar los archivos");
        return resp;
    }

    puts("Archivos Pre Fusion:\n");

    puts(PROD_COR);
    puts("=========================================");
    mostrarArchivoGen_ALU(PROD_COR, sizeof(Producto), printProducto);

    puts("\n");

    //puts(PROD_CHU_TXT);
    puts("=========================================");
    //mostrarArchivoProductosTxt(PROD_CHU_TXT);

    puts("\n");

    puts(CLI_COR);
    puts("=========================================");
    mostrarArchivoGen_ALU(CLI_COR, sizeof(Cliente), printCliente);

    puts("\n");

    puts(CLI_CHU);
    puts("=========================================");
    mostrarArchivoGen_ALU(CLI_CHU, sizeof(Cliente), printCliente);


    #ifdef SOLUCION_DOC
        resp = procesarArchivos(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
    #else
        resp = procesarArchivos_ALU(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
    #endif

    if(resp != TODO_OK)
    {
        printf("Error al procesar los archivos");
        return resp;
    }

    return 0;
}

int procesarArchivos_ALU(
	const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
	const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
	const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus)
{
    int res=0;
	char nombreArchProductosChuBin[50];
	cambiarExtension(nombreArchivoProductosChu, nombreArchProductosChuBin, ".dat");
	res=txtABin_ALU(nombreArchivoProductosChu,nombreArchProductosChuBin, sizeof(Producto), convertirTxtProducto); if(res!=TODO_OK) return res;
    //res=mostrarArchivoGen_ALU(nombreArchProductosChuBin, sizeof(Producto), printProducto); if(res!=TODO_OK) return res;
    //res=mostrarArchivoGen_ALU(nombreArchivoClientesChu, sizeof(Cliente), printCliente); if(res!=TODO_OK) return res;
	res=ordenarArchivoGen_ALU(nombreArchivoClientesChu, sizeof(Cliente), cmpClientes_ALU, NULL); if(res!=TODO_OK) return res;
    res=mostrarArchivoGen_ALU(nombreArchivoClientesChu, sizeof(Cliente), printCliente); if(res!=TODO_OK) return res;
    res=ordenarArchivoGen_ALU(nombreArchivoClientesCor, sizeof(Cliente), cmpClientes_ALU, NULL); if(res!=TODO_OK) return res;
    res=mostrarArchivoGen_ALU(nombreArchivoClientesCor, sizeof(Cliente), printCliente); if(res!=TODO_OK) return res;
    res=ordenarArchivoGen_ALU(nombreArchProductosChuBin, sizeof(Producto), cmpProductos_ALU, actualizarProductos_ALU); if(res!=TODO_OK) return res;
    res=mostrarArchivoGen_ALU(nombreArchProductosChuBin, sizeof(Producto), printProducto); if(res!=TODO_OK) return res;
    res=ordenarArchivoGen_ALU(nombreArchivoProductosCor, sizeof(Producto), cmpProductos_ALU, actualizarProductos_ALU); if(res!=TODO_OK) return res;
    res=mostrarArchivoGen_ALU(nombreArchivoProductosCor, sizeof(Producto), printProducto); if(res!=TODO_OK) return res;
    res=fusionarArchivosGen_ALU(nombreArchivoClientesChu, nombreArchivoClientesCor, nombreArchivoClientesFus, sizeof(Cliente), cmpClientes_ALU); if(res!=TODO_OK) return res;
    res=mostrarArchivoGen_ALU(nombreArchivoClientesFus, sizeof(Cliente), printCliente); if(res!=TODO_OK) return res;
	res=fusionarArchivosGen_ALU(nombreArchProductosChuBin, nombreArchivoProductosCor, nombreArchivoProductosFus, sizeof(Producto), cmpProductos_ALU); if(res!=TODO_OK) return res;
    res=mostrarArchivoGen_ALU(nombreArchivoProductosFus, sizeof(Producto), printProducto); if(res!=TODO_OK) return res;
	return TODO_OK;
}

int convertirTxtProducto(const char* linea, void* elem){
    Producto* aux = (Producto*)elem;
    if(sscanf(linea, "%31[^|]|%51[^|]|%f|%d", aux->codigo, aux->descripcion, &aux->precio, &aux->stock)==4)
        return TODO_OK;
    return -1;
}

void printProducto(void* elem){
    Producto* aux = (Producto*)elem;
    printf("Cod: %s\t desc: %s\t Precio: %.2f\t Stock: %d\n",aux->codigo, aux->descripcion, aux->precio, aux->stock);
}
void printCliente(void* elem){
    Cliente* aux = (Cliente*)elem;
    printf("Cod: %d\tAyN: %s\n", aux->codigo, aux->apellidoYNombre);
}

int mostrarArchivoGen_ALU(const char* nombreArch, size_t tamElem, print_callback print){
    FILE* arch = fopen(nombreArch, "rb");
    if(!arch){
        printf("Error al abrir el archivo %s", nombreArch);
        return ERR_ARCHIVO;
    }
    void* elem = malloc(tamElem);
    if(!elem){
        printf("Error al asignar memoria");
        fclose(arch);
        return -21;
    }
    printf("\n----------Archivo %s----------\n", nombreArch);
    while(fread(elem, tamElem, 1, arch)){
        print(elem);
    }
    puts("----------Fin de archivo----------\n");
    fclose(arch);
    free(elem);
    return TODO_OK;
}

void cambiarExtension(const char* nombreArchOrig, char* nombreArchNuevo, const char* extencion){
    nombreArchNuevo[0]='\0';
    int i = 0;
    while(nombreArchOrig[i] != '.' && nombreArchOrig[i] != '\0'){
        nombreArchNuevo[i]=nombreArchOrig[i];
        i++;
    }
    nombreArchNuevo[i]='\0';
    strcat(nombreArchNuevo, extencion);
}

int txtABin_ALU(const char* nombreArchTxt, const char* nombreArchBin, size_t tamElem, Conv convertir){
    FILE* archTxt = fopen(nombreArchTxt, "r");
    if(!archTxt){
        printf("Error al abrir el archivo %s", nombreArchTxt);
        return ERR_ARCHIVO;
    }
    FILE* archBin = fopen(nombreArchBin, "wb");
    if(!archBin){
        printf("Error al abrir el archivo %s", nombreArchBin);
        fclose(archTxt);
        return ERR_ARCHIVO;
    }
    void* elem = malloc(tamElem);
    if(!elem){
        fclose(archBin);
        fclose(archTxt);
        printf("Error al asignar memoria");
    }
    char linea[200];
    while(fgets(linea, 200, archTxt)){
        if(convertir(linea, elem) == TODO_OK)
            fwrite(elem, tamElem, 1, archBin);
    }
    fclose(archBin);
    fclose(archTxt);
    free(elem);
    return TODO_OK;
}

int ordenarArchivoGen_ALU(const char* nombreArchivo, size_t tamElem, Cmp cmp, Actualizar actu){
    FILE* arch = fopen(nombreArchivo, "rb");
    if(!arch){
        printf("Error al abrir el archivo %s", nombreArchivo);
        return ERR_ARCHIVO;
    }
    Vector vec;
    vectorCrear_ALU(&vec, tamElem);
    vectorCargarDeArchivo_ALU(nombreArchivo, &vec, tamElem, cmp, actu);
    vectorGrabar_ALU(&vec, nombreArchivo);
    vectorDestruir_ALU(&vec);
    return TODO_OK;
}

int cmpClientes_ALU(const void* cl1, const void* cl2){
    Cliente* a = (Cliente*)cl1;
    Cliente* b = (Cliente*)cl2;
    return a->codigo - b->codigo;
}

int fusionarArchivosGen_ALU(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp){
    FILE* arch1 = fopen(nombreArchivo1, "rb");
    if(!arch1){
        printf("Error al abrir el archivo %s", nombreArchivo1);
        return ERR_ARCHIVO;
    }
    FILE* arch2 = fopen(nombreArchivo2, "rb");
    if(!arch2){
        fclose(arch1);
        printf("Error al abrir el archivo %s", nombreArchivo2);
        return ERR_ARCHIVO;
    }
    FILE* archFus = fopen(nombreArchivoFus, "wb");
    if(!archFus){
        fclose(arch1);
        fclose(arch2);
        printf("Error al abrir el archivo %s", nombreArchivoFus);
        return ERR_ARCHIVO;
    }
    void* elem = malloc(tamReg); //TDAStock nombre, stock, cod, TDAmov cod, stock  [ieldrealmanchesterbanf] // 22 chars
    if(!elem){
        fclose(arch1);
        fclose(arch2);
        fclose(archFus);
        printf("Error al reservar memoria para %s", nombreArchivoFus);
        return SIN_MEM;
    }
    void* elem2 = malloc(tamReg);
    if(!elem2){
        fclose(arch1);
        fclose(arch2);
        fclose(archFus);
        free(elem);
        printf("Error al reservar memoria para %s", nombreArchivoFus);
        return SIN_MEM;
    }
    fread(elem, tamReg, 1, arch1);
    fread(elem2, tamReg, 1, arch2);
    while(!feof(arch1) && !feof(arch2)){
        int resultado = cmp(elem, elem2);
        if(resultado == 0){
            actualizarProductos_ALU(elem, elem2);
            fwrite(elem, tamReg, 1, archFus);
            fread(elem, tamReg, 1, arch1);
            fread(elem2, tamReg, 1, arch2);
        }
        if(resultado < 0){
            fwrite(elem, tamReg, 1, archFus);
            fread(elem, tamReg, 1, arch1);
        }
        if(resultado > 0){
            fwrite(elem2, tamReg, 1, archFus);
            fread(elem2, tamReg, 1, arch2);
        }
    }
    while(!feof(arch1)){
        fwrite(elem, tamReg, 1, archFus);
        fread(elem, tamReg, 1, arch1);
    }
    while(!feof(arch2)){
        fwrite(elem2, tamReg, 1, archFus);
        fread(elem2, tamReg, 1, arch2);
    }
    fclose(arch1);
    fclose(arch2);
    fclose(archFus);
    free(elem);
    free(elem2);
    return TODO_OK;
}

int cmpProductos_ALU(const void* prod1, const void* prod2){
    Producto* a = (Producto*)prod1;
    Producto* b = (Producto*)prod2;
    return strcmpi(a->codigo, b->codigo);
}

int vectorCargarDeArchivo_ALU(const char* nombreArch, Vector* vector, size_t tamElem, Cmp cmp, Actualizar actu){
    FILE* arch = fopen(nombreArch, "rb");
    if(!arch){
        printf("Error al abrir el archivo %s", nombreArch);
        return ERR_ARCHIVO;
    }
    void* elem = malloc(tamElem);
    if(!elem){
        puts("Error al asignar memoria");
        return SIN_MEM;
    }
    while(fread(elem, tamElem, 1, arch)){
        vectorOrdInsertar_ALU(vector, elem, cmp, actu);
    }
    free(elem);
    fclose(arch);

    return TODO_OK;
}

int vectorCrear_ALU(Vector* vec, size_t tamElem){
    vec->vec = malloc(tamElem * CANT_INI);
    if(!vec->vec){
        puts("Error al asignar memoria dinamica");
        return SIN_MEM;
    }
    vec->ce = 0;
    vec->cap = CANT_INI;
    vec->tamElem = tamElem;
    return TODO_OK;
}
void vectorDestruir_ALU(Vector* vec){
    if(!vec->vec){
        return;
    }
    free(vec->vec);
}
void vectorGrabar_ALU(Vector* v, const char* nombreArch){
    FILE* arch = fopen(nombreArch, "wb");
    if(!arch){
        return;
    }
    for(int i=0; i < v->ce; i++){
        fwrite((v->vec) + (i * v->tamElem), v->tamElem, 1, arch);
    }
    fclose(arch);
}

void actualizarProductos_ALU(void* pvActualizado, const void* pvActualizador){
    Producto* aux1 = (Producto*)pvActualizado;
    Producto* aux2 = (Producto*)pvActualizador;
    aux1->stock += aux2->stock;
    if(aux1->precio < aux2->precio){
        aux1->precio = aux2->precio;
    }
}

int vectorInsertarEnPos(Vector * vec, void * dato, int pos){
    if(vec->cap == vec->ce){
        vec->cap*=2;
        realloc(vec->vec, vec->cap*vec->tamElem);
        if(!vec->vec)
            return -23;
    }
    memcpy(vec->vec + (pos*vec->tamElem), dato, vec->tamElem);
    vec->ce++;
    return TODO_OK;
}

bool vectorOrdInsertar_ALU(Vector * vec, void * elem, Cmp cmp, Actualizar actu){
    int pos = 0;
    if(vec->ce==0)
        vectorInsertarEnPos(vec, elem, pos);
	else if(vectorBsearch(vec, elem, cmp, &pos)){
		actu(vec->vec + pos * vec->tamElem, elem);
	}else{
		memmove(vec->vec + (pos + 1) * vec->tamElem, vec->vec + pos * vec->tamElem, (vec->ce - pos) * vec->tamElem);
		vectorInsertarEnPos(vec, elem, pos);
	}
    return true;
}

bool vectorBsearch(Vector* vec, void* dato, Cmp cmp, int* pos){
    int ini = 0, fin = vec->ce - 1, med, resultado;
    while(ini<=fin){
        med = ini + (fin - ini) / 2;
        void* elemMed = vec->vec + (med*vec->tamElem);
        resultado = cmp(elemMed, dato);
        if(resultado==0){
            *pos = med;
            return true;
        }
        if(resultado > 0)
            fin = med - 1;
        if(resultado < 0)
            ini = med + 1;
    }
    *pos=ini;
    return false;
}
