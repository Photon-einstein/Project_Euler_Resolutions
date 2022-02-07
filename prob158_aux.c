#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include "tabdispersao.h"
#define SIZEALPHA 26
typedef struct {
  char *sol;
} solId;

/* this function makes the generation of the all the possible solution of size
2, and stores the solution in a 2D matrix of size res_step, in the end it
returns the size of the matrix in res_step by reference and the pointer of the
dynamic matrix or null if there was a problem in the function */
solId* calcBaseSol(int n, int nMax, int *res_step);

/* this function makes the generation of a 2D matrix with the new solutions
base on the old solutions stored in sol_n_base, and in the end it returns the
pointer with the dynamic memory allocation and the size by reference or null
if there was a problem in the function */
solId* calcSol(int n, int nMax, solId* sol_n_base, int res_base, int *res_new);

/* this function returns the char that are left to processe in the next step,
in the amount sizeRes, from the bulk sizeAlpha, that are complementar of the
sol solution, the result is dynamically allocated if sucess, or null if there
was a problem in the function */
char* charLeftCalc(char *sol, int sizeSol, int sizeRes, int sizeAlpha);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
solId *sol_n_base, *sol;
int n = 2, nMax = SIZEALPHA, res_base, i, res_new, res_max=0;
FILE *f;
f = fopen("sol_size3.txt", "w+");
if (f == NULL) {
  printf("\nError in opening the file.");
  return 0;
}
/* creation of the base sol_n_base */
for (n = 2; n < nMax+1; ++n) {
  if (n == 2) {
    /* creation of the base solutions */
    sol_n_base = calcBaseSol(n, nMax, &res_base);
    if (sol_n_base == NULL) {
      printf("\nThere was a problem in the function calcBaseSol.");
      return 0;
    }
    res_max = res_base;
    printf("\np(2) = %d", res_base);
    fflush(NULL);
    continue;
  } else {
    /* if it reaches here then we have not a base solution */
    sol = calcSol(n, nMax, sol_n_base, res_base, &res_new);
    if (sol == NULL) {
      printf("\nThere was a problem in the function calcSol.");
      return 0;
    }
    if (n == 3) {
      for (i = 0; i < res_new; ++i) {
        fprintf(f, "%s\n", sol[i].sol);
      }
    }
    free(sol_n_base);
    sol_n_base = NULL;
  }
  /* switch pointers */
  sol_n_base = sol;
  /* counter update */
  res_base = res_new;
  /* max update */
  if (res_max < res_new) {
    res_max = res_new;
  }
  printf("\np(%d) = %d", n, res_new);
  fflush(NULL);
  if (n == 3) {
    break;
  }
}
fclose(f);
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nThe maximum value of p(n) is %d.", res_max);
printf("\n");
return 0;
}
/******************************************************************************/
solId* calcBaseSol(int n, int nMax, int *res_step) {
/* this function makes the generation of the all the possible solution of size
2, and stores the solution in a 2D matrix of size res_step, in the end it
returns the size of the matrix in res_step by reference and the pointer of the
dynamic matrix or null if there was a problem in the function */
if (res_step == NULL) {
  return NULL;
}
solId *v;
char index[3]={0};
int sizeMax=10000, mult=1, size=0, i;
/* memory allocation */
v = (solId*) calloc(sizeMax, sizeof (solId));
if (v == NULL) {
  return NULL;
}
/* matrix fulling */
for (index[0] = 'a'; index[0] <= 'y'; ++index[0]) {
  for (index[1] = index[0]+1; index[1] <= 'z'; ++index[1]) {
    v[size].sol = strdup(index);
    if (v[size].sol == NULL) {
      return NULL;
    }
    ++size;
    if (size == sizeMax) {
      ++mult;
      sizeMax*=mult;
      v = (solId*)realloc(v, sizeMax*sizeof(solId));
      if (v == NULL) {
        printf("\nThere was an error in the reallocation of memory.");
        return NULL;
      }
    }
  }
}
/* final size reallocation */
v = (solId*)realloc(v, size*sizeof(solId));
if (v == NULL) {
  printf("\nThere was an error in the reallocation of memory.");
  return NULL;
}
*res_step = size;
return v;
}
/******************************************************************************/
solId* calcSol(int n, int nMax, solId* sol_n_base, int res_base, int *res_new) {
/* this function makes the generation of a 2D matrix with the new solutions
base on the old solutions stored in sol_n_base, and in the end it returns the
pointer with the dynamic memory allocation and the size by reference or null
if there was a problem in the function */
if (sol_n_base == NULL || res_new == NULL) {
  return NULL;
}
int nCharLeft, i, j, newSol = 0, sizeMax = 1000000, mult=1, boolean, oldSize;
char *charLeft, *possible_new_sol, left_or_right_char[2];
solId *v;
tabela_dispersao *td;
nCharLeft = nMax-n+1;
left_or_right_char[1]='\0';
/* memory allocation */
possible_new_sol = (char*) calloc(n+1, sizeof(char));
if (possible_new_sol == NULL) {
  return NULL;
}
/* matrix 2D allocation */
v = (solId*) calloc(sizeMax, sizeof (solId));
if (v == NULL) {
  return NULL;
}
/* hash table allocation */
td = tabela_nova(sizeMax*10, hash_djbm);
if (td == NULL) {
  return NULL;
}
/* res_base processing */
for (i = 0; i < res_base; ++i) {
  /* charLeft calculation */
  charLeft = charLeftCalc(sol_n_base[i].sol, n-1, nCharLeft, nMax);
  if (charLeft == NULL) {
    printf("\nThere was a problem in the function charLeftCalc.");
    return NULL;
  }
  //printf("\nCharLeft = %s", charLeft);
  fflush(NULL);
  nCharLeft = strlen(charLeft);
  /* left insertion */
  for (j = 0; j < nCharLeft; ++j) {
    /* test if cTest > sol_n_base[0] */
    if (charLeft[j] <= sol_n_base[i].sol[0]) {
      continue;
    }
    left_or_right_char[0] = charLeft[j];
    /* if it reaches here then we have a possible valid word */
    strcpy(possible_new_sol, left_or_right_char);
    strcat(possible_new_sol, sol_n_base[i].sol);
    /* test if it is not a repeated solution */
    boolean = tabela_existe(td, possible_new_sol);
    if (boolean == TABDISPERSAO_NAOEXISTE) {
      boolean = tabela_insere(td, possible_new_sol, "");
      if (boolean == TABDISPERSAO_ERRO) {
        return NULL;
      }
    } else {
      continue;
    }
    /* insertion in the 2D matrix */
    if (newSol == sizeMax) {
      ++mult;
      sizeMax*=mult;
      v = (solId*)realloc(v, sizeMax*sizeof(solId));
      if (v == NULL) {
        printf("\nThere was an error in the reallocation of memory.");
        return NULL;
      }
    }
    v[newSol].sol = strdup(possible_new_sol);
    if (v[newSol].sol == NULL) {
      return NULL;
    }
    ++newSol;
    if (n == 7) {
      if (newSol % 1000000 == 0) {
        printf("\nnewSol = %d", newSol);
        fflush(NULL);
      }
    }
  }
  /* right insertion */
  for (j = 0; j < nCharLeft; ++j) {
    /* test if sol_n_base[size-1] <= charLeft[j] */
    if (sol_n_base[i].sol[strlen(sol_n_base[i].sol)-1] <= charLeft[j]) {
      continue;
    }
    left_or_right_char[0] = charLeft[j];
    /* if it reaches here then we have a possible valid word */
    strcpy(possible_new_sol, sol_n_base[i].sol);
    strcat(possible_new_sol, left_or_right_char);
    /* test if it is not a repeated solution */
    boolean = tabela_existe(td, possible_new_sol);
    if (boolean == TABDISPERSAO_NAOEXISTE) {
      boolean = tabela_insere(td, possible_new_sol, "");
      if (boolean == TABDISPERSAO_ERRO) {
        return NULL;
      }
    } else {
      continue;
    }
    /* insertion in the 2D matrix */
    if (newSol == sizeMax) {
      ++mult;
      sizeMax*=mult;
      v = (solId*)realloc(v, sizeMax*sizeof(solId));
      if (v == NULL) {
        printf("\nThere was an error in the reallocation of memory.");
        return NULL;
      }
    }
    v[newSol].sol = strdup(possible_new_sol);
    if (v[newSol].sol == NULL) {
      return NULL;
    }
    ++newSol;
    if (n == 7) {
      if (newSol % 1000000 == 0) {
        printf("\nnewSol = %d", newSol);
        fflush(NULL);
      }
    }
  }
  /* free base solution */
  free(sol_n_base[i].sol);
  if (n == 7) {
    if (newSol % 1000000 == 0) {
      printf("\nnewSol = %d", newSol);
      fflush(NULL);
    }
  }
}
/* free memory */
free(possible_new_sol);
free(charLeft);
tabela_apaga(td);
/* size update */
*res_new = newSol;
v = (solId*)realloc(v, newSol*sizeof(solId));
if (v == NULL) {
  printf("\nThere was an error in the reallocation of memory.");
  return NULL;
}
return v;
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
char *res, *bulk;
int i, j;
bulk = (char*) calloc(sizeAlpha+1, sizeof(char));
if (bulk == NULL) {
  return NULL;
}
res = (char*) calloc(sizeRes+1, sizeof(char));
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
  if (j > sizeRes) {
    return NULL;
  }
}
res[j]='\0';
/* free memory */
free(bulk);
return res;
}
/******************************************************************************/
