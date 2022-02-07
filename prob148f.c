#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXROW 1000000

/* this function makes the calculation of all the valid
solution for up to 49 lines, 7x7 matrix, and in the end
it returns the new solutions */
long long int calcSol(long long int aHead, long long int nLines, long long int maxLine);

int main () {
clock_t inicio, fim;
double tempo;
FILE *f;
f = fopen("fast.text", "w+");
if (f == NULL) {
  return 0;
}
inicio = clock();
/* work to verify */
long long int aHead=1, aStart=1, loop=0, a, aLine, i, j, found=0, nl;
long long int sum=0, nLines=0,s, reset=0, nReset=0;
while (nLines < MAXROW) {
  for (aLine = aHead, i = 0; i < 7; i++, aLine+=aHead) {
    for (a = aLine, j=0; j < 7; j++, a+=aLine) {
      //printf("%lld\t", a);
      s=calcSol(a, nLines, MAXROW);
      sum+=s;
      if ((MAXROW-nLines) <= 49) {
        found = 1;
        nLines = MAXROW;
        break;
      }
      nLines+=49;
      fprintf(f,"\nLine= %lld\ta = %lld\ts = %lld\tsumA = %lld\ti=%lld\tloop=%lld\tnReset=%lld\treset=%lld", nLines, a,s,sum,i,loop, nReset, reset);
      fflush(NULL);
    }
    if (found == 1) {
      break;
    }
    fprintf(f,"\n");
  }
  aHead+=aStart;
  loop++;
  if (loop==7) {
    loop=0;
    aStart+=reset+1;
    nReset++;
    if (nReset==7) {
      nReset=0;
      reset++;
      aStart=reset+1;
    }
    if (aStart==8 && reset==0) {
      aStart=2;
      reset++;
    }
    aHead=aStart;
  }
  if (reset == 7) {
    reset=1;
    loop=0;
    aStart = 2;
    aHead = aStart;
  }
  fprintf(f,"\n");
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
fprintf(f,"\nTempo em segundos: %lf", tempo);
fprintf(f,"\nThe number of entries not divisible by 7 in the first %d rows of the\nPascal triangle are %lld.", MAXROW, sum);
fprintf(f,"\n");
return 0;
}
/******************************************************************************/
long long int calcSol(long long int aHead, long long int nLines, long long int maxLine) {
/* this function makes the calculation of all the valid
solution for up to 49 lines, 7x7 matrix, and in the end
it returns the new solutions */
long long int sum = 0, s, a, i, n;
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
