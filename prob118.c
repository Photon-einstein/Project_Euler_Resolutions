#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define LIMIT 0
#define MAXPRIME 98765431
#define NFORS 6
#define DIGITS 10
typedef struct {
  int prime; /* prime number */
  int *digit; /* digits of prime number */
  int nDigit; /* number of the digits of the prime number */
} primeID;

/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
int dimCalc (int counter, int *nDigit);

/* this function creates and fills the array with the digits of the number
counter, knowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *fullingVectorDigit (int counter, int dim, int nDigit);

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTeste (int nTest, primeID *v, int nPrime);

/* this function search the digit zero, and if it founds then returns 1, if not
found, it returns 0, and if there was an error in this function, it returns -1 */
int boolZeroFound (int *vDigit, int nDigit);

/* this function makes the test of the diferent digits of an array of digits,
and then it returns 1 if all the digits are diferent or 0 if the digits are
equal, some of them, or returns -1 if there was a problem in the function */
int testDiferentDigits (int *vDigit, int nDigit);

/* this function makes the sinalization with 1 in the array dTest of all the
digits found, and returns -1 if there was a problem in the function, 0 if
there are duplicated digits or 1 if all is ok */
int copyDiferentDigits (int *vDigit, int nDigit, int *dTest);

/* this function makes the sum of the digits and then return the sum or -1 if
there was a problem in the function */
int sumDigits (int *vDigit, int nDigit);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int i[NFORS], answer = 0, maxPrime = MAXPRIME+1, nPrime = 0,j, nPrimeT;
int dim, nDigit, *vDigit, booleano, nTest, sizeVprime, *dTest, limit = 1000000;
int digitsSize=DIGITS;
primeID *v;
/* prime array alocation */
sizeVprime = maxPrime/5;
v = (primeID*) calloc (sizeVprime, sizeof (primeID));
if (v == NULL) {
  printf("\nThere was a problem in the memory allocation of the prime numbers.");
  return 0;
}
/* prime fulling */
v[0].prime = 2;
v[0].nDigit = 1;
v[0].digit = fullingVectorDigit (2, 1, 1);
if (v[0].digit == NULL) {
  printf("\nThere was an erro in the the function preencheVectorDigit.");
}
nPrime++;
for (nTest=3; nTest < maxPrime; nTest+=2) {
  /* dim calc */
  dim = dimCalc (nTest, &nDigit);
  if (dim == -1) {
    printf("\nThere was a problem in the function dimCalc.");
    return 0;
  }
  /* memory allocation of digit array */
  vDigit = fullingVectorDigit (nTest, dim, nDigit);
  if (vDigit == NULL) {
    printf ("\nThere was a problem in the function fullingVectorDigit.");
    return 0;
  }
  /* zero test */
  booleano = boolZeroFound (vDigit, nDigit);
  if (booleano == -1) {
    printf("\nThere was a problem in the function boolZeroFound.");
    return 0;
  } else if (booleano == 1) {
    /* zero found */
    free (vDigit);
    continue;
  }
  /* diferent digits test */
  booleano = testDiferentDigits (vDigit, nDigit);
  if (booleano == -1) {
    printf("\nThere was a problem in the function testDiferentDigits.");
    return 0;
  } else if (booleano == 0) {
    /* equal digits */
    free (vDigit);
    continue;
  }
  /* Dirichlet Theorem test */
  if (nTest > 3) {
    booleano = sumDigits (vDigit, nDigit);
    if (booleano == -1) {
      printf("\nThere was a problem in the function testDiferentDigits.");
      return 0;
    }
    if (booleano%9==0 || booleano%9==3 || booleano%9==6) {
      /* no prime found */
      free (vDigit);
      continue;
    }
  }
  /* if it reaches here then no zero was found and all the digits are diferent */
  booleano = primeTeste (nTest, v, nPrime);
  if (booleano == -1) {
    printf("\nThere was a problem in the function primeTeste.");
    return 0;
  } else if (booleano == 0) {
    /* no prime found */
    free (vDigit);
    continue;
  }
  /* if it reaches here then we have a prime number with no zeros, and all the
  digit are diferent */
  if (nPrime == sizeVprime) {
    /* memory reallocation */
    sizeVprime*=2;
    v = (primeID*) realloc (v, sizeVprime*sizeof (primeID));
    if (v == NULL) {
      printf("\nThere was a problem in the memory reallocation.");
      return 0;
    }
  }
    /* save new values */
    v[nPrime].prime = nTest;
    v[nPrime].digit = vDigit;
    v[nPrime].nDigit = nDigit;
    nPrime++;
}
/* memory reallocation */
if (nPrime != sizeVprime) {
  /* memory reallocation */
  sizeVprime*=2;
  v = (primeID*) realloc (v, sizeVprime*sizeof (primeID));
  if (v == NULL) {
    printf("\nThere was a problem in the memory reallocation.");
    return 0;
  }
}
/* starting in 0 then */
printf("\nThere are %d primes to be evaluated.", nPrime);
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
beginning = end;
printf("\nTime in seconds after prime test: %lf", tempo);
/* test */
for (i[0] = 0; i[0] < nPrime; i[0]++) {
  /* exit test */
  for (i[1] = i[0]+1; i[1] < nPrime; i[1]++) {
    /* exit test */
    if ((v[i[0]].nDigit+v[i[1]].nDigit)>9) {
      break;
    }
    /* digit == 9 */
    if ((v[i[0]].nDigit+v[i[1]].nDigit)==9) {
      dTest = (int*) calloc (digitsSize, sizeof (int));
      if (dTest == NULL) {
        printf("\nThere was a problem in the memory allocation of dTest.");
        return 0;
      }
      for (j = 0; j < 2; j++) {
        booleano = copyDiferentDigits (v[i[j]].digit, v[i[j]].nDigit, dTest);
        if (booleano == -1) {
          printf("\nThere was a problem in the function copyDiferentDigits.");
          return 0;
        } else if (booleano == 0) {
          /* equal digits found */
          free (dTest);
          break;
        }
      }
      /* exit */
      if (booleano==0) {continue;}
      /* if it reaches here then new set was found */
      free (dTest);
      answer++;
      /* new answer found */
      if (answer<LIMIT) {
      printf("\nSet %d: {", answer);
        for (j = 0; j < 2; j++) {
          if (j < 1) {
            printf ("%d, ", v[i[j]].prime);
          } else {
            printf ("%d }", v[i[j]].prime);
          }
        }
      }
      continue;
    }
    for (i[2] = i[1]+1; i[2] < nPrime; i[2]++) {
      /* exit test */
      if ((v[i[0]].nDigit+v[i[1]].nDigit+v[i[2]].nDigit)>9) {
        break;
      }
      /* digit == 9 */
      if ((v[i[0]].nDigit+v[i[1]].nDigit+v[i[2]].nDigit)==9) {
        dTest = (int*) calloc (digitsSize, sizeof (int));
        if (dTest == NULL) {
          printf("\nThere was a problem in the memory allocation of dTest.");
          return 0;
        }
        for (j = 0; j < 3; j++) {
          booleano = copyDiferentDigits (v[i[j]].digit, v[i[j]].nDigit, dTest);
          if (booleano == -1) {
            printf("\nThere was a problem in the function copyDiferentDigits.");
            return 0;
          } else if (booleano == 0) {
            /* equal digits found */
            free (dTest);
            break;
          }
        }
        /* exit */
        if (booleano==0) {continue;}
        /* if it reaches here then new set was found */
        free (dTest);
        answer++;
        /* new answer found */
        if (answer<LIMIT) {
        printf("\nSet %d: {", answer);
          for (j = 0; j < 3; j++) {
            if (j < 2) {
              printf ("%d, ", v[i[j]].prime);
            } else {
              printf ("%d }", v[i[j]].prime);
            }
          }
        }
        continue;
      }
      for (i[3] = i[2]+1; i[3] < nPrime; i[3]++) {
        /* exit test */
        if ((v[i[0]].nDigit+v[i[1]].nDigit+v[i[2]].nDigit+v[i[3]].nDigit)>9) {
          break;
        }
        /* digit == 9 */
        if ((v[i[0]].nDigit+v[i[1]].nDigit+v[i[2]].nDigit+v[i[3]].nDigit)==9) {
          dTest = (int*) calloc (digitsSize, sizeof (int));
          if (dTest == NULL) {
            printf("\nThere was a problem in the memory allocation of dTest.");
            return 0;
          }
          for (j = 0; j < 4; j++) {
            booleano = copyDiferentDigits (v[i[j]].digit, v[i[j]].nDigit, dTest);
            if (booleano == -1) {
              printf("\nThere was a problem in the function copyDiferentDigits.");
              return 0;
            } else if (booleano == 0) {
              /* equal digits found */
              free (dTest);
              break;
            }
          }
          /* exit */
          if (booleano==0) {continue;}
          /* if it reaches here then new set was found */
          free (dTest);
          /* new set found */
          answer++;
          /* new answer found */
          if (answer<LIMIT) {
          printf("\nSet %d: {", answer);
            for (j = 0; j < 4; j++) {
              if (j < 3) {
                printf ("%d, ", v[i[j]].prime);
              } else {
                printf ("%d }", v[i[j]].prime);
              }
            }
          }
          continue;
        }
        for (i[4] = i[3]+1; i[4] < nPrime; i[4]++) {
          /* exit test */
          if ((v[i[0]].nDigit+v[i[1]].nDigit+v[i[2]].nDigit+v[i[3]].nDigit+v[i[4]].nDigit)>9) {
            break;
          }
          /* digit == 9 */
          if ((v[i[0]].nDigit+v[i[1]].nDigit+v[i[2]].nDigit+v[i[3]].nDigit+v[i[4]].nDigit)==9) {
            dTest = (int*) calloc (digitsSize, sizeof (int));
            if (dTest == NULL) {
              printf("\nThere was a problem in the memory allocation of dTest.");
              return 0;
            }
            for (j = 0; j < 5; j++) {
              booleano = copyDiferentDigits (v[i[j]].digit, v[i[j]].nDigit, dTest);
              if (booleano == -1) {
                printf("\nThere was a problem in the function copyDiferentDigits.");
                return 0;
              } else if (booleano == 0) {
                /* equal digits found */
                free (dTest);
                break;
              }
            }
            /* exit */
            if (booleano==0) {continue;}
            /* if it reaches here then new set was found */
            free (dTest);
            /* new set found */
            answer++;
            if (answer<LIMIT) {
            printf("\nSet %d: {", answer);
              for (j = 0; j < 5; j++) {
                if (j < 4) {
                  printf ("%d, ", v[i[j]].prime);
                } else {
                  printf ("%d }", v[i[j]].prime);
                }
              }
            }
            continue;
          }
          for (i[5] = i[4]+1; i[5] < nPrime; i[5]++) {
            /* exit test */
            if ((v[i[0]].nDigit+v[i[1]].nDigit+v[i[2]].nDigit+v[i[3]].nDigit+v[i[4]].nDigit+v[i[5]].nDigit)>9) {
              break;
            }
            /* digit == 9 */
            if ((v[i[0]].nDigit+v[i[1]].nDigit+v[i[2]].nDigit+v[i[3]].nDigit+v[i[4]].nDigit+v[i[5]].nDigit)==9) {
              dTest = (int*) calloc (digitsSize, sizeof (int));
              if (dTest == NULL) {
                printf("\nThere was a problem in the memory allocation of dTest.");
                return 0;
              }
              for (j = 0; j < 6; j++) {
                fflush (stdout);
                booleano = copyDiferentDigits (v[i[j]].digit, v[i[j]].nDigit, dTest);
                if (booleano == -1) {
                  printf("\nThere was a problem in the function copyDiferentDigits.");
                  return 0;
                } else if (booleano == 0) {
                  /* equal digits found */
                  free (dTest);
                  break;
                }
              }
              /* exit */
              if (booleano==0) {continue;}
              /* if it reaches here then new set was found */
              free (dTest);
              /* new set found */
              answer++;
              if (answer<LIMIT) {
              printf("\nSet %d: {", answer);
                for (j = 0; j < 6; j++) {
                  if (j < 5) {
                    printf ("%d, ", v[i[j]].prime);
                  } else {
                    printf ("%d }", v[i[j]].prime);
                  }
                }
              }
              continue;
            }
          }
        }
      }
    }
  }
}

