#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXSEARCH 100000000000
/* this function creates and fills the array with the digits of the number
counter, knowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int* fullingVectorDigit (long long int counter, long long int dim, int nDigit);

/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
long long int dimCalc (long long int counter, int *nDigit);

/* this function makes the sum of the occurrences of a given digit in the array
v of size nDigit, and in the end it returns the sum or -1 if there was an error
or -1 if there was an error in the function */
int sumDigit(int *vDigit, int nDigit, long long int *sumFreqDigit);

/* this function makes the print of the values in arrays sum ans s_n and in the
end it returns the sum of the array s_n from start to end index if all ok or -1
if there was a problem in the function */
long long int printCalcValue(long long int *sum, long long int *s_n, int start, int end,long long int maxSearch, int flagPrint);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int *v, nDigit, startD = 1, endD = 9, j, boolean;
long long int *sum, sumAcum=0, *s_n, dim, n, max = MAXSEARCH;
FILE *f;
f = fopen("results.txt", "w+");
if (f == NULL) {
  printf("\nThere was a problem in the opening of the file.");
  return 0;
}
/* memory allocation */
sum = (long long int*) calloc(10, sizeof (long long int));
if (sum == NULL) {
  printf("\nThere was a problem in the memory allocation of sum.");
  return 0;
}
s_n = (long long int*) calloc(10, sizeof (long long int));
if (s_n == NULL) {
  printf("\nThere was a problem in the memory allocation of sum.");
  return 0;
}
for (n = 1; n < max; ++n) {
  if (n % 10000000 == 0) {
    sumAcum = printCalcValue(sum, s_n, startD, endD, max, 1);
    if (sumAcum == -1) {
      printf("\nThere was an error in the function printCalcValue.");
      return 0;
    }
    printf("\nn = %lld | The sum s(1 <= d < =9) = %lld | s(1) = %lld.", n, sumAcum, s_n[1]);
  }
  /* dim calc */
  dim = dimCalc(n, &nDigit);
  if (dim  == -1) {
    printf("\nThere was an error in the function dimCalc");
    return 0;
  }
  /* fulling vectorDigit */
  v = fullingVectorDigit(n, dim, nDigit);
  if (v == NULL) {
    printf("\nThere was an error in the function fullingVectorDigit.");
    return 0;
  }
  boolean = sumDigit(v, nDigit, sum);
  if (boolean == -1) {
    printf("\nThere was a problem in the function sumDigit.");
    return 0;
  }
  /* s update */
  for (j = startD; j <= endD; ++j) {
    if (sum[j] == n) {
      fprintf(f, "\nf(n=%lld, %d) = %lld", n, j,n);
      s_n[j]+=n;
    }
  }
  /* free memory */
  free(v);
}
sumAcum = printCalcValue(sum, s_n, startD, endD, max, 1);
if (sumAcum == -1) {
  printf("\nThere was an error in the function printCalcValue.");
  return 0;
}
fclose(f);
/* free memory */
free(sum);
free(s_n);
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nThe sum s(1 <= d < =9) = %lld", sumAcum);
printf("\n");
return 0;
}
/******************************************************************************/
int *fullingVectorDigit (long long int counter, long long int dim, int nDigit) {
/* this function creates and fills the array with the digits of the number
counter, ckowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *vectorDigit, i;
vectorDigit = (int*) calloc (nDigit, sizeof (int));
if (vectorDigit == NULL) {
  printf ("\nError in the creation of the array.");
  return NULL;
}
for (i = 0; i < nDigit; ++i) {
  vectorDigit[i] = counter / dim;
  counter = counter - vectorDigit[i]*dim;
  dim = dim / 10;
}
return vectorDigit;
}
/******************************************************************************/
long long int dimCalc (long long int counter, int *nDigit) {
/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
if (nDigit == NULL || counter < 1) {
  return -1;
}
long long int dim = 1, res, nDigitsNumber = 1;
res = counter / dim;
while (res > 9) {
  dim = dim * 10;
  ++nDigitsNumber;
  res = counter / dim;
}
*nDigit = nDigitsNumber;
return dim;
}
/******************************************************************************/
int sumDigit(int *vDigit, int nDigit, long long int *sumFreqDigit) {
/* this function makes the sum of the occurrences of a given digit in the array
v of size nDigit, and in the end it returns 1 if all ok or -1 if there was an
error in the function */
if (vDigit == NULL || sumFreqDigit == NULL || nDigit < 1) {
  return -1;
}
int i;
for (i = 0; i < nDigit; ++i) {
  ++sumFreqDigit[vDigit[i]];
}
return 1;
}
/******************************************************************************/
long long int printCalcValue(long long int *sum, long long int *s_n, int start, int end,long long int maxSearch, int flagPrint) {
/* this function makes the print of the values in arrays sum ans s_n and in the
end it returns the sum of the array s_n from start to end index if all ok or -1
if there was a problem in the function */
if (sum == NULL || s_n == NULL || start != 1 || end != 9) {
  return -1;
}
long long int sumAcum=0;
int d;
for (d = start; d < end+1; ++d) {
  if (flagPrint == 1) {
    printf("\nf(n,%d) = %lld for n < %lld ", d, sum[d], maxSearch);
    printf("\ns(%d) = %lld", d, s_n[d]);
  }
  sumAcum+=s_n[d];
}
printf("\n\n\n");
return sumAcum;
}
/******************************************************************************/
