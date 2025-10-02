#!/bin/bash
set -euo pipefail
CC=gcc
CFLAGS="-Wall -Wextra -std=c99 -g -O2"
INCLUDES="-Isrc -Isrc/lib -I../../TDA/colaDinamica -I../../TDA/TDALista/listaSimpleEnlazada -I../../TDA/pilaDinamica"
SOURCES=$(cat <<'EOF'
src/main.c
src/lib/colaDinamica/colaDin.c
src/lib/listaDinamica/listaDin.c
src/lib/pilaDinamica/pilaDin.c
EOF
)
mkdir -p src/bin
$CC $CFLAGS $INCLUDES $SOURCES -o src/bin/balanceo
if [[ "${1:-}" == "run" ]]; then
  (cd src && ./bin/balanceo)
fi
