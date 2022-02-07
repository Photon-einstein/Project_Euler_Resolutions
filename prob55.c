#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX 10000
#define TECTO 50

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/
int *preencheVectorDigit (int contador, int dim, int nAlg);

/* cria dinamicamente um vector digit invertido e retorna o apontador dele */
int *criaVectorDigitInvertido (int *nDigit, int nAlg);

/* produz dinamicamente um vector soma, e soma membro a membro os 2 vectores,
calculando o carry e soma-o e retorna o apontador */
/* retorna por referencia na flag 1 se nAlg++ ou 0 se mantem */
int *somaIterativa (int *nDigit, int *nDigitInverte, int nAlg, int *booleanoDigitUp);

/* testa se os dois vectores produzem o mesmo numero, e assim o numero a testar
e palindrome, se sim retorna 1, se não retorna 0 */
int booleanoTestaPalindromeVector (int *nDigit, int *nDigitInverte, int nAlg);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
int nTeste, nIteracao, nLychrel = 0, dim, nAlg, *nDigit, *nDigitInverte, *soma;
int booleanoDigitUp, booleano;

for (nTeste = 10; nTeste < MAX; nTeste++) {
  nIteracao = 0;
  dim = dimCalc (nTeste, &nAlg);
  nDigit = preencheVectorDigit (nTeste, dim, nAlg);
  if (nDigit == NULL) {
    printf ("\nOcorreu uma falha na criação do vectorDigit.");
    return 0;
  }

  nDigitInverte = criaVectorDigitInvertido (nDigit, nAlg);
  if (nDigitInverte == NULL) {
    free (nDigit);
    printf ("\nOcorreu uma falha na criação do vectorDigit.");
    return 0;
  }

  while (nIteracao < TECTO) {
    soma = somaIterativa (nDigit, nDigitInverte, nAlg, &booleanoDigitUp);
    if (soma == NULL) {
      free (nDigit);
      free (nDigitInverte);
      printf ("\nOcorreu uma falha na criação do vector soma.");
      return 0;
    }
    if (booleanoDigitUp == 1) {
      nAlg++;
    }

    free (nDigit);
    free (nDigitInverte);

    nDigit = soma;
    nDigitInverte = criaVectorDigitInvertido (nDigit, nAlg);
    if (nDigitInverte == NULL) {
      free (nDigit);
      printf ("\nOcorreu uma falha na criação do vectorDigit.");
      return 0;
    }

    booleano = booleanoTestaPalindromeVector (nDigit, nDigitInverte, nAlg);
    if (booleano == 1) {
      /* neste caso e palindrome */
      free (nDigit);
      free (nDigitInverte);
      break;
    }

    nIteracao++;
  }

  if (nIteracao == TECTO) {
    /* neste caso temos um numero de Lychrel */
    nLychrel++;
    /*printf ("\nLyckrel nº%d = %d com nAlg = %d.", nLychrel, nTeste, nAlg); */
  }
}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nAté 10000 existem %d número de Lychrel.", nLychrel);
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

/* cria dinamicamente um vector digit invertido e retorna o apontador dele */
int *criaVectorDigitInvertido (int *nDigit, int nAlg) {

int i;
int *vDigitInv;

vDigitInv = (int*) calloc (nAlg, sizeof (int));
if (vDigitInv == NULL) {
  printf ("\nErro na criação do vector vDigitInv.");
  return NULL;
}

for (i = 0; i < nAlg; i++) {
  vDigitInv[i] = nDigit [nAlg-1-i];
}

return vDigitInv;
}

/******************************************************************************/

int *somaIterativa (int *nDigit, int *nDigitInverte, int nAlg, int *booleanoDigitUp) {
/* produz dinamicamente um vector soma, e soma membro a membro os 2 vectores,
calculando o carry e soma-o e retorna o apontador */
/* retorna por referencia na flag 1 se nAlg++ ou 0 se mantem */

int *soma, carry = 0, *somaOverflow, i;

soma = (int*) calloc (nAlg, sizeof (int));
if (soma == NULL) {
  printf ("\nErro na criação do vector soma.");
  return NULL;
}

for (i = nAlg-1; i > -1; i--) {
  soma[i] = nDigit[i] + nDigitInverte[i] + carry;
  if (soma[i] > 9) {
    carry = soma[i] / 10;
    soma [i] = soma[i] % 10;
  } else {
    carry = 0;
  }
}

/* teste a ver se o ultimo digito tem overflow */
if (carry == 0) {
  /* neste caso não há overflow */
  *booleanoDigitUp = 0;
  return soma;
} else {
  /* neste caso há overflow */
  somaOverflow = (int*) calloc (nAlg+1, sizeof (int));
  if (somaOverflow == NULL) {
    printf ("\nErro na criação do vector somaOverflow.");
    return NULL;
  }

  for (i = nAlg-1; i > -1; i--) {
    somaOverflow[i+1] = soma[i];
  }

  /* falta agora acertar o ultimo digito */
  somaOverflow[0] = carry;

  /* libertar memoria desnecessaria */
  free (soma);
  *booleanoDigitUp = 1;
  return somaOverflow;
}

}

/******************************************************************************/

int booleanoTestaPalindromeVector (int *nDigit, int *nDigitInverte, int nAlg) {
/* testa se os dois vectores produzem o mesmo numero, e assim o numero a testar
e palindrome, se sim retorna 1, se não retorna 0 */
int i;

for (i = 0; i < nAlg; i++) {
  if (nDigit[i] != nDigitInverte[i]) {
    /* neste caso não e palindrome */
    return 0;
  }
}

/* se chega aqui e porque e palindrome */
return 1;
}

/******************************************************************************/
