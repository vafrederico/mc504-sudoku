CC=gcc
CFLAGS=-g -pthread
LDFLAGS=
SOURCES=main.c dica.c solucao.c verificacao_thread.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=sudoku

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@