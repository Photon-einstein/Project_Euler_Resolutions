#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXROW 1000000000

/* this function makes the calculation of all the valid
solution for up to 49 lines, 7x7 matrix, and in the end
it returns the new solutions */
long long int calcSol(long long int aHead, long long int nLines, long long int maxLine);

/* this function makes the return of the new a to start a new cycle */
long long int getNewA(long long int *v, long long int size);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
long long int aHead=1, a, aLine, i, j, found = 0, nLines=0, v[10]={0}, size = 10;
long long int sum=0, s;
while (nLines < MAXROW) {
  for (aLine = aHead, i = 0; i < 7; i++, aLine+=aHead) {
    for (a = aLine, j=0; j < 7; j++, a+=aLine) {
      s=calcSol(a, nLines, MAXROW);
      sum+=s;
      if ((MAXROW-nLines) <= 49) {
        found = 1;
        nLines = MAXROW;
        break;
      }
      nLines+=49;
      fflush(NULL);
    }
  }
  aHead = getNewA(v, size);
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe number of entries not divisible by 7 in the first %d rows of the\nPascal triangle are %lld.", MAXROW, sum);
printf("\n");
return 0;
}
/******************************************************************************/
long long int calcSol(long long int aHead, long long int nLines, long long int maxLine) {
/* this function makes the calculation of all the valid
solution for up to 49 lines, 7x7 matrix, and in the end
it returns the new solutions */
long long int sum = 0, s, a;
int i, n;
for (i = 0, a = aHead; i < 7; i++, a+=aHead) {
  if ((maxLine-nLines) > 7) {
    n = 7;
    nLines+=7;
  } else if ((maxLine-nLines) > 0) {
    n = maxLine-nLines;
    nLines = maxLine;
  } else {
    return sum;
  }
  s = n/2.0*(2*a+(n-1)*a);
  sum+=s;
}
return sum;
}
/******************************************************************************/
long long int getNewA(long long int *v, long long int size) {
/* this function makes the return of the new a to start a new cycle */
int i;
long long int res=1;
v[0]++;
for (i = 0; i < size-1; i++) {
  if (v[i] > 6) {
    v[i] = 0;
    v[i+1]++;
  }
  res*=(v[i]+1);
}
return res;
}
/******************************************************************************/
