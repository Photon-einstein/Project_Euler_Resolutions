#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define MAX 100000000
typedef long long int lli;

/* this function makes the calculation of the gcd between a and b */
int gcd (int a, int b);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
lli res = 0, x,y, mult, max = MAX, sq;
for (x = 1; x <= max; ++x) {
  /* number of sum of all the integer divisors by x */
  res+=x*(max/x);
}
for (x = 1; x <= max/2; ++x) {
  /* sum the equal version */
  for (y = 1;; ++y) {
    if (1 != gcd(x,y)) {
      continue;
    }
    sq = x*x+y*y;
    if (sq > max) {
      break;
    }
    mult = 0;
    while (++mult*sq <= max) {
        res+=(2*x*mult)*(max/(mult*sq));
    }
  }
}
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\n\nTime in seconds: %lf", time);
printf("\nThe sum of all the divisors s(n) for n = %d is %lld", MAX, res);
printf("\n");
return 0;
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
