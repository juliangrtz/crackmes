#!/bin/bash
gcc crackme.c -o crackme -pedantic -Wall -O3 -s -static -pthread
./crackme $1 $2
