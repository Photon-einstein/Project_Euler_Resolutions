#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIMV 10
typedef struct {
  int a;
  int b;
} triangMedida;

/* booleano teste, retorna 1 se c e um valor inteiro ou 0 se ele for um valor
fracionário */
int testaValorCinteiro (int a, int b);

/* booleano teste, retorna -1 se p > (a+b+c), 0 se p = (a+b+c) ou 1 se p < (a+b+c)*/
int booleanoPTeste (int p,int a, int b);

/* verifica se já ha alguma solução guardada com a e b em ordens diferentes, no vector,
desde 0 ate nHits, devolve 0 se ok e 1 se ha repetição */
int verificaRepeticaoVector (triangMedida *vector, int nHits, int a, int b);

/* guarda a solução no vector, na posicao indice pHits */
void guardaSolucao (triangMedida *vector, int a, int b, int pHits);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */

int p, a, b, tribooleano, booleano, pHits = 0;
int mult = 1;
triangMedida *vector;
int pHitsMax = 0;
int pMax;

for (p = 5; p < 1001; p++) {
    /* criação de um novo vector para abarcar os resultados*/
    vector = (triangMedida*) calloc (DIMV, sizeof (triangMedida));
    if (vector == NULL) {
      printf ("\nOcorreu uma falha na criação de um novo vector.");
      return 0;
    }
    /* reset do contador a zero para um novo p*/
    pHits = 0;

    for (a = 1; a < (p-1); a++) {
      for (b = 1; b < (p-1); b++) {
        /* booleano teste, retorna 1 se c e um valor inteiro ou 0 se ele for um valor
        fracionário */
        booleano = testaValorCinteiro (a,b);
        if (booleano == 0) {
          /* c e um valor com parte fracionária, não interessa para este calculo */
          continue;
        }
        /* booleano teste, retorna -1 se p > (a+b+c), 0 se p = (a+b+c) ou 1 se p < (a+b+c)*/
        tribooleano = booleanoPTeste (p,a,b);
        if (tribooleano == -1) {
          continue;
        } else if (tribooleano == 1) {
          break;
        }

        /* se chega aqui e porque p = (a+b+c) */
        /* verifica se já ha alguma solução guardada com a e b em ordens diferentes, no vector,
        desde 0 ate nHits, devolve 0 se ok e 1 se ha repetição */
        booleano = verificaRepeticaoVector (vector, pHits, a, b);
        if (booleano == 1) {
          /* neste caso ha repeticao */
          continue;
        }

        /* se chega aqui é porque não há repeticao, tenho de guardar o resultado,
        mas primeiro tenho de me certificar que tenho espaço */
        if ( pHits == (DIMV*mult)) {
          /* neste caso não tenho espaco no vector para guardar o resultado */
          mult++;
          vector = (triangMedida*) realloc (vector , DIMV*mult*sizeof (triangMedida));
          if (vector == NULL) {
            printf ("\nFalha na realocação de memória.");
            return 0;
          }
        }

        /* agora vou guar dar o resultado no indice solucoes*/
        guardaSolucao (vector, a, b, pHits);
        pHits++;
      }
    }
    /* acabou o teste para o numero p, averiguação se ha um novo maximo*/
    if (pHits > pHitsMax) {
      pHitsMax = pHits;
      pMax = p;
    }

    /* agora tenho de libertar a memoria do vector */
    free (vector);
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nO número p com soluções maximizada é o p = %d\n", pMax);
return 0;
}

/******************************************************************************/

int testaValorCinteiro (int a, int b) {
/* booleano teste, retorna 1 se c e um valor inteiro ou 0 se ele for um valor
fracionário */

float c, partFracionaria;

c = sqrt (pow (a,2) + pow (b,2));

partFracionaria = c - (int)c;

if (partFracionaria == 0) {
  return 1;
} else {
  return 0;
}

}

/******************************************************************************/

int booleanoPTeste (int p,int a, int b) {
/* booleano teste, retorna -1 se p > (a+b+c), 0 se p = (a+b+c) ou 1 se p < (a+b+c)*/

int c, pCalc;

c = sqrt( pow (a, 2) + pow (b, 2));

pCalc = a + b + c;

if (p > pCalc) {
  return -1;
} else if (p == pCalc) {
  return 0;
} else {
  return 1;
}

}

/******************************************************************************/

int verificaRepeticaoVector (triangMedida *vector, int nHits, int a, int b) {
/* verifica se já ha alguma solução guardada com a e b em ordens diferentes, no vector,
desde 0 ate nHits-1, devolve 0 se ok e 1 se ha repetição */

int i;

for (i = 0; i < nHits; i++) {
  if ((vector[i].a == a && vector[i].b == b) || (vector[i].a == b && vector[i].b == a)) {
    /* se entra aqui é porque a solução é repetida logo devolve 1*/
    return 1;
  }
}

/* se chega aqui é porque não há repeticao, devolve 0 */
return 0;
}

/******************************************************************************/

void guardaSolucao (triangMedida *vector, int a, int b, int pHits) {
/* guarda a solução no vector, na posicao indice pHits */

vector[pHits].a = a;
vector[pHits].b = b;
}

/******************************************************************************/
