#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXD 1000
#define MAXINDICE 500
#define DIMFRACAO 400
typedef struct {
  int xMin;
  int d;
  int processado;
  int *xOverFlow;
  int *yOverFlow;
  int nAlg;
  int dim;
} equacao;

typedef struct {
  int x[DIMFRACAO];
  int y[DIMFRACAO];
} fracao;

typedef struct {
  int *xMax;
  int nAlgMax;
  int d;
} max;

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector, e inverte os digitos*/
int *preencheVectorDigitEinverte (int contador, int dim, int nAlg, int nAlgMax);

/* calcula o número de algarismos de x e devolve o inteiro */
int nAlgCalc (int *x, int nAlgMax);

/* esta função cria dinamicamente um vector de inteiros e preenche com os
D que não são quadrados, e devolve por referencia o nº de D disponiveis */
int *calculaDateDMAX (int maxD, int *numD);

/* compara 2 numeros com nDigitps, retorna 0 se maximo e v0,
se booleano = 1 então o maximo e v1 */
int compara2Numeros (int *v0, int *v1, int nDigits);

/* função que retorna 1 se o numero nTeste é um quadrado perfeito ou 0 se o
numero não é um quadrado perfeito */
int testaQuadradoPerfeito (int nTeste);

/* encontra o x min para equacao de diophantine e retorna o valor */
int encontraXminimo (int d);

/* cria dinamicamente um vector de indices e preenche com os indices de frações
continuadas para a raiz de d, devolve o comprimento do periodo por referencia */
int *preencheIndicesAteMAXINDICE (int d, int maxIndice, int *periodo);

/* calcula primeira aproximcao para o nTeste*/
int calculaAproximacaoRaiz (int nTeste);

/* calcula m N+1 e devolve o inteiro correspondente */
int mNextCalc (int dN, int aN, int mN);

/* calcula o d N+1 e devolve o inteiro correspondente */
int dNextCalc (int s, int mN, int dN);

/* calcula a N+1 e faz logo a seguir a aproximação */
int calculaANeAproxima (int a0, int mN, int dN);

/* calcula a proxima fracao e retorna a função principal */
void calculaProximaFracao (fracao *v, int passo, int *indices);

/* calcula a ultima parcela da fracao */
void calculaUltimaParcela (fracao *v, int passo, int *indices);

/* verifica se x² - D*y² = 1, se sim então retorna 1, senão retorna 0 */
int testaSolucao(fracao *v, int d);

/* multiplica o numero vNum por nTeste, ou seja faz nTeste^x e retorna à função principal */
void potenciaN (int* vNum, int nTeste, int nDigits);

/* soma um numero reduzido a um vector com nDigits e depois retorna à função */
void somaNumeroAvector (int *vNum, int nTeste, int nDigits);

/* testa igualdade de digitos entre dois vectores com nDigitos,
retorna 1 se os digitos forem iguais ou 0 se não forem */
int testaIgualdadeDigitos (int *v1, int *v2, int nDigits);

/* calcula o resultado no vector res de nDigits da multiplicação
do vector de mult * mult*/
void calculaQuadrado (int *res, int *mult, int nDigits);


int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
equacao *v;
fracao *f;
int *d, numD, i,j,k, start, dCalc, nOverFlow = 0, passo, booleano, found, n, periodo;
int *indices;
max resposta;

/* tenho de ver quais os D que não são quadrados */
d = calculaDateDMAX (MAXD, &numD);
if (d == NULL) {
  printf ("\nOcorreu um erro na criação do vector d.");
  return 0;
}

printf ("\nExistem %d D para serem processados.", numD);
fflush (stdout);
/* vou agora criar o vector equacao */
v = (equacao*) calloc (numD, sizeof (equacao));
if (v == NULL) {
  printf ("\nOcorreu um erro na criação do vector v.");
  return 0;
}

/* copia dos valores do vector d para o vector v */
for (i = 0; i < numD; i++) {
  v[i].d = d[i];
}

free (d);

