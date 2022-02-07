#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabdispersao.h"
#define TABDISPERSAOSIZE 1000001
#define NGAMES 50
#define NCOLUMROWS 9
#define SIZESEARCH 10
#define SIZESQUARE 3
#define DIMZCONTMAX pow(NCOLUMROWS,2)
#define SIZESTR 150

typedef struct {
  int line;
  int colun;
  int guess;
  int order; /* this says in wich order the guess, in the sudoku */
} testSud; /* this is a structure that stores the guesses tested in the sudoku */

typedef struct {
  int line; /* this says the line of the element in the sudoku matrix */
  int colun; /* this says the colun of the element in the sudoku matrix */
  int *testV; /* this is a pointer used in the verification of the zeros */
  int nZeros; /* this says how much zeros there are left */
} zCont;

typedef struct {
  int number; /* number left as possible solution */
  int booleanoTested; /* 1 if already tested or 0 if not tested */
} guess;

typedef struct {
  int number; /* number from 0 to 9 */
  int lineBeg; /* this says when start the line square verification */
  int columBeg; /* this says when start the colum square verification */
  int *testV; /* this is a pointer to use in the verification */
  int dimGuess; /* dimension of the guessV array */
} sud;

/* this function reads each sudoku to the matrix and returns -1 if there was a
problem in the reading or the number of zeros of the new sudoku */
int readingSudoku (FILE *f, sud** sudoku, int nLines, int nColum);

/* this function, is called when a sudoku is already in position to extract a
solution, and returns an integer */
int solutionCalculate (sud** sudoku);

/* this function returns the beginning of search for a number in the position
line and colun, and returns the result by reference, this function returns
also 1 if all ok or 0 if there was a problem */
int startingSquareLineColun (int line, int colun, int *sudokuLine, int *sudokuColun);

/* this function makes the line verification, and if the number is present then
is marked as 1 in the array,  in the end it returns the number of zeros in the
array */
int lineVerification (sud** sudoku, int *test, int line, int sizeLine, int sizeSearch);

/* this function makes the colum verification, and if the number is present then
is marked as 1 in the array,  in the end it returns the number of zeros in the
array */
int columVerification (sud** sudoku, int *test, int col, int sizeColun, int sizeSearch);

/* this function makes the square verification, and if the number is present then
is marked as 1 in the array,  in the end it returns the number of zeros in the
array */
int squareVerification (sud** sudoku, int *test, int lineBeg, int columBeg, int sizeSquare, int sizeSearch);

/* this function returns the number of zeros in the array from the starting point
until size be reach */
int nZerosCalc (int *test, int size, int starting);

/* this function returns the only zero position in the array missing */
int findOnlyZeroPos (int *test, int size, int starting);

/* this function free all memory allocated in the sudoku structure, and then
returns */
void freeMemoryMatrix (sud** sudoku, int sizeLine);

/* this function free all memory allocated in the array zeroV whith nZeros
elements, and then returns to the main function */
void freeMemoryZeroControl (zCont* zeroV, int nZeros);

/* this function makes the sorting of an array of nZeros, in ascending order of
by order: number of zeros, number of the line, and number of the colun, and it
returns to the main function, return 1 if all ok or 0 if there was a problem */
int sortArrayZeroControl (zCont* zeroV, int nZeros);

/*this function makes the sorting in ascending order of respectibly, line, colun
and then guess. In the end it returns to the main function 1 if all ok or 0 if
there was a problem. */
int sortArrayTestSud (testSud *testSudV, int size);

/* this function makes the duplicate of a original sudoku, and then return to
the main function, return 1 if all ok or 0 if there was a problem */
int sudokuDuplicateMaker (sud** sudoku, sud** sudokuAux, int dim);

/* this function is going to search for the new guess to be tested in the sudoku.
If sizeTestSudV = 0, then there are not yet any guess tested, so we only need to
check for a single guess to be tested for repetition in the hashtable,.
If sizeTestSudV > 0, then there are already guesses tested in this sudoku, so we
must take that in consideration. We must make a saved version of the testSudV
before inserting a new guess to be checked for any repetition.
If there are repetition, we just recover the original array and continue to
check for a new not yet repetead sequence.
If there are no repetition, we must insert this new one in the testSudV, and
then return the value to the function, so it returns the number of the zero in
the zeroV array and by reference the possibility to be tested.
If there was an error then, it returns -1.
If there is no solution yet not in the hast table then returns
duplicateBoolean = 1 by reference, else 0 if all ok */
int checkRepetitionOfPossibilities (tabela_dispersao *td, testSud *testSudV, int sizeTestSudV,
   zCont *zeroV, int zeroCount, int* zeroTest, int *duplicateBoolean, int sizeTestSudVMax);

/* this function will create a matrix of strings with all the sets (1,2,3,..,n)
of testSud elements, in a string, saved on a matrix, and then starting in the
biggest string will teste for no repetition, and then, when no repetition is to
be found, then it insert in the hast table. It returns 1 if all ok or 0 if
there was a problem in the function. */
int insertionOfNoDuplicateString (tabela_dispersao *td, testSud *testSudV, int sizeTestSudV);

