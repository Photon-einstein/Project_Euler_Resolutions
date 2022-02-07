#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int n2, n3, n4, found = 0, n5, n6, square;
int n1Square, n1, x, y, z, sum=0, xArg, yArg, zArg, diff, diffTest;
float xF,yF,zF;
/* test */
for (n3 = 3;found!=1 && n3 > 0; n3++) {
  for (n4 = n3-1; n4 > 1 && found!=1; n4--){
    /* z calc */
    zArg = (n3*n3-n4*n4);
    /* test parity of zArg */
    if (zArg % 2 != 0) {
      continue;
    }
    for (n2 = n4-1; n2 > 0 && found!=1; n2--){
      /* calc n1² */
      n1Square = n3*n3+n4*n4-n2*n2;
      n1 = roundl(sqrt((double)n1Square));
      n1*=n1;
      /* test n1 Square */
      if (n1 != n1Square) {
        /* no square found */ 
        continue;
      }
      /* x calc */
      xArg = (n1Square+n2*n2);
      /* test parity of xArg */
      if (xArg % 2 != 0) {
        continue;
      }
      /* y calc */
      yArg = (n1Square-n2*n2);
      /* test parity of yArg */
      if (yArg % 2 != 0) {
        continue;
      }
      /* speed up condition */
      if (yArg <= zArg) {
        break;
      } else if (n1Square < 0) {
        printf("\nOverflow.");
        exit(1);
      }
      /* x, y, z int calc */
      if (xArg%2!=0 || yArg%2!=0 || zArg%2!=0) {
        continue;
      }
      x = xArg/2;
      /* y calc */
      y = yArg/2;
      /* z calc */
      z = zArg/2;
      /* test y+z = n5² */
      square = y+z;
      n5 = roundl(sqrt((double)square));
      n5*=n5;
      /* test n5 Square */
      if (n5 != square) {
        /* no square found */
        continue;
      }
      /* test y-z = n6² */
      square = y-z;
      n6 = roundl(sqrt((double)square));
      n6*=n6;
      /* test n5 Square */
      if (n6 != square) {
        /* no square found */
        continue;
      }
      /* solution found */
      printf("\nNew solution found for: n1 = %d, n3 = %d, n4 = %d, n2 = %d", (int)sqrt(n1Square), n3, n4, n2);
      printf("\nx = %d, y = %d, z = %d", x, y, z);
      /* sum calc */
      sum = x+y+z;
      found = 1;
      break;
    }
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe minimal answer is sum = x+y+z = %d", sum);
printf("\n");
return 0;
}
/******************************************************************************/
