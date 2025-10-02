#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lib/pilaDinamica/../../../../TDA/pilaDinamica/pilaDin.h"
#include "lib/colaDinamica/../../../../TDA/colaDinamica/colaDin.h"
#include "lib/listaDinamica/../../../../TDA/TDALista/listaSimpleEnlazada/listaEnlazada.h"

/*
Goal: Use all three TDAs meaningfully
- Stack (pila): bracket matching validator
- Queue (cola): enqueue results for lines (in order) to flush at the end
- List (lista): collect error summaries (type and count) to print at the end
Input: resources/lines.txt (one expression per line)
Outputs:
- resources/valid.txt (lines that passed)
- resources/invalid.txt (lines that failed + first error position)
- stdout summary based on list
*/

typedef struct {
    int lineNo;
    int valid;   /* 1 valid, 0 invalid */
    int errPos;  /* 1-based error position or 0 */
} Result;

typedef struct {
    char kind; /* '}', ')', ']' for missing closer; or 'm' for mismatch; 'e' for extra */
    int count;
} ErrSummary;

static int match(char open, char close) {
    return (open=='(' && close==')') ||
           (open=='[' && close==']') ||
           (open=='{' && close=='}');
}

static void push_char(tPila *p, char c) { ponerEnPila(p, &c, sizeof(c)); }
static int pop_char(tPila *p, char *c) { return sacarDePila(p, c, sizeof(*c)); }

static void add_summary(tLista *sum, char kind) {
    /* find existing */
    tLista it = *sum;
    ErrSummary cur;
    while (it) {
        memcpy(&cur, it->info, it->tamInfo);
        if (cur.kind == kind) {
            cur.count++;
            memcpy(it->info, &cur, sizeof(cur));
            return;
        }
        it = it->sig;
    }
    /* new */
    ErrSummary neu = { kind, 1 };
    ponerAlFinal(sum, &neu, sizeof(neu));
}

int main(void) {
    FILE *pf = fopen("resources/lines.txt", "rt");
    if (!pf) {
        perror("lines.txt");
        return 1;
    }
    FILE *pfv = fopen("resources/valid.txt", "at");
    FILE *pfi = fopen("resources/invalid.txt", "at");
    if (!pfv || !pfi) {
        perror("open outputs");
        return 2;
    }

    tCola cola; crearCola(&cola);
    tLista resumen; crearLista(&resumen);

    char buf[512];
    int lineNo = 0;

    while (fgets(buf, sizeof buf, pf)) {
        lineNo++;
        /* trim newline */
        size_t n = strlen(buf);
        if (n && (buf[n-1]=='\n' || buf[n-1]=='\r')) buf[--n]='\0';
        if (n && buf[n-1]=='\r') buf[--n]='\0';

        tPila pila; crearPila(&pila);
        int pos=0, errPos=0; char errKind=0; int ok=1;
        for (pos=0; buf[pos]; ++pos) {
            char c = buf[pos];
            if (c=='('||c=='['||c=='{') {
                push_char(&pila, c);
            } else if (c==')'||c==']'||c=='}') {
                char open;
                if (!pop_char(&pila, &open)) {
                    ok=0; errPos=pos+1; errKind='e'; break; /* extra closer */
                }
                if (!match(open,c)) {
                    ok=0; errPos=pos+1; errKind='m'; break; /* mismatch */
                }
            }
        }
        if (ok) {
            char leftover;
            if (verTopePila(&pila, &leftover, sizeof(leftover))) {
                /* missing closer at end */
                ok=0; errPos=(int)n; errKind = (leftover=='(')?')':(leftover=='[')?']':'}';
            }
        }
        vaciarPila(&pila);

        Result r = { lineNo, ok, ok?0:errPos };
        ponerEnCola(&cola, &r, sizeof(r));
        if (!ok) add_summary(&resumen, errKind);
    }

    /* flush results in order */
    Result r;
    while (!colaVacia(&cola)) {
        sacarDeCola(&cola, &r, sizeof(r));
        if (r.valid)
            fprintf(pfv, "line %d: OK\n", r.lineNo);
        else
            fprintf(pfi, "line %d: ERROR at pos %d\n", r.lineNo, r.errPos);
    }

    /* print summary */
    ErrSummary s;
    printf("Summary of errors (by type):\n");
    tLista it = resumen;
    while (it) {
        memcpy(&s, it->info, it->tamInfo);
        const char *label = (s.kind=='e')?"extra closer":(s.kind=='m')?"mismatch":(s.kind=='}'||s.kind==']'||s.kind==')')?"missing closer":"other";
        printf("  %c (%s): %d\n", s.kind, label, s.count);
        it = it->sig;
    }

    vaciarCola(&cola);
    vaciarLista(&resumen);
    fclose(pfv); fclose(pfi); fclose(pf);
    return 0;
}
