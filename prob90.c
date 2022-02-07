#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabdispersao.h"
#define CUBEMIN 0
#define CUBEMAX 9
#define MAX 10
#define CUBEFACES 6
#define NSQUARES 9
#define SIZE 10000

/* this function generates a cube whith cubeFaces*/
int* cubeGenerator (int *index, int cubeFaces, int *sizeCube);

/* this function checks if this 2 cubes make all the square number until 100,
if yes then it return 1, if no, it returns 0 */
int squareCubeCheck (int *cube1, int *cube2, int sizeCube1, int sizeCube2, int nSquares);

/* this function generates a char vector from a int vetor, if ok or NULL if There
was a problem */
char* charGenerator (int *cube, int sizeCube);

/* this function makes the sorte with bubble sort, and then returns to the main */
void sorting (int *cube, int sizeCube);

/* this function makes a new cube including the 6 or 9 duplicated, and it returns
also the new dim */
int* resizeCube (int *index, int cubeFaces, int *sizeCube);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* task to check */
int *cube1, *cube2, index1[CUBEFACES], index2[CUBEFACES], sizeCube1, sizeCube2;
int booleano, answer = 0, i;
tabela_dispersao*td;
char *str1, *str2, *str;

td = tabela_nova(SIZE, hash_djbm);
if (td == NULL) {
	printf ("\nThere was an error in the generation of the hash table.");
	return 0;
}
/* we are no going to generate the faces of cube 1 and 2 */
/* cube 1 generation */
for (index1[0] = CUBEMIN; index1[0] < MAX-5; index1[0]++) {
	for (index1[1] = index1[0]+1; index1[1] < MAX-4; index1[1]++) {
		for (index1[2] = index1[1]+1; index1[2] < MAX-3; index1[2]++) {
			for (index1[3] = index1[2]+1; index1[3] < MAX-2; index1[3]++) {
				for (index1[4] = index1[3]+1; index1[4] < MAX-1; index1[4]++) {
					for (index1[5] = index1[4]+1; index1[5] < MAX; index1[5]++) {
						/* cube 2 generation */
						for (index2[0] = CUBEMIN; index2[0] < MAX-5; index2[0]++) {
							for (index2[1] = index2[0]+1; index2[1] < MAX-4; index2[1]++) {
								for (index2[2] = index2[1]+1; index2[2] < MAX-3; index2[2]++) {
									for (index2[3] = index2[2]+1; index2[3] < MAX-2; index2[3]++) {
										for (index2[4] = index2[3]+1; index2[4] < MAX-1; index2[4]++) {
											for (index2[5] = index2[4]+1; index2[5] < MAX; index2[5]++) {
												cube1 = cubeGenerator (index1, CUBEFACES, &sizeCube1);
												cube2 = cubeGenerator (index2, CUBEFACES, &sizeCube2);
												if (cube1 == NULL || cube2 == NULL) {
													printf ("\nIt happened a problem in the cubeGenerator function.");
													return 0;
												}
												/* check if this 2 cubes make all the square number until 100 */
												booleano = squareCubeCheck (cube1, cube2, sizeCube1, sizeCube2, NSQUARES);
												if (booleano == 1) {
													sorting (cube1, sizeCube1);
													sorting (cube2, sizeCube2);
													str1 = charGenerator (cube1, sizeCube1);
													str2 = charGenerator (cube2, sizeCube2);
													str = (char*) calloc ((sizeCube1 + sizeCube2 + 4), sizeof (char));
													if (str1 == NULL || str2 == NULL || str == NULL) {
														printf ("\nThere was a problem in the charGenerator function.");
														return 0;
													}
													strcpy(str, str1);
													strcat(str, str2);
													booleano = tabela_existe(td, str);
													if (booleano == TABDISPERSAO_NAOEXISTE) {
														answer++;
														/*printf ("\nCube1 = %s\tCube2 = %s", str1, str2);*/
														booleano = tabela_insere(td, str, str);
														if (booleano == TABDISPERSAO_ERRO || booleano == TABDISPERSAO_INVALIDA) {
															printf ("\nThere was a problem in the function tabela insere.");
															return 0;
														}
													}
													/* we are now going to put the inverse also, the mirror solution*/
													free (str);
													str = (char*) calloc ((sizeCube1 + sizeCube2 + 4), sizeof (char));
													if (str1 == NULL || str2 == NULL || str == NULL) {
														printf ("\nThere was a problem in the charGenerator function.");
														return 0;
													}
													strcpy(str, str2);
													strcat(str, str1);
													booleano = tabela_existe(td, str);
													if (booleano == TABDISPERSAO_NAOEXISTE) {
														booleano = tabela_insere(td, str, str);
														if (booleano == TABDISPERSAO_ERRO || booleano == TABDISPERSAO_INVALIDA) {
															printf ("\nThere was a problem in the function tabela insere.");
															return 0;
														}
													}

													free (str1);
													free (str2);
													free (str);
												}
												free (cube1);
												free (cube2);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
booleano = tabela_esvazia(td);
if (booleano == TABDISPERSAO_INVALIDA) {
	printf ("\nThere was a problem with the function tabela esvazia.");
	return 0;
}
/* end of task */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf ("\nThere are %d diferent cube combinations.", answer);
printf ("\n");
return 0;
}
/******************************************************************************/
int* cubeGenerator (int *index, int cubeFaces, int *sizeCube) {
/* this function generates a cube whith cubeFaces*/
int i, booleano = 0, *cube;

cube = (int*) calloc (cubeFaces, sizeof (int));
if (cube == NULL) {
	return NULL;
}
for (i = 0; i < cubeFaces; i++) {
	cube[i] = index[i];
}
*sizeCube = cubeFaces;
return cube;
}
/******************************************************************************/
int squareCubeCheck (int *cube1, int *cube2, int sizeCube1, int sizeCube2, int nSquares) {
/* this function checks if this 2 cubes make all the square number until 100,
if yes then it return 1, if no, it returns 0 */
int i, j, n1, n2, *square, zeroBooleano = 0;
int *cube11, *cube22, dim1, dim2;
/* rep face check */
for (i = 0; i < sizeCube1-1; i++) {
	for (j = i+1; j < sizeCube1; j++) {
		if (cube1[i] == cube1[j]) {
			return 0;
		}
	}
}
for (i = 0; i < sizeCube2-1; i++) {
	for (j = i+1; j < sizeCube2; j++) {
		if (cube2[i] == cube2[j]) {
			return 0;
		}
	}
}
/* now we are going to test the squares of each face1*face2 */
square = (int*) calloc (nSquares, sizeof (int));
if (square == NULL) {
	printf ("\nThe was a problem in the memory allocation of square.");
	return 0;
}

cube11 = resizeCube (cube1, sizeCube1, &dim1);
cube22 = resizeCube (cube2, sizeCube2, &dim2);
if (cube11 == NULL || cube22 == NULL) {
	return 0;
}

for (i = 0; i < dim1; i++) {
	for (j = 0; j < dim2; j++) {
		n1 = cube11[i]*10 + cube22[j];
		n2 = cube22[j]*10 + cube11[i];
		if (n1 == 1 || n2 == 1) {
			square[0] = 1;
		} else if (n1 == 4 || n2 == 4) {
			square[1] = 1;
		} else if (n1 == 9 || n2 == 9) {
			square[2] = 1;
		} else if (n1 == 16 || n2 == 16) {
			square[3] = 1;
		} else if (n1 == 25 || n2 == 25) {
			square[4] = 1;
		} else if (n1 == 36 || n2 == 36) {
			square[5] = 1;
		} else if (n1 == 49 || n2 == 49) {
			square[6] = 1;
		} else if (n1 == 64 || n2 == 64) {
			square[7] = 1;
		} else if (n1 == 81 || n2 == 81) {
			square[8] = 1;
		}
	}
}
free (cube11);
free (cube22);
for (i = 0; i < nSquares; i++) {
	if (square[i] == 0) {
		free (square);
		return 0;
	}
}
/* if it reaches here then it generates all square numbers */
free (square);
return 1;
}
/******************************************************************************/
char* charGenerator (int *cube, int sizeCube) {
/* this function generates a char vector from a int vetor, if ok or NULL if there
was a problem */
int maxDim = 100000, i, number = 0;
char *str;

for (i = sizeCube-1; i > -1; i--) {
	number = cube[i]*maxDim+number;
	maxDim = maxDim / 10;
}
str = (char*) calloc (sizeCube, sizeof (char));
if (str == NULL) {
	return NULL;
}
sprintf (str, "%d", number);
return str;
}
/******************************************************************************/
void sorting (int *cube, int sizeCube) {
/* this function makes the sorte with bubble sort, and then returns to the main */
int i, j, aux;

for (i = 0; i < sizeCube-1; i++) {
	for (j = i+1; j < sizeCube; j++) {
		if (cube[i] > cube[j]) {
			/* aux = i */
			aux = cube[i];
			/* i = j */
			cube[i] = cube [j];
			/* j = aux */
			cube[j] = aux;
		}
	}
}
return;
}
/******************************************************************************/
int* resizeCube (int *index, int cubeFaces, int *sizeCube) {
	/* this function generates a cube whithe cubeFaces+1, and then checks if
	6 or 9 are there, if yes, then it duplicate the number, and fill the cube, if no
	then is make a realloc and the function returns the vector and the size of the
	new cube */
	int i, booleano = 0, *cubeA, bool6 = 0, bool9 = 0, pos, j, dim;
	/* checks if 6 or 9 are there */
	for (i = 0; i < cubeFaces; i++) {
		if (index[i] == 6 || index[i] == 9) {
			booleano = 1;
			break;
		}
	}

	if (booleano == 0) {
		/* no 6 and 9 are not there */
		cubeA = (int*) calloc (cubeFaces, sizeof (int));
		if (cubeA == NULL) {
			return NULL;
		}
		for (i = 0; i < cubeFaces; i++) {
			cubeA[i] = index[i];
		}
		*sizeCube = cubeFaces;
		return cubeA;
	} else {
		/* 6 or 9 are there */
		dim = cubeFaces+1;
		cubeA = (int*) calloc (dim, sizeof (int));
		if (cubeA == NULL) {
			return NULL;
		}
		for (i = 0; i < cubeFaces; i++) {
			cubeA[i] = index[i];
			if (cubeA[i] == 6) {
				bool6 = 1;
			} else if (cubeA[i] == 9) {
				bool9 = 1;
			}
		}
		/* case in wich 6 and 9 are there */
		if (bool6 == 1 && bool9 == 1) {
			cubeA = (int*) realloc (cubeA, cubeFaces*sizeof (int));
			if (cubeA == NULL) {
				return NULL;
			}
			*sizeCube = cubeFaces;
			return cubeA;
		} else if (bool6 == 1 && bool9 == 0) {
			/* only 6 is in the cube, I have to replicate 9 */
			cubeA[dim-1] = 9;
			*sizeCube = cubeFaces+1;
			return cubeA;
		} else if (bool6 == 0 && bool9 == 1) {
			/* only 9 is here, I have to insert 6 */
			cubeA[dim-1] = 6;
			*sizeCube = cubeFaces+1;
			return cubeA;
		}
	}
}
/******************************************************************************/
