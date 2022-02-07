#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXPRIME 1000010
#define MAX 1000000

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

/* this function makes the update of char array, that prime number is prime,
and the multiples of prime are composites, then it returns 1 if all ok or 0 if
there was a problem in the function, 0 not processed, 1 prime, 2 not prime */
int updateSievePrime(char *sievePrime, int size, int prime);

/* this function makes the calculation for a given consecutive pair of prime
numbers, p1 < p2, the minimum S for this pair and then returns the S if all
went ok or 0 if there was an error in the function */
long long int findSforGivenPairPrimes(int p1,int p2);

/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
int dimCalc (int counter, int *nDigit);

/* Function for Extended Euclidean algorithm it uses pointers to return
multiple values, it solves_ ax + by = gcd (a,b) */
int extended_gcd(int a, int b, int *x, int *y);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
char sievePrime[MAXPRIME]={'0'};
int i, boolean, nPrimes = 0, *v, step=1;
long long int answer=0, booleanLong;
/* memory allocation */
v = (int*) calloc(MAXPRIME, sizeof (int));
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
    v[nPrimes] = i;
    nPrimes++;
    boolean = updateSievePrime(sievePrime, MAXPRIME, i);
    assert(boolean!=0);
  }
}
/* memory reallocation */
v = (int*) realloc(v, nPrimes*sizeof (int));
assert(v!=NULL);
/* resolution */
for (i = 0; i < 10; i++) {
  /* test prime p1 >= 5 or end of array */
  if (v[i] < 5) {
    continue;
  } else if (v[i] > MAX) {
    /* end of test reached */
    break;
  }
  /* test for a given valid pair of primes */
  booleanLong = findSforGivenPairPrimes(v[i],v[i+1]);
  printf("\np1 = %d, p2 = %d, S = %lld", v[i], v[i+1], booleanLong);
  assert(boolean!=0);
  answer+=booleanLong;
}
/* free memory */
free(v);
printf("\nUntil %d there are %d primes.", MAXPRIME, nPrimes);
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
long long int findSforGivenPairPrimes(int p1,int p2) {
/* this function makes the calculation for a given consecutive pair of prime
numbers, p1 < p2, the minimum S for this pair and then returns the S if all
went ok or 0 if there was an error in the function */
if (p1>=p2) {
  printf("\nThere was a problem in the function findSforGivenPairPrimes.");
  return 0;
}
int nDigitP1, dimP1;
long long int step, k=p2-p1+1, n=p1;
/* p1 investigation */
dimP1 = dimCalc(p1, &nDigitP1);
if (dimP1==-1) {
  printf("\nThere was a problem in the function dimCalc.");
  return 0;
}
/* minimum step to be incremented */
step = (int) roundl(pow(10.0, nDigitP1));
/* final test */
while (1) {
  /* new number to test */
  n+=step;
  /* test if S was found */
  if (n % p2 == 0 && n > 0) {
    return n;
  }
  if (n%10==p1%10) {
    k*=10;
  } else {
    k++;
  }
  /* error detection, overflow */
  if (n < 0) {
    printf("\nOverflow, erro in the function findSforGivenPairPrimes.");
    return 0;
  }
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
