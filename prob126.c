#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXI 1000
#define LMAX 20000
#define DIMARRAY 20000

/* this function makes the creation of the new layers, saving the
results in the v array, and then return 1 if all went ok, or 0 if
there was a problem in the function */
int layerFulling (int *v, int dimV, int surface, int volume, int sumxyz);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
int c,l,h, dimV, max, surface, i, cMax=0, maxI, volume, sumxyz;
int *v, boolean, answer=0, lMax;
maxI = MAXI;
lMax = LMAX;
dimV = DIMARRAY;//pow(maxI,2)+1
v = (int*) calloc (dimV, sizeof (int));
if (v == NULL) {
  printf("\nThere was an error in the memory allocation of v.");
  return 0;
}
for (l = 1; l < lMax; l++) {
  for (c = 1; c < l+1; c++) {
    surface = 2*(c*l+c*1+l*1);
    if (surface > dimV) { break;}
    for (h = 1; h < c+1; h++) {
      surface = 2*(c*l+c*h+l*h);
      if (surface > dimV) { break;}
      v[surface]++;
      volume = l*c*h;
      sumxyz= l+c+h;
      boolean = layerFulling (v, dimV, surface, volume, sumxyz);
      if (boolean == 0) {
        printf("\nThere was an error in the function layerFulling.");
        return 0;
      }
    }
  }
}
/* find result */
for (i = 0; i < dimV; i++) {
  if (v[i] == maxI) {
    answer = i;
    break;
  }
}
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
if (answer != 0) {
  printf("\nThe least value of n that C(n)=1000 is n = %d.", answer);
} else {
  printf("\nValue not found.");
}
printf("\n");
return 0;
}
/******************************************************************************/
int layerFulling (int *v, int dimV, int surface, int volume, int sumxyz) {
/* this function makes the creation of the new layers, saving the
results in the v array, and then return 1 if all went ok, or 0 if
there was a problem in the function */
if (v == NULL || dimV < 1) {
  return 0;
}
int n, value;
/* first value, n = 2 */
n = 2;
value = surface+4*(sumxyz+n-2)*(n-1);
while (value < dimV) {
  v[value]++;
  n++;
  value = surface+4*(sumxyz+n-2)*(n-1);
}
return 1;
}
/******************************************************************************/
