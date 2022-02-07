#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define NMIN 7039
#define MINEXP 10

/* this function makes the calculation of the r in pos n and then returns r in
pos n or-1 if there was a problem in the function */
long long int resMaxCalc (int a, int n);

/* this function see if there is a solution for this problem, if yes then it
returns 1, if not yet, then it returns 0, if there was a problem it returns -1 */
int answerCalc (int nTest, int n, int rExp);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int n = 0, nTest, answer, rExp, nMin, boolean;
long long int pSquare, rTest;
char nameFile[20] = "PrimeList";
FILE *f;
rExp = MINEXP;
nMin = NMIN;
rTest = pow(10, rExp);
f = fopen (nameFile, "r");
if (f == NULL) {
  printf("\nThere was a problem in the opening of the file.");
  return 0;
}
while (1) {
  /* prime test */
  boolean = fscanf (f, "%d", &nTest);
  n++;
  if (boolean == 0) {
    printf("\nEnd of file.");
    return 0;
  }
  /* if it reaches here then it is a prime number */
  if ((n < nMin) || (n % 2 == 0)) {
    /* not yet big enough or n even */
    continue;
  }
  /* if it reaches here then it is a prime number and > 7037 and n odd */
  /* nTest^2 must be > pow (10, rExp) */
  pSquare = pow(nTest,2);
  if (pSquare < rTest) {
    /* remainder not big enough for sure */
    continue;
  }
  boolean = answerCalc (nTest, n, rExp);
  if (boolean == -1) {
    printf("\nThere was a problem in the function answerCalc.");
    return 0;
  } else if (boolean == 0) {
    /* solution not yet found */
    continue;
  } else {
    /* solution found */
    answer = n;
    break;
  }
}
fclose (f);
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThe least value for which r exceeds 10^%d is %d.", rExp, answer);
printf ("\n");
return 0;
}
/******************************************************************************/
long long int resMaxCalc (int a, int n) {
/* this function makes the calculation of the r in pos n and then returns r in
pos n or-1 if there was a problem in the function */
if (a == 0) {
  return -1;
}
long long int divider, left, right, leftOriginal, rightOriginal, firstR, res, r;
long long int *v;
int dim = 100, mult = 1, realSize = 0, pos;
/* v allocation */
v = (long long int*) calloc (dim, sizeof (long long int));
if (v == NULL) {
  return -1;
}
divider = pow (a,2);
/* first values for n=1 */
left = a-1;
right = a+1;
leftOriginal = left;
rightOriginal = right;
res = left + right;
firstR = res % divider;
v[realSize] = firstR;
realSize++;
/* enter infinite cycle */
while (1) {
  /* next values */
  left*=leftOriginal;
  right*=rightOriginal;
  /* downsizing */
  left = left % divider;
  right = right % divider;
  res = left + right;
  r = res % divider;
  /* remainder update */
  if ((realSize+1) == dim) {
    /* reallocation */
    mult++;
    dim*=mult;
    v = (long long int*) realloc (v,dim*sizeof (long long int));
    if (v == NULL) {
      return -1;
    }
  }
  v[realSize] = r;
  realSize++;
  /* exit cycle test */
  if (r == firstR || realSize > n) {
    /* exit cycle */
    break;
  }
}
/* realSize++ discount */
realSize--;
/* complete cycle calculated */
if (realSize < n) {
  pos = n%realSize-1;
} else {
  pos = n-1;
}
r = v[pos];
/* free memory */
free (v);
return r;
}
/******************************************************************************/
int answerCalc (int nTest, int n, int rExp) {
/* this function see if there is a solution for this problem, if yes then it
returns 1, if not yet, then it returns 0, if there was a problem it returns -1 */
long long int rTest, r;
rTest = pow (10, rExp);
r = resMaxCalc (nTest, n);
if (r == -1) {
  printf("\nThere was a problem in the function resMaxCalc.");
  return -1;
} else if (r > rTest) {
  return 1 ;
} else {
  return 0;
}
}
/******************************************************************************/
