#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 4000

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector, e inverte os digitos*/
int *preencheVectorDigitEinverte (int contador, int dim, int nAlg, int nAlgMax);

/* soma o numero vNum, nTeste vezes e retorna à funcação principal */
int* somaVNum (int* vNum, int nTeste, int nDigits);

/* soma vNum a vSoma, com nDigits */
int* somaVSomaComVNum (int *vSoma, int *vNum, int nDigits, int nAlg);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
int nTeste, indiceP, dim, nAlg, nAlgMax, i;
int *vNum, *vSoma;

vSoma = (int*) calloc (DIM, sizeof (int));
if (vSoma == NULL) {
  printf ("\nErro na alocação de memória.");
  return 0;
}

for (nTeste = 1; nTeste < 1000; nTeste++) {
  indiceP = 1;

  dim = dimCalc (nTeste, &nAlg);

  if (nTeste < 11) {
    nAlgMax = 15;
  } else if (nTeste < 100) {
    nAlgMax = 201;
  } else if (nTeste < 200) {
    nAlgMax = 461;
  } else if (nTeste < 300) {
    nAlgMax = 744;
  } else if (nTeste < 400) {
    nAlgMax = 1042;
  } else if (nTeste < 500) {
    nAlgMax = 1400;
  } else if (nTeste < 600) {
    nAlgMax = 1667;
  } else if (nTeste < 700) {
    nAlgMax = 1992;
  } else if (nTeste < 800) {
    nAlgMax = 2325;
  } else if (nTeste < 900) {
    nAlgMax = 2661;
  } else {
    nAlgMax = 3000;
  }

  vNum = preencheVectorDigitEinverte (nTeste, dim, nAlg, nAlgMax);

  if (vNum == NULL) {
    printf ("\nErro na alocação de memória.");
    return 0;
  }

  /* agora vou calcula a potencia n^n */
  for (indiceP = 1; indiceP < nTeste; indiceP++) {
    vNum = somaVNum (vNum, nTeste, nAlgMax);
  }

  /* agora vou somar vNum a vSoma */
    vSoma = somaVSomaComVNum (vSoma, vNum, DIM, nAlgMax);
    free (vNum);
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nNúmero igual a: ");
for (i = 9; i > -1; i--) {
  printf ("%d", vSoma[i]);
}
printf ("\n");
free (vSoma);
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

int* somaVNum (int* vNum, int nTeste, int nDigits) {
/* devolve o novo nAlg, soma o numero vNum, nTeste vezes e retorna à função principal */

int i, j, carry = 0;


  carry = 0;
  for (j = 0; j < nDigits; j++) {
    vNum[j] = vNum[j] * nTeste + carry;
    if (vNum[j] < 10) {
      carry = 0;
    } else {
      carry = vNum[j] / 10;
      vNum[j] = vNum[j] - carry*10;
    }
  }

return vNum;
}

/******************************************************************************/

int* somaVSomaComVNum (int *vSoma, int *vNum, int nDigits, int nAlg) {
/*  soma vNum a vSoma, com nDigits */

int j, carry = 0;

for (j = 0; j < nAlg; j++) {
  vSoma[j] = vSoma[j] + vNum[j] + carry;
  if (vSoma[j] < 10) {
    carry = 0;
  } else {
    carry = vSoma[j] / 10;
    vSoma[j] = vSoma[j] % 10;
  }
}

carry = 0;

for (j = nAlg; j < nDigits; j++) {

  if (vSoma[j] > 9) {
    vSoma[j+1] = vSoma[j] / 10;
    vSoma[j] = vSoma[j] % 10;
  }
}


return vSoma;
}

/******************************************************************************/
