#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX 1000000
#define MAXFACTOR 200
#define MAXCHAIN 400
typedef struct {
  int factor;
  int multiplicidade;
} factorization;

typedef struct {
  int number;
  int booleanoPrimo; /* 0 if not prime or 1 if prime */
  factorization *vP; /* in the case of not prime numbers */
  int nFactors; /* in the case of not prime numbers */
  int sumProperDivisor;
  int sumPdOverflow; /* 0 if not overflow and 1 if overflow */
  int booleanoChainAmicable; /* 0 if not amicable, 1 if amicable, -1 if not processed */
  int chainSize; /* if booleanoChainAmicable = 1 */
} sumP;

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not */
int primeTeste (int nTeste, int *vPrimos, int nPrimos);

/* this function makes the factorization of a number nTest, and stores the
prime factors in an array dinamicaly made, and also the index of each factor.
I returns also by reference the number of prime numbers that has made the
factorization */
factorization* factorizacaoVecProduz (int nTeste, int *vPrimos, int nPrimos, int *n, int sizeVector);

/* this funtion returns the sigma1 calculation */
int sigma1 (int primeFactor, int multiplicity);

/* this function verifies it this is an amicable chain, if no it returns -1, if
yes then return the position of the element equal to the lastElement */
int chainAmicableVerify (int *chain, int sizeChain, int lastElement);

/* this function returns the minimal element of an integer array, from start to
end point */
int minCalculate (int *chain, int startP, int endP);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int n = 2, *primoV, nPrimos = 0, mult = 1, max, booleano, realSize, i, overflow = 0;
int maxChainSize = 0, lowerMember = 1000000, *chain, sizeChain, out, nC, smaller;
int start, end, j;
sumP *v;
/* Part 1: prime array and factorization of non prime number */
v = (sumP*) calloc (MAX, sizeof (sumP));
if (v == NULL) {
  printf ("\nThere was a problem in the generation of the vector v.");
  return 0;
}

/* I am now going to create the vector to contain the prime values */
max = MAX;
realSize = max/4;
primoV = (int*) calloc (realSize, sizeof (int));
if (primoV == NULL) {
  printf ("\nOcorreu um erro a criar o vector primoV.");
  return 0;
}

for (n = 2; n < max+1; n++) {
  /*printf ("\nn = %d", n);*/
  booleano = primeTeste (n, primoV, nPrimos);
  if (booleano == 1) {
    v[n].number = n;
    v[n].sumProperDivisor = 1;
    v[n].booleanoPrimo = 1;
    v[n].booleanoChainAmicable = 0;
    v[n].chainSize = 0;
    /* primeVector full, situation of realloc */
    if (nPrimos == (realSize*mult)) {
      mult++;
      printf ("\nThere was an overflow of the prime vector, there was a realloc done.");
      primoV = (int*) realloc (primoV, (mult*realSize)*sizeof (int));
      if (primoV == NULL) {
        printf ("\nThere was an error in the realloc of the vector primeV.");
        return 0;
      }
    }
    /* value actualization */
    primoV[nPrimos] = n;
    nPrimos++;
    continue;
  } else {
    /* in this situation there is now prime number */
    v[n].vP = factorizacaoVecProduz (n, primoV, nPrimos, &v[n].nFactors, MAXFACTOR);
    if (v[n].vP == NULL) {
      printf ("\nThere was an error in the function factorizacaoVecProduz.");
      return 0;
    }
    v[n].sumProperDivisor = 1;
    for (i = 0; i < v[n].nFactors; i++) {
      v[n].sumProperDivisor = v[n].sumProperDivisor * sigma1 (v[n].vP[i].factor, v[n].vP[i].multiplicidade);
      if ((v[n].sumProperDivisor-n) > MAX) {
        v[n].sumPdOverflow = 1;
        break;
      }
    }
    if ((v[n].sumProperDivisor-n) <= MAX) {
      v[n].sumProperDivisor = v[n].sumProperDivisor - n;
      v[n].sumPdOverflow = 0;
    } else {
      v[n].sumPdOverflow = 1;
      overflow++;
    }
    /*printf ("\n");
    printf ("\nFactorizacao de %d: ", n);
    printf ("\nThe number %d has sum of proper divisores of %d wirh overflow = %d.", n, v[n].sumProperDivisor, v[n].sumPdOverflow);*/
  }
}
printf ("\nThere are %d prime numbers until %d.", nPrimos, max);
/* prime and factorization memory free */
free(primoV);
for (i = 0; i < max+1; i++) {
  v[i].booleanoChainAmicable = -1;
  if (v[i].booleanoPrimo == 0) {
    free (v[i].vP);
  }
}
/* Part 2: chain sequences processing */
for (i = 2; i < max+1; i++) {
/* situation that don´t need to be processed */
if (v[i].booleanoPrimo == 1) {
  continue;
} else if (v[i].sumPdOverflow == 1) {
  continue;
} else if (v[i].booleanoChainAmicable == 0 || v[i].booleanoChainAmicable == 1) {
  continue;
}
/* if it reaches here then it is a proper number to begin */
/* new chain created */
chain = (int*) calloc (MAXCHAIN, sizeof (int));
if (chain == NULL) {
  printf ("\nThere was an error in the creation of the chain vector.");
  return 0;
}
out = 0;
mult = 1;
/* first element of the chain */
chain[0] = i;
sizeChain = 1;
  while (out == 0) {
    nC = chain[sizeChain-1];
    if (v[nC].sumPdOverflow == 0) {
      chain[sizeChain] = v[nC].sumProperDivisor;
      sizeChain++;
    } else {
      /* chain with overflow member */
      free (chain);
      break;
    }
    /* if this is full chain, it needs to be reallocated */
    if (sizeChain == MAXCHAIN*mult) {
      mult++;
      chain = (int*) realloc (chain, mult*MAXCHAIN*sizeof (int));
      if (chain == NULL) {
        printf ("\nThere was an error in the reallocation of the chain vector.");
        return 0;
      }
    }
    /* now we need to see if there are amicable chains */
    if (sizeChain > 1) {
      booleano = chainAmicableVerify (chain, sizeChain, chain[sizeChain-1]);
      if (booleano == -1) {
        continue;
      } else {
        /* there was an amicable chain found */
        out = 1;
        nC = chain[sizeChain-1];
        v[nC].booleanoChainAmicable = 1;
        start = booleano;
        end = sizeChain-1;
        realSize = end-start;
        if (maxChainSize < realSize) {
          maxChainSize = realSize;
          smaller = minCalculate (chain, start, end);
          /*printf ("\nNovo minimo %d para maxChainSize = %d.", smaller, maxChainSize);*/
          lowerMember = smaller;
          if (realSize > 0) {
            for (j = 0; j < sizeChain; j++) {
              if (j == start || j == end) {
                continue;
              }
              v[chain[j]].booleanoChainAmicable = 0;
            }
          }
        }
        /*if (realSize > 0 && chain[end] != 0) {
          printf ("\nNew chain found for i = %d: ", i);
          for (j = start; j < end+1; j++) {
            printf ("%d ", chain[j]);
          }
        }*/
        free(chain);
      }
    }
  }
}
/* memory free */
free (v);
printf ("\nThere are %d overflows.", overflow);

