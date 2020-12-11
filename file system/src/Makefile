CC=gcc
OPTS=-g -std=c99 -Werror

all: cache_size.o 
		$(CC) $(OPTS) -o cache_size cache_size.o -lm

cache_size.o: cache_size.c 
		$(CC) $(OPTS) -c cache_size.c

clean:
		rm -f *.o cache_size