#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabdispersao.h"
#define LIMIT 100
#define MAXLIMIT 170
#define DATANUMBER 63
#define SIZECHAR 4
#define SIZEPLAY 3
typedef struct {
  int scoreIndex; /* play code from 0 until 63 */
  int scorePlay; /* score from 0 until 60 */
  char scoreChar[SIZECHAR]; /* char from a given play */
  int doubleEndBoolean; /* 0 if not ending in a double or 1 if ending in a double */
} dart;

/* this function makes the fulling of the dart array and then returns 1 if
it went all ok or 0 if there was a problem in the function */
int fullingDartArray (dart *v, int dataNumber, int sizeChar);

/* this function counts the number of zeros in the array indice of dim sizePlay
and then return the number of zeros or -1 if there was a problem in this
function */
int nZerosCount (int *indice, int dim);

/* this function creates the char array of a given checkout, dynamicaly allocated
the memory and then returns the pointer of the array if all went ok or NULL if
there was a problem in this function, and returns also by reference the score
of this play */
char *charCreat (dart *v, int *indice, int nZeros, int sizeChar, int sizePlay, int *score);

/* if checkout with 3 darts, swap first and secont dart,
this function makes the copy of the values of index array to index2 array,
and then return 1 if it went all ok or 0 if there was a problem in the
function */
int copyIndexValuesWithSwap (int *index, int *index2);

/* this function makes the test of ending in a double, and returns 1 if yes, 0
if not or -1 if there was a problem in this function */
int testingEndingInDouble (dart *v, int *index, int nZeros, int sizePlay, int realSize);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int dataNumber=DATANUMBER, maxLimite=MAXLIMIT+1, limit=LIMIT, sizePlay=SIZEPLAY;
int sizeChar = SIZECHAR, tamanhoTd, answer = 0, booleano, index[sizePlay];
int nZeros, score, realSize, index2[sizePlay], j = 0;
char *c;
tabela_dispersao *td;
dart *v;

