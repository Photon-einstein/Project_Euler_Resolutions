#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 99 /* n not nBounce until 10^DIM */
#define INDEXMAX 10
typedef struct {
  long long int vA[INDEXMAX]; /* for each digit of 10^dim, it says how many bouncy
                        numbers it generates, in ascending type of non bouncy */
  long long int vD[INDEXMAX]; /* for each digit of 10^dim, it says how many bouncy
                        numbers it generates, in descending type of non bouncy */
} nonBouncy;

/* this function makes the calculation of all the ascending nonBouncy number
that are in the array v, with the index i and the digit j, and then it returns
the number or -1 if there was an error in the function */
long long int calcAscendingNonBouncyDigit (nonBouncy *v, int i, int j, int dim, int indexMax);

/* this function makes the calculation of all the descending nonBouncy number
that are in the array v, with the index i and the digit j, and then it returns
the number or -1 if there was an error in the function */
long long int calcDescendingNonBouncyDigit (nonBouncy *v, int i, int j, int dim, int indexMax);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int dim = DIM, i,j, indexMax = INDEXMAX, nDigit = DIM+1;
long long int ans = 0, ansA = 0, ansD = 0, discount = 0;
nonBouncy *v;
/* start of the array */
v = (nonBouncy*) calloc (nDigit, sizeof (nonBouncy));
if (v == NULL) {
  printf("\nThere was an error in the memory allocation of v array.");
  return 0;
}
/* starting values */
v[1].vA[0] = 0;
v[1].vD[0] = 0;
/* ascending starting up */
for (i = 1; i < 10; i++) {
  v[1].vA[i] = 9-i+1;
}
/* descending starting up */
for (i = 1; i < 10; i++) {
  v[1].vD[i] = i+1;
}
/* cycle begins */
for (i = 2; i < dim+1; i++) {
  /* if it reaches here then it is i > 0 */
  for (j = 1; j < indexMax; j++) {
    v[i].vA[j] = calcAscendingNonBouncyDigit (v, i, j, dim, indexMax);
    if (v[i].vA[j] == -1) {
      printf("\nThere was an error in the function calcAscendingNonBouncyDigit.");
      return 0;
    }
    v[i].vD[j] = calcDescendingNonBouncyDigit (v, i, j, dim, indexMax);
    if (v[i].vD[j] == -1) {
      printf("\nThere was an error in the function calcDescendingNonBouncyDigit.");
      return 0;
    }
  }
}
/* answer calc */
for (i = 1; i < dim+1; i++) {
  for (j = 1; j < indexMax; j++) {
    ansA+=v[i].vA[j];
    ansD+=v[i].vD[j];
  }
}
/* equal digit number repeated, must be discounted and first 9 digits must be
counted */
discount = 9*dim-9;
ans = ansA+ansD-discount;
/* free memory */
free (v);
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThere are %lld non bouncy numbers until 10^%d.", ans, dim);
printf ("\n");
return 0;
}
/******************************************************************************/
long long int calcAscendingNonBouncyDigit (nonBouncy *v, int i, int j, int dim, int indexMax) {
/* this function makes the calculation of all the ascending nonBouncy number
that are in the array v, with the index i and the digit j, and then it returns
the number or -1 if there was an error in the function */
if (v == NULL || i < 0 || i > dim || j < 0 || j > indexMax-1) {
  return -1;
}
long long int res = 0;
int k;
if (j == 0) {
  return 0;
}
for (k = j; k < indexMax; k++) {
  res+=v[i-1].vA[k];
}
return res;
}
/******************************************************************************/
long long int calcDescendingNonBouncyDigit (nonBouncy *v, int i, int j, int dim, int indexMax) {
/* this function makes the calculation of all the descending nonBouncy number
that are in the array v, with the index i and the digit j, and then it returns
the number or -1 if there was an error in the function */
if (v == NULL || i < 0 || i > dim || j < 0 || j > indexMax-1) {
  return -1;
}
long long int res = 0;
int k;
for (k = j; k > 0; k--) {
  res+=v[i-1].vD[k];
}
/* all zero count */
res++;
return res;
}
/******************************************************************************/
