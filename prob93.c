#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXGENERATED 100
#define START 4
#define NNUMBERS 4
#define NOPERATORS 4
#define NBRACKETS NNUMBERS-1
#define MAX 100
#define MAXREP 25
typedef struct {
  int operation[3]; /* 1-"+", 2-"-", 3-"*", 4-"/" */
} operators;
typedef struct {
  int priority[3];
} brackets;
typedef struct {
  float numbers[4];
} nPermutation;

/* this function returns the number of the diferente permutations with repetition
of aA´b */
int permutationsCalc (int a, int b);

/* this function returns the number of the diferente permutations with no
repetition of aAb */
int permutationsCalcNoRepetition (int a, int b);

/* this functions retuns the number of n! */
int factorial (int n);

/* this function fills the vector v with the diferent permutations of the
4 operators, 3 each time, until dim be reach, and return 1 if all ok or zero if
there was a problem */
int fillOperatorVector (operators *v, int dim);

/* this function fills the vector v with the diferent permutations of the
dim diferent priority of the diferent brackets, until dim be reach, and return 1
if all ok or zero if there was a problem */
int fillBracketsVector (brackets *v, int dim);

/* this function fills the vector v with the diferent permutations of the
dim diferent priority of the diferent numbers, until dim be reach, and return 1
if all ok or zero if there was a problem */
int fillNumberVector (nPermutation *v, int dim, int *index, int nNumbers);

/* this function returns the numbers generated consecutively starting in 1, or
-1 if there was a problem */
int numberGeneratedCalc (nPermutation *numberV, int nNumbersPermutation, operators *op, int nOperationsOperator, brackets *priorityV, int nBracketsMember, int *memoryNGenerate, int sizeMemory);

/* this function returns 1 if all the numbers in the index are diferent or 0 if
at least one is equal */
int testRepetition (int *indices, int dim);

/* this function returns 1 if the float is a integer or 0 if is a float */
int intTest (float res);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* task to verify */
/* first I am going to generate the permutations of the signals */
operators *op;
int nOperationsOperator, nBrackets = NBRACKETS, booleano, nBracketsMember, numbers[4];
int maxNumber = 0, *memoryNGenerate, max, numberPermut, i, count = 0, exitF = 0, dim;
char answer[50], string[10];
brackets *priorityV;
nPermutation *numberV;

nOperationsOperator = permutationsCalc (NOPERATORS, 3);
printf ("\nI am now going to generate a vector of operators of %d with %dA´3 size.", nOperationsOperator, NOPERATORS);
op = (operators*) calloc (nOperationsOperator, sizeof (operators));
if (op == NULL) {
  printf ("\nThere was a erro in the generation of the vector op.");
  return 0;
}
booleano = fillOperatorVector (op, nOperationsOperator);
if (booleano == 0) {
  printf ("\nThere was a problem in the function fillOperatorVector.");
  return 0;
}
nBracketsMember = permutationsCalcNoRepetition  (NBRACKETS, NBRACKETS);
priorityV = (brackets*) calloc (nBracketsMember, sizeof (brackets));
if (priorityV == NULL) {
  printf ("\nThere was a error in the creation of the vector priorityV.");
  return 0;
}
booleano = fillBracketsVector (priorityV, nBracketsMember);
if (booleano == 0) {
  printf ("\nThere was a problem in the function fillOperatorVector.");
  return 0;
}

/* initial condition */
numbers[0] = START;
numberPermut = permutationsCalcNoRepetition  (NNUMBERS, NNUMBERS);
printf ("\nThere are %d permutations.", numberPermut);