v = calloc (dataNumber, sizeof (dart));
if (v == NULL) {
  printf("\nThere was an error in the memory allocation of v array.");
  return 0;
}
tamanhoTd = pow(limit, sizePlay);
td = tabela_nova(tamanhoTd, hash_djbm);
if (td == NULL) {
  printf("\nThere was an error in the function tabela_nova.");
  return 0;
}
booleano = fullingDartArray (v, dataNumber, sizeChar);
if (booleano == 0) {
  printf("\nThere was an error in the function fullingDartArray.");
  return 0;
}
/* cycle */
for (index[0] = 0; index[0] < dataNumber; index[0]++) {
  for (index[1] = index[0]; index[1] < dataNumber; index[1]++) {
    for (index[2] = 21; index[2] < dataNumber; index[2]++) {
      if (index[2] == 41) {
        index[2] = 62;
      }
      nZeros = nZerosCount (index, sizePlay);
      if (nZeros == -1) {
        printf("\nThere was a problem in the function nZerosCount.");
        return 0;
      }
      /* all zeros in the play */
      if (nZeros == sizePlay) {
        continue;
      }
      realSize = sizePlay-nZeros;
      /*booleano = testingEndingInDouble (v, index, nZeros, sizePlay, realSize);
      if (booleano == -1) {
        printf("\nThere was a problem in the function testingEndingInDouble.");
        return 0;
      } else if (booleano == 0) {
        /* does not end in a double
        continue;
      }
      */
      c = charCreat (v, index, nZeros, sizeChar, sizePlay, &score);
      if (c == NULL) {
        printf("\nThere was a problem in the function charCreat.");
        return 0;
      }
      if (score >= limit) {
        /* score over limit */
        free (c);
        continue;
      }

      /* if it reaches here then score under the limit */
      booleano = tabela_existe(td, c);
      if (booleano == TABDISPERSAO_INVALIDA) {
        printf("\nThere was a problem in the function tabela_existe.");
        return 0;
      } else if (booleano == TABDISPERSAO_EXISTE) {
        free (c);
        continue;
      }
      /* if it reaches here then then this play do not exist */
      booleano = tabela_insere(td, c, c);
      if (booleano == TABDISPERSAO_ERRO || booleano == TABDISPERSAO_INVALIDA) {
        printf("\nThere was a problem in the function tabela insere.");
        return 0;
      }
      /* free memory */
      free (c);
      /* answer calc */
      answer++;
      if (realSize < sizePlay) {
        /* no need to swap darts, work finish for this index */
        continue;
      }
      /* checkout with 3 darts, swap first and secont dart */
      booleano = copyIndexValuesWithSwap (index, index2);
      if (booleano == 0) {
        printf("\nThere was a problem in the function copyIndexValues.");
        return 0;
      }
      c = charCreat (v, index2, nZeros, sizeChar, sizePlay, &score);
      if (c == NULL) {
        printf("\nThere was a problem in the function charCreat.");
        return 0;
      }
      booleano = tabela_insere(td, c, c);
      if (booleano == TABDISPERSAO_ERRO || booleano == TABDISPERSAO_INVALIDA) {
        printf("\nThere was a problem in the function tabela insere.");
        return 0;
      }
      /* free memory */
      free (c);
    }
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThere are %d diferent ways of checkout less than %d points.", answer, limit);
/* free memory */
free (v);
tabela_apaga(td);
printf ("\n");
return 0;
}
/******************************************************************************/
int fullingDartArray (dart *v, int dataNumber, int sizeChar) {
/* this function makes the fulling of the dart array and then returns 1 if
it went all ok or 0 if there was a problem in the function */
if (v == NULL || dataNumber < 1 || sizeChar < 1) {
  return 0;
}
int i, scoreCharI;
char c[sizeChar];
for (i = 0; i < dataNumber; i++) {
  v[i].scoreIndex = i;
  /* score play calculation and scoreChar calc */
  if (i == 0) {
    v[i].doubleEndBoolean = 0;
    v[i].scorePlay = 0;
  } else if (i > 0 && i < 21) {
    v[i].doubleEndBoolean = 0;
    v[i].scorePlay = i;
    strcpy (v[i].scoreChar, "S");
    sprintf(c,"%d",v[i].scorePlay);
    strcat(v[i].scoreChar, c);
  } else if (i > 20 && i < 41) {
    v[i].doubleEndBoolean = 1;
    v[i].scorePlay = (i-20)*2;
    strcpy (v[i].scoreChar, "D");
    sprintf(c,"%d",v[i].scorePlay/2);
    strcat(v[i].scoreChar, c);
  } else if (i > 40 && i < 61) {
    v[i].doubleEndBoolean = 0;
    v[i].scorePlay = (i-40)*3;
    strcpy (v[i].scoreChar, "T");
    sprintf(c,"%d",v[i].scorePlay/3);
    strcat(v[i].scoreChar, c);
  } else if (i == 61) {
    v[i].doubleEndBoolean = 0;
    v[i].scorePlay = 25;
    strcpy (v[i].scoreChar, "S");
    sprintf(c,"%d",v[i].scorePlay);
    strcat(v[i].scoreChar, c);
  } else {
    v[i].doubleEndBoolean = 1;
    v[i].scorePlay = 25*2;
    strcpy (v[i].scoreChar, "D");
    sprintf(c,"%d",v[i].scorePlay/2);
    strcat(v[i].scoreChar, c);
  }
}
return 1;
}
/******************************************************************************/
int nZerosCount (int *index, int dim) {
/* this function counts the number of zeros in the array indice of size dim
and then return the number of zeros or -1 if there was a problem in this
function */
if (index == NULL || dim < 1) {
  return -1;
}
int nZeros = 0, i;
for (i = 0; i < dim; i++) {
  if (index[i] == 0) {
    nZeros++;
  }
}
return nZeros;
}
/******************************************************************************/
char *charCreat (dart *v, int *index, int nZeros, int sizeChar, int sizePlay, int *score) {
/* this function creates the char array of a given checkout, dynamicaly allocated
the memory and then returns the pointer of the array if all went ok or NULL if
there was a problem in this function, and returns also by reference the score
of this play */
if (v == NULL || nZeros < 0 || nZeros > sizePlay || index == NULL || score == NULL) {
  return NULL;
}
char *c;
int size, i, dim = 0, scoreF = 0;
size = (sizePlay-nZeros)*sizeChar;
c = calloc (size, sizeof (char));
if (c == NULL) {
  return NULL;
}
for (i = 0; i < sizePlay; i++) {
  if (v[index[i]].scorePlay > 0) {
    /* first element to insert */
    if (dim == 0) {
      strcpy(c, v[index[i]].scoreChar);
    } else {
      strcat (c, v[index[i]].scoreChar);
    }
    dim++;
    scoreF+=v[index[i]].scorePlay;
  }
}
*score = scoreF;
return c;
}
/******************************************************************************/
int copyIndexValuesWithSwap (int *index, int *index2) {
/* if checkout with 3 darts, swap first and secont dart,
this function makes the copy of the values of index array to index2 array,
and then return 1 if it went all ok or 0 if there was a problem in the
function */
if (index == NULL || index2 == NULL) {
  return 0;
}
index2[0] = index[1];
index2[1] = index[0];
index2[2] = index[2];
return 1;
}
/******************************************************************************/
int testingEndingInDouble (dart *v, int *index, int nZeros, int sizePlay, int realSize) {
/* this function makes the test of ending in a double, and returns 1 if yes, 0
if not or -1 if there was a problem in this function */
if (v == NULL || index == NULL || nZeros < 0 || nZeros > sizePlay) {
  return -1;
}
int booleano, index2[sizePlay], i, j=0,endPos;
/* copy values of index */
for (i = 0; i < sizePlay; i++) {
  /* ignore zeros */
  if (index[i] == 0) {
    continue;
  }
  /* storing only numbers diferent from zeros */
  index2[j] = index[i];
  j++;
}
/* testing double ending */
endPos = index2[realSize-1];
if (v[endPos].doubleEndBoolean == 1) {
  /* ends in a double */
  return 1;
} else {
  /* does not end in a double */
  return 0;
}
}
/******************************************************************************/