/* free memory */
for (j = 0; j < nPrime; j++) {
  free(v[j].digit);
}
free (v);
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThere are %d diferent sets to be evaluated.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int dimCalc (int counter, int *nDigit) {
/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
if (nDigit == NULL || counter < 1) {
  return -1;
}
int dim = 1;
int res, nDigitsNumber = 1;
res = counter / dim;
while (res > 9) {
  dim = dim * 10;
  nDigitsNumber++;
  res = counter / dim;
}
*nDigit = nDigitsNumber;
return dim;
}
/******************************************************************************/
int *fullingVectorDigit (int counter, int dim, int nDigit) {
/* this function creates and fills the array with the digits of the number
counter, ckowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *vectorDigit;
int i;
vectorDigit = (int*) calloc (nDigit, sizeof (int));
if (vectorDigit == NULL) {
  printf ("\nError in the creation of the array.");
  return NULL;
}
for (i = 0; i < nDigit; i++) {
  vectorDigit[i] = counter / dim;
  counter = counter - vectorDigit[i]*dim;
  dim = dim / 10;
}
return vectorDigit;
}
/******************************************************************************/
int primeTeste (int nTest, primeID *v, int nPrime) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
if (v == NULL || nPrime < 0) {
  return -1;
}
int i, comparador;
if (nTest <= 1) {
	return 0;
}
if (nTest  == 2) {
	return 1;
} else if (nTest % 2 == 0) {
	return 0;
}
for (i = 3; i < sqrt(nTest+1); i = i+2) {
	if (nTest % i == 0) {
		return 0;
	}
}
/* if it reaches here, then it is a prime number */
return 1;
}
/******************************************************************************/
int boolZeroFound (int *vDigit, int nDigit) {
/* this function search the digit zero, and if it founds then returns 1, if not
found, it returns 0, and if there was an error in this function, it returns -1 */
if (vDigit == NULL || nDigit < 1) {
  return -1;
}
int i;
for (i = 0; i < nDigit; i++) {
  if (vDigit[i] == 0) {
    return 1;
  }
}
/* if it reaches here then no zero was found */
return 0;
}
/******************************************************************************/
int testDiferentDigits (int *vDigit, int nDigit) {
/* this function makes the test of the diferent digits of an array of digits,
and then it returns 1 if all the digits are diferent or 0 if the digits are
equal, some of them, or returns -1 if there was a problem in the function */
if (vDigit == NULL || nDigit < 1) {
  return -1;
}
int i, j;
for (i = 0; i < nDigit-1; i++) {
  for (j = i+1; j < nDigit; j++) {
    if (vDigit[i] == vDigit[j]) {
      return 0;
    }
  }
}
/* if it reaches here then the digits are all diferent */
return 1;
}
/******************************************************************************/
int copyDiferentDigits (int *vDigit, int nDigit, int *dTest) {
/* this function makes the sinalization with 1 in the array dTest of all the
digits found, and returns -1 if there was a problem in the function, 0 if
there are duplicated digits or 1 if all is ok */
if (vDigit == NULL || nDigit < 1 || dTest == NULL) {
  return -1;
}
int i, index;
for (i = 0; i < nDigit; i++) {
  index = vDigit[i];
  if (dTest[index] == 1) {
    /* duplicated digit */
    return 0;
  } else {
    dTest[index] = 1;
  }
}
/* if it reaches here then all is ok */
return 1;
}
/******************************************************************************/
int sumDigits (int *vDigit, int nDigit) {
/* this function makes the sum of the digits and then return the sum or -1 if
there was a problem in the function */
if (vDigit == NULL || nDigit < 1) {
  return -1;
}
int sum = 0, i;
for (i = 0; i < nDigit; i++) {
  sum+=vDigit[i];
}
return sum;
}
/******************************************************************************/
