#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define GOAL 18
#define DIFF 0.0000000001
typedef struct {
  double value;
  int nCapacitors;
} capID;

/* this function makes the calculation of the number of different values up to
goal capacitors and in the end returns the result or -1 if there was a problem
with the function */
int resCalc (int goal);

/* this function makes the search of a check of equal value of a given capacitor
and in the end it return 1 if there is a check with a given capacitor, 0 if it
is a new capacitor value or -1 if there was a problem in the function */
int checkRepeatedCapacitor(capID *c, int dim, double diff, double newC);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int res=0, goal = GOAL;
res = resCalc(goal);
if (res == -1) {
  printf("\nThere was a problem in the function.");
  return 0;
}
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nThe number of different values up to %d capacitors is %d.", goal, res);
printf("\n");
return 0;
}
/******************************************************************************/
int resCalc (int goal) {
/* this function makes the calculation of the number of different values up to
goal capacitors and in the end returns the result or -1 if there was a problem
with the function */
if (goal < 0) {
  return -1;
}
double diff = DIFF, newC;
capID *c;
int maxdim=10000000, mult=1, dim=0, i, j, oldDim, found, k;
if (goal == 0) {
  return 0;
}
/* memory allocation */
c = (capID*) calloc(maxdim, sizeof (capID));
if (c == NULL) {
  printf("\nThere was an error in the memory allocation of c.");
  return -1;
}
/* first cycle */
/* 1 capacitor */
c[0].value=60;
c[0].nCapacitors=1;
++dim;
/* 2 capacitors */
c[1].value=30;
c[1].nCapacitors=2;
++dim;
c[2].value=120;
c[2].nCapacitors=2;
++dim;
for (i = 2; i < goal; ++i) {
  oldDim = dim;
  for (j = 0; j < oldDim; ++j) {
    for (k = j+1; k < oldDim; ++k) {
        if (c[j].nCapacitors+c[k].nCapacitors > i+1) {
          break;
        } else if (c[j].nCapacitors+c[k].nCapacitors < i+1) {
          continue;
        }
        /* generating paralel dynamic capacitors */
        newC = c[j].value+c[k].value;
        /* search of repeated value of capacitors */
        found = checkRepeatedCapacitor(c, dim, diff, newC);
        if (found == -1) {
          printf("\nThere was an error in the function checkRepeatedCapacitor.");
          return -1;
        } else if (found == 0) {
          /* new value to insert */
          if (dim == maxdim) {
            /* memory reallocation */
            ++mult;
            maxdim*=mult;
            c = (capID*) realloc(c, maxdim*sizeof (capID));
            if (c == NULL) {
              printf("\nThere was an error in the reallocation of c.");
              return -1;
            }
          }
          /* new value to insert */
          c[dim].value = newC;
          c[dim].nCapacitors = i+1;
          ++dim;
        }
        /* generating series dynamic capacitors */
        newC = (c[j].value*c[k].value)/(c[j].value+c[k].value);
        /* search of repeated value of capacitors */
        found = checkRepeatedCapacitor(c, dim, diff, newC);
        if (found == -1) {
          printf("\nThere was an error in the function checkRepeatedCapacitor.");
          return -1;
        } else if (found == 0) {
          /* new value to insert */
          if (dim == maxdim) {
            /* memory reallocation */
            ++mult;
            maxdim*=mult;
            c = (capID*) realloc(c, maxdim*sizeof (capID));
            if (c == NULL) {
              printf("\nThere was an error in the reallocation of c.");
              return -1;
            }
          }
          c[dim].value = newC;
          c[dim].nCapacitors = i+1;
          ++dim;
      }
    }
  }
  printf("\nD(%d) = %d", i+1, dim);
  /*for (j = 0; j < dim; ++j) {
    printf("%.1f ", c[j].value);
  }*/
  fflush(NULL);
}
/* free memory */
free(c);
return dim;
}
/******************************************************************************/
int checkRepeatedCapacitor(capID *c, int dim, double diff, double newC) {
/* this function makes the search of a check of equal value of a given capacitor
and in the end it return 1 if there is a check with a given capacitor, 0 if it
is a new capacitor value or -1 if there was a problem in the function */
if (c == NULL || dim < 1) {
  return -1;
}
int k, found;
for (k = 0, found = 0; k < dim; ++k) {
  if (fabs(newC-c[k].value) < diff) {
    found = 1;
    return found;
  }
}
return found;
}
/******************************************************************************/
