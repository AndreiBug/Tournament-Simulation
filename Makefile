CC = gcc
CFLAGS = -Wall -Wextra -g

all: build

build: main.o
	$(CC) $(CFLAGS) main.o -o lanParty

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main.o lanParty
