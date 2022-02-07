#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define FACTOR 1000000000
#define SIZE 40
#define BASE 10

long long int power(long long int x, long long int y, long long int p);
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int sumPrime = 0, n = 2, step = 1, nPrime = 0, boolean;
long long int returnValue;
while (1) {
  boolean = primeTest(n);
  assert(boolean!=-1);
  if (boolean == 1) {
    /* prime number, further test need to be done */
    returnValue = power(BASE, FACTOR, 9*n);
    //printf("\nn = %d and res = %d", n, returnValue);
    fflush(stdout);
    if (returnValue == 1) {
      /* new prime factor of R(10^FACTOR) */
      sumPrime+=n;
      nPrime++;
    }
  }
  /* test exit */
  if (nPrime == SIZE) {
    break;
  }
  /* new step */
  if (n == 3) {
    step++;
  }
  /* new number to be tested */
  n+=step;
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe sum of first %d primes of R(10^%d) is %d.", SIZE, FACTOR, sumPrime);
printf("\n");
return 0;
}
/******************************************************************************/
/* Iterative Function to calculate (x^y)%p in O(log y) */
long long int power(long long int x, long long  int y, long long int p) {
    long long int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
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
