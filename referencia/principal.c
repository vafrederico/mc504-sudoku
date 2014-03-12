#include <stdio.h>

/*Funcao que imprime a matriz 9x9 que armazena o jogo de Sudoku (opcionalmente a matriz pode ser global e nao passada por parametro)*/
void imprime(int mat[9][9]){
	int i, j;
	for(i=0; i<9; i++){
		if(i%3 == 0)
			printf("--------------------------\n");
		for(j=0; j<9; j++){
			if(j%3 == 0)
				printf(" |");
			printf(" %d", mat[i][j]);
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

// Checa se o numero esta no bloco definido por X = [inicioX,fimX] e Y = [inicioY,fimY]
int checaNumeroBloco(int matriz[9][9], int inicioX, int fimX, int inicioY, int fimY, int v){

	int i,j;

	for(i = inicioX; i <= fimX; i++){

		for(j = inicioY; j <= fimY; j++){

			if(matriz[i][j] == v){
				return 0;
			}

		}

	}

	return 1;

}

// Testa se é possivel adicionar v na posicao (x,y), caso possivel o faz, senão retorna 0
int insereNumero(int matriz[9][9], int x, int y, int v){
	
	int inicioX, fimX, inicioY, fimY;

	int i;
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

	if(checaNumeroBloco(matriz, inicioX, fimX, inicioY, fimY, v)){

		// Se for um número válido, colocamos o valor
		matriz[x][y] = v;

		//imprime(matriz);

		return 1;

	}

	return 0;

}

int rodaPosicao(int matriz[9][9], int x, int y){

	// Existe numero na posicao?
	if(matriz[x][y] != 0){

		// Final?
		if(x == 8 && y == 8)
			return 1;

		// Nao esta no fim da coluna
		else if (x < 8)
			return rodaPosicao(matriz, x + 1, y); // Roda a linha abaixo

		// Esta no fim da coluna
		else
			return rodaPosicao(matriz, 0, y + 1); // Roda a proxima coluna


	} else {

		int i;

		for(i = 1; i <= 9; i++){ // Pra cada valor

			 // Valor valido? Se sim, roda a proxima posicao, se nao conseguir resposta, testa proximo valor
			if(insereNumero(matriz, x, y, i))
			{

				// Nao esta no fim da coluna
				if (x < 8){
					if(rodaPosicao(matriz, x + 1, y)) return 1; // Roda a linha abaixo
				}

				// Esta no fim da coluna
				else if (y < 8){
					if (rodaPosicao(matriz, 0, y + 1)) return 1; // Roda a proxima coluna
			
				} 
				// Final
				else
					return 1;

			}

		}
		
		// Nao houve valor válido com a matriz atual, retroceder, alterar o valor para testar novamente
		matriz[x][y] = 0;		
		return 0;

	}

}

int sudoku(int tabuleiro[9][9]){

	int i,j;
	int x, y, v, n;

	// Inicializa o tabuleiro
	for(i = 0; i < 9; i++)
		for(j = 0; j < 9;j++)
			scanf("%d", &tabuleiro[i][j]);

	//imprime(tabuleiro);

	// Comeca a processar, se a posicao 0,0 nao tiver nenhum valor valido, o sudoku nao possui solucao
	return rodaPosicao(tabuleiro, 0, 0);

}

int main(){

	int matriz[9][9];
	
	if(sudoku(matriz)) // Ha solucao?
		imprime(matriz);

	else
		printf("Sem solucao\n");

	return 0;
}