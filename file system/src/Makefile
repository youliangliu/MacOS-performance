CC=gcc
OPTS=-g -std=c99 -Werror

all: main.o cache_size.o local_read.o
		$(CC) $(OPTS) -o cache main.o cache_size.o local_read.o -lm

main.o: main.c cache_size.h local_read.h
		$(CC) $(OPTS) -c main.c

cache_size.o: cache_size.h cache_size.c 
		$(CC) $(OPTS) -c cache_size.c

local_read.o: local_read.h local_read.c
		$(CC) $(OPTS) -c local_read.c

clean:
		rm -f *.o cache