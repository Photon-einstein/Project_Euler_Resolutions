#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 20000

void preencheVectores (unsigned long long int *vTriangle, unsigned long long int *vPentagonal, unsigned long long int *vHexagonal, int nNumeros);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */

unsigned long long int *vTriangle, *vPentagonal, *vHexagonal, resposta;
int i, j, k, found = 0;

vTriangle   = (unsigned long long int*) calloc (DIM, sizeof (unsigned long long int));
vPentagonal = (unsigned long long int*) calloc (DIM, sizeof (unsigned long long int));
vHexagonal  = (unsigned long long int*) calloc (DIM, sizeof (unsigned long long int));

if (vTriangle == NULL || vPentagonal == NULL || vHexagonal == NULL) {
  printf ("\nFalha na alocação de memória.");
  return 0;
}

preencheVectores (vTriangle, vPentagonal, vHexagonal, DIM);

for (i = 0; i < DIM; i++) {
  printf ("\ni = %d", i);

  if (found == 1) {
    break;
  }

  for (j = 0; j < DIM; j++) {
    if (vTriangle[i] > vPentagonal[j]) {
      continue;
    }

    if (vTriangle[i] < vPentagonal[j]) {
      break;
    }

    if (found == 1) {
      break;
    }

    for (k = 0; k < DIM; k++) {

        if (vTriangle[i] > vHexagonal[k]) {
          continue;
        }


        if (vTriangle[i] == vPentagonal[j]) {
          if (vTriangle[i] == vHexagonal[k]) {
            found = 1;
            resposta = vTriangle[i];
            break;
          }
        }

        if (vTriangle[i] < vHexagonal[k]) {
          break;
        }



    }
  }
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
if (found == 0) {
  printf ("\nNão foi encontrado.\n");
  return 0;
}
printf ("\nNext triangle number = %lli.\n", resposta);
return 0;
}

/******************************************************************************/

void preencheVectores (unsigned long long int *vTriangle, unsigned long long int *vPentagonal, unsigned long long int *vHexagonal, int nNumeros) {

long long int i;

for (i = 0; i < DIM; i++) {
  vTriangle[i] = (286+i)*(286+i +1)/2;
  vPentagonal[i] = (166+i)*(3*(166+i) - 1)/2;
  vHexagonal[i] = (144+i)*(2*(144+i) - 1);
}

for (i = DIM-5; i < DIM; i++) {
  printf ("\n %llu %llu %llu ", vTriangle[i], vPentagonal[i], vHexagonal[i]);
}
printf ("\n");

return;
}

/******************************************************************************/
