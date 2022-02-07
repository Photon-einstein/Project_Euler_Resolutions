#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabdispersao.h"
#define MINSIZEINDEX 7
#define SIZEDATA 12
#define SIZEDATALINE 100
#define SIZEINDEX 12

typedef struct {
  int index[SIZEINDEX]; /* max combinations have 12 elements */
  int sizeComb; /* this says what is size of this combination */
} combinations;

typedef struct {
  int data[SIZEDATA];
  int realSize; /* this says whats the real size of this data */
} data;

typedef struct {
  int sizeComb;
  int totalCombinations; /* this says what is the total of combinations */
} combSize;

/* this function creates dynamicaly an array of data type, size sizeDataLine,
and the it fills the areas of each type of the variable data type, and then
returns the pointer if it all went ok or NULL if there was a problem in this
function */
data* getDataFromFile (char *nameFile, int sizeDataLine);

/* this function makes the calculation of the number of diferente combinations
of a set of nCombDim elements, and then returns the number if all went ok or -1
if there was a problem in the function */
int sizeCombination (int nCombDim);

/* this function makes the calculation of n! */
int factorial (int n);

/* this function creates all of possible combinations of sizeIndex elements, and
return the real size if all ok or 0 if there was a problem in this function */
int createCombinations (combinations *comb, int sizeIndex, int maxIndexElement);

/* this function sortes in ascending order, and then returns 1 if all went ok,
or 0 if there was a problem in the function */
int sorting(int *v, int size);

/* this function makes the calculation of the number to insert in the hash table,
using the array v and the array comb in the nComb position, it returns the number
if it went all ok or 0 if there was a problem */
int numberToInsertCalc (int *v, int sizeSum, combinations *comb, int nComb);

/* this function makes the sum of all the elements of the array v, and then
returns 1 if all went ok or 0 if there was a problem in the function */
int answerCalc (int *v, int size);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int answer = 0, sizeDataLine = SIZEDATALINE, sizeComb, i, j,linesDimComb = SIZEINDEX-MINSIZEINDEX+1 /* 6 */;
int sizeIndex, booleano, maxSum[sizeDataLine*2], size, numberToInsert, k, greater, nComb;
int found;
char nameFile[9] = "sets.txt", c[SIZEINDEX];
data *dataV;
combinations **combV;
combSize *sizeCombV;
tabela_dispersao *td;

dataV = getDataFromFile (nameFile, sizeDataLine);
if (dataV == NULL) {
  printf("\nThere was an error in the function getDataFromFile.");
  return 0;
}
/* sorting the data */
for (i = 0; i < sizeDataLine; i++) {
  booleano = sorting(dataV[i].data, dataV[i].realSize);
  if (booleano == 0) {
    printf("\nThere was a problem in the function sorting.");
    return 0;
  }
}

/* combinations matrix array creator */
combV = (combinations**) calloc (linesDimComb, sizeof (combinations*));
if (combV == NULL) {
  printf("\nThere was an error in the memory allocation of combV array.");
  return 0;
}
sizeCombV = (combSize*) calloc (linesDimComb, sizeof (combSize));
if (sizeCombV == NULL) {
  printf("\nThere was an error in the memory allocation of sizeCombV array.");
  return 0;
}
/* line starter, memory allocation */
i = 0;
for (j = MINSIZEINDEX; j < SIZEINDEX+1; j++) {
  sizeComb = sizeCombination (j);
  combV[i] = (combinations*) calloc (sizeComb, sizeof (combinations));
  if (combV[i] == NULL) {
    printf("\nThere was an error in the memory allocation of combV[i] array.");
    return 0;
  }
  i++;
}

