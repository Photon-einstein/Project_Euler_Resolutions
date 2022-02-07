#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MIN 4000000
#define NPRIME 13
#define MAXPRIMEREP 19
#define SIZEANSWER 50

/* this function makes the calculation of the number of solutions of a given
set of prime and power, and then return the number if all went ok or -1 if there
was a problem in the function */
int nSolutionsCalc (int *index, int nPrime);

/* this function makes the calculation of log n, and then returns the resulting
float or -1 if there was a problem in the function */
float nLogCalc (int *vPrime, int *index, int nPrime);

/* this function makes the memory allocation of the int array answer and then
makes the calculation of the real answer, and then returns the pointer or NULL
if there was a problem in this function */
int* calcRealAnswer (int *vPrime, int *index, int nPrime, int sizeAnswer);

/* this function makes the multiplication of the number vNum with nTest, and
then return 1 if all ok or 0 if there was a problem in this function */
int powerNarray (int *a, int nTest, int nDigits);

/* this function makes the calculation of the realSize of the answer and then
return the size or -1 if there was a problem in the function */
int calcRealSizeAnswer (int *answer, int sizeAnswer);

int main () {

clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int vPrime[NPRIME] = {2,3,5,7,11,13,17,19,23,29,31,37,41}, nSolutions;
int limitM, *answer, booleanoFirstData = 0, index[NPRIME], maxIndex, nPrime,i;
int sizeAnswer, booleano, nSolutionsAnswer;
float nF, nMinF;
limitM = 2*MIN-1;
nPrime = NPRIME;
booleanoFirstData = 0; /* float not yet with data stored */
maxIndex = MAXPRIMEREP;
sizeAnswer = SIZEANSWER;
/* enter cycle */
for (index[0] = 2; index[0] < maxIndex; index[0]+=2) {
for (index[1] = 0; index[1] < index[0]+1; index[1]+=2) {
for (index[2] = 0; index[2] < index[1]+1; index[2]+=2) {
for (index[3] = 0; index[3] < index[2]+1; index[3]+=2) {
for (index[4] = 0; index[4] < index[3]+1; index[4]+=2) {
for (index[5] = 0; index[5] < index[4]+1; index[5]+=2) {
for (index[6] = 0; index[6] < index[5]+1; index[6]+=2) {
for (index[7] = 0; index[7] < index[6]+1; index[7]+=2) {
for (index[8] = 0; index[8] < index[7]+1; index[8]+=2) {
for (index[9] = 0; index[9] < index[8]+1; index[9]+=2) {
for (index[10] = 0; index[10] < index[9]+1; index[10]+=2) {
for (index[11] = 0; index[11] < index[10]+1; index[11]+=2) {
for (index[12] = 0; index[12] < index[11]+1; index[12]+=2) {
nSolutions = nSolutionsCalc (index, nPrime);
if (nSolutions == -1) {
  printf("\nThere was a problem in the function nSolutionsCalc.");
  return 0;
}
if (nSolutions > limitM) {
  nF = nLogCalc (vPrime, index, nPrime);
  if (nF == -1) {
    printf("\nThere was a problem in the function nLogCalc.");
    return 0;
  }
  if (booleanoFirstData == 0) {
    nMinF = nF;
    booleanoFirstData = 1;
    nSolutionsAnswer = nSolutions;
    /* calc real answer */
    answer = calcRealAnswer (vPrime, index, nPrime, sizeAnswer);
    if (answer == NULL) {
      printf("\nThere was a problem in the function calcRealAnswer.");
      return 0;
    }
  } else if (nF < nMinF) {
    nMinF = nF;
    /* free previous answer */
    free (answer);
    /* calc real answer */
    answer = calcRealAnswer (vPrime, index, nPrime, sizeAnswer);
    if (answer == NULL) {
      printf("\nThere was a problem in the function calcRealAnswer.");
      return 0;
    }
  }
}}}}}}}}}}}}}}
booleano = calcRealSizeAnswer (answer, sizeAnswer);
if (booleano == -1) {
  printf("\nThere was a problem in the function calcRealSizeAnswer.");
  return 0;
}
sizeAnswer = booleano;
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThe least n in this condition is: ");
for (i = sizeAnswer-1; i > -1; i--) {
  printf("%d", answer[i]);
}
printf(" with %d solutions.", nSolutionsAnswer/2);
printf ("\n");
free (answer);
return 0;
}
/******************************************************************************/
int nSolutionsCalc (int *index, int nPrime) {
/* this function makes the calculation of the number of solutions of a given
set of prime and power, and then return the number if all went ok or -1 if there
was a problem in the function */
if (index == NULL || nPrime < 0) {
  return -1;
}
int n = 1, i;
for (i = 0; i < nPrime; i++) {
  n*=(index[i]+1);
}
return n;
}
/******************************************************************************/
float nLogCalc (int *vPrime, int *index, int nPrime) {
/* this function makes the calculation of log n, and then returns the resulting
float or -1 if there was a problem in the function */
if (vPrime == NULL || index == NULL || nPrime < 1) {
  return -1;
}
int i;
float nF = 0;
for (i = 0; i < nPrime; i++) {
  nF+=(index[i]*log(vPrime[i]));
}
return nF;
}
/******************************************************************************/
int* calcRealAnswer (int *vPrime, int *index, int nPrime, int sizeAnswer) {
/* this function makes the memory allocation of the int array answer and then
makes the calculation of the real answer, and then returns the pointer or NULL
if there was a problem in this function */
if (vPrime == NULL || index == NULL || sizeAnswer < 1 || nPrime < 1) {
  return NULL;
}
int *v, i, j, booleano, indexUpdated;
v = (int*) calloc (sizeAnswer, sizeof (int));
if (v == NULL) {
  return NULL;
}
/* start value */
v[0] = 1;
for (i = 0; i < nPrime; i++) {
  for (j = 0; j < index[i]/2; j++) {
    booleano = powerNarray (v, vPrime[i], sizeAnswer);
    if (booleano == 0) {
      printf("\nThere was a problem in the function calcRealAnswer.");
      return NULL;
    }
  }
}
return v;
}
/******************************************************************************/
int powerNarray (int* vNum, int nTest, int nDigits) {
/* this function makes the multiplication of the number vNum with nTest, and
then return 1 if all ok or 0 if there was a problem in this function */
if (vNum == NULL || nDigits < 1) {
  return 0;
}
int i, j, carry = 0;
carry = 0;
for (j = 0; j < nDigits; j++) {
  vNum[j] = vNum[j] * nTest + carry;
  if (vNum[j] < 10) {
    carry = 0;
  } else {
    carry = vNum[j] / 10;
    vNum[j] = vNum[j] - carry*10;
  }
}
return 1;
}
/******************************************************************************/
int calcRealSizeAnswer (int *answer, int sizeAnswer) {
/* this function makes the calculation of the realSize of the answer and then
return the size or -1 if there was a problem in the function */
if (answer == NULL || sizeAnswer < 0) {
  return -1;
}
int i, realSize;
for (i = sizeAnswer-1; i > -1; i--) {
  if (answer[i] != 0) {
    realSize = i+1;
    break;
  }
}
return realSize;
}
/******************************************************************************/
