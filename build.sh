#!/bin/sh -ex

CC="gcc -ansi -pedantic"
for MODULE in formula assumptions proof; do
    (cd src && ${CC} -I../include -c $MODULE.c -o $MODULE.o)
done
