CC=gcc
CFLAGS=-Iinclude -Wall -g

default: main.o heap.o
	$(CC) $(CFLAGS) main.o heap.o -o heapsort
	rm main.o heap.o

main.o:
	$(CC) $(CFLAGS) -c src/main.c -o main.o

heap.o:
	$(CC) $(CFLAGS) -c src/heap.c -o heap.o
