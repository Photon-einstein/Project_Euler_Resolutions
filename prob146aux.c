#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXPRIME 150000000+5
#define MAXLIMIT 150000000

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTeste (long long int nTest, int *v, int nPrime);

/* this function makes the primality test of n, and if pass the test it returns
1, if not it returns 0 and we can skip the rest of the tests, if there is an
error in the function then it returns -1 */
int testN(int n, int *v, int nPrime);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int maxSize, i, *v, mult = 1, boolean, nPrime=0;
long long int number, sum=0, n;
FILE *f;
f = fopen("primes.txt", "r");
if (f == NULL) {
  printf("\nError.");
  return 0;
}
rewind (f);
/* memory allocation */
maxSize = 1.2*MAXPRIME/log(MAXPRIME);
printf("\nmaxSize = %d", maxSize);
v =(int*) calloc(maxSize, sizeof (int));
if (v == NULL) {
  printf("\nThere was an error in the memory allocation of v.");
  return 0;
}
for (i = 0; i < maxSize; i++) {
    /* prime storage */
    boolean = fscanf(f, "%d", &v[i]);
    if (boolean == 0 || v[i]==0) {
      nPrime = i;
      break;
    }
}
/* search number */
for (n=10; n < MAXLIMIT; n+=10) {
  /* speed up test */
  if (n%3==0||n%7==0||n%13==0) {
    continue;
  }
  boolean = testN(n, v, nPrime);
  if (boolean == 0) {
    continue;
  } else if (boolean == -1) {
    printf("\nThere was an error in the function testN.");
    return 0;
  }
  /* test n²+1 prime */
  boolean = primeTeste (n*n+1, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 0) {
    /* not prime */
    continue;
  }
  /* test n²+3 prime */
  boolean = primeTeste (n*n+3, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 0) {
    /* not prime */
    continue;
  }
  /* test n²+7 prime */
  boolean = primeTeste (n*n+7, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 0) {
    /* not prime */
    continue;
  }
  /* test n²+9 prime */
  boolean = primeTeste (n*n+9, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 0) {
    /* not prime */
    continue;
  }
  /* test n²+13 prime */
  boolean = primeTeste (n*n+13, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 0) {
    /* not prime */
    continue;
  }
  /* test n²+27 prime */
  boolean = primeTeste (n*n+27, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 0) {
    /* not prime */
    continue;
  }
  /* not prime tests */
  /* test n²+11 not prime */
  boolean = primeTeste (n*n+11, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 1) {
    /* prime */
    continue;
  }
  /* test n²+15 not prime */
  boolean = primeTeste (n*n+15, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 1) {
    /* prime */
    continue;
  }
  /* test n²+17 not prime */
  boolean = primeTeste (n*n+17, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 1) {
    /* prime */
    continue;
  }
  /* test n²+19 not prime */
  boolean = primeTeste (n*n+19, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 1) {
    /* prime */
    continue;
  }
  /* test n²+21 not prime */
  boolean = primeTeste (n*n+21, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 1) {
    /* prime */
    continue;
  }
  /* test n²+13 not prime */
  boolean = primeTeste (n*n+23, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 1) {
    /* prime */
    continue;
  }
  /* test n²+13 not prime */
  boolean = primeTeste (n*n+25, v, nPrime);
  if (boolean == -1) {
    return 0;
  } else if (boolean == 1) {
    /* prime */
    continue;
  }
  /* new answer found */
  sum+=n;
}
/* free memory */
free(v);
fclose(f);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThere are %d primes until %d.", nPrime, MAXPRIME);
printf("\nThe sum of all such integers n below %d is %lld.", MAXLIMIT, sum);
printf("\n");
return 0;
}
/******************************************************************************/
int primeTeste (long long int nTest, int *v, int nPrime) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
if (v == NULL || nPrime < 0) {
  return -1;
}
int i, limit;
//printf("\nNew test: %lld", nTest);
if (nTest <= 1) {
	return 0;
}
if (nTest  == 2) {
	return 1;
} else if (nTest % 2 == 0) {
	return 0;
}
limit = sqrt (nTest+1);
//printf("\nThe limit for nTest = %lld is %d.", nTest, limit);
for (i = 0; i < nPrime && v[i] < limit+1; i++) {
  if (nTest % v[i] == 0) {
		return 0;
	}
}
/* if it reaches here, then it is a prime number */
return 1;
}
/******************************************************************************/
int testN(int n, int *v, int nPrime) {
/* this function makes the primality test of n, and if pass the test it returns
1, if not it returns 0 and we can skip the rest of the tests, if there is an
error in the function then it returns -1 */
if (n < 2 || v == NULL || nPrime < 1) {
  return -1;
}
int vT[6]={1,3,7,9,13,27}, nTest=6, maxPrime, boolean, i, j, nCase;
maxPrime = (int)sqrt(n+1);
for (i = 0; i < nPrime && v[i] <= maxPrime; i++) {
  for (j = 0; j < nTest; j++) {
    nCase = (n%v[i])*(n%v[i])+vT[j];
    if (nCase % v[i]==0) {
      /* n failed primality test */
      return 0;
    }
  }
}
/* if it reaches here then we have found another valid n */
return 1;
}
/******************************************************************************/
