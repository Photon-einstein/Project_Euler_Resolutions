#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"
#define SIZEANSWER 10000
#define SIZE 100000
#define RAIZ 0
typedef struct {
  int factor;
  int multiplicity;
} factorization;

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTeste (int nTest);

/* this function makes the factorization of a number nTest, and stores the
prime factors in an array dinamicaly made, and also the index of each factor.
It returns also by reference the number of prime numbers that has made the
factorization */
factorization* factorizacaoVecProduz (int nTest, int *vPrime, int nPrime, int *n, int sizeVector);

/* this function makes the saving of future composite numbers in the array v,
and returns 1 if all went ok or 0 if there was a problem in the function */
int composeNumbersSaving (char *v, int prime, int sizeMax);

/* this function makes the calculation of the rad and then returns the rad or
-1 if there was a problem in the function */
int radCalc (factorization *fac, int sizeFac);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int n, size, sizeAnswer, boolean, realSizeHeap = 0, nAux, radAux, booleanP;
int *vPrime, nPrimeMax, nPrime = 0, sizeFac, answer, i, radAnswer;
char *v;
factorization*fac;
elemento *e1, *e2, *et;
heap *h;
size = SIZE;
sizeAnswer = SIZEANSWER;
nPrimeMax = size/5;
/* v allocation */
v = (char*) calloc (size+1, sizeof (char));
if (v == NULL) {
  printf("\nThere was an error in the memory allocation of v.");
  return 0;
}
/* vPrime allocation */
vPrime = (int*) calloc (nPrimeMax, sizeof (int));
if (vPrime == NULL) {
  printf("\nThere was an error in the memory allocation of vPrime.");
  return 0;
}
/* element allocation */
e2 = (elemento*) calloc (1, sizeof (elemento));
if (e2 == NULL) {
  printf("\nThere was an error in the memory allocation of e2.");
  return 0;
}
et = (elemento*) calloc (1, sizeof (elemento));
if (et == NULL) {
  printf("\nThere was an error in the memory allocation of et.");
  return 0;
}
/* heap creation */
h = heap_nova(sizeAnswer);
if (h == NULL) {
  printf("\nThere was a problem in the heap creation.");
  return 0;
}
/* enter cycle */
for (n = 1; n < size+1; n++) {
  if (v[n] == 0) {
    if (n <= 2) {
      booleanP = primeTeste (n);
    } else {
      booleanP = 1;
    }
    if (booleanP == 1) {
      /* prime number saved */
      if (nPrime == nPrimeMax) {
        nPrimeMax*=2;
        vPrime = (int*) realloc (vPrime, nPrimeMax*sizeof (int));
        if (vPrime == NULL) {
          printf("\nThere was an error in the memory allocation of vPrime.");
          return 0;
        }
      }
      /* prime number saved */
      vPrime[nPrime] = n;
      nPrime++;
      /* value insertion in the heap */
      if (n <= sizeAnswer) {
        boolean = heap_insere(h, n, n);
        if (boolean == 0) {
          printf("\nThere was an error in the function heap_insere.");
          return 0;
        }
      } else if (n == (sizeAnswer+1)){
        e1 = h->elementos[RAIZ];
        /* e2 fulling */
        e2->n = n;
        e2->rad = n;
        boolean = maior_que(e2, e1);
        if (boolean == 0) {
          /* e1 > e2, must switch sides */
          e1 =  heap_remove(h);
          if (e1 == NULL) {
            printf("\nThere was an error in the function heap_remove.");
            return 0;
          }
          /* e2 insertion */
          boolean = heap_insere(h, e2->rad, e2->n);
          if (boolean == 0) {
            printf("\nThere was an error in the function heap_insere.");
            return 0;
          }
          /* copy new data to e2 */
          e2->n = e1->n;
          e2->rad = e1->rad;
          /* free memory from e1 */
          free (e1);
        }
      } else {
        /* n > (sizeAnswer+1) */
        e1 = h->elementos[RAIZ];
        /* et fulling */
        et->n = n;
        et->rad = n;
        /* test element < maxHeap */
        boolean = maior_que(e1, et);
        if (boolean == 1) {
          /* e1 > et */
          /* et goes to maxHeap */
          e1 =  heap_remove(h);
          if (e1 == NULL) {
            printf("\nThere was an error in the function heap_remove.");
            return 0;
          }
          boolean = heap_insere(h, et->rad, et->n);
          if (boolean == 0) {
            printf("\nThere was an error in the function heap_insere.");
            return 0;
          }
          /* e1 goes to e2 */
          e2->n = e1->n;
          e2->rad = e1->rad;
          /* free memory from e1 */
          free (e1);
        } else {
          /* e1 < et */
          /* test element < 10k1 */
          boolean = maior_que(e2, et);
          if (boolean == 1) {
            /* et > e1 and et < e2 */
            /* swicht e2 for et */
            e2->n = et->n;
            e2->rad = et->rad;
          }
        }
      }
      /* not prime numbers fulling */
      boolean = composeNumbersSaving (v, n, size);
      if (boolean == 0) {
        printf("\nThere was a problem in the function composeNumbersSaving.");
        return 0;
      }
    }
  }
  /* not primes processing */
    if (v[n]==1 || booleanP == 0) {
    /* this number is not a prime */
    et->n = n;
    /* rad calc */
    if (n > 1) {
      fac =  factorizacaoVecProduz (n, vPrime, nPrime, &sizeFac, nPrime);
      if (fac == NULL) {
        printf("\nThere was an error in the function factorizacaoVecProduz.");
        return 0;
      }
      et->rad = radCalc (fac, sizeFac);
      free (fac);
      if (et->rad == -1) {
        printf ("\nThere was an error in the function radCalc.");
        return 0;
      }
    } else {
      et->rad = 1;
    }
    /* value insertion in the heap */
    if (n <= sizeAnswer) {
      boolean = heap_insere(h, et->rad, et->n);
      if (boolean == 0) {
        printf("\nThere was an error in the function heap_insere.");
        return 0;
      }
    } else if (n == (sizeAnswer+1)){
      e1 = h->elementos[RAIZ];
      /* e2 fulling */
      e2->n = et->n;
      e2->rad = et->rad;
      boolean = maior_que(e2, e1);
      if (boolean == 0) {
        /* e1 > e2, must switch sides */
        e1 =  heap_remove(h);
        if (e1 == NULL) {
          printf("\nThere was an error in the function heap_remove.");
          return 0;
        }
        /* e2 insertion */
        boolean = heap_insere(h, e2->rad, e2->n);
        if (boolean == 0) {
          printf("\nThere was an error in the function heap_insere.");
          return 0;
        }
        /* copy new data to e2 */
        e2->n = e1->n;
        e2->rad = e1->rad;
        /* free memory from e1 */
        free (e1);
      }
    } else {
      /* n > (sizeAnswer+1) */
      e1 = h->elementos[RAIZ];
      /* test element < maxHeap */
      boolean = maior_que(e1, et);
      if (boolean == 1) {
        /* et < e1 */
        /* et goes to maxHeap */
        e1 =  heap_remove(h);
        if (e1 == NULL) {
          printf("\nThere was an error in the function heap_remove.");
          return 0;
        }
        boolean = heap_insere(h, et->rad, et->n);
        if (boolean == 0) {
          printf("\nThere was an error in the function heap_insere.");
          return 0;
        }
        /* e1 goes to e2 */
        e2->n = e1->n;
        e2->rad = e1->rad;
        /* free memory from e1 */
        free (e1);
      } else {
        /* e1 < et */
        /* test element < 10k1 */
        boolean = maior_que(e2, et);
        if (boolean == 1) {
          /* et > e1 and et < e2 */
          /* swicht e2 for et */
          e2->n = et->n;
          e2->rad = et->rad;
        }
      }
    }
  }
}
/* answer calc */
e1 =  heap_remove(h);
if (e1 == NULL) {
  printf("\nThere was an error in the function heap_remove.");
  return 0;
}
answer = e1->n;
radAnswer = e1->rad;
/* free memory */
free (v);
heap_apaga(h);
free (e1);
free (e2);
free (et);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe k=%dth element in the sorted array is n=%d with rad=%d.", sizeAnswer, answer, radAnswer);
printf ("\n");
return 0;
}
/******************************************************************************/
int primeTeste (int nTest) {
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
  if (n > sizeMax) {
    return 1;
  }
  v[n]=1;
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

