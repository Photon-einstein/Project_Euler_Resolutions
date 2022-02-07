#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZE 50001

/* gera dinamicamente uma matriz quadrada e retorna o apontador */
int** geraMatrizQuadrada (int dim);

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

/* liberta a memoria toda da matriz, e depois retorna */
void apagaMatriz (int **matriz, int dim);

/* preenche a matriz começando na linhaInicio e colunaInicio, x passos para a direita, comecando no actual */
/* retorna o proximo actual */
int preencheMatrizDireita (int **matriz, int linhaInicio, int colunaInicio, int passo, int actual);

/* preenche a matriz começando na linhaInicio e colunaInicio, x passos para a Cima, comecando no actual */
/* retorna o proximo actual */
int preencheMatrizCima (int **matriz, int linhaInicio, int colunaInicio, int passo, int actual);

/* preenche a matriz começando na linhaInicio e colunaInicio, x passos para a esquerda, comecando no actual */
/* retorna o proximo actual */
int preencheMatrizEsquerda (int **matriz, int linhaInicio, int colunaInicio, int passo, int actual);

/* preenche a matriz começando na linhaInicio e colunaInicio, x passos para a baixo, comecando no actual */
/* retorna o proximo actual */
int preencheMatrizBaixo (int **matriz, int linhaInicio, int colunaInicio, int passo, int actual);

/* calcula o racio de primos nas duas diagonais da matriz e devolve o float com o racio de primos */
float calculaRacioPrimos (int **matriz, int colunaInicio, int inicioDiagonalCima, int inicioDiagonalBaixo, int nColunas, int nNumeros, int *nPrimosAnterior);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int **matriz, i, j, passo = 1, linhaInicio, colunaInicio, contador = 1, actual = 1, centro, nPrimosAnterior = 0;
float racio = 1;

matriz = geraMatrizQuadrada (SIZE);
if (matriz == NULL) {
  printf ("\nFalha na criação da matriz quadrada.");
  return 0;
}

/* inicialização da matriz */
linhaInicio = SIZE/2 - 1;
centro = linhaInicio;
colunaInicio = linhaInicio;
matriz[linhaInicio] [linhaInicio] = actual;
colunaInicio++;
actual++;

while (1) {
  actual = preencheMatrizDireita (matriz, linhaInicio, colunaInicio, passo, actual);
  linhaInicio--;
  colunaInicio = colunaInicio + passo -1;
  /* testar aqui */
  if (passo > 1) {
    racio = calculaRacioPrimos (matriz, colunaInicio-contador, linhaInicio-contador+2, linhaInicio+1, contador, contador*2-1, &nPrimosAnterior);
    printf ("\nRacio matriz de %d elementos é de %f.", contador, racio);
    if (racio < 0.10) {
      break;
    }
  }
  actual = preencheMatrizCima (matriz, linhaInicio, colunaInicio, passo, actual);
  colunaInicio--;
  linhaInicio = linhaInicio - passo + 1;
  passo++;
  actual = preencheMatrizEsquerda (matriz, linhaInicio, colunaInicio, passo, actual);
  linhaInicio++;
  colunaInicio = colunaInicio - passo + 1;
  actual = preencheMatrizBaixo (matriz, linhaInicio, colunaInicio, passo, actual);
  linhaInicio = linhaInicio + passo - 1;
  colunaInicio++;
  passo++;

  if (matriz[SIZE-1][SIZE-1] != 0) {
    printf ("\nA matriz execedeu o seu tamanho.");

  }
  contador= contador + 2;

}
apagaMatriz (matriz, passo);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nO side lenght da matriz com racio menor que 0.10 e de %d.", passo);
printf ("\n");
return 0;
}

/******************************************************************************/

int ** geraMatrizQuadrada (int dim) {
/* gera dinamicamente uma matriz quadrada e retorna o apontador */

int **matriz, i;

matriz = (int **) calloc (dim, sizeof (int*));
if (matriz == NULL) {
  return NULL;
}

for (i = 0; i < dim; i++) {
  matriz[i] = (int*) calloc (dim, sizeof (int));
  if (matriz[i] == NULL) {
    return NULL;
  }
}
return matriz;
}

