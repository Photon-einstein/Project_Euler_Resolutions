#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define SIZEARRAY 12
#define SIZEANSWER 12

/* this function makes the creation of Ln = xn^2+y^2 and then stores Ln at the
location pos = start + i, i = 0, 1 , ..., size-1, and then it returns 1 if all
ok or 0 if there was a problem in the function */
int fillArray (int x1, int y1, long long int *v, int start, int size);

/* this function returns the answer if all ok or 0 if there was a problem in
the function */
long long int answerCalc(long long int *v, int size);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int x1, y1, sizeArray, boolean, start, size, sizeAnswer;
long long int answer, *v;
/* memory allocation */
sizeArray = SIZEARRAY;
v = (long long int*) calloc(sizeArray, sizeof (long long int));
if (v == NULL) {
  exit(1);
}
/* array fulling, for eq 1: h = b + 1 */
x1 = 1;
y1 = 0;
start = 0;
size = sizeArray/2;
boolean = fillArray (x1, y1, v, start, size);
if (boolean == 0) {
  printf("\nThere was an error in the function fillArray.");
  exit(1);
}
/* array fulling, for eq 2: h = b - 1 */
x1 = 0;
y1 = 1;
start = sizeArray/2;
size = sizeArray;
boolean = fillArray (x1, y1, v, start, size);
if (boolean == 0) {
  printf("\nThere was an error in the function fillArray.");
  exit(1);
}
/* sorting and answer calc */
sizeAnswer = SIZEANSWER;
answer = answerCalc(v, sizeAnswer);
if (answer == 0){
  exit(1);
}
/* free memory */
free(v);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe sum of the first %d L elements is %lld.", SIZEANSWER, answer);
printf("\n");
return 0;
}
/******************************************************************************/
int fillArray (int x1, int y1, long long int *v, int start, int size) {
/* this function makes the creation of Ln = xn^2+y^2 and then stores Ln at the
location pos = start + i, i = 0, 1 , ..., size-1, and then it returns 1 if all
ok or 0 if there was a problem in the function */
if (v == NULL || start > size || start < 0 || size < 0) {
    return 0;
}
int i;
long long int xbefore, ybefore, x, y;
x = x1;
y = y1;
for (i = start; i < size; i++) {
  /* save x n-1 and y n-1 */
  xbefore = x;
  ybefore = y;
  /* new x and y calc */
  x = 17*xbefore + 4*ybefore;
  y = 4*xbefore + ybefore;
  /* new L at pos i */
  v[i] = x*x+y*y;
}
return 1;
}
/******************************************************************************/
long long int answerCalc(long long int *v, int size) {
/* this function returns the answer if all ok or 0 if there was a problem in
the function */
int i, j;
long long int aux, answer = 0;
/* sorting until sizeAnswer th element */
for (i = 0; i < size; i++) {
  /* sum calc */
  answer+=v[i];
}
return answer;
}
/******************************************************************************/
