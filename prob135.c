#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXN 1000000
#define MAXD 1000000
#define MAXAN 749999
#define NGOAL 10

/* this function makes the fulling of the array answer, and then it returns 1 if
all ok or 0 if there was a problem in the function */
int fillArray (char *answer, int maxN);

/* this solution counts the number of diferent positions of the array answer
that have nGoal solutions, for an array if size = dim, and then it returns the
number of solutions or -1 if there was an error in the function */
int answerCalc(char *answer, int dim, int nGoal);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int boolean, maxN;
char *answer;
/* dinamic allocation */
answer = (char*) calloc(MAXN, sizeof (char));
assert(answer!=NULL);
maxN = MAXN;
/* fill array answer */
boolean = fillArray(answer, maxN);
if (boolean == 0) {
  printf("\nThere was an error in the function.");
}
/* answer calc */
boolean = answerCalc(answer, maxN, NGOAL);
if (boolean == -1) {
  printf("\nThere was an error in the function answerCalc.");
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\n%d values of n less than %d have exactly %d distinct solutions.", boolean, MAXN, NGOAL);
/* free memory */
free(answer);
printf("\nTempo em segundos: %lf", tempo);
printf("\n");
return 0;
}
/******************************************************************************/
int fillArray (char *answer, int maxN) {
/* this function makes the fulling of the array answer, and then it returns 1 if
all ok or 0 if there was a problem in the function */
long long int boolean = 0, d, an, n;
for (an = 1; an < MAXAN; an++) {
  for (d = 1+an/3; d < MAXD; d++) {
    /* pos calc */
    n = (an+d)*(3*d-an);
    if (n >= maxN) {
      /* array boundary reached */
      break;
    } else {
      /* new valid value reached, overflowing avoid */
      answer[n]++;
    }
  }
}
return 1;
}
/******************************************************************************/
int answerCalc(char *answer, int dim, int nGoal) {
/* this solution counts the number of diferent positions of the array answer
that have nGoal solutions, for an array if size = dim, and then it returns the
number of solutions or -1 if there was an error in the function */
if (answer == NULL || dim < 1 || nGoal < 0) {
  return -1;
}
int count = 0, i;
for (i = 0; i < dim; i++) {
  if (answer[i] == nGoal) {
    count++;
  }
}
return count;
}
/******************************************************************************/
