#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM 1100

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/
int *preencheVectorDigit (int contador, int dim, int nAlg);

/* esta função retorna 1 se os 2 vectores tiverem os mesmos digitos ou 0 se não */
int testaIgualdadeDigitos (int *primo1, int *primo2, int nAlg);

/* esta função preenche o vector resposta com a chave contida no vector respostaIndice*/
void preencheVectorResposta (int *resposta, int *vPrimos, int *respostaIndice);

/* esta função ordena por ordem crescente os 3 numeros contidos no vector resposta */
void ordenaResposta (int *resposta);

/* retorna 1 se a sequencia e aritmetica ou 0 se não */
int checkAritmetic (int *resposta);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
int *resposta, respostaIndice[100] = {0}, nTeste, booleano, i, nRep, *primo1, *primo2, erro;
int *vPrimos, nPrimos = 0, j;


vPrimos = (int*) calloc (DIM, sizeof (int));
resposta = (int*) calloc (100, sizeof (int));

if ( (vPrimos == NULL) || (resposta == NULL) ) {
  printf ("\nErro na criação de vector.");
  return 0;
}

for (nTeste = 1001; nTeste < 10000; nTeste = nTeste + 2) {
  booleano = primeTeste (nTeste);
  if (booleano == 1) {
    vPrimos [nPrimos] = nTeste;
    nPrimos++;
  }
}

vPrimos = realloc (vPrimos, nPrimos*sizeof (int));
if (vPrimos == NULL) {
  printf ("\nErro na realocação do vector.");
  return 0;
}

printf ("\nExistem %d primos.", nPrimos);

for (i = 0; i < nPrimos; i++) {
  nRep = 0;
  erro = 0;
  primo1 = preencheVectorDigit (vPrimos[i], 1000, 4);

  for (j = 0; j < nPrimos; j++) {
    /* se os numero forem iguais então não faz nada */
    if (i == j) {
      continue;
    }
    primo2 = preencheVectorDigit (vPrimos[j], 1000, 4);
    booleano = testaIgualdadeDigitos (primo1, primo2, 4);
    free (primo2);

    if (booleano == 1) {
      respostaIndice[nRep] = j;
      nRep++;
    }
  }
  free (primo1);

  if (nRep != 0) {
    respostaIndice[nRep] = i;
    preencheVectorResposta (resposta, vPrimos, respostaIndice);
    ordenaResposta (resposta);

    booleano = checkAritmetic (resposta);

    if (booleano == 0) {
      continue;
    } else {
      break;
    }

  }

}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nResposta: %d %d %d\n", resposta[0], resposta[1], resposta[2]);
free (vPrimos);
free (resposta);
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

int *preencheVectorDigit (int contador, int dim, int nAlg) {
/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/

int *vectorDigit;
int i;

vectorDigit = (int*) calloc (nAlg, sizeof (int));
if (vectorDigit == NULL) {
  printf ("\nErro a criar o vector.");
  return NULL;
}

for (i = 0; i < nAlg; i++) {
  vectorDigit[i] = contador / dim;
  contador = contador - vectorDigit[i]*dim;
  dim = dim / 10;
}

return vectorDigit;

}

/******************************************************************************/

int testaIgualdadeDigitos (int *primo1, int *primo2, int nAlg) {
/* esta função retorna 1 se os 2 vectores tiverem os mesmos digitos ou 0 se não */

int i, j;
int *vectorBooleano;

vectorBooleano = (int*) calloc (nAlg, sizeof (int));
if (vectorBooleano == NULL) {
  printf ("\nOcorreu um erro na criação do vector.");
  return 0;
}

for (i = 0; i < nAlg; i++) {
  vectorBooleano[i] = primo2[i];
}

for (i = 0; i < nAlg; i++) {
  for (j = 0; j < nAlg; j++) {
    if (primo1[i] == vectorBooleano[j]) {
      vectorBooleano[j] = -1;
      break;
    }
  }
}

for (i = 0; i < nAlg; i++) {
  if (vectorBooleano[i] != -1) {
    free (vectorBooleano);
    return 0;
  }
}
free (vectorBooleano);

/* se chega aqui é porque os digitos são iguais */
return 1;
}

/******************************************************************************/

void preencheVectorResposta (int *resposta, int *vPrimos, int *respostaIndice) {
/* esta função preenche o vector resposta com a chave contida no vector respostaIndice*/

int i, indice;

for (i = 0; i < 3; i++) {
  indice = respostaIndice[i];
  resposta[i] = vPrimos[indice];
}

return;
}

/******************************************************************************/

void ordenaResposta (int *resposta) {
/* esta função ordena por ordem crescente os 3 numeros contidos no vector resposta */

int i, j, aux;

for (i = 0; i < 2; i++) {
  for (j = i+1; j < 3; j++) {
    if (resposta[i] > resposta[j]) {
      /* tenho de trocar*/
      aux = resposta[i];
      resposta[i] = resposta[j];
      resposta[j] = aux;
    }
  }
}
}

/******************************************************************************/

int checkAritmetic (int *resposta) {
/* retorna 1 se a sequencia e aritmetica ou 0 se não */

int dif, dif1, i;

dif = resposta[1] - resposta[0];
dif1 = resposta[2] - resposta[1];

if (dif1 == dif) {
  return 1;
} else {
  return 0;
}

}

/******************************************************************************/
