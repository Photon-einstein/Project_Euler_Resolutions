#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define N 1000000000000
#define MAX 200000
#define DIM 100
typedef struct {
  int prime;
  int mult;
} primeID;

typedef struct {
  primeID *vP; /* this field contains the array with the factorization of n! */
  int nPrimes; /* this field contains the number of primes in the prime ID array */
  int maxSize; /* this field contains the maximum number of primes in the prime ID, before reallocation is needed */
  int *multGoal; /* this field contains the multiplicity of the factors of 10^12 */
} facID;

/* this function makes the factorization of the number nTest, and it stores
the prime numbers in an array, allocated dinamicaly, and it also returns by
reference in n, the number of primes that made the nTest factorization,  or
NULL if there was an error in the function */
primeID* factorizationVecMake (long long int nTest, int *vPrime, int nPrimes, int *n);

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

/* this function makes the calculation of the final result and then it returns
the answer if all ok or -1 if there was a problem in the function */
long long int resCalc(int **factExp, int max, facID *goal);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int *boolPrime, max=MAX, n, boolean, nPrimes=0, phi_x, *prime_mult, i, j;
int **factExp, *vPrimes;
long long int res, div=N;
facID *fac, goal;
/* memory allocation */
boolPrime = (int*) calloc(max+1, sizeof (int));
if (boolPrime == NULL) {
  printf("\nThere was an error in the memory allocation of boolPrime.");
  return 0;
}
prime_mult = (int*) calloc(max+1, sizeof (int));
if (prime_mult == NULL) {
  printf("\nThere was an error in the memory allocation of prime_mult.");
  return 0;
}
phi_x = max/log(max);
vPrimes = (int*)calloc(2*phi_x, sizeof (int));
if (vPrimes == NULL) {
  printf("\nThere was an error in the memory allocation of vPrimes.");
  return 0;
}
for (n = 2; n <= max; ++n) {
  boolean = primeTest(n);
  if (boolean == -1) {
    printf("\nThere was a problem in the function primeTest.");
    return 0;
  } else if (boolean == 1) {
    /* new prime found */
    boolPrime[n] = 1;
    vPrimes[nPrimes] = n;
    ++nPrimes;
  }
  prime_mult[n]=nPrimes;
}
/* memory reallocation of vPrimes */
vPrimes = (int*) realloc(vPrimes, nPrimes*sizeof (int));
if (vPrimes == NULL) {
  printf("\nThere was an error in the memory reallocation of vPrimes.");
  return 0;
}
/* fac memory allocation */
fac = (facID*) calloc(max+1, sizeof (facID));
if (fac == NULL) {
  printf("\nThere was an error in the memory allocation of the fac array.");
  return 0;
}
goal.vP = factorizationVecMake (div, vPrimes, nPrimes, &goal.nPrimes);
if (goal.vP == NULL) {
  printf("\nThere was an error in the function factorizacaoVecMake.");
  return 0;
}
/* factExp memory allocation */
factExp = (int**) calloc(max+1, sizeof (int*));
if (factExp == NULL) {
  printf("\nThere was an error in the memory allocation of factExp.");
  return 0;
}
for (i = 0; i < max+1; ++i) {
  factExp[i] = (int*) calloc(goal.nPrimes, sizeof (int));
  if (factExp[i] == NULL) {
    printf("\nThere was an error in the memory allocation of factExp[i].");
    return 0;
  }
}
/* fac calculation */
for (n = 2; n < max+1; ++n) {
  fac[n].vP = factorizationVecMake (n, vPrimes, nPrimes, &fac[n].nPrimes);
  if (fac[n].vP == NULL) {
    printf("\nThere was an error in the function factorizacaoVecMake.");
    return 0;
  }
  /* memory allocation of the field multGoal */
  fac[n].multGoal = (int*) calloc(goal.nPrimes, sizeof (int));
  if (fac[n].multGoal == NULL) {
    printf("\nThere was an error in the memory allocation of fac[n].multGoal.");
  }
  /* the idea now is to turn this into a general aproach */
  for (i = 0; i < fac[n].nPrimes; ++i) {
    for (j = 0; j < goal.nPrimes; ++j) {
      if (fac[n].vP[i].prime == goal.vP[j].prime) {
        fac[n].multGoal[j]=fac[n].vP[i].mult;
      }
    }
  }
  /* factExp fulling */
  for (i = 0; i < goal.nPrimes; ++i) {
    factExp[n][i] = factExp[n-1][i]+fac[n].multGoal[i];
  }
}
/* final answer calculation */
res = resCalc(factExp, max, &goal);
/* free memory */
free(prime_mult);
free(boolPrime);
free(vPrimes);
for (n = 0; n <= max; ++n) {
  if (n >= 2) {
    free(fac[n].vP);
    free(fac[n].multGoal);
  }
  free(factExp[n]);
}
free(fac);
free(factExp);
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\nThere are %lld coeficients multiples of (x+y+z)^%lld", res, div);
printf("\n\nTime in seconds: %lf", time);
printf("\n");
return 0;
}
/******************************************************************************/
primeID* factorizationVecMake (long long int nTest, int *vPrime, int nPrimes, int *n) {
/* this function makes the factorization of the number nTest, and it stores
the prime numbers in an array, allocated dinamicaly, and it also returns by
reference in n, the number of primes that made the nTest factorization, or
NULL if there was an error in the function */
if (vPrime == NULL || n == NULL || nPrimes < 1) {
  printf("\nThere was an error in the parameters of factorizacaoVecMake.");
  return NULL;
}
long long int nTesteM = nTest, nP = 0, i, mult = 1, repeat = 0, j;
primeID *vectorPrimeFac;
vectorPrimeFac = (primeID*) calloc (DIM*mult, sizeof (primeID));
if (vectorPrimeFac == NULL) {
  printf ("\nThere was an error in the memory allocation of factorizacaoVecMake.");
  return NULL;
}
while (nTest != 1) {
  repeat = 0;
  for (i = 0; i < nPrimes; ++i) {
    if (nTest % vPrime[i] == 0) {
      nTest/=vPrime[i];
      /* I am now going to check if that prime already is present in vectorPrimeFac */
      /* case it is the first prime number to be inserted */
      if (nP == 0) {
        vectorPrimeFac[nP].prime = vPrime[i];
        vectorPrimeFac[nP].mult+=1;
        ++nP;
        /* reset divisor search */
        break;
      }
      /* test repeated divisor found */
      for (j = 0; j < nP; ++j) {
        if (vectorPrimeFac[j].prime == vPrime[i]) {
          vectorPrimeFac[j].mult+=1;
          repeat = 1;
          /* reset divisor search */
          break;
        }
      }
      /* case that it is not a repeated prime found, and also not the first */
      if (repeat != 1) {
          if (nP < (DIM*mult)) {
            vectorPrimeFac[nP].prime = vPrime[i];
            vectorPrimeFac[nP].mult+=1;
            ++nP;
          } else if (nP == (DIM*mult) ) {
            ++mult;
            vectorPrimeFac = (primeID*) realloc (vectorPrimeFac, DIM*mult*sizeof (primeID));
            if (vectorPrimeFac == NULL) {
              printf ("\nThere was an error in the memory allocation of factorizacaoVecMake.");
              return NULL;
            }
            vectorPrimeFac[nP].prime = vPrime[i];
            vectorPrimeFac[nP].mult+=1;
            ++nP;
        }
      }
      /* I have now to restart by the smalest prime numbers */
      break;
    }
  }
}
/* memory reallocation */
vectorPrimeFac = (primeID*) realloc(vectorPrimeFac, nP*sizeof(primeID));
if (vectorPrimeFac == NULL) {
  printf("\nThere was an error in the memory allocation of vectorPrimeFac.");
  return NULL;
}
*n = nP;
return vectorPrimeFac;
}
/******************************************************************************/
int primeTest (int nTest) {
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
long long int resCalc(int **factExp, int max, facID *goal) {
/* this function makes the calculation of the final result and then it returns
the answer if all ok or -1 if there was a problem in the function */
if (factExp == NULL || max < 1 || goal == NULL) {
  return -1;
}
int i, j, k, p, *expWork, valid, nZeros;
long long int res=0;
expWork = (int*) calloc(goal->nPrimes, sizeof(int));
if (expWork == NULL) {
  printf("\nThere was an error in the memory allocation of expWork.");
  return -1;
}
/* i <= j <= k generation, i+j+k=max */
for (i = 0; i <= max/3; ++i) {
  for (j = i; j <= (max-1)/2; ++j) {
    k = max-i-j;
    if (k < j) {
      break;
    }
    /* max! load values */
    for (p = 0, valid = 1; p < goal->nPrimes && valid == 1; ++p) {
      expWork[p] = factExp[max][p]-factExp[i][p]-factExp[j][p]-factExp[k][p];
      if (expWork[p] < goal->vP[p].mult) {
        valid = 0;
        break;
      }
    }
    /* test if we have another valid triplet */
    if (valid == 1) {
      if (i < j && j < k) {
        /* all indexes are different */
        res+=6;
      } else if ( (i==j && j < k) || (i < j && j == k) ) {
        /* 2 indexes different */
        res+=3;
      } else {
        /* all indexes are equal */
        ++res;
      }
    }
  }
}
return res;
}
/******************************************************************************/
