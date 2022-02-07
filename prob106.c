#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZESET 12

typedef struct {
  int index[SIZESET]; /* max combinations have 12 elements */
  int sizeComb; /* this says what is size of this combination */
} combinations;

/* this function makes the calculation of the number of diferente combinations
of a set of nCombDim elements, and then returns the number if all went ok or -1
if there was a problem in the function */
int sizeCombination (int nCombDim);

/* this function makes the calculation of n! */
int factorial (int n);

/* this function creates all of possible combinations of sizeIndex elements, and
return the real size if all ok or 0 if there was a problem in this function */
int createCombinations (combinations *comb, int sizeIndex, int maxIndexElement);

/* this function makes the comparation between the set i and the set j, and
returns 1 if they have all diferent elements or 0 if they have common elements,
or -1 if there was a problem in the function */
int testingDiferentElements (combinations *comb, int i, int j);

/* this function tests the encapsulation of 2 arrays of combinations, one in
index posBigger, and the other in the index posLower, and then returns -1 if
there was a problem in the function or 1 if went all ok or 0 if fail the test */
int encapsulationTest (combinations *comb, int posBigger, int posLower);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int sizeSet = SIZESET, maxIndexElement = SIZESET, sizeIndex = sizeSet/2, sizeComb, realSizeComb;
int answer = 0, booleano, i, j;
combinations *comb;

/* sizeComb calculation */
sizeComb = sizeCombination (sizeSet);
if (sizeComb == -1) {
  printf("\nThere was an error in the function sizeCombination.");
}
/* array combinations creation */
comb = (combinations*) calloc (sizeComb, sizeof (combinations));
if (comb == NULL) {
  printf("\nThere was an error in the memory allocation of comb array.");
  return 0;
}
/* fulling of the comb array */
realSizeComb = createCombinations (comb, sizeIndex, maxIndexElement);
if (realSizeComb == 0) {
  printf("\nThere was an error in the function createCombinations.");
  return 0;
}
/* testing elements from sets diferent from each other */
for (i = realSizeComb-1; i > 0; i--) {
  for (j = i-1; j > -1; j--) {
    if (comb[i].sizeComb != comb[j].sizeComb) {
      /* j reset */
      break;
    }
    booleano = testingDiferentElements (comb, i, j);
    if (booleano == -1) {
      printf("\nThere was an error in the function testingDiferentElements.");
      return 0;
    } else if (booleano == 0) {
      /* test fail, common elements true */
      continue;
    }
    /*if it reaches here then the set i and the set j have not commom elements*/
    booleano = encapsulationTest (comb, i, j);
    if (booleano == -1) {
      printf("\nThere was a problem in the function encapsulationTest.");
      return 0;
    } else if (booleano == 0) {
      /* test fail */
      answer++;
    }
  }
}
free (comb);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nWe must check %d set pair for n = %d.", answer, sizeSet);
printf("\n");
return 0;
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
int testingDiferentElements (combinations *comb, int i, int j) {
/* this function makes the comparation between the set i and the set j, and
returns 1 if they have all diferent elements or 0 if they have common elements,
or -1 if there was a problem in the function */
if (comb == NULL || i < 0 || j < 0) {
  return -1;
}
if (comb[i].sizeComb != comb[j].sizeComb) {
  return -1;
}
int x, y;
for (x = 0; x < comb[i].sizeComb; x++) {
  for (y = 0; y < comb[j].sizeComb; y++) {
    if (comb[i].index[x] == comb[j].index[y]) {
      /* test fail */
      return 0;
    }
  }
}
/* if it reaches here then test ok */
return 1;
}
/******************************************************************************/
int encapsulationTest (combinations *comb, int posBigger, int posLower) {
/* this function tests the encapsulation of 2 arrays of combinations, one in
index posBigger, and the other in the index posLower, and then returns -1 if
there was a problem in the function or 1 if went all ok or 0 if fail the test */
if (comb == NULL || posBigger < 0 || posLower < 0) {
  return -1;
}
if (comb[posBigger].sizeComb != comb[posLower].sizeComb) {
  return -1;
}
int i, j;
for (i = 0; i < comb[posBigger].sizeComb; i++) {
  j = i;
  if (comb[posBigger].index[i] < comb[posLower].index[j]) {
    return 0;
  }
}
/* if it reaches here then it went all ok */
return 1;
}
/******************************************************************************/
