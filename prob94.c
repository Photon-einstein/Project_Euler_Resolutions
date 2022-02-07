#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define LMAX 1000000000

/* this function returns the greathest commmon denominator between the integrer
numbers a and b, if returns 1 them the numbers a and b are coprime */
int gcd (int u, int v);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int m, n, a, b, c, out = 0, booleano, imparesTds, l, res, contador = 0;
int spCase, k, perimeterMax, perimeter, answer = 0;
int aM, bM, cM, lMax, newPerimeter;
float area;

perimeterMax = (float)(LMAX/1000)*623+1;
m = 1;
lMax = LMAX;
lMax = sqrt(10*lMax)/3;
while (m < lMax) {
  m++;
  for (n = 1; n < m; n++) {
    booleano = gcd (m, n);
    if ((m % 2 != 0 && n % 2 != 0) || (m % 2 == 0 && n % 2 == 0))  {
      /* we have to discard the situation when all are even or all are odd
      numbers */
      /* situation when we have all numbers even or all odd */
      imparesTds = 1;
    } else {
      /* at least one number is even */
      imparesTds = 0;
    }

    if (booleano == 1 && imparesTds == 0)  {
      /* in this case we have another primitive triplet */
      a = m*m - n*n;
      b = 2*m*n;
      c = m*m + n*n;
      l = a+b+c;
      if (l > LMAX) {
        break;
      }
      /* initial conditions */
      k = 1;
      perimeter = a+b+c;
      aM = a;
      bM = b;
      cM = c;
      while (perimeter < perimeterMax) {
        /* we are now going to separate this in two possible triangles */
        if ((2*a) == (c+1)) {
          /* we are going to have a triangle c-c-2a whith c=2a-1*/
          newPerimeter = 2*a+2*c;
          if (newPerimeter <= LMAX) {
            answer = answer + 2*a+2*c;
          }
        } else if ((2*a) == (c-1)) {
          /* we are going to have a triangle c-c-2a whith c=2a+1*/
          newPerimeter = 2*a+2*c;
          if (newPerimeter <= LMAX) {
            answer = answer + 2*a+2*c;
          }
        } else if ((2*b) == (c+1)) {
          /* we are going to have a triangle c-c-2b whith c=2b-1*/
          newPerimeter = 2*a+2*b;
          if (newPerimeter <= LMAX) {
            answer = answer + 2*b+2*c;
          }
        } else if ((2*b) == (c-1)) {
          /* we are going to have a triangle c-c-2b whith c=2b+1*/
          newPerimeter = 2*a+2*b;
          if (newPerimeter <= LMAX) {
            answer = answer + 2*b+2*c;
          }
        }
        k++;
        a = k*aM;
        b = k*bM;
        c = k*cM;
        perimeter = a+b+c;
      }

    }
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nThe answer is: %d.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int gcd (int u, int v) {
/* this function returns the greathest commmon denominator between the integrer
numbers a and b, if returns 1 them the numbers a and b are coprime */
  if (u < 0) u = -u;
  if (v < 0) v = -v;
  if (v) while ((u %= v) && (v %= u));
  return (u + v);
}
/******************************************************************************/
