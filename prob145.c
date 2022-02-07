#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAX 100000000

/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
int dimCalc (int counter, int *nDigit);

/* this function creates and fills the array with the digits of the number
counter, knowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *fullingVectorDigit (int counter, int dim, int nDigit);

/* this function makes the calculation of the reversible number, and in the
end it returns the number or -1 if there was an error in the function */
int reversibleNumberCalc(int *v, int dim, int nDigit);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
char *c;
int count=0, nDigit, *v, i, rn, dim, boolean, j, sum;
c = (char*) calloc(MAX, sizeof (char));
if (c == NULL) {
  return 0;
}
for (i = 12; i < MAX; i++) {
  /* test if not processed */
  if (c[i] != 0) {
    /* already processed */
    continue;
  }
  /* test if the number has a leading zero */
  if (i%10==0) {
    continue;
  }
  /* dim calc */
  dim = dimCalc (i, &nDigit);
  if (dim  == -1) {
    return 0;
  }
  /* test if leading + last number is odd */
  if ((i%10+(int)i/dim)%2==0) {
    continue;
  }
  /* digit calc */
  v = fullingVectorDigit (i, dim, nDigit);
  if (v == NULL) {
    return 0;
  }
  /* reversible number calc */
  rn = reversibleNumberCalc(v, dim, nDigit);
  if (rn < 0) {
    return 0;
  }
  /* free memory */
  free(v);
  /* sum both numbers */
  sum=rn+i;
  /*test last digit diferent from 0 */
  if (sum%2==0) {
    c[rn]=2;
    c[i]=2;
    continue;
  }
  /* test rest of the digits */
  dim = dimCalc (sum, &nDigit);
  if (dim  == -1) {
    return 0;
  }
  /* digit calc */
  v = fullingVectorDigit (sum, dim, nDigit);
  if (v == NULL) {
    return 0;
  }
  /* test all digits */
  boolean = 0;
  for (j = 0; j < nDigit; j++) {
    if (v[j]%2 == 0) {
      boolean = 1;
      break;
    }
  }
  /* free memory */
  free(v);
  if (boolean == 0) {
    /* new solution found */
    count+=2;
    c[rn]=1;
    c[i]=1;
  } else {
    c[rn]=2;
    c[i]=2;
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThere are %d reversible numbers up to %d.", count, MAX);
free(c);
printf("\n");
return 0;
}
/******************************************************************************/
int dimCalc (int counter, int *nDigit) {
/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
if (nDigit == NULL || counter < 1) {
  return -1;
}
long long int dim = 1, res, nDigitsNumber = 1;
res = counter / dim;
while (res > 9) {
  dim*=10;
  nDigitsNumber++;
  res = counter / dim;
}
*nDigit = nDigitsNumber;
return dim;
}
/******************************************************************************/
int *fullingVectorDigit (int counter, int dim, int nDigit) {
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
  counter-=vectorDigit[i]*dim;
  dim/=10;
}
return vectorDigit;
}
/******************************************************************************/
int reversibleNumberCalc(int *v, int dim, int nDigit) {
/* this function makes the calculation of the reversible number, and in the
end it returns the number or -1 if there was an error in the function */
if (v == NULL || dim < 1 || nDigit < 1) {
  return -1;
}
int n=0, i;
for (i = nDigit-1; i >= 0; i--) {
  n+=v[i]*dim;
  dim/=10;
}
return n;
}
/******************************************************************************/
