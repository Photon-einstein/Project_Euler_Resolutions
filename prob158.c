#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define SIZEALPHA 26

/* this function returns the char that are left to processe in the next step,
in the amount sizeRes, from the bulk sizeAlpha, that are complementar of the
sol solution, the result is dynamically allocated if sucess, or null if there
was a problem in the function */
char* charLeftCalc(char *sol, int sizeSol, int sizeRes, int sizeAlpha);

/* this function makes the calculation of max value of solution for a given
size, equal or less than sizeAlpha, and in the end it returns the value or 0
if there was a problem in the function */
long long int calcSol(int sizeAlpha);

/* this function makes the print of the acumulated count of solutions up to
this point, as also the index and the timeAux, and in the end it returns */
void printSol(char *index, long long int *nTotalSolution, double timeAux, int sizeAlpha);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int sizeAlpha;
long long int res_max;
sizeAlpha = SIZEALPHA;
res_max = calcSol(sizeAlpha);
if (res_max == 0) {
  printf("\nThere was a problem in the function calcSol.");
  return 0;
}
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nThe maximum value of p(n) is %lld.", res_max);
printf("\n");
return 0;
}
/******************************************************************************/
char* charLeftCalc(char *sol, int sizeSol, int sizeRes, int sizeAlpha) {
/* this function returns the char that are left to processe in the next step,
in the amount sizeRes, from the bulk sizeAlpha, that are complementar of the
sol solution, the result is dynamically allocated if sucess, or null if there
was a problem in the function */
if (sol == NULL || sizeSol < 1 || sizeAlpha < sizeSol || sizeRes < 1) {
  return NULL;
}
char *res, bulk[SIZEALPHA+1]={0};
int i, j;
res = (char*) calloc(sizeAlpha+1, sizeof(char));
if (res == NULL) {
  return NULL;
}
for (i = 0; i < sizeSol; ++i) {
  bulk[sol[i]-'a']=1;
}
for (i = 0, j = 0; i < sizeAlpha; ++i) {
  if (bulk[i] == 0) {
    res[j] = 'a'+i;
    ++j;
  }
}
res[j]='\0';
/* free memory */
return res;
}
/******************************************************************************/
long long int calcSol(int sizeAlpha) {
/* this function makes the calculation of max value of solution for a given
size, equal or less than sizeAlpha, and in the end it returns the value or 0
if there was a problem in the function */
clock_t startAux, endAux;
double timeAux;
startAux = clock();
/* Work to be done */
int i, *j, nTest=0;
long long int *nSolution, *nTotalSolution, maxRes=0;
char *index, **validIndex, *aux;
nSolution = (long long int*)calloc(sizeAlpha, sizeof (long long int));
if (nSolution == NULL) {
  return 0;
}
nTotalSolution = (long long int*)calloc(sizeAlpha, sizeof (long long int));
if (nTotalSolution == NULL) {
  return 0;
}
index = (char*)calloc(sizeAlpha, sizeof (char));
if (nSolution == NULL) {
  return 0;
}
validIndex = (char**)calloc(sizeAlpha, sizeof(char*));
if (validIndex == NULL) {
  return 0;
}
for (i = 0; i < sizeAlpha; ++i) {
  validIndex[i] = (char*)calloc(sizeAlpha+1, sizeof(char));
  if (validIndex[i] == NULL) {
    return 0;
  }
}
j = (int*)calloc(sizeAlpha, sizeof (int));
if (j == NULL) {
  return 0;
}
/* first for cyle: size 1 */
for (index[0] = 'a'; index[0] <= 'z'; ++index[0]) {
  /* second for cyle: size 2 */
  for (index[1] = 'a'; index[1] <= 'z'; ++index[1]) {
    index[2]='\0';
    if (index[0] == index[1]) {
      continue;
    }
    if (index[0] < index[1]) {
      nSolution[1] = 1;
      ++nTest;
      ++nTotalSolution[1];
      endAux = clock();
      timeAux = (double)(endAux - startAux) / CLOCKS_PER_SEC;
      printSol(index, nTotalSolution, timeAux, sizeAlpha);
    } else {
      nSolution[1] = 0;
    }
    /* calculation of the valid indexes for the next for cycle */
    aux = charLeftCalc(index, 2, sizeAlpha-2, sizeAlpha);
    if (aux == NULL) {
      return 0;
    }
    strcpy(validIndex[2], aux);
    free(aux);
    /* third for cyle: size 3 */
    for (j[2] = 0; j[2] < (sizeAlpha-2); ++j[2]) {
      index[2] = validIndex[2][j[2]];
      index[3]='\0';
      /* initialization of nSolution[i] */
      nSolution[2] = nSolution[2-1];
      /* calculation of nSolution[i] */
      if (index[1] < index[2]) {
        ++nSolution[2];
      }
      /* test */
      if (nSolution[2] >= 2) {
        break;
      } else if (nSolution[2] == 1) {
        ++nTotalSolution[2];
        endAux = clock();
        timeAux = (double)(endAux - startAux) / CLOCKS_PER_SEC;
        printSol(index, nTotalSolution, timeAux, sizeAlpha);
      }
      /* calculation of the valid indexes for the next for cycle */
      aux = charLeftCalc(index, 3, sizeAlpha-3, sizeAlpha);
      if (aux == NULL) {
        printf("\nError in the function charLeftCalc");
        return 0;
      }
      strcpy(validIndex[3], aux);
      free(aux);
        /* fourth for cyle: size 4 */
        for (j[3] = 0; j[3] < (sizeAlpha-3); ++j[3]) {
          index[3] = validIndex[3][j[3]];
          index[4]='\0';
          /* initialization of nSolution[i] */
          nSolution[3] = nSolution[3-1];
          /* calculation of nSolution[i] */
          if (index[2] < index[3]) {
            ++nSolution[3];
          }
          /* test */
          if (nSolution[3] >= 2) {
            break;
          } else if (nSolution[3] == 1) {
            /* new solution found */
            ++nTotalSolution[3];
          }
          /* calculation of the valid indexes for the next for cycle */
          aux = charLeftCalc(index, 4, sizeAlpha-4, sizeAlpha);
          if (aux == NULL) {
            return 0;
          }
          strcpy(validIndex[4], aux);
          free(aux);
          /* fifth for cyle: size 5 */
          for (j[4] = 0; j[4] < (sizeAlpha-4); ++j[4]) {
            index[4] = validIndex[4][j[4]];
            index[5]='\0';
            /* initialization of nSolution[i] */
            nSolution[4] = nSolution[4-1];
            /* calculation of nSolution[i] */
            if (index[3] < index[4]) {
              ++nSolution[4];
            }
            /* test */
            if (nSolution[4] >= 2) {
              break;
            } else if (nSolution[4] == 1) {
              /* new solution found */
              ++nTotalSolution[4];
            }
            /* calculation of the valid indexes for the next for cycle */
            aux = charLeftCalc(index, 5, sizeAlpha-5, sizeAlpha);
            if (aux == NULL) {
              return 0;
            }
            strcpy(validIndex[5], aux);
            free(aux);
            /* sixth for cyle: size 6 */
            for (j[5] = 0; j[5] < (sizeAlpha-5); ++j[5]) {
              index[5] = validIndex[5][j[5]];
              index[6]='\0';
              /* initialization of nSolution[i] */
              nSolution[5] = nSolution[5-1];
              /* calculation of nSolution[i] */
              if (index[4] < index[5]) {
                ++nSolution[5];
              }
              /* test */
              if (nSolution[5] >= 2) {
                break;
              } else if (nSolution[5] == 1) {
                /* new solution found */
                ++nTotalSolution[5];
              }
              /* calculation of the valid indexes for the next for cycle */
              aux = charLeftCalc(index, 6, sizeAlpha-6, sizeAlpha);
              if (aux == NULL) {
                return 0;
              }
              strcpy(validIndex[6], aux);
              free(aux);
              /* 7th for cyle: size 7 */
              for (j[6] = 0; j[6] < (sizeAlpha-6); ++j[6]) {
                index[6] = validIndex[6][j[6]];
                index[7]='\0';
                /* initialization of nSolution[i] */
                nSolution[6] = nSolution[6-1];
                /* calculation of nSolution[i] */
                if (index[5] < index[6]) {
                  ++nSolution[6];
                }
                /* test */
                if (nSolution[6] >= 2) {
                  break;
                } else if (nSolution[6] == 1) {
                  /* new solution found */
                  ++nTotalSolution[6];
                }
                /* calculation of the valid indexes for the next for cycle */
                aux = charLeftCalc(index, 7, sizeAlpha-7, sizeAlpha);
                if (aux == NULL) {
                  return 0;
                }
                strcpy(validIndex[7], aux);
                free(aux);
                /* 8th for cyle: size 8 */
                for (j[7] = 0; j[7] < (sizeAlpha-7); ++j[7]) {
                  index[7] = validIndex[7][j[7]];
                  index[8]='\0';
                  /* initialization of nSolution[i] */
                  nSolution[7] = nSolution[7-1];
                  /* calculation of nSolution[i] */
                  if (index[6] < index[7]) {
                    ++nSolution[7];
                  }
                  /* test */
                  if (nSolution[7] >= 2) {
                    break;
                  } else if (nSolution[7] == 1) {
                    /* new solution found */
                    ++nTotalSolution[7];
                  }
                  /* calculation of the valid indexes for the next for cycle */
                  aux = charLeftCalc(index, 8, sizeAlpha-8, sizeAlpha);
                  if (aux == NULL) {
                    return 0;
                  }
                  strcpy(validIndex[8], aux);
                  free(aux);
                  //continue;
                  /* 9th for cyle: size 9 */
                  for (j[8] = 0; j[8] < (sizeAlpha-8); ++j[8]) {
                    index[8] = validIndex[8][j[8]];
                    index[9]='\0';
                    /* initialization of nSolution[i] */
                    nSolution[8] = nSolution[8-1];
                    /* calculation of nSolution[i] */
                    if (index[7] < index[8]) {
                      ++nSolution[8];
                    }
                    /* test */
                    if (nSolution[8] >= 2) {
                      break;
                    } else if (nSolution[8] == 1) {
                      /* new solution found */
                      ++nTotalSolution[8];
                    }
                    /* calculation of the valid indexes for the next for cycle */
                    aux = charLeftCalc(index, 9, sizeAlpha-9, sizeAlpha);
                    if (aux == NULL) {
                      return 0;
                    }
                    strcpy(validIndex[9], aux);
                    free(aux);
                    /* 10th for cyle: size 10 */
                    for (j[9] = 0; j[9] < (sizeAlpha-9); ++j[9]) {
                      index[9] = validIndex[9][j[9]];
                      index[10]='\0';
                      /* initialization of nSolution[i] */
                      nSolution[9] = nSolution[9-1];
                      /* calculation of nSolution[i] */
                      if (index[8] < index[9]) {
                        ++nSolution[9];
                      }
                      /* test */
                      if (nSolution[9] >= 2) {
                        break;
                      } else if (nSolution[9] == 1) {
                        /* new solution found */
                        ++nTotalSolution[9];
                      }
                      /* calculation of the valid indexes for the next for cycle */
                      aux = charLeftCalc(index, 10, sizeAlpha-10, sizeAlpha);
                      if (aux == NULL) {
                        return 0;
                      }
                      strcpy(validIndex[10], aux);
                      free(aux);
                      /* 11th for cyle: size 11 */
                      for (j[10] = 0; j[10] < (sizeAlpha-10); ++j[10]) {
                        index[10] = validIndex[10][j[10]];
                        index[11]='\0';
                        /* initialization of nSolution[i] */
                        nSolution[10] = nSolution[10-1];
                        /* calculation of nSolution[i] */
                        if (index[9] < index[10]) {
                          ++nSolution[10];
                        }
                        /* test */
                        if (nSolution[10] >= 2) {
                          break;
                        } else if (nSolution[10] == 1) {
                          /* new solution found */
                          ++nTotalSolution[10];
                        }

                        /* calculation of the valid indexes for the next for cycle */
                        aux = charLeftCalc(index, 11, sizeAlpha-11, sizeAlpha);
                        if (aux == NULL) {
                          return 0;
                        }
                        strcpy(validIndex[11], aux);
                        free(aux);
                        /* 12th for cyle: size 12 */
                        for (j[11] = 0; j[11] < (sizeAlpha-11); ++j[11]) {
                          index[11] = validIndex[11][j[11]];
                          index[12]='\0';
                          /* initialization of nSolution[i] */
                          nSolution[11] = nSolution[11-1];
                          /* calculation of nSolution[i] */
                          if (index[10] < index[11]) {
                            ++nSolution[11];
                          }
                          /* test */
                          if (nSolution[11] >= 2) {
                            break;
                          } else if (nSolution[11] == 1) {
                            /* new solution found */
                            ++nTotalSolution[11];
                          }
                          /* calculation of the valid indexes for the next for cycle */
                          aux = charLeftCalc(index, 12, sizeAlpha-12, sizeAlpha);
                          if (aux == NULL) {
                            return 0;
                          }
                          strcpy(validIndex[12], aux);
                          free(aux);
                          /* 13th for cyle: size 13 */
                          for (j[12] = 0; j[12] < (sizeAlpha-12); ++j[12]) {
                             index[12] = validIndex[12][j[12]];
                            index[13]='\0';
                            /* initialization of nSolution[i] */
                            nSolution[12] = nSolution[12-1];
                            /* calculation of nSolution[i] */
                            if (index[11] < index[12]) {
                              ++nSolution[12];
                            }
                            /* test */
                            if (nSolution[12] >= 2) {
                              break;
                            } else if (nSolution[12] == 1) {
                              /* new solution found */
                              ++nTotalSolution[12];
                            }
                            /* calculation of the valid indexes for the next for cycle */
                            aux = charLeftCalc(index, 13, sizeAlpha-13, sizeAlpha);
                            if (aux == NULL) {
                              return 0;
                            }
                            strcpy(validIndex[13], aux);
                            free(aux);
                            /* 14th for cyle: size 14 */
                            for (j[13] = 0; j[13] < (sizeAlpha-13); ++j[13]) {
                              index[13] = validIndex[13][j[13]];
                              index[14]='\0';
                              /* initialization of nSolution[i] */
                              nSolution[13] = nSolution[13-1];
                              /* calculation of nSolution[i] */
                              if (index[12] < index[13]) {
                                ++nSolution[13];
                              }
                              /* test */
                              if (nSolution[13] >= 2) {
                                break;
                              } else if (nSolution[13] == 1) {
                                /* new solution found */
                                ++nTotalSolution[13];
                              }
                              /* calculation of the valid indexes for the next for cycle */
                              aux = charLeftCalc(index, 14, sizeAlpha-14, sizeAlpha);
                              if (aux == NULL) {
                                return 0;
                              }
                              strcpy(validIndex[14], aux);
                              free(aux);
                              /* 15th for cyle: size 15 */
                              for (j[14] = 0; j[14] < (sizeAlpha-14); ++j[14]) {
                                index[14] = validIndex[14][j[14]];
                                index[15]='\0';
                                /* initialization of nSolution[i] */
                                nSolution[14] = nSolution[14-1];
                                /* calculation of nSolution[i] */
                                if (index[13] < index[14]) {
                                  ++nSolution[14];
                                }
                                /* test */
                                if (nSolution[14] >= 2) {
                                  break;
                                } else if (nSolution[14] == 1) {
                                  /* new solution found */
                                  ++nTotalSolution[14];
                                }
                                /* calculation of the valid indexes for the next for cycle */
                                aux = charLeftCalc(index, 15, sizeAlpha-15, sizeAlpha);
                                if (aux == NULL) {
                                  return 0;
                                }
                                strcpy(validIndex[15], aux);
                                free(aux);
                                /* 16th for cyle: size 16 */
                                for (j[15] = 0; j[15] < (sizeAlpha-15); ++j[15]) {
                                  index[15] = validIndex[15][j[15]];
                                  index[16]='\0';
                                  /* initialization of nSolution[i] */
                                  nSolution[15] = nSolution[15-1];
                                  /* calculation of nSolution[i] */
                                  if (index[14] < index[15]) {
                                    ++nSolution[15];
                                  }
                                  /* test */
                                  if (nSolution[15] >= 2) {
                                    break;
                                  } else if (nSolution[15] == 1) {
                                    /* new solution found */
                                    ++nTotalSolution[15];
                                  }
                                  /* calculation of the valid indexes for the next for cycle */
                                  aux = charLeftCalc(index, 16, sizeAlpha-16, sizeAlpha);
                                  if (aux == NULL) {
                                    return 0;
                                  }
                                  strcpy(validIndex[16], aux);
                                  free(aux);
                                  /* 17th for cyle: size 17 */
                                  for (j[16] = 0; j[16] < (sizeAlpha-16); ++j[16]) {
                                    index[16] = validIndex[16][j[16]];
                                    index[17]='\0';
                                    /* initialization of nSolution[i] */
                                    nSolution[16] = nSolution[16-1];
                                    /* calculation of nSolution[i] */
                                    if (index[15] < index[16]) {
                                      ++nSolution[16];
                                    }
                                    /* test */
                                    if (nSolution[16] >= 2) {
                                      break;
                                    } else if (nSolution[16] == 1) {
                                      /* new solution found */
                                      ++nTotalSolution[16];
                                    }
                                    /* calculation of the valid indexes for the next for cycle */
                                    aux = charLeftCalc(index, 17, sizeAlpha-17, sizeAlpha);
                                    if (aux == NULL) {
                                      return 0;
                                    }
                                    strcpy(validIndex[17], aux);
                                    free(aux);
                                    /* 18th for cyle: size 18 */
                                    for (j[17] = 0; j[17] < (sizeAlpha-17); ++j[17]) {
                                      index[17] = validIndex[17][j[17]];
                                      index[18]='\0';
                                      /* initialization of nSolution[i] */
                                      nSolution[17] = nSolution[17-1];
                                      /* calculation of nSolution[i] */
                                      if (index[16] < index[17]) {
                                        ++nSolution[17];
                                      }
                                      /* test */
                                      if (nSolution[17] >= 2) {
                                        break;
                                      } else if (nSolution[17] == 1) {
                                        /* new solution found */
                                        ++nTotalSolution[17];
                                      }
                                      /* calculation of the valid indexes for the next for cycle */
                                      aux = charLeftCalc(index, 18, sizeAlpha-18, sizeAlpha);
                                      if (aux == NULL) {
                                        return 0;
                                      }
                                      strcpy(validIndex[18], aux);
                                      free(aux);
                                      /* 19th for cyle: size 19 */
                                      for (j[18] = 0; j[18] < (sizeAlpha-18); ++j[18]) {
                                        index[18] = validIndex[18][j[18]];
                                        index[19]='\0';
                                        /* initialization of nSolution[i] */
                                        nSolution[18] = nSolution[18-1];
                                        /* calculation of nSolution[i] */
                                        if (index[17] < index[18]) {
                                          ++nSolution[18];
                                        }
                                        /* test */
                                        if (nSolution[18] >= 2) {
                                          break;
                                        } else if (nSolution[18] == 1) {
                                          /* new solution found */
                                          ++nTotalSolution[18];
                                        }
                                        /* calculation of the valid indexes for the next for cycle */
                                        aux = charLeftCalc(index, 19, sizeAlpha-19, sizeAlpha);
                                        if (aux == NULL) {
                                          return 0;
                                        }
                                        strcpy(validIndex[19], aux);
                                        free(aux);
                                        /* 20th for cyle: size 20 */
                                        for (j[19] = 0; j[19] < (sizeAlpha-19); ++j[19]) {
                                          index[19] = validIndex[19][j[19]];
                                          index[20]='\0';
                                          /* initialization of nSolution[i] */
                                          nSolution[19] = nSolution[19-1];
                                          /* calculation of nSolution[i] */
                                          if (index[18] < index[19]) {
                                            ++nSolution[19];
                                          }
                                          /* test */
                                          if (nSolution[19] >= 2) {
                                            break;
                                          } else if (nSolution[19] == 1) {
                                            /* new solution found */
                                            ++nTotalSolution[19];
                                          }
                                          /* calculation of the valid indexes for the next for cycle */
                                          aux = charLeftCalc(index, 20, sizeAlpha-20, sizeAlpha);
                                          if (aux == NULL) {
                                            return 0;
                                          }
                                          strcpy(validIndex[20], aux);
                                          free(aux);
                                          /* 21th for cyle: size 21 */
                                          for (j[20] = 0; j[20] < (sizeAlpha-20); ++j[20]) {
                                            index[20] = validIndex[20][j[20]];
                                            index[21]='\0';
                                            /* initialization of nSolution[i] */
                                            nSolution[20] = nSolution[20-1];
                                            /* calculation of nSolution[i] */
                                            if (index[19] < index[20]) {
                                              ++nSolution[20];
                                            }
                                            /* test */
                                            if (nSolution[20] >= 2) {
                                              break;
                                            } else if (nSolution[20] == 1) {
                                              /* new solution found */
                                              ++nTotalSolution[20];
                                            }
                                            /* calculation of the valid indexes for the next for cycle */
                                            aux = charLeftCalc(index, 21, sizeAlpha-21, sizeAlpha);
                                            if (aux == NULL) {
                                              return 0;
                                            }
                                            strcpy(validIndex[21], aux);
                                            free(aux);
                                            /* 22th for cyle: size 22 */
                                            for (j[21] = 0; j[21] < (sizeAlpha-21); ++j[21]) {
                                              index[21] = validIndex[21][j[21]];
                                              index[22]='\0';
                                              /* initialization of nSolution[i] */
                                              nSolution[21] = nSolution[21-1];
                                              /* calculation of nSolution[i] */
                                              if (index[20] < index[21]) {
                                                ++nSolution[21];
                                              }
                                              /* test */
                                              if (nSolution[21] >= 2) {
                                                break;
                                              } else if (nSolution[21] == 1) {
                                                /* new solution found */
                                                ++nTotalSolution[21];
                                              }
                                              /* calculation of the valid indexes for the next for cycle */
                                              aux = charLeftCalc(index, 22, sizeAlpha-22, sizeAlpha);
                                              if (aux == NULL) {
                                                return 0;
                                              }
                                              strcpy(validIndex[22], aux);
                                              free(aux);
                                              /* 23th for cyle: size 23 */
                                              for (j[22] = 0; j[22] < (sizeAlpha-22); ++j[22]) {
                                                index[22] = validIndex[22][j[22]];
                                                index[23]='\0';
                                                /* initialization of nSolution[i] */
                                                nSolution[22] = nSolution[22-1];
                                                /* calculation of nSolution[i] */
                                                if (index[21] < index[22]) {
                                                  ++nSolution[22];
                                                }
                                                /* test */
                                                if (nSolution[22] >= 2) {
                                                  break;
                                                } else if (nSolution[22] == 1) {
                                                  /* new solution found */
                                                  ++nTotalSolution[22];
                                                }
                                                /* calculation of the valid indexes for the next for cycle */
                                                aux = charLeftCalc(index, 23, sizeAlpha-23, sizeAlpha);
                                                if (aux == NULL) {
                                                  return 0;
                                                }
                                                strcpy(validIndex[23], aux);
                                                free(aux);
                                                /* 24th for cyle: size 24 */
                                                for (j[23] = 0; j[23] < (sizeAlpha-23); ++j[23]) {
                                                  index[23] = validIndex[23][j[23]];
                                                  index[24]='\0';
                                                  /* initialization of nSolution[i] */
                                                  nSolution[23] = nSolution[23-1];
                                                  /* calculation of nSolution[i] */
                                                  if (index[22] < index[23]) {
                                                    ++nSolution[23];
                                                  }
                                                  /* test */
                                                  if (nSolution[23] >= 2) {
                                                    break;
                                                  } else if (nSolution[23] == 1) {
                                                    /* new solution found */
                                                    ++nTotalSolution[23];
                                                  }
                                                  /* calculation of the valid indexes for the next for cycle */
                                                  aux = charLeftCalc(index, 24, sizeAlpha-24, sizeAlpha);
                                                  if (aux == NULL) {
                                                    return 0;
                                                  }
                                                  strcpy(validIndex[24], aux);
                                                  free(aux);
                                                  /* 25th for cyle: size 25 */
                                                  for (j[24] = 0; j[24] < (sizeAlpha-24); ++j[24]) {
                                                    index[24] = validIndex[24][j[24]];
                                                    index[25]='\0';
                                                    /* initialization of nSolution[i] */
                                                    nSolution[24] = nSolution[24-1];
                                                    /* calculation of nSolution[i] */
                                                    if (index[23] < index[24]) {
                                                      ++nSolution[24];
                                                    }
                                                    /* test */
                                                    if (nSolution[24] >= 2) {
                                                      break;
                                                    } else if (nSolution[24] == 1) {
                                                      /* new solution found */
                                                      ++nTotalSolution[24];
                                                    }
                                                    /* calculation of the valid indexes for the next for cycle */
                                                    aux = charLeftCalc(index, 25, sizeAlpha-25, sizeAlpha);
                                                    if (aux == NULL) {
                                                      return 0;
                                                    }
                                                    strcpy(validIndex[25], aux);
                                                    free(aux);
                                                    /* 26th for cyle: size 26 */
                                                    for (j[25] = 0; j[25] < (sizeAlpha-25); ++j[25]) {
                                                      index[25] = validIndex[25][j[25]];
                                                      index[26]='\0';
                                                      /* initialization of nSolution[i] */
                                                      nSolution[25] = nSolution[25-1];
                                                      /* calculation of nSolution[i] */
                                                      if (index[24] < index[25]) {
                                                        ++nSolution[25];
                                                      }
                                                      /* test */
                                                      if (nSolution[25] >= 2) {
                                                        break;
                                                      } else if (nSolution[25] == 1) {
                                                        /* new solution found */
                                                        ++nTotalSolution[25];
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
/* max calc */
for (i = 0; i < sizeAlpha; ++i) {
  printf("\nnTotalSolution[%d] = %lld", i, nTotalSolution[i]);
  if (maxRes < nTotalSolution[i]) {
    maxRes = nTotalSolution[i];
  }
}
/* free memory */
free(nSolution);
free(index);
for (i = 0; i < sizeAlpha; ++i) {
  free(validIndex[i]);
}
free(validIndex);
free(j);
free(nTotalSolution);
return maxRes;
}
/******************************************************************************/
void printSol(char *index, long long int *nTotalSolution, double timeAux, int sizeAlpha) {
/* this function makes the print of the acumulated count of solutions up to
this point, as also the index and the timeAux, and in the end it returns */
int i;
printf("\n%s", index);
for (i = 0; i < sizeAlpha; ++i) {
  printf("\nnTotalSolution[%d-1] = %lld;", i+1, nTotalSolution[i]);
}
printf("\nTime in seconds: %f\n", timeAux);
fflush(NULL);
return;
}
/******************************************************************************/
