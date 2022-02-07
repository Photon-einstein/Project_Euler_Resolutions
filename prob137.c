#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAX 15

/* this function allocates dimAnswer fields of size int and then fill with the
sequence of fibonaci, and in the end it returns the pointer or NULL if there
was an error in the function */
int* fillArray(int dimAnswer);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int *fib, boolean, count, sizeArray;
long long int res;
/* full fib array */
sizeArray = 2*MAX+2;
/* fill array fibonacci */
fib = fillArray(sizeArray);
if (fib == NULL) {
  exit(1);
}
/* get answer */
res = (long long int)fib[MAX*2]*fib[MAX*2+1];
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe %d fibonacci golden nugget is %lld", MAX, res);
free(fib);
printf("\n");
return 0;
}
/******************************************************************************/
int* fillArray(int dimAnswer) {
/* this function allocates dimAnswer fields of size int and then fill with the
sequence of fibonaci, and in the end it returns the pointer or NULL if there
was an error in the function */
if (dimAnswer < 1) {
  return NULL;
}
int *v, step;
/* memory allocation */
v = (int*) calloc(dimAnswer, sizeof (int));
if (v == NULL) {
  return NULL;
}
/* first three fields of the array */
for (step = 1; step < 3 && step < dimAnswer; step++) {
  v[step] = 1;
}
if (step == dimAnswer) {
  return v;
}
/* next fields of the array */
for (;step < dimAnswer; step++) {
  v[step] = v[step-1] + v[step-2];
}
return v;
}
/******************************************************************************/