/* agora tenho de calcular o xMin para cada um dos D */
for (i = 0; i < numD; i++) {
  printf ("\ni = %d: D = %d", i, v[i].d);
  fflush (stdout);
  v[i].xMin = encontraXminimo (v[i].d);

  /* situação de overflow */
  if (v[i].xMin == 0) {
    printf ("  Overflow.");
    nOverFlow++;
    v[i].processado = 0;
    continue;
  }
  /* situação de não overflow */
  v[i].processado = 1;
}
printf ("\nTratamento agora dos overflows.");
/* chegado aqui tenho de processar todos os que ainda faltam que estão em
situação de overflow */

for (i = 0; i < numD; i++) {
  /* número pequeno que eu já consegui processar */
  if (v[i].processado == 1) {
    printf ("\ni = %d e D = %d: %d", i+1, v[i].d, v[i].xMin);
    continue;
  }
  printf ("\ni = %d e D = %d", i+1, v[i].d);
  /* vou ter agora de preencher os indices para aquele numero em particular */
  indices = preencheIndicesAteMAXINDICE (v[i].d, MAXINDICE, &periodo);
  if (indices == NULL) {
    printf ("\nOcorreu uma falha a criar o vector indices.");
    return 0;
  }

  /* agora vou ter de testar todas os convergentes desde o inicio, até encontrar
  um par x/y que funcione */
  found = 0;
  for (j = 1; j < MAXINDICE; j++) {
    f = (fracao*) calloc (1, sizeof(fracao));
    if (f == NULL) {
      printf ("\nOcorreu um erro a criar a fracao.");
      return 0;
    }
    /* tenho agora de calcular a fraçao para o indice[j] */
    /* fracao nº 0 */
    f->x[0] = 1;
    f->y[0] = indices[j];
    for (passo = j-1; passo > 0; passo--) {
      calculaProximaFracao (f, passo, indices);
    }
    /* falta agora somar a ultima parcela */
    calculaUltimaParcela (f, 0, indices);

    /* falta agora testar as soluções x e y */
    booleano = testaSolucao(f, v[i].d);
    if (booleano == 1) {
      printf (": ");
      /*foi encontrado uma solução, tenho de copiar esta solução para a equacao*/
      /* copia do x */
      v[i].xOverFlow = (int*) calloc (DIMFRACAO, sizeof(int));
      if (v[i].xOverFlow == NULL) {
        printf ("\nOcorreu um erro na criação do vector v[i].xOverFlow.");
        return 0;
      }
      for (k = 0; k < DIMFRACAO; k++) {
        v[i].xOverFlow[k] = f->x[k];
      }
      /* copia do y */
      v[i].yOverFlow = (int*) calloc (DIMFRACAO, sizeof(int));
      if (v[i].yOverFlow == NULL) {
        printf ("\nOcorreu um erro na criação do vector v[i].yOverFlow.");
        return 0;
      }
      for (k = 0; k < DIMFRACAO; k++) {
        v[i].yOverFlow[k] = f->y[k];
      }
      /* impressão do x */
      v[i].nAlg = nAlgCalc (v[i].xOverFlow, DIMFRACAO);
      for (k = v[i].nAlg-1; k > -1; k--) {
        printf ("%d", v[i].xOverFlow[k]);
      }
      printf (" / ");
      /* impressão do y */
      n = nAlgCalc (v[i].yOverFlow, DIMFRACAO);
      for (k = n-1; k > -1; k--) {
        printf ("%d", v[i].yOverFlow[k]);
      } 
      found = 1;
    }
    free (f);
    if (found == 1) {
      /* sai fora do ciclo para encontrar a solução */
      break;
    }
  }
  free (indices);
}

