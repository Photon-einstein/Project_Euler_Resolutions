#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MIN 1000
typedef struct {
  int factor;
  int multiplicity;
} factorization;

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTeste (int nTest, int *vPrime, int nPrime);

/* this function makes the factorization of a number nTest, and stores the
prime factors in an array dinamicaly made, and also the index of each factor.
I returns also by reference the number of prime numbers that has made the
factorization, or NULL if there was a problem in the function */
factorization* factorizacaoVecProduz (int nTest, int *vPrime, int nPrime, int *n, int sizeVector);

/* this function takes the array of factorization of nTeste and calculate the
factorization of nTeste² and then returns 1 if all ok or 0 if there was a
problem in this function */
int factorizationNSquare (factorization *fac, int n);

/* this function calculates the number of divisors of the number nTest² and
then return the number or 0 if there was a problem in the function */
int numberOfDivisor (factorization *fac, int dimV);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int nTest = 2, n, min = MIN, limiteM, mult = 1, sizeVector = min*20;
int *vPrime, answer, nPrime = 0, booleano, i;
factorization *fac;

limiteM = min*2-1;
vPrime = (int*) calloc (sizeVector, sizeof (int));
if (vPrime == NULL) {
  printf("\nThere was an error in the memory allocation of primoV.");
  return 0;
}
/* enter cycle test */
while (1) {
  /* prime test */
  booleano = primeTeste (nTest, vPrime, nPrime);
  if (booleano == -1) {
    printf("\nThere was a problem in the function primeTest.");
    return 0;
  } else if (booleano == 1) {
    /* new prime number */
    if (nPrime == sizeVector) {
      /* space not available */
      mult++;
      sizeVector*=mult;
      vPrime = realloc (vPrime, sizeVector*sizeof (int));
      if (vPrime == NULL) {
        printf("\nThere was an error in the reallocation of primoV.");
        return 0;
      }
    }
    /* storage number */
    vPrime[nPrime] = nTest;
    nPrime++;
    nTest++;
    continue;
  }
  /* if it reaches here then it is not a prime number */
  fac = factorizacaoVecProduz (nTest, vPrime, nPrime, &n, sizeVector);
  if (fac == NULL) {
    printf("\nThere was a problem in the function fac.");
    return 0;
  }
  booleano = factorizationNSquare (fac, n);
  if (booleano == 0) {
    printf("\nThere was a problem in the function factorizationNSquare.");
    return 0;
  }
  booleano = numberOfDivisor (fac, n);
  /* free memory */
  free (fac);
  if (booleano == 0) {
    printf("\nThere was a problem in the function numberOfDivisor.");
    return 0;
  } else if (booleano > limiteM) {
    answer = nTest;
    break;
  }
  /* next number */
  nTest++;
}
/* free memory */
free(vPrime);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe minimum n in this conditions is %d.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int primeTeste (int nTest, int *vPrime, int nPrime) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
if (vPrime == NULL || nPrime < 0) {
  return -1;
}
int i, comparator;
if (nTest <= 1) {
	return 0;
}
if (nTest  == 2) {
	return 1;
} else if (nTest % 2 == 0) {
	return 0;
}
if (nTest > 100) {
  comparator = sqrt (nTest+1);
  for (i = 0; i < nPrime; i++) {
    if (vPrime[i] > comparator) {
      /* case of prime number */
      return 1;
    }
    if (nTest % vPrime[i] == 0) {
      /* case of not prime */
      return 0;
    }
  }
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
factorization* factorizacaoVecProduz (int nTest, int *vPrime, int nPrime, int *n, int sizeVector) {
/* this function makes the factorization of a number nTest, and stores the
prime factors in an array dinamicaly made, and also the index of each factor.
I returns also by reference the number of prime numbers that has made the
factorization, or NULL if there was a problem in the function */
if (vPrime == NULL || n == NULL || sizeVector < 0 || nPrime < 0) {
  return NULL;
}
int nTesteM = nTest, nP = 0, i, mult = 1, repeat = 0, j;
factorization *vectorPrimoFac;

vectorPrimoFac = (factorization*) calloc (sizeVector*mult, sizeof (factorization));
if (vectorPrimoFac == NULL) {
  printf ("\nThere was an error in the memory allocation of the vector factorization.");
  return NULL;
}
while (nTest != 1) {
  repeat = 0;
  for (i = 0; i < nPrime; i++) {
    if (nTest % vPrime[i] == 0) {
      nTest = nTest / vPrime[i];
      /* I am now going to verify if that prime number is also in the array of vectorPrimoFac */
      /* situation in that this is the first prime number to be inserted */
      if (nP == 0) {
        vectorPrimoFac[nP].factor = vPrime[i];
        vectorPrimoFac[nP].multiplicity++;
        nP++;
        break;
      }
      /* this is not the first prime to be inserted, we must check if this
      is a new prime to be inserted */
      for (j = 0; j < nP; j++) {
        if (vectorPrimoFac[j].factor == vPrime[i]) {
          vectorPrimoFac[j].multiplicity++;
          repeat = 1;
          break;
        }
      }
      /* in the case of a new prime we have to insert the new prime */
      if (repeat != 1) {
          if (nP < (sizeVector*mult)) {
            vectorPrimoFac[nP].factor = vPrime[i];
            vectorPrimoFac[nP].multiplicity++;
            nP++;
          } else if (nP == (sizeVector*mult) ) {
            mult++;
            vectorPrimoFac = (factorization*) realloc (vectorPrimoFac, sizeVector*mult*sizeof (factorization));
            if (vectorPrimoFac == NULL) {
              printf ("\nThere was an error in the memory reallocation of the vector factorization.");
              return NULL;
            }
            vectorPrimoFac[nP].factor = vPrime[i];
            vectorPrimoFac[nP].multiplicity++;
            nP++;
        }
      }
      /* I have now to start back by the lower prime factors */
      break;
    }
  }
}
vectorPrimoFac = (factorization*) realloc (vectorPrimoFac, nP*sizeof(factorization));
if (vectorPrimoFac == NULL) {
  return NULL;
}
*n = nP;
return vectorPrimoFac;
}
/******************************************************************************/
int factorizationNSquare (factorization *fac, int n) {
/* this function takes the array of factorization of nTeste and calculate the
factorization of nTeste² and then returns 1 if all ok or 0 if there was a
problem in this function */
if (fac == NULL) {
  return 0;
}
int i;
for (i = 0; i < n; i++) {
  fac[i].multiplicity*=2;
}
return 1;
}
/******************************************************************************/
int numberOfDivisor (factorization *fac, int dimV) {
/* this function calculates the number of divisors of the number nTest² and
then return the number or 0 if there was a problem in the function */
if (fac == NULL || dimV < 0) {
  return 0;
}
int i, nDiv = 1;
for (i = 0; i < dimV; i++) {
  nDiv*=(fac[i].multiplicity+1);
}
return nDiv;
}
/******************************************************************************/
