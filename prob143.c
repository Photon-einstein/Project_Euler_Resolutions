#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXSUM 120000

typedef struct {
  int r;
  int q;
} id;

/* this function makes the testing if a given number is a square, 1 return,
or not, 0 returned */
int testSquare (long long int s);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int boolean, count=0, nPseudoSol=0, *solution;
id *memVal;
long long int p, q, r, s, s1, s2, s3, i, sum=0;
/* memory allocation */
memVal = (id*) calloc(MAXSUM*10, sizeof(id));
if (memVal == NULL) {
  printf("\nError in memory allocation.");
  exit(1);
}
solution = (int*) calloc(MAXSUM+1, sizeof(int));
if (solution == NULL) {
  printf("\nError in memory allocation.");
  exit(1);
}
r=1;
/* loop cycle */
while (1) {
  for (q=1;(r+q) <= MAXSUM && q <= MAXSUM/2 && q <= r; q++) {
      /* test 1 */
      s = r*r+r*q+q*q;
      s2 = s;
      boolean = testSquare(s);
      if (boolean == 0) {
        continue;
      }
      /* new pseudo-solution found */
      memVal[nPseudoSol].r=r;
      memVal[nPseudoSol].q=q;
      nPseudoSol++;
  }
  /* break condition of outer loop */
  if ((r+2) > MAXSUM) {
    break;
  } else {
    /* new cyle */
    r++;
  }
}
for (i = 0; i < nPseudoSol; i++) {
  r = memVal[i].r;
  q = memVal[i].q;
  for (p=1;(r+q+p) <= MAXSUM && p <= MAXSUM/3 && p <= q; p++) {
    /* test 2 */
    s = p*p+p*r+r*r;
    s1 = s;
    boolean = testSquare(s);
    if (boolean == 0) {
      continue;
    }
    /* test 3 */
    s = q*q+q*p+p*p;
    s3 = s;
    boolean = testSquare(s);
    if (boolean == 0) {
      continue;
    } else if (solution[p+q+r] == 0) {
      solution[p+q+r] = 1;
      sum+=p+q+r;
      count++;
      //printf("\ncount = %d; p=%lld; q=%lld; r=%lld; s1=%lld; s2=%lld; s3=%lld; sum = %lld;", count, p, q, r, s1, s2, s3, sum);
      //fflush(NULL);
    }
  }
}
/* free memory */
free(memVal);
free(solution);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThere are %d diferent of p+q+r <= %d for Torricelli triangles with sum = %lld.", count, MAXSUM, sum);
printf("\n");
return 0;
}
/******************************************************************************/
int testSquare (long long int s) {
/* this function makes the testing if a given number is a square, 1 return,
or not, 0 returned */
double r;
long long int sGuess;
r = sqrt ((double)s);
sGuess = r;
if (sGuess == r) {
  return 1;
} else {
  return 0;
}
}
/******************************************************************************/
