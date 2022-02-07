#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZESTRING 15
#define SIZEARRAY 2000
typedef struct {
  char letters[SIZESTRING];
  int booleanoFreq[SIZESTRING];
  int booleanoFreqSorted; /* 1 if already sorted or 0 if not yet sorted */
  int size;
} freq;
typedef struct {
  int base;
  int square;
  char name[SIZESTRING];
  int size;
  freq v;
} pow2;
typedef struct {
  char name[SIZESTRING];
  int size;
  char palindrome[SIZESTRING];
  char letterArranged[SIZESTRING];
  freq v;
} words;


/* this function fill the array v with the words readed in
the file, until the file is over or maxSize be reached.
It returns by reference the real size of the array v and
the sizeStringMax of all the string evaluated.
Returns 1 if all ok or 0 if there was a problem or if the maxSize
was reached */
int fillArray (FILE *f, words *v, int maxSize, int *realSize, int *sizeStringMax);

/* this function removes the quotation marks and then return 1 if
all ok or 0 if there was a problem */
int quotationMarksRemove (char *original, int size);

/* this function creates a palindrome word from a original array
of chars. It then returns 1 if all ok or 0 if there was a problem */
int palindromeCreate (char *original, char *palindrome, int size);

/* this function makes the sorting of the array v in descending
order of size of each string name.
It then returns 1 if all ok or 0 if there was a problem */
int orderArray (words *v, int size);

/* this function makes the sorting of letters in ascending order
and then returns 1 if all ok or 0 if there was a problem */
int sortLettersAscendingOrder (char *v, int size);

/* this function fill the array v withe the square, starting
in the number start, going until size elements and then
returns 1 if all ok or 0 if there was a problem */
int squareFill (pow2 *v, int size, int start);

/* this function calculate the dimension of the count and returns by reference
the number of numbers of the count. It returns the dimension if all ok or 0 if
there was a problem */
int dimCalc (int count, int *nAlg);

/* this function compute the first ocurrence of two diferente words non
palindromic that have the same letters in other orders. It returns the
sizeStrMax of this word by reference and it returns the index in the array of
this words found or if there was a problem returns -1 */
int sizeSolutionMax (words *v, int size, int *sizeStrMax);

/* this function makes creates the memory allocation for the digits and then
fills the array with the digits of the number, it returns the pointer of the
new array or NULL if there was a problem in the function. */
int *fillsArrayDigit (int count, int dim, int nAlg);

/* this function makes the calculation of the letters that existe in the original,
to the letters array, only 1 times. It search in the sizeOriginal size.
It calculates also the freq of the letters.
It returns the size if all ok or 0 if there was a problem. */
int creationOfFeqLettersNonRepetead (char *letters, char *original, int sizeOriginal, int *booleanoFreq);

/* this function makes the order in ascending order, of an array of char values,
of dim = size. It returns then 1 if went all ok or 0 if there was a problem */
int orderFreqArray (int *v, int size);

/* this function computes the answer and then it returns or the answer or 0 if
not found or -1 if there was an error */
int findingTheAnswer (words *names, int startSearch, int realSize, pow2 *squareV, int powSizeMax);

/* this function tests if v1 has the same digits as v2, and returns -1 if there
was a problem in the function, 0 if there have not the same digits or 1 if they
have the same digits */
int testEqualArray (int *v1, int *v2, int size);

/* this function search for a second number square in the array squareV, and
test if this is a anagram of the first number. It returns -1 if there was an
error in the function, 0 if there was no solution found or the answer if the
number generated was also a square number */
int searchAnswer (char *name1, int sizeSearchStr, char *name2, char *square1, int startSearchSquare, int powSizeMax, pow2 *squareV);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int booleano, maxSize, realSize, i,j, sizeStrMax, startSearch, powSizeMax, answer;
char nameFile[10] = "words.txt";
words names[SIZEARRAY];
FILE *f;
pow2 *squareV;

