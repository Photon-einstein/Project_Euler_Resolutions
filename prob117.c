#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 50
#define NCOLOUR 4
typedef struct {
  int repColour; /* tile number, for each colour */
} colourID;
typedef struct {
  colourID colourV[NCOLOUR];
  int sizeColour; /* number of diferent colour in the colourV */
} combTile;

/* this function makes the creation of the pascal triangle of size dim*dim,
and then returns 1 if all went ok or 0 if there was a problem in the function */
int pascalTriangleCreation (long long int **pascalV, int dim);

/* this function makes the calculation of the maxTileRep per colour, and
then return maxSizeArray if all went ok or 0 if there was a problem in the
function */
int maxTileColourCalc (int *maxTileColour, int nColour, int dim);

/* this function makes the fulling of the combV array in the position = realSize,
then it sorts in descending order of size, and returns 1 if all went ok, or 0 if
there was a problem in the function */
int fullingComV (combTile *combV, int realSize, int *indexColour, int nColour);

/* this function sorts in descending order the array in the colourV, and then
return 1 if all went ok or 0 if there was a problem in the function */
int sortDescendingOrder (colourID *colourV, int sizeColour);

/* this function makes the calculation of the answer using the array combV and
the array pascalV, and then returns the answer or -1 if there was a problem in
the function */
long long int answerCalc (combTile *combV, int realSize, long long int **pascalV);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
long long int **pascalV, answer=0;
int dim = DIM, i,j, booleano, indexColour[NCOLOUR], maxTileColour[NCOLOUR];
int nColour = NCOLOUR, maxSizeArrayCombV, realSizeCombV=0;
combTile *combV;
/* pascal array creation */
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
/* pascal array fulling */
booleano = pascalTriangleCreation (pascalV, dim);
if (booleano == 0) {
  printf ("\nThere was a problem in the function pascalTriangleCreation.");
  return 0;
}
/* maxCalculation */
booleano = maxTileColourCalc (maxTileColour, nColour, dim);
if (booleano == 0) {
  printf("\nThere was a problem in the function maxTileColour.");
  return 0;
}
/* array creation */
maxSizeArrayCombV = booleano/10;
combV = (combTile*) calloc (maxSizeArrayCombV, sizeof (combTile));
if (combV == NULL) {
  printf("\nThere was a problem in the memory allocation of combV.");
}
/* cycle */
for (indexColour[0] = 0; indexColour[0] < maxTileColour[0]+1; indexColour[0]++) {
  for (indexColour[1] = 0; indexColour[1] < maxTileColour[1]+1; indexColour[1]++) {
    /* seed cycle 1 */
    booleano = indexColour[0]+indexColour[1]*2;
    if (booleano > dim) { break; }
    for (indexColour[2] = 0; indexColour[2] < maxTileColour[2]+1; indexColour[2]++) {
      /* seed cycle 2 */
      booleano = indexColour[0]+indexColour[1]*2+indexColour[2]*3;
      if (booleano > dim) { break; }
      for (indexColour[3] = 0; indexColour[3] < maxTileColour[3]+1; indexColour[3]++) {
          /* seed cycle 3 */
          booleano = indexColour[0]+indexColour[1]*2+indexColour[2]*3+indexColour[3]*4;
          if (booleano > dim) {
            break;
          } else if (booleano == dim) {
            /* fulling values in array comV */
              booleano = fullingComV (combV, realSizeCombV, indexColour, nColour);
              if (booleano == 0) {
                printf("\nThere was a problem in the function fullingCombV.");
                return 0;
              }
              realSizeCombV++;
          } else {
            continue;
          }
      }
    }
  }
}
/* reallocation of the extra memory */
combV = (combTile*) realloc (combV, realSizeCombV*sizeof (combTile));
if (combV == NULL) {
  printf("\nThere was an error in the reallocation of combV.");
  return 0;
}
/* answer calc */
answer = answerCalc (combV, realSizeCombV, pascalV);
if (answer == -1) {
  printf("\nThere was an erro in the function answerCalc.");
  return 0;
}
/* free memory */
for (i = 0; i < dim; i++) {
  free (pascalV[i]);
}
free (pascalV);
free (combV);
printf ("\n");
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nFor a row of %d tile there are %lld diferent combinations.", dim, answer);

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
int maxTileColourCalc (int *maxTileColour, int nColour, int dim) {
/* this function makes the calculation of the maxTileRep per colour, and
then return maxSizeArray if all went ok or 0 if there was a problem in the
function */
if (maxTileColour == NULL || nColour < 1 || dim < 1) {
  return 0;
}
int i, size = 1, maxSize = 1;
for (i = 0; i < nColour; i++) {
  maxTileColour[i] = dim/size;
  size++;
  maxSize*=maxTileColour[i];
  if (maxSize <0) {
    return 99999999;
  }
}
return maxSize;
}
/******************************************************************************/
int fullingComV (combTile *combV, int realSize, int *indexColour, int nColour) {
/* this function makes the fulling of the combV array in the position = realSize,
then it sorts in descending order of size, and returns 1 if all went ok, or 0 if
there was a problem in the function */
if (combV == NULL || indexColour == NULL || realSize < 0 || nColour < 0) {
  return 0;
}
int i,j, nColourSize = 0, booleano;
/* fulling */
for (i = 0; i < nColour; i++) {
  combV[realSize].colourV[i].repColour = indexColour[i];
  if (indexColour[i] != 0) {
    nColourSize++;
  }
}
combV[realSize].sizeColour = nColourSize;
/* sorting in descending order */
booleano = sortDescendingOrder (combV[realSize].colourV, nColour);
if (booleano == 0) {
  printf("\nThere was an error in the function sortDescendingOrder.");
  return 0;
}
return 1;
}
/******************************************************************************/
int sortDescendingOrder (colourID *colourV, int sizeColour) {
/* this function sorts in descending order the array in the colourV, and then
return 1 if all went ok or 0 if there was a problem in the function */
if (colourV == NULL || sizeColour < 0) {
  return 0;
}
int i, j;
colourID aux;
for (i = 0; i < sizeColour-1; i++) {
  for (j = i+1; j < sizeColour; j++) {
    if (colourV[i].repColour < colourV[j].repColour) {
      /* aux = i */
      aux.repColour = colourV[i].repColour;
      /* i = j */
      colourV[i].repColour = colourV[j].repColour;
      /* j = aux */
      colourV[j].repColour = aux.repColour;
    }
  }
}
return 1;
}
/******************************************************************************/
long long int answerCalc (combTile *combV, int realSize, long long int **pascalV) {
/* this function makes the calculation of the answer using the array combV and
the array pascalV, and then returns the answer or -1 if there was a problem in
the function */
if (combV == NULL || pascalV == NULL || realSize < 1) {
  return -1;
}
long long int answer = 0;
int i, p1, p2, p3, n1, n2, n3;
for (i = 0 ; i < realSize; i++) {
  if (combV[i].sizeColour == 1) {
    /* 1 colour */
    answer++;
  } else if (combV[i].sizeColour == 2) {
    /* 2 colour */
    p1 = combV[i].colourV[0].repColour+combV[i].colourV[1].repColour;
    n1 = combV[i].colourV[1].repColour;
    answer+=pascalV[p1][n1];
  } else if (combV[i].sizeColour == 3) {
    /* 3 colour */
    p1 = combV[i].colourV[0].repColour+combV[i].colourV[1].repColour+combV[i].colourV[2].repColour;
    n1 = combV[i].colourV[1].repColour+combV[i].colourV[2].repColour;
    p2 = combV[i].colourV[1].repColour+combV[i].colourV[2].repColour;
    n2 = combV[i].colourV[1].repColour;
    answer+=pascalV[p1][n1]*pascalV[p2][n2];
  } else {
    /* 4 colour */
    p1 = combV[i].colourV[0].repColour+combV[i].colourV[1].repColour+combV[i].colourV[2].repColour+combV[i].colourV[3].repColour;
    n1 = combV[i].colourV[1].repColour+combV[i].colourV[2].repColour+combV[i].colourV[3].repColour;
    p2 = combV[i].colourV[1].repColour+combV[i].colourV[2].repColour+combV[i].colourV[3].repColour;
    n2 = combV[i].colourV[2].repColour+combV[i].colourV[3].repColour;
    p3 = combV[i].colourV[2].repColour+combV[i].colourV[3].repColour;
    n3 = combV[i].colourV[2].repColour;
    answer+=pascalV[p1][n1]*pascalV[p2][n2]*pascalV[p3][n3];
  }
}
return answer;
}
/******************************************************************************/
