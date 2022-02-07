#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define PERCENTAGE 99
#define SIZEV 20

/* this function makes the sum of the array a with size nAlg and max size
nAlgMax, and then returns *nAlgDigitUpBool = 1 if nAlg is up or 0 is not, and
returns 1 if all went ok or 0 if there was a problem in the function */
int iterativeSum (int *a, int b, int nAlg, int nAlgMax, int *nAlgDigitUpBool);

/* this function makes test of increasing digits starting in 0 until nAlg-1,
and the returns 1 if increasing, 0 if not or -1 if there was a problem in this
function */
int testIncreasingValues (int *v, int nAlg);

/* this function makes test of decreasing digits starting in nAlg-1 until 0,
and the returns 1 if decreasing, 0 if not or -1 if there was a problem in this
function */
int testDecreasingValues (int *v, int nAlg);

/* this function makes the test of out of cycle and return 1 if we can get off
cycle or 0 if not yet */
int testOutOfCycle (int n, int nBounce, int percentage);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int n, nBounce = 0, *v, percentage = PERCENTAGE, answer, realSize;
int nAlgMax = SIZEV, nAlg, nAlgDigitUpBool, booleano, found, booleano2;
int b = 1;
/* array creation */
v = (int*) calloc (nAlgMax, sizeof (int));
if (v == NULL) {
  printf("\nThere was an error in the function v.");
  return 0;
}
/* starting values */
/* numbers below 100 all increasing or decreasing */
v[2]++;
nAlg = 3;
n = 100;
/* enter infinite cycle */
while (1) {
  /* test bouncy number */
  booleano = testIncreasingValues (v, nAlg);
  if (booleano == -1) {
    printf("\nThere was a problem in the function testIncreasingValues.");
    return 0;
  }
  /* shortcut path, no bouncy number found */
  if (booleano == 0) {
    booleano2 = testDecreasingValues (v, nAlg);
    if (booleano2 == -1) {
      printf("\nThere was a problem in the function testIncreasingValues.");
      return 0;
    }
    /* test bouncy found */
    if (booleano == 0 && booleano2 == 0) {
      nBounce++;
    }
  }
  /* test out of cycle */
  booleano = testOutOfCycle (n, nBounce, percentage);
  if (booleano == 1) {
    /* answer found */
    answer = n;
    break;
  }
  /* new test number worked out */
  booleano = iterativeSum (v, b, nAlg, nAlgMax, &nAlgDigitUpBool);
  if (booleano == 0) {
    printf ("\nThere was a problem in the function iterativeSum.");
    return 0;
  }
  n++;
  /* new size calc */
  if (nAlgDigitUpBool == 1) {
    nAlg++;
  }
}
/* free memory */
free (v);
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThe minimal n for %d%% of bouncy number is %d.", percentage, answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int iterativeSum (int *a, int b, int nAlg, int nAlgMax, int *nAlgDigitUpBool) {
/* this function makes the sum of the array a with size nAlg and max size
nAlgMax, and then returns *nAlgDigitUpBool = 1 if nAlg is up or 0 is not, and
returns 1 if all went ok or 0 if there was a problem in the function */
int carry = 0, i;
a[0]+=b;
//printf("\na = ");
for (i = 0; i < nAlg; i++) {
  //printf("%d", a[nAlg-i-1]);
  a[i] = a[i] + carry;
  if (a[i] > 9) {
    carry = a[i] / 10;
    a[i] = a[i] % 10;
  } else {
    carry = 0;
  }
}
if (carry != 0) {
  if (nAlgMax >= (nAlg+1)) {
    a[i] = carry;
    *nAlgDigitUpBool = 1;
  } else {
    printf("\nSum Overflow.");
    return 0;
  }
} else {
  *nAlgDigitUpBool = 0;
}
return 1;
}
/******************************************************************************/
int testIncreasingValues (int *v, int nAlg) {
/* this function makes test of increasing digits starting in 0 until nAlg-1,
and the returns 1 if increasing, 0 if not or -1 if there was a problem in this
function */
if (v == NULL || nAlg < 1) {
  return -1;
}
int i, j;
for (i = 0; i < nAlg-1; i++) {
  if (v[i] > v[i+1]) {
    return 0;
  }
}
/* if it reaches here then it is an increasing number */
return 1;
}
/******************************************************************************/
int testDecreasingValues (int *v, int nAlg) {
/* this function makes test of decreasing digits starting in nAlg-1 until 0,
and the returns 1 if decreasing, 0 if not or -1 if there was a problem in this
function */
if (v == NULL || nAlg < 1) {
  return -1;
}
int i, j;
for (i = 0; i < nAlg-1; i++) {
  if (v[i] < v[i+1]) {
    return 0;
  }
}
/* if it reaches here then it is a decreasing number */
return 1;
}
/******************************************************************************/
int testOutOfCycle (int n, int nBounce, int percentage) {
/* this function makes the test of out of cycle and return 1 if we can get off
cycle or 0 if not yet */
if ((nBounce*100)/n == percentage && (n*percentage) == (nBounce*100)) {
  return 1;
} else {
  return 0;
}
}
/******************************************************************************/
