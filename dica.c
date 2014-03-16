#include "dica.h"
#include <stdio.h>
#include <pthread.h>

char tabuleiro[9][9];
char respostas[9][9][9];

/*Funcao que imprime a matriz 9x9 que armazena o jogo de Sudoku (opcionalmente a matriz pode ser global e nao passada por parametro)*/
void imprime_dica(){
	int i, j, k;
	for(i=0; i<9; i++){
		if(i%3 == 0)
			printf("--------------------------\n");
		for(j=0; j<9; j++){
			if(j%3 == 0)
				printf(" |");

			if (tabuleiro[i][j] == 'X'){

				printf( " (");

				for(k = 0; k < 9; k++)
					if(respostas[i][j][k] != 'X')
						printf(" %c", respostas[i][j][k]);
				printf(")");

			} else {

				printf(" %c", tabuleiro[i][j]);

			}

		}
		printf(" |\n");
	}
	printf("--------------------------\n");
	return;
}

/*======================================

 	LEMBRAR: 
	X => LINHA; Y => COLUNA

======================================*/

void adicionaResposta(int x, int y, int v){
	int i;

	for(i = 0; i <9; i++){

		if (respostas[x][y][i] == 'X'){
			respostas[x][y][i] = v+48;
			return;
		}
	}
}


void* f_threadTestaNumero(void *v) {
  	
  	int id = (int) v;
   	int x = id/9;
  	int y = id%9;

  	int z;
  	
  	for(z = 1; z <= 9; z++){
  		//printf("Thread X, Y: %d %d %d\n", x, y, z);

		if(testaNumero(x, y, z))
			adicionaResposta(x, y, z);
  	}

  return NULL;
}


int testaNumero(int x, int y, int v){

	int i,j;
	int inicioX, fimX, inicioY, fimY;


	for(i = 0; i < 9; i++){ // Checa se o elemento esta na linha

		if(tabuleiro[x][i] == v+48)
			return 0;

	}

	for(i = 0; i < 9; i++){ // Checa se o elemento esta na coluna

		if(tabuleiro[i][y] == v+48)
			return 0;

	}

	inicioX = x/3 * 3;
	fimX = inicioX + 3;
	
	inicioY = y/3 * 3;
	fimY = inicioY + 3;
	
	for(i = inicioX; i <= fimX; i++){

		for(j = inicioY; j <= fimY; j++){

			if(tabuleiro[i][j] == v+48){
				return 0;
			}

		}

	}

	return 1;

}


void rodaDicas(){

	int i,j, v, count=0, id;

	printf ("Digite a matriz com o sudoku:\n");
  	pthread_t thr[81];
  	// Inicializa o tabuleiro
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9;j++){
			scanf("%c ", &tabuleiro[i][j]);

			for(v = 0; v < 9; v++)
				respostas[i][j][v] = 'X';
		}
	}

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9;j++){
			if(tabuleiro[i][j] == 'X'){
				id = (i*9+j);
				if(pthread_create(&thr[count], NULL, f_threadTestaNumero, (void *) id)){
			 	    printf("Erro na criacao da thread. \n");
		 	   	} else {
		 	   		count++;
		 	   	}
			}
		}
	}

	for(i = 0; i < count; i++){
		pthread_join(thr[i], NULL);
	}

	imprime_dica();

}