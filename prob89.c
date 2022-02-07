#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZEDATA 1000
typedef struct {
	char *strOld;
	int oldSize;
	char *strNew;
	int newSize;
	int number;
	int savedChar;
} roman;

/* this fill the data in the structure. If there was a problem in the function,
it returns 0, if ok it returns 1 */
int dataCalc (char *fileName, roman *v, int size);

/* this function frees all the memory allocated in the structure vector and then
returns to the main */
void freeMemoryRoman (roman *v, int size);

/* this function calculate the number in decimal contained in a roman numeral, and
returns the value if ok or 0 if there was a problem */
int numCalcDecifer (char *str, int size);

/* this function creates a new char vector with the old size, if in the end the
new vector is with less characters, them is made a calloc.
If the function works fine, it returns 1, if error them returns 0.
This function writes the number in roman numeral in the new char vector.
In the end it makes the calculation of the new size and of the savedChar */
int numberRewrite(roman *v, int index, int maxSize);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* task to check */
char fileName[10] = "roman.txt";
int booleano, i, answer = 0;
roman *v;

v = (roman*) calloc (SIZEDATA, sizeof (roman));
if (v == NULL) {
	printf ("\nError in the memory allocation of the v vector.");
	return 0;
}
booleano = dataCalc (fileName, v, SIZEDATA);
if (booleano == 0) {
	printf ("\nThere was a problem in the dataCalc function.");
	return 0;
}
for (i = 0; i < SIZEDATA; i++) {
	v[i].number = numCalcDecifer (v[i].strOld, v[i].oldSize);
	booleano = numberRewrite(v, i, SIZEDATA);
	if (booleano == 0) {
		printf ("\nThere was a problem in the function rewrite.");
		return 0;
	}

	if (v[i].savedChar != 0) {
		answer = answer + v[i].savedChar;
		/*printf ("\nNumero antigo %s, novo: %s com valor %d e %d salvo.", v[i].strOld, v[i].strNew, v[i].number, v[i].savedChar);*/
	} else {
		/*printf ("\nNumero %s com valor %d.", v[i].strOld, v[i].number);*/
	}
}