/*this function makes the sorting in ascending order of order of insertion.
In the end it returns to the main function 1 if all ok or 0 if
there was a problem. */
int sortArrayTestSudbyOrder (testSud *testSudV, int size);

/* this function prints the content of the array zeroV and then returns to the
main function */
void printOfZeroVArray (zCont *zeroV, int sizeZeroV);

/* this function makes the print of the testSudV array, and then returns to the
main function */
void printfTestSudV (testSud *testSudV, int sizeTestSudV);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int i, j, k, answer = 0, nZeros, modification, line, col, booleano, zeros, count = 0, sizeZeroV = DIMZCONTMAX;
int zeroCount, solved, savedSudoku, tdBooleano, zeroTest, testSudBool, sizeTestSudV, nZerosMem;
int duplicateBoolean, problem, nInsertion;
char nameFile[11] = "sudoku.txt";
FILE *f;
sud **sudoku, **sudokuAux;
zCont *zeroV = NULL;
tabela_dispersao*td;
testSud *testSudV = NULL;

f = fopen (nameFile, "r");
if (f == NULL) {
  printf ("\nThere was an error in the opening of the file %s.\n", nameFile);
  return 0;
}
/* we are now going to create the matrix for the sudoku resolution */
sudoku = (sud**) calloc (NCOLUMROWS, sizeof(sud*));
if (sudoku == NULL) {
  printf ("\nThere was an error in the creation of the sudoku matrix.\n");
  return 0;
}
for (i = 0; i < NCOLUMROWS; i++) {
  sudoku[i] = (sud*) calloc (NCOLUMROWS, sizeof(sud));
  if (sudoku[i] == NULL) {
    printf ("\nThere was an error in the creation of the sudoku matrix.\n");
    return 0;
  }
}
for (i = 0; i < NCOLUMROWS; i++) {
  for (j = 0; j < NCOLUMROWS; j++) {
    booleano = startingSquareLineColun (i, j, &sudoku[i][j].lineBeg, &sudoku[i][j].columBeg);
    if (booleano == 0) {
      printf ("\nThere was an error in the function startingSquareLineColun.\n");
      return 0;
    }
  }
}
/* we are now going to process each of the 50 games */
for (i = 0; i < NGAMES; i++) {
  printf ("\nSudoku nº%d a ser processado.", i+1);
  fflush (stdout);
  nZeros = readingSudoku (f, sudoku, NCOLUMROWS, NCOLUMROWS);
  if (nZeros == -1) {
    printf ("\nThere was an error in the function readingSudoku.\n");
    return 0;
  }
  if (nZeros == 0) {
    /* work already done */
    answer+=solutionCalculate (sudoku);
    continue;
  }
  modification = 1;
  count = 0;
  solved = 0;
  savedSudoku = 0; /* if 1 then the sudoku is already with a saved version */
  tdBooleano = 0; /* if 1 then there is already a dispersion table created */
  testSudBool = 0; /* if 1 then the array of the possibilities is already created */
  problem = 0; /* flag for repetition of combination in the hast table */
  nInsertion = 0;
while (solved == 0) {
  modification = 1;
  while (nZeros != 0 && modification == 1) {
    modification = 0;
    if (problem != 1) {
      /* creation of a new array for testing the zeros in the hard sudokus */
      zeroV = (zCont*) calloc (sizeZeroV, sizeof(zCont));
      if (zeroV == NULL) {
        printf ("\nThere was an error in the creation of the array zeroV.\n");
        return 0;
      }
      zeroCount = 0;
    }
    for (line = 0; line < NCOLUMROWS; line++) {
      if (nZeros == 0) {
        break;
      }
      for (col = 0; col < NCOLUMROWS; col++) {
        if (nZeros == 0) {
          break;
        }
        if (sudoku[line][col].number == 0 && problem != 1) {
            /* number need to be checked */
            /* array for testing created */
            sudoku[line][col].testV = (int*) calloc (SIZESEARCH, sizeof (int));
            if (sudoku[line][col].testV == NULL) {
              printf ("\nThere was a problem in the creation of the array.\n");
              return 0;
            }
            /*printf ("\n1");
            fflush (stdout);*/
            /* line verification */
            zeros = lineVerification (sudoku, sudoku[line][col].testV, line, NCOLUMROWS ,SIZESEARCH);
            if (zeros == 1 && testSudBool == 0) {
              sudoku[line][col].number = findOnlyZeroPos(sudoku[line][col].testV, SIZESEARCH, 1);
              free(sudoku[line][col].testV);
              modification = 1;
              nZeros--;
              continue;
            }
            /* colum verification */
            zeros = columVerification (sudoku, sudoku[line][col].testV, col, NCOLUMROWS,SIZESEARCH);
            if (zeros == 1 && testSudBool == 0) {
              sudoku[line][col].number = findOnlyZeroPos(sudoku[line][col].testV, SIZESEARCH, 1);
              free(sudoku[line][col].testV);
              modification = 1;
              nZeros--;
              continue;
            }
            /* square verification */
            zeros = squareVerification (sudoku, sudoku[line][col].testV, sudoku[line][col].lineBeg, sudoku[line][col].columBeg, SIZESQUARE, SIZESEARCH);
            if (zeros == 1) {
              sudoku[line][col].number = findOnlyZeroPos(sudoku[line][col].testV, SIZESEARCH, 1);
              free(sudoku[line][col].testV);
              modification = 1;
              nZeros--;
              continue;
            }
            if (zeros != 0 && zeros != 1) {
              /* if it reaches here then it was no solution found */
              zeroV[zeroCount].line = line;
              zeroV[zeroCount].colun = col;
              zeroV[zeroCount].testV = sudoku[line][col].testV;
              zeroV[zeroCount].nZeros = zeros;
              sudoku[line][col].testV = NULL;
              sudoku[line][col].dimGuess = nZeros;
              /* increase of the counter of no solution yet found */
              zeroCount++;
              continue;
            }
        }
        /* error in the guess test */
        if ((zeros == 0 || problem == 1) && testSudBool == 1) {
          if (sudoku[line][col].testV != NULL) {
            free(sudoku[line][col].testV);
          }
          if (i == -1) {
            printOfZeroVArray (zeroV, sizeZeroV);
            printfTestSudV (testSudV, sizeTestSudV);
          }
          booleano = insertionOfNoDuplicateString (td, testSudV, sizeTestSudV);
          nInsertion++;
          if (booleano == 0) {
            printf ("\nThere was an error in the function insertionOfNoDuplicateString.\n");
            return 0;
          }
          if (testSudBool == 1) {
            free (testSudV);
            sizeTestSudV = 0;
            testSudBool = 0;
          }
          /* recover of the previous values of the original sudoku */
          booleano = sudokuDuplicateMaker (sudokuAux, sudoku, NCOLUMROWS);
          if (booleano == 0) {
            printf ("\nThere was a problem in the function sudokuDuplicateMaker.\n");
            return 0;
          }
          if (zeroV != NULL) {
            free (zeroV);
            zeroV = NULL;
          }
          modification = 1;
          nZeros = nZerosMem;
          /* creation of a new array for testing the zeros in the hard sudokus */
          zeroV = (zCont*) calloc (sizeZeroV, sizeof(zCont));
          if (zeroV == NULL) {
            printf ("\nThere was an error in the creation of the array zeroV.\n");
            return 0;
          }
          zeroCount = 0; /* dim of zeroV array reset */
          /* reset of the values */
          line = 0;
          col = 0;
          problem = 0; /* reset of the flag for repetition in the function check.. */
          continue;
        }
      }
    }
    /* free memory allocated if modification == 1 or nZeros == 0 (no use to be
    done to the array)*/
    if (nZeros != 0 && modification == 1 && zeroV != NULL) {
      freeMemoryZeroControl (zeroV, zeroCount);
      zeroV = NULL;
    }
  }
  /* test of failure mode */
  if (nZeros == 0) {
    answer = answer+solutionCalculate (sudoku);
    solved = 1;
    if (savedSudoku == 1) {
      freeMemoryMatrix (sudokuAux, NCOLUMROWS);
      savedSudoku = 0;
    }
    if (tdBooleano == 1) {
      tabela_apaga(td);
      tdBooleano = 0;
      td = NULL;
    }
    if (testSudBool == 1 && testSudV != NULL) {
      free (testSudV);
      testSudV = NULL;
      testSudBool = 0;
    }
  } else {
    booleano = sortArrayZeroControl (zeroV, zeroCount);
    if (booleano == 0) {
      printf ("\nThere was a problem in the function sortArrayZeroControl.\n");
      return 0;
    }
    /* we are now going to make a saved sudoku version if savedSudoku = 0 */
    if (savedSudoku == 0) {
      /* sudoku is going to be saved */
      nZerosMem = nZeros;
      sudokuAux = (sud**) calloc (NCOLUMROWS, sizeof(sud*));
      if (sudoku == NULL) {
        printf ("\nThere was an error in the creation of the sudoku matrix.\n");
        return 0;
      }
      for (k = 0; k < NCOLUMROWS; k++) {
        sudokuAux[k] = (sud*) calloc (NCOLUMROWS, sizeof(sud));
        if (sudokuAux[k] == NULL) {
          printf ("\nThere was an error in the creation of the sudoku matrix.\n");
          return 0;
        }
      }
      /* function is now going to be called to make a saved version of the sudoku */
      booleano = sudokuDuplicateMaker (sudoku, sudokuAux, NCOLUMROWS);
      if (booleano == 0) {
        printf ("\nThere was a problem in the function sudokuDuplicateMaker.\n");
        return 0;
      }
      /* memory of the action taked */
      savedSudoku = 1;
    }
    if (tdBooleano == 0) {
      /* then there were not yet disperson table been created */
       td = tabela_nova(TABDISPERSAOSIZE, hash_djbm);
       if (td == NULL) {
         printf ("\nThere was a problem in the creation of a new hash table.\n");
         return 0;
       }
       tdBooleano = 1;
    }
    if (testSudBool == 0) {
      /* then there is not yet created a array of possibilities tested in a
      sudoku */
      testSudV = (testSud*) calloc (nZerosMem, sizeof(testSud));
      if (testSudV == NULL) {
        printf ("\nThere was a problem in the creation of the testSudV array.\n");
        return 0;
      }
      sizeTestSudV = 0;
      testSudBool = 1;
    }
    /* now we are going to check if the possibilities are already tested in the
    hash table or not */
    booleano = checkRepetitionOfPossibilities (td, testSudV, sizeTestSudV, zeroV,
      zeroCount, &zeroTest, &duplicateBoolean, nZerosMem);
    if (booleano == -1) {
      printf ("\nThere was a problem in the function checkRepetitionOfPossibilities.\n");
      return 0;
    }
    if (duplicateBoolean == 1) {
      modification = 1;
      problem = 1;
    } else {
      /* new possibility to be inserted */
      sudoku[zeroV[booleano].line][zeroV[booleano].colun].number = zeroTest;
      sizeTestSudV++;
      if (i == -1) {
        printf ("\n\nNew String inserted in testSudV.");
        printOfZeroVArray (zeroV, sizeZeroV);
        printf ("\n");
        printfTestSudV (testSudV, sizeTestSudV);
        printf("\n");
      }
      modification = 1;
      nZeros--;
      if (zeroV != NULL) {
        free (zeroV);
        zeroV = NULL;
      }
    }
    }
  }
}
/* free matriz memory */
freeMemoryMatrix (sudoku, NCOLUMROWS);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nThe answer is %d.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int readingSudoku (FILE *f, sud** sudoku, int nLines, int nColum) {
/* this function reads each sudoku to the matrix and returns -1 if there was a
problem in the reading or the number of zeros of the new sudoku */
if (f == NULL || sudoku == NULL || nLines == 0 || nColum == 0) {
  return -1;
}
int i, j, nZeros = 0, size;
char line[12];
fgets(line, sizeof (line), f);
size = strlen(line)-1;
line[size] = '\0';
/*printf ("\n%s in processing", line);*/
for (i = 0; i < nLines; i++) {
  fgets(line, sizeof (line), f);
  size = strlen(line)-1;
  line[size] = '\0';
  printf ("\nLine %d:", i+1);
  for (j = 0; j < nColum; j++) {
    sudoku[i][j].number = (int)line[j] - (int)'0';
    printf ("%d", sudoku[i][j].number);
    if (sudoku[i][j].number == 0) {
      nZeros++;
    }
  }
}
return nZeros;
}
/******************************************************************************/
int solutionCalculate (sud** sudoku) {
/* this function, is called when a sudoku is already in position to extract a
solution, and returns an integer */
int answer = 0;
answer+=sudoku[0][0].number*100+sudoku[0][1].number*10+sudoku[0][2].number;
return answer;
}
/******************************************************************************/
int startingSquareLineColun (int line, int colun, int *sudokuLine, int *sudokuColun) {
/* this function returns the beginning of search for a number in the position
line and colun, and returns the result by reference, this function returns
also 1 if all ok or 0 if there was a problem */
if (sudokuLine == NULL || sudokuColun == NULL || line < 0 || colun < 0 || line > 8 || colun > 8) {
  return 0;
}
if (line >= 0 && line <=2) {
  /* first three squares */
  if (colun >=0 && colun < 3) {
    *sudokuLine = 0;
    *sudokuColun = 0;
    return 1;
  } else if (colun >= 3 && colun < 6) {
    *sudokuLine = 0;
    *sudokuColun = 3;
    return 1;
  } else {
    *sudokuLine = 0;
    *sudokuColun = 6;
    return 1;
  }
} else if (line >= 3 && line <= 5) {
  /* three squares in the middle */
  if (colun >=0 && colun < 3) {
    *sudokuLine = 3;
    *sudokuColun = 0;
    return 1;
  } else if (colun >= 3 && colun < 6) {
    *sudokuLine = 3;
    *sudokuColun = 3;
    return 1;
  } else {
    *sudokuLine = 3;
    *sudokuColun = 6;
    return 1;
  }
} else {
  /* last three squares of the bottom */
  if (colun >=0 && colun < 3) {
    *sudokuLine = 6;
    *sudokuColun = 0;
    return 1;
  } else if (colun >= 3 && colun < 6) {
    *sudokuLine = 6;
    *sudokuColun = 3;
    return 1;
  } else {
    *sudokuLine = 6;
    *sudokuColun = 6;
    return 1;
  }
}
}
/******************************************************************************/
int lineVerification (sud** sudoku, int *test, int line, int sizeLine, int sizeSearch) {
/* this function makes the line verification, and if the number is present then
is marked as 1 in the array,  in the end it returns the number of zeros in the
array */
int i;
for (i = 0; i < sizeLine; i++) {
  if (sudoku[line][i].number != 0 && test[sudoku[line][i].number] == 0) {
    test[sudoku[line][i].number] = 1;
  }
}
return (nZerosCalc (test, sizeSearch, 1));
}
/******************************************************************************/
int columVerification (sud** sudoku, int *test, int col, int sizeColun, int sizeSearch) {
/* this function makes the colum verification, and if the number is present then
is marked as 1 in the array,  in the end it returns the number of zeros in the
array */
int i;
for (i = 0; i < sizeColun; i++) {
  if (sudoku[i][col].number != 0 && test[sudoku[i][col].number] == 0) {
    test[sudoku[i][col].number] = 1;
  }
}
return (nZerosCalc (test, sizeSearch, 1));
}
/******************************************************************************/
int squareVerification (sud** sudoku, int *test, int lineBeg, int columBeg, int sizeSquare, int sizeSearch) {
/* this function makes the square verification, and if the number is present then
is marked as 1 in the array,  in the end it returns the number of zeros in the
array */
int i, j;
for (i = 0; i < sizeSquare; i++) {
    for (j = 0; j < sizeSquare; j++) {
      if (sudoku[lineBeg+i][columBeg+j].number != 0 && test[sudoku[lineBeg+i][columBeg+j].number] == 0) {
        test[sudoku[lineBeg+i][columBeg+j].number] = 1;
      }
  }
}
return (nZerosCalc (test, sizeSearch, 1));
}
/******************************************************************************/
int nZerosCalc (int *test, int size, int starting) {
/* this function returns the number of zeros in the array from the starting point
until size be reach */
int i, count = 0;
for (i = starting; i < size; i++) {
  if (test[i] == 0) {
    count++;
  }
}
return count;
}
/******************************************************************************/
int findOnlyZeroPos (int *test, int size, int starting) {
/* this function returns the only zero position in the array missing */
int i;
for (i = starting; i < size; i++) {
  if (test[i] == 0) {
    return i;
  }
}
}
/******************************************************************************/
void freeMemoryMatrix (sud** sudoku, int sizeLine) {
/* this function free all memory allocated in the sudoku structure, and then
returns */
if (sudoku == NULL || sizeLine < 0) {
  return;
}
int i;
for (i = 0; i < sizeLine; i++) {
  free(sudoku[i]);
}
free (sudoku);
return;
}
/******************************************************************************/
void freeMemoryZeroControl (zCont* zeroV, int nZeros) {
/* this function free all memory allocated in the array zeroV whith nZeros
elements, and then returns to the main function */
if (zeroV == NULL) {
  return;
} else if (nZeros < 1) {
  free(zeroV);
  return;
}
int i;
for (i = 0; i < nZeros; i++) {
  free (zeroV[i].testV);
}
free (zeroV);
return;
}
/******************************************************************************/
int sortArrayZeroControl (zCont* zeroV, int nZeros) {
/* this function makes the sorting of an array of nZeros, in ascending order of
by order: number of zeros, number of the line, and number of the colun, and it
returns to the main function, return 1 if all ok or 0 if there was a problem */
if (zeroV == NULL || nZeros < 0) {
  return 0;
}
int i, j;
zCont aux;
for (i = 0; i < nZeros-1; i++) {
  for (j = i+1; j < nZeros; j++) {
    /* first number of zeros */
    if (zeroV[i].nZeros > zeroV[j].nZeros) {
      /* switch position */
      /* aux = i */
      aux.line = zeroV[i].line;
      aux.colun = zeroV[i].colun;
      aux.testV = zeroV[i].testV;
      aux.nZeros = zeroV[i].nZeros;
      /* i = j */
      zeroV[i].line = zeroV[j].line;
      zeroV[i].colun = zeroV[j].colun;
      zeroV[i].testV = zeroV[j].testV;
      zeroV[i].nZeros = zeroV[j].nZeros;
      /* j = aux */
      zeroV[j].line = aux.line;
      zeroV[j].colun = aux.colun;
      zeroV[j].testV = aux.testV;
      zeroV[j].nZeros = aux.nZeros;
      continue;
    } else if (zeroV[i].nZeros == zeroV[j].nZeros) {
      /* second number of the line */
      if (zeroV[i].line > zeroV[j].line) {
        /* switch position */
        /* aux = i */
        aux.line = zeroV[i].line;
        aux.colun = zeroV[i].colun;
        aux.testV = zeroV[i].testV;
        aux.nZeros = zeroV[i].nZeros;
        /* i = j */
        zeroV[i].line = zeroV[j].line;
        zeroV[i].colun = zeroV[j].colun;
        zeroV[i].testV = zeroV[j].testV;
        zeroV[i].nZeros = zeroV[j].nZeros;
        /* j = aux */
        zeroV[j].line = aux.line;
        zeroV[j].colun = aux.colun;
        zeroV[j].testV = aux.testV;
        zeroV[j].nZeros = aux.nZeros;
        continue;
      } else if (zeroV[i].line == zeroV[j].line) {
          /* third: number of the colun */
          if (zeroV[i].colun > zeroV[j].colun) {
            /* switch position */
            /* aux = i */
            aux.line = zeroV[i].line;
            aux.colun = zeroV[i].colun;
            aux.testV = zeroV[i].testV;
            aux.nZeros = zeroV[i].nZeros;
            /* i = j */
            zeroV[i].line = zeroV[j].line;
            zeroV[i].colun = zeroV[j].colun;
            zeroV[i].testV = zeroV[j].testV;
            zeroV[i].nZeros = zeroV[j].nZeros;
            /* j = aux */
            zeroV[j].line = aux.line;
            zeroV[j].colun = aux.colun;
            zeroV[j].testV = aux.testV;
            zeroV[j].nZeros = aux.nZeros;
            continue;
          }
      }
    }
  }
}
return 1;
}
/******************************************************************************/
int sudokuDuplicateMaker (sud** sudoku, sud** sudokuAux, int dim) {
/* this function makes the duplicate of a original sudoku, and then return to
the main function, return 1 if all ok or 0 if there was a problem */
if (sudoku == NULL || sudokuAux == NULL || dim < 1) {
  return 0;
}

int i, j;

for (i = 0; i < dim; i++) {
  for (j = 0; j < dim; j++) {
    sudokuAux[i][j].number = sudoku[i][j].number;
    sudokuAux[i][j].lineBeg = sudoku[i][j].lineBeg;
    sudokuAux[i][j].columBeg = sudoku[i][j].columBeg;
    sudokuAux[i][j].testV = sudoku[i][j].testV;
    sudokuAux[i][j].dimGuess = sudoku[i][j].dimGuess;
  }
}
return 1;
}
/******************************************************************************/
int checkRepetitionOfPossibilities (tabela_dispersao *td, testSud *testSudV,
  int sizeTestSudV, zCont *zeroV, int zeroCount, int* zeroTest, int *duplicateBoolean,
   int sizeTestSudVMax) {
/* this function is going to search for the new guess to be tested in the sudoku.
If sizeTestSudV = 0, then there are not yet any guess tested, so we only need to
check for a single guess to be tested for repetition in the hashtable,.
If sizeTestSudV > 0, then there are already guesses tested in this sudoku, so we
must take that in consideration. We must make a saved version of the testSudV
before inserting a new guess to be checked for any repetition.
If there are repetition, we just recover the original array and continue to
check for a new not yet repetead sequence.
If there are no repetition, we must insert this new one in the testSudV, and
then return the value to the function, so it returns the number of the zero in
the zeroV array and by reference the possibility to be tested.
If there was an error then, it returns -1.
If there is no solution yet not in the hast table then returns
duplicateBoolean = 1 by reference, else 0 if all ok */
if (td == NULL || testSudV == NULL || zeroV == NULL || zeroTest == NULL ||
  sizeTestSudV < 0 || zeroCount < 0 || duplicateBoolean == NULL) {
  return -1;
}
int i, j, k, l, booleano;
char *str, aux[3];
testSud *auxTestSudV;
if (sizeTestSudV == 0) {
/* If sizeTestSudV = 0, then there are not yet any guess tested, so we only need to
check for a single guess to be tested for repetition in the hashtable */
for (i = 0; i < zeroCount; i++) {
  for (j = 1; j < SIZESEARCH+1; j++) {
    if (zeroV[i].testV[j] == 0) {
      /* we arrived a new version to be tested */
      str = (char*) calloc (SIZESTR, sizeof (char));
      if (str == NULL) {
        return -1;
      }
      /* we are no going to save the data for be tested in the hash table */
      str[0] = 'L';
      sprintf(aux, "%d", zeroV[i].line);
      strcat(str, aux);
      strcat (str, "C");
      sprintf(aux, "%d", zeroV[i].colun);
      strcat(str, aux);
      strcat (str, "H");
      sprintf(aux, "%d", j);
      strcat(str, aux);
      booleano = tabela_existe(td, str);
      if (booleano == TABDISPERSAO_EXISTE) {
        free (str);
        continue;
      } else if (booleano == TABDISPERSAO_INVALIDA) {
        return -1;
      } else {
        /*printf ("\nThis function is now going to return %s.", str);*/
          /* saving of the values before leaving the function */
          testSudV[0].line = zeroV[i].line;
          testSudV[0].colun = zeroV[i].colun;
          testSudV[0].guess = j;
          testSudV[0].order = 0;
          /*retorno: se o valor for adicionado correctamente, a funcao retorna TABDISPERSAO_OK */
          *zeroTest = j; /* returns by reference the possibility to be tested */
          *duplicateBoolean = 0; /* all ok, diferent combination found */
          return i;

      }
    }
  }
}
} else {
/*  If sizeTestSudV > 0, then there are already guesses tested in this sudoku, so we
must take that in consideration. */
for (i = 0; i < zeroCount; i++) {
  for (j = 1; j < SIZESEARCH+1; j++) {
    if (zeroV[i].testV[j] == 0) {
      /* we arrived a new version to be tested */
      str = (char*) calloc (SIZESTR, sizeof (char));
      if (str == NULL) {
        return -1;
      }
      /* first we need to make a saved version of testSudV */
      auxTestSudV = (testSud*) calloc (sizeTestSudVMax, sizeof (testSudV));
      if (auxTestSudV == NULL) {
        return -1;
      }
      /* copy of the previuos values */
      for (l = 0; l < sizeTestSudV; l++) {
        auxTestSudV[l].line = testSudV[l].line;
        auxTestSudV[l].colun = testSudV[l].colun;
        auxTestSudV[l].guess = testSudV[l].guess;
        auxTestSudV[l].order = testSudV[l].order;
      }
      /* insertion of the new hipotetical guess in the end to be tested in the
      next steps */
      auxTestSudV[sizeTestSudV].line = zeroV[i].line;
      auxTestSudV[sizeTestSudV].colun = zeroV[i].colun;
      auxTestSudV[sizeTestSudV].guess = j;
      auxTestSudV[sizeTestSudV].order = sizeTestSudV;
      /* sorting of the vector auxTestSudV */
      booleano = sortArrayTestSud (auxTestSudV, sizeTestSudV+1);
      if (booleano == 0) {
        printf ("\nThere was a problem in the function sortArrayTestSud.");
        return -1;
      }
      /* we are no going to save the data for be tested in the hash table */
      for (k = 0; k < sizeTestSudV+1; k++) {
        if (k == 0) {
          strcpy(str, "L");
        } else {
          strcat (str, "L");
        }
        sprintf(aux, "%d", auxTestSudV[k].line);
        strcat(str, aux);
        strcat (str, "C");
        sprintf(aux, "%d", auxTestSudV[k].colun);
        strcat(str, aux);
        strcat (str, "H");
        sprintf(aux, "%d", auxTestSudV[k].guess);
        strcat(str, aux);
      }
      booleano = tabela_existe(td, str);
      if (booleano == TABDISPERSAO_EXISTE) {
        free (str);
        free (auxTestSudV);
        continue;
      } else if (booleano == TABDISPERSAO_INVALIDA) {
        return -1;
      } else {
          /*printf ("\nThis function is now going to return %s.", str);*/
          for (l = 0; l < sizeTestSudV+1; l++) {
            testSudV[l].line = auxTestSudV[l].line;
            testSudV[l].colun = auxTestSudV[l].colun;
            testSudV[l].guess = auxTestSudV[l].guess;
            testSudV[l].order = auxTestSudV[l].order;
          }
          free (str);
          free (auxTestSudV);
          *zeroTest = j; /* returns by reference the possibility to be tested */
          *duplicateBoolean = 0; /* all ok, diferent combination found */
          return i;
        }
      }
    }
  }
}
*duplicateBoolean = 1; /* no diferent combination found */
return 0;
}
/******************************************************************************/
int sortArrayTestSud (testSud *testSudV, int size) {
/*this function makes the sorting in ascending order of respectibly, line, colun
and then guess. In the end it returns to the main function 1 if all ok or 0 if
there was a problem. */
if (testSudV == NULL || size < 0) {
  return 0;
}
int i, j;
testSud aux;
for (i = 0; i < size-1; i++) {
  for (j = i+1; j < size; j++) {
    /* first: testing line */
    if (testSudV[i].line > testSudV[j].line) {
      /* aux = i */
      aux.line = testSudV[i].line;
      aux.colun = testSudV[i].colun;
      aux.guess = testSudV[i].guess;
      aux.order = testSudV[i].order;
      /* i = j */
      testSudV[i].line = testSudV[j].line;
      testSudV[i].colun = testSudV[j].colun;
      testSudV[i].guess = testSudV[j].guess;
      testSudV[i].order = testSudV[j].order;
      /* j = aux */
      testSudV[j].line = aux.line;
      testSudV[j].colun = aux.colun;
      testSudV[j].guess = aux.guess;
      testSudV[j].order = aux.order;
      continue;
    } else if (testSudV[i].line == testSudV[j].line) {
      /* second: testing colun */
      if (testSudV[i].colun > testSudV[j].colun) {
        /* aux = i */
        aux.line = testSudV[i].line;
        aux.colun = testSudV[i].colun;
        aux.guess = testSudV[i].guess;
        aux.order = testSudV[i].order;
        /* i = j */
        testSudV[i].line = testSudV[j].line;
        testSudV[i].colun = testSudV[j].colun;
        testSudV[i].guess = testSudV[j].guess;
        testSudV[i].order = testSudV[j].order;
        /* j = aux */
        testSudV[j].line = aux.line;
        testSudV[j].colun = aux.colun;
        testSudV[j].guess = aux.guess;
        testSudV[j].order = aux.order;
        continue;
      } else if (testSudV[i].colun == testSudV[j].colun) {
          /* third : testing guess */
          if (testSudV[i].guess > testSudV[j].guess) {
            /* aux = i */
            aux.line = testSudV[i].line;
            aux.colun = testSudV[i].colun;
            aux.guess = testSudV[i].guess;
            aux.order = testSudV[i].order;
            /* i = j */
            testSudV[i].line = testSudV[j].line;
            testSudV[i].colun = testSudV[j].colun;
            testSudV[i].guess = testSudV[j].guess;
            testSudV[i].order = testSudV[j].order;
            /* j = aux */
            testSudV[j].line = aux.line;
            testSudV[j].colun = aux.colun;
            testSudV[j].guess = aux.guess;
            testSudV[j].order = aux.order;
            continue;
          }
      }
    }
  }
}
return 1;
}
/******************************************************************************/
int insertionOfNoDuplicateString (tabela_dispersao *td, testSud *testSudV, int sizeTestSudV) {
/* this function will create a matrix of strings with all the sets (1,2,3,..,n)
of testSud elements, in a string, saved on a matrix, and then starting in the
biggest string will teste for no repetition, and then, when no repetition is to
be found, then it insert in the hast table. It returns 1 if all ok or 0 if
there was a problem in the function. */
if (td == NULL || testSudV == NULL || sizeTestSudV < 1) {
  return 0;
}
char **matrix, aux[3];
int i, j, booleano, size, insertionBooleano;
testSud *auxTestSudV;
matrix = (char**) calloc (sizeTestSudV, sizeof(char*));
if (matrix == NULL) {
  return 0;
}
for (i = 0; i < sizeTestSudV; i++) {
  matrix[i] = (char*) calloc (SIZESTR, sizeof(char));
  if (matrix[i] == NULL) {
    return 0;
  }
}
booleano = sortArrayTestSudbyOrder (testSudV, sizeTestSudV);
if (booleano == 0) {
  printf ("\nThere was an error in the function sortArrayTestSudbyOrder.");
  return 0;
}
/* fulling of the matrix to insert by means of sorting by order */
for (i = 0; i < sizeTestSudV; i++) {
  if (i == 0) {
    strcpy(matrix[i], "L");
  } else {
    /* store previous element */
    strcpy (matrix[i], matrix[i-1]);
    strcat (matrix[i], "L");
  }
  sprintf(aux, "%d", testSudV[i].line);
  strcat(matrix[i], aux);
  strcat (matrix[i], "C");
  sprintf(aux, "%d", testSudV[i].colun);
  strcat(matrix[i], aux);
  strcat (matrix[i], "H");
  sprintf(aux, "%d", testSudV[i].guess);
  strcat(matrix[i], aux);
}
/* testing of no repetitions */
insertionBooleano = 0;
for (i = sizeTestSudV-1; i > -1; i--) {
  booleano = tabela_existe(td, matrix[i]);
  if (booleano == TABDISPERSAO_INVALIDA) {
    /* delete of the matrix */
    for (j = 0; j < sizeTestSudV; j++) {
      free (matrix[j]);
    }
    free (matrix);
    matrix = NULL;
    return 0;
  } else if (booleano == TABDISPERSAO_NAOEXISTE) {
    /*we are now going to insert a new element no repetead, in the hash table*/
    booleano = tabela_insere (td, matrix[i], "A");
    if (booleano == TABDISPERSAO_ERRO || booleano == TABDISPERSAO_INVALIDA) {
      /* delete of the matrix */
      for (j = 0; j < sizeTestSudV; j++) {
        free (matrix[j]);
      }
      free (matrix);
      matrix = NULL;
      return 0;
    } else {
      insertionBooleano = 1;
      break;
    }
  }
}
/* delete of the matrix */
for (j = 0; j < sizeTestSudV; j++) {
  free (matrix[j]);
}
free (matrix);
matrix = NULL;
return 1;
}
/******************************************************************************/
int sortArrayTestSudbyOrder (testSud *testSudV, int size) {
/*this function makes the sorting in ascending order of order of insertion.
In the end it returns to the main function 1 if all ok or 0 if
there was a problem. */
if (testSudV == NULL || size < 0) {
  return 0;
}
int i, j;
testSud aux;
for (i = 0; i < size-1; i++) {
  for (j = i+1; j < size; j++) {
    /* first: testing order */
    if (testSudV[i].order > testSudV[j].order) {
      /* aux = i */
      aux.line = testSudV[i].line;
      aux.colun = testSudV[i].colun;
      aux.guess = testSudV[i].guess;
      aux.order = testSudV[i].order;
      /* i = j */
      testSudV[i].line = testSudV[j].line;
      testSudV[i].colun = testSudV[j].colun;
      testSudV[i].guess = testSudV[j].guess;
      testSudV[i].order = testSudV[j].order;
      /* j = aux */
      testSudV[j].line = aux.line;
      testSudV[j].colun = aux.colun;
      testSudV[j].guess = aux.guess;
      testSudV[j].order = aux.order;
      continue;
    }
  }
}
return 1;
}
/******************************************************************************/
void printOfZeroVArray (zCont *zeroV, int sizeZeroV) {
/* this function prints the content of the array zeroV and then returns to the
main function */
if (zeroV == NULL || sizeZeroV < 0) {
  printf ("\nProblem in the parameter of zeroVPrintFunction.");
  return;
}
int i, j;
printf ("\nPrint of zeroV array.");
for (i = 0; i < sizeZeroV; i++) {
  if (zeroV[i].nZeros == 0) {
    continue;
  }
  printf ("\nPos:%d, Line:%d, Colun:%d; Hipot:%d,Numbers:", i, zeroV[i].line, zeroV[i].colun, zeroV[i].nZeros);
  for (j = 1; j < SIZESEARCH; j++) {
    if (zeroV[i].testV != NULL) {
      if (zeroV[i].testV[j] == 0) {
        printf (" %d,", j);
      }
    }
  }
}
return;
}
/******************************************************************************/
void printfTestSudV (testSud *testSudV, int sizeTestSudV) {
/* this function makes the print of the testSudV array, and then returns to the
main function */
if (testSudV == NULL || sizeTestSudV < 0) {
  printf ("\nProblem in the parameter of printfTestSudV.");
  return;
}
int i, j;
printf ("\nPrint of testSudV array.");
for (i = 0; i < sizeTestSudV; i++) {
  printf ("\nPos:%d, Line:%d, Colun:%d; Guess:%d,Order: %d", i, testSudV[i].line,
   testSudV[i].colun, testSudV[i].guess, testSudV[i].order);
}
return;
}
/******************************************************************************/