while (numbers[0] < MAX) {
  for (numbers[1] = numbers[0]-1; numbers[1] > 2; numbers[1]--) {
    if (numbers[1] > 10) {
      break;
    }
    for (numbers[2] = numbers[1]-1; numbers[2] > 1; numbers[2]--) {
      if (numbers[2] > 8) {
        break;
      }
      for (numbers[3] = numbers[2]-1; numbers[3] > 0; numbers[3]--) {
        if (numbers[3] > 4) {
          break;
        }
        /* max number to be calculated */
        dim = MAXGENERATED;
        memoryNGenerate = (int*) calloc (dim, sizeof (int));
        if (memoryNGenerate == NULL) {
          printf ("\nThere was an error in the creation of the vector memoryNGenerate.");
          return 0;
        }
        numberV = (nPermutation*) calloc (numberPermut, sizeof (nPermutation));
        if (numberV == NULL) {
          printf ("\nThere was an error in the creation of the vector numberV.");
          return 0;
        }
        booleano = fillNumberVector (numberV, numberPermut, numbers, NNUMBERS);
        if (booleano == 0) {
          printf ("\nThere was an erro in the function fillNumberVector.");
          return 0;
        }
        max = numberGeneratedCalc (numberV, numberPermut, op, nOperationsOperator, priorityV, nBracketsMember, memoryNGenerate, dim);
        if (max == -1) {
          printf ("\nThere was a problem in the function numberGeneratedCalc.");
          return 0;
        }
        if (maxNumber < max) {
          maxNumber = max;
          sprintf(string,"%d", numbers[3]);
          strcpy(answer,string);
          printf ("\nNew combination found: ");
          printf ("%d ", numbers[3]);
          for (i = 2; i > -1; i--) {
            sprintf(string,"%d", numbers[i]);
            printf ("%d ", numbers[i]);
            strcat(answer,string);
          }
          printf ("whith %d combinations.", maxNumber);
        }
        free (numberV);
        free (memoryNGenerate);
      }
    }
  }
  numbers[0]++;
}
/* end of the task */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nUntil %d the max the string is %s.", MAX, answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int permutationsCalc (int a, int b) {
/* this function returns the number of the permutation of aPb */
int res;
res = pow (a,b);
return res;
}
/******************************************************************************/
int factorial (int n) {
/* this functions retuns the number of n! */
int res = 1;
if (n == 0 || n == 1) {
  return 1;
}
while (n > 1) {
  res*=n;
  n--;
}
return res;
}
/******************************************************************************/
int fillOperatorVector (operators *v, int dim) {
/* this function fills the vector v with the diferent permutations of the
4 operators, 3 each time, until dim be reach, and return 1 if all ok or zero if
there was a problem */
int index[3], max = 5, count = 0;
if (v == NULL || dim == 0) {
  return 0;
}
for (index[0] = 1; index[0] < max; index[0]++) {
  for (index[1] = 1; index[1] < max; index[1]++) {
    for (index[2] = 1; index[2] < max; index[2]++) {
        v[count].operation[0] = index[0];
        v[count].operation[1] = index[1];
        v[count].operation[2] = index[2];
        count++;
    }
  }
}
return 1;
}
/******************************************************************************/
int permutationsCalcNoRepetition (int a, int b) {
/* this function returns the number of the diferente permutations with no
repetition of aAb */
int numerator, denominator, res;
numerator = factorial (a);
denominator = factorial (a-b);
res = numerator / denominator;
return res;
}
/******************************************************************************/
int fillBracketsVector (brackets *v, int dim) {
/* this function fills the vector v with the diferent permutations of the
dim diferent priority of the diferent brackets, until dim be reach, and return 1
if all ok or zero if there was a problem */
if (v == NULL || dim == 0) {
  return 0;
}
int index[3] = {0}, count = 0, i;
for (index[0] = 0; index[0] < 3; index[0]++) {
  for (index[1] = 0; index[1] < 3; index[1]++) {
    for (index[2] = 0; index[2] < 3; index[2]++) {
      /* test if the diferent index are diferent */
      if (index[0] == index[1] || index[0] == index[2] || index[1] == index[2]) {
        continue;
      }
      /* if here then they are diferent */
      for (i = 0; i < 3; i++) {
        v[count].priority[i] = index[i];
      }
      count++;
    }
  }
}
return 1;
}
/******************************************************************************/
int fillNumberVector (nPermutation *v, int dim, int *index, int nNumbers) {
/* this function fills the vector v with the diferent permutations of the
dim diferent priority of the diferent numbers, until dim be reach, and return 1
if all ok or zero if there was a problem */
if (v == NULL || dim == 0 || index == NULL) {
  return 0;
}
int indices[4], count = 0, booleano, i;
for (indices[0] = 0; indices[0] < nNumbers; indices[0]++) {
  for (indices[1] = 0; indices[1] < nNumbers; indices[1]++) {
    for (indices[2] = 0; indices[2] < nNumbers; indices[2]++) {
      for (indices[3] = 0; indices[3] < nNumbers; indices[3]++) {
        if (count >= dim) {
          break;
        }
        booleano = testRepetition (indices, 4);
        if (booleano == 0) {
          continue;
        }
        for (i = 0; i < 4; i++) {
          v[count].numbers[i] = (float)index[indices[i]];
        }
        count++;
      }
    }
  }
}
return 1;
}
/******************************************************************************/
int numberGeneratedCalc (nPermutation *numberV, int nNumbersPermutation, operators *op, int nOperationsOperator, brackets *priorityV, int nBracketsMember, int *memoryNGenerate, int sizeMemory) {
/* this function returns the numbers generated consecutively starting in 1, or
-1 if there was a problem */
float res, res1, res2;
int index[3]={0}, number, booleano, count = 0, i;
int countExit = 0, exitF = 0;

/* permutation of numbers, operators and brackets */
for (index[0] = 0; index[0] < nNumbersPermutation; index[0]++) {
  if (exitF == 1) {
    break;
  }
  for (index[1] = 0; index[1] < nOperationsOperator; index[1]++) {
    if (exitF == 1) {
      break;
    }
    for (index[2] = 0; index[2] < nBracketsMember; index[2]++) {
      if (countExit > MAXREP) {
        exitF = 1;
        break;
      }
      res = 0;
      res1 = 0;
      res2 = 0;
      /* last operation not in the middle */
      if (priorityV[index[2]].priority[2] != 1) {
          /* brackets test: 1st operation */
          if (priorityV[index[2]].priority[0] == 0) {
            /* first operation on the left */
            /* operator test: 1st */
            if (op[index[1]].operation[0] == 1) {
              /* + */
              res = (float)numberV[index[0]].numbers[0]+(float)numberV[index[0]].numbers[1];
            } else if (op[index[1]].operation[0] == 2) {
              /* - */
              res = (float)numberV[index[0]].numbers[0]-(float)numberV[index[0]].numbers[1];
            } else if (op[index[1]].operation[0] == 3) {
              /* * */
              res = (float)numberV[index[0]].numbers[0]*(float)numberV[index[0]].numbers[1];
            } else {
              /* / */
              res = (float)numberV[index[0]].numbers[0]/(float)numberV[index[0]].numbers[1];
            }
          } else if (priorityV[index[2]].priority[0] == 1) {
            /* first operation on the middle */
            /* operator test: 2st */
            if (op[index[1]].operation[1] == 1) {
              /* + */
              res = (float)numberV[index[0]].numbers[1]+(float)numberV[index[0]].numbers[2];
            } else if (op[index[1]].operation[1] == 2) {
              /* - */
              res = (float)numberV[index[0]].numbers[1]-(float)numberV[index[0]].numbers[2];
            } else if (op[index[1]].operation[1] == 3) {
              /* * */
              res = (float)numberV[index[0]].numbers[1]*(float)numberV[index[0]].numbers[2];
            } else {
              /* / */
              res = ((float)numberV[index[0]].numbers[1] / (float)numberV[index[0]].numbers[2]);
            }
          } else {
            /* first operation on the right*/
            /* operator test: 3st */
            if (op[index[1]].operation[2] == 1) {
              /* + */
              res = (float)numberV[index[0]].numbers[2]+(float)numberV[index[0]].numbers[3];

            } else if (op[index[1]].operation[2] == 2) {
              /* - */
              res = (float)numberV[index[0]].numbers[2]-(float)numberV[index[0]].numbers[3];
            } else if (op[index[1]].operation[2] == 3) {
              /* * */
              res = (float)numberV[index[0]].numbers[2]*(float)numberV[index[0]].numbers[3];
            } else {
              /* / */
              res = (float)numberV[index[0]].numbers[2]/(float)numberV[index[0]].numbers[3];
            }
          }

          /* brackets test: 2st operation */
          if (priorityV[index[2]].priority[1] == 0) {
            /* second operation on the left */
            /* operator test: 1st */

            if (op[index[1]].operation[0] == 1) {
              /* + */
              res = numberV[index[0]].numbers[0]+res;
            } else if (op[index[1]].operation[0] == 2) {
              /* - */
              res = numberV[index[0]].numbers[0]-res;
            } else if (op[index[1]].operation[0] == 3) {
              /* * */
              res = numberV[index[0]].numbers[0]*res;
            } else {
              /* / */
              res = numberV[index[0]].numbers[0]/res;
            }
          } else if (priorityV[index[2]].priority[1] == 1) {
            /* second operation on the middle */

            if (priorityV[index[2]].priority[0] == 0) {
              /* 1st operation on the left */
              if (op[index[1]].operation[1] == 1) {
                /* + */
                res = res+numberV[index[0]].numbers[2];
              } else if (op[index[1]].operation[1] == 2) {
                /* - */
                res = res-numberV[index[0]].numbers[2];
              } else if (op[index[1]].operation[1] == 3) {
                /* * */
                res = res*numberV[index[0]].numbers[2];
              } else {
                /* / */
                res = res/numberV[index[0]].numbers[2];
              }
            } else {
              /* 1st operation on the right */
              if (op[index[1]].operation[1] == 1) {
                /* + */
                res = res+numberV[index[0]].numbers[1];
              } else if (op[index[1]].operation[1] == 2) {
                /* - */
                res = res-numberV[index[0]].numbers[1];
              } else if (op[index[1]].operation[1] == 3) {
                /* * */
                res = res*numberV[index[0]].numbers[1];
              } else {
                /* / */
                res = res/numberV[index[0]].numbers[1];
              }
            }
          } else {
            /* second operation on the right */
            /* operator test: 3st */
            if (op[index[1]].operation[2] == 1) {
              /* + */
              res = res+numberV[index[0]].numbers[3];

            } else if (op[index[1]].operation[2] == 2) {
              /* - */
              res = res-numberV[index[0]].numbers[3];
            } else if (op[index[1]].operation[2] == 3) {
              /* * */
              res = res*numberV[index[0]].numbers[3];
            } else {
              /* / */
              res = res/numberV[index[0]].numbers[3];
            }
          }

          /* brackets test: 3st operation */
          if (priorityV[index[2]].priority[2] == 0) {
            /* third operation on the left */
            /* operator test: 1st */
            if (op[index[1]].operation[0] == 1) {
              /* + */
              res = numberV[index[0]].numbers[0]+res;
            } else if (op[index[1]].operation[0] == 2) {
              /* - */
              res = numberV[index[0]].numbers[0]-res;
            } else if (op[index[1]].operation[0] == 3) {
              /* * */
              res = numberV[index[0]].numbers[0]*res;
            } else {
              /* / */
              res = numberV[index[0]].numbers[0]/res;
            }
          } else if (priorityV[index[2]].priority[2] == 1) {
            /* third operation on the middle */
            /* we need another code for this situation */
          } else {
            /* third operation on the right */
            /* operator test: 3st */
            if (op[index[1]].operation[2] == 1) {
              /* + */
              res = res+numberV[index[0]].numbers[3];

            } else if (op[index[1]].operation[2] == 2) {
              /* - */
              res = res-numberV[index[0]].numbers[3];
            } else if (op[index[1]].operation[2] == 3) {
              /* * */
              res = res*numberV[index[0]].numbers[3];
            } else {
              /* / */
              res = res/numberV[index[0]].numbers[3];
            }
          }
        }
      /* situation when we have priority 0-2-1, last operation in the middle */
      if (priorityV[index[2]].priority[2] == 1) {
        res = 0;
        res1 = 0;
        res2 = 0;
        /* operation on the left */
        /* operator test: 1st */
        if (op[index[1]].operation[0] == 1) {
          /* + */
          res1 = numberV[index[0]].numbers[0]+numberV[index[0]].numbers[1];
        } else if (op[index[1]].operation[0] == 2) {
          /* - */
          res1 = numberV[index[0]].numbers[0]-numberV[index[0]].numbers[1];
        } else if (op[index[1]].operation[0] == 3) {
          /* * */
          res1 = numberV[index[0]].numbers[0]*numberV[index[0]].numbers[1];
        } else {
          /* / */
          res1 = numberV[index[0]].numbers[0]/numberV[index[0]].numbers[1];
        }
        /* operation on the right */
        if (op[index[1]].operation[2] == 1) {
          /* + */
          res2 = numberV[index[0]].numbers[2]+numberV[index[0]].numbers[3];

        } else if (op[index[1]].operation[2] == 2) {
          /* - */
          res2 = numberV[index[0]].numbers[2]-numberV[index[0]].numbers[3];
        } else if (op[index[1]].operation[2] == 3) {
          /* * */
          res2 = numberV[index[0]].numbers[2]*numberV[index[0]].numbers[3];
        } else {
          /* / */
          res2 = numberV[index[0]].numbers[2]/numberV[index[0]].numbers[3];
        }
        /* operation on the middle */
        if (op[index[1]].operation[1] == 1) {
          /* + */
          res = res1+res2;
        } else if (op[index[1]].operation[1] == 2) {
          /* - */
          res = res1-res2;
        } else if (op[index[1]].operation[1] == 3) {
          /* * */
          res = res1*res2;
        } else {
          /* / */
          res = res1/res2;
        }
      }
      /* int test */
      booleano = intTest (res);
      if (booleano == 0) {
        continue;
      }
      number = (int)res;
      if (number < 1) {
        continue;
      }
      /* if it reaches here, then it is a integer proper solution
      printf ("\nSolutions found for Numbers: ");
      for (i = 0; i < 4; i++) {
        printf ("%.0f ", numberV[index[0]].numbers[i]);
      }
      printf (" with brackets: ");
      for (i = 0; i < 3; i++) {
        printf ("%d ", priorityV[index[2]].priority[i]);
      }
      printf (" whith operators: ");
      for (i = 0; i < 3; i++) {
        printf ("%d ", op[index[1]].operation[i]);
      }
      printf ("with res = %d and float %.2f.", number, res);
      fflush (stdout);*/
      if (booleano == 0) {
        continue;
      }
      if (number < sizeMemory) {
        memoryNGenerate[number-1] = 1;
      } else {
        continue;
      }
    }
  }
}
while (memoryNGenerate[count] != 0 && count < sizeMemory) {
  count++;
}
return count;
}
/******************************************************************************/
int testRepetition (int *indices, int dim) {
/* this function returns 1 if all the numbers in the index are diferent or 0 if
at least one is equal */
int i, j;
for (i = 0; i < dim-1; i++) {
  for (j = i+1; j < dim; j++) {
    if (indices[i] == indices[j]) {
      /* then they are equal */
      return 0;
    }
  }
}
return 1;
}
/******************************************************************************/
int intTest (float res) {
/* this function returns 1 if the float is a integer or 0 if is a float */
float decimal;
int grown = 10000000;
decimal = res-(int)res;
grown = decimal*grown;
if (grown > 0.00001) {
  /* this number is a float */
  return 0;
} else {
  /* this number is an integer */
  return 1;
}
}
/******************************************************************************/