freeMemoryRoman (v, SIZEDATA);
/* end of task */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThe number of characters saved by this program is %d.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int dataCalc (char *fileName, roman *v, int size) {
/* this fill the data in the structure. If there was a problem in the function,
it returns 0, if ok it returns 1 */
if (fileName == NULL || v == NULL) {
	return 0;
}
FILE *f;
int count = 0;
char line[40];

f = fopen (fileName, "r");
if (f == NULL) {
	return -1;
}
while (fscanf (f, "%s", line) != EOF) {
	v[count].oldSize = strlen (line);
	v[count].strOld = (char*) calloc (v[count].oldSize+1, sizeof (char));
	strcpy (v[count].strOld, line);
	if (v[count].strOld == NULL) {
		printf ("\nThere was a problem in the memory allocation of the str.");
		return 0;
	}
	/*printf ("\nNumero nº %d com %d caracteres: %s.", count+1, v[count].oldSize , v[count].strOld);*/
	count++;
}
return count;
}
/******************************************************************************/
void freeMemoryRoman (roman *v, int size) {
/* this function frees all the memory allocated in the structure vector and then
returns to the main */
int i;
for (i = 0; i < size; i++) {
	free (v[i].strOld);
	free (v[i].strNew);
}
free (v);
return;
}
/******************************************************************************/
int numCalcDecifer (char *str, int size) {
/* this function calculate the number in decimal contained in a roman numeral, and
returns the value if ok or 0 if there was a problem */
int count = 0, number = 0;

while (count < size) {
	/* subtraction case */
	 if ((count+1) < size) {
		if (str[count] == 'C' && str[count+1] == 'D') {
			/* CD test */
			number = number + 400;
			count = count + 2;
			continue;
		} else if (str[count] == 'C' && str[count+1] == 'M') {
		/* CM test */
			number = number + 900;
			count = count + 2;
			continue;
		} else if (str[count] == 'X' && str[count+1] == 'L') {
		/* XL test */
			number = number + 40;
			count = count + 2;
			continue;
		} else if (str[count] == 'X' && str[count+1] == 'C') {
		/* XC test */
			number = number + 90;
			count = count + 2;
			continue;
		} else if (str[count] == 'I' && str[count+1] == 'V') {
		/* IV test */
			number = number + 4;
			count = count + 2;
			continue;
		} else if (str[count] == 'I' && str[count+1] == 'X') {
		/* IX test */
			number = number + 9;
			count = count + 2;
			continue;
		}
	}
	/* normal case */
	if (str[count] == 'M') {
		/* 1000 test */
			number = number + 1000;
			count++;
			continue;
	} else if (str[count] == 'D') {
		/* 500 test */
			number = number + 500;
			count++;
			continue;
	} else if (str[count] == 'C') {
		/* 100 test */
			number = number + 100;
			count++;
			continue;
	} else if (str[count] == 'L') {
		/* 50 test */
			number = number + 50;
			count++;
			continue;
	} else if (str[count] == 'X') {
		/* 10 test */
			number = number + 10;
			count++;
			continue;
	} else if (str[count] == 'V') {
		/* 500 test */
			number = number + 5;
			count++;
			continue;
	} else if (str[count] == 'I') {
		/* 1 test */
			number++;
			count++;
			continue;
	}
}
return number;
}
/******************************************************************************/
int numberRewrite(roman *v, int index, int maxSize) {
/* this function creates a new char vector with the old size, if in the end the
new vector is with less characters, them is made a calloc.
If the function works fine, it returns 1, if error them returns 0.
This function writes the number in roman numeral in the new char vector.
In the end it makes the calculation of the new size and of the savedChar */
if (v == NULL || index < 0 || index >= maxSize) {
	return 0;
}
int count = 0, number;

number = v[index].number;
v[index].strNew = (char*) calloc (v[index].oldSize, sizeof (char));
if (v[index].strNew == NULL) {
	return 0;
}

while (number != 0) {
	if (number >= 1000) {
		v[index].strNew[count] = 'M';
		number = number - 1000;
		count++;
	} else if (number >= 900) {
		v[index].strNew[count] = 'C';
		v[index].strNew[count+1] = 'M';
		number = number - 900;
		count = count + 2;
	} else if (number >= 500) {
		v[index].strNew[count] = 'D';
		number = number - 500;
		count++;
	} else if (number >= 400) {
		v[index].strNew[count] = 'C';
		v[index].strNew[count+1] = 'D';
		number = number - 400;
		count = count + 2;
	} else if (number >= 100) {
		v[index].strNew[count] = 'C';
		number = number - 100;
		count++;
	} else if (number >= 90) {
		v[index].strNew[count] = 'X';
		v[index].strNew[count+1] = 'C';
		number = number - 90;
		count = count + 2;
	} else if (number >= 50) {
		v[index].strNew[count] = 'L';
		number = number - 50;
		count++;
	} else if (number >= 40) {
		v[index].strNew[count] = 'X';
		v[index].strNew[count+1] = 'L';
		number = number - 40;
		count = count + 2;
	} else if (number >= 10) {
		v[index].strNew[count] = 'X';
		number = number - 10;
		count++;
	} else if (number == 9) {
		v[index].strNew[count] = 'I';
		v[index].strNew[count+1] = 'X';
		number = number - 9;
		count = count + 2;
	} else if (number >= 5) {
		v[index].strNew[count] = 'V';
		number = number - 5;
		count++;
	} else if (number == 4) {
		v[index].strNew[count] = 'I';
		v[index].strNew[count+1] = 'V';
		number = number - 4;
		count = count + 2;
	} else if (number >= 1) {
		v[index].strNew[count] = 'I';
		number--;
		count++;
	}
}
v[index].newSize = count;
if (v[index].oldSize != v[index].newSize) {
	v[index].savedChar = v[index].oldSize - v[index].newSize;
} else {
	v[index].savedChar = 0;
}
return 1;
}
/******************************************************************************/
