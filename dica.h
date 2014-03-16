#include <stdio.h>
#include <pthread.h>

void imprime_dica();

void adicionaResposta(int x, int y, int v);

void* f_threadTestaNumero(void *v);

int testaNumero(int x, int y, int v);

void rodaDicas();