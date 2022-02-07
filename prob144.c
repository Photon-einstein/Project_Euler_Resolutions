#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define XABSMAX 0.01
#define MI -14.07142857
#define BI 10.1
#define XLASTCOL 0.0
#define YLASTCOL 10.1
#define PI 3.1415926535

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
double yi, mi, bi, yr, mr, br, xMaxOut, a, b, c, x1, x2, y1, y2, ma;
double xLastCol, yLastCol, mt, tetaI, tetaT, tetaN, tetaR;
int nR = 0;
/* first line */
mi = MI;
bi = BI;
xMaxOut = XABSMAX;
xLastCol = XLASTCOL;
yLastCol = YLASTCOL;
/* enter cyle of reflections */
while (1) {
  /* calculation of the next hitting point */
  //printf("\nmi = %f, bi = %f", mi, bi);
  a = mi*mi+4;
  b = 2*mi*bi;
  c = bi*bi-100;
  //printf("\na = %f, b = %f, c = %f", a,b,c);
  x1 = (-b-sqrt(b*b-4*a*c))/(2*a);
  x2 = (-b+sqrt(b*b-4*a*c))/(2*a);
  y1 = mi*x1+bi;
  y2 = mi*x2+bi;
  if (fabs(xLastCol-x1) < fabs(xLastCol-x2)) {
    xLastCol = x2;
    yLastCol = y2;
  } else if (fabs(xLastCol-x1) > fabs(xLastCol-x2)) {
    xLastCol = x1;
    yLastCol = y1;
  } else {
    if (fabs(yLastCol-y1) <= fabs(yLastCol-y2)) {
      xLastCol = x2;
      yLastCol = y2;
    } else {
      xLastCol = x1;
      yLastCol = y1;
    }
  }
  //printf("\nxLastCol = %f, yLastCol = %f", xLastCol, yLastCol);
  /* test if we hit the exit */
  if (fabs(xLastCol) <= xMaxOut && yLastCol > 0) {
    //printf("\nnR = %d: xLastCol = %f, yLastCol = %f", nR, xLastCol, yLastCol);
    break;
  } else {
    /* one more reflection */
    nR++;
    //printf("\nnR = %d: xLastCol = %f, yLastCol = %f", nR, xLastCol, yLastCol);
  }
  /* reflection line calculation */
  mt = -4*xLastCol/yLastCol;
  tetaT = atan(mt)*180/PI;
  tetaI = atan(mi)*180/PI;
  ma = (mi-mt)/(1+mi*mt);
  mr = (mt-ma)/(1+mt*ma);
  br = yLastCol-mr*xLastCol;
  /* line reflected passes to incident line */
  mi = mr;
  bi = br;
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nIt took %d reflections before the laser went out.", nR);
printf("\n");
return 0;
}
/******************************************************************************/
