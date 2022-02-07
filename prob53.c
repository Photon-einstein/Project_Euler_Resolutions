#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MIN 1000000

/* faz a soma do triangulo de pascal e devolve proxima linha do triangulo de pascal */
/* se o numero for superior a 1M então fica como -1 */
int *somaTrianguloPascal (int *linhaAnterior, int nElementos);

/* faz a verificação da linha completa e conta o numero de elementos maiores que 1M */
int verificaDadosSupMAX (int *linhaAnterior, int dim);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
int n, i, r, contador = 0, resultado = 0;
int *linhaAnterior, *linhaActual;

linhaAnterior = (int*) calloc (2, sizeof (int));
if (linhaActual == NULL) {
  printf ("\nOcorreu uma falha na alocação de memória.");
  return 0;
}

/* preenchimento do vector para n = 1 do triangulo de pascal */
linhaAnterior[0] = 1;
linhaAnterior[1] = 1;

for (n = 2; n < 101; n++) {
  linhaAnterior = somaTrianguloPascal (linhaAnterior, n+1);
  if (linhaAnterior == NULL) {
    return 0;
  }
  resultado = resultado + verificaDadosSupMAX (linhaAnterior, n+1);
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nExistem %d valores maiores que 1M com n <= 100.", resultado);
printf ("\n");
return 0;
}

/******************************************************************************/

int *somaTrianguloPascal (int *linhaAnterior, int nElementos) {
/* faz a soma do triangulo de pascal e devolve proxima linha do triangulo de pascal */
/* se o numero for superior a 1M então fica como -1 */

int *linhaActual, i, j = 0;

linhaActual = (int*) calloc (nElementos, sizeof (int));
if (linhaActual == NULL) {
  printf ("\nOcorreu uma falha na alocação de memória.");
  return NULL;
}

for (i = 0; i < nElementos; i++) {
  if (i == 0 || i == (nElementos-1) ) {
    linhaActual[i] = 1;
  } else {
    if (linhaAnterior[j] < MIN && linhaAnterior[j+1] < MIN && linhaAnterior[j] != -1 && linhaAnterior[j+1] != -1) {
      linhaActual[i] = linhaAnterior[j] + linhaAnterior[j+1];

      if (linhaActual[i] > MIN) {
        linhaActual[i] = -1;
      }
    } else {
      linhaActual[i] = -1;
    }
    j++;
  }
}

free (linhaAnterior);
return linhaActual;
}

/******************************************************************************/

int verificaDadosSupMAX (int *linhaAnterior, int dim) {
/* faz a verificação da linha completa e conta o numero de elementos maiores que 1M */

int i, contador = 0;

for (i = 0; i < dim; i++) {
  if (linhaAnterior[i] == -1) {
    contador++;
  }
}

return contador;
}

/******************************************************************************/
