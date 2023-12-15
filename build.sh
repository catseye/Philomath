#!/bin/sh -e

CC="gcc -ansi -pedantic"
for MODULE in assert formula assumptions theorem; do
    (cd src && ${CC} ${CFLAGS} -I../include -c $MODULE.c -o $MODULE.o)
done
