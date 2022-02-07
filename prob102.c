#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZE 1000
#define NDATA 3
typedef struct {
  int x[NDATA];
  int y[NDATA];
  int xMin;
  int xMax;
  int yMin;
  int yMax;
  int booleanoContainTheOrigin; /* 0 if dont know, -1 if not or 1 if yes */
} triangle;

/* this function reads the data from the file into the pointer v, it returns
1 if the function went all ok, 0 if there was a problem in the function */
int readFile (FILE *f, triangle *v, int sizeData, int nElem);

/* this function sortes in ascending order of X the nElem points of a triangle,
and then returns 1 if it went all ok, or 0 if there was a problem in this
function */
int sortInAscendingOrderX (triangle *v, int size, int nElem);

/* this function fills the fields x and y min and man in the structure triangle,
and then, it returns 0 if there was a problem in the function, -1 if this
triangle don't contain the origin, or 1 if we still dont know */
int tracingParameteresXandY (triangle *v, int size, int nElem);

/* this function makes the calculation to know if a given triange in pos, has
the origin, if yes it returns 1, if not it returns -1, it there was a problem
in the function it returns 0 */
int booleanoCountainsTheOrigin (triangle *v, int pos, int nElem, int sizeMax);

/* this function makes the calculation of the area of a given triangle*2,
and then return the absolute value or -1 if there was a problem in the function */
int areaTriangleCalculation (int x1, int y1, int x2, int y2, int x3, int y3);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int i, j, booleano, sizeData = SIZE, nElem = NDATA, answer = 0;
FILE *f;
triangle *v;
char nameFile[15] = "triangles.txt";

