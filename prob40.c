#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/
int *preencheVectorDigit (int contador, int dim, int nAlg);

/* preenche vector, desde passo, nAlg, com os digitos de vectorAlgContador,
devolve 0 se ainda não tiver chegado a 1000000-1 ou 1 se sim */
int preencheVector (int *vector, int passo, int nAlg, int *vectorAlgContador);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */

int vector[1000006] = {0};
int booleano = 0;
int contador = 1;
int dim, nAlg, score;
int passo = 0;
int *vectorAlgContador;


while (booleano == 0) {
  dim = dimCalc (contador, &nAlg);
  vectorAlgContador = preencheVectorDigit (contador, dim, nAlg);
  if (vectorAlgContador == NULL) {
    return 0;
  }
  booleano = preencheVector (vector, passo, nAlg, vectorAlgContador);
  passo = passo + nAlg;
  contador++;
}

score = vector[0]*vector[9]*vector[99]*vector[999]*vector[10000-1]*vector[100000-1]*vector[1000000-1];
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nSolução = %d\n", score);
return 0;
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

int preencheVector (int *vector, int passo, int nAlg, int *vectorAlgContador) {
/* preenche vector, desde passo, nAlg, com os digitos de vectorAlgContador,
devolve 0 se ainda não tiver chegado a 1000000-1 ou 1 se sim */

int i;

for (i = 0; i < nAlg; i++) {
  vector[passo+i] = vectorAlgContador[i];
  if ((passo+i) == 1000000) {
    return 1;
  }
}

return 0;
}

/******************************************************************************/