/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nThe minimal element of the longest amicable chain is %d whith maxSize %d.", lowerMember, maxChainSize);
printf ("\n");
return 0;
}
/******************************************************************************/
int primeTeste (int nTeste, int *vPrimos, int nPrimos) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not */
int i, comparador;
if (nTeste <= 1) {
	return 0;
}
if (nTeste  == 2) {
	return 1;
} else if (nTeste % 2 == 0) {
	return 0;
}
if (nTeste > 100) {
  comparador = sqrt (nTeste+1);
  for (i = 0; i < nPrimos; i++) {
    if (vPrimos[i] > comparador) {
      /* case of prime number */
      return 1;
    }
    if (nTeste % vPrimos[i] == 0) {
      /* case of not prime */
      return 0;
    }
  }
}
for (i = 3; i < sqrt(nTeste+1); i = i+2) {
	if (nTeste % i == 0) {
		return 0;
	}
}
/* if it reaches here, then it is a prime number */
return 1;
}
/******************************************************************************/
factorization* factorizacaoVecProduz (int nTeste, int *vPrimos, int nPrimos, int *n, int sizeVector) {
/* this function makes the factorization of a number nTest, and stores the
prime factors in an array dinamicaly made, and also the index of each factor.
I returns also by reference the number of prime numbers that has made the
factorization */
int nTesteM = nTeste, nP = 0, i, mult = 1, repeat = 0, j;
factorization *vectorPrimoFac;

vectorPrimoFac = (factorization*) calloc (sizeVector*mult, sizeof (factorization));
if (vectorPrimoFac == NULL) {
  printf ("\nThere was an error in the memory allocation of the vector factorization.");
  return NULL;
}
while (nTeste != 1) {
  repeat = 0;
  for (i = 0; i < nPrimos; i++) {
    if (nTeste % vPrimos[i] == 0) {
      nTeste = nTeste / vPrimos[i];
      /* I am now going to verify if that prime number is also in the array of vectorPrimoFac */
      /* situation in that this is the first prime number to be inserted */
      if (nP == 0) {
        vectorPrimoFac[nP].factor = vPrimos[i];
        vectorPrimoFac[nP].multiplicidade++;
        nP++;
        break;
      }
      /* this is not the first prime to be inserted, we must check if this
      is a new prime to be inserted */
      for (j = 0; j < nP; j++) {
        if (vectorPrimoFac[j].factor == vPrimos[i]) {
          vectorPrimoFac[j].multiplicidade++;
          repeat = 1;
          break;
        }
      }
      /* in the case of a new prime we have to insert the new prime */
      if (repeat != 1) {
          if (nP < (sizeVector*mult)) {
            vectorPrimoFac[nP].factor = vPrimos[i];
            vectorPrimoFac[nP].multiplicidade++;
            nP++;
          } else if (nP == (sizeVector*mult) ) {
            mult++;
            vectorPrimoFac = (factorization*) realloc (vectorPrimoFac, sizeVector*mult*sizeof (factorization));
            if (vectorPrimoFac == NULL) {
              printf ("\nThere was an error in the memory reallocation of the vector factorization.");
              return NULL;
            }
            vectorPrimoFac[nP].factor = vPrimos[i];
            vectorPrimoFac[nP].multiplicidade++;
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
int sigma1 (int primeFactor, int multiplicity) {
/* this funtion returns the sigma1 calculation */
int calc;
calc = (pow(primeFactor,multiplicity+1)-1) / (primeFactor-1);
return calc;
}
/******************************************************************************/
int chainAmicableVerify (int *chain, int sizeChain, int lastElement) {
/* this function verifies it this is an amicable chain, if no it returns -1, if
yes then return the position of the element equal to the lastElement */
int i;
for(i = 0; i < sizeChain-1; i++) {
  if (chain[i] == lastElement) {
    return i;
  }
}
/* if it reaches here then there are no amicable chains */
return -1;
}
/******************************************************************************/
int minCalculate (int *chain, int startP, int endP) {
/* this function returns the minimal element of an integer array, from start to
end point */
int i, min = chain[startP];
for (i = startP+1; i < endP+1; i++) {
  if (min > chain[i]) {
    min = chain[i];
  }
}
return min;
}
/******************************************************************************/
