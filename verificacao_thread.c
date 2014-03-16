#include <pthread.h>
#include <stdio.h>
#include "verificacao.h"

char sudoku[9][9];

void* v_thread(void *v)
{
	int id = *(int *) v;
	int i, j, k, l;
	int flag = 0;
	i = id/9;
	j = id % 9;
	for(k = 0; k <9; k++)
	{
		if(i != k && sudoku[i][j] == sudoku[k][j])
		{
			flag = 1;
			//printf("[LINHA] LINHA %d, COLUNA %d",i,j);
			break;
		}
		
		if(j != k && sudoku[i][j] == sudoku[i][k])
		{
			flag = 1;
			//printf("[COLUNA] LINHA %d, COLUNA %d",i,j);
			break;
		}
		
	}
	
	for(k = (i/3) * 3; k < (i/3) * 3 + 3; k++)
	{
		for(l = (j/3) * 3; l < (j/3) * 3 + 3; l++)
		{
			if((i != k || j != l) && sudoku[i][j] == sudoku[k][l])
			{
				flag = 1;
				//printf("[BOX] LINHA %d, COLUNA %d com LINHA %d, COLUNA %d",i,j,k,l);
				break;
			}
		}
		if(flag > 0) break;
	}
	return (void*) flag;
}

int rodaVerificacao()
{
	int i, j;

	int flag_erro = 0;
	pthread_t thr[9][9];
	int id_thr[9][9];
	void *retorno[9][9];
		
	for(i = 0; i< 9; i++)
		for(j = 0; j< 9; j++)
		{
			scanf("%c ",&sudoku[i][j]);
		}
		
	for(i = 0; i< 9; i++)
		for(j = 0; j< 9; j++)
		{
			id_thr[i][j] = i*9 + j;
			pthread_create(&thr[i][j],NULL,v_thread,(void*) &id_thr[i][j]);
		}
		
	for(i = 0; i< 9; i++)
	{
		for(j = 0; j< 9; j++)
		{
			pthread_join(thr[i][j],&retorno[i][j]);
			if((int)retorno[i][j] == 1)
			{
				flag_erro = 1;
				break;
			}
		}
		if(flag_erro == 1) break;
	}
	
	if(flag_erro == 1)
		printf("Errado.");
	else
		printf("Correto.");
	
	return 0;
}

/*
EXEMPLO QUE FUNCIONA:
8 6 1 3 4 7 2 9 5
4 3 2 8 9 5 1 6 7
9 5 7 1 6 2 4 8 3
2 7 8 4 5 1 6 3 9 
5 4 9 6 8 3 7 2 1 
6 1 3 2 7 9 8 5 4
3 2 4 9 1 8 5 7 6
1 8 5 7 3 6 9 4 2
7 9 6 5 2 4 3 1 8

EXEMPLO QUE NÃO FUNCIONA:
8 6 1 3 4 7 2 9 5
4 3 2 8 9 5 1 6 7
9 5 9 1 6 2 4 8 3
2 7 8 4 5 1 6 3 9 
5 4 9 6 8 3 7 2 1 
6 1 3 2 7 9 8 5 4
3 2 4 9 1 8 5 7 6
1 8 5 7 3 6 9 4 2
7 9 6 5 2 4 3 1 8
*/
