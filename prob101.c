#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 11
#define START 1

/* this function will generate a array of integers solutions, that has the first
dim values of a function, starting in the value start, it returns the pointer if
all ok or it returns NULL if there was a problem in the function. */
long long int* generateSolutions (int dim, int start);

/* this function calculate the next an of the interpolator function, using the
Newton's method. It returns the value and the flag problem in 0 or if there was
a problem int the function it returns by reference the flag at 1 */
long long int anNextCalculator (long long int *v, long long int *an, int dim, int start, int *booleano, int xk);

/* this function makes the calculation of the Wk(n) for the interpolator
polinomial of the Newton's method. It returns the number or 0 if there was a
problem */
long long int wCalculator (int size, int start, int n);

/* this function makes the calculation of the Pk-1(xk) of the interpolator
polinomial of Newton's method. It returns the number and flat booleano = 0
if no problem or flag booleano = 1 if there was a problem */
long long int pk1Calculator (long long int *an, int dim, int start, int xk,
  int *booleano);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int dim = DIM, start = START, i, booleano;
long long int *v, solution = 0, *an, guess, xk;

v = generateSolutions (dim, start);
if (v == NULL) {
  printf ("\nThere was a problem in the function generateSolutions.");
  return 0;
}
an = (long long int*) calloc (dim, sizeof (long long int));
if (an == NULL) {
  printf ("\nThere was a problem in the memory allocation for an.");
  return 0;
}
/* calculating the solution */
for (i = 0; i < dim-1; i++) {
  /* first value of the function interpolator */
  if (i == 0) {
    an[i] = v[i];
    if (an[i] == v[i+1]) {
      /* perfect interpolation */
      break;
    } else {
      printf ("\nGuess = %lld and value = %lld", an[i], v[i+1]);
      solution+=an[i];
    }
    continue;
  }
  xk = start+i;
  /* other value of the function interpolator */
  an[i] = anNextCalculator (v, an, i+1, start, &booleano, xk);
  if (booleano == 1) {
    printf ("\nThere was a problem in the function anNextCalculator.\n");
    return 0;
  }
  guess = pk1Calculator (an, i+1, start, xk+1, &booleano);
  printf ("\nGuess = %lld and value = %lld", guess, v[i+1]);
  if (booleano == 1) {
    printf ("\nThere was a problem in the function pk1Calculator.");
    return 0;
  }
  /* interpolation test */
  if (guess == v[i+1]) {
    /* perfect interpolation */
    break;
  } else {
    solution+=guess;
  }
}
/* free memory allocated */
free(v);
free(an);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThe sum of all the FITs for the BOPs is %lld.", solution);
printf ("\n");
return 0;
}
/******************************************************************************/
long long int* generateSolutions (int dim, int start) {
/* this function will generate a array of integers solutions, that has the first
dim values of a function, starting in the value start, it returns the pointer if
all ok or it returns NULL if there was a problem in the function. */
if (dim < 1) {
  return NULL;
}
int i, n;
long long int *v;
v = (long long int*) calloc (dim, sizeof(long long int));
if (v == NULL) {
  return NULL;
}
/* fulling the array */
for (i = 0; i < dim; i++) {
  n = i + start;
  /*v[i] = pow(n,3);*/
  v[i] = 1-n+pow(n,2)-pow(n,3)+pow(n,4)-pow(n,5)+pow(n,6)-pow(n,7)+pow(n,8)-
  pow(n,9)+pow(n,10);
}
return v;
}
/******************************************************************************/
long long int anNextCalculator (long long int *v, long long int *an, int dim, int start,
  int *booleano, int xk) {
/* this function calculate the next an of the interpolator function, using the
Newton's method. It returns the value and the flag problem in 0 or if there was
a problem int the function it returns by reference the flag at 1 */
if (v == NULL || an == NULL || booleano == NULL || dim < 1) {
  *booleano = 1;
  return 0;
}
int booleanoF;
long long int pkminus1, wkminus1, ak;
pkminus1 = pk1Calculator (an, dim-1, start, xk, &booleanoF);
if (booleanoF == 1) {
  printf ("\nThere was a problem in the function pk1Calculator.");
  *booleano = 1;
  return 0;
}
wkminus1 = wCalculator (dim-1, start, xk);
ak = (v[xk-start]- pkminus1)/wkminus1;
if ((v[xk-start]-pkminus1)%wkminus1 != 0) {
  printf ("\nak is not an integer number.");
  *booleano = 1;
  return 0;
}
return ak;
}
/******************************************************************************/
long long int wCalculator (int size, int start, int n) {
/* this function makes the calculation of the Wk(n) for the interpolator
polinomial of the Newton's method. It returns the number or 0 if there was a
problem */
if (size < 1) {
  return 0;
}
int i;
long long int value = 0, x;
for (i = 0; i < size; i++) {
  x = start + i;
  if (i == 0) {
    value = n - x;
  } else {
    value = value*(n-x);
  }
}
return value;
}
/******************************************************************************/
long long int pk1Calculator (long long int *an, int dim, int start, int xk,
  int *booleano) {
/* this function makes the calculation of the Pk-1(xk) of the interpolator
polinomial of Newton's method. It returns the number and flat booleano = 0
if no problem or flag booleano = 1 if there was a problem */
if (an == NULL || booleano == NULL || dim < 1) {
  *booleano = 1;
  return 0;
}
long long int pk1 = 0, wn;
int i, sizeW;
for (i = 0; i < dim; i++) {
  sizeW = i;
  if (i == 0) {
    /* only a0 */
    pk1+=an[i];
  } else {
    wn = wCalculator(sizeW, start, xk);
    if (wn == 0) {
      printf ("\nThere was a problem in the function wCalculator.");
      *booleano = 1;
      return 0;
    }
    pk1+=(an[i]*wn);
  }
}
*booleano = 0;
return pk1;
}
/******************************************************************************/
