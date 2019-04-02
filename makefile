CC = gcc
COMPILER_FLAGS = -g -std=c99

siguel: main.o inSVG.o outSVG.o consulta.o
	gcc -o siguel main.o inSVG.o outSVG.o consulta.o -lm

main.o: main.c inSVG.h structs.h outSVG.h consulta.h
	gcc -c main.c -o main.o

inSVG.o: inSVG.c inSVG.h outSVG.h structs.h
	gcc -c inSVG.c -o inSVG.o

outSVG.o: outSVG.c outSVG.h structs.h
	gcc -c outSVG.c -o outSVG.o

consulta.o: consulta.c structs.h consulta.h outSVG.h
	gcc -c consulta.c -o consulta.o