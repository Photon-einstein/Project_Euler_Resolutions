#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

/* this function makes the calculation of the probability using depth aproach
and in the end it returns the correct probability */
double depthTestCalc();

/* this function makes the recursive calculation of the probability */
double recTestCalc(int v0, int v1, int v2, int v3, int nIter, int flagSinglePaper, double prob);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
double prob=0;
prob = depthTestCalc();
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\n\nTempo em segundos: %lf", tempo);
printf("\nThe expected number of times for the supervisor to find the A5 envelope is %.6f", prob);
/* free memory */
printf("\n");
return 0;
}
/******************************************************************************/
double depthTestCalc() {
/* this function makes the calculation of the probability using depth approach
and in the end it returns the correct probability */
int v1[4]={0,2,2,2}, v2[4]={1,0,2,2}, v3[4]={1,1,0,2}, v4[4]={1,1,1,0}, nIter=13, flagSinglePaper=0;
double prob=0.25, res=0;
res = recTestCalc(v1[0], v1[1], v1[2], v1[3], nIter, flagSinglePaper, prob)+
recTestCalc(v2[0], v2[1], v2[2], v2[3], nIter, flagSinglePaper, prob)+
recTestCalc(v3[0], v3[1], v3[2], v3[3], nIter, flagSinglePaper, prob)+
recTestCalc(v4[0], v4[1], v4[2], v4[3], nIter, flagSinglePaper, prob);
return res;
}
/******************************************************************************/
double recTestCalc(int v0, int v1, int v2, int v3, int nIter, int flagSinglePaper, double prob) {
/* this function makes the recursive calculation of the probability */
if (nIter == 0) {
  return prob*flagSinglePaper;
}
int flagNotNull[4]={0}, nElements=0, i, sumFlagsNotNull=0, v[4], aux, flagS=0;
double probPick[4]={0};
/* nElements calc */
v[0]=v0;
v[1]=v1;
v[2]=v2;
v[3]=v3;
for (i = 0; i < 4; ++i) {
  if (v[i]!=0) {
    flagNotNull[i]=1;
    ++sumFlagsNotNull;
  }
  nElements+=v[i];
}
if (nElements == 1) {
  flagS=1;
}
--nIter;
/* probPick calc */
for (i = 0; i < 4; ++i) {
  probPick[i] = (double)v[i]/nElements;
}
if (sumFlagsNotNull == 3 && flagNotNull[0] == 0) {
  /* 1-2-3 */
  return recTestCalc(v0, v1-1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[1])+
  recTestCalc(v0, v1, v2-1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[2])+
  recTestCalc(v0, v1, v2, v3-1, nIter, flagSinglePaper+flagS, prob*probPick[3]);
} else if (sumFlagsNotNull == 3 && flagNotNull[1]==0) {
  /* 0-2-3 */
  return recTestCalc(v0-1, v1+1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[0])+
  recTestCalc(v0, v1, v2-1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[2])+
  recTestCalc(v0, v1, v2, v3-1, nIter, flagSinglePaper+flagS, prob*probPick[3]);
} else if (sumFlagsNotNull == 3 && flagNotNull[2]==0) {
  /* 0-1-3 */
  return recTestCalc(v0-1, v1+1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[0])+
  recTestCalc(v0, v1-1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[1])+
  recTestCalc(v0, v1, v2, v3-1, nIter, flagSinglePaper+flagS, prob*probPick[3]);
} else if (sumFlagsNotNull == 3 && flagNotNull[3]==0) {
  /* 0-1-2 */
  return recTestCalc(v0-1, v1+1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[0])+
  recTestCalc(v0, v1-1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[1])+
  recTestCalc(v0, v1, v2-1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[2]);
} else if (sumFlagsNotNull == 2 && flagNotNull[0] == 0 && flagNotNull[1] == 0) {
  /* 2-3 */
  return recTestCalc(v0, v1, v2-1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[2])+
  recTestCalc(v0, v1, v2, v3-1, nIter, flagSinglePaper+flagS, prob*probPick[3]);
} else if (sumFlagsNotNull == 2 && flagNotNull[0] == 0 && flagNotNull[2] == 0) {
  /* 1-3 */
  return recTestCalc(v0, v1-1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[1])+
  recTestCalc(v0, v1, v2, v3-1, nIter, flagSinglePaper+flagS, prob*probPick[3]);
} else if (sumFlagsNotNull == 2 && flagNotNull[0] == 0 && flagNotNull[3] == 0) {
  /* 1-2 */
  return recTestCalc(v0, v1-1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[1])+
  recTestCalc(v0, v1, v2-1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[2]);
} else if (sumFlagsNotNull == 2 && flagNotNull[1] == 0 && flagNotNull[2] == 0) {
  /*0-3 */
  return recTestCalc(v0-1, v1+1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[0])+
  recTestCalc(v0, v1, v2, v3-1, nIter, flagSinglePaper+flagS, prob*probPick[3]);
} else if (sumFlagsNotNull == 2 && flagNotNull[1] == 0 && flagNotNull[3] == 0) {
  /* 0-2 */
  return recTestCalc(v0-1, v1+1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[0])+
  recTestCalc(v0, v1, v2-1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[2]);
} else if (sumFlagsNotNull == 2 && flagNotNull[2] == 0 && flagNotNull[3] == 0) {
  /* 0-1 */
  return recTestCalc(v0-1, v1+1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[0])+
  recTestCalc(v0, v1-1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[1]);
} else if (sumFlagsNotNull == 1 && flagNotNull[0] == 1) {
  /* 0 */
  return recTestCalc(v0-1, v1+1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[0]);
} else if (sumFlagsNotNull == 1 && flagNotNull[1] == 1) {
  /* 1 */
  return recTestCalc(v0, v1-1, v2+1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[1]);
} else if (sumFlagsNotNull == 1 && flagNotNull[2] == 1) {
  /* 2 */
  return recTestCalc(v0, v1, v2-1, v3+1, nIter, flagSinglePaper+flagS, prob*probPick[2]);
} else if (sumFlagsNotNull == 1 && flagNotNull[3] == 1) {
  /* 3 */
  return recTestCalc(v0, v1, v2, v3-1, nIter, flagSinglePaper+flagS, prob*probPick[3]);
}
}
/******************************************************************************/
