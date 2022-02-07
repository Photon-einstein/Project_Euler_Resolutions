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

/* esta função retorna 1 se os 2 vectores tiverem os mesmos digitos ou 0 se não */
int testaIgualdadeDigitos (int *vDigit1, int *vDigit2, int nAlg);

/* retorna 1 se os digitos tiverem os mesmos algarismos ou 0 se não */
int booleanotestaIgualdadeDigitos (int *vDigit1, int numero2, int dim1, int nAlg);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
int nTeste = 9, n2, n3, n4, n5, n6, found = 0, *vDigit;
int dim, nAlg, booleano = 0, *vDigit2, dim2;


while (1) {
  nTeste++;
  n2 = nTeste * 2;
  n3 = nTeste * 3;
  n4 = nTeste * 4;
  n5 = nTeste * 5;
  n6 = nTeste * 6;

  dim = dimCalc (nTeste, &nAlg);
  vDigit = preencheVectorDigit (nTeste, dim, nAlg);

  /* teste 2x */
  booleano = booleanotestaIgualdadeDigitos (vDigit, n2, dim, nAlg);
  if (booleano == 0) {
    free (vDigit);
    continue;
  }
  /* teste 3x */
  booleano = booleanotestaIgualdadeDigitos (vDigit, n3, dim, nAlg);
  if (booleano == 0) {
    free (vDigit);
    continue;
  }
  /* teste 4x */
  booleano = booleanotestaIgualdadeDigitos (vDigit, n4, dim, nAlg);
  if (booleano == 0) {
    free (vDigit);
    continue;
  }
  /* teste 5x */
  booleano = booleanotestaIgualdadeDigitos (vDigit, n5, dim, nAlg);
  if (booleano == 0) {
    free (vDigit);
    continue;
  }
  /* teste 6x */
  booleano = booleanotestaIgualdadeDigitos (vDigit, n6, dim, nAlg);
  if (booleano == 0) {
    free (vDigit);
    continue;
  }
  /* se chega aqui e porque os digitos são iguais para todos os numeros */
  break;
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nO menor número positivo é o %d nestas condições.", nTeste);
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

int testaIgualdadeDigitos (int *primo1, int *primo2, int nAlg) {
/* esta função retorna 1 se os 2 vectores tiverem os mesmos digitos ou 0 se não */

int i, j;
int *vectorBooleano;

vectorBooleano = (int*) calloc (nAlg, sizeof (int));
if (vectorBooleano == NULL) {
  printf ("\nOcorreu um erro na criação do vector.");
  return 0;
}

for (i = 0; i < nAlg; i++) {
  vectorBooleano[i] = primo2[i];
}

for (i = 0; i < nAlg; i++) {
  for (j = 0; j < nAlg; j++) {
    if (primo1[i] == vectorBooleano[j]) {
      vectorBooleano[j] = -1;
      break;
    }
  }
}

for (i = 0; i < nAlg; i++) {
  if (vectorBooleano[i] != -1) {
    free (vectorBooleano);
    return 0;
  }
}
free (vectorBooleano);

/* se chega aqui é porque os digitos são iguais */
return 1;
}

/******************************************************************************/

int booleanotestaIgualdadeDigitos (int *vDigit1, int numero2, int dim1, int nAlg) {
/* retorna 1 se os digitos tiverem os mesmos algarismos ou 0 se não */

int dim2, booleano, nAlg2, *vDigit2;

dim2 = dimCalc (numero2, &nAlg2);

if (dim2 != dim1 || nAlg != nAlg2) {
  return 0;
}

vDigit2 = preencheVectorDigit (numero2, dim2, nAlg2);
booleano = testaIgualdadeDigitos (vDigit1, vDigit2, nAlg);
free (vDigit2);

return booleano;
}

/******************************************************************************/
