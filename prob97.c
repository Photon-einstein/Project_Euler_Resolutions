#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZEPOWER 7830457
#define SIZEANSWER 2357207

/* this function calculate the dimension of the count, and returns the nDigit of
the count number */
int dimCalc (int count, int *nDigit);

/* it makes the multiplication of the number vNum*nTeste and then it returns the
new nDigit, or -1 if there was a problem */
int multiplication (int *vNum, int nTest, int nDigits);


/* this function makes the sum of a[] = a[] + c and the returns to the main */
void sumIterativSimplified (int *a, int c, int nDigit);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int *v, sizePow, i, nDigit, mult = 2, j;


v = (int*) calloc (10, sizeof(int));
if (v == NULL) {
  printf ("\nThere was an error in the creation of the vector v.");
  return 0;
}

/* start of the array */
v[0] = 2;
nDigit = 1;
for (sizePow = 2; sizePow < SIZEPOWER+1; sizePow++) {
  nDigit = multiplication (v, 2, 10);
  if (nDigit == -1) {
    printf ("\nThere was a problem in the function multiplicacao.");
    return 0;
  }
}
nDigit = multiplication (v, 28433, 10);
sumIterativSimplified (v, 1, 10);
printf ("\nAnswer: ");
for (i = 9; i > -1; i--) {
  printf ("%d", v[i]);
}

/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\n");
return 0;
}
/******************************************************************************/
int dimCalc (int count, int *nDigit) {
/* this function calculate the dimension of the count, and returns the nDigit of
the count number */
int dim = 1;
int res, nDigitos = 1;
res = count / dim;
while (res > 9) {
  dim = dim * 10;
  nDigitos++;
  res = count / dim;
}
*nDigit = nDigitos;
return dim;
}
/******************************************************************************/
int multiplication (int *vNum, int nTest, int nDigits) {
/* it makes the multiplication of the number vNum*nTeste and then it returns the
new nDigit, or -1 if there was a problem */
if (vNum == NULL) {
  return -1;
}
int i, carry = 0, dim, nAlg, nAlgMax;
carry = 0;
for (i = 0; i < nDigits; i++) {
  vNum[i] = vNum[i] * nTest + carry;
  if (vNum[i] < 10) {
    carry = 0;
  } else {
    carry = vNum[i] / 10;
    vNum[i] = vNum[i] % 10;
  }
}
return i;
}
/******************************************************************************/
void sumIterativSimplified (int *a, int c, int nDigit) {
/* this function makes the sum of a[] = a[] + c and the returns to the main */
int carry = 0, i;
/* start of the sum */
a[0] = a[0] + c;
for (i = 0; i < nDigit; i++) {
  if (a[i] > 9) {
    carry = a[i] / 10;
    a [i] = a[i] % 10;
  } else {
    carry = 0;
  }
}
return;
}
/******************************************************************************/
