#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MINSIZESEARCH 1
#define DIMFIBSTART  100000000
#define DIMFIBSTARTL 100000000000000
#define NDIGIT  9
#define NDIGITL 15
#define MINFINDE 2749

/* this function returns the first fib of the dim = dimFib and also it returns
by reference the index k. If there was a problem it returns -1 */
int calcFibOfSize (int dimFib, int *k, int *fnMinus1P);

/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
int dimCalc (int counter, int *nDigit);

/* this function creates and fills the array with the digits of the number
counter, ckowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *preencheVectorDigit (int counter, int dim, int nDigit);

/* this function creates and fills the array with the digits of the number
counter, ckowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *preencheVectorDigitL (long long int counter, long long int dim, int nDigit);

/* this functions makes the confirmation the this nAlg digits are in fact a
Pandigital number, if yes returns 1 if not it returns 0, or -1 if there was a
problem in the function */
int pandigitalCheck (int *vector, int nAlg);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int minSearch = MINSIZESEARCH, fnD, dim;
int fnMinus1D, fnMinus2D, dimFibStart = DIMFIBSTART, divider = dimFibStart*10;
int k, *v, booleano1 = 0, booleano2 = 0, res, nDigit = NDIGIT, answer, found = 0;
long long int fnL, fnMinus1L, fnMinus2L, dimFibStartL = DIMFIBSTARTL;
int nDigitL = NDIGITL, booleanoDigit = 0, minFinde = MINFINDE;

fnD = calcFibOfSize (dimFibStart, &k, &fnMinus1D);
/* preparations for enter cycle */
/* fn-2 */
fnMinus2L = fnMinus1D;
fnMinus2D = fnMinus1D;
/* fn-1 */
fnMinus1L = fnD;
fnMinus1D = fnD;
dim = dimFibStart;
while (!found) {
  /* right calc */
  fnD = fnMinus1D + fnMinus2D;
  k++;
  /* resize of fnD */
  fnD%=divider;
  /* nDigit = 9 and dim = 10⁹ */
  if (k > minSearch) {
    v = preencheVectorDigit (fnD, dim, nDigit);
    if (v == NULL) {
      printf("\nThere was an error in the function v.");
      return 0;
    }

    booleano1 = pandigitalCheck (v, nDigit);
    if (booleano1 == -1) {
      printf ("\nThere was a problem in the function.");
    }
    /* free memory */
    free (v);
    v = NULL;
  }
  /* next menber */
  fnMinus2D = fnMinus1D;
  fnMinus1D = fnD;
  /* left calc */
  fnL = fnMinus1L + fnMinus2L;
  /* resize of fnD */
  res = fnL / dimFibStartL;
  if (res > 9) {
    /* overflow, downsize */
    fnL/=10;
    fnMinus1L/=10;
  }
  /* next menber */
  fnMinus2L = fnMinus1L;
  fnMinus1L = fnL;
  /* testing conditions if right size is pandigital */
  if (booleano1 == 1 && k > minFinde) {
    /* nDigitL = 15 and dim = pow(10,15) */
    v = preencheVectorDigitL (fnL, dimFibStartL, nDigit);
    if (v == NULL) {
      printf("\nThere was an error in the function v.");
      return 0;
    }
    booleano2 = pandigitalCheck (v, nDigit);
    /* free memory */
    free (v);
    v = NULL;
    if (booleano2 == -1) {
      printf ("\nThere was a problem in the function.");
    } else if (booleano2 == 1) {
      answer = k;
      found = 1;
    }
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThe answer is %d.", answer);
printf("\n");
return 0;
}
/******************************************************************************/
int pandigitalCheck (int *vector, int nAlg) {
/* this functions makes the confirmation the this nAlg digits are in fact a
Pandigital number, if yes returns 1 if not it returns 0, or -1 if there was a
problem in the function */
if (vector == NULL) {
  return -1;
}
int *vectorCheck;
int i, j;
vectorCheck = (int*) calloc (nAlg, sizeof (int));
if (vectorCheck == NULL) {
  printf ("\nError in the memory allocation of vectorCheck.");
  return -1;
}
/*fulling of vector check*/
for (i = 0; i < nAlg; i++) {
  vectorCheck [i] = i+1;
}
/* check to see if exist the numbers from 1 until nAlg */
for (i = 0; i < nAlg; i++) {
  for (j = 0; j < nAlg; j++) {
    if (vector[i] == vectorCheck[j]) {
      vectorCheck[j] = -1;
    }
  }
}
for (i = 0; i < nAlg; i++) {
  /* no pandigital found */
  if (vectorCheck[i] != -1) {
    free(vectorCheck);
    return 0;
  }
}
/* if it arrives here then it is a pandigital number */
free(vectorCheck);
return 1;
}
/******************************************************************************/
int dimCalc (int counter, int *nDigit) {
/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
if (nDigit == NULL || counter < 1) {
  return -1;
}
int dim = 1;
int res, nDigitsNumber = 1;
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
int *preencheVectorDigit (int counter, int dim, int nDigit) {
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
int calcFibOfSize (int dimFib, int *k, int *fnMinus1P) {
/* this function returns the first fib of the dim = dimFib and also it returns
by reference the index k. If there was a problem it returns -1 */
if (k == NULL || dimFib < 1 || fnMinus1P == NULL) {
  return -1;
}
int fn, fnMinus1 = 1, fnMinus2 = 1, kcalc = 2, dim, nDigit;
while (1) {
  fn = fnMinus1 + fnMinus2;
  kcalc++;
  dim = dimCalc (fn, &nDigit);
  if (dim == dimFib) {
    break;
  }
  /* next number preparations */
  fnMinus2 = fnMinus1;
  fnMinus1 = fn;
}
*k = kcalc;
*fnMinus1P = fnMinus1;
return fn;
}
/******************************************************************************/
int *preencheVectorDigitL (long long int counter, long long int dim, int nDigit) {
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
