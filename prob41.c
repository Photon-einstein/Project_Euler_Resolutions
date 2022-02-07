#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define START 7654321

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/
int *preencheVectorDigit (int contador, int dim, int nAlg);

/* confirma se este conjunto de n digitos são de facto um numero Pandigital de 1 a N,
retorna 1 se sim ou 0 se não */
int pandigitalCheck (int *vector, int nAlg);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */

int nTeste, booleano, dim, nAlg;
int *vectorDigit;
int maxNumber = 0;

for (nTeste = START; nTeste > 1; nTeste --) {
	/* se chega aqui é porque se trata de um número primo*/
	dim = dimCalc (nTeste, &nAlg);
	vectorDigit = preencheVectorDigit (nTeste, dim, nAlg);

	if (vectorDigit == NULL) {
		printf ("\nErro na criação de um vectorDigit.");
		return 0;
	}
	/* confirma se este conjunto de n digitos são de facto um numero Pandigital de 1 a N,
	retorna 1 se sim ou 0 se não */

	booleano = pandigitalCheck (vectorDigit, nAlg);
	if (booleano == 0) {
		free (vectorDigit);
		continue;
	}

	booleano = primeTeste (nTeste);
	if (booleano == 0) {
		/* neste caso não se trata de um número primo */
		/* avança para um novo número sem fazer mais nada para baixo */
		continue;
	}

	/* se chega aqui e porque e primo e pandigital */
	maxNumber = nTeste;
	free (vectorDigit);
	break;
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nO número Pandigital máximo é o %d.\n", maxNumber);
return 0;
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

int dimCalc (int contador, int *nAlg) {
/* calcula dim do contador e devolve também o nAlg do contador */

int dim = 1;
int res, nAlgarismos = 1;

res = contador / dim;

while (res > 9) {
  dim = dim * 10;
  nAlgarismos++;
  res = contador / dim;
}

*nAlg = nAlgarismos;
return dim;
}

/******************************************************************************/

int *preencheVectorDigit (int contador, int dim, int nAlg) {
/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/

int *vectorDigit;
int i;

vectorDigit = (int*) calloc (nAlg, sizeof (int));
if (vectorDigit == NULL) {
  printf ("\nErro a criar o vector.");
  return NULL;
}

for (i = 0; i < nAlg; i++) {
  vectorDigit[i] = contador / dim;
  contador = contador - vectorDigit[i]*dim;
  dim = dim / 10;
}

return vectorDigit;

}

/******************************************************************************/

int pandigitalCheck (int *vector, int nAlg) {
/* confirma se este conjunto de 9 digitos são de facto um numero Pandigital,
retorna 1 se sim ou 0 se não */

int *vectorCheck;
int i, j;

vectorCheck = (int*) calloc (nAlg, sizeof (int));
if (vectorCheck == NULL) {
  printf ("\nFalha na alocação de memória do vector check.");
  return 0;
}

/*preenchimento do vector check*/
for (i = 0; i < nAlg; i++) {
  vectorCheck [i] = i+1;
}

/*check a ver se existem todos os numeros de 1 a 9 */
for (i = 0; i < nAlg; i++) {
  for (j = 0; j < nAlg; j++) {
    if (vector[i] == vectorCheck[j]) {
      vectorCheck[j] = -1;
    }
  }
}

for (i = 0; i < nAlg; i++) {
  if (vectorCheck[i] != -1) {
    free(vectorCheck);
    return 0;
  }
}

/* se chega aqui e porque é nPandigital*/
free(vectorCheck);
return 1;
}

/******************************************************************************/
