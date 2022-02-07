#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define DIM 8000
#define MAX 100000000

typedef struct {
  int prime;
  int mult;
} primeID;

/* this function makes the factorization of the number nTest, and it stores
the prime numbers in an array, allocated dinamicaly, and it also returns by
reference in n, the number of primes that made the nTest factorization,  or
NULL if there was an error in the function */
primeID* factorizationVecMake (int nTest, int *vPrime, int nPrimes, int *n);

/* this function makes the calculation of the sum of the divisors of a given
number, that has a factorization in v, with size, and returns the value of
sigma1 if all ok or 0 if there was a problem in the function */
int sigma1Calc(primeID *v, int size, int n);

/* this function makes the calculation of the final result and in the end it
returns the result greater than 0 if all was ok or equal to 0 if there was a
problem in the function */
long long int finalResultCalc(int max, int *vPrime, int nPrime, char *binaryPrime);

/* this function makes the calculation of the sum of the sumSigma1Divisors,
and in the end it returns the number if all ok or -1 if there was a problem
in the function, and also retuns by reference the value of the sum of the
divisors of n, sigma1 */
int sumSigma1Divisors(int *sigma1Gauss, int n, int* sigma1);

/* this function makes the sum of the real parts of the diophantine equation
x²+y²=n, and in the end it returns the result for the solutions x²+y² = n,
for greater solutions such that x²+y²>n it is returned by reference using
nGSolGreaterN */
int diophantineSolver(int n, int *nSumSolGreaterN);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
long long int res=0;
int *vPrime, sizevPrimeMax, nPrime=0, x, boolean, i=0;
char *binaryPrime, c;
FILE *f;
x = MAX/2+MAX/100;
sizevPrimeMax = x/(log(x)-1);
/* memory allocation of the vPrime array */
vPrime = (int*) calloc(sizevPrimeMax, sizeof (int));
if (vPrime == NULL) {
  printf("\nThere was an error in the memory allocation of vPrime.");
  return 0;
}
/* memory allocation of binary prime */
binaryPrime = (char*) calloc(MAX, sizeof (char));
if (binaryPrime == NULL) {
  printf("\nThere was an error in the memory allocation of binaryPrime.");
  return 0;
}
/* open prime file */
f = fopen("primes.txt", "r");
if (f == NULL) {
  printf("\nThere was an error opening primes.txt.");
  return 0;
}
/* read prime file */
while ((fscanf(f, "%d", &vPrime[nPrime++]))!= EOF) {}
/* memory reallocation */
vPrime = (int*)realloc(vPrime, nPrime*sizeof (int));
if (vPrime == NULL) {
  printf("\nThere was an error in the nPrime memory reallocation.");
  return 0;
}
/* close prime file */
fclose(f);
/* open binary prime file */
f = fopen("primes_binary.txt", "r");
if (f == NULL) {
  printf("\nThere was an error opening primes_binary.txt.");
  return 0;
}
/* read prime file */
while ((fscanf(f, "%c", &binaryPrime[i++]))!= EOF && fgetc(f) != EOF) {}
/* close prime file */
fclose(f);
/* processing the final result */
res = finalResultCalc(MAX, vPrime, nPrime, binaryPrime);
if (res == 0) {
  printf("\nThere was a problem in the function finalResultCalc.");
  return 0;
}
/* free memory */
free(vPrime);
free(binaryPrime);
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nThe sum of all the divisors s(n) for n = %d is %lld", MAX, res);
printf("\n");
return 0;
}
/******************************************************************************/
primeID* factorizationVecMake (int nTest, int *vPrime, int nPrimes, int *n) {
/* this function makes the factorization of the number nTest, and it stores
the prime numbers in an array, allocated dinamicaly, and it also returns by
reference in n, the number of primes that made the nTest factorization, or
NULL if there was an error in the function */
if (vPrime == NULL || n == NULL || nPrimes < 1) {
  printf("\nThere was an error in the parameters of factorizacaoVecMake.");
  return NULL;
}
int nTesteM = nTest, nP = 0, i, mult = 1, repeat = 0, j;
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
*n = nP;
return vectorPrimeFac;
}
/******************************************************************************/
int sigma1Calc(primeID *v, int size, int n) {
/* this function makes the calculation of the sum of the divisors of a given
number, that has a factorization in v, with size, and returns the value of
sigma1 if all ok or 0 if there was a problem in the function */
int sum=1, i;
if (n <= 5) {
  fflush(NULL);
}
for (i = 0; i < size; ++i) {
  if (n <= 5) {
    fflush(NULL);
  }
  sum*=(int)(pow(v[i].prime, v[i].mult+1)-1.0)/(v[i].prime-1.0);
}
return sum;
}
/******************************************************************************/
long long int finalResultCalc(int max, int *vPrime, int nPrime, char *binaryPrime) {
/* this function makes the calculation of the final result and in the end it
returns the result greater than 0 if all was ok or equal to 0 if there was a
problem in the function */
if (vPrime == NULL || binaryPrime == NULL || nPrime < 1) {
  return 0;
}
long long int res = 0;
int n, stepBinary=0, *sigma1Gauss, size, boolean, sigma1, aux, b,nSumSolGreaterN;
primeID *p;
/* memory allocation */
sigma1Gauss = (int*) calloc(max+1, sizeof(int));
if (sigma1Gauss == NULL) {
  return 0;
}
/* first case # 1 */
res+=1;
/* second case # 2 */
sigma1Gauss[2] = 2;
res+=5;
for (n = 3; n < max+1; ++n) {
  if (n%1000 == 0) {
    printf("\nn = %d", n);
  }
  aux = 0;
  sigma1 = 0;
  if (n%2!= 0 && binaryPrime[n-2]=='1' && n%4==3) {
    /* prime of the form n mod 4 = 3, sigma1Gauss[n] = 0 */
    sigma1=n+1;
    aux = sigma1;
    res+=sigma1;
  } else if (n%2!= 0 && binaryPrime[n-2]=='1') {
    /* prime of the form n mod 4 = 1 */
    sigma1Gauss[n] = diophantineSolver(n, &nSumSolGreaterN);
    sigma1 = 1+n;
    aux = sigma1+sigma1Gauss[n]+nSumSolGreaterN;
    res+=aux;
  } else {
    /* composit number */
    boolean=sumSigma1Divisors(sigma1Gauss, n, &sigma1);
    if (boolean == -1) {
      printf("\nThere was an error in the function sumSigma1Divisors.");
      return 0;
    }
    aux=boolean;
    sigma1Gauss[n] = diophantineSolver(n, &nSumSolGreaterN);
    aux+=sigma1+sigma1Gauss[n]+nSumSolGreaterN;
    res+=aux;
    /* free memory */
    free(p);
  }
  /* debugging */
  if (n <= 300) {
    printf("\nGauss(%d) = %d", n, sigma1Gauss[n]);
    printf("\nSumSolGreaterN(%d) = %d", n, nSumSolGreaterN);
    printf("\nSigma1(%d) = %d", n, sigma1);
    printf("\ns(%d) = %d",n, aux);
    printf("\ns(n) up to %d = %lld\n", n,res);
    /* out condition */
    if (n == 300) {
      break;
    }
  }
}
/* free memory */
free(sigma1Gauss);
return res;
}
/******************************************************************************/
int sumSigma1Divisors(int *sigma1Gauss, int n, int *sigma1) {
/* this function makes the calculation of the sum of the sumSigma1Divisors,
and in the end it returns the number if all ok or -1 if there was a problem
in the function, and also retuns by reference the value of the sum of the
divisors of n, sigma1 */
if (sigma1Gauss == NULL || n < 1) {
  return -1;
}
int res=0, div, maxDiv=n/2+1, sumDiv = n+1;
for (div = 2; div <= maxDiv; ++div) {
  if (n%div==0) {
    res+=sigma1Gauss[div];
    sumDiv+=div;
  }
}
*sigma1=sumDiv;
return res;
}
/******************************************************************************/
int diophantineSolver(int n, int *nSumSolGreaterN) {
/* this function makes the sum of the real parts of the diophantine equation
x²+y²=n, and in the end it returns the result for the solutions x²+y² = n,
for greater solutions such that x²+y²>n it is returned by reference using
nSumSolGreaterN */
int res=0, x,y, arg, nSumG=0;
if (n%2==0) {
  res+=n;
}
for (x = 1; (x*x+(x+1)*(x+1)) <= n*x ; ++x) {
  for (y = x+1; n*x >= (x*x+y*y) && n*y >= (x*x+y*y); ++y) {
    arg = x*x+y*y;
    if (n*x%arg==0 && n*y%arg==0 && arg >= n) {
      if (arg == n) {
        res+=2*x+2*y;
      } else {
        nSumG+=2*x+2*y;
      }
      printf("\nn(in) = %d: x = %d | y = %d", n, x, y);
    } else if (n*x%arg==0 && n*y%arg==0 && arg < n && n%arg!=0) {
      nSumG+=2*x+2*y;
      printf("\nn(out) = %d: x = %d | y = %d", n, x, y);
    }
  }
}
*nSumSolGreaterN=nSumG;
return res;
}
/******************************************************************************/