/* agora falta-me encontrar o maximo X de entre as soluções encontradas */
/* preenchimento dos valores simples de calcular para ficarem todos normalizados */
start = 0;
for (i = 0; i < numD; i++) {
  if (v[i].xOverFlow == NULL) {
    v[i].dim = dimCalc (v[i].xMin, &v[i].nAlg);
    v[i].xOverFlow = preencheVectorDigitEinverte (v[i].xMin, v[i].dim, v[i].nAlg, DIMFRACAO);
  }
  /* agora vou determinar o xMax */
  if (start == 0) {
    /* inicio da variavel de estado para guardar a resposta */
    resposta.xMax = v[0].xOverFlow;
    resposta.nAlgMax = v[0].nAlg;
    resposta.d = v[0].d;
    start = 1;
  } else if (resposta.nAlgMax < v[i].nAlg) {
    /* actualização directa dos valores */
    resposta.xMax = v[i].xOverFlow;
    resposta.nAlgMax = v[i].nAlg;
    resposta.d = v[i].d;
  } else if (resposta.nAlgMax == v[i].nAlg) {
    /* tenho de ver digito a digito, para saber qual e o maior*/
    /* se booleano = 0 então o max mantem-se, se booleano = 1,
    os maximos trocam */
    booleano = compara2Numeros (resposta.xMax, v[i].xOverFlow, DIMFRACAO);
    if (booleano == 1) {
      /* tenho de trocar os maximos */
      resposta.xMax = v[i].xOverFlow;
      resposta.nAlgMax = v[i].nAlg;
      resposta.d = v[i].d;
    }
  }
}

