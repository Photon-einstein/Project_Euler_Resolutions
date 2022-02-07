#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/* this function read 2 int numbers from a file, and returns by reference the
base and the expt. If the file reaches not yet the end it returns 1, else it
returns 0, 0 also it there was a problem. */
int readNumbers(FILE *f, int *base, int *expt);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
char nameFile[13] = "base_exp.txt";
FILE *f;
int base, expt, lineMax, booleano, line = 1;
float number, max;

f = fopen (nameFile, "r");
if (f == NULL) {
  printf ("\nThere was an error in the opening of the file %s.", nameFile);
  return 0;
}

while (readNumbers(f, &base, &expt)) {
  number = expt * logf(base);
  if (number > max) {
      max = number;
      lineMax = line;
  }
  line++;
}
fclose(f);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nThe line with the biggest number is %d.", lineMax);
printf ("\n");
return 0;
}
/******************************************************************************/
int readNumbers(FILE *f, int *base, int *expt) {
/* this function read 2 int numbers from a file, and returns by reference the
base and the expt. If the file reaches not yet the end it returns 1, else it
returns 0, 0 also it there was a problem. */
if (f == NULL || base == NULL || expt == NULL) {
  return 0;
}
int baseN, expN;
if ((fscanf (f, "%d,%d", &baseN, &expN)) != EOF ) {
  *base = baseN;
  *expt = expN;
  return 1;
} else {
  return 0;
}
}
/******************************************************************************/
