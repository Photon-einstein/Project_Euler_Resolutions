#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define FACTOR 1000000000
#define SIZE 40
#define MAXSIZEPRIME 8
#define MAXINDEX 104420
#define SIZBUFFER 2000

/* this function makes the calculation of the max index element of the array
*prime with nPrime elements, and then returns the index of the max element or
-1 if there was an error in the function */
int posMaxCalc (int *prime, int nPrime);

/* this function makes the sum of all the elements in the array *prime, with
nPrime elements, and then returns the sum or 0 if there was an error */
int sumPrimes(int *prime, int nPrime);

/* this function makes the verification of primeNumber is already in the array,
if yes then it returns 1, if not present it returns 0, if an error occurs then
it returns -1 */
int isPresent (int *prime, int nPrime, int primeNumber);

/* this function makes the possible insertion in the array prime of until
maxPrimeSize primes, from the char array str, and then return the updated
account of nPrime numbers and 1 if sucess or 0 if error has occurred */
int insertionOfNewPrimes(int *prime, int *nPrime, int maxPrimeSize, char *str,
int maxPrimeLenght);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int fac = FACTOR, prime[SIZE]={0}, nPrime=0, repunit = 1, i=0, maxPrime = 0;
int maxPrimeIndex = 0, bool, primeNumber, answer;
FILE *f;
char nameFile[100] = "Phin10.txt", buffer[SIZBUFFER], buf2[SIZBUFFER],*boolean, *s;
f = fopen(nameFile, "r");
assert (f!=NULL);
while (i<MAXINDEX) {
  /* read new prime factorization */
  boolean = fgets(buffer,1000,f);
  if (boolean == NULL) {
    /* end of file */
    break;
  }
  buffer[strlen(buffer)-1] = '\0';
  strcpy(buf2,buffer);
  s = strtok(buf2, " ");
  assert(s!=NULL);
  /* test division of repunits */
  if (fac%repunit==0&&repunit!=1) {
    bool = insertionOfNewPrimes(prime, &nPrime, SIZE, buffer, MAXSIZEPRIME);
    assert(bool!=0);
  }
  /* next values */
  /* test if duplicated line for same repunit */
  if (s[strlen(s)-1] != 'L') {
    i++;
    repunit++;
  }
  if (repunit==FACTOR) {
    break;
  }
}
answer = sumPrimes(prime, nPrime);
assert(answer!=0);
bool = fclose(f);
assert(bool==0);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nThe sum of all the first %d forty prime number of R(10^9) is %d.", SIZE, answer);
printf("\nTempo em segundos: %lf", tempo);
printf("\n");
return 0;
}
/******************************************************************************/
int insertionOfNewPrimes(int *prime, int *nPrime, int maxPrimeSize, char *str,
int maxPrimeLenght) {
/* this function makes the possible insertion in the array prime of until
maxPrimeSize primes, from the char array str, and then return the updated
account of nPrime numbers and 1 if sucess or 0 if error has occurred */
if (prime == NULL || nPrime == NULL || maxPrimeSize < 1 || str == NULL ||
  maxPrimeLenght < 1) {
  return 0;
}
int primeNumber, boolean;
char *s;
/* first string not needed */
s = strtok (str, " ");
/* enter cycle of reading numbers */
while (1) {
  s = strtok(NULL, " ");
  /* test end of line */
  if (s == NULL) {
    break;
  }
  /* test prime lenght */
  if (strlen(s) > maxPrimeLenght) {
    /* prime Number is to big */
    continue;
  }
  /* if it reaches here then the prime number has a valid size */
  primeNumber = atoi(s);
  /* test if prime number is already present on the array prime */
  boolean = isPresent (prime, *nPrime, primeNumber);
  if (boolean == -1) {
    /* error on the function */
    printf("\nThere was an error in the function isPresent.");
    return 0;
  } else if (boolean == 0) {
    /* prime not on the array */
    if (*nPrime < maxPrimeSize) {
      /* array prime not yet full, insertion is direct */
      prime[*nPrime] = primeNumber;
      *nPrime+=1;
    } else {
      /* array prime is already full */
      boolean = posMaxCalc (prime, *nPrime);
      if (boolean == -1) {
        /* error on the function */
        printf("\nThere was an error on the function posMaxCalc.");
        return 0;
      }
      /* test trade prime */
      if (primeNumber < prime[boolean]) {
        /* new insertion */
        prime[boolean] = primeNumber;
      }
    }
  }
}
/* if it reaches here then sucess */
return 1;
}
/******************************************************************************/
int posMaxCalc (int *prime, int nPrime){
/* this function makes the calculation of the max index element of the array
*prime with nPrime elements, and then returns the index of the max element or
-1 if there was an error in the function */
if (prime == NULL || nPrime < 1) {
  return -1;
}
int indexMax, primeMax = -1, i;
for (i = 0; i < nPrime; i++) {
  if (prime[i] > primeMax) {
    /* max update */
    primeMax = prime[i];
    indexMax = i;
  }
}
return indexMax;
}
/******************************************************************************/
int sumPrimes(int *prime, int nPrime) {
/* this function makes the sum of all the elements in the array *prime, with
nPrime elements, and then returns the sum or 0 if there was an error */
if (prime == NULL || nPrime < 1) {
  return 0;
}
int i,j, sum = 0, auxPrime;
for (i = 0; i < nPrime; i++){
  sum+=prime[i];
}
return sum;
}
/******************************************************************************/
int isPresent (int *prime, int nPrime, int primeNumber) {
/* this function makes the verification of primeNumber is already in the array,
if yes then it returns 1, if not present it returns 0, if an error occurs then
it returns -1 */
if (prime == NULL || nPrime < 0 || primeNumber < 2) {
  return -1;
}
int bool = 0, i;
for (i = 0; i < nPrime; i++) {
  if (prime[i] == primeNumber) {
    bool = 1;
    break;
  }
}
/* return value calc */
if (bool == 0) {
  /* not present */
  return 0;
} else {
  /* present */
  return 1;
}
}
/******************************************************************************/
