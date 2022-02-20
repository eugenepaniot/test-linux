#!/bin/bash

gcc time.c -o time.out

echo "Syscall"
time ./time.out syscall
echo "Vsyscall"
time ./time.out vsyscall
echo "VDSO"
time ./time.out vdso

rm -f time.out
