#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define NSTART 91
#define NSUM 25

/* this function makes the calculation of the A(n) and then returns the
value or 0 if there was a problem in this function, it returns also -1 if
A > (n-1)/2 */
int aCalc (int n);

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int n, nSum, nCount = 0, aK, boolean,step, sum = 0;
n = NSTART;
step = 2;
nSum = NSUM;
while (nCount!=nSum) {
  /* GCD (n,10)= 1 test */
  if (n%5==0) {
    n+=step;
    continue;
  }
  /* prime test */
  boolean = primeTest (n);
  if (boolean == -1) {
    printf("\nThere was a problem in the function prime test.");
    return 0;
  } else if (boolean == 1) {
    /* prime found */
    n+=step;
    continue;
  }
  /* if it reaches here then it is a composite number */
  aK = aCalc (n);
  if (aK == 0) {
    printf("\nThere was a problem in the function aCalc.");
    return 0;
  } else if (aK == -1) {
    /* flag overflow on */
    n+=step;
    continue;
  }
  /* if it reaches here then n is composite number and A(n) >= (n-1)/2 */
  if ((n-1)%aK==0) {
    nCount++;
    sum+=n;
  }
  /* new n calc */
  n+=step;
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe sum of the first values %d are: %d.", nSum, sum);
printf("\n");
return 0;
}
/******************************************************************************/
int aCalc (int n) {
/* this function makes the calculation of the A(n) and then returns the
value or 0 if there was a problem in this function, it returns also -1 if
A > (n-1)/2 */
if (n <= 0 || n % 5 == 0 || n % 2 == 0) {
  return 0;
}
int x = 1, k = 1;
while (x!=0) {
  x = x*10 +1;
  x = x % n;
  k++;
  /* shortcut condition */
  if (k > ((n-1)/2)) {
    return -1;
  }
}
return k;
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
