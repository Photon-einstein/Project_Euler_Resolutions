#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabdispersao.h"
#define MAXSIZE 300
#define SIZESUM 7
#define SIZEINDEX 6
#define START 45
typedef struct {
  int index[SIZEINDEX]; /* max combinations have 6 elements */
  int sizeComb; /* this says what is size of this combination */
} combinations;

/* this function creates all of possible combinations of sizeIndex elements, and
return the real size if all ok or 0 if there was a problem in this function */
int createCombinations (combinations *comb, int sizeIndex, int maxIndexElement);

/* this function returns the sum of the elements of the array v, or 0 if there
was a problem in the function */
int sumCalc (int *v, int size);

/* this function makes the calculation of the number to insert in the hash table,
using the array v and the array comb in the nComb position, it returns the number
if it went all ok or 0 if there was a problem */
int numberToInsertCalc (int *v, int sizeSum, combinations *comb, int nComb);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
combinations comb[MAXSIZE];
int booleano, sizeIndex = SIZEINDEX, size = SIZESUM, i = 0, nComb, j, greater, found = 0;
int v[size], refSum = 255, sum, n = 0, numberToInsert, maxSum[2*size], solution[size];
tabela_dispersao*td;
char c[size];

nComb = createCombinations (comb, sizeIndex, size);
td = tabela_nova(nComb, hash_djbm);
if (td == NULL) {
  printf ("\nThere was an error in the function tabela_nova.");
  return 0;
}
if (nComb == 0) {
  printf ("\nThere was a problem in the function createCombinations.");
  return 0;
}
for (v[6] = START; v[6] < START+1; v[6]++) {
  if (found == 1) {break;}
  for (v[5] = START-5; v[5] < v[6]; v[5]++) {
    if (found == 1) {break;}
    for (v[4] = START-10; v[4] < v[5]; v[4]++) {
      if (found == 1) {break;}
      for (v[3] = START-15; v[3] < v[4]; v[3]++) {
        if (found == 1) {break;}
        for (v[2] = START-20; v[2] < v[3]; v[2]++) {
          if (found == 1) {break;}
          for (v[1] = START-25; v[1] < v[2]; v[1]++) {
            if (found == 1) {break;}
            for (v[0] = START-30; v[0] < v[1]; v[0]++) {
              if (found == 1) {break;}
              /* sum test comparation */
              sum = sumCalc (v, size);
              if (sum == 0) {
                printf ("\nThere was a problem in the function sumCalc.");
                return 0;
              } else if (sum > refSum) {
                continue;
              }
              /* reset maxSum array */
              for (i = 0; i < size; i++) {
                maxSum[i] = 0;
              }
              /* if it reaches here then the sum is < 255 */
              booleano = tabela_esvazia(td);
              if (booleano == TABDISPERSAO_INVALIDA) {
                printf ("\nThere was an error in the function tabela_esvazia.");
                return 0;
              }
              for (i = 0; i < nComb; i++) {
                /* bigger element */
                maxSum[1] = v[6];
                numberToInsert = numberToInsertCalc (v, size, comb, i);
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
                for (j = 1; j < comb[i].sizeComb; j++) {
                  /*printf("\nMax dim %d: %d:", j, maxSum[j]);*/
                  if (maxSum[j] > numberToInsert) {
                    /* bigger number detected in lower levels */
                    greater = 0;
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
                if (numberToInsert > maxSum[comb[i].sizeComb]) {
                  maxSum[comb[i].sizeComb] = numberToInsert;
                }
              }

              /* if it reaches here then this is the right solution */
              if (tabela_numelementos(td)) {
                /* then this is the right solution, because the hash is not empty */
                for (i = 0; i < size; i++) {
                  solution[i] = v[i];
                }
                found = 1;
                break;
              }
            }
          }
        }
      }
    }
  }
}
/* end of the work */
tabela_apaga(td);
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
if (found == 1) {
  printf ("\nThe solution is: ");
  for (i = 0; i < size; i++) {
    printf ("%d", solution[i]);
  }
}
printf("\nTime in seconds: %lf", tempo);
printf ("\n");
return 0;
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
  }
}
return nComb;
}
/******************************************************************************/
int sumCalc (int *v, int size) {
/* this function returns the sum of the elements of the array v, or 0 if there
was a problem in the function */
if (v == NULL || size < 1) {
  return 0;
}
int sum = 0, i;
for (i = 0; i < size; i++) {
  sum+=v[i];
}
return sum;
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
