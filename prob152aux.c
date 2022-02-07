#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define GOAL 2
#define LCM 1073217600

int main () {
clock_t start, end;
double time;
start = clock();
/* work to verify */
int index[29]={4,5,6,7,8,9,10,12,13,14,15,18,20,21,24,28,30,35,36,39,40,42,45,52,56,60,63,70,72};
int goal, sizeIndex = 29, goalStep[22]={0}, indexStep[22]={0}, count = 0, i;
/* index work out */
for (i = 0; i < sizeIndex; ++i) {
  index[i]=LCM/(index[i]*index[i]);
}
/* goal calc */
goal = LCM/2-LCM/(2*2)-LCM/(3*3);
/* for 1 */
for (indexStep[0] = 0; indexStep[0] < sizeIndex; ++indexStep[0]) {
goalStep[0]=index[indexStep[0]];
/* for 2 */
for (indexStep[1] = indexStep[0]+1; indexStep[1] < sizeIndex; ++indexStep[1]) {
goalStep[1]=goalStep[0]+index[indexStep[1]];
/* for 3 */
for (indexStep[2] = indexStep[1]+1; indexStep[2] < sizeIndex; ++indexStep[2]) {
goalStep[2]=goalStep[1]+index[indexStep[2]];
/* for 4 */
for (indexStep[3] = indexStep[2]+1; indexStep[3] < sizeIndex; ++indexStep[3]) {
goalStep[3]=goalStep[2]+index[indexStep[3]];
/* overflow */
if (goalStep[3] > goal) {
  continue;
} else if (goalStep[3] == goal) {
  ++count;
  continue;
}
/* for 5 */
for (indexStep[4] = indexStep[3]+1; indexStep[4] < sizeIndex; ++indexStep[4]) {
goalStep[4]=goalStep[3]+index[indexStep[4]];
/* overflow */
if (goalStep[4] > goal) {
  continue;
} else if (goalStep[4] == goal) {
  ++count;
  continue;
}
/* for 6 */
for (indexStep[5] = indexStep[4]+1; indexStep[5] < sizeIndex; ++indexStep[5]) {
goalStep[5]=goalStep[4]+index[indexStep[5]];
/* overflow */
if (goalStep[5] > goal) {
  continue;
} else if (goalStep[5] == goal) {
  ++count;
  continue;
}
/* for 7 */
for (indexStep[6] = indexStep[5]+1; indexStep[6] < sizeIndex; ++indexStep[6]) {
goalStep[6]=goalStep[5]+index[indexStep[6]];
/* overflow */
if (goalStep[6] > goal) {
  continue;
} else if (goalStep[6] == goal) {
  ++count;
  continue;
}
/* for 8 */
for (indexStep[7] = indexStep[6]+1; indexStep[7] < sizeIndex; ++indexStep[7]) {
goalStep[7]=goalStep[6]+index[indexStep[7]];
/* overflow */
if (goalStep[7] > goal) {
  continue;
} else if (goalStep[7] == goal) {
  ++count;
  continue;
}
/* for 9 */
for (indexStep[8] = indexStep[7]+1; indexStep[8] < sizeIndex; ++indexStep[8]) {
goalStep[8]=goalStep[7]+index[indexStep[8]];
/* overflow */
if (goalStep[8] > goal) {
  continue;
} else if (goalStep[8] == goal) {
  ++count;
  continue;
}
/* for 10 */
for (indexStep[9] = indexStep[8]+1; indexStep[9] < sizeIndex; ++indexStep[9]) {
goalStep[9]=goalStep[8]+index[indexStep[9]];
/* overflow */
if (goalStep[9] > goal) {
  continue;
} else if (goalStep[9] == goal) {
  ++count;
  continue;
}
/* for 11 */
for (indexStep[10] = indexStep[9]+1; indexStep[10] < sizeIndex; ++indexStep[10]) {
goalStep[10]=goalStep[9]+index[indexStep[10]];
/* overflow */
if (goalStep[10] > goal) {
  continue;
} else if (goalStep[10] == goal) {
  ++count;
  continue;
}
/* for 12 */
for (indexStep[11] = indexStep[10]+1; indexStep[11] < sizeIndex; ++indexStep[11]) {
goalStep[11]=goalStep[10]+index[indexStep[11]];
/* overflow */
if (goalStep[11] > goal) {
  continue;
} else if (goalStep[11] == goal) {
  ++count;
  continue;
}
/* for 13 */
for (indexStep[12] = indexStep[11]+1; indexStep[12] < sizeIndex; ++indexStep[12]) {
goalStep[12]=goalStep[11]+index[indexStep[12]];
/* overflow */
if (goalStep[12] > goal) {
  continue;
} else if (goalStep[12] == goal) {
  ++count;
  continue;
}
/* for 14 */
for (indexStep[13] = indexStep[12]+1; indexStep[13] < sizeIndex; ++indexStep[13]) {
goalStep[13]=goalStep[12]+index[indexStep[13]];
/* overflow */
if (goalStep[13] > goal) {
  continue;
} else if (goalStep[13] == goal) {
  ++count;
  continue;
}
/* for 15 */
for (indexStep[14] = indexStep[13]+1; indexStep[14] < sizeIndex; ++indexStep[14]) {
goalStep[14]=goalStep[13]+index[indexStep[14]];
/* overflow */
if (goalStep[14] > goal) {
  continue;
} else if (goalStep[14] == goal) {
  ++count;
  continue;
}
/* for 16 */
for (indexStep[15] = indexStep[14]+1; indexStep[15] < sizeIndex; ++indexStep[15]) {
goalStep[15]=goalStep[14]+index[indexStep[15]];
/* overflow */
if (goalStep[15] > goal) {
  continue;
} else if (goalStep[15] == goal) {
  ++count;
  continue;
}
/* for 17 */
for (indexStep[16] = indexStep[15]+1; indexStep[16] < sizeIndex; ++indexStep[16]) {
goalStep[16]=goalStep[15]+index[indexStep[16]];
/* overflow */
if (goalStep[16] > goal) {
  continue;
} else if (goalStep[16] == goal) {
  ++count;
  continue;
}
/* for 18 */
for (indexStep[17] = indexStep[16]+1; indexStep[17] < sizeIndex; ++indexStep[17]) {
goalStep[17]=goalStep[16]+index[indexStep[17]];
/* overflow */
if (goalStep[17] > goal) {
  continue;
} else if (goalStep[17] == goal) {
  ++count;
  continue;
}
/* for 19 */
for (indexStep[18] = indexStep[17]+1; indexStep[18] < sizeIndex; ++indexStep[18]) {
goalStep[18]=goalStep[17]+index[indexStep[18]];
/* overflow */
if (goalStep[18] > goal) {
  continue;
} else if (goalStep[18] == goal) {
  ++count;
  continue;
}
/* for 20 */
for (indexStep[19] = indexStep[18]+1; indexStep[19] < sizeIndex; ++indexStep[19]) {
goalStep[19]=goalStep[18]+index[indexStep[19]];
/* overflow */
if (goalStep[19] > goal) {
  continue;
} else if (goalStep[19] == goal) {
  ++count;
  continue;
}
/* for 21 */
for (indexStep[20] = indexStep[19]+1; indexStep[20] < sizeIndex; ++indexStep[20]) {
goalStep[20]=goalStep[19]+index[indexStep[20]];
/* overflow */
if (goalStep[20] > goal) {
  continue;
} else if (goalStep[20] == goal) {
  ++count;
  continue;
}
/* for 22 */
for (indexStep[21] = indexStep[20]+1; indexStep[21] < sizeIndex; ++indexStep[21]) {
goalStep[21]=goalStep[20]+index[indexStep[21]];
/* overflow */
if (goalStep[21] > goal) {
  continue;
} else if (goalStep[21] == goal) {
  ++count;
  continue;
}}}}}}}}}}}}}}}}}}}}}}}
/* end of the work */
end = clock();
time = (double)(end - start) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", time);
printf("\nThere are %d combinations to form 1/2 using up to 80.", count);
printf("\n");
return 0;
}
/******************************************************************************/
