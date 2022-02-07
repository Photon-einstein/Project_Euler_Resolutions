#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZE 200
#define MAX 100

/* faz vNum * nTeste, se vNum for uma potencia de nTeste^n então devolve nTeste^(n+1),
 num vector, que e o vNum*/
void potenciaVNum (int* vNum, int nTeste, int nDigits);

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector, e inverte os digitos*/
int *preencheVectorDigitEinverte (int contador, int dim, int nAlg, int nAlgMax);

/* soma os algarismos do numero nDigit e retorna o valor inteiro */
int somaDigit (int *nDigit, int nAlg);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int i, a, b, *nDigit, dim, nAlg, somaAlg, somaAlgMax = 0;

for (a = 2; a < MAX; a++) {
  dim = dimCalc (a, &nAlg);
  nDigit = preencheVectorDigitEinverte (a, dim, nAlg, SIZE);
  if (nDigit == NULL) {
    printf ("\nErro na criação do vector nDigit.");
  }

  for (b = 2; b < MAX; b++) {
    potenciaVNum (nDigit, a, SIZE);
    somaAlg = somaDigit (nDigit, SIZE);
    if (somaAlg > somaAlgMax) {
      somaAlgMax = somaAlg;
    }
  }
  free (nDigit);
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nA soma máxima de algarismos de a^b, com a,b < 100 é de %d.", somaAlgMax);
printf ("\n");
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

int *preencheVectorDigitEinverte (int contador, int dim, int nAlg, int nAlgMax) {
/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/

int *vectorDigit, *vectorDigitInvertido;
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

vectorDigitInvertido = (int*) calloc (nAlgMax, sizeof (int));
if (vectorDigitInvertido == NULL) {
  printf ("\nErro a criar o vector.");
  return NULL;
}

/* inverte digitos */
for (i = 0; i < nAlg; i++) {
  vectorDigitInvertido[i] = vectorDigit[nAlg-1-i];
}

free (vectorDigit);

return vectorDigitInvertido;
}

/******************************************************************************/

void potenciaVNum (int* vNum, int nTeste, int nDigits) {
/* faz vNum * nTeste, se vNum for uma potencia de nTeste^n então devolve nTeste^(n+1),
num vector, que e o vNum*/

int i, j, carry = 0;


carry = 0;
for (j = 0; j < nDigits; j++) {
  vNum[j] = vNum[j] * nTeste + carry;
  if (vNum[j] < 10) {
    carry = 0;
  } else {
    carry = vNum[j] / 10;
    vNum[j] = vNum[j] % 10;
  }
}

return;
}

/******************************************************************************/

int somaDigit (int *nDigit, int nAlg) {
/* soma os algarismos do numero nDigit e retorna o valor inteiro */

int i, soma = 0;

for (i = 0; i < nAlg; i++) {
  soma = soma + nDigit[i];
}

return soma;
}

/******************************************************************************/
