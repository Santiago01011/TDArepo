# Simulación de parcial – Procesamiento de pedidos con TDA Cola (ANSI C)

Fecha: 27/09/2025

## Enunciado
Una ferretería mantiene su stock de productos en un archivo binario `productos.dat` con el siguiente formato por registro (longitud fija, sin orden particular):
- cod: 10 chars (código de producto, padded con espacios si hace falta)
- descripcion: 20 chars (padded)
- stock: unsigned int (4 bytes)
- precio: float (4 bytes)

Periódicamente llega un archivo de texto con registros de longitud fija, ordenado por `cod_ped`, con el detalle de los nuevos pedidos realizados al almacén:
- `pedidos.txt` (una línea por ítem del pedido):
  - cod_ped: numérico entero de 6 caracteres (padded con ceros a la izquierda si corresponde)
  - cod_prod: 10 chars
  - cantidad: numérico de 3 caracteres (000–999)

El archivo `pedidos.txt` está ordenado por `cod_ped` y puede tener múltiples renglones para el mismo pedido (un renglón por producto pedido).

## Objetivo
Procesar los pedidos de forma tal que, para cada `cod_ped`:
- Si el pedido completo se puede procesar (hay stock suficiente para todos sus productos), actualizar el stock en `productos.dat`, calcular el precio total y registrarlo en `pedidos_realizados.txt`.
- Si no se puede procesar (al menos un ítem sin stock suficiente), no actualizar el stock de ese pedido y registrar en `pedidos_faltantes.txt` cuáles son los productos faltantes (con cantidades faltantes) para ese `cod_ped`.

## Restricciones y Aclaraciones
- Programación en ANSI C (C89/C90). Sin extensiones específicas.
- NO usar TDA Árbol en esta versión del parcial. Para localizar productos puede usarse búsqueda secuencial sobre el archivo o una estructura auxiliar en memoria si se desea (opcional).
- Debe usarse una Cola Dinámica (sus primitivas de poner_en_cola y sacar_de_cola) para modelar y procesar, al menos, el conjunto de ítems del pedido actual.
- Mantener los archivos con los formatos especificados. `productos.dat` se actualiza en sitio (modo binario de lectura/escritura). Los outputs `pedidos_realizados.txt` y `pedidos_faltantes.txt` son de texto.
- Se asume que `productos.dat` fue creado con el mismo entorno/compilador. Para mayor portabilidad, se recomienda leer/escribir campo a campo evitando depender del padding de `struct`.

## Archivos de entrada/salida
- Entrada
  - `productos.dat` (binario, registros de tamaño fijo)
  - `pedidos.txt` (texto, líneas de longitud fija: 6+10+3 = 19 caracteres por línea, sin separadores; puede haber salto de línea al final)
- Salida
  - `pedidos_realizados.txt`: una línea por pedido realizado con formato: `cod_ped;total` donde `total` es precio final con dos decimales.
  - `pedidos_faltantes.txt`: para cada pedido no realizado, una o más líneas con formato: `cod_ped;cod_prod;faltante`.

## Definiciones y contratos sugeridos
Estructuras (en memoria, con terminación para manipulación segura):
- Producto (para trabajo en memoria, NO se sugiere volcar esta struct directo al binario):
  - `char cod[11]; // +1 para terminador`  
  - `char desc[21];`  
  - `unsigned stock;`  
  - `float precio;`
- Ítem de pedido:
  - `char codProd[11];`
  - `unsigned cant;`
- Nodo de cola: usar su TDA Cola Dinámica (nodo contiene `void* info`, `size_t tamInfo`, etc.).

Contratos clave:
- Cola Dinámica (ya provista en su TDA):
  - `int ponerEnCola(tCola*, const void* d, size_t tam);`
  - `int sacarDeCola(tCola*, void* d, size_t tam);`
- Acceso a productos:
  - `int buscarProducto(FILE* f, const char* cod, Producto* p, long* posReg);`
    - Busca secuencialmente por `cod` en `productos.dat`.
    - Devuelve 1 si encuentra; 0 si no. Si encuentra, carga `p` y devuelve en `posReg` el índice/offset del registro.
  - `int leerProductoEn(FILE* f, long posReg, Producto* p);`
  - `int escribirProductoEn(FILE* f, long posReg, const Producto* p);`

## Algoritmo propuesto (alto nivel)
1. Abrir `productos.dat` en modo `rb+` (lectura/escritura binaria) y `pedidos.txt` en modo texto para lectura.
2. Abrir/crear `pedidos_realizados.txt` y `pedidos_faltantes.txt` en modo texto para escritura/apéndice.
3. Inicializar una Cola Dinámica para los ítems del pedido actual.
4. Leer `pedidos.txt` línea por línea; parsear `cod_ped`, `cod_prod`, `cantidad` (trim/pad según corresponda).
5. Mientras el `cod_ped` sea el mismo que el `cod_ped` en curso, encolar cada ítem (`{cod_prod, cant}`). Cuando cambie el `cod_ped` (o fin de archivo):
   - Evaluar si el pedido puede cumplirse: para cada ítem de la cola, buscar el producto en `productos.dat` (búsqueda secuencial) y verificar `stock >= cant`. Acumular los faltantes si los hubiera. Puede usarse una segunda cola o una lista temporal para almacenar una copia de los ítems mientras se verifica.
   - Si todos tienen stock suficiente:
     - Recorra nuevamente los ítems y actualice en `productos.dat` (en sitio) el `stock -= cant` y acumule `total += cant * precio`.
     - Escriba `cod_ped;total` en `pedidos_realizados.txt`.
   - Si algún ítem no tiene stock suficiente:
     - Escriba una línea por ítem faltante en `pedidos_faltantes.txt` con `cod_ped;cod_prod;faltante` donde `faltante = max(0, cant - stock_existente)`.
     - NO modifique el stock de ningún producto para ese pedido.
   - Vacíe la cola del pedido y comience un nuevo grupo con el nuevo `cod_ped` (si lo hay).
