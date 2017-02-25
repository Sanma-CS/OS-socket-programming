CC = gcc

all: server client

server: lib/libserver.h lib/libserver.c src/server.c
	$(CC) lib/libserver.h lib/libserver.c src/server.c -o bin/server.o
	
client: lib/libclient.h lib/libclient.c src/client.c
	$(CC) lib/libclient.h lib/libclient.c src/client.c -o bin/client.o
	