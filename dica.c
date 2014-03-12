#include <stdio.h>
int respostas[9][9][9];
	
/*Funcao que imprime a matriz 9x9 que armazena o jogo de Sudoku (opcionalmente a matriz pode ser global e nao passada por parametro)*/
void imprime(int tabuleiro[9][9]){
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

// Checa se o numero esta no bloco definido por X = [inicioX,fimX] e Y = [inicioY,fimY]
int testaNumero(int matriz[9][9], int x, int y, int v){

	int i,j;
	int inicioX, fimX, inicioY, fimY;


	for(i = 0; i <= 8; i++){ // Checa se o elemento esta na linha

		if(matriz[x][i] == v)
			return 0;

	}

	for(i = 0; i <= 8; i++){ // Checa se o elemento esta na coluna

		if(matriz[i][y] == v)
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

			if(matriz[i][j] == v){
				return 0;
			}

		}

	}

	return 1;

}


void rodaDicas(){

	int i,j, v;

	int tabuleiro[9][9];
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
			if(tabuleiro[i][j] == 0)
				for(v = 1; v <= 9; v++)
					if(testaNumero(tabuleiro, i, j, v))
						adicionaResposta(i, j, v);
		}
	}

	imprime(tabuleiro);
}

int main(){

	rodaDicas();

	return 0;
}