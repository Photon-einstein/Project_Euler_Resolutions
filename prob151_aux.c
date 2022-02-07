#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define NREPS 1000000

/* this function makes the calculation of the number of times that the
supervisor has to pick to the envelope to grab the 14 A5 pieces between the 1st
and the last envelope, the 16th */
double test(void);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
long long int i, maxTries = NREPS;
long double sum=0, n;
/* rand initialization */
srand(time(NULL));
/* test of Monte Carlo */
for (i = 0; i < maxTries; ++i) {
  n = test();
  sum+=n;
}
/* average calculation */
sum/=maxTries;
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe expected number of times for the supervisor to find the A5 envelope is %.7Lf.", sum);
/* free memory */
printf("\n");
return 0;
}
/******************************************************************************/
double test(void) {
/* this function makes the calculation of the number of times that the
supervisor has to pick to the envelope to grab the 14 A5 pieces between the
1st and the last envelope, the 16th */
int v[4]={1,1,1,1}, n=0, n_single=0, maxN=4, i, j,test, sumTest;
double res;
char s[10000]="", aux[200];
while (n < 14) {
  test = rand()%maxN+1;
  /* test to see if we have the right envelope */
  for (i = 0, sumTest = 0; i < 4; ++i) {
    sumTest+=v[i];
    if (test <= sumTest) {
      break;
    }
  }
  if (maxN == 1) {
    ++n_single;
  }
  /* check if it is the right envelope */
  if (i >= 3) {
    /* we have found the right envelope */
    --v[i];
    --maxN;
  } else {
    --v[i];
    --maxN;
    for (j = i+1; j < 4; ++j) {
      ++v[j];
      ++maxN;
    }
  }
  /* count the number of times that the experience was made */
  ++n;
}
res = (double)n_single/n;
return res*14;
}
/******************************************************************************/
