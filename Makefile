CC=gcc
CFLAGS=-Iinclude -Wall -g

default: main.o heap.o
	$(CC) $(CFLAGS) build/obj/main.o build/obj/heap.o -o heapsort

main.o:
	$(CC) $(CFLAGS) -c src/main.c -o build/obj/main.o

heap.o:
	$(CC) $(CFLAGS) -c src/heap.c -o build/obj/heap.o