/******************************************************************************/

void apagaMatriz (int **matriz, int dim) {
/* liberta a memoria toda da matriz, e depois retorna */
int i;

for (i = 0; i < dim; i++) {
  free (matriz[i]);
}

free (matriz);
return;
}

/******************************************************************************/

int primeTeste (int nTeste) {
/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */

int i;

if (nTeste <= 1) {
	return 0;
}

if (nTeste  == 2) {
	return 1;
} else if (nTeste % 2 == 0) {
	return 0;
}

for (i = 3; i < sqrt(nTeste+1); i = i+2) {
	if (nTeste % i == 0) {
		return 0;
	}
}

/* se chega aqui é porque é um número primo */
return 1;
}

/******************************************************************************/

int preencheMatrizDireita (int **matriz, int linhaInicio, int colunaInicio, int passo, int actual) {
/* preenche a matriz começando na linhaInicio e colunaInicio, x passos para a direita, comecando no actual */
/* retorna o proximo actual */

int i;

for (i = 0; i < passo; i++) {
  matriz[linhaInicio][colunaInicio+i] = actual;
  actual++;
}

return actual;
}

/******************************************************************************/

int preencheMatrizCima (int **matriz, int linhaInicio, int colunaInicio, int passo, int actual) {
/* preenche a matriz começando na linhaInicio e colunaInicio, x passos para a Cima, comecando no actual */
/* retorna o proximo actual */

int i;

for (i = 0; i < passo; i++) {
  matriz[linhaInicio-i][colunaInicio] = actual;
  actual++;
}

return actual;
}

/******************************************************************************/

int preencheMatrizEsquerda (int **matriz, int linhaInicio, int colunaInicio, int passo, int actual) {
/* preenche a matriz começando na linhaInicio e colunaInicio, x passos para a esquerda, comecando no actual */
/* retorna o proximo actual */

int i;

for (i = 0; i < passo; i++) {
  matriz[linhaInicio][colunaInicio-i] = actual;
  actual++;
}

return actual;
}

/******************************************************************************/

int preencheMatrizBaixo (int **matriz, int linhaInicio, int colunaInicio, int passo, int actual) {
/* preenche a matriz começando na linhaInicio e colunaInicio, x passos para a baixo, comecando no actual */
/* retorna o proximo actual */

int i;

for (i = 0; i < passo; i++) {
  matriz[linhaInicio+i][colunaInicio] = actual;
  actual++;
}

return actual;
}

/******************************************************************************/

float calculaRacioPrimos (int **matriz, int colunaInicio, int inicioDiagonalCima, int inicioDiagonalBaixo, int nColunas, int nNumeros, int *nPrimosAnterior) {
/* calcula o racio de primos nas duas diagonais da matriz e devolve o float com o racio de primos */

int contadorPrimos = 0, booleano, i;
float racioPrimos;

  booleano = primeTeste (matriz[inicioDiagonalCima][colunaInicio]);
  if (booleano == 1) {
    contadorPrimos++;
  }
  booleano = primeTeste (matriz[inicioDiagonalCima+nColunas-1][colunaInicio+nColunas-1]);
  if (booleano == 1) {
    contadorPrimos++;
  }
  booleano = primeTeste (matriz[inicioDiagonalBaixo][colunaInicio]);
  if (booleano == 1) {
    contadorPrimos++;
  }
  booleano = primeTeste (matriz[inicioDiagonalBaixo-nColunas+1][colunaInicio+nColunas-1]);
  if (booleano == 1) {
    contadorPrimos++;
  }

*nPrimosAnterior = *nPrimosAnterior + contadorPrimos;

racioPrimos = ((float) *nPrimosAnterior) / nNumeros;
return racioPrimos;
}

/******************************************************************************/
