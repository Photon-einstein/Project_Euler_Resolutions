#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/
int *preencheVectorDigit (int contador, int dim, int nAlg);

/* confirma se este conjunto de n digitos são de facto um numero Pandigital de 1 a N,
retorna 1 se sim ou 0 se não */
int pandigitalCheck (int *vector, int nAlg);

/* cria um vector de 10 inteiros e preenche pela ordem, da esquerda para a direita*/
/* no fim retorna o apontador do vector de inteiros */
int* vectorConcatena (int d1, int *vd2d3d4, int *vd5d6d7, int *vd8d9d10);

/* devolve o numero com os digitos no vector, de de dimensão dim */
long long int geraNumero (int *vPrincipal, long long int dim, int nAlg);

/* preenche vectores intermedios apartir de vPrincipal */
void preencheVectorIntermedios (int *vPrincipal, int *vd3d4d5, int *vd4d5d6, int *vd6d7d8, int *vd7d8d9);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */

int d2d3d4, d5d6d7, d8d9d10, d1, booleano, j;
long long int nTeste, sumP = 0;
int *vd2d3d4, *vd5d6d7, *vd8d9d10, *vPrincipal;
int *vd3d4d5, *vd4d5d6, *vd6d7d8, *vd7d8d9;
int d3d4d5, d4d5d6, d6d7d8, d7d8d9;

for (d1 = 1; d1 < 10; d1++) {
  printf ("\nd1 = %d", d1);
  for (d2d3d4 = 102; d2d3d4 < 999; d2d3d4 = d2d3d4 + 2) {
    if (d2d3d4 % 2 != 0) {
      continue;
    }
    for (d5d6d7 = 105; d5d6d7 < 1000; d5d6d7 = d5d6d7 + 7) {
      if (d5d6d7 % 7 != 0) {
        continue;
      }
      for (d8d9d10 = 102; d8d9d10 < 1000; d8d9d10 = d8d9d10 + 17) {
              if (d8d9d10 % 17 != 0) {
                continue;
              }
              vd2d3d4 = preencheVectorDigit (d2d3d4, 100, 3);
              vd5d6d7 = preencheVectorDigit (d5d6d7, 100, 3);
              vd8d9d10 = preencheVectorDigit (d8d9d10, 100, 3);
              if (vd2d3d4 == NULL || vd5d6d7 == NULL || vd8d9d10 == NULL) {
                  printf ("\nErro na função vector digit Calc.");
                  free (vd2d3d4);
                  free (vd5d6d7);
                  free (vd8d9d10);
                  return 0;
              }
              vPrincipal = vectorConcatena (d1, vd2d3d4, vd5d6d7, vd8d9d10);
              if (vPrincipal == NULL) {
                printf ("\nErro na função concatena.");
                return 0;
              }
              booleano = pandigitalCheck (vPrincipal, 10);
              free (vd2d3d4);
              free (vd5d6d7);
              free (vd8d9d10);

              if (booleano == 0) {
                /* neste caso não e pandigital */
                free (vPrincipal);
                continue;
              }

              vd3d4d5 = (int*) calloc (3, sizeof (int));
              vd4d5d6 = (int*) calloc (3, sizeof (int));
              vd6d7d8 = (int*) calloc (3, sizeof (int));
              vd7d8d9 = (int*) calloc (3, sizeof (int));
              if (vd3d4d5 == NULL || vd4d5d6 == NULL || vd6d7d8 == NULL || vd7d8d9 == NULL) {
                printf ("\nErro na alocação de memória.");
                return 0;
              }
              preencheVectorIntermedios (vPrincipal, vd3d4d5, vd4d5d6, vd6d7d8, vd7d8d9);
              d3d4d5 = geraNumero (vd3d4d5, 100, 3);
              d4d5d6 = geraNumero (vd4d5d6, 100, 3);
              d6d7d8 = geraNumero (vd6d7d8, 100, 3);
              d7d8d9 = geraNumero (vd7d8d9, 100, 3);

              free (vd3d4d5);
              free (vd4d5d6);
              free (vd6d7d8);
              free (vd7d8d9);

              if (d3d4d5 % 3 != 0 || d4d5d6 % 5 != 0 || d6d7d8 % 11 != 0 || d7d8d9 % 13 != 0) {
                free (vPrincipal);
                continue;
              }

              /* se chega aqui e porque e pandigital */
              j++;
              nTeste = geraNumero (vPrincipal, 1000000000, 10);
              printf ("\nNTeste ok nº %d = %lli", j, nTeste);
              sumP = sumP + nTeste;
              free (vPrincipal);
            }
        }
    }
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf\n", tempo);
printf ("\nA soma dos numeros com esta propriedade é de %lli.\n", sumP);
return 0;
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

int pandigitalCheck (int *vector, int nAlg) {
/* confirma se este conjunto de 9 digitos são de facto um numero Pandigital,
retorna 1 se sim ou 0 se não */

int *vectorCheck;
int i, j;

vectorCheck = (int*) calloc (nAlg, sizeof (int));
if (vectorCheck == NULL) {
  printf ("\nFalha na alocação de memória do vector check.");
  return 0;
}

/*preenchimento do vector check*/
for (i = 0; i < nAlg; i++) {
  vectorCheck [i] = i;
}

/*check a ver se existem todos os numeros de 1 a 9 */
for (i = 0; i < nAlg; i++) {
  for (j = 0; j < nAlg; j++) {
    if (vector[i] == vectorCheck[j]) {
      vectorCheck[j] = -1;
    }
  }
}

for (i = 0; i < nAlg; i++) {
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

int* vectorConcatena (int d1, int *vd2d3d4, int *vd5d6d7, int *vd8d9d10) {
/* cria um vector de 10 inteiros e preenche pela ordem, da esquerda para a direita*/
/* no fim retorna o apontador do vector de inteiros */

int *vPrincipal, i;

vPrincipal = (int*) calloc (10, sizeof(int));
if (vPrincipal == NULL) {
  return NULL;
}

vPrincipal[0] = d1;

for (i = 0; i < 3; i++) {
  vPrincipal[1+i] = vd2d3d4[i];
  vPrincipal[4+i] = vd5d6d7[i];
  vPrincipal[7+i] = vd8d9d10[i];
}

return vPrincipal;
}

/******************************************************************************/

long long int geraNumero (int *vPrincipal, long long int dim, int nAlg) {
/* devolve o numero com os digitos no vector, de de dimensão dim */

long long int numero = 0;
int i;

for (i = 0; i < nAlg; i++) {
  numero = numero + vPrincipal[i]*dim;
  dim = dim / 10;
}

return numero;
}

/******************************************************************************/

void preencheVectorIntermedios (int *vPrincipal, int *vd3d4d5, int *vd4d5d6, int *vd6d7d8, int *vd7d8d9) {
/* preenche vectores intermedios apartir de vPrincipal */

int i;

for (i = 0; i < 3; i++) {
  vd3d4d5[i] = vPrincipal[3-1+i];
  vd4d5d6[i] = vPrincipal[4-1+i];
  vd6d7d8[i] = vPrincipal[6-1+i];
  vd7d8d9[i] = vPrincipal[7-1+i];
}
return;
}

/******************************************************************************/
