#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define XMAX 47
#define YMAX 43

/* this function makes the calculation of the number of possible rectangles
and in the end ir returns the number of rectangles, ortogonal and diagonal */
unsigned int countRectangles(unsigned int xMax, unsigned int yMax);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
unsigned int x,y, res, sum=0;
for (x = 1; x <= XMAX; x++) {
  for (y = 1; y <= YMAX && y <= x; y++) {
    res = countRectangles(x,y);
    if (y <= XMAX && x <= YMAX && x != y) {
      sum+=res*2;
    } else {
      sum+=res;
    }
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe number of different rectangles that could be situated within %dx%d\nand smaller grids is %u", XMAX, YMAX, sum);
printf("\n");
return 0;
}
/******************************************************************************/
unsigned int countRectangles(unsigned int xMax, unsigned int yMax) {
/* this function makes the calculation of the number of possible rectangles
and in the end ir returns the number of rectangles, ortogonal and diagonal */
int x,y, alfaA, alfaD;
float xB, yB;
int sum=0;
/* rectangle ortogonal */
for (x = 0; x < xMax; x++) {
  for (y = 0; y < yMax; y++) {
    sum+=(xMax-x)*(yMax-y);
  }
}
/* diagonal rectangles */
for (xB = 0; xB <= xMax-0.5; xB+=0.5) {
  for (yB = 0; yB <= yMax-0.5; yB+=0.5) {
    if ((xB == trunc(xB) && yB != trunc(yB)) || (xB != trunc(xB) && yB == trunc(yB))) {
      continue;
    }
    for (alfaA = 1; xB-alfaA/2.0 >= 0 && yB+alfaA/2.0<=yMax ;alfaA++) {
      for (alfaD = 1; xB+alfaD/2.0 <= xMax && yB+alfaD/2.0 <= yMax && yB+alfaA/2.0+alfaD/2.0 <= yMax;alfaD++) {
        sum++;
      }
    }
  }
}
return sum;
}
/******************************************************************************/
