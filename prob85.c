#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define GOAL 2000000
#define COMP 100

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int comprimento = 3, largura, found = 0, count, minDiff = GOAL;
int x, y, diff, area, exitF;

do {
for (largura = 1; largura < comprimento; largura++) {
	/* teste do rectangulo de comprimento e largura */
	count = 0;
	exitF = 0;
	count = comprimento*(comprimento+1)*largura*(largura+1)/4;
		if (exitF == 1) {
			break;
		}
	/*printf ("\ncomp = %d, largura = %d e nº rect = %d", comprimento, largura, count);*/
	/* agora vamos calcular a solucao mais proxima */
	diff = GOAL - count;
	if (diff < 0) {
		diff = diff * -1;
	}
	/* vamos verificar se temos um novo minimo */
	if (diff < minDiff) {
		minDiff = diff;
		area = comprimento * largura;
	}
}
	/* condicao de saida */
	if (comprimento > COMP) {
		found = 1;
	}
comprimento++;
} while (found == 0);

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nA area mais proxima de %d rectangulos e de %d.", GOAL, area);
printf ("\n");
return 0;
}
/******************************************************************************/
