CC = gcc
CFLAGS=-g

main.o: main.c graph.h
	gcc -c main.c

graph.o: graph.c graph.h pFile.h
	gcc -c graph.c

pFile.o: pFile.c pFile.h
	gcc -c pFile.c

mon_exe: pFile.o graph.o main.o
	gcc pFile.o graph.o main.o -o mon_exe


