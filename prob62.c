#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZE 10000
typedef struct {
  int nTeste;
  int nAlg;
  int *nDigit;
  int contaD[10];
} cube;

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector, e inverte os digitos*/
int *preencheVectorDigitEinverte (int contador, int dim, int nAlg, int nAlgMax);

/* multiplica o numero vNum por nTeste, ou seja faz nTeste^x e retorna à função principal */
int* potenciaN (int* vNum, int nTeste, int nDigits);

/* devolve o numero de algarismos significativos */
int calcNAlgarismos (cube *vector, int contador, int nAlgMax);

/* preenche o contaD com o numero de algarismos com determinado numero*/
void contaDigitos (cube *vector, int contador, int nAlgMax);

/* verifica igualdade de digitos entre dois cubos, retorna 1 se iguais ou 0 se
diferentes*/
int  verificaIgualdadeDigitos (cube *vector, int i, int j);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int nTeste, dim, nAlg, contador = 0, j, nAlgRef, nPermut, i, booleano, found;
cube *v;

v = (cube*) calloc (SIZE, sizeof (cube));
if (v == NULL) {
  printf ("\nOcorreu um erro a gerar o cube.");
  return 0;
}

/* preenchimento dos cubos até 999*/
for (nTeste = 2; nTeste < SIZE; nTeste++) {
  dim = dimCalc (nTeste, &nAlg);
  v[contador].nTeste = nTeste;
  v[contador].nDigit = preencheVectorDigitEinverte (nTeste, dim, nAlg, 3*nAlg);
  if (v[contador].nDigit == NULL) {
    printf ("\nOcorreu um erro a criar o vector digitos.");
    return 0;
  }
  for (j = 0; j < 2; j++) {
    v[contador].nDigit = potenciaN (v[contador].nDigit, nTeste, 3*nAlg);
    if (v[contador].nDigit == NULL) {
      printf ("\nOcorreu um erro a criar o vector digitos.");
      return 0;
    }
  }
  v[contador].nAlg = calcNAlgarismos (v, contador, 3*nAlg);
  v[contador].nDigit = realloc (v[contador].nDigit, v[contador].nAlg*sizeof (int));
  if (v[contador].nDigit == NULL) {
    printf ("\nOcorreu uma falha na realocagem.");
    return 0;
  }
  contaDigitos (v, contador, v[contador].nAlg);
  contador++;
}

/* falta agora testar cada um dos cubos, para cada nAlg, e verificando os seus
digitos, se nAlg forem iguais e o vector de contaDigitos também for igual então
está tudo ok*/
for (i = 0; i < contador-1; i++) {
  nAlgRef = v[i].nAlg;
  nPermut = 1;
  for (j = i+1;  j < contador; j++) {
    if (v[j].nAlg > nAlgRef) {
      break;
    }
    booleano = verificaIgualdadeDigitos (v, i, j);
    if (booleano == 0) {
      continue;
    }
    nPermut++;
  }
  if (nPermut == 5) {
    found = 1;
    break;
  }
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
if (found == 1) {
  printf ("\nO cubo mais pequeno é %d ao cubo.", v[i].nTeste);
  printf ("\nDigitos: ");
  for (j = v[i].nAlg-1; j > -1; j--) {
    printf ("%d", v[i].nDigit[j]);
  }
} else {
  printf ("\nNão foi encontrado nenhum cubo desses.");
}

for (i = 0; i < contador; i++) {
  free (v[i].nDigit);
}
free (v);
printf ("\n");
return 0;
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
int* potenciaN (int* vNum, int nTeste, int nDigits) {
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

return vNum;
}
/******************************************************************************/
int calcNAlgarismos (cube *vector, int contador, int nAlgMax) {
/* devolve o numero de algarismos significativos */
int i, n = 0, res;

for (i = nAlgMax-1; i > -1; i--) {
  if (vector[contador].nDigit[i] == 0) {
    n++;
  } else {
    break;
  }
}

res = nAlgMax-n;
return res;
}
/******************************************************************************/
void contaDigitos (cube *vector, int contador, int nAlgMax) {
/* preenche o contaD com o numero de algarismos com determinado numero*/
int i;

for (i = 0; i < 10; i++) {
  vector[contador].contaD[i] = 0;
}

for (i = 0; i < nAlgMax; i++) {
  if (vector[contador].nDigit[i] == 0) {
    vector[contador].contaD[0]++;
  } else if (vector[contador].nDigit[i] == 1) {
    vector[contador].contaD[1]++;
  } else if (vector[contador].nDigit[i] == 2) {
    vector[contador].contaD[2]++;
  } else if (vector[contador].nDigit[i] == 3) {
    vector[contador].contaD[3]++;
  } else if (vector[contador].nDigit[i] == 4) {
    vector[contador].contaD[4]++;
  } else if (vector[contador].nDigit[i] == 5) {
    vector[contador].contaD[5]++;
  } else if (vector[contador].nDigit[i] == 6) {
    vector[contador].contaD[6]++;
  } else if (vector[contador].nDigit[i] == 7) {
    vector[contador].contaD[7]++;
  } else if (vector[contador].nDigit[i] == 8) {
    vector[contador].contaD[8]++;
  } else {
    vector[contador].contaD[9]++;
  }
}
return;
}
/******************************************************************************/
int  verificaIgualdadeDigitos (cube *vector, int i, int j) {
  /* verifica igualdade de digitos entre dois cubos, retorna 1 se iguais ou 0 se
  diferentes*/
int n;

for (n = 0; n < 10; n++) {
  if (vector[i].contaD[n] != vector[j].contaD[n]) {
    return 0;
  }
}
/* se chega aqui é porque está tudo ok*/
return 1;
}
/******************************************************************************/