6. Cerrar todos los archivos y liberar recursos.

## Pseudocódigo
```
inicializar cola items
leer primera línea de pedidos.txt
while (!EOF) {
  curr = parse(linea)
  codActual = curr.cod_ped
  encolar(curr)
  while (siguiente línea existe y siguiente.cod_ped == codActual) {
    encolar(siguiente)
  }
  // evaluar pedido
  posible = true
  total = 0
  // hacer una pasada para ver stock
  clonar cola -> colaEval (o recorrer y volver a encolar en otra cola)
  for cada item en colaEval {
    if (!buscarProducto(fProd, item.cod, prod, pos)) { faltantes[item]=item.cant; posible=false; }
    else if (prod.stock < item.cant) { faltantes[item]=item.cant - prod.stock; posible=false; }
  }
  if (posible) {
    // aplicar
    for cada item en items {
      buscarProducto(..., pos) // o use pos guardado en una estructura auxiliar
      leerProductoEn(...)
      prod.stock -= item.cant
      total += item.cant * prod.precio
      escribirProductoEn(...)
    }
    escribir pedidos_realizados.txt: codActual;total
  } else {
    for cada faltante { escribir pedidos_faltantes.txt: codActual;cod_prod;faltante }
  }
  vaciar cola items
}
```

## Parsing y E/S (sugerencias)
- `pedidos.txt`: leer con `fgets(buf, sizeof buf, f)`, luego:
  - `cod_ped`: copiar los primeros 6 chars a un buffer `char codPed[7];` y terminar en `\0`.
  - `cod_prod`: `line+6` por 10 chars -> `char codProd[11];` + `\0`.
  - `cantidad`: `line+16` por 3 chars -> convertir con `atoi`.
- `productos.dat` (binario): para portabilidad, leer/escribir campo a campo:
  - `fread(bufCod, 1, 10, f); bufCod[10]='\0';`
  - `fread(bufDesc, 1, 20, f); bufDesc[20]='\0';`
  - `fread(&stock, sizeof(unsigned), 1, f);`
  - `fread(&precio, sizeof(float), 1, f);`
  - Para escribir, si guarda strings, re-pad a longitud fija (rellenando con espacios hasta 10/20) antes de `fwrite`.
- Cálculo del tamaño de registro: 10 + 20 + 4 + 4 = 38 bytes.

## Casos borde a contemplar
- Producto inexistente en `productos.dat` → todo el pedido falla; listar faltantes de todos los ítems inexistentes.
- Múltiples renglones del mismo producto dentro del mismo `cod_ped` → sumar cantidades al evaluar (recomendado agrupar por `cod_prod` dentro de la cola antes de verificar/aplicar).
- Cantidad 0 o negativa en `pedidos.txt` → ignorar renglón o tratar como inválido (defina criterio y documente).
- `productos.dat` vacío.
- Precios 0 o negativos (datos inválidos) → permitir pero total será acorde al dato; puede validarse.
- Desbordes de stock (bajo cero) → prevenir con validación previa.
- Espacios/ruido en `cod`/`descripcion` → normalizar con trim a la hora de comparar.

## Entregables
- Código ANSI C que:
  - Implementa (o reutiliza) el TDA Cola Dinámica: `ponerEnCola`, `sacarDeCola`.
  - Implementa el procesamiento de pedidos según lo especificado.
  - Compila con `gcc` sin warnings graves (`-Wall -Wextra`).
- Archivos de salida `pedidos_realizados.txt` y `pedidos_faltantes.txt` generados a partir de entradas de prueba.

## Criterios de evaluación
- Correctitud del procesamiento y de la actualización de `productos.dat`.
- Uso adecuado del TDA Cola en el armado y procesamiento de cada pedido.
- Manejo de E/S robusto (parsing, padding, errores de apertura, etc.).
- Claridad de código y modularización (funciones pequeñas con contratos claros).
- Consideración de casos borde.

## Pistas de implementación (stubs sugeridos)
```c
/* ANSI C */
typedef struct {
    char cod[11];
    char desc[21];
    unsigned stock;
    float precio;
} Producto;

typedef struct {
    char codProd[11];
    unsigned cant;
} Item;

int buscarProducto(FILE* f, const char* cod, Producto* p, long* posReg);
int leerProductoEn(FILE* f, long posReg, Producto* p);
int escribirProductoEn(FILE* f, long posReg, const Producto* p);
```

## Mini dataset de ejemplo (opcional)
- `pedidos.txt`:
```
000001AAA0000005
000001BBB0000010
000002AAA0000003
```
- `productos.dat` (equivalente):
  - AAA....... (stock 7, precio 10.0)
  - BBB....... (stock 9, precio 5.0)

Resultado esperado:
- `000001` no se procesa (BBB faltan 1; AAA faltan 0) → listar faltantes.
- `000002` se procesa si stock de AAA remanente alcanza.

---
Suerte en el parcial. Cualquier duda o si querés que te arme un esqueleto de `main.c` con la cola integrada, avisame y lo agrego.
