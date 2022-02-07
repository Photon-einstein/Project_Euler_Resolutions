#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 1000
#define ANSWER 4

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

/* faz a factorizacao de um numero nTeste, e guarda os numeros primos num vector,
produzido dinamicamente, alem disso devolve por referencia em n o numero de primos
que factorizou o numero */
void factorizacaoVecProduz (int nTeste, int *vPrimos, int nPrimos, int *n);


int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
int nTeste = 2, booleano, dimV, mult = 1, i;
int *vPrimos, nPrimos = 0, *factorizacao, n, dif;
int resposta[ANSWER] = {0}, passoResposta = 0, found = 0;

dimV = mult*DIM;
vPrimos = (int*) calloc (dimV, sizeof(int));
if (vPrimos == NULL) {
  printf ("\nOcorreu uma falha na alocação de memória.");
  return 0;
}

while (found == 0) {

  booleano = primeTeste (nTeste);

  /* caso o numero seja um primo e guardado num vector */
  if (booleano == 1 && nPrimos < dimV) {
    vPrimos[nPrimos] = nTeste;
    nPrimos++;
    nTeste++;
    continue;
  } else if (booleano == 1 && nPrimos == dimV) {
    mult++;
    dimV = mult*DIM;
    vPrimos = (int*) realloc (vPrimos, dimV*sizeof(int));
    if (vPrimos == NULL) {
      printf ("\nOcorreu uma falha na alocação de memória.");
      return 0;
    }
    vPrimos[nPrimos] = nTeste;
    nPrimos++;
    nTeste++;
    continue;
  }

  /* se chega aqui é porque nTeste não e um numero primo */
  factorizacaoVecProduz (nTeste, vPrimos, nPrimos, &n);

  if (n != ANSWER) {
    nTeste++;
    continue;
  }

  /* se chega aqui é porque o numero e factorizado com 4 primos */
  if (passoResposta == 0) {
    /* primeiro valor da serie a ser inserido */
    resposta[passoResposta] = nTeste;
    passoResposta++;
    nTeste++;
    continue;
  }

  /* se chega aqui e porque não e o primeiro numero da resposta, tenho de verificar
  se o nTeste e consecutivo */
  dif = nTeste - resposta[passoResposta-1];

  if (dif == 1 && passoResposta < (ANSWER-1) ) {
    /* neste caso são numeros consecutivos e ainda não cheguei ao 4 numero */
    resposta[passoResposta] = nTeste;
    passoResposta++;
    nTeste++;
    continue;
  } else if (dif == 1) {
    /* já cheguei ao fim do problema com este valor */
    resposta[passoResposta] = nTeste;
    passoResposta++;
    found = 1;
  } else {
    for (i = 0; i < ANSWER; i++) {
      resposta[i] = 0;
    }
    passoResposta = 0;
    /* primeiro valor da serie a ser inserido */
    resposta[passoResposta] = nTeste;
    passoResposta++;
  }

  nTeste++;
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nNúmero igual a %d.\n", resposta[0]);
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

void factorizacaoVecProduz (int nTeste, int *vPrimos, int nPrimos, int *n) {
/* faz a factorizacao de um numero nTeste, e guarda os numeros primos num vector,
produzido dinamicamente, alem disso devolve por referencia em n o numero de primos
que factorizou o numero */

int nTesteM = nTeste, *vectorPrimoFac, nP = 0, i, mult = 1, repeat = 0, j;

vectorPrimoFac = (int*) calloc (DIM*mult, sizeof (int));
if (vectorPrimoFac == NULL) {
  printf ("\nOcorreu uma falha na alocação de memória na função factorizacaoVecProduz.");
  return;
}

while (nTeste != 1) {
  repeat = 0;

  for (i = 0; i < nPrimos; i++) {
    if (nTeste % vPrimos[i] == 0) {
      nTeste = nTeste / vPrimos[i];
      /* vou agora verificar se aquele primo já consta do vectorPrimoFac */

      /* caso em que e o primeiro primo a ser inserido */
        if (nP == 0) {
          vectorPrimoFac [nP] = vPrimos[i];
          nP++;
        }

      for (j = 0; j < nP; j++) {
        if (vectorPrimoFac[j] == vPrimos[i]) {
          repeat = 1;
          break;
        }
      }

      if (repeat != 1) {
          if (nP < (DIM*mult)) {
            vectorPrimoFac [nP] = vPrimos[i];
            nP++;
          } else if (nP == (DIM*mult) ) {
            mult++;
            vectorPrimoFac = (int*) realloc (vectorPrimoFac, DIM*mult*sizeof (int));
            if (vectorPrimoFac == NULL) {
              printf ("\nOcorreu uma falha na alocação de memória na função factorizacaoVecProduz.");
              return;
            }
            vectorPrimoFac [nP] = vPrimos[i];
            nP++;
        }
      }

      /* tenho agora de recomecar pelos primos mais baixos */
      break;
    }
  }

}

free (vectorPrimoFac);
*n = nP;
}

/******************************************************************************/
