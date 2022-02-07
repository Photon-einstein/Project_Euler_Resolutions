#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXPRIME 1000010
#define MAX 1000000
typedef struct {
  int prime;
  int powerDigit;
  int nDigit;
} primeId;

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

/* this function makes the update of char array, that prime number is prime,
and the multiples of prime are composites, then it returns 1 if all ok or 0 if
there was a problem in the function, 0 not processed, 1 prime, 2 not prime */
int updateSievePrime(char *sievePrime, int size, int prime);

/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
int dimCalc (int counter, int *nDigit);

/* Function for Extended Euclidean algorithm it uses pointers to return
multiple values, it solves_ ax + by = gcd (a,b) */
int extended_gcd(int a, int b, int *x, int *y);

/* this function makes the calculation of x for this problem: a.x = b mod n, or
0 if there was a problem in the function */
long long int calcValue(int a, int n, int b);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
char sievePrime[MAXPRIME]={'0'};
int i, boolean, nPrimes = 0, step=1;
long long int answer=0, booleanLong;
primeId *v;
/* memory allocation */
v = (primeId*) calloc(MAXPRIME, sizeof (primeId));
assert(v!=NULL);
for (i = 2; i < MAXPRIME; i+=step) {
  /* step update */
  if (i == 3) {
    step++;
  }
  /* 0 not processed, 1 prime, 2 not prime */
  if (sievePrime[i] == '2') {
    continue;
  }
  /* test not processed numbers */
  boolean = primeTest(i);
  assert(boolean!=-1);
  if (boolean == 1) {
    /* new prime found */
    v[nPrimes].prime = i;
    v[nPrimes].powerDigit = dimCalc(i, &v[nPrimes].nDigit);
    v[nPrimes].powerDigit = (int) roundl(pow(10.0, v[nPrimes].nDigit));
    nPrimes++;
    boolean = updateSievePrime(sievePrime, MAXPRIME, i);
    assert(boolean!=0);
  }
}
/* memory reallocation */
v = (primeId*) realloc(v, nPrimes*sizeof (primeId));
assert(v!=NULL);
/* resolution */
for (i = 0; i < nPrimes; i++) {
  /* test prime p1 >= 5 or end of array */
  if (v[i].prime < 5) {
    continue;
  } else if (v[i].prime > MAX) {
    /* end of test reached */
    break;
  }
  /* test for a given valid pair of primes */
  booleanLong = calcValue(v[i].powerDigit, v[i+1].prime, v[i+1].prime-v[i].prime);
  assert(booleanLong!=0);
  booleanLong = v[i].powerDigit*booleanLong+v[i].prime;
  answer+=booleanLong;
}
/* free memory */
free(v);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe sum of S for 5 < p1 <= %d is %lld.", MAX, answer);
printf("\n");
return 0;
}
/******************************************************************************/
int primeTest (int nTest) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int i, comparador;
if (nTest <= 1) {
	return 0;
}
if (nTest  == 2) {
	return 1;
} else if (nTest % 2 == 0) {
	return 0;
}
for (i = 3; i < sqrt(nTest+1); i = i+2) {
	if (nTest % i == 0) {
		return 0;
	}
}
/* if it reaches here, then it is a prime number */
return 1;
}
/******************************************************************************/
int updateSievePrime(char *sievePrime, int size, int prime) {
/* this function makes the update of char array, that prime number is prime,
and the multiples of prime are composites, then it returns 1 if all ok or 0 if
there was a problem in the function, 0 not processed, 1 prime, 2 not prime */
if (sievePrime == NULL || size < 1 || prime < 2) {
  return 0;
}
int mult = 2, pos;
while (1) {
  pos = mult*prime;
  if (pos>=size) {
    /* end array */
    return 1;
  }
  sievePrime[pos] = '2';
  mult++;
}
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
int extended_gcd(int a, int b, int *x, int *y) {
/* Function for Extended Euclidean algorithm it uses pointers to return
multiple values, it solves_ ax + by = gcd (a,b) */
if (a == 0) {
	*x = 0;
	*y = 1;
	return b;
}
int _x, _y;
int gcd = extended_gcd(b % a, a, &_x, &_y);
*x = _y - (b/a) * _x;
*y = _x;
return gcd;
}
/******************************************************************************/
long long int calcValue(int a, int n, int b) {
/* this function makes the calculation of x for this problem: a.x = b mod n, or
0 if there was a problem in the function */
int xBarra, yBarra, d, i;
long long int res;
d = extended_gcd(a, n, &xBarra, &yBarra);
res = xBarra*b/d % n;
if (res > 0) {
  return res;
} else {
  return (res+n);
}
return res;
}
/******************************************************************************/
