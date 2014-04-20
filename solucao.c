#include "solucao.h"
#include <stdio.h>
#include <pthread.h>

#define N_THR 10

typedef struct {
	char matriz[9][9];
	int x, y, id;
} Input;

char sudoku[9][9];
int flag_solucao;
int qtdThreads;

Input thrInput[N_THR];
pthread_t threadPool[N_THR];
int freeStack[N_THR];
int freeCount = 0;
volatile int interesse[N_THR]; 
volatile int ultimo[N_THR-1];

void* f_thread(void* p);

void addToStack(int i)
{
	freeStack[freeCount] = i;
	freeCount++;
}

int getFromStack()
{
	if(freeCount == 0)
	{
		//printf("Tem algo MUITO errado...");
		return -1;
	}
	freeCount--;
	qtdThreads++;
	return freeStack[freeCount];
}

int testaPossibilidade(char mat[9][9], int x, int y, int v)
{
	int i, j;
	v+= 48;
	for(i = 0; i< 9; i++)
	{
		if(mat[x][i] == v) return 0;
		if(mat[i][y] == v) return 0;
	}
	for(i = x/3 * 3; i< x/3 * 3 + 3; i++)
		for(j = y/3 * 3; j< y/3 * 3 + 3; j++)
			if(mat[i][j] == v) return 0;
			
	return 1;
}

void* backtrack_thread(int id)
{
	int i, flag, nextTry = -1;
	int x = thrInput[id].x;
	int y = thrInput[id].y;
	//imprime(thrInput[id].matriz);
	flag = 1;
	if(thrInput[id].matriz[x][y] == 'X')
	{
		flag = 0;
		for(i = 1; i<10; i++){
			if(testaPossibilidade(thrInput[id].matriz,x,y,i))
			{
				//printf("POSSIVEL: %d",i);
				/*a thread pega a primeira possibilidade para si mesma para diminuir a quantidade de threads
				e tenta passar as outras possibilidades para outras threads
				if(nextTry == -1)
				{
					nextTry = i;
					continue;
				}*/
				
				// !INICIO DA ZONA CRITICA!
				int f,k;
				for (f = 0; f < N_THR-1; f++) {
					interesse[id] = f;
					ultimo[f] = id; 
					for (k = 0; k < N_THR && ultimo[f] == id; k++)
					    if (k != id)
						   while (f <= interesse[k] && ultimo[f] == id);  
				}
				int next = getFromStack();
				interesse[id] = -1;
				// !FIM DA ZONA CRITICA!
				if(next != -1)
				{
					//printf("next:%d\n",next);
					memcpy(thrInput[next].matriz,thrInput[id].matriz, 81*sizeof(char));
					thrInput[next].matriz[x][y] = i+48;
					thrInput[next].id = next;
					
					if(x < 9)
					{
						thrInput[next].x = x+1;
						thrInput[next].y = y;
						pthread_create(&threadPool[next],NULL,f_thread,&thrInput[next]);
					}
					else if(y < 9)
					{
						thrInput[next].x = 0;
						thrInput[next].y = y+1;
						pthread_create(&threadPool[next],NULL,f_thread,&thrInput[next]);
					}
					else
					{
						printf("Solucao encontrada:\n");
						imprime(thrInput[id].matriz);
						flag_solucao = 1;
					}
				}
				else
				{
					thrInput[id].matriz[x][y] = i+48;
					if(x < 9)
					{
						thrInput[id].x = x+1;
						thrInput[id].y = y;
						backtrack_thread(id);
					}
					else if(y < 9)
					{
						thrInput[id].x = 0;
						thrInput[id].y = y+1;
						backtrack_thread(id);
					}
					else
					{
						printf("Solucao encontrada:\n");
						imprime(thrInput[id].matriz);
						flag_solucao = 1;
					}
					//thrInput[id].x = x;
					//thrInput[id].y = y;
					thrInput[id].matriz[x][y] = 'X';
				}
			}
		}
	}
	else{
		if(x < 9)
		{
			thrInput[id].x = x+1;
			thrInput[id].y = y;
			backtrack_thread(id);
		}
		else if(y < 9)
		{
			thrInput[id].x = 0;
			thrInput[id].y = y+1;
			backtrack_thread(id);
		}
		else
		{
			printf("Solucao encontrada:\n");
			imprime(thrInput[id].matriz);
			flag_solucao = 1;
		}
	}
	
	//pthread_exit((void*)flag);
	return flag;
}

void* f_thread(void* p)
{
	Input *inp = p;
	int id = inp->id;
	void *resp = backtrack_thread(id);
	
	// !INICIO DA ZONA CRITICA!
	int f,k;
	for (f = 0; f < N_THR-1; f++) {
		interesse[id] = f;
		ultimo[f] = id; 
		for (k = 0; k < N_THR && ultimo[f] == id; k++)
			if (k != id)
			   while (f <= interesse[k] && ultimo[f] == id);  
	}
	addToStack(inp->id);
	interesse[id] = -1;
	// !FIM DA ZONA CRITICA!
	pthread_exit(0);	
	return (void*)	55;
}

void imprime(char mat[9][9]){
	int i, j;
	for(i=0; i<9; i++){
		if(i%3 == 0)
			printf("--------------------------\n");
		for(j=0; j<9; j++){
			if(j%3 == 0)
				printf(" |");
			printf(" %c", mat[i][j]);
		}
		printf(" |\n");
	}
	printf("--------------------------\n\n");
	return;
}

int rodaSolucao()
{
	int i, j, first;
	int retorno;
	Input teste;
	qtdThreads = 0;
	
	for(i = 0; i<N_THR; i++)
	{
		addToStack(i);
		interesse[i] = -1;
	}

	first = getFromStack();
	
	for(i = 0; i< 9; i++)
			for(j = 0; j< 9; j++)
				scanf("%c ",&thrInput[first].matriz[i][j]);
	
	thrInput[first].x = 0;
	thrInput[first].y = 0;
	thrInput[first].id = first;
	
	pthread_create(&threadPool[first],NULL,f_thread,&thrInput[first]);
	while(freeCount < N_THR);
	//	printf("|%d|",freeCount);
	
	//printf("total:%d",qtdThreads);
	
	if(flag_solucao == 0)
		printf("Sudoku invalido.\n");
	
	return 0;
}