#!/bin/sh -ex

CC="gcc -ansi -pedantic"
for MODULE in assert formula assumptions proof; do
    (cd src && ${CC} ${CFLAGS} -I../include -c $MODULE.c -o $MODULE.o)
done
