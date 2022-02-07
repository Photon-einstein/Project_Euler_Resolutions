#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define EXP 12
#define MAXNUMBER (long int)roundl(pow(10.0,EXP))
#define RMAX 20.0
#define MAGICNUMBER 432

/* this function makes the test of a new triplet, for members of a consecutive
progressive sequence, and returns 1 if yes, 0 if not, and -1 if there was a
problem in the function */
long int testTripet (long int x, long int y, long int z, double r21, long int n);

/* this function allocates memory for int array and then fill the array with
square, cube and multiples of magicNumber, and then it returns the number of
elements of the given array or NULL if there was a problem in the function, and
also returns, using the pointer, the real value of the array */
int* getXArray(int xMax, int magicNumber, int *xArraySize);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
long int maxSquare = MAXNUMBER, nTest, sum=0, boolean, yy;
double r21, r32;
int x,y,z, xMax, yMax, yGuess, out=0, *xArray, xArraySize, i;
xMax = sqrt(maxSquare);
yMax = xMax+1;
/* test triplets */
/* x < y < z */
/* getting array of x numbers square and cube and multiples of 512 until xMax */
xArray = getXArray(xMax, MAGICNUMBER, &xArraySize);
if (xArray==NULL) {
  printf("\nThere was a problem in the function getXArray");
  exit(1);
}
for (i = 0;i < xArraySize; i++) {
  /* x must be a square or cube number */
  /* break test */
  nTest = (long int)(xArray[i]+2)*(xArray[i]+1)+xArray[i];
  for (y = xArray[i]+1;y < yMax;y++) {
    if (y%2!=0 && y%75!=0) {
      continue;
    }
    /* break test */
    nTest = (long int)y*(y+1)+xArray[i];
    if (nTest >= maxSquare) {break;}
    /* r21 calc */
    r21 = (double)y/xArray[i];
    if (r21 > RMAX) {break;}
    /* z calc */
    z = roundl(y*r21);
      /* break test */
      nTest = (long int)y*z+xArray[i];
      if (nTest >= maxSquare) {break;}
      /* d*d = q*r, so q = d*d/r */
      yy = (long int)y*y;
      if (yy%xArray[i] != 0) {continue;}
      /* test triplet, for members of a geometric progression */
      boolean = testTripet ((long int)xArray[i],(long int)y,(long int)z, r21, nTest);
      if (boolean == -1) {
        printf("\nThere was a problem in the function testTripet.");
        exit(1);
      } else if (boolean == 0) {
        /* no new triplet found */
        continue;
      }
      /* insert new triplet answer */
      sum+=boolean;
      //printf(" with sum = %ld", sum);
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe sum of all progressive perfect squares below 100k (10^%d) is %ld.", EXP, sum);
printf("\n");
/* free memory */
free (xArray);
return 0;
}
/******************************************************************************/
long int testTripet (long int x, long int y, long int z, double r21, long int n) {
/* this function makes the test of a new triplet, for members of a consecutive
progressive sequence, and returns 1 if yes, 0 if not, and -1 if there was a
problem in the function, x < y < z */
if (x < 1) {
  return -1;
}
double r32;
long int nRoot;
/* r calc */
/*x < y < z */
r32 = (double)z/y;
if (r21 == r32) {
  /* n = d.q + r */
  /* test: r < d < q */
  nRoot = round(sqrt((double)n));
  nRoot*=nRoot;
  if (n == nRoot) {
    //printf("\nNew square: %ld with: n = %ld*%ld+%ld and r = %f", n, y, z, x, r21);
    return n;
  }
}
return 0;
}
/******************************************************************************/
int* getXArray(int xMax, int magicNumber, int *xArraySize) {
/* this function allocates memory for int array and then fill the array with
square, cube and multiples of magicNumber, and then it returns the number of
elements of the given array or NULL if there was a problem in the function, and
also returns, using the pointer, the real value of the array */
if (xMax < 1 | xArraySize == NULL || magicNumber <= 0) {
  return NULL;
}
int *x, realSize=0, i, j, n, size=0, aux, subtract=0;
x = (int*)calloc(xMax, sizeof (int));
if (x == NULL) {
  return NULL;
}
/* square number */
for (i = 1;; i++) {
  /* square calc */
  n = i*i;
  if (n > xMax) {
    break;
  }
  x[size] = n;
  size++;
}
/* cube number */
for (j = 2;; j++, j++) {
  /* square calc */
  n = j*j*j;
  if (n > xMax) {
    break;
  }
  x[size] = n;
  size++;
}
/* magic number*multiple^3 */
for (j = 1;; j++) {
  /* square calc */
  n = j*j*j*magicNumber;
  if (n > xMax) {
    break;
  }
  x[size] = n;
  size++;
}
/* memory reallocation */
x = (int*) realloc(x, size*sizeof (int));
if (x == NULL) {
  return NULL;
}
for (i = 0; i < size-1; i++) {
  for (j = i+1; j < size; j++) {
    /* equal members */
    if (x[i] == x[j]) {
      x[j] = xMax;
      subtract++;
    }
  }
}
/* sorting array */
for (i = 0; i < size-1; i++) {
  for (j = i+1; j < size; j++) {
    if (x[i] > x[j]) {
      /* aux = i */
      aux = x[i];
      /* i = j */
      x[i] = x[j];
      /* j = aux */
      x[j] = aux;
    }
  }
}
/* size update */
*xArraySize = size-subtract;
printf("\nThere are %d elements", size);
return x;
}
/******************************************************************************/
