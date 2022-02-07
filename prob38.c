#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/* gera vector não preenchido com 9 digitos por preencher e devolve apontador*/
int* geraVector9Digitos ();

/* gera o numero para preencher no vectorPandigital*/
int geraNumero (int nTeste, int n);

/* calcula a dimensão do numero nTeste e devolve por referencia o nAlg */
int dimCalc (int nTeste, int* nAlg);

/* copia digitos do numero para o vector desde nDigitos antigo ate nDigitos+nAlg*/
/* retorna 1 se o preenchimento ocorrer com sucesso ou 0 se exceder dim = 9 alg*/
int preencheValoresVector (int *vector, int numero, int nDigitos, int nAlg, int dim);

/* confirma se este conjunto de 9 digitos são de facto um numero Pandigital,
retorna 1 se sim ou 0 se não */
int pandigitalCheck (int *vector);

/* calcula o numero Pandigital contido no vector, e retorna esse valor*/
int nPandigitalCalc (int *vector);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int nTeste, n, numero, booleano, nDigitos, nPandigital, nAlg, dimNumero, booleanoPreenche;
int *vector;
int maxPandigital = 0;

for (nTeste = 1; nTeste < 10001; nTeste++) {
  /* novo teste */
  n = 1;
  booleano = 1;
  nDigitos = 0;
  vector = geraVector9Digitos();

  while (booleano == 1 && nDigitos != 9) {
    if (vector == NULL) {
      printf ("\nFalha na alocação de memória do vector.");
      return 0;
    }
    numero = geraNumero (nTeste, n);
    dimNumero = dimCalc (numero, &nAlg);

    if ((nDigitos + nAlg) < 10) {
      booleanoPreenche = preencheValoresVector (vector, numero, nDigitos, nAlg, dimNumero);

      if (booleanoPreenche == 0) {
        printf ("\nVector excedeu limites.");
        booleano = 0;
      }
    } else {
      booleano = 0;
      break;
    }
    /* avanço dos contadores */
    nDigitos = nDigitos + nAlg;
    n++;
  }

  /* já sai do ciclo while*/
  if (booleano == 0) {
    /*ocorreu um erro, excesso de digitos*/
    free (vector);
    continue;
  } else {
    /* a inserção correu bem*/
    booleano = pandigitalCheck (vector);
    if (booleano == 0) {
      /* não e um numero pandigital*/
      free(vector);
      continue;
    }
  }
    printf ("\nnTeste %d e um numero pandigital.", nTeste);
    nPandigital = nPandigitalCalc (vector);
    free(vector);

  if (nPandigital > maxPandigital) {
    maxPandigital = nPandigital;
  }
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nO número Pandigital máximo é o %d.\n", maxPandigital);
return 0;
}

/******************************************************************************/

int* geraVector9Digitos () {
/* gera vector não preenchido com 9 digitos por preencher e devolve apontador*/

int *vector;

vector = (int*) calloc (9, sizeof (int));
return vector;
}

/******************************************************************************/

int geraNumero (int nTeste, int n) {
/* gera o numero para preencher no vectorPandigital*/

int numero;

numero = nTeste * n;

return numero;
}

/******************************************************************************/

int dimCalc (int nTeste, int* nAlg) {
/* calcula a dimensão do numero nTeste e devolve por referencia o nAlg */

int dim = 1;
int nAlgarismos = 1;
int res;

res = nTeste / dim;

while (res > 9) {
  dim = dim * 10;
  nAlgarismos++;
  res = nTeste / dim;
}

*nAlg = nAlgarismos;
return dim;
}

/******************************************************************************/

int preencheValoresVector (int *vector, int numero, int nDigitos, int nAlg, int dim) {
/* copia digitos do numero para o vector desde nDigitos antigo ate nDigitos+nAlg*/
/* retorna 1 se o preenchimento ocorrer com sucesso ou 0 se exceder dim = 9 alg*/

int *vectorAuxiliar;
int i, j;

vectorAuxiliar = (int*) calloc (nAlg, sizeof (int));
if (vectorAuxiliar == NULL) {
  printf ("\nOcorreu uma falha na alocação de memória.");
}

for (i = 0; i < nAlg; i++) {
  vectorAuxiliar[i] = numero / dim;
  numero = numero - vectorAuxiliar[i]*dim;
  dim = dim / 10;
}

j = 0;
for (i = nDigitos; i < (nDigitos + nAlg); i++) {
  /* controlo de inserção*/
  if (i > 9) {
    free(vectorAuxiliar);
    return 0;
  }
  vector[i] = vectorAuxiliar[j];
  j++;
}

/* se chega aqui e porque correu tudo bem*/
free(vectorAuxiliar);
return 1;
}


/******************************************************************************/

int pandigitalCheck (int *vector) {
/* confirma se este conjunto de 9 digitos são de facto um numero Pandigital,
retorna 1 se sim ou 0 se não */

int *vectorCheck;
int i, j;

vectorCheck = (int*) calloc (9, sizeof (int));
if (vectorCheck == NULL) {
  printf ("\nFalha na alocação de memória do vector check.");
  return 0;
}

/*preenchimento do vector check*/
for (i = 0; i < 9; i++) {
  vectorCheck [i] = i+1;
}

/*check a ver se existem todos os numeros de 1 a 9 */
for (i = 0; i < 9; i++) {
  for (j = 0; j < 9; j++) {
    if (vector[i] == vectorCheck[j]) {
      vectorCheck[j] = -1;
    }
  }
}

for (i = 0; i < 9; i++) {
  if (vectorCheck[i] != -1) {
    free(vectorCheck);
    return 0;
  }
}

/* se chega aqui e porque é nPandigital*/
free(vectorCheck);
return 1;
}

/******************************************************************************/

int nPandigitalCalc (int *vector) {
/* calcula o numero Pandigital contido no vector, e retorna esse valor*/

int i, nPandigital = 0;
int dim = 100000000;

for (i = 0; i < 9; i++) {
  nPandigital = nPandigital + vector[i] * dim;
  dim = dim / 10;
}

return nPandigital;
}

/******************************************************************************/
