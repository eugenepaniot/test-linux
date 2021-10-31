#!/bin/bash
# test procedure
# rongtao 2021.10.31

gcc -nostdlib obj1.c -c -m32
gcc -nostdlib obj2.c -c -m32

readelf -r obj1.o
objdump -d obj1.o
objdump -d obj2.o

gcc -nostdlib obj1.o obj2.o -m32 -o a.out
objdump -d a.out
