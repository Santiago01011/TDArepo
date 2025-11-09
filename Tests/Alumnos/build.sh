#!/bin/bash
set -euo pipefail

# Simple build script for Tests/Alumnos
CC=gcc
CFLAGS="-Wall -Wextra -std=c89 -g -O2"
INCLUDES="-I. -Isrc -Isrc/lib"
SOURCES=$(cat <<'EOF'
src/main.c
src/lib/Alumnos.c
EOF
)

mkdir -p src/bin
BIN=src/bin/alumnos

echo "Compiling ${SOURCES} -> ${BIN}"
$CC $CFLAGS $INCLUDES $SOURCES -o "$BIN"

if [[ "${1:-}" == "run" ]]; then
  (cd src && ./bin/alumnos)
fi
