#!/bin/sh -ex

CC="gcc -ansi -pedantic"
for MODULE in assert formula assumptions proof; do
    (cd src && ${CC} -I../include -c $MODULE.c -o $MODULE.o)
done