maxSize = SIZEARRAY;
f = fopen (nameFile, "r");
if (f == NULL) {
  printf ("\nThere was a problem in the opening of the file.");
  return 0;
}
booleano = fillArray (f, names, maxSize, &realSize, &sizeStrMax);
if (booleano == 0) {
  printf ("\nThere was a problem in the function fillArray.");
  return 0;
}
booleano = orderArray (names, realSize);
if (booleano == 0) {
  printf ("\nThere was a problem in the function orderArray.");
  return 0;
}
/* creation of the palindrome char */
for (i = 0; i < realSize; i++) {
  booleano = palindromeCreate (names[i].name, names[i].palindrome, names[i].size);
  if (booleano == 0) {
    printf ("\nThere was a problem in the function palindromeCreate.");
    return 0;
  }
}
/* creation of letterArranged char */
for (i = 0; i < realSize; i++) {
  strcpy(names[i].letterArranged, names[i].name);
  booleano = sortLettersAscendingOrder (names[i].letterArranged, names[i].size);
  if (booleano == 0) {
    printf ("\nThere was a problem in the function sortLettersAscendingOrder.");
    return 0;
  }
}
/*printf ("\nThe max size of all the strings is %d.", sizeStrMax);*/
startSearch = sizeSolutionMax (names, realSize, &sizeStrMax);
if (startSearch == -1) {
  printf ("\nThere was a problem in the function sizeSolutionMax.");
  return 0;
}
/*printf ("\nThe search starts at %d and has a sizeStrMax = %d.", startSearch, sizeStrMax);*/
powSizeMax = sqrt(pow(10,sizeStrMax+1));
/*printf ("\nThe search has a maximum size of %d.", powSizeMax);*/
/* square fill */
squareV = (pow2*) calloc (powSizeMax, sizeof (pow2));
if (squareV == NULL) {
  printf ("\nThere was an error in the memory allocation of squareV array.");
  return 0;
}
booleano = squareFill (squareV, powSizeMax, powSizeMax-1);
/* creation of the freq array of the letters of the names */
for (i = startSearch; i < realSize; i++) {
  names[i].v.size = creationOfFeqLettersNonRepetead (names[i].v.letters, names[i].name, names[i].size, names[i].v.booleanoFreq);
  names[i].v.booleanoFreqSorted = 0; /* not yet sorted */
  if (names[i].v.size == 0) {
    printf("\nThere was a problem in the function creationOfFeqLettersNonRepetead.");
    return 0;
  }
}
/* ordering of the array of the letters of the names */
for (i = startSearch; i < realSize; i++) {
  booleano = orderFreqArray (names[i].v.booleanoFreq, names[i].v.size);
  if (booleano == 0) {
    printf ("\nThere was a problem in the function orderFreqArray.");
    return 0;
  }
  names[i].v.booleanoFreqSorted = 1; /* already sorted */
}
/* creation of the freq array of the letters of the pow2 */
for (i = 0; i < powSizeMax; i++) {
  if (squareV[i].size > sizeStrMax) {
    /* no need to compute this */
    continue;
  }
  squareV[i].v.size = creationOfFeqLettersNonRepetead (squareV[i].v.letters, squareV[i].name, squareV[i].size, squareV[i].v.booleanoFreq);
  squareV[i].v.booleanoFreqSorted = 0; /* not yet sorted */
  if (squareV[i].v.size == 0) {
    printf("\nThere was a problem in the function creationOfFeqLettersNonRepetead.");
    return 0;
  }
/* ordering of the array of the letters of the pow numbers */
  booleano = orderFreqArray (squareV[i].v.booleanoFreq, squareV[i].v.size);
  if (booleano == 0) {
    printf ("\nThere was a problem in the function orderFreqArray.");
    return 0;
  }
  /*printf ("\nFor the number: %d the freq is: ", squareV[i].square);
  for (j = 0; j < squareV[i].v.size; j++) {
    printf (" %d", squareV[i].v.booleanoFreq[j]);
  }*/
  squareV[i].v.booleanoFreqSorted = 1; /* already sorted */
}

