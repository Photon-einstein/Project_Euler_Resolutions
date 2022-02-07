#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXEXP 11
#define SIZEARRAY 60
#define MAXBASE 100
#define N 30

/* this function makes the sum of the digits and then return the sum or -1 if
there was a problem in the function */
int sumDigits (int *vDigit, int nDigit);

/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
long long int dimCalc (long long int counter, int *nDigit);

/* this function creates and fills the array with the digits of the number
counter, knowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *fullingVectorDigit (long long int counter, long long int dim, int nDigit);

/* this function makes the sorting in ascending order of the array values, of
size dim, and then return 1 if all went ok or 0 if there was a problem in the
function */
int sortingAscendingOrder (long long int *values, int dim);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int base, maxSizeValues = SIZEARRAY, realSizeValues = 0, maxBase = MAXBASE;
int expo, maxExp = MAXEXP, nDigit, *vDigit, sum, n = N, booleano;
long long int *values, nTest, dim, answer;
/* array creation */
values = (long long int*) calloc (maxSizeValues, sizeof (long long int));
if (values == NULL) {
  printf("\nThere was an error in the memory allocation of values.");
  return 0;
}
/* test cycle */
for (base = 2; base < maxBase+1; base++) {
  for (expo = 2; expo < maxExp+1; expo++) {
    nTest = pow (base, expo);
    /* overflow test */
    if (nTest < 0) {
      break;
    }
    /* dim calc */
    dim = dimCalc (nTest, &nDigit);
    if (dim == -1) {
      printf("\nThere was a problem in the function dimCalc.");
      return 0;
    }
    /* fulling vector digit */
    vDigit = fullingVectorDigit (nTest, dim, nDigit);
    if (vDigit == NULL) {
      printf("\nThere was an erro in the function fullingVectorDigit.");
      return 0;
    }
    /* sum digit calc */
    sum = sumDigits (vDigit, nDigit);
    if (sum == -1) {
      printf("\nThere was a problem in the function sumDigits.");
      return 0;
    }
    /* free memory */
    free (vDigit);
    /* test equality of base and sum */
    if (base == sum) {
      /* new value found */
      /* overflow possibillity */
      if ((realSizeValues+1)==maxSizeValues) {
        maxSizeValues*=2;
        values = (long long int*) realloc (values, maxSizeValues*sizeof (long long int));
        if (values == NULL) {
          printf("\nThere was an error the memory reallocation.");
          return 0;
        }
      }
      /* new values saved */
      values[realSizeValues] = nTest;
      realSizeValues++;
    }
  }
}
/* sorting of the values array */
booleano = sortingAscendingOrder (values, realSizeValues);
if (booleano == 0) {
  printf("\nThere was a problem in the function sortingAscendingOrder.");
  return 0;
}
answer = values[n-1];
/* free memory */
free (values);
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\na%d = %lld and realSizeValues = %d", n, answer, realSizeValues);
printf ("\n");
return 0;
}
/******************************************************************************/
int sumDigits (int *vDigit, int nDigit) {
/* this function makes the sum of the digits and then return the sum or -1 if
there was a problem in the function */
if (vDigit == NULL || nDigit < 1) {
  return -1;
}
int sum = 0, i;
for (i = 0; i < nDigit; i++) {
  sum+=vDigit[i];
}
return sum;
}
/******************************************************************************/
long long int dimCalc (long long int counter, int *nDigit) {
/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
if (nDigit == NULL || counter < 1) {
  return -1;
}
long long int dim = 1;
long long int res, nDigitsNumber = 1;
res = counter / dim;
while (res > 9) {
  dim = dim * 10;
  nDigitsNumber++;
  res = counter / dim;
}
*nDigit = nDigitsNumber;
return dim;
}
/******************************************************************************/
int *fullingVectorDigit (long long int counter, long long int dim, int nDigit) {
/* this function creates and fills the array with the digits of the number
counter, ckowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *vectorDigit;
int i;
vectorDigit = (int*) calloc (nDigit, sizeof (int));
if (vectorDigit == NULL) {
  printf ("\nError in the creation of the array.");
  return NULL;
}
for (i = 0; i < nDigit; i++) {
  vectorDigit[i] = counter / dim;
  counter = counter - vectorDigit[i]*dim;
  dim = dim / 10;
}
return vectorDigit;
}
/******************************************************************************/
int sortingAscendingOrder (long long int *values, int dim) {
/* this function makes the sorting in ascending order of the array values, of
size dim, and then return 1 if all went ok or 0 if there was a problem in the
function */
if (values == NULL || dim < 1) {
  return 0;
}
int i, j;
long long int aux;
for (i = 0; i < dim-1; i++) {
  for (j = i+1; j < dim; j++) {
    /* swap test */
    if (values[i] > values[j]) {
      /* aux = i */
      aux = values[i];
      /* i = j */
      values[i] = values[j];
      /* j = aux */
      values[j] = aux;
    }
  }
}
return 1;
}
/******************************************************************************/
