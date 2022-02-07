#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define M 50
#define MIN 1000000
#define SIZE 500

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int n = 0, m = M, min = MIN, f, fnMinus1=1, fnMinus2=1;
int data[SIZE] = {0}, sizeData = SIZE, nMin;
while (1) {
  /* starting value */
  if (n > m) {
    f = 2*fnMinus1-fnMinus2+data[n-m-1];
    /* storing data */
    fnMinus2 = fnMinus1;
    fnMinus1 = f;
  } else if (n == m) {
    f = 2;
    fnMinus1 = f;
  } else {
    f = 1;
  }
  /* storing data */
  data[n] = f;
  /* exit condition */
  if (f > min) {
    nMin = n;
    break;
  }
  /* advancing data */
  n++;
}
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nMinimum n is %d with F[n=%d] = %d.", nMin, nMin, f);
printf ("\n");
return 0;
}
/******************************************************************************/
