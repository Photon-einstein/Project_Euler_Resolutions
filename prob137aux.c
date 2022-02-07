#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAX 15

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int count = 0;
long long int aF, aproxSq, res;
double sq;
for (aF = 1; count < MAX; aF++) {
  res = 5*aF*aF+2*aF+1;
  if (res < 0) {
    printf("\nOverflow");
    exit(1);
  }
  sq = roundl(sqrt(res));
  aproxSq = (long long int) sq;
  aproxSq*=aproxSq;
  if (aproxSq == res) {
    count++;
    printf("\nAF%d = %lld", count, aF);
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
