#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXPER 10000
#define MMAX (-0.5+sqrt(MAXPER/2+0.25))

/* Iterative binary algorithm - gcd */
int gcd_iter(int u, int v);

/* this function makes the test of z²mod(y-x)=0 given a given pair of primitive
triangle generator,that generates all the triangles until perimeter<maxPerimeter
is false, returning the number of diferent solutions if all went ok, or -1 if
there was a problem in the function */
int testTriangle(int m, int n, int maxPerimeter);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int m, n, mMax = MMAX, answer = 0, x,y,z, boolean;
//printf("\nmMax = %d", mMax);
for (m = 2; m <= MMAX; m++) {
  for (n = 1; n < m; n++) {
    /* test primitive triangle */
    /* 1st test: parity of m and n must diferent */
    if ((m%2 == 0 && n%2 == 0)||(m%2!=0 && n%2!=0)){
      /* m and n have equal parity */
      continue;
    }
    /* 2nd test: gcd(m,n) must be 1 to exist a primitive triangle */
    boolean = gcd_iter(m,n);
    if (boolean!=1) {
      continue;
    }
    /* if it reaches here then we have a new primitive triangle: */
    boolean = testTriangle (m, n, MAXPER);
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
int gcd_iter(int u, int v) {
  if (u < 0) u = -u;
  if (v < 0) v = -v;
  if (v) while ((u %= v) && (v %= u));
  return (u + v);
}
/******************************************************************************/
int testTriangle(int m, int n, int maxPerimeter){
/* this function makes the test of z²mod(y-x)=0 given a given pair of primitive
triangle generator,that generates all the triangles until perimeter<maxPerimeter
is false, returning the number of diferent solutions if all went ok, or -1 if
there was a problem in the function */
if (m < 1 || n < 1 || m <= n || maxPerimeter < 1) {
  return -1;
}
int k=1, x,y,z, count=0, perimeter, xPrim, yPrim, zPrim;
xPrim = (m*m-n*n);
yPrim = (2*m*n);
zPrim = (m*m+n*n);
while (1) {
  x = k*xPrim;
  y = k*yPrim;
  z = k*zPrim;
  perimeter = x+y+z;
  /* test break condition */
  if (perimeter >= maxPerimeter) {
    /* end of test */
    return count;
  }
  /* test of a new solution */
  if (z % (y-x) == 0) {
    count++;
    if (k == 1) {
      printf("\nNew solution: k = %d, (%d, %d, %d)", k, x, y, z);
    }
  }
  /* next k */
  k++;
}
}
/******************************************************************************/
