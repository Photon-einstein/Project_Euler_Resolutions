#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define NSOLUTIONS 6
#define SIZEANSWER 30
typedef struct {
  long long int x;
  long long int y;
} solution;

/* this function tests the seed solutions in the two tests for a given number
of solutions and then saves this to the array answer, returning the number of
solutions found if all ok 0 if there was a problem in the function */
int testSolutions(solution *v1, solution *v2, int nSolutions, long long int *answer, int sizeAnswer);

/* this function sortes the array until sizeAnswer, and returns the 1st sum of
the sizeAnswer elements or -1 if there was a problem in the function */
long long int sumAnswerArray(long long int *answer, int sizeAnswer, int nFound);

/* this function tests the answer array for a new x solution, on nFound elements
and then it returns 1 if new solution, 0 if not or -1 if there was an error in
the function */
int testNewSolution(long long int *answer, int nFound, long long int x);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
solution v1[NSOLUTIONS], v2[NSOLUTIONS];
int nSolutions, sizeAnswer, boolean, nFound;
long long int answer[SIZEANSWER*10], total;
nSolutions = NSOLUTIONS,
sizeAnswer = SIZEANSWER;
/* solution array fulling */
/* 1st test array initialization */
/* 1st pair */
v1[0].x = 2;
v1[0].y = -7;
/* 2nd pair */
v1[1].x = 0;
v1[1].y = -1;
/* 3rd pair */
v1[2].x = 0;
v1[2].y = 1;
/* 4th pair */
v1[3].x = -4;
v1[3].y = 5;
/* 5th pair */
v1[4].x = -3;
v1[4].y = 2;
/* 6th pair */
v1[5].x = -3;
v1[5].y = -2;
/* 1st test array initialization */
/* 1st pair */
v2[0].x = 2;
v2[0].y = -7;
/* 2nd pair */
v2[1].x = 0;
v2[1].y = -1;
/* 3rd pair */
v2[2].x = 0;
v2[2].y = 1;
/* 4th pair */
v2[3].x = -4;
v2[3].y = 5;
/* 5th pair */
v2[4].x = -3;
v2[4].y = 2;
/* 6th pair */
v2[5].x = -3;
v2[5].y = -2;
/* test seed solutions */
boolean = testSolutions(v1,v2, nSolutions, answer, sizeAnswer);
if (boolean == -1) {
  printf("\nThere was an error in the function testSolutions.");
  exit(1);
}
nFound = boolean;
printf("\nThere were found %d solutions.", nFound);
/* answer calc */
total = sumAnswerArray(answer, sizeAnswer, nFound);
if (total == -1) {
  printf("\nThere was an error in the function sumAnswerArray.");
  exit(1);
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe sum of the first %d elements is %lld.", sizeAnswer, total);
printf("\n");
return 0;
}
/******************************************************************************/
int testSolutions(solution *v1, solution *v2, int nSolutions, long long int *answer, int sizeAnswer) {
/* this function tests the seed solutions in the two tests for a given number
of solutions and then saves this to the array answer, returning the number of
solutions found if all ok 0 if there was a problem in the function */
if (v1 == NULL || v2 == NULL || nSolutions < 1 || answer == NULL || sizeAnswer < 1) {
  return 0;
}
int i, nFound=0, k, boolean;
long long int xAux, yAux;
for (i = 0; i < sizeAnswer; i++) {
  for (k = 0; k < nSolutions; k++) {
    /* 1st pair work */
    if (i == 0) {
      if (v1[k].x > 0) {
        answer[nFound] = v1[k].x;
        nFound++;
      }
      continue;
    }
    /* others pair work */
    /* 1st test */
    xAux = v1[k].x;
    yAux = v1[k].y;
    v1[k].x = -9*xAux-4*yAux-14;
    v1[k].y = -20*xAux-9*yAux-28;
    /* test x */
    if (v1[k].x > 0){
      boolean = testNewSolution(answer, nFound, v1[k].x);
      if (boolean == -1) {
        printf("\nThere was an error in the function testNewSolution.");
        exit(0);
      } else if (boolean == 1) {
        answer[nFound] = v1[k].x;
        nFound++;
      }
    }
    /* 2st test */
    xAux = v2[k].x;
    yAux = v2[k].y;
    v2[k].x = -9*xAux+4*yAux-14;
    v2[k].y = 20*xAux-9*yAux+28;
    /* test x */
    if (v2[k].x > 0){
      boolean = testNewSolution(answer, nFound, v2[k].x);
      if (boolean == -1) {
        printf("\nThere was an error in the function testNewSolution.");
        exit(0);
      } else if (boolean == 1) {
        answer[nFound] = v2[k].x;
        nFound++;
      }
    }
  }
}
return nFound;
}
/*******************************************************************************/
long long int sumAnswerArray(long long int *answer, int sizeAnswer, int nFound) {
/* this function sortes the array until sizeAnswer, and returns the 1st sum of
the sizeAnswer elements or -1 if there was a problem in the function */
int i,j;
long long int aux, answerCount = 0;
for (i = 0; i < sizeAnswer; i++) {
  for (j = i+1; j < nFound; j++) {
    if (answer[i]>answer[j]) {
      /* aux = i */
      aux = answer[i];
      /* i = j */
      answer[i] = answer[j];
      /* j = aux */
      answer[j] = aux;
    }
  }
  //printf("\nElement %d: %lld", i+1, answer[i]);
  answerCount+=answer[i];
}
return answerCount;
}
/******************************************************************************/
int testNewSolution(long long int *answer, int nFound, long long int x) {
/* this function tests the answer array for a new x solution, on nFound elements
and then it returns 1 if new solution, 0 if not or -1 if there was an error in
the function */
if (answer == NULL || nFound < 1 || x < 1) {
  return -1;
}
int i;
for (i = 0; i < nFound; i++) {
  if (answer[i] == x) {
    return 0;
  }
}
return 1;
}
/******************************************************************************/
