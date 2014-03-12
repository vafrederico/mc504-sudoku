CC = gcc
CFLAGS = -g -pthread

PROGRAMS = sudoku

all: $(PROGRAMS)

sudoku: verificacao_thread.o dica.o

dica.o: dica.h

clean:
	rm -f *~ *.o $(PROGRAMS)