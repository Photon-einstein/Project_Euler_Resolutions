#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include "tabdispersao.h"
#define MIN 1
#define MAX 9
#define DIM 100
typedef long long int lli;
typedef struct {
  int prime;
  int mult;
} primeID;

/* this function makes the factorization of the number nTest, and it stores
the prime numbers in an array, allocated dinamicaly, and it also returns by
reference in n, the number of primes that made the nTest factorization,  or
NULL if there was an error in the function */
primeID* factorizationVecMake (long long int nTest, int *vPrime, int nPrimes, int *n);

/* this function makes the calculation of the sigma zero parameter and in the
end it returns the value or -1 if there was an error in the function */
int sigmaZeroCalc(primeID *v, int size_fact);

/* this function makes the fulling of the sieveFulling and in the end it returns
1 if all ok or 0 if there was a problem in the function */
int sieveFulling(char *sieve, int maxSieve);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int r, s, res=0, res_n=0, nMin=MIN, nMax=MAX, n;
int nPrimes, size_fact, boolean2, maxPower;
char *sieve, word[100], word2[100];
lli p_line, y, power_ten, two_over_r, boolean, size_sieve, x_, i, j;
int *vPrime;
tabela_dispersao *td;
primeID *fact;
/* sieve memory allocation */
if (nMax < 7) {
  maxPower = nMax;
} else {
  maxPower = 7;
}
size_sieve = 2*pow(7,nMax);
sieve = (char*) calloc(size_sieve+1, sizeof(char));
/* sieve fulling */
nPrimes = sieveFulling(sieve, size_sieve);
if (nPrimes == 0) {
  printf("\nThere was a problem in the function sieveFulling.");
  return 0;
}
/* prime memory allocation */
vPrime = (int*) calloc(nPrimes, sizeof (int));
if (vPrime == NULL) {
  printf("\nThere was a problem in the memory allocation of vPrimes.");
  return 0;
}
for (i = 2, j=0; i < size_sieve+1; ++i) {
  if (sieve[i] == '1') {
    vPrime[j] = i;
    ++j;
  }
}
/* free memory */
free(sieve);
/* cycle to run n */
for (n = nMin; n <= nMax; ++n) {
  td = tabela_nova(10000, hash_djbm);
  if (td == NULL) {
    printf("\nThere was a problem in the function tabela_nova.");
    return 0;
  }
  res_n = 0;
  power_ten = pow(10.0, n);
  /* cycle run */
  /* x = 2^r and y = 5^s */
  for (r = 0; r <= n; ++r) {
    x_ = pow(2.0,r);
    for (s = 0; s <= n; ++s) {
      y = pow(5.0,s);
      if (x_ > y) {
        continue;
      }
      if (y > power_ten) {
        break;
      }
      /* if it reaches here then we have a new valid pair (x,y) with gcd(x,y)=1 */
      p_line = (x_+y)*(power_ten/(x_*y));
      if (p_line > 2*power_ten) {
        continue;
      }
      /* check if we have a new solution */
      sprintf(word2,"%lld|%lld", x_*p_line, y*p_line);
      boolean2 = tabela_existe(td, word2);
      if (boolean2 == TABDISPERSAO_NAOEXISTE) {
        /* factorization calc */
        fact = factorizationVecMake (p_line, vPrime, nPrimes, &size_fact);
        if (fact == NULL) {
          printf("\nThere was an error in the function factorizacaoVecMake.");
          return 0;
        }
        boolean = sigmaZeroCalc(fact, size_fact);
        if (boolean == -1) {
          printf("\nThere was an error in the function sigmaZeroCalc.");
          return 0;
        }
        tabela_insere(td, word2, "");
        res_n+=boolean;
        /* free memory */
        free(fact);
      }
    }
  }
  /* x = 1 and y = 2^r*5^s */
  for (r = 0; r <= n; ++r) {
    x_=1;
    two_over_r = pow(2.0,r);
    for (s = 0; s <= n; ++s) {
      y = two_over_r*pow(5.0,s);
      if (x_ > y) {
        continue;
      }
      if (y > power_ten) {
        break;
      }
      /* if it reaches here then we have a new valid pair (x,y) with gcd(x,y)=1 */
      p_line = (x_+y)*(power_ten/(x_*y));
      if (p_line > 2*power_ten) {
        continue;
      }
      /* check if we have a new solution */
      sprintf(word2,"%lld|%lld", x_*p_line, y*p_line);
      boolean2 = tabela_existe(td, word2);
      if (boolean2 == TABDISPERSAO_NAOEXISTE) {
        /* factorization calc */
        fact = factorizationVecMake (p_line, vPrime, nPrimes, &size_fact);
        if (fact == NULL) {
          printf("\nThere was an error in the function factorizacaoVecMake.");
          return 0;
        }
        boolean = sigmaZeroCalc(fact, size_fact);
        if (boolean == -1) {
          printf("\nThere was an error in the function sigmaZeroCalc.");
          return 0;
        }
        tabela_insere(td, word2, "");
        res_n+=boolean;
        /* free memory */
        free(fact);
      }
    }
  }
  /* x = 5^r and y = 2^s */
  for (r = 0; r <= n; ++r) {
    x_ = pow(5.0,r);
    for (s = 0; s <= n; ++s) {
      y = pow(2.0,s);
      if (x_ > y) {
        continue;
      }
      if (y > power_ten) {
        break;
      }
      /* if it reaches here then we have a new valid pair (x,y) with gcd(x,y)=1 */
      p_line = (x_+y)*(power_ten/(x_*y));
      if (p_line > 2*power_ten) {
        continue;
      }
      /* check if we have a new solution */
      sprintf(word2,"%lld|%lld", x_*p_line, y*p_line);
      boolean2 = tabela_existe(td, word2);
      if (boolean2 == TABDISPERSAO_NAOEXISTE) {
        /* factorization calc */
        fact = factorizationVecMake (p_line, vPrime, nPrimes, &size_fact);
        if (fact == NULL) {
          printf("\nThere was an error in the function factorizacaoVecMake.");
          return 0;
        }
        boolean = sigmaZeroCalc(fact, size_fact);
        if (boolean == -1) {
          printf("\nThere was an error in the function sigmaZeroCalc.");
          return 0;
        }
        tabela_insere(td, word2, "");
        res_n+=boolean;
        /* free memory */
        free(fact);
      }
    }
  }
  printf("\nn = %d | res_n = %d | ", n, res_n);
  res+=res_n;
  printf("res = %d", res);
  fflush(NULL);
  tabela_apaga(td);
}
/* free memory */
free(vPrime);
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nFrom %d <= n <= %d there are up to %d solutions.", nMin, nMax, res);
printf("\n");
return 0;
}
/******************************************************************************/
primeID* factorizationVecMake (lli nTest, int *vPrime, int nPrimes, int *n) {
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
int sigmaZeroCalc(primeID *v, int size_fact) {
/* this function makes the calculation of the sigma zero parameter and in the
end it returns the value or -1 if there was an error in the function */
if (v == NULL || size_fact < 1) {
  return -1;
}
int res=1, i;
for (i = 0; i < size_fact; ++i) {
  res*=(v[i].mult+1);
}
return res;
}
/******************************************************************************/
int sieveFulling(char *sieve, int maxSieve) {
/* this function makes the fulling of the sieveFulling and in the end it returns
the number of primes if all ok or 0 if there was a problem in the function */
if (sieve == NULL || maxSieve < 1) {
  return 0;
}
lli i, j;
int nPrime = 0;
/* 0 - not processed | 1 - prime | 2 - composit */
/* 1 is not prime */
sieve[0] = '2';
sieve[1] = '2';
for (i = 2; i < maxSieve+1; ++i) {
  if (sieve[i] == '2') {
    continue;
  }
  /* new prime found */
  ++nPrime;
  sieve[i] = '1';
  for (j = 2*i; j < maxSieve+1; j+=i) {
    sieve[j] = '2';
  }
}
return nPrime;
}
/******************************************************************************/