v = (triangle*) calloc (sizeof(triangle), SIZE);
if (v == NULL) {
  printf ("\nThere was a problem in the creation of the array v.");
  return 0;
}
f = fopen (nameFile, "r");
if (f == NULL) {
  printf ("\nThere was a problem in the opening of the file.");
  return 0;
}
booleano = readFile (f, v, sizeData, nElem);
if (booleano == 0) {
  printf ("\nThere was a problem in the function readFile.");
  return 0;
}
booleano = sortInAscendingOrderX (v, sizeData, nElem);
if (booleano == 0) {
  printf ("\nThere was a problem in the function sortInAscendingOrderX.");
  return 0;
}
booleano = tracingParameteresXandY (v, sizeData, nElem);
if (booleano == 0) {
  printf ("\nThere was a problem in the function tracingParameteresXandY.");
  return 0;
}
for (i = 0; i < sizeData; i++) {
  if (v[i].booleanoContainTheOrigin == -1) {
    continue;
  }
  /* if it reaches here we must make further calculations */
  booleano = booleanoCountainsTheOrigin (v, i, nElem, sizeData);
  if (booleano == 0) {
    printf ("\nThere was a problem in the function booleanoCountainsTheOrigin.");
    return 0;
  } else if (booleano == 1) {
    /* then it contains the origin */
    /*printf ("\nTriangle %d countains the origin.\n", i);*/
    answer++;
  }
}
/* free memory */
fclose (f);
free(v);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThere are %d triangles that countain the origin.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int readFile (FILE *f, triangle *v, int sizeData, int nElem) {
/* this function reads the data from the file into the pointer v, it returns
1 if the function went all ok, 0 if there was a problem in the function */
if (f == NULL || v == NULL) {
  return 0;
}
int nData, i, j;
for (i = 0; i < sizeData; i++) {
  nData = 0;
  /* starting the value */
  v[i].booleanoContainTheOrigin = 0; /* dont know for now */
  for (j = 0; j < nElem; j++) {
    nData = (fscanf (f,"%d,", &v[i].x[j]));
    nData+=(fscanf (f,"%d,", &v[i].y[j]));
    if (nData != 2) {
      return 0;
    }
  }
}
/* if it reaches here it went all ok*/
return 1;
}
/******************************************************************************/
int sortInAscendingOrderX (triangle *v, int size, int nElem) {
/* this function sortes in ascending order of X the nElem points of a triangle,
and then returns 1 if it went all ok, or 0 if there was a problem in this
function */
if (v == NULL || size < 1 || nElem < 1) {
  return 0;
}
int xAux, yAux, i, j, k;
for (i = 0; i < size; i++) {
  for (j = 0; j < nElem; j++) {
    for (k = j+1; k < nElem; k++) {
      /* swap points */
      if (v[i].x[j] > v[i].x[k]) {
        /* aux = j */
        xAux = v[i].x[j];
        yAux = v[i].y[j];
        /* j = k */
        v[i].x[j] = v[i].x[k];
        v[i].y[j] = v[i].y[k];
        /* k = aux */
        v[i].x[k] = xAux;
        v[i].y[k] = yAux;
      }
    }
  }
}
return 1;
}
/******************************************************************************/
int tracingParameteresXandY (triangle *v, int size, int nElem) {
/* this function fills the fields x and y min and man in the structure triangle,
and then, it returns 0 if there was a problem in the function, or 1 if went all
ok */
if (v == NULL || size < 1 || nElem < 1) {
  return 0;
}
int i, j;
for (i = 0; i < size; i++) {
  for (j = 0; j < nElem; j++) {
    /* starting values */
    if (j == 0) {
      v[i].xMin = v[i].x[j];
      v[i].xMax = v[i].x[j];
      v[i].yMin = v[i].y[j];
      v[i].yMax = v[i].y[j];
    }
    /* x Parameter Control */
    if (v[i].xMin > v[i].x[j]) {
      /* new xMin */
      v[i].xMin = v[i].x[j];
    } else if (v[i].xMax < v[i].x[j]) {
      /* new xMax */
      v[i].xMax = v[i].x[j];
    }
    /* y Parameter Control */
    if (v[i].yMin > v[i].y[j]) {
      /* new yMin */
      v[i].yMin = v[i].y[j];
    } else if (v[i].yMax < v[i].y[j]) {
      /* new yMax */
      v[i].yMax = v[i].y[j];
    }
  }
  /* working the values min and max */
  if (!(v[i].xMin < 0 && v[i].xMax > 0 && v[i].yMin < 0 && v[i].yMax > 0)) {
    /* if it reaches here it dont contain the origin */
    v[i].booleanoContainTheOrigin = -1;
  }
}
return 1;
}
/******************************************************************************/
int booleanoCountainsTheOrigin (triangle *v, int pos, int nElem, int sizeMax) {
/* this function makes the calculation to know if a given triange in pos, has
the origin, if yes it returns 1, if not it returns -1, it there was a problem
in the function it returns 0 */
if (v == NULL || pos < 0 || pos >= sizeMax) {
  return 0;
}
int i, j, areaT = 0, areaOrigin = 0, parcel;
/* one more test, areas testing needed */
areaT = areaTriangleCalculation (v[pos].x[0], v[pos].y[0], v[pos].x[1], v[pos].y[1], v[pos].x[2], v[pos].y[2]);
if (areaT < 0) {
  printf ("\nThere was an error in the function areaTriangleCalculation.");
  return 0;
}
for (i = 0; i < nElem-1; i++) {
  for (j = i+1; j < nElem; j++) {
    parcel = areaTriangleCalculation (0, 0, v[pos].x[i], v[pos].y[i], v[pos].x[j], v[pos].y[j]);
    if (parcel < 0) {
      printf ("\nThere was an error in the function areaTriangleCalculation.");
      return 0;
    }
    areaOrigin+=parcel;
  }
}
if (areaT == areaOrigin) {
  return 1;
} else {
  return -1;
}
}
/******************************************************************************/
int areaTriangleCalculation (int x1, int y1, int x2, int y2, int x3, int y3) {
/* this function makes the calculation of the area of a given triangle*2,
and then return the absolute value or -1 if there was a problem in the function */
int area = 0;
area = x1*y2-x1*y3+x2*y3-x2*y1+x3*y1-x3*y2;
if (area < 0) {
  area*=-1;
}
return area;
}
/******************************************************************************/
