#include <stdio.h>

int main()
{
	int i, j;
	char sudoku[9][9];
	int flag = 0;
	
	for(i = 0; i< 9; i++)
		for(j = 0; j< 9; j++)
		{
			scanf("%c ",&sudoku[i][j]);
		}
		
	for(i = 0; i< 9; i++)
	{
		for(j = 0; j< 9; j++)
		{
			int k, l;
			for(k = 0; k <9; k++)
			{
				if(i != k && sudoku[i][j] == sudoku[k][j])
				{
					flag = 1;
					printf("[LINHA] LINHA %d, COLUNA %d",i,j);
					break;
				}
				
				if(j != k && sudoku[i][j] == sudoku[i][k])
				{
					flag = 1;
					printf("[COLUNA] LINHA %d, COLUNA %d",i,j);
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
						printf("[BOX] LINHA %d, COLUNA %d com LINHA %d, COLUNA %d",i,j,k,l);
						break;
					}
				}
				if(flag > 0) break;
			}
			
			if(flag > 0) break;
		}
		if(flag > 0) break;
	}
	
	if(flag > 0)
		printf("NOPE.");
	else
		printf("YEP.");
}
