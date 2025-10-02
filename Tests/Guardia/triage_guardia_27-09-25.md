# Simulación de parcial — Triage de Guardia con TDA Cola/Lista/Pila (ANSI C)

Fecha: 27/09/2025

## Enunciado
Un hospital realiza el triage de pacientes en Guardia. Los pacientes llegan con una prioridad clínica y deben ser
asignados a médicos disponibles. La atención se considera instantánea para este ejercicio (no hay tiempos de
servicio), por lo que un médico vuelve a quedar disponible inmediatamente luego de asignarse un paciente.

Se utiliza el siguiente esquema de prioridades (de mayor a menor):
- Rojo (R)
- Amarillo (A)
- Verde (V)

Los pacientes llegan en un archivo de texto ordenado por horario de llegada. Los médicos habilitados para la
Guardia se listan en otro archivo. Debe procesarse la guardia asignando pacientes a médicos siguiendo la
prioridad R > A > V y balanceando la asignación entre médicos de manera circular (round-robin).

## Objetivo
Procesar las llegadas y generar:
- `atendidos.txt`: una línea por paciente atendido con el médico asignado.
- `pendientes.txt`: pacientes que quedaron en espera al finalizar el archivo de llegadas.

Mientras haya médicos disponibles y pacientes esperando, debe asignarse en el orden de prioridad. Los médicos
se asignan en rotación: si el médico M1 atendió, el siguiente en atender será M2, luego M3, … y al final vuelve a M1.

## Restricciones
- ANSI C (C89/C90). Sin extensiones.
- NO usar árbol/binario. Debe usarse al menos:
  - Tres Colas Dinámicas (una por prioridad: R, A, V) — usando el TDA Cola Dinámica provisto.
  - Una Lista (dinámica simple) para manejar el pool de médicos en rotación (round-robin).
  - (Opcional) Una Pila para mantener un historial de los últimos N pacientes atendidos (para auditar).
- Los archivos de entrada son pequeños: se permite búsqueda lineal y estructuras en memoria simples.

## Archivos
Entrada:
- `medicos.txt` (texto, un médico por línea):
  - Formato por línea (longitud variable): `legajo;apellido_nombre`  
    Ej.: `0001;SUAREZ, ANA`  
    NOTA: El legajo es un numérico, pero se recomienda tratarlo como texto para conservar ceros a la izquierda.
- `llegadas.txt` (texto, líneas de longitud fija, ordenado por hora):
  - `hora`: 4 chars, HHMM (ej.: `0830`)  
  - `dni`: 8 chars, sólo dígitos (ej.: `12345678`)  
  - `prioridad`: 1 char en {`R`,`A`,`V`}  
  - Longitud total por línea: 13 caracteres, puede terminar con `\n`.
  - Ej.: `083012345678R`  

Salida:
- `atendidos.txt` (texto): `hora;dni;prioridad;legajo_medico`  
  Ej.: `0830;12345678;R;0001`
- `pendientes.txt` (texto): `dni;prioridad` por cada paciente que quedó en alguna cola al final.

## Uso de TDA
- Cola Dinámica: una cola por prioridad (R, A, V).  
  Operaciones: `ponerEnCola`, `sacarDeCola`, `colaVacia`.
- Lista Dinámica: lista de médicos para rotación round-robin.  
  Operaciones sugeridas: `crearLista`, `insertarAlFinal`, `sacarPrimero` + `insertarAlFinal` (para rotar),
  o una operación `moverPrimeroAlFinal` si la tiene.
- Pila Dinámica (opcional): historial de últimos N atendidos.  
  Operaciones: `ponerEnPila`, `sacarDePila`.

## Contratos sugeridos
Estructuras de trabajo (en memoria):
```c
/* ANSI C */
#define MAX_MED 64

typedef struct {
    char hora[5];   /* HHMM + '\0' */
    char dni[9];    /* 8 + '\0' */
    char prioridad; /* 'R' | 'A' | 'V' */
} Paciente;

typedef struct {
    char legajo[8];      /* hasta 7 + '\0' */
    char apellNom[64];   /* uso interno opcional */
} Medico;

/* Lista de médicos (usar su TDA lista) */
/* Cola por prioridad (usar su TDA cola dinámica) */

int cargarMedicos(const char* path, /*out*/tLista* listaMed); /* inserta en orden de archivo */
int parseLlegada(const char* linea, Paciente* p);              /* valida y separa campos */
```

