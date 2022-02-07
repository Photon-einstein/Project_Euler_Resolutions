#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 50

/* this function makes the creation of the pascal triangle of size dim*dim,
and then returns 1 if all went ok or 0 if there was a problem in the function */
int pascalTriangleCreation (long long int **pascalV, int dim);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
long long int **pascalV, answer=0;
int dim = DIM, i, booleano, n, p;
pascalV = (long long int**) calloc (dim, sizeof (long long int*));
if (pascalV == NULL) {
  printf("\nThere was an error in the memory allocation of pascalV.");
}
for (i = 0; i < dim; i++) {
  pascalV[i] = (long long int *) calloc (dim, sizeof (long long int));
  if (pascalV[i] == NULL) {
    printf("\nThere was an error in the memory allocation of pascalV[i].");
  }
}
booleano = pascalTriangleCreation (pascalV, dim);
if (booleano == 0) {
  printf ("\nThere was a problem in the function pascalTriangleCreation.");
  return 0;
}
/* red calc */
n = dim-1;
p = 1;
while (1) {
  answer+=pascalV[n][p];
  n--;
  p++;
  /* exit condition */
  if (n < p){
    break;
  }
}
/* green calc */
n = dim-2;
p = 1;
while (1) {
  answer+=pascalV[n][p];
  n-=2;
  p++;
  /* exit condition */
  if (n < p){
    break;
  }
}
/* blue calc */
n = dim-3;
p = 1;
while (1) {
  answer+=pascalV[n][p];
  n-=3;
  p++;
  /* exit condition */
  if (n < p){
    break;
  }
}
/* free memory */
for (i = 0; i < dim; i++) {
  free (pascalV[i]);
}
free (pascalV);
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThere are %lld ways of sorting the row of dim = %d.", answer, dim);
printf ("\n");
return 0;
}
/******************************************************************************/
int pascalTriangleCreation (long long int **pascalV, int dim){
/* this function makes the creation of the pascal triangle of size dim*dim,
and then returns 1 if all went ok or 0 if there was a problem in the function */
if (pascalV == NULL || dim < 1) {
  return 0;
}
int i, j;
for (i = 0; i < dim; i++) {
  /* starting value */
  if (i == 0) {
    pascalV[0][0] = 1;
    continue;
  }
  for (j = 0; j < i+1; j++) {
    if (j == 0) {
      pascalV[i][j] = 1;
    } else {
      pascalV[i][j] = pascalV[i-1][j-1]+pascalV[i-1][j];
    }
  }
}
return 1;
}
/******************************************************************************/
