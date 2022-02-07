#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabdispersao.h"
#define MAX 50000000
#define DIM 2500
#define SIZE MAX/10

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int maxPrimo, booleano, nPrimos = 0, n, mult = 1, *primoV, i, j, k;
long long int numero, *square, *triple, *quadruple;
int count = 0;
tabela_dispersao*td;
char *str;

td = tabela_nova(MAX/20, hash_djbm);
if (td == NULL){
  printf ("\nOcorreu uma falha a criar a tabela de dispersao.");
}

maxPrimo = sqrt (MAX-pow(2,4)-pow(2,3));

primoV = (int*) calloc (DIM, sizeof (int));
if (primoV == NULL) {
  printf ("\nOcorreu um erro a criar o vector primoV.");
  return 0;
}

/* tarefa nº 1: criar um vector de primos < max */
for (n = 2; n < maxPrimo+1; n++) {
  booleano = primeTeste (n);
  if (booleano == 1) {
		/* situação de limite execedido */
    if (nPrimos == (mult*DIM)) {
      mult++;
      printf ("\nHouve excedimento de limite, teve de ser feito um realloc.");
      primoV = (int*) realloc (primoV, (mult*DIM)*sizeof (int));
      if (primoV == NULL) {
        printf ("\nHouve um erro na realocagem do vector primoV.");
        return 0;
      }
    }
    /* actualizacao de valores */
    primoV[nPrimos] = n;
    nPrimos++;
    continue;
  }
}

square = (long long int*) calloc (nPrimos, sizeof (long long int));
triple = (long long int*) calloc (nPrimos, sizeof (long long int));
quadruple = (long long int*) calloc (nPrimos, sizeof (long long int));
if (square == NULL || triple == NULL || quadruple == NULL) {
  printf ("\nOcorreu uma falha a criar os vector auxiliares.");
  return 0;
}
for (i = 0; i < nPrimos; i++) {
  square[i] = pow(primoV[i],2);
  triple[i] = pow(primoV[i],3);
  quadruple[i] = pow(primoV[i],4);
}
for (i = nPrimos-1; i > -1; i--) {
	for (j = 0; j < nPrimos; j++) {
    numero = triple[j] + quadruple[i];
		if (numero > MAX) {
			break;
		}
		for (k = 0; k < nPrimos; k++) {
      numero = triple[j] + quadruple[i] + square[k];
			if (numero < MAX) {
        /* temos agora de verificar se ha duplicacao de valores */
        str = (char*) calloc (11, sizeof (char));
        if (str == NULL) {
          printf ("\nOcorreu uma falha a criar o vector str.");
          return 0;
        }
        sprintf (str, "%lld", numero);
        booleano = tabela_existe(td, str);
        if (booleano == TABDISPERSAO_NAOEXISTE) {
          /*printf ("\nVamos agora inserir o valor %d.", numero);*/
          booleano = tabela_insere(td, str, str);
          if (booleano == TABDISPERSAO_ERRO || booleano == TABDISPERSAO_INVALIDA) {
            printf ("\nOcorreu um erro na insercao do valor na tabela.");
            return 0;
          }
          count++;
        }
			} else {
				break;
			}
		}
	}
}
free (primoV);
free (square);
free (triple);
free (quadruple);
booleano = tabela_esvazia(td);
if (booleano == TABDISPERSAO_INVALIDA) {
  printf ("\nOcorreu um erro a apagar a tabela.");
}
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nExistem  %d numeros abaixo de %d.", count, MAX);
printf ("\n");
return 0;
}
/******************************************************************************/
int primeTeste (int nTeste) {
/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int i;
if (nTeste <= 1) {
	return 0;
}
if (nTeste  == 2) {
	return 1;
} else if (nTeste % 2 == 0) {
	return 0;
}
for (i = 3; i < sqrt(nTeste+1); i = i+2) {
	if (nTeste % i == 0) {
		return 0;
	}
}
/* se chega aqui é porque é um número primo */
return 1;
}
/******************************************************************************/
