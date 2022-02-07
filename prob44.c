#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 25000

/* gera dinamicamente um vector de inteiros de dim  = nNumeros e preenche-os
com os numeros pentagonos desde o indice 0 */
long long int *geraVectorPentNum (int nNumeros);

/* função retorna 1 se tiver pentagono number como sumP e difP ou 0 se um deles
ou os dois não o for */
int booleanoEncontraSumPdifP (long long int *vector, int nNumeros, long long int numP);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */

long long int *vector;
int i, j;
long long int sumP, difP;
int booleano;
long long int dCur, dMin = 0;
int count = 0;
int found = 0;

vector = geraVectorPentNum (DIM);
if (vector == NULL) {
  printf ("\nVector nulo à saída da função gera vector.");
  return 0;
}

for (i = 1; i < DIM-5; i++) {
  /*printf ("\ni = %d, dMin = %lli, vector[i] = %lli", i, dMin, vector[i]); */
  if (found == 1) {
    break;
  }
  for (j = 0; j < i; j++) {
      /*printf ("\ni = %d, j = %d, dMin = %d, count = %d", i, j, dMin, count);*/
      sumP = vector[i] + vector[j];
      difP = vector[i] - vector[j];
      booleano = booleanoEncontraSumPdifP (vector, DIM, sumP);
      if (booleano == 0) {
        continue;
      }
      booleano = booleanoEncontraSumPdifP (vector, DIM, difP);
      if (booleano == 0) {
        continue;
      }

      dCur = vector[i] - vector[j];

      if (count == 0) {
        /* primeiro valor de dMin */
        dMin = dCur;
        found = 1;
      } else if (dMin > dCur) {
        dMin = dCur;
      }
      count++;
      printf ("\ndMin = %lli.", dMin);
  }
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nD é minimo para dMin = %lli.\n", dMin);
return 0;
}

/******************************************************************************/

long long int *geraVectorPentNum (int nNumeros) {
/* gera dinamicamente um vector de inteiros de dim  = nNumeros e preenche-os
com os numeros pentagonos desde o indice 0 */

long long int *vector;
int i;

vector = (long long int*) calloc (nNumeros, sizeof (long long int));
if (vector == NULL) {
  printf ("\nOcorreu uma falha na criação do vector.");
  return NULL;
}

for (i = 0; i < nNumeros; i++) {
  vector[i] = (i+1)*(3*(i+1)-1)/2;
}

return vector;
}

/******************************************************************************/

int booleanoEncontraSumPdifP (long long int *vector, int nNumeros, long long int numP) {
/* função retorna 1 se tiver pentagono number como sumP e difP ou 0 se um deles
ou os dois não o for */

int i;

for (i = 0; i < nNumeros; i++) {
  if (numP == vector[i]) {
    return 1;
  } else if (numP < vector[i]) {
    return 0;
  }
}

/* se chega aqui e porque não e */
return 0;

}

/******************************************************************************/