/* searching the answer */
answer = findingTheAnswer (names, startSearch, realSize, squareV, powSizeMax);
if (answer == 0) {
  printf ("\nThere was no solution found.");
} else if (answer == -1) {
  printf ("\nThere was an error in the function findingTheAnswer.");
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThe biggest square number formed in such a pair is %d.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int fillArray (FILE *f, words *v, int maxSize, int *realSize, int *sizeStringMax) {
/* this function fill the array v with the words readed in
the file, until the file is over or maxSize be reached.
It returns by reference the real size of the array v and
the sizeStringMax of all the string evaluated.
Returns 1 if all ok or 0 if there was a problem or if the maxSize
was reached */
if (f == NULL || v == NULL || sizeStringMax == NULL || maxSize == 0) {
  return 0;
}
char name[maxSize*14], *str, compare[6] = """,""";
int count = 0, booleano, sizeStrMax = 0;

fscanf (f, "%s", name);
str = strtok (name, compare);
strcpy (v[count].name, str);
booleano = quotationMarksRemove (v[count].name, strlen(v[count].name));
v[count].size = strlen (v[count].name);
if (v[count].size > sizeStrMax) {
  sizeStrMax = v[count].size;
}
if (booleano == 0) {
  printf ("\nThere was a problem in the function quotationMarksRemove.");
  return 0;
}
count++;
while (str != NULL) {
  str = strtok (NULL, compare);
  if (str == NULL) {
    break;
  }
  if (strcmp (str, compare) == 0) {
    continue;
  }
  strcpy (v[count].name, str);
  booleano = quotationMarksRemove (v[count].name, strlen(v[count].name));
  if (booleano == 0) {
    printf ("\nThere was a problem in the function quotationMarksRemove.");
    return 0;
  }
  v[count].size = strlen (v[count].name);
  if (v[count].size > sizeStrMax) {
    sizeStrMax = v[count].size;
  }
  count++;
}
*realSize = count;
*sizeStringMax = sizeStrMax;
return 1;
}
/******************************************************************************/
int quotationMarksRemove (char *original, int size) {
/* this function removes the quotation marks and then return 1 if
all ok or 0 if there was a problem */
if (original == NULL || size == 0) {
  return 0;
}
int i, j = 0;
char replace[SIZESTRING];
for (i = 1; i < size-1; i++) {
  replace[j] = original[i];
  j++;
}
replace[j] = '\0';
strcpy(original, replace);
return 1;
}
/******************************************************************************/
int palindromeCreate (char *original, char *palindrome, int size) {
/* this function creates a palindrome word from a original array
of chars. It then returns 1 if all ok or 0 if there was a problem */
if (original == NULL || palindrome == NULL) {
  return 0;
}
int i;
if (size > 1) {
  for (i = 0; i < size; i++) {
    palindrome[i] = original[size-1-i];
  }
} else {
  strcpy(palindrome, original);
  return 1;
}
palindrome[size] = '\0';
return 1;
}
/******************************************************************************/
int orderArray (words *v, int size) {
/* this function makes the sorting of the array v in descending
order of size of each string name.
It then returns 1 if all ok or 0 if there was a problem */
if (v == NULL) {
  return 0;
}
int i, j, auxSize;
char auxName[SIZESTRING];
for (i = 0; i < size-1; i++) {
  for (j = i+1; j < size; j++) {
    if (v[i].size < v[j].size) {
      /* aux = i */
      auxSize = v[i].size;
      strcpy(auxName, v[i].name);
      /* i = j */
      v[i].size = v[j].size;
      strcpy(v[i].name, v[j].name);
      /* j = aux */
      v[j].size = auxSize;
      strcpy(v[j].name, auxName);
    }
  }
}
return 1;
}
/******************************************************************************/
int sortLettersAscendingOrder (char *v, int size) {
/* this function makes the sorting of letters in ascending order
and then returns 1 if all ok or 0 if there was a problem */
if (v == NULL) {
  return 0;
}
int i, j;
char aux;
if (size == 1) {
  /* letters already sorted */
  return 1;
}
for (i = 0; i < size-1; i++) {
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
int squareFill (pow2 *v, int size, int start) {
/* this function fill the array v withe the square, starting
in the number start, going until size elements and then
returns 1 if all ok or 0 if there was a problem */
if (v == NULL || size < 0 || start < 0) {
  return 0;
}
int i, dim;
for (i = 0; i < size; i++) {
  v[i].base = start-i;
  v[i].square = pow(v[i].base,2);
  sprintf (v[i].name,"%d", v[i].square);
  v[i].size = strlen(v[i].name);
  v[i].v.size = creationOfFeqLettersNonRepetead (v[i].v.letters, v[i].name, v[i].size, v[i].v.booleanoFreq);
  if (v[i].v.size == 0) {
    printf("\nThere was a problem in the function creationOfFeqLettersNonRepetead.");
    return 0;
  }
}
return 1;
}
/******************************************************************************/
int dimCalc (int count, int *nAlg) {
/* this function calculate the dimension of the count and returns by reference
the number of numbers of the count. It returns the dimension if all ok or 0 if
there was a problem */
if (nAlg == NULL) {
  return 0;
}
int dim = 1;
int res, nAlgarismos = 1;
res = count / dim;
while (res > 9) {
  dim = dim * 10;
  nAlgarismos++;
  res = count / dim;
}
*nAlg = nAlgarismos;
return dim;
}
/******************************************************************************/
int sizeSolutionMax (words *v, int size, int *sizeStrMax) {
/* this function compute the first ocurrence of two diferente words non
palindromic that have the same letters in other orders. It returns the
sizeStrMax of this word by reference and it returns the index in the array of
this words found or if there was a problem returns -1 */
if (v == NULL || sizeStrMax == NULL || size < 0) {
  return -1;
}
int i,j, sizeSearch, booleano;

for (i = 0; i < size-1; i++) {
  sizeSearch = v[i].size;
  for (j = i+1; j < size; j++) {
      if (v[j].size != sizeSearch) {
        /* no solution found */
        break;
      }
      /* palindromic test */
      if (strcmp(v[i].palindrome, v[j].name) == 0) {
        continue;
      }
      /* found test */
      if (strcmp(v[i].letterArranged, v[j].letterArranged) == 0) {
        /*printf ("\nMatch of %s and %s.", v[i].name, v[j].name);*/
        *sizeStrMax = v[i].size;
        return i;
      }
  }
}
printf ("\nNo solution found.");
return -1;
}
/******************************************************************************/
int *fillsArrayDigit (int count, int dim, int nAlg) {
/* this function makes creates the memory allocation for the digits and then
fills the array with the digits of the number, it returns the pointer of the
new array or NULL if there was a problem in the function. */
int *vectorDigit;
int i;
vectorDigit = (int*) calloc (nAlg, sizeof (int));
if (vectorDigit == NULL) {
  printf ("\nError in the creation of the array.");
  return NULL;
}
for (i = 0; i < nAlg; i++) {
  vectorDigit[i] = count / dim;
  count = count - vectorDigit[i]*dim;
  dim = dim / 10;
}
return vectorDigit;
}
/******************************************************************************/
int creationOfFeqLettersNonRepetead (char *letters, char *original, int sizeOriginal, int *booleanoFreq) {
/* this function makes the calculation of the letters that existe in the original,
to the letters array, only 1 times. It search in the sizeOriginal size.
It calculates also the freq of the letters.
It returns size if all ok or 0 if there was a problem. */
if (letters == NULL || original == NULL) {
  return 0;
}
int i,j, found, sizeSearch;
/* first letters is non repeated */
letters[0] = original[0];
booleanoFreq[0] = 1;
sizeSearch = 1;
for (i = 1; i < sizeOriginal; i++) {
  found = 0;
  for (j = 0; j < sizeSearch; j++) {
    if (letters[j] == original[i]) {
      booleanoFreq[j]++;
      found = 1;
    }
  }
  if (found == 0) {
    /* new letter found, that is non repeated */
    letters[sizeSearch] = original[i];
    booleanoFreq[sizeSearch] = 1;
    sizeSearch++;
  }
}
/* print of results
printf ("\nOriginal: %s and letters: %s.", original, letters);
printf ("\nFreq: ");
for (i = 0; i < sizeSearch; i++) {
  printf ("%d ", booleanoFreq[i]);
} */
return sizeSearch;
}
/******************************************************************************/
int orderFreqArray (int *v, int size) {
/* this function makes the order in ascending order, of an array of int values,
of dim = size. It returns then 1 if went all ok or 0 if there was a problem */
if (v == NULL || size < 0) {
  return 0;
}
if (size == 0 || size == 1) {
  return 1; /* array already sorted */
}
int i, j, aux;
for (i = 0; i < size-1; i++) {
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
int findingTheAnswer (words *names, int startSearch, int realSize, pow2 *squareV, int powSizeMax) {
/* this function computes the answer and then it returns or the answer or 0 if
not found or -1 if there was an error */
if (names == NULL || startSearch < 0 || startSearch > realSize-1 || squareV == NULL || powSizeMax < 0) {
  return -1;
}
int i, j, k, sizeSearch, booleanoFound = 0, answer, booleano, sizeMaxFound = 0, l;

for (i = startSearch; i < realSize-1; i++) {
  sizeSearch = names[i].size;
  /* exit test
  if (booleanoFound == 1 && sizeMaxFound > sizeSearch) {
    return answer;
  } */

  for (j = i+1; j < realSize; j++) {
      if (names[j].size < sizeSearch) {
        /* no solution found */
        break;
      } else if (names[j].size > sizeSearch) {
        /* not yet in the range */
        continue;
      }
      /* if it reaches here then names[i].size == names[j].size */
      /* palindromic test */
      if (strcmp(names[i].palindrome, names[j].name) == 0) {
        continue;
      }
      /* found test */
      if (strcmp(names[i].letterArranged, names[j].letterArranged) == 0) {
        /* first number test */
        for (k = 0; k < powSizeMax; k++) {
          /* size test */
          if (squareV[k].size > sizeSearch) {
            /* not yet in the specified range */
            continue;
          } else if (squareV[k].size < sizeSearch) {
            /* not found */
            break;
          }
          /* if it reaches here then it was found a right size */
          /* test if the freq array have the same size */
          if (names[i].v.size == squareV[k].v.size) {
            booleano = testEqualArray (names[i].v.booleanoFreq, squareV[k].v.booleanoFreq, squareV[k].v.size);
            if (booleano == -1) {
              printf ("\nThere was an error in the function testEqualArray.");
              return -1;
            } else if (booleano == 1) {
              /* first solution hipotetical found */
              /* test of the second name array */
              booleano = searchAnswer (names[i].name, sizeSearch, names[j].name, squareV[k].name, k+1, powSizeMax, squareV);
              if (booleano == -1) {
                printf ("\nThere was an error in the function searchAnswer.");
              } else if (booleano == 0) {
                /* no solution found for this squareV[k] number */
                continue;
              }
              /* if it reaches here then ot was found a new solution */
              if (booleanoFound == 0 && booleano != 0) {
                booleanoFound = 1;
                sizeMaxFound = sizeSearch;
                answer = booleano;
                /*printf ("\nbase = %d", squareV[k].base);
                printf ("\nMatch in the place %d between %s and %s.", i, names[i].name, names[j].name);
                printf ("\nFor the number: %d the freq is: ", squareV[k].square);
                for (l = 0; l < squareV[k].v.size; l++) {
                  printf (" %d", squareV[k].v.booleanoFreq[l]);
                }*/
                continue;
              }
              /* other solutions */
              if (booleanoFound == 1 && booleano != 0) {
                if (answer < squareV[k].square) {
                  answer = booleano;
                  if (sizeMaxFound < sizeSearch) {
                    sizeMaxFound = sizeSearch;
                  }
                }
              }
            }
          }
        }

      }
  }
}
if (booleanoFound == 1) {
  return answer;
} else {
  return 0;
}
}
/******************************************************************************/
int testEqualArray (int *v1, int *v2, int size) {
/* this function tests if v1 has the same digits as v2, and returns -1 if there
was a problem in the function, 0 if there have not the same digits or 1 if they
have the same digits */
if (v1 == NULL || v2 == NULL || size < 0) {
  return -1;
}
int i;
for (i = 0; i < size; i++) {
  if (v1[i] != v2[i]) {
    return 0;
  }
}
/* if it reaches here then they are equal */
return 1;
}
/******************************************************************************/
int searchAnswer (char *name1, int sizeSearchStr, char *name2, char *square1,
  int startSearchSquare, int powSizeMax, pow2 *squareV) {
/* this function search for a second number square in the array squareV, and
test if this is a anagram of the first number. It returns -1 if there was an
error in the function, 0 if there was no solution found or the answer if the
number generated was also a square number */
if (name1 == NULL || name2 == NULL || sizeSearchStr < 1 || square1 == NULL ||
startSearchSquare < 1 || startSearchSquare > powSizeMax-1 || powSizeMax < 1 ||
squareV == NULL) {
  return -1;
}
int i, j, answer = 0, booleanoCalculated[sizeSearchStr], numberRead;
char search;
/* reset of the array */
for (i = 0; i < sizeSearchStr; i++) {
  booleanoCalculated[i] = 0;
}
/* calculating the number answer test */
for (i = 0; i < sizeSearchStr; i++) {
  search = name1[i];
  for (j = 0; j < sizeSearchStr; j++) {
    if (name2[j] == search && booleanoCalculated[j] == 0) {
      /* memory of the action */
      booleanoCalculated[j] = 1;
      /* read the number */
      numberRead = (int) square1[i]-48;
      if (numberRead == 0 && j == 0) {
        /* starting in zero, not found */
        return 0;
      }
      answer+=numberRead*pow(10, sizeSearchStr-j-1);
    }
  }
}
/* search of this is a square number */
for (i = startSearchSquare; i < powSizeMax; i++) {
  if (squareV[i].square == answer) {
    /*printf ("\nName1 = %s and name2 = %s and square1 = %s.", name1, name2, square1);
    printf ("\nNumber1 = %d and searchCalculated = %d.\n", squareV[startSearchSquare-1].square, answer);*/
    if (answer > squareV[startSearchSquare-1].square) {
      return answer;
    } else {
      return squareV[startSearchSquare-1].square;
    }
  } else if (answer > squareV[i].square) {
    /* not found */
    return 0;
  }
}
/* it it reaches here then it was not found */
return 0;
}
/******************************************************************************/
