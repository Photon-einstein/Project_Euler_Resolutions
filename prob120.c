#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define AMAX 1000
#define AMIN 3

/* this function makes the calculation of the r max and then returns r max or
-1 if there was a problem in the function */
int resMaxCalc (int a);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int a, booleano, answer=0, aMin, aMax;
aMin = AMIN;
aMax = AMAX;
/* enter cycle */
for (a = aMin; a < aMax+1; a++) {
  booleano = resMaxCalc (a);
  if (booleano == -1) {
    printf("\nThere was a problem in the function resMaxCalc.");
    return 0;
  }
  answer+=booleano;
}
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThe sum of r max from a=%d to a=%d is %d", aMin, aMax, answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int resMaxCalc (int a) {
/* this function makes the calculation of the r max and then returns r max or
-1 if there was a problem in the function */
if (a == 0) {
  return -1;
}
int divider, left, right, leftOriginal, rightOriginal, firstR, maxR = -1, res, r;
int rPrevious = -1;
divider = pow (a,2);
/* first values for n=1 */
left = a-1;
right = a+1;
leftOriginal = left;
rightOriginal = right;
res = left + right;
firstR = res % divider;
if (maxR < firstR) {
  maxR = firstR;
}
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
  /* r max update */
  if (maxR < r) {
    maxR = r;
  } else if (r == firstR) {
    /* exit cycle */
    break;
  }
}
return maxR;
}
/******************************************************************************/
