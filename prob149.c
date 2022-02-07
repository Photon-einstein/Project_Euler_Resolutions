#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define DIM 2000

/* this function makes the fulling of the array v and s, and in the end
it returns 1 if all went ok or 0 if there was a problem in the function */
int numberGenerator(int *s, int **v, int nRow);

/* this function makes the calculation of the maxSum and in the end it returns
the value or -1 if there was a problem in the function */
long long int calcMaxSum(int **s, int nRow);

/* this function makes the calculation of the maxSum in the horizontal and in
the end it returns the value or -1 if there was a problem in the function */
long long int horCalcMaxSum(int **s, int nRow);

/* this function makes the calculation of the maxSum in the vertical and in
the end it returns the value or -1 if there was a problem in the function */
long long int vertCalcMaxSum(int **s, int nRow);

/* this function makes the calculation of the maxSum in the diagonal and in
the end it returns the value or -1 if there was a problem in the function */
long long int diagCalcMaxSum(int **s, int nRow);

/* this function makes the calculation of the maxSum in the anti diagonal and
in the end it returns the value or -1 if there was a problem in the function */
long long int antiDiagCalcMaxSum(int **s, int nRow);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int i, j, *s, **v, nRow=DIM, boolean;
long long int maxSum;
/* memory allocation */
s = (int*) calloc(nRow*nRow+1, sizeof(int));
if (s == NULL) {
  return 0;
}
v = (int**) calloc(nRow, sizeof(int*));
if (v == NULL) {
  return 0;
}
for (i = 0; i < nRow; ++i) {
  v[i] = (int*) calloc(nRow, sizeof(int));
  if (v[i] == NULL) {
    return 0;
  }
}
/* fulling matrix */
boolean = numberGenerator(s, v, nRow);
if (boolean == 0) {
  printf("\nThere was an error in the function numberGenerator.");
}
/* test sum */
maxSum = calcMaxSum(v, nRow);
if (maxSum < 0) {
  printf("\nThere was a problem in the function calcMaxSum.");
  return 0;
}
/* free memory */
free(s);
for (i = 0; i < nRow; ++i) {
  free(v[i]);
}
free(v);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nThe max sum with square matrix %d is %lld.", nRow, maxSum);
printf("\nTempo em segundos: %lf", tempo);
printf("\n");
return 0;
}
/******************************************************************************/
int numberGenerator(int *s, int **v, int nRow) {
/* this function makes the fulling of the array v and s, and in the end
it returns 1 if all went ok or 0 if there was a problem in the function */
/* number generation */
if (s == NULL || v == NULL || nRow < 1) {
  return 0;
}
int i, j;
long long int k=1;
for (i = 0; i < nRow; ++i) {
  for (j = 0; j < nRow; ++j) {
    if (k <= 55) {
      s[k] = (100003-200003*k+300007*k*k*k)%1000000 - 500000;
    } else {
      s[k] = (s[k-24]+s[k-55]+1000000)%1000000-500000;
    }
    v[i][j] = s[k];
    k++;
  }
}
return 1;
}
/******************************************************************************/
long long int calcMaxSum(int **s, int nRow) {
/* this function makes the calculation of the maxSum and in the end it
returns the value or -1 if there was a problem in the function */
if (s == NULL || nRow < 1) {
  return -1;
}
int method;
long long int sumMax = 0, sum;
/* method: 0 - hor, 1 - vert, 2 - diag, 3 - antidiag */
/* horizontal search */
for (method = 0; method < 4; ++method) {
  if (method == 0) {
    sum = horCalcMaxSum(s, nRow);
    if (sum == -1) {
      printf("\nThere was an error in the function horCalcMaxSum.");
      return -1;
    }
  } else if (method == 1) {
    sum = vertCalcMaxSum(s, nRow);
    if (sum == -1) {
      printf("\nThere was an error in the function horCalcMaxSum.");
      return -1;
    }
  } else if (method == 2) {
    sum = diagCalcMaxSum(s, nRow);
    if (sum == -1) {
      printf("\nThere was an error in the function horCalcMaxSum.");
      return -1;
    }
  } else {
    sum = antiDiagCalcMaxSum(s, nRow);
    if (sum == -1) {
      printf("\nThere was an error in the function horCalcMaxSum.");
      return -1;
    }
  }
  if (sum > sumMax) {
    sumMax = sum;
  }
}
return sumMax;
}
/******************************************************************************/
long long int horCalcMaxSum(int **s, int nRow) {
/* this function makes the calculation of the maxSum in the horizontal and in
the end it returns the value or -1 if there was a problem in the function */
if (s == NULL || nRow < 1) {
  return -1;
}
int line, colun;
long long int sum, sumMax=0;
for (line = 0; line < nRow; ++line) {
  sum = 0;
  for (colun = 0; colun < nRow; ++colun) {
    sum+=s[line][colun];
    if (sum < 0) {
      sum = 0;
    } else if (sum > sumMax) {
      sumMax = sum;
    }
  }
}
return sumMax;
}
/******************************************************************************/
long long int vertCalcMaxSum(int **s, int nRow) {
/* this function makes the calculation of the maxSum in the horizontal and in
the end it returns the value or -1 if there was a problem in the function */
if (s == NULL || nRow < 1) {
  return -1;
}
int line, colun;
long long int sum, sumMax=0;
for (colun = 0; colun < nRow; ++colun) {
  sum=0;
  for (line = 0; line < nRow; ++line) {
    sum+=s[line][colun];
    if (sum < 0) {
      sum=0;
    } else if (sum > sumMax) {
      sumMax = sum;
    }
  }
}
return sumMax;
}
/******************************************************************************/
long long int diagCalcMaxSum(int **s, int nRow) {
/* this function makes the calculation of the maxSum in the diagonal and in
the end it returns the value or -1 if there was a problem in the function */
if (s == NULL || nRow < 1) {
  return -1;
}
int lineStart, colunStart, line, colun;
long long int sum, sumMax=0;
/* first colun process */
for (colunStart=0, lineStart=nRow-1; lineStart >= 0; --lineStart) {
  sum = 0;
  for (line = lineStart, colun = colunStart; line < nRow && colun < nRow; ++line, ++colun) {
    sum+=s[line][colun];
    if (sum < 0) {
      sum=0;
    } else if (sum > sumMax) {
      sumMax = sum;
    }
  }
}
/* first line process */
for (colunStart=1, lineStart=0; colunStart < nRow; ++colunStart) {
  sum = 0;
  for (line = lineStart, colun = colunStart; line < nRow && colun < nRow; ++line, ++colun) {
    sum+=s[line][colun];
    if (sum < 0) {
      sum=0;
    } else if (sum > sumMax) {
      sumMax = sum;
    }
  }
}
return sumMax;
}
/******************************************************************************/
long long int antiDiagCalcMaxSum(int **s, int nRow) {
/* this function makes the calculation of the maxSum in the anti diagonal and
in the end it returns the value or -1 if there was a problem in the function */
if (s == NULL || nRow < 1) {
  return -1;
}
int lineStart, colunStart, line, colun;
long long int sum, sumMax=0;
/* first colun process */
for (colunStart=0, lineStart=nRow-1; lineStart >= 0; --lineStart) {
  sum = 0;
  for (line = lineStart, colun = colunStart; line >= 0 && colun < nRow; --line, ++colun) {
    sum+=s[line][colun];
    if (sum < 0) {
      sum=0;
    } else if (sum > sumMax) {
      sumMax = sum;
    }
  }
}
/* first line process */
for (colunStart=1, lineStart=0; colunStart < nRow; ++colunStart) {
  sum = 0;
  for (line = lineStart, colun = colunStart; line < nRow && colun >= 0; ++line, --colun) {
    sum+=s[line][colun];
    if (sum < 0) {
      sum=0;
    } else if (sum > sumMax) {
      sumMax = sum;
    }
  }
}
return 1;
}
/******************************************************************************/
