mc504-sudoku
============
Grupo:
Gustavo de Mello Crivelli  - RA 136008
Vinicius Andrade Frederico - RA 139223

Instruções de uso:
Rode o Makefile para gerar o executável sudoku.
Uma vez dentro do programa, escolha dentre as opções disponíveis:

1. Verificação de Sudoku
- Use para verificar se um diagrama completo de sudoku é válido ou não.
- Basta digitar a matriz conforme pedido.

2. Dicas de Sudoku
- Digite um diagrama de sudoku, com X nas casas vazias. 
- O programa imprimirá todas as possibilidades para cada uma das casas vazias.

3. Solução de Sudoku
- Digite um diagrama de sudoku, com X nas casas vazias. 
- O programa imprimirá todas as soluções possíveis para aquele diagrama.
- Caso não haja soluções possíveis, o programa imprimirá "Sudoku inválido".

4. Sair
- Fecha o programa.


Estratégias utilizadas:
Para a verificação, é criada uma thread por casa do diagrama, resultando em 81 threads
que checam a validade de cada valor simultaneamente. Como não há escrita de dados, não
existem problemas com o acesso de variáveis ao mesmo tempo. 

Para a criação de dicas, é preciso verificar as possibilidades para cada casa com um X.
A estratégia é a mesma da verificação: uma thread por casa com X. Baixo custo, alta 
eficiência.

Para a criação de sudokus:
Com backtracking (e thread única), o programa gasta mais tempo porém consome pouca memória.
Sem backtracking (e threads múltiplas), o programa é rápido porém consome MUITA memória,
visto que precisa criar uma cópia da matriz do sudoku para cada thread.
A estratégia utilizada é um misto das duas coisas: Estabelecemos um teto para a quantidade de threads,
de modo que o programa tentará criar novas threads até atingir 100 delas, ponto no qual as threads
passarão a se comportar como um backtracking simples (em cada uma delas, um backtrack).
Para reduzir o custo de memória, criou-se também uma pool de threads, de onde elas são retiradas ao se
criar uma nova thread, e devolvidas quando essa thread morre (termina o seu caminho no backtrack).
No entanto, a inserção e remoção de threads na pool é uma operação crítica. Usamos então um
algoritmo de desempate para garantir que apenas uma thread acesse a pool por vez.
Desta forma, temos um programa mais eficiente que o backtrack simples, que gasta menos memória
do que a abordagem apenas com threads, e que ainda consegue apontar múltiplas soluções.