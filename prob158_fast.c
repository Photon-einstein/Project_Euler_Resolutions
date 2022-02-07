#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define SIZEALPHA 26
typedef struct{
  int nMax;
  long long int pn_max;
} sol_id;

/* this function makes the calculation of the next line of the Pascal triangle,
and in the end it returns the new line or NULL if there was an error in the
function */
int *somaTrianguloPascal (int *linhaAnterior, int nElementos);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int *linhaAnterior, *linhaActual, nMax = SIZEALPHA, i;
long long int n, p[SIZEALPHA+1]={0};
sol_id s={0};
linhaAnterior = (int*) calloc (2, sizeof (int));
if (linhaActual == NULL) {
  printf ("\nThere was an error in the memory allocation.");
  return 0;
}
/* vetor fulling of the pascal triangle for n = 1 */
linhaAnterior[0] = 1;
linhaAnterior[1] = 1;
for (i = 2; i <= nMax; ++i) {
  linhaAnterior = somaTrianguloPascal (linhaAnterior, i+1);
  if (linhaAnterior == NULL) {
    printf("\nThere was an error in the function somaTrianguloPascal.");
    return 0;
  }
}
for (n = 1; n <= nMax; ++n) {
  p[n] = ((long long int)linhaAnterior[n])*(pow(2,n)-n-1);
  if (p[n] > s.pn_max) {
    s.nMax = n;
    s.pn_max = p[n];
  }
}
/* free memory */
free(linhaAnterior);
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nThe maximum value of p(n) is p(%d) = %lld.", s.nMax, s.pn_max);
printf("\n");
return 0;
}
/******************************************************************************/
int *somaTrianguloPascal (int *linhaAnterior, int nElementos) {
/* this function makes the calculation of the next line of the Pascal triangle,
and in the end it returns the new line or NULL if there was an error in the
function */
if (linhaAnterior == NULL || nElementos < 1) {
  return NULL;
}
int *linhaActual, i, j = 0;
linhaActual = (int*) calloc (nElementos, sizeof (int));
if (linhaActual == NULL) {
  printf ("\nOcorreu uma falha na alocação de memória.");
  return NULL;
}
for (i = 0; i < nElementos; ++i) {
  if (i == 0 || i == (nElementos-1) ) {
    linhaActual[i] = 1;
  } else {
    linhaActual[i] = linhaAnterior[j] + linhaAnterior[j+1];
    ++j;
  }
}
free (linhaAnterior);
return linhaActual;
}
/******************************************************************************/
