#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXPRIME 150000000+5

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTeste (int nTest, int *v, int nPrime);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int maxSize, i, step=1, *v, mult = 1, boolean, nPrime=0;
FILE *f;
f = fopen("primes.txt", "w+");
if (f == NULL) {
  printf("\nError.");
  return 0;
}
/* memory allocation */
maxSize = 1.2*MAXPRIME/log(MAXPRIME);
printf("\nmaxSize = %d", maxSize);
v =(int*) calloc(maxSize, sizeof (int));
if (v == NULL) {
  printf("\nThere was an error in the memory allocation of v.");
  return 0;
}
for (i = 2; i < MAXPRIME; i+=step) {
  //printf("\ni = %d", i);
  boolean = primeTeste (i, v, nPrime);
  if (boolean == -1) {
    printf("\nThere was an error in the function primeTest.");
    return 0;
  } else if (boolean == 1) {
    /* out of space */
    if (nPrime == maxSize) {
      mult++;
      maxSize*=mult;
      v = (int*) realloc (v, maxSize*sizeof (int));
      if (v == NULL) {
        printf("\nThere was a problem in the memory reallocation.");
        return 0;
      }
    }
    /* prime storage */
    v[nPrime] = i;
    nPrime++;
    fprintf(f, "%d\n", i);
    //printf("\nPrime %d: %d", nPrime, i);
  }
  if (i == 3) {
    step=2;
  }
}
/* free memory */
free(v);
fclose(f);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThere are %d primes until %d.", nPrime, MAXPRIME);
printf("\n");
return 0;
}
/******************************************************************************/
int primeTeste (int nTest, int *v, int nPrime) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
if (v == NULL || nPrime < 0) {
  return -1;
}
int i, comparador;
if (nTest <= 1) {
	return 0;
}
if (nTest  == 2) {
	return 1;
} else if (nTest % 2 == 0) {
	return 0;
}
for (i = 0; i < nPrime && v[i] < sqrt(nTest+1); i++) {
  if (nTest % v[i] == 0) {
		return 0;
	}
}
/* explore top primes unexplored */
/* iStart */
if (nPrime == 1) {
  i = 3;
} else {
  i = v[nPrime-1]+2;
}
for (i = v[nPrime-1]+2; i < sqrt(nTest+1); i = i+2) {
	if (nTest % i == 0) {
		return 0;
	}
}
/* if it reaches here, then it is a prime number */
return 1;
}
/******************************************************************************/
