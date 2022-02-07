#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define NSTART 1000003
#define AMIN 1000001

/* this function makes the calculation of the A(n) and then returns the
value or 0 if there was a problem in this function */
int aCalc (int n);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int n, aMin, found = 0, a;
/* starting values */
n = NSTART;
aMin = AMIN;
while(!found) {
  if (n%5!=0) {
    a = aCalc (n);
    if (a == 0) {
      printf("\nThere was a problem in the function aCalc.");
      return 0;
    }
    if (a > aMin) {
      found = n;
    }
  }
  /* next n */
  n+=2;
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe least value of n for wich A(n) first exceeds 1M is %d.", found);
printf("\n");
return 0;
}
/******************************************************************************/
int aCalc (int n) {
/* this function makes the calculation of the A(n) and then returns the
value or 0 if there was a problem in this function */
if (n <= 0 || n % 5 == 0 || n % 2 == 0) {
  return 0;
}
int x = 1, k = 1;
while (x!=0) {
  x = x*10 +1;
  x = x % n;
  k++;
}
return k;
}
/******************************************************************************/
