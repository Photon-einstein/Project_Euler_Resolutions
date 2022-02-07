#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZE 1000

/* inicializa os valores para começar o programa, e retorna */
void inicializacaoDosValores (int *dN, int *dNmenos1, int *numN, int *numNmenos1);

/* gera dinamicamente um vector dNmais1, de dimensao dim, e recebe o resultado
de: d(n+1) = 2*d(n) + 1* d(n-1) */
int* calculaNmais1 (int *dN, int *dNmenos1, int dim);

/* retorna 1 se numerador tem mais digitos que denominador ou 0 se não */
int testaNumeradorComMaisDigitos (int *dNmais1, int *numNmais1, int dim);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int *dNmais1, *dN, *dNmenos1,*numNmais1, *numN, *numNmenos1;
int booleano, expansoes, contador = 0;

dNmais1 = calloc (SIZE, sizeof (int));
dN = calloc (SIZE, sizeof (int));
dNmenos1 = calloc (SIZE, sizeof (int));
numNmais1 = calloc (SIZE, sizeof (int));
numN = calloc (SIZE, sizeof (int));
numNmenos1 = calloc (SIZE, sizeof (int));

inicializacaoDosValores (dN, dNmenos1, numN, numNmenos1);

for (expansoes = 2; expansoes < 1001; expansoes++) {
  dNmais1 = calculaNmais1 (dN, dNmenos1, SIZE);
  numNmais1 = calculaNmais1 (numN, numNmenos1, SIZE);
  booleano = testaNumeradorComMaisDigitos (dNmais1, numNmais1, SIZE);
  if (booleano == 1) {
    contador++;
  }

  free (dNmenos1);
  free (numNmenos1);
  /* reciclagem de apontadores de denominador */
  dNmenos1 = dN;
  dN = dNmais1;
  /* reciclagem de apontadores de numerador */
  numNmenos1 = numN;
  numN = numNmais1;
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nNúmero de vezes que numerador com mais digitos que denuminador = %d", contador);
printf ("\n");
return 0;
}

/******************************************************************************/

void inicializacaoDosValores (int *dN, int *dNmenos1, int *numN, int *numNmenos1) {
/* inicializa os valores para começar o programa, e retorna */

/* numerador */
numN[0] = 7;
numNmenos1[0] = 3;

/* denominador */
dN[0] = 5;
dNmenos1[0] = 2;
return;
}

/******************************************************************************/

int* calculaNmais1 (int *dN, int *dNmenos1, int dim) {
/* gera dinamicamente um vector dNmais1, de dimensao dim, e recebe o resultado
de: d(n+1) = 2*d(n) + 1* d(n-1) */

int i, carry = 0, *nMais1;

nMais1 = (int*) calloc (dim, sizeof (int));
if (nMais1 == NULL) {
  printf ("\nErro na criação do vector dinâmico.");
  return 0;
}

for (i = 0; i < dim; i++) {
  nMais1[i] = carry + 2*dN[i] + dNmenos1[i];
  if (nMais1[i] > 9) {
    carry = nMais1[i] / 10;
    nMais1[i] = nMais1[i] % 10;
  } else {
    carry = 0;
  }
}

return nMais1;
}

/******************************************************************************/

int testaNumeradorComMaisDigitos (int *dNmais1, int *numNmais1, int dim) {
/* retorna 1 se numerador tem mais digitos que denominador ou 0 se não */

int i;

for (i = dim-1; i > -1; i--) {
  if (dNmais1[i] != 0) {
    return 0;
  } else if (numNmais1[i] != 0) {
    return 1;
  }
}

}

/******************************************************************************/
