#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 50

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
long long int fnMinus2 = 2, fnMinus1 = 4, fn, answer = 0;
int step = 4, dim = DIM;
/* calc res */
if (dim < 3) {
  fn = 1;
} else if (dim == 3) {
  fn = 2;
} else if (dim == 4) {
  fn = 4;
} else {
  while (1) {
    /* +1 */
    fn = fnMinus2 + fnMinus1 + 1;
    fnMinus2 = fnMinus1;
    fnMinus1 = fn;
    step++;
    if (step == dim) {
      break;
    }
    /* - */
    fn = fnMinus2 + fnMinus1;
    fnMinus2 = fnMinus1;
    fnMinus1 = fn;
    step++;
    if (step == dim) {
      break;
    }
    /* -1 */
    fn = fnMinus2 + fnMinus1 - 1;
    fnMinus2 = fnMinus1;
    fnMinus1 = fn;
    step++;
    if (step == dim) {
      break;
    }
    /* -1 */
    fn = fnMinus2 + fnMinus1 - 1;
    fnMinus2 = fnMinus1;
    fnMinus1 = fn;
    step++;
    if (step == dim) {
      break;
    }
    /* - */
    fn = fnMinus2 + fnMinus1;
    fnMinus2 = fnMinus1;
    fnMinus1 = fn;
    step++;
    if (step == dim) {
      break;
    }
    /* +1 */
    fn = fnMinus2 + fnMinus1 + 1;
    fnMinus2 = fnMinus1;
    fnMinus1 = fn;
    step++;
    if (step == dim) {
      break;
    }
  }
}
answer = fn;
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThere are %lld diferent configurations.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
