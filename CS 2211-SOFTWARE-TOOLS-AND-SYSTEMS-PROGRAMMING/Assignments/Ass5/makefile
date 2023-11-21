# Makefile for this assignment

# Define the target and dependencies
mymatrix: main.o bstree.o datatype.o matrix.o
	gcc -o mymatrix main.o bstree.o datatype.o matrix.o

# Define the object file dependencies
main.o: main.c headers.h bstree.h datatype.h matrix.h
	gcc -c main.c

bstree.o: bstree.c headers.h bstree.h datatype.h
	gcc -c bstree.c

datatype.o: datatype.c headers.h datatype.h
	gcc -c datatype.c

matrix.o: matrix.c headers.h matrix.h
	gcc -c matrix.c

# Define the clean target
clean:
	rm -f mymatrix *.o core
