#!/bin/sh -e

CFLAGS=""
if [ "x$1" = "x-D" ]; then
    CFLAGS="-DDEBUG"
    shift
fi
CFLAGS=${CFLAGS} ./build.sh
PROOF=$1
CC="gcc -ansi -pedantic"
${CC} -Iinclude $PROOF.c src/*.o -o $PROOF.exe
