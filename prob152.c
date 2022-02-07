#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXDEN 80
#define NFORMAX 24
#define MAXNUM 1000000000000000
#define GOAL 2

typedef struct {
  long long int numerator;
  long long int denominator;
  double sumAcum; /* sum acumulated until this step */
} sol;

/* this function prints the answer up to size of index
and then it returns */
void printAnswer(int *index, int size, int count);

/* this function is the euclidean algorithm, and calculates the
great common diviser between a and b */
long long int gcd(long long int a, long long int b);

/* this function makes the calculation of the number of solutions
up to maxDen */
int calcSolutions(int maxDen, int nForMax);

/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int primeTest (int nTest);

/* this function returns 1 if (goal-sumAcum) <= (nForMax-actualIndex)/testIndex²
or 0 if not */
int boolTest(double goal, double sumAcum, int actualIndex, int nForMax, int testIndex);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int maxDen = MAXDEN, nSolutions, nForMax = NFORMAX;
/* memory allocation */
nSolutions = calcSolutions(maxDen, nForMax);
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", time);
printf("\nThe number of solutions up to %d is %d.", maxDen, nSolutions);
printf("\n");
return 0;
}
/******************************************************************************/
void printAnswer(int *index, int size, int count) {
/* this function prints the answer up to size of index
and then it returns */
int i;
printf ("\n");
for (i = 0; i < size; ++i) {
  printf("%d ", index[i]);
}
printf("\tsize = %d\tcount = %d", size, count);
fflush(NULL);
return;
}
/******************************************************************************/
long long int gcd(long long int a, long long int b) {
/* this function is the euclidean algorithm, and calculates the
great common diviser between a and b */
if (a < 0 || b < 0 ) {
  printf("\nOverflow!");
}
while (a != b) {
     if (a > b) {
         a = a - b;
     } else {
         b = b - a;
       }
 }
 return a;
}
/******************************************************************************/
int calcSolutions(int maxDen, int nForMax) {
/* this function makes the calculation of the number of solutions
up to maxDen */
int *index, *maxIndex, i, j, count = 0, d, boolean;
sol *s;
int *id;
/* memory allocation */
index = (int*) calloc(nForMax, sizeof (int));
if (index == NULL) {
  return 0;
}
maxIndex = (int*) calloc(nForMax, sizeof (int));
for (i = nForMax-1, j = 0; i >= 0; --i, ++j) {
  maxIndex[i] = maxDen-j;
}
s = (sol*) calloc(nForMax, sizeof (sol));
if (s == NULL) {
  return 0;
}
/* index id malloc  */
id = (int*)calloc(maxDen+1, sizeof (int));
if (id == NULL) {
  return 0;
}
for (i = 1; i < maxDen+1; ++i) {
  if (i==2||i==3||i==4||i==5||i==6||i==7||i==8||i==9||i==10||i==12||i==13||
      i==14||i==15||i==18||i==20||i==21||i==24||i==28||i==30||i==35||i==36||i==39||i==40||
      i==42||i==45||i==52||i==56||i==60||i==63||i==70||i==72) {
      id[i] = 1;
  } else {
      id[i] = 0;
  }
}
/* calculation */
/* for 0 */
for (index[0] = 2; index[0] < 3; ++index[0]) {
if (id[index[0] == 0]) {
  continue;
}
printf("\nindex[0] = %d", index[0]);
fflush(NULL);
/* sol update */
s[0].numerator = 1;
s[0].denominator = index[0]*index[0];
s[0].sumAcum = (double)s[0].numerator/s[0].denominator;
/* for 1 */
for (index[1] = 3; index[1] < 3+1; ++index[1]) {
  if (id[index[1] == 0]) {
    continue;
  } else if (!boolTest(1.0/GOAL, s[0].sumAcum, 2, nForMax, index[1])) {
    break;
  }
  //printf("\nindex[1] = %d", index[1]);
  fflush(NULL);
  /* downsizing and update */
  d = gcd(s[0].denominator+index[1]*index[1]*s[0].numerator, s[0].denominator*index[1]*index[1]);
  s[1].numerator = (s[0].denominator+index[1]*index[1]*s[0].numerator)/d;
  s[1].denominator = (s[0].denominator*index[1]*index[1])/d;
  s[1].sumAcum+=(double)s[1].numerator/s[1].denominator;
/* for 2 */
for (index[2] = index[1]+1; index[2] < maxIndex[2]+1; ++index[2]) {
  if (id[index[2]] == 0) {
    continue;
  } else if (!boolTest(1.0/GOAL, s[1].sumAcum, 3, nForMax, index[2])) {
    break;
  }
  //printf("\nindex[2] = %d", index[2]);
  fflush(NULL);
  /* downsizing and update */
  d = gcd(s[1].denominator+index[2]*index[2]*s[1].numerator, s[1].denominator*index[2]*index[2]);
  s[2].numerator = (s[1].denominator+index[2]*index[2]*s[1].numerator)/d;
  s[2].denominator = (s[1].denominator*index[2]*index[2])/d;
  s[2].sumAcum+=(double)s[2].numerator/s[2].denominator;
/* for 3 */
for (index[3] = index[2]+1; index[3] < maxIndex[3]+1; ++index[3]) {
  if (id[index[3]] == 0) {
    continue;
  } else if (!boolTest(1.0/GOAL, s[2].sumAcum, 4, nForMax, index[3])) {
    break;
  }
  //printf("\nindex[3] = %d, count = %d", index[3], count);
  fflush(NULL);
  /* downsizing and update */
  d = gcd(s[2].denominator+index[3]*index[3]*s[2].numerator, s[2].denominator*index[3]*index[3]);
  s[3].numerator = (s[2].denominator+index[3]*index[3]*s[2].numerator)/d;
  s[3].denominator = (s[2].denominator*index[3]*index[3])/d;
  s[3].sumAcum+=(double)s[3].numerator/s[3].denominator;
/* for 4 */
for (index[4] = index[3]+1; index[4] < maxIndex[4]+1; ++index[4]) {
  if (id[index[4]] == 0) {
    continue;
  } else if (!boolTest(1.0/GOAL, s[3].sumAcum, 5, nForMax, index[4])) {
    break;
  }
  /* downsizing and update */
  d = gcd(s[3].denominator+index[4]*index[4]*s[3].numerator, s[3].denominator*index[4]*index[4]);
  s[4].numerator = (s[3].denominator+index[4]*index[4]*s[3].numerator)/d;
  s[4].denominator = (s[3].denominator*index[4]*index[4])/d;
  s[4].sumAcum+=(double)s[4].numerator/s[4].denominator;
/* for 5 */
for (index[5] = index[4]+1; index[5] < maxIndex[5]+1; ++index[5]) {
  if (id[index[5]] == 0) {
    continue;
  } else if (boolTest(1.0/GOAL, s[4].sumAcum, 6, nForMax, index[5])==0) {
    break;
  }
  /* downsizing and update */
  d = gcd(s[4].denominator+index[5]*index[5]*s[4].numerator, s[4].denominator*index[5]*index[5]);
  s[5].numerator = (s[4].denominator+index[5]*index[5]*s[4].numerator)/d;
  s[5].denominator = (s[4].denominator*index[5]*index[5])/d;
  s[5].sumAcum+=(double)s[5].numerator/s[5].denominator;
  /* res calc */
  if (s[5].numerator*2 == s[5].denominator) {
    ++count;
    printAnswer(index, 6, count);
    continue;
  } else if (s[5].numerator*2 > s[5].denominator) {
    continue;
  } else if (s[5].denominator > MAXNUM) {
    continue;
  }
  /* for 6 */
  for (index[6] = index[5]+1; index[6] < maxIndex[6]+1; ++index[6]) {
    if (id[index[6]] == 0) {
      continue;
    } else if (!boolTest(1.0/GOAL, s[5].sumAcum, 7, nForMax, index[6])) {
      break;
    }
    /* downsizing and update */
    d = gcd(s[5].denominator+index[6]*index[6]*s[5].numerator, s[5].denominator*index[6]*index[6]);
    s[6].numerator = (s[5].denominator+index[6]*index[6]*s[5].numerator)/d;
    s[6].denominator = (s[5].denominator*index[6]*index[6])/d;
    s[6].sumAcum+=(double)s[6].numerator/s[6].denominator;
    /* res calc */
    if (s[6].numerator*2 == s[6].denominator) {
      ++count;
      printAnswer(index, 7, count);
      continue;
    } else if (s[6].numerator*2 > s[6].denominator) {
      continue;
    } else if (s[6].denominator > MAXNUM) {
      continue;
    }
  /* for 7 */
  for (index[7] = index[6]+1; index[7] < maxIndex[7]+1; ++index[7]) {
    if (id[index[7]] == 0) {
      continue;
    } else if (!boolTest(1.0/GOAL, s[6].sumAcum, 8, nForMax, index[7])) {
      break;
    }
    /* downsizing and update */
    d = gcd(s[6].denominator+index[7]*index[7]*s[6].numerator, s[6].denominator*index[7]*index[7]);
    s[7].numerator = (s[6].denominator+index[7]*index[7]*s[6].numerator)/d;
    s[7].denominator = (s[6].denominator*index[7]*index[7])/d;
    s[7].sumAcum+=(double)s[7].numerator/s[7].denominator;
    /* res calc */
    if (s[7].numerator*2 == s[7].denominator) {
      ++count;
      printAnswer(index, 8, count);
      continue;
    } else if (s[7].numerator*2 > s[7].denominator) {
      continue;
    } else if (s[7].denominator > MAXNUM) {
      continue;
    }
  /* for 8 */
  for (index[8] = index[7]+1; index[8] < maxIndex[8]+1; ++index[8]) {
    if (id[index[8]] == 0) {
      continue;
    } else if (!boolTest(1.0/GOAL, s[7].sumAcum, 9, nForMax, index[8])) {
      break;
    }
    /* downsizing and update */
    d = gcd(s[7].denominator+index[8]*index[8]*s[7].numerator, s[7].denominator*index[8]*index[8]);
    s[8].numerator = (s[7].denominator+index[8]*index[8]*s[7].numerator)/d;
    s[8].denominator = (s[7].denominator*index[8]*index[8])/d;
    s[8].sumAcum+=(double)s[8].numerator/s[8].denominator;
    /* res calc */
    if (s[8].numerator*2 == s[8].denominator) {
      ++count;
      printAnswer(index, 9, count);
      continue;
    } else if (s[8].numerator*2 > s[8].denominator) {
      continue;
    } else if (s[8].denominator > MAXNUM) {
      continue;
    }
    /* for 9 */
    for (index[9] = index[8]+1; index[9] < maxIndex[9]+1; ++index[9]) {
      if (id[index[9]] == 0) {
        continue;
      } else if (!boolTest(1.0/GOAL, s[8].sumAcum, 10, nForMax, index[9])) {
        break;
      }
      /* downsizing and update */
      d = gcd(s[8].denominator+index[9]*index[9]*s[8].numerator, s[8].denominator*index[9]*index[9]);
      s[9].numerator = (s[8].denominator+index[9]*index[9]*s[8].numerator)/d;
      s[9].denominator = (s[8].denominator*index[9]*index[9])/d;
      s[9].sumAcum+=(double)s[9].numerator/s[9].denominator;
      /* res calc */
      if (s[9].numerator*2 == s[9].denominator) {
        ++count;
        printAnswer(index, 10, count);
        continue;
      } else if (s[9].numerator*2 > s[9].denominator) {
        continue;
      } else if (s[9].denominator > MAXNUM) {
        continue;
      }
    /* for 10 */
    for (index[10] = index[9]+1; index[10] < maxIndex[10]+1; ++index[10]) {
      if (id[index[10]] == 0) {
        continue;
      } else if (!boolTest(1.0/GOAL, s[9].sumAcum, 11, nForMax, index[10])) {
        break;
      }
      /* downsizing and update */
      d = gcd(s[9].denominator+index[10]*index[10]*s[9].numerator, s[9].denominator*index[10]*index[10]);
      s[10].numerator = (s[9].denominator+index[10]*index[10]*s[9].numerator)/d;
      s[10].denominator = (s[9].denominator*index[10]*index[10])/d;
      s[10].sumAcum+=(double)s[10].numerator/s[10].denominator;
      /* res calc */
      if (s[10].numerator*2 == s[10].denominator) {
        ++count;
        printAnswer(index, 11, count);
        continue;
      } else if (s[10].numerator*2 > s[10].denominator) {
        continue;
      } else if (s[10].denominator > MAXNUM) {
        continue;
      }
    /* for 11 */
    for (index[11] = index[10]+1; index[11] < maxIndex[11]+1; ++index[11]) {
      if (id[index[11]] == 0) {
        continue;
      } else if (!boolTest(1.0/GOAL, s[10].sumAcum, 12, nForMax, index[11])) {
        break;
      }
      /* downsizing and update */
      d = gcd(s[10].denominator+index[11]*index[11]*s[10].numerator, s[10].denominator*index[11]*index[11]);
      s[11].numerator = (s[10].denominator+index[11]*index[11]*s[10].numerator)/d;
      s[11].denominator = (s[10].denominator*index[11]*index[11])/d;
      s[11].sumAcum+=(double)s[11].numerator/s[11].denominator;
      /* res calc */
      if (s[11].numerator*2 == s[11].denominator) {
        ++count;
        printAnswer(index, 12, count);
        continue;
      } else if (s[11].numerator*2 > s[11].denominator) {
        continue;
      } else if (s[11].denominator > MAXNUM) {
        continue;
      }
    /* for 12 */
    for (index[12] = index[11]+1; index[12] < maxIndex[12]+1; ++index[12]) {
      if (id[index[12]] == 0) {
        continue;
      } else if (!boolTest(1.0/GOAL, s[11].sumAcum, 13, nForMax, index[12])) {
        break;
      }
      /* downsizing and update */
      d = gcd(s[11].denominator+index[12]*index[12]*s[11].numerator, s[11].denominator*index[12]*index[12]);
      s[12].numerator = (s[11].denominator+index[12]*index[12]*s[11].numerator)/d;
      s[12].denominator = (s[11].denominator*index[12]*index[12])/d;
      s[12].sumAcum+=(double)s[12].numerator/s[12].denominator;
      if (s[12].numerator*2 == s[12].denominator) {
        ++count;
        printAnswer(index, 13, count);
        continue;
      } else if (s[12].numerator*2 > s[12].denominator) {
        continue;
      } else if (s[12].denominator > MAXNUM) {
        continue;
      }
      /* for 13 */
      for (index[13] = index[12]+1; index[13] < maxIndex[13]+1; ++index[13]) {
        if (id[index[13]] == 0) {
          continue;
        } else if (!boolTest(1.0/GOAL, s[12].sumAcum, 14, nForMax, index[13])) {
          break;
        }
        /* downsizing and update */
        d = gcd(s[12].denominator+index[13]*index[13]*s[12].numerator, s[12].denominator*index[13]*index[13]);
        s[13].numerator = (s[12].denominator+index[13]*index[13]*s[12].numerator)/d;
        s[13].denominator = (s[12].denominator*index[13]*index[13])/d;
        s[13].sumAcum+=(double)s[13].numerator/s[13].denominator;
        if (s[13].numerator*2 == s[13].denominator) {
          ++count;
          printAnswer(index, 14, count);
          continue;
        } else if (s[13].numerator*2 > s[13].denominator) {
          continue;
        } else if (s[13].denominator > MAXNUM) {
          continue;
        }
        /* for 14 */
        for (index[14] = index[13]+1; index[14] < maxIndex[14]+1; ++index[14]) {
          if (id[index[14]] == 0) {
            continue;
          } else if (!boolTest(1.0/GOAL, s[13].sumAcum, 15, nForMax, index[14])) {
            break;
          }
          /* downsizing and update */
          d = gcd(s[13].denominator+index[14]*index[14]*s[13].numerator, s[13].denominator*index[14]*index[14]);
          s[14].numerator = (s[13].denominator+index[14]*index[14]*s[13].numerator)/d;
          s[14].denominator = (s[13].denominator*index[14]*index[14])/d;
          s[14].sumAcum+=(double)s[14].numerator/s[14].denominator;
          if (s[14].numerator*2 == s[14].denominator) {
            ++count;
            printAnswer(index, 15, count);
            continue;
          } else if (s[14].numerator*2 > s[14].denominator) {
            continue;
          } else if (s[14].denominator > MAXNUM) {
            continue;
          }
          /* for 15 */
          for (index[15] = index[14]+1; index[15] < maxIndex[15]+1; ++index[15]) {
            if (id[index[15]] == 0) {
              continue;
            } else if (!boolTest(1.0/GOAL, s[14].sumAcum, 16, nForMax, index[15])) {
              break;
            }
            /* downsizing and update */
            d = gcd(s[14].denominator+index[15]*index[15]*s[14].numerator, s[14].denominator*index[15]*index[15]);
            s[15].numerator = (s[14].denominator+index[15]*index[15]*s[14].numerator)/d;
            s[15].denominator = (s[14].denominator*index[15]*index[15])/d;
            s[15].sumAcum+=(double)s[15].numerator/s[15].denominator;
            if (s[15].numerator*2 == s[15].denominator) {
              ++count;
              printAnswer(index, 16, count);
              continue;
            } else if (s[15].numerator*2 > s[15].denominator) {
              continue;
            } else if (s[15].denominator > MAXNUM) {
              continue;
            }
            /* for 16 */
            for (index[16] = index[15]+1; index[16] < maxIndex[16]+1; ++index[16]) {
              if (id[index[16]] == 0) {
                continue;
              } else if (!boolTest(1.0/GOAL, s[15].sumAcum, 17, nForMax, index[16])) {
                break;
              }
              /* downsizing and update */
              d = gcd(s[15].denominator+index[16]*index[16]*s[15].numerator, s[15].denominator*index[16]*index[16]);
              s[16].numerator = (s[15].denominator+index[16]*index[16]*s[15].numerator)/d;
              s[16].denominator = (s[15].denominator*index[16]*index[16])/d;
              s[16].sumAcum+=(double)s[16].numerator/s[16].denominator;
              if (s[16].numerator*2 == s[16].denominator) {
                ++count;
                printAnswer(index, 17, count);
                continue;
              } else if (s[16].numerator*2 > s[16].denominator) {
                continue;
              } else if (s[16].denominator > MAXNUM) {
                continue;
              }
              /* for 17 */
              for (index[17] = index[16]+1; index[17] < maxIndex[17]+1; ++index[17]) {
                if (id[index[17]] == 0) {
                  continue;
                } else if (!boolTest(1.0/GOAL, s[16].sumAcum, 18, nForMax, index[17])) {
                  break;
                }
                /* downsizing and update */
                d = gcd(s[16].denominator+index[17]*index[17]*s[16].numerator, s[16].denominator*index[17]*index[17]);
                s[17].numerator = (s[16].denominator+index[17]*index[17]*s[16].numerator)/d;
                s[17].denominator = (s[16].denominator*index[17]*index[17])/d;
                s[17].sumAcum+=(double)s[17].numerator/s[17].denominator;
                if (s[17].numerator*2 == s[17].denominator) {
                  ++count;
                  printAnswer(index, 18, count);
                  continue;
                } else if (s[17].numerator*2 > s[17].denominator) {
                  continue;
                } else if (s[17].denominator > MAXNUM) {
                  continue;
                }
                /* for 18 */
                for (index[18] = index[17]+1; index[18] < maxIndex[18]+1; ++index[18]) {
                  if (id[index[18]] == 0) {
                    continue;
                  } else if (!boolTest(1.0/GOAL, s[17].sumAcum, 19, nForMax, index[18])) {
                    break;
                  }
                  /* downsizing and update */
                  d = gcd(s[17].denominator+index[18]*index[18]*s[17].numerator, s[17].denominator*index[18]*index[18]);
                  s[18].numerator = (s[17].denominator+index[18]*index[18]*s[17].numerator)/d;
                  s[18].denominator = (s[17].denominator*index[18]*index[18])/d;
                  s[18].sumAcum+=(double)s[18].numerator/s[18].denominator;
                  if (s[18].numerator*2 == s[18].denominator) {
                    ++count;
                    printAnswer(index, 19, count);
                    continue;
                  } else if (s[18].numerator*2 > s[18].denominator) {
                    continue;
                  } else if (s[18].denominator > MAXNUM) {
                    continue;
                  }
                  /* for 19 */
                  for (index[19] = index[18]+1; index[19] < maxIndex[19]+1; ++index[19]) {
                    if (id[index[19]] == 0) {
                      continue;
                    } else if (!boolTest(1.0/GOAL, s[18].sumAcum, 20, nForMax, index[19])) {
                      break;
                    }
                    /* downsizing and update */
                    d = gcd(s[18].denominator+index[19]*index[19]*s[18].numerator, s[18].denominator*index[19]*index[19]);
                    s[19].numerator = (s[18].denominator+index[19]*index[19]*s[18].numerator)/d;
                    s[19].denominator = (s[18].denominator*index[19]*index[19])/d;
                    s[19].sumAcum+=(double)s[19].numerator/s[19].denominator;
                    if (s[19].numerator*2 == s[19].denominator) {
                      ++count;
                      printAnswer(index, 20, count);
                      continue;
                    } else if (s[19].numerator*2 > s[19].denominator) {
                      continue;
                    } else if (s[19].denominator > MAXNUM) {
                      continue;
                    }
                    /* for 20 */
                    for (index[20] = index[19]+1; index[20] < maxIndex[20]+1; ++index[20]) {
                      if (id[index[20]] == 0) {
                        continue;
                      } else if (!boolTest(1.0/GOAL, s[19].sumAcum, 21, nForMax, index[20])) {
                        break;
                      }
                      /* downsizing and update */
                      d = gcd(s[19].denominator+index[20]*index[20]*s[19].numerator, s[19].denominator*index[20]*index[20]);
                      s[20].numerator = (s[19].denominator+index[20]*index[20]*s[19].numerator)/d;
                      s[20].denominator = (s[19].denominator*index[20]*index[20])/d;
                      s[20].sumAcum+=(double)s[20].numerator/s[20].denominator;
                      if (s[20].numerator*2 == s[20].denominator) {
                        ++count;
                        printAnswer(index, 21, count);
                        continue;
                      } else if (s[20].numerator*2 > s[20].denominator) {
                        continue;
                      } else if (s[20].denominator > MAXNUM) {
                        continue;
                      }
                    /* for 21 */
                    for (index[21] = index[20]+1; index[21] < maxIndex[21]+1; ++index[21]) {
                      if (id[index[21]] == 0) {
                        continue;
                      } else if (!boolTest(1.0/GOAL, s[20].sumAcum, 22, nForMax, index[21])) {
                        break;
                      }
                      /* downsizing and update */
                      d = gcd(s[20].denominator+index[21]*index[21]*s[20].numerator, s[20].denominator*index[21]*index[21]);
                      s[21].numerator = (s[20].denominator+index[21]*index[21]*s[20].numerator)/d;
                      s[21].denominator = (s[20].denominator*index[21]*index[21])/d;
                      s[21].sumAcum+=(double)s[21].numerator/s[21].denominator;
                      if (s[21].numerator*2 == s[21].denominator) {
                        ++count;
                        printAnswer(index, 22, count);
                        continue;
                      } else if (s[21].numerator*2 > s[21].denominator) {
                        continue;
                      } else if (s[21].denominator > MAXNUM) {
                        continue;
                      }
                    /* for 22 */
                    for (index[22] = index[21]+1; index[22] < maxIndex[22]+1; ++index[22]) {
                      if (id[index[22]] == 0) {
                        continue;
                      } else if (!boolTest(1.0/GOAL, s[21].sumAcum, 23, nForMax, index[22])) {
                        break;
                      }
                      /* downsizing and update */
                      d = gcd(s[21].denominator+index[22]*index[22]*s[21].numerator, s[21].denominator*index[22]*index[22]);
                      s[22].numerator = (s[21].denominator+index[22]*index[22]*s[21].numerator)/d;
                      s[22].denominator = (s[21].denominator*index[22]*index[22])/d;
                      s[22].sumAcum+=(double)s[22].numerator/s[22].denominator;
                      if (s[22].numerator*2 == s[22].denominator) {
                        ++count;
                        printAnswer(index, 23, count);
                        continue;
                      } else if (s[22].numerator*2 > s[22].denominator) {
                        continue;
                      } else if (s[22].denominator > MAXNUM) {
                        continue;
                      }
                    /* for 23 */
                    for (index[23] = index[22]+1; index[23] < maxIndex[23]+1; ++index[23]) {
                      if (id[index[23]] == 0) {
                        continue;
                      } else if (!boolTest(1.0/GOAL, s[22].sumAcum, 24, nForMax, index[23])) {
                        break;
                      }
                      /* downsizing and update */
                      d = gcd(s[22].denominator+index[23]*index[23]*s[22].numerator, s[22].denominator*index[23]*index[23]);
                      s[23].numerator = (s[22].denominator+index[23]*index[23]*s[22].numerator)/d;
                      s[23].denominator = (s[22].denominator*index[23]*index[23])/d;
                      s[23].sumAcum+=(double)s[23].numerator/s[23].denominator;
                      if (s[23].numerator*2 == s[23].denominator) {
                        ++count;
                        printAnswer(index, 24, count);
                        continue;
                      } else if (s[23].numerator*2 > s[23].denominator) {
                        continue;
                      } else if (s[23].denominator > MAXNUM) {
                        continue;
                      }
}}}}}}}}}}}}}}}}}}}}}}}}
/* free memory */
free(index);
free(s);
free(id);
/* return the result */
return count;
}
/******************************************************************************/
int primeTest (int nTest) {
/* this function verifies if a number nTest is a prime number, returns 1 if
prime or 0 if not, it return -1 if there was a problem in the function */
int i, comparador;
if (nTest <= 1) {
	return 0;
}
if (nTest  == 2) {
	return 1;
} else if (nTest % 2 == 0) {
	return 0;
}
for (i = 3; i < sqrt(nTest+1); i = i+2) {
	if (nTest % i == 0) {
		return 0;
	}
}
/* if it reaches here, then it is a prime number */
return 1;
}
/******************************************************************************/
int boolTest(double goal, double sumAcum, int actualIndex, int nForMax, int testIndex) {
/* this function returns 1 if (goal-sumAcum) <= (nForMax-actualIndex)/testIndex²
or 0 if not */
double right = goal-sumAcum, left;
left = ((double)nForMax-actualIndex)/(testIndex*testIndex);
if (left >= right) {
  return 1;
} else {
  return 0;
}
}
/******************************************************************************/
