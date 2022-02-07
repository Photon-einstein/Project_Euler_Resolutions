#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include "tabdispersao.h"
#define GOAL 18
typedef struct {
  int num;
  int den;
} capID;

/* this function makes the calculation of the gcd between a and b */
int gcd (int a, int b);

/* this function makes the calculation of the number of different values up to
goal capacitors and in the end returns the result or -1 if there was a problem
with the function */
int resCalc (int goal);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int res=0, goal = GOAL;
res = resCalc(goal);
if (res == -1) {
  printf("\nThere was a problem in the function.");
  return 0;
}
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nThe number of different values up to %d capacitors is %d.", goal, res);
printf("\n");
return 0;
}
/******************************************************************************/
int resCalc (int goal) {
/* this function makes the calculation of the number of different values up to
goal capacitors and in the end returns the result or -1 if there was a problem
with the function */
if (goal < 0) {
  return -1;
}
int *sizeLevels, res=0, i, boolean, j, k, mult, maxSizeLevel=2000000, d, n;
tabela_dispersao *td;
char v[200];
capID **c, test;
/* memory allocation */
sizeLevels = (int*) calloc(goal, sizeof (int));
if (sizeLevels == NULL) {
  return -1;
}
td = tabela_nova(50000000, hash_djbm);
if (td == NULL) {
  return -1;
}
c = (capID**)calloc(goal, sizeof(capID*));
if (c == NULL) {
  return -1;
}
/* first value insert */
c[0]=(capID*)calloc(1, sizeof (capID));
if (c[0] == NULL) {
  return -1;
}
c[0][0].num = 60;
c[0][0].den = 1;
sprintf(v, "%d/%d", c[0][0].num, c[0][0].den);
boolean = tabela_insere(td, v, "");
if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
  printf("\nThere was an error in the function tabela_insere.");
  return -1;
}
++res;
sizeLevels[0]=1;
/* second level insert */
c[1]=(capID*)calloc(2, sizeof (capID));
if (c[1] == NULL) {
  return -1;
}
c[1][0].num = 30;
c[1][0].den = 1;
sprintf(v, "%d/%d", c[1][0].num, c[1][0].den);
boolean = tabela_insere(td, v, "");
if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
  printf("\nThere was an error in the function tabela_insere.");
  return -1;
}
c[1][1].num = 120;
c[1][1].den = 1;
sprintf(v, "%d/%d", c[1][1].num, c[1][1].den);
boolean = tabela_insere(td, v, "");
if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
  printf("\nThere was an error in the function tabela_insere.");
  return -1;
}
res+=2;
sizeLevels[1]=2;
for (n = 2, mult=1; n < goal; ++n) {
  /* memory allocation of the actual n level */
  c[n]=(capID*)calloc(maxSizeLevel, sizeof (capID));
  if (c[n] == NULL) {
    return -1;
  }
  for (i = 0; i < n; ++i) {
    for (j = 0; j < sizeLevels[i]; ++j) {
      for (k = 0; k < sizeLevels[n-i-1]; ++k) {
        /* test paralel capacitors */
        test.num = c[i][j].num*c[n-i-1][k].den+c[n-i-1][k].num*c[i][j].den;
        test.den = c[i][j].den*c[n-i-1][k].den;
        //printf("\nnum = %d||den = %d", test.num, test.den);
        fflush(NULL);
        d = gcd(test.num, test.den);
        test.num/=d;
        test.den/=d;
        sprintf(v, "%d/%d", test.num, test.den);
        boolean = tabela_existe(td, v);
        if (boolean == TABDISPERSAO_INVALIDA) {
          return -1;
        } else if (boolean == TABDISPERSAO_NAOEXISTE) {
          /* insertion */
          //printf("\n%s", v);
          ++res;
          if (sizeLevels[n] == maxSizeLevel*mult) {
            ++mult;
            maxSizeLevel*=mult;
            c[n] = (capID*) realloc(c[n], maxSizeLevel*sizeof(capID));
            if (c[n] == NULL) {
              printf("\nThere was an error in the memory reallocation of c[n].");
              return -1;
            }
          }
          c[n][sizeLevels[n]].num = test.num;
          c[n][sizeLevels[n]].den = test.den;
          boolean = tabela_insere(td, v, "");
          if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
            printf("\nThere was an error in the function tabela_insere.");
            return -1;
          }
          /* size update */
          ++sizeLevels[n];
        }
        /* test series capacitors */
        test.num = c[i][j].num*c[n-i-1][k].num;
        test.den = c[i][j].num*c[n-i-1][k].den+c[n-i-1][k].num*c[i][j].den;
        d = gcd(test.num, test.den);
        test.num/=d;
        test.den/=d;
        //printf("\nnum = %d||den = %d", test.num, test.den);
        fflush(NULL);
        sprintf(v, "%d/%d", test.num, test.den);
        boolean = tabela_existe(td, v);
        if (boolean == TABDISPERSAO_INVALIDA) {
          return -1;
        } else if (boolean == TABDISPERSAO_NAOEXISTE) {
          /* insertion */
          //printf("\n%s", v);
          ++res;
          if (sizeLevels[n] == maxSizeLevel*mult) {
            ++mult;
            maxSizeLevel*=mult;
            c[n] = (capID*) realloc(c[n], maxSizeLevel*sizeof(capID));
            if (c[n] == NULL) {
              printf("\nThere was an error in the memory reallocation of c[n].");
              return -1;
            }
          }
          c[n][sizeLevels[n]].num = test.num;
          c[n][sizeLevels[n]].den = test.den;
          boolean = tabela_insere(td, v, "");
          if (boolean == TABDISPERSAO_ERRO || boolean == TABDISPERSAO_INVALIDA) {
            printf("\nThere was an error in the function tabela_insere.");
            return -1;
          }
          /* size update */
          ++sizeLevels[n];
        }
      }
    }
  }
  /* realloc of the memory */
  c[n] = (capID*) realloc (c[n], sizeLevels[n]*sizeof(capID));
  if (c[n] == NULL) {
    printf("\nThere was an error in the reallocation of c[n].");
    return -1;
  }
}
/* free memory */
free(sizeLevels);
tabela_apaga(td);
for (i = 0; i < goal; ++i) {
  free(c[i]);
}
free(c);
/* return the result */
return res;
}
/******************************************************************************/
int gcd (int a, int b) {
/* this function makes the calculation of the gcd between a and b */
int q, r;
while (b > 0) {
	q = a / b;
	r = a - q * b;
	a = b;
	b = r;
}
return a;
}
/******************************************************************************/
