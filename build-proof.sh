#!/bin/sh -ex

./build.sh
PROOF=$1
CC="gcc -ansi -pedantic"
${CC} -Iinclude $PROOF.c src/*.o -o $PROOF.exe
