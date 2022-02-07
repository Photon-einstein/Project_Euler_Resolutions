#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MIN 1000000

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int comprimento, laltura, m, esquerdo, direito, count = 0, max = 1;
int solucoes [3000] = {0}, passo = 0, largura, altura, soma;

do {
	count = 0;
	for (comprimento = max; comprimento >= 1; comprimento--) {
		if (comprimento == max) {
			for (laltura = 2*comprimento; laltura >= 1; laltura--) {
				m = sqrt (pow(comprimento,2) + pow(laltura, 2));
				/* teste a ver se o valor m e inteiro */
				esquerdo = pow (m,2);
				direito = pow (comprimento,2) + pow (laltura,2);
				if (esquerdo == direito) {
					/* neste caso o valor de m e inteiro */
					soma = 0;
					for (largura = max; largura > 0; largura--) {
						for (altura = largura; altura > 0; altura--) {
								if ((largura + altura) == laltura) {
									soma++;
								} else if ((largura + altura) < laltura) {
									break;
								}
						}
					}
					count = count + soma;
				}
				if (esquerdo > direito) {
					break;
				}
			}
		}  else {
				count = count + solucoes[passo-1];
				break;
		}
	}
/*printf ("\nM a testar = %d com count = %d", max, count);*/
solucoes[passo] = count;
passo++;
/* avancar do ciclo */
if (count <= MIN) {
	max++;
}
} while (count < MIN);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nO valor que primeiro excede %d e M = %d", MIN, max);
printf ("\n");
return 0;
}
/******************************************************************************/
