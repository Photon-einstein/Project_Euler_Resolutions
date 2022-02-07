#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/* cria dinamicamente um nome e devolve o nome lido no ficheiro */
/* se o ficheiro chega ao fim a flag *booleanoCheio = 1 */
char* lerNome (FILE *f, int *booleanoCheio);

/* calcula o score correspondente àquela string, e devolve o inteiro */
/* retorn 0 ou o valor se ok */
int scoreCalc (char *str);

/* determina se o score é um triangleWorld ou não. Se sim devolve 1, se não
devolve 0 */
int booleanoTriangleWord (int score);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
FILE *f;
int booleanoCheio = 0;
int booleano;
int triangWord = 0;
int score;
char *str;



f = fopen ("words.txt", "r");
if (f == NULL) {
	printf ("\nOcorreu uma falha a abrir o ficheiro.");
	return 0;
}

while (1) {
	str = lerNome (f, &booleanoCheio);
	if (str == NULL && booleanoCheio == 0) {
		printf ("\nErro na função leitura.");
		return 0;
	}

	/* se chegou ao fim do ficheiro, neste caso já não vou ler mais nenhum nome */
	if (str == NULL || booleanoCheio == 1) {
		break;
	}

	score = scoreCalc (str);
	if (score == 0) {
		free (str);
		break;
	}



	booleano = booleanoTriangleWord (score);
	if (booleano == 0) {
		free (str);
		continue;
	} else if (booleano == 1) {
		triangWord++;
		printf ("\nTriangleWord Nª %d: %s", triangWord, str);

		free (str);
	}


}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nO número de triangleWorld é de %d.\n", triangWord);
return 0;
}

/******************************************************************************/

char* lerNome (FILE *f, int *booleanoCheio) {
/* cria dinamicamente um nome e devolve o nome lido no ficheiro */
/* se o ficheiro chega ao fim a flag *booleanoCheio = 1 */

if (f == NULL) {
	return NULL;
}

char *str;

str = (char*) calloc (40, sizeof (char));
if (str == NULL) {
	return NULL;
}

int contadorAspas = 0;
int i = 0;
char cActual;

while (contadorAspas < 2) {
	if ( (cActual = fgetc(f) ) == EOF) {
		*booleanoCheio = 1;
		return NULL;
	}


	if (cActual == '"') {
		contadorAspas++;
		continue;
	}

	str[i] = cActual;
	i++;
}

/* leitura da virgula */
if ( (cActual = fgetc(f) ) == EOF) {
	*booleanoCheio = 1;
}

/* se chega aqui é porque esta tudo ok */
return str;
}

/******************************************************************************/

int scoreCalc (char *str) {
/* calcula o score correspondente àquela string, e devolve o inteiro */
/* retorn 0 ou o valor se ok */

if (str == NULL) {
	return 0;
}

int i, score = 0;

for (i = 0; i < strlen(str); i++) {
	score = score + (int)str[i] - (int)'A' + 1;
}

return score;
}

/******************************************************************************/

int booleanoTriangleWord (int score) {
/* determina se o score é um triangleWorld ou não. Se sim devolve 1, se não
devolve 0 */

if (score <= 0) {
	return 0;
}

int t, i = 1;

while (1) {
	t = i*(i+1)/2;
	if (t == score) {
		return 1;
	} else if (t > score) {
		return 0;
	}
	i++;
}

}

/******************************************************************************/
