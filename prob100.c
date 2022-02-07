#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MIN   1000000000000
#define XSTART 1
#define YSTART 1

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int count = 0;
unsigned long long int x0 = XSTART, y0 = YSTART, out = 0, min = MIN, x1, y1;
/* start of the initial values */
while (out == 0) {
  x1 = 3*x0+2*y0-2;
  y1 = 4*x0+3*y0-3;
  x0=x1;
  y0=y1;
  if (y0 > min) {
    out = 1;
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThe minimal blue discs that this would contain is %lld.", x0);
printf ("\n");
return 0;
}
/******************************************************************************/
