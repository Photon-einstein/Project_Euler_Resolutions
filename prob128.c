#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZEANSWER 2000
#define SIZEANALYSE 6

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (long long int nTest);

/* this function makes the calculation of pdCalc and then returns -1 if there
was a problem in the function, 1 if pD(n)=3 or 0 if pD(n)!=3 */
int pdCalc (long long int center, long long int *analyse, int sizeAnalyse);

/* this function returns the dimension of a given ring, or -1 if there was a
problem in the function */
long long int dimCalc (long long int nRing);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int nAnswers = 0, goal, boolean, n, i, sizeAnalyse;
long long int *ringHead, *lastElement, answer, analyse[SIZEANALYSE], center;
goal = SIZEANSWER;
sizeAnalyse = SIZEANALYSE;
/* array creation */
ringHead = (long long int*) calloc (3, sizeof (long long int));
if (ringHead == NULL) {
  printf("\nThere was a problem in the memory allocation of ringHead.");
  return 0;
}
lastElement = (long long int*) calloc (3, sizeof (long long int));
if (lastElement == NULL) {
  printf("\nThere was a problem in the memory allocation of lastElement.");
  return 0;
}
n = 1;
/* enter cycle */
while (1) {
  if (n == 1) {
    /* analyse calc */
    center = 1;
    for (i = 0; i < sizeAnalyse; i++) {
      analyse[i] = i+2;
    }
    boolean = pdCalc (center, analyse, sizeAnalyse);
    if (boolean == -1) {
      printf("\nThere was a problem in the function pdCalc.");
      return 0;
    } else if (boolean == 1) {
      /* new solution found */
      nAnswers++;
    }
    /* new values calc for ring head*/
    n++;
    /* ring 0 */
    ringHead[0] = 1;
    /* ring 2 */
    ringHead[1] = dimCalc(1)+1;
    /* ring 3 */
    ringHead[2] = ringHead[1]+dimCalc(2);
  } else if (n == 2) {
    /* last element of the ring 2 */
    /* ring 2 */
    lastElement[1] = ringHead[2]-1;
    /* ring 3 */
    lastElement[2] = ringHead[2]+dimCalc(3)-1;
    /* analyse calc for ringHead element */
    analyse[0] = ringHead[2];
    analyse[1] = ringHead[2]+1;
    analyse[2] = ringHead[1]+1;
    analyse[3] = ringHead[0];
    analyse[4] = lastElement[1];
    analyse[5] = ringHead[2]+dimCalc(n+1)-1;
    /* pd calc */
    center = ringHead[1];
    boolean = pdCalc (center, analyse, sizeAnalyse);
    if (boolean == -1) {
      printf("\nThere was a problem in the function pdCalc.");
      return 0;
    } else if (boolean == 1) {
      /* new solution found */
      nAnswers++;
    }
    /* lastElement calc values */
    /* analyse calc for lastElement element for n = 2, exception */
    analyse[0] = ringHead[0];
    analyse[1] = ringHead[1];
    analyse[2] = lastElement[1]-1;
    analyse[3] = lastElement[2];
    analyse[4] = lastElement[2]-1;
    analyse[5] = lastElement[2]-2;
    /* pd calc */
    center = lastElement[1];
    boolean = pdCalc (center, analyse, sizeAnalyse);
    if (boolean == -1) {
      printf("\nThere was a problem in the function pdCalc.");
      return 0;
    } else if (boolean == 1) {
      /* new solution found */
      nAnswers++;
    }
    /* new values calc for ring head and lastElement for next n */
    n++;
    /* shifting values */
    for (i = 0; i < 2; i++) {
      ringHead[i] = ringHead[i+1];
      lastElement[i] = lastElement[i+1];
    }
    /* next value n+1 */
    ringHead[2] = ringHead[1]+dimCalc(n);
    lastElement[2] = ringHead[2]+dimCalc(n+1)-1;
  } else {
    /* n >= 3 */
    /* analyse calc for ringHead element */
    analyse[0] = ringHead[2];
    analyse[1] = ringHead[2]+1;
    analyse[2] = ringHead[1]+1;
    analyse[3] = ringHead[0];
    analyse[4] = lastElement[1];
    analyse[5] = ringHead[2]+dimCalc(n+1)-1;
    /* pd calc */
    center = ringHead[1];
    boolean = pdCalc (center, analyse, sizeAnalyse);
    if (boolean == -1) {
      printf("\nThere was a problem in the function pdCalc.");
      return 0;
    } else if (boolean == 1) {
      /* new solution found */
      nAnswers++;
      /* exit condition */
      if (nAnswers == goal) {
        answer = center;
        break;
      }
    }
    /* analyse calc for lastElement element */
    analyse[0] = lastElement[1]-1;
    analyse[1] = lastElement[0];
    analyse[2] = ringHead[0];
    analyse[3] = ringHead[1];
    analyse[4] = lastElement[2];
    analyse[5] = lastElement[2]-1;
    /* pd calc */
    center = lastElement[1];
    boolean = pdCalc (center, analyse, sizeAnalyse);
    if (boolean == -1) {
      printf("\nThere was a problem in the function pdCalc.");
      return 0;
    } else if (boolean == 1) {
      /* new solution found */
      nAnswers++;
      /* exit condition */
      if (nAnswers == goal) {
        answer = center;
        break;
      }
    }
    /* new values calc for ring head and lastElement for next n */
    n++;
    /* shifting values */
    for (i = 0; i < 2; i++) {
      ringHead[i] = ringHead[i+1];
      lastElement[i] = lastElement[i+1];
    }
    /* next value n+1 */
    ringHead[2] = ringHead[1]+dimCalc(n);
    lastElement[2] = ringHead[2]+dimCalc(n+1)-1;
  }
  /* exit condition */
  if (nAnswers == goal) {
    break;
  }
}

/* free memory */
free (ringHead);
free (lastElement);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe tile %d th is %lld.", goal, answer);
printf("\n");
return 0;
}
/******************************************************************************/
int primeTest (long long int nTest) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
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
int pdCalc (long long int center, long long int *analyse, int sizeAnalyse) {
/* this function makes the calculation of pdCalc and then returns -1 if there
was a problem in the function, 1 if pD(n)=3 or 0 if pD(n)!=3 */
if (analyse == NULL || sizeAnalyse < 1 || center < 1) {
  return -1;
}
int i, number, pd = 0, boolean;
for (i = 0; i < sizeAnalyse; i++) {
  number = center - analyse[i];
  if (number < 0){
    number*=-1;
  }
  boolean = primeTest (number);
  if (boolean == -1) {
    printf("\nThere was a problem in the function primeTest.");
    return -1;
  } else if (boolean == 1) {
    pd++;
  }
}
/* return value calc */
if (pd == 3) {
  return 1;
} else {
  return 0;
}
}
/******************************************************************************/
long long int dimCalc (long long int nRing) {
/* this function returns the dimension of a given ring, or -1 if there was a
problem in the function */
if (nRing < 0) {
  return -1;
}
if (nRing == 0) {
  return 0;
} else if (nRing == 1) {
  return 1;
} else {
  return 6*(nRing-1);;
}
}
/******************************************************************************/
