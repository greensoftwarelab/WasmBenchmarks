#CC=gcc
CC=g++
CFLAGS=-O2 -Wall -fpermissive

server: rapl.o client
	$(CC) $(CFLAGS) -pthread -o raplServer raplServer.cpp rapl.o -lm

client:
	$(CC) $(CFLAGS) -o raplClient raplClient.c

rapl.o: rapl.c rapl.h
	$(CC) -c $(CFLAGS) $< -lm

clean:
	rm -rf raplServer raplClient rapl.o
