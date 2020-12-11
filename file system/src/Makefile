CC=gcc
OPTS=-g -std=c99 -Werror

all: main.o cache_size.o 
		$(CC) $(OPTS) -o cache main.o cache_size.o -lm

main.o: main.c cache_size.h
		$(CC) $(OPTS) -c main.c

cache_size.o: cache_size.h cache_size.c 
		$(CC) $(OPTS) -c cache_size.c

clean:
		rm -f *.o cache