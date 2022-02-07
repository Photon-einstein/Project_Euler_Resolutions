#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIM   100
#define DIMP  140
#define DIMPP 140
typedef struct {
  int num;
  int booleanoSquare;
} square;

/* preencho booleanoSquare com 1 em todos os quadrados perfeitos, se não forem
perfeitos deixo estar em 0. Se a funcao funcionar correctamente retorna 1,
senao retorna 0 */
/* devolve por referencia o numero de quadrados perfeitos */
int preencheVector (square *v, int dim, int *nPerfeito);

/* gera dinamicamente um vector contendo todos os quadrados nao perfeitos, e
depois retorna */
int* geraVectorQuadradoNImperfeito (square *v, int dim, int nperfeitos);

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector, e inverte os digitos*/
int *preencheVectorDigitEinverte (int contador, int dim, int nAlg, int nAlgMax);

/* multiplica o numero vNum por nTeste, ou seja faz vNum*nTeste e retorna à função principal */
void potenciaN (int *a, int nTeste, int nDigits);

/* multiplica o numero vNum por nTeste, ou seja faz vNum*nTeste e retorna à função principal
com um novo vector dinamico*/
int *CopiaPotenciaN (int *a, int nTeste, int nDigits);

/* soma membro a membro os 2 vectores, a = a + b
calculando o carry e soma-o e retorna a funcao principal */
void somaIterativa (int *a, int *b, int nAlg);

/* soma membro a membro os 2 vectores, a = a + b
calculando o carry e soma-o e retorna a funcao principal */
void subtracao (int *a, int *b, int nAlg);

/* devolve o numero de algarismos significativos de um vector de inteiros com
nAlgMax de dimensao */
int calcNAlgarismos (int *vector, int nAlgMax);

/* esta funcao retorna 0 se a >= b ou 1 se a < b */
int booleanoComparaNumeros (int *a, int *b, int dim);

/* soma os algarismos de b desde o comeco, dim algarismos e depois retorna o
numero */
int somaDigitos (int *b, int comeco, int dim);

/* calcula o numero inteiro da raiz quadrada de numero e devolve o valor */
int calculaInteiroRaiz (int numero);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
square v[DIM];
int i, booleano, nPerfeitos, *s, nImperfeitos, res, total = 0, dim, nAlg;
int *digit, *numerador, *denominador, passo, *esquerdo, unidade, j, *apendice;

/* preenchimento do vector v */
for (i = 0; i < DIM; i++) {
  v[i].num = i+1;
  v[i].booleanoSquare = 0;
}

booleano = preencheVector (v, DIM, &nPerfeitos);
if (booleano == 0) {
  printf ("\nOcorreu um erro na criacao do vector booleano.");
  return 0;
}
printf ("\nExistem %d quadrados perfeitos.", nPerfeitos);
/* vou agora criar um vector so com os quadrados imperfeitos */
nImperfeitos = DIM - nPerfeitos;
s = geraVectorQuadradoNImperfeito (v, DIM, nPerfeitos);

if (s == NULL) {
  printf ("\nOcorreu um erro a criar o vector s.");
  return 0;
}
printf ("\nVou agora entrar neste ciclo.");