## Algoritmo (alto nivel)
1. Cargar médicos desde `medicos.txt` en una lista; la lista define el orden de rotación.
2. Inicializar tres colas: `colaR`, `colaA`, `colaV`.
3. Abrir `llegadas.txt` y outputs `atendidos.txt` y `pendientes.txt`.
4. Para cada línea de `llegadas.txt`:
   - Parsear a `Paciente p`.
   - Encolar en la cola correspondiente según `p.prioridad`.
   - Mientras haya médicos en la lista y exista algún paciente encolado:
     - Tomar el primer médico de la lista (quitar de la cabeza) y volver a insertarlo al final (rotación).
     - Seleccionar la primera cola no vacía en el orden R, A, V.
     - Desencolar un paciente y escribir `atendidos.txt` con `hora;dni;prioridad;legajo_medico`.
     - (Opcional) Push a una pila de historial (tamaño N fijo) con ese atendido.
5. Al terminar el archivo, volcar el remanente de las colas a `pendientes.txt` en el orden R, A, V (primero todos los R pendientes, luego A, luego V).
6. Cerrar archivos y liberar TDAs.

## Pseudocódigo
```
crearLista(&meds)
if (!cargarMedicos("medicos.txt", &meds)) error
crearCola(&colaR); crearCola(&colaA); crearCola(&colaV)
open llegadas, atendidos, pendientes
for cada linea in llegadas:
  p = parseLlegada(linea)
  switch p.prioridad: 'R' -> ponerEnCola(colaR,p); 'A' -> ...; 'V' -> ...
  while (!listaVacia(meds) && (!colaVacia(colaR)||!colaVacia(colaA)||!colaVacia(colaV))):
     m = sacarPrimero(meds); insertarAlFinal(meds,m)  // rotación
     if (!colaVacia(colaR))   paciente = sacarDeCola(colaR)
     else if (!colaVacia(colaA)) paciente = sacarDeCola(colaA)
     else paciente = sacarDeCola(colaV)
     escribir atendidos: hora;dni;prioridad;m.legajo
     (opcional) push pilaHist(paciente)
fin for
// volcamos pendientes al final
volcar colaR -> pendientes; colaA -> pendientes; colaV -> pendientes
cerrar todo
```

## Consideraciones de parsing
- `llegadas.txt`: usar `fgets(buf, sizeof buf, f)`.  
  - `hora`: copiar `buf[0..3]`, verificar 00≤HH≤23 y 00≤MM≤59.  
  - `dni`: copiar `buf[4..11]`, verificar 8 dígitos.  
  - `prioridad`: `buf[12]` ∈ {R,A,V}.  
- `medicos.txt`: leer línea, separar por `;`. Validar que `legajo` no sea vacío.

## Casos borde
- Lista de médicos vacía → nadie será atendido; todo va a `pendientes.txt`.
- Prioridad inválida en `llegadas.txt` → descartar línea (loggear en stderr opcional).
- DNI con caracteres no numéricos → descartar línea.
- Múltiples llegadas con misma hora → mantener el orden del archivo.
- Repetición de médicos en el archivo → permitir o deduplicar (definir criterio; documentar).

## Criterios de evaluación
- Uso correcto de TDA Cola (tres colas), Lista (rotación de médicos) y, si aplica, Pila (historial).
- Correctitud del orden de atención (prioridad y round-robin de médicos).
- Robustez en parsing y manejo de archivos.
- Código claro y modular con contratos definidos.

## Stubs sugeridos (interfaces)
```c
/* Lista de médicos (usando su TDA lista simple) */
int cargarMedicos(const char* path, tLista* meds);
int tomarYRotarMedico(tLista* meds, Medico* m); /* saca primero e inserta al final */

/* Colas por prioridad (usando su TDA cola dinámica) */
int encolarPorPrioridad(tCola* r, tCola* a, tCola* v, const Paciente* p);
int hayPacientes(const tCola* r, const tCola* a, const tCola* v);
int sacarPorPrioridad(tCola* r, tCola* a, tCola* v, Paciente* p);
```

## Mini dataset de ejemplo
- `medicos.txt`:
```
0001;SUAREZ, ANA
0002;PEREZ, LUIS
0003;GOMEZ, MARIA
```
- `llegadas.txt`:
```
083012345678R
083112340000V
083313335555A
083412345679R
```
- `atendidos.txt` (posible) — suponiendo rotación 0001→0002→0003→0001… y prioridad R>A>V:
```
0830;12345678;R;0001
0833;13335555;A;0002
0834;12345679;R;0003
0831;12340000;V;0001
```
- `pendientes.txt`: vacío si todos fueron asignados durante el procesamiento.

---
Si querés, puedo armarte un esqueleto `main.c` que use tus TDAs (cola dinámica + lista) y tenga el parsing y la rotación listos para completar detalles.
