#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX 100
#define DIM 100
typedef struct {
  int numerador[DIM];
  int denominador[DIM];
} fracao;

/* esta função preenche os indices do numero e */
void preencherIndices (int *indices, int max);

/* calcula a proxima fracao e retorna a função principal */
void calculaProximaFracao (fracao *v, int passo, int *indices);

/* calcula a ultima parcela da fracao */
void calculaUltimaParcela (fracao *v, int passo, int *indices);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int indices[MAX] = {0}, soma = 0, passo, i, found;
fracao *v;

v = (fracao*) calloc (1, sizeof (fracao));
if (v == NULL) {
  printf ("\nOcorreu um erro na criação do vector fracao.");
  return 0;
}

preencherIndices (indices, MAX);
/* impressão dos valores de v[] desde 0 ate 99 */
for (passo = 0; passo < MAX; passo++) {
  printf ("\npassoNº%d: %d.", passo, indices[passo]);
}

/* fracao nº 0 */
v->numerador[0] = 1;
v->denominador[0] = indices[MAX-1];

for (passo = MAX-2; passo > 0; passo--) {
  calculaProximaFracao (v, passo, indices);
}
/* falta agora somar a ultima parcela */
calculaUltimaParcela (v, 0, indices);

printf ("\nNumerador: ");
found = 0;

for (i = DIM-1; i > -1; i--) {
  if (v->numerador[i] == 0 && found == 0) {
    continue;
  }
  found = 1;
  soma = v->numerador[i] + soma;
  printf ("%d", v->numerador[i]);
}

printf ("\nDenominador: ");
found = 0;

for (i = DIM-1; i > -1; i--) {
  if (v->denominador[i] == 0 && found == 0) {
    continue;
  }
  found = 1;
  printf ("%d", v->denominador[i]);
}
free (v);

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nA soma dos digitos é de %d para i numerador do 100th convergente de e.", soma);
printf ("\n");
return 0;
}
/******************************************************************************/
void preencherIndices (int *indices, int max) {
/* esta função preenche os indices do numero e */

int passo = 1, andamento, v[3];

indices[0] = 2;
/* preenchimento dos valores iniciais de v*/
v[0] = 1;
v[1] = 2;
v[2] = 1;
andamento = 0;

for (passo = 1; passo < max; passo++) {
  indices[passo] = v[andamento];
  andamento++;
  if (andamento == 3) {
    /* reset do valor de andamento */
    andamento = 0;
    /* actualização do valor de v[] */
    v[1] = v[1]+2;
  }
}
return;
}
/******************************************************************************/
void calculaProximaFracao (fracao *v, int passo, int *indices) {
/* calcula a proxima fracao e retorna a função principal */
int n[200] = {0}, d[200] = {0}, a, i, carry = 0;

a = indices[passo];

/* copia de valores de v->numerador e v->denominador para n e d */
for (i = 0; i < DIM; i++) {
    n[i] = v->numerador[i];
    d[i] = v->denominador[i];
}


/* calculo da nova fraçao */
/* v->numerador = d */
for (i = 0; i < DIM; i++) {
  v->numerador[i] = d[i];
}

/* v->denominador = a*d+n */
for (i = 0; i < DIM; i++) {
  v->denominador[i] = a*d[i]+n[i]+carry;
  if (v->denominador[i] > 9) {
    carry = v->denominador[i] / 10;
    v->denominador[i] = v->denominador[i] % 10;
  } else {
    carry = 0;
  }
}

return;
}
/******************************************************************************/
void calculaUltimaParcela (fracao *v, int passo, int *indices) {
/* calcula a ultima parcela da fracao */
int n[200] = {0}, d[200] = {0}, a, i, carry = 0;

/* copia de valores de v->numerador e v->denominador para n e d */
for (i = 0; i < DIM; i++) {
    n[i] = v->numerador[i];
    d[i] = v->denominador[i];
}

a = indices[passo];

/* calculo da nova fraçao */
/* v->numerador = a*d+n */
/* v->denominador = d */
for (i = 0; i < DIM; i++) {
  v->numerador[i] = a*d[i]+n[i]+carry;
  if (v->numerador[i] > 9) {
    carry = v->numerador[i] / 10;
    v->numerador[i] = v->numerador[i] % 10;
  } else {
    carry = 0;
  }
}
return;
}
/******************************************************************************/
