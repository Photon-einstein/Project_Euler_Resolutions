#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAXROW 100000

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
long long int sum = 0, aux=0, sumL=0;
char *first, *second;
int maxLine = MAXROW, line=1, i, j, nLine=0;
FILE *f;
first = (char*) calloc(line, sizeof(char));
if (first == NULL) {
  return 0;
}
f = fopen("res.txt", "w+");
if (f == NULL) {
  return 0;
}
first [0] = 1;
line++;
/* sum of the 1's on the perimeter of the triangle */
sum++;
sumL+=(sum-aux);
fprintf(f, "%lld\t", sum-aux);
for (line; line <= maxLine; ++line) {
  aux = sum;
  /* memory allocation of second */
  second = (char*) calloc(line, sizeof(char));
  if (second == NULL) {
    return 0;
  }
  second[0]=1;
  second[line-1]=1;
  sum+=2;
  for (j = 1; j < line-1; j++) {
    second[j]=(first[j]+first[j-1])%7;
    if (second[j] != 0) {
      sum++;
    }
  }
  fprintf(f, "%lld\t", sum-aux);
  sumL+=(sum-aux);
  if (line%7==0){
    nLine++;
    fprintf(f, " sumL=%lld\tLine = %d\tSumA=%lld\n", sumL, line, sum);
    sumL=0;
    if (nLine%7==0) {
      fprintf(f,"\n");
    }
  }
  /* free memory */
  free(first);
  first = second;
}
/* free memory */
free(second);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf("\nThe number of entries not divisible by 7 in the first %d rows of the\nPascal triangle are %lld.", maxLine, sum);
fprintf(f, "\nTempo em segundos: %lf", tempo);
fprintf(f, "\nThe number of entries not divisible by 7 in the first %d rows of the\nPascal triangle are %lld.", maxLine, sum);
fclose(f);
printf("\n");
return 0;
}
/******************************************************************************/