/* libertação da memória que foi usada */
for (i = 0; i < numD; i++) {
  free (v[i].xOverFlow);
}
free (v);
printf ("\nExistem %d overflows.", nOverFlow);

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nO max X com D ate %d é de %d.", MAXD, resposta.d);
printf ("\n");
return 0;
}
/******************************************************************************/
int *calculaDateDMAX (int maxD, int *numD) {
/* esta função cria dinamicamente um vector de inteiros e preenche com os
D que não são quadrados, e devolve por referencia o nº de D disponiveis */
int *v, d, booleano, contador = 0;

v = (int*) calloc (maxD, sizeof (int));
if (v == NULL) {
  return NULL;
}

for (d = 1; d < maxD+1; d++) {
  booleano = testaQuadradoPerfeito (d);
  if (booleano == 1) {
    continue;
  }
  /* se chega aqui é porque não é um quadrado perfeito */
  v[contador] = d;
  contador++;
}
v = (int*) realloc (v, contador*sizeof(int));
if (v == NULL) {
  return NULL;
}
*numD = contador;
return v;
}
/******************************************************************************/
int testaQuadradoPerfeito (int nTeste) {
/* função que retorna 1 se o numero nTeste é um quadrado perfeito ou 0 se o
numero não é um quadrado perfeito */
double raiz;
int iRaiz, n;

raiz = sqrt (nTeste);
iRaiz = (int) raiz;

n = pow (iRaiz, 2);
if (n == nTeste) {
  return 1;
} else {
  /* neste caso não é um quadrado perfeito */
  return 0;
}
}
/******************************************************************************/
int encontraXminimo (int d) {
/* encontra o x min para equacao de diophantine e retorna o valor */
int x, y = 1, found = 0, inicio, esquerda, direita;
int res, contador;

/*determinação de x min */
x = (int) sqrt (1+d);

while (1) {
  y = sqrt ( (pow(x,2)-1) / d );
  contador = 0;
  while (1) {
    if (y == 0) {
      y++;
    }
    esquerda = pow (x,2);
    direita = d*pow(y,2);
    res = esquerda-direita;

    if (esquerda < 0 || direita < 0) {
      return 0;
    }
    if (res == 1) {
      printf (" x = %d e y = %d", x, y);
      fflush (stdout);
      found = 1;
      break;
    } else if (res < 1 || contador > 4) {
      /* impossivel encontrar para este x */
      break;
    }
    contador++;
    y++;
  }
  if (found == 1) {
    break;
  }
  x++;
}
return x;
}
/******************************************************************************/
int *preencheIndicesAteMAXINDICE (int d, int maxIndice, int *periodo) {
/* cria dinamicamente um vector de indices e preenche com os indices de frações
continuadas para a raiz de d, devolve o comprimento do periodo por referencia */
int *indices, a0, mN, dN, aN, contadorPeriodo, found = 0;

indices = (int*) calloc (maxIndice, sizeof (int));
if (indices == NULL) {
  return NULL;
}

indices[0] = calculaAproximacaoRaiz (d);
a0 = indices[0];
/* inicialização das variaveis */
mN = 0;
dN = 1;
aN = a0;
contadorPeriodo = 1;
while (contadorPeriodo < maxIndice) {
  mN = mNextCalc (dN, aN, mN);
  dN = dNextCalc (d, mN, dN);
  aN = calculaANeAproxima (a0, mN, dN);
  if (contadorPeriodo == maxIndice) {
    printf ("\nFoi ultrapassado o limite do vector periodo.");
    return NULL;
  }
  indices[contadorPeriodo] = aN;
  if (aN == 2*a0 && found == 0) {
    *periodo = contadorPeriodo;
    found = 1;
  }
  contadorPeriodo++;
}
return indices;
}
/******************************************************************************/
int calculaAproximacaoRaiz (int nTeste) {
/* calcula primeira aproximcao para o nTeste*/

double raiz;
int iRaiz, n;
raiz = sqrt (nTeste);
iRaiz = (int) raiz;
return (iRaiz);
}
/******************************************************************************/
int mNextCalc (int dN, int aN, int mN) {
/* calcula m N+1 e devolve o inteiro correspondente */
int res;
res = dN*aN - mN;
return res;
}
/******************************************************************************/
int dNextCalc (int s, int mN, int dN) {
/* calcula o d N+1 e devolve o inteiro correspondente */
int res;
res = (s-pow(mN, 2)) / dN;
return res;
}
/******************************************************************************/
int calculaANeAproxima (int a0, int mN, int dN) {
/* calcula a N+1 e faz logo a seguir a aproximação */
double resF;
int res;
resF = ((float) a0 + mN)/dN;
res = (int) resF;
return res;
}
/******************************************************************************/
void calculaProximaFracao (fracao *v, int passo, int *indices) {
/* calcula a proxima fracao e retorna a função principal */
int n[DIMFRACAO] = {0}, d[DIMFRACAO] = {0}, a, i, carry = 0;

a = indices[passo];

/* copia de valores de v->numerador e v->denominador para n e d */
for (i = 0; i < DIMFRACAO; i++) {
    n[i] = v->x[i];
    d[i] = v->y[i];
}
/* calculo da nova fraçao */
/* v->numerador = d */
for (i = 0; i < DIMFRACAO; i++) {
  v->x[i] = d[i];
}
/* v->denominador = a*d+n */
for (i = 0; i < DIMFRACAO; i++) {
  v->y[i] = a*d[i]+n[i]+carry;
  if (v->y[i] > 9) {
    carry = v->y[i] / 10;
    v->y[i] = v->y[i] % 10;
  } else {
    carry = 0;
  }
}
return;
}
/******************************************************************************/
void calculaUltimaParcela (fracao *v, int passo, int *indices) {
/* calcula a ultima parcela da fracao */
int n[DIMFRACAO] = {0}, d[DIMFRACAO] = {0}, a, i, carry = 0;

/* copia de valores de v->numerador e v->denominador para n e d */
for (i = 0; i < DIMFRACAO; i++) {
    n[i] = v->x[i];
    d[i] = v->y[i];
}
a = indices[passo];
/* calculo da nova fraçao */
/* v->numerador = a*d+n */
/* v->denominador = d */
for (i = 0; i < DIMFRACAO; i++) {
  v->x[i] = a*d[i]+n[i]+carry;
  if (v->x[i] > 9) {
    carry = v->x[i] / 10;
    v->x[i] = v->x[i] % 10;
  } else {
    carry = 0;
  }
}
return;
}
/******************************************************************************/
int testaSolucao(fracao *v, int d) {
/* verifica se x² - D*y² = 1, se sim então retorna 1, senão retorna 0 */
fracao resultado;
int i, booleano, k, nAlg, found;
/* vou agora zerar o resultado */
for (i = 0; i < DIMFRACAO; i++) {
  resultado.x[i] = 0;
  resultado.y[i] = 0;
}
/* primeiro tenho de calcular x² */
calculaQuadrado (resultado.x, v->x, DIMFRACAO);
/* depois tenho de calcular y² */
calculaQuadrado (resultado.y, v->y, DIMFRACAO);
/* depois tenho de multiplicar y² por D */
potenciaN (resultado.y, d, DIMFRACAO);
/* por fim tenho de somar 1 a y²*D */
somaNumeroAvector (resultado.y, 1, DIMFRACAO);
/* agora tenho de testar se o vector x² e D*y²+1 são iguais */
booleano = testaIgualdadeDigitos (resultado.x, resultado.y, DIMFRACAO);
if (booleano == 1) {
  return 1;
} else {
  return 0;
}

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
    vNum[j] = vNum[j] % 10;
  }
}
return;
}
/******************************************************************************/
void somaNumeroAvector (int *vNum, int nTeste, int nDigits) {
/* soma um numero reduzido a um vector com nDigits e depois retorna à função */
int i, carry = 0;
/* inicio da soma */
vNum[0] = vNum[0] + nTeste;
for (i = 0; i < nDigits; i++) {
  vNum[i] = vNum[i] + carry;
  if (vNum[i] > 9) {
    carry = vNum[i] / 10;
    vNum[i] = vNum[i] % 10;
  } else {
    carry = 0;
  }
}
return;
}
/******************************************************************************/
int testaIgualdadeDigitos (int *v1, int *v2, int nDigits) {
/* testa igualdade de digitos entre dois vectores com nDigitos,
retorna 1 se os digitos forem iguais ou 0 se não forem */
int i;

for (i = 0; i < nDigits; i++) {
  if (v1[i] != v2[i]) {
    return 0;
  }
}
/* se chega aqui é porque são iguais os digitos dos vectores */
return 1;
}
/******************************************************************************/
void calculaQuadrado (int *res, int *mult, int nDigits) {
/* calcula o resultado no vector res de nDigits da multiplicação
do vector de mult * mult*/
int i,j, k, carry, nTeste, *vNum;

for (i = 0; i < nDigits; i++) {
  nTeste = mult[i];
  /* caso em que o numero é zero, neste caso não faço nada*/
  if (nTeste == 0) {
    continue;
  }

  carry = 0;
  vNum = (int*) calloc (nDigits, sizeof (int));
  if (vNum == NULL) {
    printf ("\nOcorreu um erro na criação do vector vNum.");
    return;
  }
  /* copia de mult para vNum */
  for (j = 0; j < nDigits; j++) {
    vNum[j] = mult[j];
  }

  /* aqui eu calculo cada uma das parcelas que eu depois vou somar */
  for (j = 0; j < nDigits; j++) {
    vNum[j] = vNum[j] * nTeste + carry;
    if (vNum[j] < 10) {
      carry = 0;
    } else {
      carry = vNum[j] / 10;
      vNum[j] = vNum[j] % 10;
    }
  }

  /* chegado aqui eu vou ter de somar vNum a res, apartir de i digitos */
  carry = 0;
  k = 0;
  for (j = i; j < nDigits; j++) {
    res[j] = res[j] + vNum[k] + carry;
    if (res[j] > 9) {
      carry = res[j] / 10;
      res[j] = res[j] % 10;
    } else {
      carry = 0;
    }
    k++;
  }
  free (vNum);
}
return;
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
int nAlgCalc (int *x, int nAlgMax) {
/* calcula o número de algarismos de x e devolve o inteiro */
int contadorZeros = 0, i, nAlg;

for (i = nAlgMax-1; i > -1; i--) {
  if (x[i] == 0) {
    contadorZeros++;
  } else {
    break;
  }
}
nAlg = nAlgMax - contadorZeros;
return (nAlg);
}
/******************************************************************************/
int compara2Numeros (int *v0, int *v1, int nDigits) {
/* compara 2 numeros com nDigitps, retorna 0 se maximo e v0,
se booleano = 1 então o maximo e v1 */
int i;

for (i = nDigits-1; i > -1; i--) {
  if (v0[i] == 0 && v1[i] == 0) {
    continue;
  } else if (v0[i] > v1[i]) {
    return 0;
  } else if (v0[i] < v1[i]) {
    return 1;
  } else {
    continue;
  }
}
/* se chega aqui é porque são iguais, logo mantem-se tudo igual */
return 0;
}
/******************************************************************************/
