#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 10000

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

/* devolve -1 se numero fabricado menor que nTeste, 0 se igual e 1 se maior que nTeste */
int verificaConjectura (int *vPrimos, int i, int j, int nTeste);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */

int i, j, booleano, ok, nTeste = 3;
int booleanoFinde = 0;
int nPrimos = 0;
int *vPrimos, dimPrimo = DIM, mult = 1;

vPrimos = (int*) calloc (mult*DIM, sizeof (int));
if (vPrimos == NULL) {
  printf ("\nFalha na alocação do vector de primos.");
  return 0;
}

while (booleanoFinde == 0) {

  /* teste para ver se o nTeste é primo, se sim guarda-o no vector */
  booleano = primeTeste (nTeste);
  if (booleano == 1 && nPrimos < dimPrimo) {
    vPrimos[nPrimos] = nTeste;
    nPrimos++;
    nTeste = nTeste + 2;
    continue;
  } else if ((booleano == 1) && (nPrimos == dimPrimo)) {
    mult++;
    vPrimos = (int*) realloc (vPrimos, mult*DIM*sizeof (int));
    if (vPrimos == NULL) {
      printf ("\nFalha na realocação do vector de primos.");
      return 0;
    }
    vPrimos[nPrimos] = nTeste;
    nPrimos++;
    nTeste = nTeste + 2;
    continue;
  }

/* se chega aqui é porque o numero é impar mas não e primo */

for (i = 0; i < nPrimos; i++) {
  /* condição de arranque do teste */
  j = 1;
  ok = 0;

  while (1) {
    booleano = verificaConjectura (vPrimos, i, j, nTeste);
    if (booleano == -1) {
      /* neste caso o numero fabricado e menor que nTeste */
      j++;
      continue;
    } else if (booleano == 0) {
      /* neste caso o numero e igual a nTeste */
      ok = 1;
      break;
    } else {
      /* se chega aqui e porque o numero fabricado e maior que nTeste */
      break;
    }
    j++;
  }

  if (ok == 1) {
    break;
  }
}

  /* teste a ver se o numero nTeste teve um match com ok = 1*/
  if (ok == 0) {
    break;
  }
  nTeste = nTeste + 2;
}

free (vPrimos);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nConjectura falhou em  %d.\n", nTeste);
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

int verificaConjectura (int *vPrimos, int i, int j, int nTeste) {
/* devolve -1 se numero fabricado menor que nTeste, 0 se igual e 1 se maior que nTeste */


int numero;

numero = vPrimos[i] + 2 * pow (j, 2);

if (numero < nTeste) {
  return -1;
} else if (numero == nTeste) {
  return 0;
} else {
  return 1;
}

}

/******************************************************************************/
