#include "dica.h"
#include <pthread.h>

int tabuleiro[9][9];
int respostas[9][9][9];
	
/*Funcao que imprime a matriz 9x9 que armazena o jogo de Sudoku (opcionalmente a matriz pode ser global e nao passada por parametro)*/
void imprime(){
	int i, j, k;
	for(i=0; i<9; i++){
		if(i%3 == 0)
			printf("--------------------------\n");
		for(j=0; j<9; j++){
			if(j%3 == 0)
				printf(" |");

			if (tabuleiro[i][j] == 0){
				
				printf( " (");

				for(k = 0; k < 9; k++)
					if(respostas[i][j][k] != -1)
						printf(" %d", respostas[i][j][k]);
				printf(")");

			} else {

				printf(" %d", tabuleiro[i][j]);

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

		if (respostas[x][y][i] == -1){
			respostas[x][y][i] = v;
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


	for(i = 0; i <= 8; i++){ // Checa se o elemento esta na linha

		if(tabuleiro[x][i] == v)
			return 0;

	}

	for(i = 0; i <= 8; i++){ // Checa se o elemento esta na coluna

		if(tabuleiro[i][y] == v)
			return 0;

	}
	
	// Primeira linha de bloco
	if(x <= 2){

		inicioX = 0;
		fimX = 2;
		
	} else if(x <= 5) { // Segunda linha de bloco

		inicioX = 3;
		fimX = 5;

	} else { // Terceira linha de bloco

		inicioX = 6;
		fimX = 8;

	}
	
	// Primeira coluna de bloco
	if(y <= 2){

		inicioY = 0;
		fimY = 2;
		
	} else if(y <= 5) { // Segunda coluna de bloco

		inicioY = 3;
		fimY = 5;

	} else { // Terceira coluna de bloco

		inicioY = 6;
		fimY = 8;

	}

	for(i = inicioX; i <= fimX; i++){

		for(j = inicioY; j <= fimY; j++){

			if(tabuleiro[i][j] == v){
				return 0;
			}

		}

	}

	return 1;

}


void rodaDicas(){

	int i,j, v, count=0, id;

	printf ("Digite a matriz com o sudoku abaixo, usar 0 para campos vazios ao inves de X:\n");
  	pthread_t thr[81];
  	// Inicializa o tabuleiro
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9;j++){
			scanf("%d", &tabuleiro[i][j]);

			for(v = 0; v < 9; v++)
				respostas[i][j][v] = -1;
		}
	}

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9;j++){
			if(tabuleiro[i][j] == 0){
				id = (i*9+j);
				if(pthread_create(&thr[count], NULL, f_threadTestaNumero, (void *) id)){
			 	    fprintf(stderr, "Erro na criação da thread. \n");
		 	   	} else {
		 	   		count++;
		 	   	}
			}
		}
	}

	for(i = 0; i < count; i++){
		pthread_join(thr[i], NULL);
	}

	imprime();

}
