#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 10000000
#define SIZE 2000

/* this function calculate the dimension of the number, and returns also the
number of digits of the counter by reference */
int dimCalc (int number, int *nDigit);

/* this function creates and returns the vector with the digits of the number,
knowing the dimension and the number of digits, it returns the pointer to the
vector */
int *preencheVectorDigit (int number, int dim, int nDigit);

/* this functions calculate the pow of each digit and sums them all */
int powDigits (int *nDigit, int nDigits);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* task to verify */
int i, dim, *digit, nDigit, mult, *test, step, j, answer = 0, number, found = 0;
char *v;

/* this vector will save the results of this function */
/* 0 if not processed, 1 if ending in 1, or 2 if ending in 89 */
v = (char*) calloc (DIM, sizeof (char));
if (v == NULL) {
	printf ("\nThere was a problem with the memory allocation of v.");
	return 0;
}

for (i = 1; i < DIM; i++) {
	if (v[i] == 1 || v[i] == 2) {
		/* the number was already processed */
		continue;
	}
	mult = 1;
	step = 0;
	found = 0;
	test = (int*) calloc (mult*SIZE, sizeof (int));
	if (test == NULL) {
		printf ("\nThere was a problem with the creation of the vector test.");
		return 0;
	}
	test[step] = i;
	while (test[step] != 1 && test[step] != 89) {
		dim = dimCalc (test[step], &nDigit);
		digit = preencheVectorDigit (test[step], dim, nDigit);
		if (digit == NULL) {
			printf ("\nThere was a problem with the creation of the vector digit.");
			return 0;
		}
		step++;
		if (step >= (mult*SIZE)) {
			mult++;
			test = (int*) realloc (test, mult*SIZE*sizeof (int));
			if (test == NULL) {
				printf ("\nThere was a problem with the realocation of the vector test.");
				return 0;
			}
		}
		test[step] = powDigits (digit, nDigit);
	}

	if (test[step] == 1) {
		for (j = 0; j < step; j++) {
			if (test[j] < DIM) {
				v[test[j]] = 1;
			}
		}
	} else if (test[step] == 89) {
		if (step == 0) {
			v[test[step]] = 2;
		}
		for (j = 0; j < step; j++) {
			if (test[j] < DIM) {
				v[test[j]] = 2;
			}
		}
	}
	if (step != 0) {
		free (test);
		free(digit);
	}
}
for (j = 1; j < DIM; j++) {
	if (v[j] == 2) {
		answer++;
	}
}
free (v);
/* end of the task */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThere are %d numbers ending in 89 until %d.", answer, DIM);
printf ("\n");
return 0;
}
/******************************************************************************/
int dimCalc (int number, int *nDigit) {
/* this function calculate the dimension of the number, and returns also the
number of digits of the counter by reference */
int dim = 1;
int res, nDigits = 1;
res = number / dim;
while (res > 9) {
  dim = dim * 10;
  nDigits++;
  res = number / dim;
}
*nDigit = nDigits;
return dim;
}
/******************************************************************************/
int *preencheVectorDigit (int number, int dim, int nDigit) {
/* this function creates and returns the vector with the digits of the number,
knowing the dimension and the number of digits, it returns the pointer to the
vector */
int *vectorDigit;
int i, j, mem = number, memD = dim;
vectorDigit = (int*) calloc (nDigit, sizeof (int));
if (vectorDigit == NULL) {
  return NULL;
}
for (i = 0; i < nDigit; i++) {
  vectorDigit[i] = number / dim;
  number = number - vectorDigit[i]*dim;
  dim = dim / 10;
}
return vectorDigit;
}
/******************************************************************************/
int powDigits (int *nDigit, int nDigits) {
/* this functions calculate the pow of each digit and sums them all */
int sum = 0, i, j;
for (i = 0; i < nDigits; i++) {
	sum = sum + pow(nDigit[i], 2);
}
return sum;
}
/******************************************************************************/
