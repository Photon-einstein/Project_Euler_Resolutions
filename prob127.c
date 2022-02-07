#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define CMAX 120000
typedef struct {
  int factor;
  int multiplicity;
} factorization;
typedef struct {
  factorization *fac;
  int number;
  int nFactors;
} matrix;
/* Iterative binary algorithm - gcd */
int gcd_iter(int u, int v);

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

/* this function makes the factorization of a number nTest, and stores the
prime factors in an array dinamicaly made, and also the index of each factor.
It returns also by reference the number of prime numbers that has made the
factorization */
factorization* factorizacaoVecProduz (int nTest, int *vPrime, int nPrime,
  int *n, int sizeVector);

/* this function makes the saving of future composite numbers in the array v,
and returns 1 if all went ok or 0 if there was a problem in the function */
int composeNumbersSaving (char *v, int prime, int sizeMax);

/* this function makes the calculation of the rad and then returns the rad or
-1 if there was a problem in the function */
int radCalc (factorization *fac, int sizeFac);

/* this function makes the calculation of the number of prime numbers in the
triplet (a,b,c), and then returns the number of primes or -1 if there was a
problem in this function */
int nPrimesCount (char *primeBool, int a, int b, int c);

/* this function makes the calculation of the rad(a,b,c) and then returns the
value or 0 if there was a problem in the function */
int radabcCalc (factorization *fa, int nPa, factorization *fb, int nPb,
  factorization *fc, int nPc);

