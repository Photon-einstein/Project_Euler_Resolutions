#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXPOWER 19
#define MAXPRIME 100000
#define BASE 10

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

/* this function makes the update of char array, that prime number is prime,
and the multiples of prime are composites, then it returns 1 if all ok or 0 if
there was a problem in the function, 0 not processed, 1 prime, 2 not prime */
int updateSievePrime(char *sievePrime, int size, int prime);

/* Iterative Function to calculate (base^exponent)%modulus in O(log exponent) */
long long int modular_pow(long long int base, long long int exponent,
  long long int modulus);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
char sievePrime[MAXPRIME]={'0'};
int i, boolean, nPrimes = 0, *v, j, nFound = 0, answer, sumFound=0, totalSum=0,nAnswer;
int step=1;
long long int res;
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
    totalSum+=i;
    nPrimes++;
    boolean = updateSievePrime(sievePrime, MAXPRIME, i);
    assert(boolean!=0);
  }
}
/* memory reallocation */
v = (int*) realloc(v, nPrimes*sizeof (int));
assert(v!=NULL);
/* testing primes */
for (i = 0; i < nPrimes; i++) {
  for (j = 0; j < MAXPOWER; j++) {
    res = modular_pow(BASE, roundl(pow(10,j)), 9*v[i]);
    if (res == 1) {
      nFound++;
      sumFound+=v[i];
      /* no more need to further tests */
      break;
    }
  }
}
/* answer calc */
answer = totalSum - sumFound;
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nUntil primes < %d, the total sum of all the primes that will never be\nprime of R(10^n) is %d.", MAXPRIME, answer);
printf("\n");
/* free memory */
free(v);
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
long long int modular_pow(long long int base, long long int exponent,
  long long int modulus) {
/* Iterative Function to calculate (base^exponent)%modulus in O(log exponent) */
if (modulus == 1) {
  return 0;
}
//Assert :: (modulus - 1) * (modulus - 1) does not overflow base
long long int result = 1;
base = base % modulus;
while (exponent > 0){
    if (exponent % 2 == 1) {
       result = (result * base) % modulus;
    }
    exponent = exponent >> 1;
    base = (base * base) % modulus;
}
return result;
}
/******************************************************************************/
