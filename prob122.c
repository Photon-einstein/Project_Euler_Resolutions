#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define KMIN 1
#define KMAX 200
#define LIMIT 200
#define SIGMANDIM 10

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function.
If not prime, then returns by reference the lowest prime dividing nTest */
int primeTest (int nTest, int *pMin);

/* this function makes the fulling of the sigmaN array and then returns 1 if
all went ok or 0 if there was a problem in the function sigmaNfulling */
int sigmaNfulling (int *sigmaN, int sigmaDim);

/* this function makes the calculation of sigmaN for a given nTest and
returns 1 if in nTest in the table, 0 if not or -1 if there was a problem
in the function */
int sigmaNCalc (int *sigmaN, int sigmaDim, int nTest);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int *ln, i, *sigmaN, dim, kmin, kmax, sigmaDim, boolean, nTest, answer = 0, lnR;
int pMin;
kmin = KMIN;
kmax = KMAX;
dim = kmax+1;
sigmaDim = SIGMANDIM;
/* default */
if (kmax > LIMIT) {
  printf("\nOverfault of the range, lower k please.");
  return 0;
}

/* ln generation */
ln = (int*) calloc (dim, sizeof (int));
if (ln == NULL) {
  printf("\nThere was an error in the memory allocation of ln.");
  return 0;
}
/* sigmaN generation */
sigmaN = (int*) calloc (sigmaDim, sizeof (int));
if (sigmaN == NULL) {
  printf("\nThere was an error in the memory allocation of sigmaN.");
  return 0;
}
/* sigmaN fulling */
boolean = sigmaNfulling (sigmaN, sigmaDim);
if (boolean == 0) {
  printf("\nThere was an error in the function sigmaNfulling.");
  return 0;
}
/* answer calc */
for (nTest = 1; nTest < kmax+1; nTest++) {
  /* first value */
  if (nTest == 1) {
    ln[nTest] = 0;
    continue;
  }
  /* other values */
  boolean = primeTest (nTest, &pMin);
  if (boolean == -1) {
    printf("There was a problem in the function primeTeste");
  } else if (boolean == 1) {
    /* prime number */
    ln[nTest] = ln[nTest-1]+1;
  } else {
    /* not prime number */
    lnR = ln[pMin] + ln[(int)nTest/pMin];
    /* min calc */
    if ((ln[nTest-1]+1) < lnR) {
      ln[nTest] = ln[nTest-1]+1;
    } else {
      ln[nTest] = lnR;
    }
  }
  /* sigmaN tune */
  boolean = sigmaNCalc (sigmaN, sigmaDim, nTest);
  if (boolean == -1) {
    printf("\nThere was an error in the function sigmaNCalc.");
    return 0;
  } else if (boolean == 1) {
    ln[nTest]--;
  }
  answer+=ln[nTest];
}

/* free memory */
free (ln);
free (sigmaN);
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nFor %d <= k <= %d Sum k = %d", kmin, kmax, answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int primeTest (int nTest, int *pMin) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function.
If not prime, then returns by reference the lowest prime dividing nTest */
if (pMin == NULL) {
  return -1;
}
int i, comparador;
if (nTest <= 1) {
	return 0;
}
if (nTest  == 2) {
	return 1;
} else if (nTest % 2 == 0) {
  /* not prime */
  *pMin = 2;
  return 0;
}
for (i = 3; i < sqrt(nTest+1); i = i+2) {
	if (nTest % i == 0) {
    /* not prime */
    *pMin = i;
    return 0;
	}
}
/* if it reaches here, then it is a prime number */
return 1;
}
/******************************************************************************/
int sigmaNfulling (int *sigmaN, int sigmaDim) {
/* this function makes the fulling of the sigmaN array and then returns 1 if
all went ok or 0 if there was a problem in the function sigmaNfulling */
if (sigmaN == NULL || sigmaDim < 1) {
  return 0;
}
int i;
for (i = 0; i < sigmaDim; i++) {
  if (i == 0) {
    sigmaN[i] = 23;
  } else if (i == 1) {
    sigmaN[i] = 43;
  } else if (i == 2) {
    sigmaN[i] = 59;
  } else if (i == 3) {
    sigmaN[i] = 77;
  } else if (i == 4) {
    sigmaN[i] = 83;
  } else if (i == 5) {
    sigmaN[i] = 107;
  } else if (i == 6) {
    sigmaN[i] = 149;
  } else if (i == 7) {
    sigmaN[i] = 163;
  } else if (i == 8) {
    sigmaN[i] = 165;
  } else if (i == 9) {
    sigmaN[i] = 179;
  }
}
return 1;
}
/******************************************************************************/
int sigmaNCalc (int *sigmaN, int sigmaDim, int nTest) {
/* this function makes the calculation of sigmaN for a given nTest and
returns 1 if in nTest in the table, 0 if not or -1 if there was a problem
in the function */
if (sigmaN == NULL || sigmaDim < 1) {
  return -1;
}
int i;
for (i = 0; i < sigmaDim; i++) {
  if (sigmaN[i] == nTest) {
    /* value found in the table */
    return 1;
  } else if (nTest < sigmaN[i]) {
    /* value not found in the table */
    return 0;
  }
}
}
/******************************************************************************/
