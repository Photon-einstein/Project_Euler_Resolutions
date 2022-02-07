#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define NTURNS 15

/* this function makes the calculation of the answer for a given nTurns and
a given nRed, and then return the value or -1 if there was a problem in the
function */
long long int nWaysCalc (int nTurns, int nRed);

int main () {
clock_t beginning, end;
double tempo;
beginning = clock();
/* work to verify */
int nTurns = NTURNS, nRed, nRedMax;
long long int boolean, numerator = 0, d, denominator = 1, answer;
/* nRedMax calc */
if (nTurns % 2 == 0) {
  nRedMax = nTurns/2-1;
} else {
  nRedMax = nTurns/2;
}
/* cycle calc */
for (d = 2; d < nTurns+2; d++) {
  denominator*=d;
}
for (nRed = 0; nRed < nRedMax+1; nRed++) {
  boolean = nWaysCalc (nTurns, nRed);
  if (boolean == -1) {
    printf("\nThere was an error in the function nWaysCalc.");
    return 0;
  }
  /* answer update */
  numerator+=boolean;
}
/* answer  final tune up */
answer = denominator/numerator;
/* end of the work */
end = clock();
tempo = (double)(end - beginning) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThe max prize using %d turns is %lld pounds.", nTurns, answer);
printf ("\n");
return 0;
}
/******************************************************************************/
long long int nWaysCalc (int nTurns, int nRed) {
/* this function makes the calculation of the answer for a given nTurns and
a given nRed, and then return the value or -1 if there was a problem in the
function */
if (nTurns < 1 || nRed < 0 || nRed > nTurns){
  return -1;
}
int i[nTurns];
long long int res = 0;
/* res calc */
if (nRed == 0) {
  /* nRed = 0 */
  return 1;
} else if (nRed == 1) {
  /* nRed = 1 */
  for (i[0] = 1; i[0] < nTurns+1; i[0]++) {
    res+=i[0];
  }
  return res;
} else if (nRed == 2) {
  /* nRed = 2 */
  for (i[0] = 1; i[0] < nTurns; i[0]++) {
    for (i[1] = i[0]+1; i[1] < nTurns+1; i[1]++) {
      res+=i[0]*i[1];
    }
  }
  return res;
} else if (nRed == 3) {
  /* nRed = 3 */
  for (i[0] = 1; i[0] < nTurns-1; i[0]++) {
    for (i[1] = i[0]+1; i[1] < nTurns; i[1]++) {
      for (i[2] = i[1]+1; i[2] < nTurns+1; i[2]++) {
        res+=i[0]*i[1]*i[2];
      }
    }
  }
  return res;
} else if (nRed == 4) {
  /* nRed = 4 */
  for (i[0] = 1; i[0] < nTurns-2; i[0]++) {
    for (i[1] = i[0]+1; i[1] < nTurns-1; i[1]++) {
      for (i[2] = i[1]+1; i[2] < nTurns; i[2]++) {
        for (i[3] = i[2]+1; i[3] < nTurns+1; i[3]++) {
          res+=i[0]*i[1]*i[2]*i[3];
        }
      }
    }
  }
  return res;
} else if (nRed == 5) {
  /* nRed = 5 */
  for (i[0] = 1; i[0] < nTurns-3; i[0]++) {
    for (i[1] = i[0]+1; i[1] < nTurns-2; i[1]++) {
      for (i[2] = i[1]+1; i[2] < nTurns-1; i[2]++) {
        for (i[3] = i[2]+1; i[3] < nTurns; i[3]++) {
          for (i[4] = i[3]+1; i[4] < nTurns+1; i[4]++) {
            res+=i[0]*i[1]*i[2]*i[3]*i[4];
          }
        }
      }
    }
  }
  return res;
} else if (nRed == 6) {
  /* nRed = 6 */
  for (i[0] = 1; i[0] < nTurns-4; i[0]++) {
    for (i[1] = i[0]+1; i[1] < nTurns-3; i[1]++) {
      for (i[2] = i[1]+1; i[2] < nTurns-2; i[2]++) {
        for (i[3] = i[2]+1; i[3] < nTurns-1; i[3]++) {
          for (i[4] = i[3]+1; i[4] < nTurns; i[4]++) {
            for (i[5] = i[4]+1; i[5] < nTurns+1; i[5]++) {
              res+=i[0]*i[1]*i[2]*i[3]*i[4]*i[5];
            }
          }
        }
      }
    }
  }
  return res;
} else if (nRed == 7) {
  /* nRed = 7 */
  for (i[0] = 1; i[0] < nTurns-5; i[0]++) {
    for (i[1] = i[0]+1; i[1] < nTurns-4; i[1]++) {
      for (i[2] = i[1]+1; i[2] < nTurns-3; i[2]++) {
        for (i[3] = i[2]+1; i[3] < nTurns-2; i[3]++) {
          for (i[4] = i[3]+1; i[4] < nTurns-1; i[4]++) {
            for (i[5] = i[4]+1; i[5] < nTurns; i[5]++) {
              for (i[6] = i[5]+1; i[6] < nTurns+1; i[6]++) {
                res+=i[0]*i[1]*i[2]*i[3]*i[4]*i[5]*i[6];
              }
            }
          }
        }
      }
    }
  }
  return res;
}
}
/******************************************************************************/
