#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DSTART 0
#define DEND 9
#define N 10
typedef struct {
  int d;
  int nDigit; /* aka n */
  int m; /* aka M(n,d) */
  int n; /* aka N(n,d) */
  long long int s; /* aka S(n,d) */
} run;

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTeste (long long int nTest);

/* function makes the creation of the number equal at the array nTest and
then return the number if all went ok or 0 is there was a problem in the
function */
long long int numberCreation (int *nTest, int n);

/* this function makes the load of the digit d into the array nTest of size n
and then returns 1 if all went ok or 0 if there was a problem in the function */
int dLoadingToArray (int *nTest, int d, int n);

/* this function makes the calculation of the answer for this problem and
then returns the answer or 0 if there was a problem in this function */
long long int answerCalc (run *v, int d);

int main () {

clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int dStart = DSTART, dEnd = DEND, sizeD, d, n = N, pos, value, *nTest, booleano;
int primeFound, i, pos2, value2;
long long int answer = 0, number;
run *v;


/* array creation */
sizeD = dEnd - dStart + 1;
v = (run*)calloc (sizeD, sizeof (run));
if (v == NULL) {
  printf("\nThere was an error in the creation of v.");
  return 0;
}
/* starting cycle */
for (d = dStart; d < dEnd+1; d++) {
  v[d].nDigit = n;
  v[d].d = d;
  /* flag prime found deactivated */
  primeFound = 0;
  /* enter test */
  if (d != 0) {
    /* d  > 0 */
    /* flag prime found deactivated */
    primeFound = 0;
    /* enter test cycle */
    for (pos = 0; pos < n; pos++) {
      for (value = 1; value < 10; value++) {
        /* even ending */
        if ((pos == (n-1) && value % 2 == 0) || (value == d)) {
          continue;
        }
        /* test array creation */
        nTest = (int*) calloc (n, sizeof (int));
        if (nTest == NULL) {
          printf("\nThere was an error in the creation of nTest.");
          return 0;
        }
        /* d loading to array */
        booleano = dLoadingToArray (nTest, d, n);
        if (booleano == 0) {
          printf("\nThere was a problem in the function dLoadingToArray.");
          return 0;
        }
        /* changing values */
        nTest[pos] = value;
        /* numberCreation */
        number = numberCreation (nTest, n);
        if (number == 0) {
          printf("\nThere was an error in the function numberCreation.");
          return 0;
        }
        /* prime testing */
        booleano = primeTeste (number);
        if (booleano == 1) {
          /* prime number */
          /* flag activation */
          if (primeFound == 0) {
            primeFound = 1;
          }
          /* saving results */
          v[d].m = n-1;
          v[d].n++;
          v[d].s+=number;
        }
        /* free memory */
        free (nTest);
      }
    }
  }
  if (primeFound) {
    continue;
  }
  if (d == 0) {
    /* test array creation */
    nTest = (int*) calloc (n, sizeof (int));
    if (nTest == NULL) {
      printf("\nThere was an error in the creation of nTest.");
      return 0;
    }
    /* enter test cycle */
    for (nTest[0] = 1; nTest[0] < 10; nTest[0]++) {
      for (nTest[n-1] = 1; nTest[n-1] < 10; nTest[n-1]+=2) {
        /* numberCreation */
        number = numberCreation (nTest, n);
        if (number == 0) {
          printf("\nThere was an error in the function numberCreation.");
          return 0;
        }
        /* prime testing */
        booleano = primeTeste (number);
        if (booleano == 1) {
          /* prime number */
          /* flag activation */
          if (primeFound == 0) {
            primeFound = 1;
          }
          /* saving results */
          v[d].m = n-2;
          v[d].n++;
          v[d].s+=number;
        }
      }
    }
    /* free memory */
    free (nTest);
  }
  if (primeFound) {
    continue;
  }
  if (primeFound == 0) {
    /* d  > 0 */
    /* flag prime found deactivated */
    primeFound = 0;
    /* enter test cycle */
    for (pos = 0; pos < n-1; pos++) {
      for (pos2 = pos+1; pos2 < n; pos2++) {
        for (value = 0; value < 10; value++) {
          if (value == 0 && pos == 0) {
            continue;
          }
          for (value2 = 0; value2 < 10; value2++) {
            /* even ending or repeated d */
            if ((value == d) || (pos2 == (n-1) && (value2 % 2 == 0)) || (value2 == d)) {
              continue;
            }
            /* test array creation */
            nTest = (int*) calloc (n, sizeof (int));
            if (nTest == NULL) {
              printf("\nThere was an error in the creation of nTest.");
              return 0;
            }
            /* d loading to array */
            booleano = dLoadingToArray (nTest, d, n);
            if (booleano == 0) {
              printf("\nThere was a problem in the function dLoadingToArray.");
              return 0;
            }
            /* changing values */
            nTest[pos] = value;
            nTest[pos2] = value2;
            /* numberCreation */
            number = numberCreation (nTest, n);
            if (number == 0) {
              printf("\nThere was an error in the function numberCreation.");
              return 0;
            }
            /* prime testing */
            booleano = primeTeste (number);
            if (booleano == 1) {
              /* prime number */
              /* flag activation */
              if (primeFound == 0) {
                primeFound = 1;
              }
              /* saving results */
              v[d].m = n-2;
              v[d].n++;
              v[d].s+=number;
            }
            /* free memory */
            free (nTest);
          }
        }
      }
    }
  }
  /* test conditions test ok */
  if (primeFound == 0) {
    printf("\nThere was a problem in the testing conditions, not enought conditions.");
    printf("\n");
    return 0;
  }
}
answer = answerCalc (v, sizeD);
if (answer == 0) {
  printf("\nThere was a problem in the function answerCalc.");
  return 0;
}
/* free memory */
free (v);
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThe sum of all the S(%d,d) is %lld.", n, answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int primeTeste (long long int nTest) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not */
long long int i, max;
/* data managing */
if (nTest == 1 && nTest == 0) {
	return 0;
}
if (nTest  == 2) {
	return 1;
} else if (nTest % 2 == 0) {
	return 0;
}
for (i = 3; i < sqrt (nTest+1); i+=2) {
	if (nTest % i == 0) {
		return 0;
	}
}
/* if it reaches here, then it is a prime number */
return 1;
}
/******************************************************************************/
long long int numberCreation (int *nTest, int n) {
/* function makes the creation of the number equal at the array nTest and
then return the number if all went ok or 0 is there was a problem in the
function */
if (nTest == NULL || n < 1) {
  return 0;
}
long long int number = 0;
int i, base = 10, pos = 0;
for (i = n-1; i > -1; i--) {
  number+=nTest[pos]*pow(base, i);
  pos++;
}
return number;
}
/******************************************************************************/
int dLoadingToArray (int *nTest, int d, int n) {
/* this function makes the load of the digit d into the array nTest of size n
and then returns 1 if all went ok or 0 if there was a problem in the function */
if (nTest == NULL || d < 0 || d > 9) {
  return 0;
}
int i;
for (i = 0; i < n; i++) {
  nTest[i] = d;
}
return 1;
}
/******************************************************************************/
long long int answerCalc (run *v, int d) {
/* this function makes the calculation of the answer for this problem and
then returns the answer or 0 if there was a problem in this function */
if (v == NULL || d < 1) {
  return 0;
}
long long int answer = 0;
int i;
for (i = 0; i < d; i++) {
  printf("\nS(%d,%d) = %lld\t M(%d,%d) = %d\t N(%d,%d) = %d ",v[i].nDigit, i, v[i].s,
  v[i].nDigit, i, v[i].m, v[i].nDigit, i, v[i].n);
  answer+=v[i].s;
}
return answer;
}
/******************************************************************************/
