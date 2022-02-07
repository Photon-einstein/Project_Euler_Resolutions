#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabdispersao.h"
#define POWMAX 8
#define SIZEHASH 100000
#define SIZEKEY 15

/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
int dimCalc (int counter, int *nDigit);

/* this function creates and fills the array with the digits of the number
counter, knowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *fullArrayDigit (int counter, int dim, int nDigit);

/* this function makes the calculation of the palindrome with even digits,
and then returns the number or 0 if there was a problem in the function */
long long int palindromeCalcEvenDigit (int *rightDigitV, int dim, int nDigit);

/* this function makes the calculation of the palindrome with odd digits,
and then returns the number or 0 if there was a problem in the function */
long long int palindromeCalcOddDigit (int *rightDigitV, int dim, int nDigit, int middle);

/* this function makes the calculation of the palindrome number to be insert
in the hash and then return the number or 0 if there was a problem in the
function */
long long int palCalc (int *digitPal, long long int dimPal, int nDigitPal);

/* this function makes the manufacture of the test number and then returns the
long long int number */
long long int numberTestCalc (int firstNumber, int sizeChain);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int tamanhoTd, powmax, dim, nDigitMax, n, nEvenMax, nOddMax, nDigit;
int boolean, *rightDigitV, sizeKey, middle, nPal=0, sizeChain = 2, firstNumber = 1;
long long int palindrome, maxNumber, number, answer=0;
tabela_dispersao *td, *tdTest;
char *key, value[2]="\0";
/* value update */
powmax = POWMAX;
tamanhoTd = SIZEHASH;
nDigitMax = powmax;
sizeKey = SIZEKEY;
maxNumber = pow (10, powmax);
/* hash creation */
td = tabela_nova(tamanhoTd, hash_djbm);
if (td == NULL) {
  printf("\nThere was a problem in the hash creation.");
  return 0;
}
tdTest = tabela_nova(tamanhoTd, hash_djbm);
if (tdTest == NULL) {
  printf("\nThere was a problem in the hash creation.");
  return 0;
}
/* key allocation */
key = (char*) calloc (sizeKey, sizeof (char));
if (key == NULL) {
  printf("\nThere was an error in the memory allocation of the key.");
  return 0;
}
/* even digit palindrome calc */
nEvenMax = pow(10, powmax/2);
if (powmax%2==0) {
  nOddMax = pow (10, powmax/2-1);
} else {
  nOddMax = pow (10, (powmax+1)/2-1);
}
for (n = 1; n < nEvenMax; n++) {
  nPal++;
  /* dim calc */
  dim = dimCalc (n, &nDigit);
  if (dim == -1) {
    printf("\nThere was a problem in the function dimCalc.");
    return 0;
  }
  rightDigitV = fullArrayDigit (n, dim, nDigit);
  if (rightDigitV == NULL) {
    printf("\nThere was an error in the function preencheVectorDigit.");
  }
  palindrome = palindromeCalcEvenDigit (rightDigitV, dim, nDigit);
  if (palindrome == 0) {
    printf("\nThere was a problem in the function palindromeCalcEvenDigit.\n");
    return 0;
  }
  /* free memory */
  free (rightDigitV);
  sprintf(key,"%lld", palindrome);
  //printf("\nfor n = %d: palindrome = %lld and key = %s", n, palindrome, key);
  /* hash insertion */
  boolean = tabela_insere(td, key, value);
  if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
    printf("\nThere was an error in the function tabela_insere.");
    return 0;
  }
}
/* 1 to 9 numbers */
for (n = 1; n < 10; n++) {
  nPal++;
  palindrome = n;
  sprintf(key,"%lld", palindrome);
  //printf("\nfor n = %d: palindrome = %lld and key = %s", n, palindrome, key);
  /* hash insertion */
  boolean = tabela_insere(td, key, value);
  if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
    printf("\nThere was an error in the function tabela_insere.");
    return 0;
  }
}
/* odd digit palindrome calc  */
for (n = 1; n < nOddMax; n++) {
  //printf("\n");
  for (middle = 0; middle < 10; middle++) {
    nPal++;
    /* dim calc */
    dim = dimCalc (n, &nDigit);
    if (dim == -1) {
      printf("\nThere was a problem in the function dimCalc.");
      return 0;
    }
    rightDigitV = fullArrayDigit (n, dim, nDigit);
    if (rightDigitV == NULL) {
      printf("\nThere was an error in the function preencheVectorDigit.");
    }
    palindrome = palindromeCalcOddDigit (rightDigitV, dim, nDigit, middle);
    if (palindrome == 0) {
      printf("\nThere was a problem in the function palindromeCalcEvenDigit.\n");
      return 0;
    }
    /* free memory */
    free (rightDigitV);
    sprintf(key,"%lld", palindrome);
    //printf("\nfor n = %d: pal = %lld, middle = %d and key = %s",n,palindrome,middle,key);
    /* hash insertion */
    boolean = tabela_insere(td, key, value);
    if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
      printf("\nThere was an error in the function tabela_insere.");
      return 0;
    }
  }
}
//printf("\nThere are %d palindrome numbers to evaluate.", nPal);
/* 2nd phase, number of palindrome squares */
while (1) {
  /* firstNumber tune */
  firstNumber = 1;
  /* first test before enter 2nd infinite cycle */
  number = numberTestCalc (firstNumber, sizeChain);
  /* test overflow */
  if (number >= maxNumber) {
    break;
  }
  sprintf(key,"%lld", number);
  boolean = tabela_existe(td, key);
  if (boolean == TABDISPERSAO_INVALIDA) {
    printf("\nThere was an error in the function tabela_insere.");
    return 0;
  } else if (boolean == TABDISPERSAO_EXISTE) {
      /* test duplicated answer */
      /* hash insertion */
      boolean = tabela_existe(tdTest, key);
      if (boolean == TABDISPERSAO_INVALIDA) {
        printf("\nThere was an error in the function tabela_insere.");
        return 0;
      } else if (boolean == TABDISPERSAO_NAOEXISTE) {
        //printf("\nNew number found: %lld.", number);
        answer+=number;
        boolean = tabela_insere(tdTest, key, value);
        if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
          printf("\nThere was an error in the function tabela_insere.");
          return 0;
        }
    }
  }
  /* enter 2nd cycle */
  firstNumber++;
  while (1) {
        number = numberTestCalc (firstNumber, sizeChain);
        /* test overflow */
        if (number >= maxNumber) {
          break;
        }
        sprintf(key,"%lld", number);
        boolean = tabela_existe(td, key);
        if (boolean == TABDISPERSAO_INVALIDA) {
          printf("\nThere was an error in the function tabela_insere.");
          return 0;
        } else if (boolean == TABDISPERSAO_EXISTE) {
          /* test duplicated answer */
          /* hash insertion */
          boolean = tabela_existe(tdTest, key);
          if (boolean == TABDISPERSAO_INVALIDA) {
            printf("\nThere was an error in the function tabela_insere.");
            return 0;
          } else if (boolean == TABDISPERSAO_NAOEXISTE) {
            //printf("\nNew number found: %lld.", number);
            answer+=number;
            boolean = tabela_insere(tdTest, key, value);
            if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
              printf("\nThere was an error in the function tabela_insere.");
              return 0;
            }
          }
        }
        /* advancing firstNumber */
        firstNumber++;
  }
  /* advancing size chain */
  sizeChain++;
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nUntil 10^%d, the sum of all the square palindrome is %lld.", powmax, answer);
printf ("\n");
/* free memory */
boolean = tabela_esvazia(td);
if (boolean == TABDISPERSAO_INVALIDA) {
  printf("\nThere was an error in the function tabela_esvazia.");
  return 0;
}
boolean = tabela_esvazia(tdTest);
if (boolean == TABDISPERSAO_INVALIDA) {
  printf("\nThere was an error in the function tabela_esvazia.");
  return 0;
}
/* free memory */
free (key);
return 0;
}
/******************************************************************************/
int dimCalc (int counter, int *nDigit) {
/* this function makes the calculation of the dimension of the counter and then
it returns the number of digits of the counter, it returns the dimension or -1
if there was a problem in the function */
if (nDigit == NULL || counter < 1) {
  return -1;
}
int dim = 1;
int res, nDigitsNumber = 1;
res = counter / dim;
while (res > 9) {
  dim = dim * 10;
  nDigitsNumber++;
  res = counter / dim;
}
*nDigit = nDigitsNumber;
return dim;
}
/******************************************************************************/
int *fullArrayDigit (int counter, int dim, int nDigit) {
/* this function creates and fills the array with the digits of the number
counter, ckowing that dim and nDigits. It returns the pointer of the array or
NULL if there was a problem in the function */
int *vectorDigit;
int i;
vectorDigit = (int*) calloc (nDigit, sizeof (int));
if (vectorDigit == NULL) {
  printf ("\nError in the creation of the array.");
  return NULL;
}
for (i = 0; i < nDigit; i++) {
  vectorDigit[i] = counter / dim;
  counter = counter - vectorDigit[i]*dim;
  dim = dim / 10;
}
return vectorDigit;
}
/******************************************************************************/
long long int palindromeCalcEvenDigit (int *rightDigitV, int dim, int nDigit) {
/* this function makes the calculation of the palindrome with even digits,
and then returns the number or 0 if there was a problem in the function */
if (rightDigitV == NULL || dim < 1 || nDigit < 1) {
  return 0;
}
int *digitPal, nDigitPal, i, j;
long long int pal, dimPal;
nDigitPal = nDigit*2;
dimPal = pow(10, nDigitPal-1);
/* digitPal creation */
digitPal = (int*) calloc (nDigitPal, sizeof (int));
if (digitPal == NULL) {
  return 0;
}
/*  left side */
for (i = 0; i < nDigit; i++) {
  digitPal[i] = rightDigitV[i];
}
/* right side */
j = 0;
for (i = nDigit; i < nDigitPal; i++) {
  digitPal[i] = rightDigitV[nDigit-j-1];
    j++;
}
pal = palCalc (digitPal, dimPal, nDigitPal);
if (pal == 0) {
  printf("\nThere was an error in the function palCalc.");
  return 0;
}
/* free memory */
free (digitPal);
/* if it reaches here then it is ok */
return pal;
}
/******************************************************************************/
long long int palCalc (int *digitPal, long long int dimPal, int nDigitPal) {
/* this function makes the calculation of the palindrome number to be insert
in the hash and then return the number or 0 if there was a problem in the
function */
if (digitPal == NULL || dimPal < 1 || nDigitPal < 1) {
  return 0;
}
int i;
long long int pal=0;
for (i = 0; i < nDigitPal; i++) {
  pal+=digitPal[i]*dimPal;
  dimPal/=10;
}
return pal;
}
/******************************************************************************/
long long int palindromeCalcOddDigit (int *rightDigitV, int dim, int nDigit, int middle) {
/* this function makes the calculation of the palindrome with odd digits,
and then returns the number or 0 if there was a problem in the function */
if (rightDigitV == NULL || dim < 1 || nDigit < 1 || middle < 0 || middle > 9) {
  return 0;
}
int *digitPal, nDigitPal, i, j;
long long int pal, dimPal;
nDigitPal = nDigit*2+1;
dimPal = pow(10, nDigit*2);
/* digitPal creation */
digitPal = (int*) calloc (nDigitPal, sizeof (int));
if (digitPal == NULL) {
  return 0;
}
/*  left side */
for (i = 0; i < nDigit; i++) {
  digitPal[i] = rightDigitV[i];
}
/* middle number */
digitPal[i] = middle;
/* right side */
j = 0;
for (i = nDigit+1; i < nDigitPal; i++) {
  digitPal[i] = rightDigitV[nDigit-j-1];
    j++;
}
pal = palCalc (digitPal, dimPal, nDigitPal);
if (pal == 0) {
  printf("\nThere was an error in the function palCalc.");
  return 0;
}
/* free memory */
free (digitPal);
/* if it reaches here then it is ok */
return pal;
}
/******************************************************************************/
long long int numberTestCalc (int firstNumber, int sizeChain) {
/* this function makes the manufacture of the test number and then returns the
long long int number */
long long int number = 0;
int i, endI;
endI = firstNumber+sizeChain;
for (i = firstNumber; i < endI; i++) {
  number+=pow(i,2);
}
return number;
}
/******************************************************************************/
