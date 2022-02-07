#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MIN 1
#define MAX 5
typedef long long int lli;

/* this function makes the calculation of the gcd between a and b */
lli gcd (lli a, lli b);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int nMin = MIN, nMax = MAX, n, res = 0, resDecad=0;
lli p, a, num, den, powerTen, b, powerTenGcd, d, pL;
for (n = nMin; n < nMax+1; ++n) {
  powerTen = (int)pow(10.0,n);
  resDecad = 0;
  for (p = 1; p < 2*powerTen+1; ++p) {
    if (p % 10000 == 0) {
      printf("\np = %lld | pMax = %lld | n = %d", p, 2*powerTen+1, n);
      fflush(NULL);
    }
    d = gcd(p,powerTen);
    pL = p/d;
    powerTenGcd = powerTen/d;
    for (a = 1; a < 2*powerTenGcd+1; ++a) {
      /* num calc */
      num = a*powerTenGcd;
      /* den calc */
      den = pL*a-powerTenGcd;
      if (den < 1) {
        continue;
      }
      if (num % den == 0) {
        b = num/den;
        if (a > b) {
          continue;
        }
        ++resDecad;
        if (gcd(a,b)==1) {
          printf("\n%lld|%lld|%lld", a, b, p);
        }
      }
    }
  }
  /* res update */
  res+=resDecad;
  printf("\nn = %d | There are %d solution in %lld decade", n, resDecad, powerTen);
  fflush(NULL);
}
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nFrom %d <= n <= %d there are up to %d solutions.", nMin, nMax, res);
printf("\n");
return 0;
}
/******************************************************************************/
lli gcd (lli a, lli b) {
/* this function makes the calculation of the gcd between a and b */
lli q, r;
while (b > 0) {
	q = a / b;
	r = a - q * b;
	a = b;
	b = r;
}
return a;
}
/******************************************************************************/
