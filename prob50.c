#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX 1000000

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

/* esta função verifica se somaTeste é um numero primo, num vector de primos, com
nPrimos, retorna 1 se primo ou 0 se não primo */
int primeVerificaBooleano (int *vPrimos, int nPrimos, int somaTeste, int start);

/* preenche as balizas por referencia apartir do vector *vPrimos */
void balizarPreenche (int* vPrimos, int nPrimos, int *n10, int *n100, int *n1K, int *n10K, int *n100K);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
int nTeste, *vPrimos, nPrimos = 0, dimVector = MAX/3, mult = 1, booleano;
int nPrimeSomaTamanho, nPrimeSomaTamanhoMax = 0, i, j, somaTeste, somaPrimeMax = 0;
int n10, n100, n1K, n10K, n100K, start;

vPrimos = (int*) calloc (dimVector, sizeof (int));
if (vPrimos == NULL) {
  printf ("\nErro na criação do vector vPrimos.");
  return 0;
}

for (nTeste = 2; nTeste < MAX; nTeste++) {
  booleano = primeTeste (nTeste);
  if (booleano == 1) {
    if (nPrimos < dimVector) {
      vPrimos[nPrimos] = nTeste;
      nPrimos++;
    } else {
      /* neste caso o tamanho do vector primos esta ja cheio */
      mult++;
      dimVector = dimVector * mult;
      vPrimos = (int*) realloc (vPrimos, dimVector*sizeof (int));
      if (vPrimos == NULL) {
        printf ("\nErro na criação do vector vPrimos.");
        return 0;
      }

      /* agora vou guardar os valores normalmente*/
      vPrimos[nPrimos] = nTeste;
      nPrimos++;
    }
  }
}

printf ("\nExistem %d primos menores do que %d.", nPrimos, MAX);
fflush (stdout);
vPrimos = (int*) realloc (vPrimos, nPrimos*sizeof (int));
if (vPrimos == NULL) {
  printf ("\nErro na criação do vector vPrimos.");
  return 0;
}

balizarPreenche (vPrimos, nPrimos, &n10, &n100, &n1K, &n10K, &n100K);

/* agora vou resolver o problema */

for (i = 0; i < nPrimos-1; i++) { /* O(N) */
  /* a soma de um primo e o proprio primo */
  nPrimeSomaTamanho = 1;
  if (nPrimeSomaTamanho > nPrimeSomaTamanhoMax) {
    nPrimeSomaTamanhoMax = nPrimeSomaTamanho;
    somaPrimeMax = vPrimos[i];
  }
  somaTeste = vPrimos[i];

  for (j = i+1; j < nPrimos; j++) { /* O(N) */
    nPrimeSomaTamanho++;
    somaTeste = somaTeste + vPrimos[j];
    if (somaTeste > (MAX-1) ) {
      break;
    }
    /* maxPrimo para 100K, como é uma função crescente escuso de comparar
    restantes valores para tras */
    if (somaTeste < 92951) {
      continue;
    }


    if (somaTeste < 10) {
      start = 0;
    } else if (somaTeste > 10 && somaTeste < 100) {
      start = n10;
    } else if (somaTeste > 100 && somaTeste < 1000) {
      start = n100;
    } else if (somaTeste > 1000 && somaTeste < 10000) {
      start = n1K;
    } else if (somaTeste > 10000 && somaTeste < 100000) {
      start = n10K;
    } else if (somaTeste > 100000) {
      start = n100K;
    }

    if (somaTeste < 953) {
      continue;
    }

    booleano = primeVerificaBooleano (vPrimos, nPrimos, somaTeste, start); /* O (N) */

    if (booleano == 1) {
      /* neste caso a soma é um número primo */
      if (nPrimeSomaTamanho > nPrimeSomaTamanhoMax) {
        nPrimeSomaTamanhoMax = nPrimeSomaTamanho;
        somaPrimeMax = somaTeste;
      }
    }
  }

}

free (vPrimos);

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nPrimo com maximo numero de termos: %d com %d termos.\n", somaPrimeMax, nPrimeSomaTamanhoMax);
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

int primeVerificaBooleano (int *vPrimos, int nPrimos, int somaTeste, int start) {
/* esta função verifica se somaTeste é um numero primo, num vector de primos, com
nPrimos, retorna 1 se primo ou 0 se não primo */

int i;

for (i = start; i < nPrimos; i++) {
  if (somaTeste == vPrimos[i]) {
    return 1;
  }
  if (vPrimos[i] > somaTeste) {
    break;
  }
}

/* se chega aqui e porque não e primo */
return 0;

}

/******************************************************************************/

void balizarPreenche (int* vPrimos, int nPrimos, int *n10, int *n100, int *n1K, int *n10K, int *n100K) {
/* preenche as balizas por referencia apartir do vector *vPrimos */

int i, iMemoria;

for (i = 0; i < nPrimos; i++) {
  if (vPrimos[i] > 10) {
    *n10 = i;
    iMemoria = i;
    break;
  }
}

for (i = iMemoria; i < nPrimos; i++) {
  if (vPrimos[i] > 100) {
    *n100 = i;
    iMemoria = i;
    break;
  }
}

for (i = iMemoria; i < nPrimos; i++) {
  if (vPrimos[i] > 1000) {
    *n1K = i;
    iMemoria = i;
    break;
  }
}

for (i = iMemoria; i < nPrimos; i++) {
  if (vPrimos[i] > 10000) {
    *n10K = i;
    iMemoria = i;
    break;
  }
}

for (i = iMemoria; i < nPrimos; i++) {
  if (vPrimos[i] > 100000) {
    *n100K = i;
    iMemoria = i;
    break;
  }
}

return;
}

/******************************************************************************/
