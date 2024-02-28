#!/bin/bash

build: tema3.o functions.o functions.h
	gcc -o tema3 tema3.o functions.o -g
tema3.o: tema3.c
	gcc -c tema3.c -g
functions.o: functions.c functions.h
	gcc -c functions.c -g
clean:
	rm -rf *.o
	rm "tema3"
