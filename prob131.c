#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXPRIME 1000000

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int maxPrime = MAXPRIME, boolean, guess, answer = 0, x;
/* prime testing  */
x = 1;
while (1) {
  guess = pow((1+x),3)-pow(x,3);
  if (guess > maxPrime) {
    break;
  }
  boolean = primeTest(guess);
  if (boolean == -1) {
    printf("\nThere was a problem in the primeTest function.");
    return 0;
  } else if (boolean == 1) {
    answer++;
  }
  x++;
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nUntil %d there are %d prime cube partnership.", maxPrime, answer);
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