/* filling of the matrix of combinations */
sizeIndex = MINSIZEINDEX-1; /* 6 elements from a set of 7 elements */
for (i = 0; i < linesDimComb; i++) {
  sizeCombV[i].totalCombinations = createCombinations (combV[i], sizeIndex, sizeIndex+1);
  if (sizeCombV[i].totalCombinations == 0) {
    printf ("\nThere was a problem in the function createCombinations.");
    return 0;
  }
  sizeIndex++;
}
/* datatesting */
sizeIndex = MINSIZEINDEX; /* 7 elements */
for (j = 0; j < sizeDataLine; j++) {
  /* new hast table */
  /* nComb is the number of combinations for a set of n elements */
  nComb = sizeCombV[dataV[j].realSize-sizeIndex].totalCombinations;
  td = tabela_nova(nComb, hash_djbm);
  if (td == NULL) {
    printf ("\nThere was an error in the function tabela_nova.");
    return 0;
  }
  size = dataV[j].realSize;
  /* reset maxSum array */
  for (i = 0; i < size; i++) {
    maxSum[i] = 0;
  }
  /* testing */
  found = 1; /* flag on */
  for (i = 0; i < nComb; i++) {
    /* bigger element */
    maxSum[1] = dataV[j].data[dataV[j].realSize-1];
    numberToInsert = numberToInsertCalc (dataV[j].data, size, combV[size-MINSIZEINDEX], i);
    if (numberToInsert == 0) {
      printf ("\nThere was a problem in the function numberToInsert, i = %d.\n", i);
      return 0;
    }
    /* string creation */
    sprintf(c,"%d",numberToInsert);
    /* test one: repetition check */
    booleano = tabela_existe(td, c);
    if (booleano == TABDISPERSAO_INVALIDA) {
      printf ("\nThere was an error in the function tabela_existe.\n");
      return 0;
    } else if (booleano == TABDISPERSAO_EXISTE) {
      /* number repeated in the hash, not the right solution */
      /*printf("\nNumber repeated.");*/
      booleano = tabela_esvazia(td);
      if (booleano == TABDISPERSAO_INVALIDA) {
        printf ("\nThere was an error in the function tabela_esvazia.");
        return 0;
      }
      found = 0;
      break;
    }
    /* if it reaches here then it must be done an insertion in the
    hash table */
    booleano = tabela_insere(td, c, c);
    if (booleano == TABDISPERSAO_ERRO || booleano == TABDISPERSAO_INVALIDA) {
      printf ("\nThere was an error in the function tabela_insere.");
      return 0;
    }
    /* flag high to detect if test two pass, if continue 1 ok */
    greater = 1;
    /* test two: greater than the less dimension groups */
    for (k = 1; k < combV[size-MINSIZEINDEX][i].sizeComb; k++) {
      /*printf("\nMax dim %d: %d:", j, maxSum[j]);*/
      if (maxSum[k] > numberToInsert) {
        /* bigger number detected in lower levels */
        greater = 0;
        found = 0;
        break;
      }
    }
    if (greater == 0) {
      /* not the right solution */
      booleano = tabela_esvazia(td);
      /*printf("\nNot greater than.");
      printf("\nmaxSum[j] = %d > numberToInsert = %d", maxSum[j], numberToInsert);*/
      if (booleano == TABDISPERSAO_INVALIDA) {
        printf ("\nThere was an error in the function tabela_esvazia.");
        return 0;
      }
      break;
    }
    /* if it reaches here we must now update the max if this is the
    case */
    if (numberToInsert > maxSum[combV[size-MINSIZEINDEX][i].sizeComb]) {
      maxSum[combV[size-MINSIZEINDEX][i].sizeComb] = numberToInsert;
    }
  }
  /* if it reaches here then this is the right solution */
  if (tabela_numelementos(td) && found == 1) {
    /* then this is the right solution, because the hash is not empty */
      booleano = answerCalc (dataV[j].data, dataV[j].realSize);
      if (booleano == 0) {
        printf("\nThere was a problem in the function answerCalc.");
        return 0;
      }
      answer+=booleano;
  }
  tabela_apaga(td);
}
/* memory free */
free (dataV);
/* free comb matrix */
for (i = 0; i < linesDimComb+1; i++) {
  free (combV[i]);
}
free (combV);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThe sum is %d.", answer);
printf("\n");
return 0;
}
/******************************************************************************/
data* getDataFromFile (char *nameFile, int sizeDataLine) {
/* this function creates dynamicaly an array of data type, size sizeDataLine,
and the it fills the areas of each type of the variable data type, and then
returns the pointer if it all went ok or NULL if there was a problem in this
function */
if (nameFile == NULL || sizeDataLine < 1) {
  return NULL;
}
data *dataV;
int lineN = 0, realSize;
FILE *f;
char line[400], *c;

dataV = (data*) calloc (sizeDataLine, sizeof(data));
if (dataV == NULL) {
  return NULL;
}
f = fopen (nameFile, "r");
if (f == NULL) {
  return NULL;
}
while ((fgets(line, sizeof (line), f)) != NULL) {
  realSize = 0;
  c = strtok(line, ",");
  dataV[lineN].data[realSize] = atoi(c);
  realSize++;
  while ((c = strtok(NULL,","))!= NULL) {
    dataV[lineN].data[realSize] = atoi(c);
    realSize++;
  }
  dataV[lineN].realSize = realSize;
  lineN++;
}
return dataV;
}
/******************************************************************************/
int sizeCombination (int nCombDim) {
/* this function makes the calculation of the number of diferente combinations
of a set of nCombDim elements, and then returns the number if all went ok or -1
if there was a problem in the function */
int answer = 0, n = nCombDim, r, nMinusR, nF, rF;
nF = factorial(nCombDim);
for (r = 2; r < nCombDim; r++) {
  rF = factorial(r);
  nMinusR = factorial (n-r);
  answer+=(nF/(rF*nMinusR));
}
return answer;
}
/******************************************************************************/
int factorial (int n) {
/* this function makes the calculation of n! */
int sign = 0, fac = n;
if (n < 0) {
  sign = 1;
  n*=-1; /* sign inverter */
}
n--;
while (n > 1) {
  fac*=n;
  n--;
}
if (sign == 1) {
  fac*=-1;
}
return fac;
}
/******************************************************************************/
int createCombinations (combinations *comb, int sizeIndex, int maxIndexElement) {
/* this function creates all of possible combinations of sizeIndex elements, and
return 1 if all ok or 0 if there was a problem in this function */
if (comb == NULL || sizeIndex < 1) {
  return 0;
}
int size, index[sizeIndex], nComb = 0, i;
for (size = 2; size < sizeIndex+1; size++) {
  if (size == 2) {
    for (index[0] = 0; index[0] < maxIndexElement-1; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement; index[1]++) {
        comb[nComb].sizeComb = size;
        for (i = 0; i < size; i++) {
          comb[nComb].index[i] = index[i];
        }
        nComb++;
      }
    }
  } else if (size == 3) {
    for (index[0] = 0; index[0] < maxIndexElement-2; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-1; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement; index[2]++) {
          comb[nComb].sizeComb = size;
          for (i = 0; i < size; i++) {
            comb[nComb].index[i] = index[i];
          }
          nComb++;
        }
      }
    }
  } else if (size == 4) {
    for (index[0] = 0; index[0] < maxIndexElement-3; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-2; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-1; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement; index[3]++) {
            comb[nComb].sizeComb = size;
            for (i = 0; i < size; i++) {
              comb[nComb].index[i] = index[i];
            }
            nComb++;
          }
        }
      }
    }
  } else if (size == 5) {
    for (index[0] = 0; index[0] < maxIndexElement-4; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-3; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-2; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement-1; index[3]++) {
            for (index[4] = index[3]+1; index[4] < maxIndexElement; index[4]++) {
              comb[nComb].sizeComb = size;
              for (i = 0; i < size; i++) {
                comb[nComb].index[i] = index[i];
              }
              nComb++;
            }
          }
        }
      }
    }
  } else if (size == 6) {
    for (index[0] = 0; index[0] < maxIndexElement-5; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-4; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-3; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement-2; index[3]++) {
            for (index[4] = index[3]+1; index[4] < maxIndexElement-1; index[4]++) {
              for (index[5] = index[4]+1; index[5] < maxIndexElement; index[5]++) {
                comb[nComb].sizeComb = size;
                for (i = 0; i < size; i++) {
                  comb[nComb].index[i] = index[i];
                }
                nComb++;
              }
            }
          }
        }
      }
    }
  } else if (size == 7) {
    for (index[0] = 0; index[0] < maxIndexElement-6; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-5; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-4; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement-3; index[3]++) {
            for (index[4] = index[3]+1; index[4] < maxIndexElement-2; index[4]++) {
              for (index[5] = index[4]+1; index[5] < maxIndexElement-1; index[5]++) {
                for (index[6] = index[5]+1; index[6] < maxIndexElement; index[6]++) {
                  comb[nComb].sizeComb = size;
                  for (i = 0; i < size; i++) {
                    comb[nComb].index[i] = index[i];
                  }
                  nComb++;
                }
              }
            }
          }
        }
      }
    }
  } else if (size == 8) {
    for (index[0] = 0; index[0] < maxIndexElement-7; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-6; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-5; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement-4; index[3]++) {
            for (index[4] = index[3]+1; index[4] < maxIndexElement-3; index[4]++) {
              for (index[5] = index[4]+1; index[5] < maxIndexElement-2; index[5]++) {
                for (index[6] = index[5]+1; index[6] < maxIndexElement-1; index[6]++) {
                  for (index[7] = index[6]+1; index[7] < maxIndexElement; index[7]++) {
                    comb[nComb].sizeComb = size;
                    for (i = 0; i < size; i++) {
                      comb[nComb].index[i] = index[i];
                    }
                    nComb++;
                  }
                }
              }
            }
          }
        }
      }
    }
  } else if (size == 9) {
    for (index[0] = 0; index[0] < maxIndexElement-8; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-7; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-6; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement-5; index[3]++) {
            for (index[4] = index[3]+1; index[4] < maxIndexElement-4; index[4]++) {
              for (index[5] = index[4]+1; index[5] < maxIndexElement-3; index[5]++) {
                for (index[6] = index[5]+1; index[6] < maxIndexElement-2; index[6]++) {
                  for (index[7] = index[6]+1; index[7] < maxIndexElement-1; index[7]++) {
                    for (index[8] = index[7]+1; index[8] < maxIndexElement; index[8]++) {
                      comb[nComb].sizeComb = size;
                      for (i = 0; i < size; i++) {
                        comb[nComb].index[i] = index[i];
                      }
                      nComb++;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  } else if (size == 10) {
    for (index[0] = 0; index[0] < maxIndexElement-9; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-8; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-7; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement-6; index[3]++) {
            for (index[4] = index[3]+1; index[4] < maxIndexElement-5; index[4]++) {
              for (index[5] = index[4]+1; index[5] < maxIndexElement-4; index[5]++) {
                for (index[6] = index[5]+1; index[6] < maxIndexElement-3; index[6]++) {
                  for (index[7] = index[6]+1; index[7] < maxIndexElement-2; index[7]++) {
                    for (index[8] = index[7]+1; index[8] < maxIndexElement-1; index[8]++) {
                      for (index[9] = index[8]+1; index[9] < maxIndexElement; index[9]++) {
                        comb[nComb].sizeComb = size;
                        for (i = 0; i < size; i++) {
                          comb[nComb].index[i] = index[i];
                        }
                        nComb++;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  } else if (size == 11) {
    for (index[0] = 0; index[0] < maxIndexElement-10; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-9; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-8; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement-7; index[3]++) {
            for (index[4] = index[3]+1; index[4] < maxIndexElement-6; index[4]++) {
              for (index[5] = index[4]+1; index[5] < maxIndexElement-5; index[5]++) {
                for (index[6] = index[5]+1; index[6] < maxIndexElement-4; index[6]++) {
                  for (index[7] = index[6]+1; index[7] < maxIndexElement-3; index[7]++) {
                    for (index[8] = index[7]+1; index[8] < maxIndexElement-2; index[8]++) {
                      for (index[9] = index[8]+1; index[9] < maxIndexElement-1; index[9]++) {
                        for (index[10] = index[9]+1; index[10] < maxIndexElement; index[10]++) {
                          comb[nComb].sizeComb = size;
                          for (i = 0; i < size; i++) {
                            comb[nComb].index[i] = index[i];
                          }
                          nComb++;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  } else if (size == 12) {
    for (index[0] = 0; index[0] < maxIndexElement-11; index[0]++) {
      for (index[1] = index[0]+1; index[1] < maxIndexElement-10; index[1]++) {
        for (index[2] = index[1]+1; index[2] < maxIndexElement-9; index[2]++) {
          for (index[3] = index[2]+1; index[3] < maxIndexElement-8; index[3]++) {
            for (index[4] = index[3]+1; index[4] < maxIndexElement-7; index[4]++) {
              for (index[5] = index[4]+1; index[5] < maxIndexElement-6; index[5]++) {
                for (index[6] = index[5]+1; index[6] < maxIndexElement-5; index[6]++) {
                  for (index[7] = index[6]+1; index[7] < maxIndexElement-4; index[7]++) {
                    for (index[8] = index[7]+1; index[8] < maxIndexElement-3; index[8]++) {
                      for (index[9] = index[8]+1; index[9] < maxIndexElement-2; index[9]++) {
                        for (index[10] = index[9]+1; index[10] < maxIndexElement-1; index[10]++) {
                          for (index[11] = index[10]+1; index[11] < maxIndexElement; index[11]++) {
                            comb[nComb].sizeComb = size;
                            for (i = 0; i < size; i++) {
                              comb[nComb].index[i] = index[i];
                            }
                            nComb++;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
return nComb;
}
/******************************************************************************/
int sorting(int *v, int size) {
/* this function sortes in ascending order, and then returns 1 if all went ok,
or 0 if there was a problem in the function */
if (v == NULL) {
  return 0;
}
int i, j, aux;
for (i = 0; i < size; i++) {
  for (j = i+1; j < size; j++) {
    if (v[i] > v[j]) {
      /* aux = i */
      aux = v[i];
      /* i = j */
      v[i] = v[j];
      /* j = aux */
      v[j] = aux;
    }
  }
}
return 1;
}
/******************************************************************************/
int numberToInsertCalc (int *v, int sizeSum, combinations *comb, int nComb) {
/* this function makes the calculation of the number to insert in the hash table,
using the array v and the array comb in the nComb position, it returns the number
if it went all ok or 0 if there was a problem */
if (v == NULL || comb == NULL || nComb < 0) {
  return 0;
}
int number = 0, i, index;
for (i = 0; i < comb[nComb].sizeComb; i++) {
  index = comb[nComb].index[i];
  number+=v[index];
}
return number;
}
/******************************************************************************/
int answerCalc (int *v, int size) {
/* this function makes the sum of all the elements of the array v, and then
returns 1 if all went ok or 0 if there was a problem in the function */
if (v == NULL) {
  return 0;
}
int sum = 0, i;
for (i = 0; i < size; i++) {
  sum+=v[i];
}
return sum;
}
/******************************************************************************/
