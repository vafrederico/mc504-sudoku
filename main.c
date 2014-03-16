#include <stdio.h>
#include "./dica.h"
#include "./solucao.h"
#include "./verificacao.h"

int main(int argc, char const *argv[])
{
	
	int o;
	printf("Menu:\n1. Verificacao\n2. Dicas\n3. Resolucao\n4. Sair\nDigite sua opcao:");
	
	while(scanf("%d", &o ) && o != 4){
		scanf("\n");
		switch(o){

			case 1:
				rodaVerificacao();
				break;
			case 2:
				rodaDicas();
				break;
			case 3:
				rodaSolucao();
				break;
			case 4:
				return 0;
				break;
			default:
				break;
		}

		printf("Menu:\n1. Verificacao\n2. Dicas\n3. Resolucao\n4. Sair\nDigite sua opcao:");
		
	}
	return 0;
}