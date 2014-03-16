#include<stdio.h>
#include<pthread.h>

#define N_THR 100

void addToStack(int i);
int getFromStack();
int testaPossibilidade(char sudoku[9][9], int x, int y, int v);
void* backtrack_thread(int id);
void* f_thread(void* p);
void imprime(char mat[9][9]);
int rodaSolucao();