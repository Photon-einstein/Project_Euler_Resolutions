#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define GOAL 2
#define LCM 1073217600

/* this function prints the answer up to size of index
and then it returns */
void printAnswer(int *index, int size, int count, int *indexStep);

/* this function returns 1 if sum = goal, if sum > goal return 0 otherwise
goes one step deeper */
int recursSearch(int goal, int sum, int *index, int i, int depth,int sizeIndex);

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int index[29]={4,5,6,7,8,9,10,12,13,14,15,18,20,21,24,28,30,35,36,39,40,42,45,52,56,60,63,70,72};
int goal, sizeIndex = 29, count = 0, i;
/* index work out */
for (i = 0; i < sizeIndex; ++i) {
  index[i]=LCM/(index[i]*index[i]);
}
/* goal calc */
goal = LCM/2-LCM/(2*2)-LCM/(3*3);
printf("\ngoal = %d", goal);
for (i = 0; i < sizeIndex; ++i) {
  count+=recursSearch(goal, 0, index, i, sizeIndex-1, sizeIndex);
}
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", time);
printf("\nThere are %d combinations to form 1/2 using up to 80.", count);
printf("\n");
return 0;
}
/******************************************************************************/
void printAnswer(int *index, int size, int count, int *indexStep) {
/* this function prints the answer up to size of index
and then it returns */
int i;
printf ("\n");
for (i = 0; i < size; ++i) {
  printf("%d ", index[indexStep[i]]);
}
printf("\tsize = %d\tcount = %d", size, count);
fflush(NULL);
return;
}
/******************************************************************************/
int recursSearch(int goal, int sum, int *index, int i, int depth, int sizeIndex) {
/* this function returns 1 if sum = goal, if sum > goal return 0 otherwise
goes one step deeper */
if (index == NULL) {
  return 0;
}
int j, answer = 0;
sum+=index[i];
if (sum == goal) {
  return 1;
} else if (depth == 0 || sum > goal) {
  return 0;
}
/* otherwise go one step deeper */
for (j = i+1; j < sizeIndex; ++j) {
  answer+=recursSearch(goal, sum, index, j, --depth, sizeIndex);
}
return answer;
}
/******************************************************************************/