/* this function returns the gcd of the numbers a and b, and then returns the
gcd or -1 if there was a problem in the function, 1-mode fast, 0-mode slow */
int gcd_own (factorization *fa, int nFactorA, factorization *fb, int nFactorB, int mode);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int a, b, c, nHits=0, *vPrime, maxSizePrime, cMax, mult=1, aMax, bMax;
long long int sumHits=0, rad;
char *primeBool; /* 0 not processed, 1 prime, 2 not prime */
int boolean, nPrime=0, nPa, nPb, nPc, i, mode=1, *radV;
matrix *m;
cMax = CMAX;
aMax = cMax/2;
bMax = cMax-1;
maxSizePrime = cMax/5;
/* prime array memory allocation */
vPrime = (int*) calloc (maxSizePrime, sizeof (int));
if (vPrime == NULL) {
  printf("\nThere was a problem in the memory allocation.");
  return 0;
}
primeBool = (char*) calloc (cMax, sizeof (char));
if (primeBool == NULL) {
  printf("\nThere was a problem in the memory allocation.");
  return 0;
}
/* prime fulling */
for (a = 2; a < cMax; a++) {
  if (primeBool[a] == 0) {
    /* number not yet processed */
    boolean = primeTest (a);
    if (boolean == -1) {
      printf("\nThere was a problem in the function primeTest.");
    } else if (boolean == 1) {
      /* prime number found */
      /* compose number fulling */
      boolean = composeNumbersSaving (primeBool, a, cMax);
      if (boolean == 0) {
        printf("\nThere was a problem in the function composeNumbersSaving.");
        return 0;
      }
      /* prime storing */
      primeBool[a] = 1;
      if (nPrime == maxSizePrime) {
        /* reallocation */
        mult++;
        maxSizePrime*=mult;
        vPrime = (int*) realloc (vPrime, maxSizePrime*sizeof(int));
        if (vPrime == NULL) {
          printf("\nThere was a problem in the reallocation of vPrimes.");
        }
      }
      vPrime[nPrime]=a;
      nPrime++;
    }
  }
}
/* factorization matrix */
m = (matrix*) calloc (cMax, sizeof (matrix));
if (m == NULL) {
  printf("\nThere was an error in the memory allocation of m.");
  return 0;
}
for (i = 1; i < cMax; i++) {
  if (primeBool[i]==1 || i == 1) {
    /* prime number */
    m[i].number = i;
    m[i].fac = (factorization*) calloc (1, sizeof (factorization));
    if (m[i].fac == NULL) {
      printf("\nThere was an error in the factorization.");
      return 0;
    }
    m[i].fac[0].factor = i;
    m[i].fac[0].multiplicity = 1;
    m[i].nFactors = 1;
  } else {
    m[i].fac = factorizacaoVecProduz (i, vPrime, nPrime,
      &m[i].nFactors, 100);
    if (m[i].fac == NULL) {
      printf("\nThere was an error in the function factorizacaoVecProduz.");
      return 0;
    }
  }
}
/* precomputation of rad values */
radV = (int*) calloc (cMax+1, sizeof (int));
if (radV == NULL) {
  printf ("\nThere was an error in the memory allocation of radV.");
  return 0;
}
for (i = 1; i < cMax; i++) {
  boolean = radCalc (m[i].fac, m[i].nFactors);
  if (boolean == -1) {
    printf("\nThere was an error in the function radCalc.");
    return 0;
  }
  radV[i] = boolean;
}
/* testing selected a, b and c */
for (a = 1; a < aMax+1; a++) {
  for (b = a+1; b < cMax+1; b++) {
    /* exit condition */
    c = a + b;
    if (c >= cMax) {
      break;
    }
    /* test number of primes */
    boolean = nPrimesCount (primeBool, a, b, c);
    if (boolean == -1) {
      printf("\nThere was a problem in the function nPrimesCount.");
      return 0;
    } else if (boolean >=2) {
      /* number of primes >= 2, no need to further tests */
      continue;
    }
    /* now we have to calculate rad (a.b.c) */
    rad = radV[a];
    rad*=radV[b];
    if (rad >= c) {continue;}
    rad*=radV[c];
    /* test: rad (a.b.c) < c */
    if (rad < c && rad > 1) {
      /* gcd test */
      boolean = gcd_own (m[a].fac, m[a].nFactors, m[b].fac, m[b].nFactors,mode);
      if (boolean == 1) {
        /* new answer found */
        nHits++;
        sumHits+=c;
      }
    }
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nFor c < %d there are only %d abc-hits with the sum of c = %lld.", cMax, nHits, sumHits);
printf("\n");
/* free memory */
free (vPrime);
free (primeBool);
for (i = 0; i < cMax; i++) {
  free (m[i].fac);
}
free (m);
return 0;
}
/******************************************************************************/
int gcd_iter(int u, int v) {
  if (u < 0) u = -u;
  if (v < 0) v = -v;
  if (v) while ((u %= v) && (v %= u));
  return (u + v);
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
int composeNumbersSaving (char *v, int prime, int sizeMax) {
/* this function makes the saving of future composite numbers in the array v,
and returns 1 if all went ok or 0 if there was a problem in the function */
if (v == NULL || prime < 2 || sizeMax < 1) {
  return 0;
}
int n, i = 2;
while (1) {
  n = prime*i;
  /* exit condition */
  if (n >= sizeMax) {
    return 1;
  }
  v[n]=2;
  i++;
}
}
/******************************************************************************/
int radCalc (factorization *fac, int sizeFac) {
/* this function makes the calculation of the rad and then returns the rad or
-1 if there was a problem in the function */
if (fac == NULL || sizeFac < 1) {
  return -1;
}
int res = 1, i;
for (i = 0; i < sizeFac; i++) {
  res*=fac[i].factor;
}
return res;
}
/******************************************************************************/
int nPrimesCount (char *primeBool, int a, int b, int c) {
/* this function makes the calculation of the number of prime numbers in the
triplet (a,b,c), and then returns the number of primes or -1 if there was a
problem in this function */
if (primeBool == NULL) {
  return -1;
}
int nPrimes = 0,i[3], dim = 3, k;
i[0] = a;
i[1] = b;
i[2] = c;
for (k = 0; k < dim; k++) {
  if (i[k] == 1) {
    nPrimes++;
  }
}
return nPrimes;
}
/******************************************************************************/
int radabcCalc (factorization *fa, int nPa, factorization *fb, int nPb,
  factorization *fc, int nPc) {
/* this function makes the calculation of the rad(a,b,c) and then returns the
value or 0 if there was a problem in the function */
if (fa == NULL || nPa < 1 || fb == NULL || nPb < 1 || fc == NULL || nPc < 1) {
  return 0;
}
int *factors, dimFactors, i, j, radabc=1;
dimFactors = nPa + nPb + nPc;
factors = (int*) calloc (dimFactors, sizeof (int));
if (factors == NULL) {
  return 0;
}
/* copy of the values */
j = 0;
/* fa */
for (i = 0; i < nPa; i++) {
  factors[i] = fa[i].factor;
  j++;
}
/* fb */
for (i = 0; i < nPb; i++) {
  factors[j] = fb[i].factor;
  j++;
}
/* fc */
for (i = 0; i < nPc; i++) {
  factors[j] = fc[i].factor;
  j++;
}
/* erasing repeated values */
for (i = 0; i < dimFactors-1; i++) {
  for (j = i+1; j < dimFactors; j++) {
    if (factors[i] == factors[j] && factors[i] != 0) {
      /* repeated factor, erase the upper factor */
      factors[j] = 0;
    }
  }
}
/* calculating the rad (a,b,c) */
for (i = 0; i < dimFactors; i++) {
  if (factors[i] != 0) {
    radabc*=factors[i];
  }
}
/* free memory */
free (factors);
return radabc;
}
/******************************************************************************/
int gcd_own (factorization *fa, int nFactorA, factorization *fb, int nFactorB, int mode) {
/* this function returns the gcd of the numbers a and b, and then returns the
gcd or -1 if there was a problem in the function, 1-mode fast, 0-mode slow */
if (fa == NULL || fb == NULL || nFactorA < 1 || nFactorB < 1) {
  return -1;
}
int gcd = 1, i, j;
if (mode == 1) {
  for (i = 0; i < nFactorA; i++) {
    for (j = 0; j < nFactorB; j++) {
      if (fa[i].factor == fb[j].factor) {
        /* update gcd */
        return 2;
      }
    }
  }
  return gcd;
} else {
  for (i = 0; i < nFactorA; i++) {
    for (j = 0; j < nFactorB; j++) {
      if (fa[i].factor == fb[j].factor) {
        /* update gcd */
        if (gcd < fa[i].factor) {
          gcd = fa[i].factor;
        }
      }
    }
  }
  return gcd;
}
}
/******************************************************************************/
