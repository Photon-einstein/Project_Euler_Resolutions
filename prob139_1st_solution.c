#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXPER 100000000
#define MMAX (-0.5+sqrt(MAXPER/2+0.25))

/* this function makes the calculation of the number of diferent triangles,
for a given primitive rectangular triangle as seed, valid for this problem,
knowing that perimeter < maxPerimeter, and then it returns in the end the
number of combinations or -1 if there was a problem in the function  */
int testTriangle(int x, int y, int z, int maxPerimeter);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int m, n, mMax = MMAX, answer = 0, x,y,z, boolean;
for (m = 2; m <= MMAX; m++) {
  for (n = 1; n < m; n++) {
    /* test primitive triangle */
    /* 1st test: parity of m and n must diferent */
    if ((m%2 == 0 && n%2 == 0)||(m%2!=0 && n%2!=0)){
      /* m and n have equal parity */
      continue;
    }
    /* 2nd test: x = y+1 */
    x = m*m-n*n;
    y = 2*m*n;
    if (x != (y+1) && x != (y-1)){
      continue;
    }
    /* if it reaches here then we have a new primitive triangle: */
    z = m*m+n*n;
    boolean = testTriangle (x, y, z, MAXPER);
    if (boolean == -1) {
      fprintf(stderr,"There was an error in the function testTriangle.");
      exit(1);
    }
    answer+=boolean;
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nUntil Perimeter <= %d, the number of Pythagorean triangles that", MAXPER);
printf("\nallow for such a tilling to take place are %d.", answer);
printf("\n");
return 0;
}
/******************************************************************************/
int testTriangle(int x, int y, int z, int maxPerimeter) {
/* this function makes the calculation of the number of diferent triangles,
for a given primitive rectangular triangle as seed, valid for this problem,
knowing that perimeter < maxPerimeter, and then it returns in the end the
number of combinations or -1 if there was a problem in the function  */
if (x < 1 || y < 1 || z < 1) {
  return -1;
}
int perimeter;
perimeter = x+y+z;
return ((maxPerimeter-1)/perimeter);
}
/******************************************************************************/
