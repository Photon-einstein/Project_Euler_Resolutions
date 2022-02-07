#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAX 30

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int count = 0;
long long int aF, aproxSq, res, sum=0;
double sq;
for (aF = 1; count < MAX; aF++) {
  res = 5*aF*aF+14*aF+1;
  if (res < 0) {
    printf("\n");
    //printf("\nOverflow\n");
    exit(1);
  }
  sq = roundl(sqrt(res));
  aproxSq = (long long int) sq;
  aproxSq*=aproxSq;
  if (aproxSq == res) {
    count++;
    sum+=aF;
    printf("\nAG(%d) = %lld", count, aF);
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\n");
return 0;
}
/******************************************************************************/