for (i = 0; i < nImperfeitos; i++) {
  /*printf ("\nVamos agora processar a raiz quadrada de %d.", s[i]); */
  /* vou agora criar o vector com o resultado para cada uma das raizes */
  digit = (int*) calloc (DIMPP, sizeof (int));
  if (digit == NULL) {
    printf ("\nOcorreu uma falha a criar os vectores start.");
    return 0;
  }
  /* digito inteiro da raiz */
  digit[0] = calculaInteiroRaiz (s[i]);
  /* a soma vai comecar em 1 */
  passo = 1;
  /* inicializacao do numerador */
  dim = dimCalc (s[i], &nAlg);
  numerador = preencheVectorDigitEinverte (s[i], dim, nAlg, DIMPP);
  /* inicializacao do denominador */
  dim = dimCalc (pow(digit[0],2), &nAlg);
  denominador = preencheVectorDigitEinverte (pow(digit[0],2), dim, nAlg, DIMPP);
  /* inicializacao do numero esquerdo */
  dim = dimCalc ((digit[0]*2), &nAlg);
  esquerdo = preencheVectorDigitEinverte ((digit[0]*2), dim, nAlg, DIMPP);
  if (numerador == NULL || denominador == NULL || esquerdo == NULL) {
    printf ("\nOcorreu uma falha a criar os vectores numerador, denominador ou esquerdo.");
    return 0;
  }
  res = 0;
  /* determinacao das casas decimais da raiz */
  for (passo = 1; passo  < DIMP; passo++) {
    nAlg = calcNAlgarismos (numerador, DIMPP);
    subtracao (numerador, denominador, nAlg);
    free (denominador);
    /* faz-se cair mais um par de zeros no numerador */
    potenciaN (numerador, 100, DIMPP);
    /* avanca-se o esquerdo uma casa decimal */
    potenciaN (esquerdo, 10, DIMPP);
    /* inicio do contador digito das unidades */
    unidade = 1;
    while (1) {
      esquerdo[0] = unidade;
      denominador = CopiaPotenciaN (esquerdo, esquerdo[0], DIMPP);
      if (denominador == NULL) {
        printf ("\nOcorreu uma falha a criar o vector denominador.");
        return 0;
      }
      booleano = booleanoComparaNumeros (numerador, denominador, DIMPP);
      /* se o denominador for maior do que o numerador ja excedeu esquerdo[0] */
      if (booleano == 1) {
        /* a < b */
        /* desconto da unidade a mais */
        unidade--;
        esquerdo[0] = unidade;
        /* mais uma casa decimal de precisao */
        digit[passo] = unidade;
        /* calculo do verdadeiro denominador */
        denominador = CopiaPotenciaN (esquerdo, esquerdo[0], DIMPP);
        if (denominador == NULL) {
          printf ("\nOcorreu uma falha a criar o vector denominador.");
          return 0;
        }
        /* agora tenho de dobrar o ultimo digito da esquerda */
        dim = dimCalc (2*esquerdo[0], &nAlg);
        if (dim == 1) {
          /* basta actualizar */
          esquerdo[0] = esquerdo[0]*2;
        } else {
          /* tenho de fazer uma soma vectorial */
          apendice = preencheVectorDigitEinverte (2*esquerdo[0], dim, nAlg, DIMPP);
          if (apendice == NULL) {
            printf ("\nOcorreu uma falha a criar o vector apendice.");
            return 0;
          }
          /* desconto do do esquerdo[0] */
          esquerdo[0] = 0;
          somaIterativa (esquerdo, apendice, DIMP);
          free (apendice);
        }
        break;
      } else {
        free (denominador);
        unidade++;
      }
    }
  }
  res = 0;
  for (j = 0; j < 100; j++) {
    /*printf ("%d", digit[j]); */
    res = res + digit[j];
  }
  free (digit);
  free (numerador);
  free (denominador);
  free (esquerdo);
  total = total + res;
}
free (s);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nTemos um total de %d.", total);
return 0;
}
/******************************************************************************/
int preencheVector (square *v, int dim, int *nPerfeito) {
/* preencho booleanoSquare com 1 em todos os quadrados perfeitos, se não forem
perfeitos deixo estar em 0. Se a funcao funcionar correctamente retorna 1,
senao retorna 0 */
/* devolve por referencia o numero de quadrados perfeitos */
if (v == NULL || dim == 0) {
  return 0;
}
int i, num, nP = 0;
for (i = 0; i < sqrt(dim+1); i++) {
  num = pow(v[i].num, 2);
  if (num > dim) {
    /* ja atingi o limite */
    break;
  } else {
    v[num-1].booleanoSquare = 1;
    nP++;
  }
}
*nPerfeito = nP;
return 1;
}
/******************************************************************************/
int* geraVectorQuadradoNImperfeito (square *v, int dim, int nPerfeitos) {
/* gera dinamicamente um vector contendo todos os quadrados nao perfeitos, e
depois retorna */
int realDim, *s, i, passo = 0;
/* teste dos parametros */
if (v == NULL) {
  return NULL;
}
realDim = dim - nPerfeitos;
s = (int*) calloc (realDim, sizeof(int));
if (s == NULL) {
  return NULL;
}
for (i = 0; i < dim; i++) {
  if (v[i].booleanoSquare == 1) {
    /* neste caso nao se faz nada */
    continue;
  }
  s[passo] = v[i].num;
  passo++;
}
return s;
}
/******************************************************************************/
int dimCalc (int contador, int *nAlg) {
/* calcula dim do contador e devolve também o nAlg do contador */
int dim = 1;
int res, nAlgarismos = 1;
res = contador / dim;
while (res > 9) {
  dim = dim * 10;
  nAlgarismos++;
  res = contador / dim;
}
*nAlg = nAlgarismos;
return dim;
}
/******************************************************************************/
int *preencheVectorDigitEinverte (int contador, int dim, int nAlg, int nAlgMax) {
/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/
int *vectorDigit, *vectorDigitInvertido;
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
vectorDigitInvertido = (int*) calloc (nAlgMax, sizeof (int));
if (vectorDigitInvertido == NULL) {
  printf ("\nErro a criar o vector.");
  return NULL;
}
/* inverte digitos */
for (i = 0; i < nAlg; i++) {
  vectorDigitInvertido[i] = vectorDigit[nAlg-1-i];
}
free (vectorDigit);
return vectorDigitInvertido;
}
/******************************************************************************/
void potenciaN (int* vNum, int nTeste, int nDigits) {
/* devolve o novo nAlg, soma o numero vNum, nTeste vezes e retorna à função principal */
int i, j, carry = 0;
carry = 0;
for (j = 0; j < nDigits; j++) {
  vNum[j] = vNum[j] * nTeste + carry;
  if (vNum[j] < 10) {
    carry = 0;
  } else {
    carry = vNum[j] / 10;
    vNum[j] = vNum[j] - carry*10;
  }
}
return;
}
/******************************************************************************/
void somaIterativa (int *a, int *b, int nAlg) {
/* soma membro a membro os 2 vectores, a = a + b
calculando o carry e soma-o e retorna a funcao principal */
int carry = 0, *somaOverflow, i;
for (i = 0; i < nAlg; i++) {
  a[i] = a[i] + b[i] + carry;
  if (a[i] > 9) {
    carry = a[i] / 10;
    a [i] = a[i] % 10;
  } else {
    carry = 0;
  }
}
return;
}
/******************************************************************************/
void subtracao (int *a, int *b, int nAlg) {
/* soma membro a membro os 2 vectores, a = a + b
calculando o carry e soma-o e retorna a funcao principal */
int i, j;

for (i = 0; i < nAlg; i++) {
  /* caso mais simples */
  if (a[i] >= b[i]) {
    a[i] = a[i] - b[i];
  } else if (a[i] < b[i] && a[i+1] != 0 && i+1 < nAlg) {
  /* 2º caso em que tenho de que pedir imprestado ao numero seguinte */
  /* subtracao feita com o borrow */
    a[i] = 10+a[i] - b[i];
  /* desconto do borrow */
    a[i+1]--;
  } else {
    /* caso mais dificil*/
    a[i] = 10+a[i] - b[i];
    for (j = i+1; j < nAlg; j++) {
      if (a[j] == 0) {
        a[j] = 9;
      } else {
        a[j]--;
        break;
      }
    }
  }
}
}
/******************************************************************************/
int calcNAlgarismos (int *vector, int nAlgMax) {
/* devolve o numero de algarismos significativos de um vector de inteiros com
nAlgMax de dimensao */
int i, n = 0, res;
for (i = nAlgMax-1; i > -1; i--) {
  if (vector[i] == 0) {
    n++;
  } else {
    break;
  }
}
res = nAlgMax-n;
return res;
}
/******************************************************************************/
int booleanoComparaNumeros (int *a, int *b, int dim) {
/* esta funcao retorna 0 se a >= b ou 1 se a < b */
int i;
for (i = dim-1; i > -1; i--) {
  if (a[i] == 0 && b[i] == 0) {
    continue;
  } else if (a[i] > b[i]) {
    return 0;
  } else if (a[i] < b[i]) {
    return 1;
  }
}
/* se chega aqui e porque sao iguais */
return 0;
}
/******************************************************************************/
int somaDigitos (int *b, int comeco, int dim) {
/* soma os algarismos de b desde o comeco, dim algarismos e depois retorna o
numero */
int i, soma = 0;
for (i = 0; i < dim; i++) {
  soma = soma + b[comeco + i];
}
return soma;
}
/******************************************************************************/
int calculaInteiroRaiz (int numero) {
/* calcula o numero inteiro da raiz quadrada de numero e devolve o valor */
int antes, depois, antesS, depoisS;
antes = 1;
depois = antes + 1;
while (1) {
  antesS = pow (antes, 2);
  depoisS = pow (depois, 2);
  if (antesS < numero && depoisS > numero) {
    break;
  }
  antes++;
  depois++;
}
return antes;
}
/******************************************************************************/
int *CopiaPotenciaN (int *a, int nTeste, int nDigits) {
/* multiplica o numero vNum por nTeste, ou seja faz vNum*nTeste e retorna à função principal
com um novo vector dinamico*/
int j, carry = 0, *res;
carry = 0;
res = (int*) calloc (nDigits, sizeof (int));
if (res == NULL) {
  return NULL;
}
for (j = 0; j < nDigits; j++) {
  res[j] = a[j] * nTeste + carry;
  if (res[j] < 10) {
    carry = 0;
  } else {
    carry = res[j] / 10;
    res[j] = res[j] % 10;
  }
}
return res;
}
/******************************************************************************/
