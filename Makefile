# slsolve makefile
CC=gcc
CFLAGS=-lm#-Wall -Werror "
BINS=slsolve
SRCS=$(wildcard *.c)

all: $(BINS)

slsolve: main.o tests.o mat.o
	$(CC) $(CFLAGS) -o slsolve $^

main.o: main.c sl_solver.h sl_mat.h
	$(CC) $(CFLAGS) -c $^

tests.o: tests.c sl_solver.h sl_mat.h
	$(CC) $(CFLAGS) -c $^

mat.o: mat.c sl_mat.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(BINS) *.o
