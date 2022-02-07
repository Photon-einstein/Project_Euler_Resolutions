#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX 50
#define MIN 0
#define SIZE 20000

/* this function sortes by size, in descending order a vector if dim elements */
void sorting (int *v, int dim);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* task to check */
int x1, x2, y1, y2, v[3], count = 0, dim, sizeC, booleano, nAlg, booleano2;

for (x1 = MIN; x1 <= MAX; x1++) {
  for (x2 = MIN; x2 <= MAX; x2++) {
    for (y1 = MIN; y1 <= MAX; y1++) {
        for (y2 = MIN; y2 <= MAX; y2++) {
          /* test if the points are equal */
          if (x1 == x2 && y1 == y2) {
            continue;
          }
					/* points equal to the origin */
					if ( (x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0) ) {
						continue;
					}
          v[0] = pow(x2,2)+pow(y2,2);
          v[1] = pow((x2-x1),2)+pow((y2-y1),2);
          v[2] = pow(x1,2)+pow(y1,2);
          sorting (v,3);
          /* square triangle test */
          if (v[0] == (v[1]+v[2])) {
            /* there is a rectangular triangle, now we have to check if there
            are any repetitions */
            count++;
          }

        }
    }
  }
}
count/=2;
/* end of task */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThere are %d triangles in this situation.", count);
printf ("\n");
return 0;
}
/******************************************************************************/
void sorting (int *v, int dim) {
/* this function sortes by size, in descending order a vector if dim elements */
int i, j, aux;
for (i = 0; i < dim-1; i++){
  for (j = i+1; j < dim; j++) {
    if (v[i] < v[j]) {
      /* swap positions */
      /* aux = i */
      aux = v[i];
      /* i = j */
      v[i] = v[j];
      /* j = aux */
      v[j] = aux;
    }
  }
}
return;
}
/******************************************************************************/
