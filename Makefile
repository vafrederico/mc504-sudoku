CC = gcc
CFLAGS = -g -pthread

PROGRAMS = sudoku

all: $(PROGRAMS)

sudoku: verificacao_thread.o dica.o solucao.o

dica.o: dica.h

solucao.o: solucao.h

clean:
	rm -f *~ *.o $(PROGRAMS)