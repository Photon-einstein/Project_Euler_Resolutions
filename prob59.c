#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZECIFRAS 2000
#define SIZEPALAVRAS 3001
#define PALAVRA 80
#define MIN 97
#define MAX 122

/* cria dinamicamente um vector de int e guarda as cifras no vector,
e devolve nChar por referencia */
int* leCifra (FILE *f, int *nChar, int size);

/* cria dinamicamente um vector de int e guarda as palavras num vector,
e devolve nChar por referencia */
char **lePalavras (FILE *f, int *nPalavras, int size, int tamanhoPalavra);

/* cria dinamicamente um vector de char, de dim nChar, e faz a conversao do
vector de inteiros  cifras para char e, retorna apontador */
char *conversaoIntCharCifras (int *cifras, int nChar);

/* devolve o numero de reps e o apontador da cifra desincriptada. Faz o XOR com a cifra ijk no vector de
caracteres e depois corre um strstr para as 3000 palavras aplicado ao vector cifrasChar,
se o apontador de strstr for diferente de NULL mais do que x vezes, então retorna 1,
senão retorna 0 */
char* testaCifra (int *cifrasInt, int nChar, char **palavras, int nPalavras, int i, int j, int k, int *reps);

/* com a cifra desincriptada, faz a soma dos caracteres e devolve o valor da soma*/
int somaCaracteres (char *cifrasChar, int nChar);

/* faz uma copia do vector e retorna o apontador */
int* copiaVectorIntCifras (int *cifras, int nChar);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
/* cipher.txt, palavrasEngComuns.txt */
FILE *f;
int *cifras, nChar, nPalavras, i, j, k, reps, repMax = 0, sumAsci = 0, n, *cifrasInt;
char **palavras, *cifrasChar;

f = fopen ("cipher.txt", "r");
if (f == NULL) {
  printf ("\nOcorreu uma falha a abrir o ficheiro.");
  return 0;
}

cifras = leCifra (f, &nChar, SIZECIFRAS);
if (cifras == NULL) {
  printf ("\nOcorreu um problema na leitura das cifras.");
  return 0;
}

f = fopen ("palavras.txt", "r");
if (f == NULL) {
  printf ("\nOcorreu uma falha a abrir o ficheiro.");
  return 0;
}

palavras = lePalavras (f, &nPalavras, SIZEPALAVRAS, PALAVRA);


for (i = MIN; i < MAX+1;i++) {
  for (j = MIN; j < MAX+1; j++) {
    for (k = MIN; k < MAX+1; k++) {
      cifrasInt = copiaVectorIntCifras (cifras, nChar);
      if (cifrasInt == NULL) {
        printf ("\nOcorreu um problema na cópia das cifras.");
        return 0;
      }
      cifrasChar = testaCifra (cifrasInt, nChar, palavras, nPalavras, i, j, k, &reps);
      if (reps > repMax) {
        repMax = reps;
        sumAsci = somaCaracteres (cifrasChar, nChar);
      }
      free (cifrasChar);
    }
  }
}
free (cifras);

/* libertação da memória total */
for (i = 0; i < nPalavras; i++) {
  free (palavras[i]);
}
free(palavras);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nA soma dos caracteres ASCI do texto original é %d com hitsMax = %d.", sumAsci, repMax);
printf ("\n");
return 0;
}

/******************************************************************************/

int* leCifra (FILE *f, int *nChar, int size) {
/* cria dinamicamente um vector de int e guarda as cifras no vector,
e devolve nChar por referencia */

int *cifras;
int i = 0, j = 1;

cifras = (int*) calloc (size, sizeof (int));
if (cifras == NULL) {
  return NULL;
}

while ((fscanf (f, "%d,", &cifras[i])) != EOF) {
  i++;
  if (i == size) {
    break;
    j++;
    cifras = (int*)realloc (cifras, size*j*sizeof (int));
    if (cifras == NULL) {
      return NULL;
    }
  }
}

*nChar = i;
return cifras;
}

/******************************************************************************/

char **lePalavras (FILE *f, int *nPalavras, int size, int tamanhoPalavra) {
/* cria dinamicamente um vector de int e guarda as palavras num vector,
e devolve nChar por referencia */

char **palavras;
int i = 0, j;

palavras = (char**) calloc (size, sizeof (char*));
if (palavras == NULL) {
  return NULL;
}

for (i = 0; i < size; i++) {
  palavras[i] = (char*) calloc (tamanhoPalavra, sizeof (char));
  if (palavras[i] == NULL) {
    return NULL;
  }
}
i = 0;

while ( fscanf (f, "%s\n", palavras[i]) != EOF) {
  i++;
  if (i == size) {
    printf ("\nTamanho excedido.");
    break;
    }
  }

j = i;
for (i; i < size; i++) {
  free (palavras[i]);
}
palavras = (char**) realloc (palavras, j*sizeof (char*));
if (palavras == NULL) {
  return NULL;
}
*nPalavras = j;
return palavras;
}

/******************************************************************************/

char *conversaoIntCharCifras (int *cifras, int nChar) {
/* cria dinamicamente um vector de char, de dim nChar, e faz a conversao do
vector de inteiros  cifras para char e, retorna apontador */

char *cifrasChar;
int i;

cifrasChar = (char*) calloc (nChar+1, sizeof (char));
if (cifrasChar == NULL) {
  return NULL;
}

for (i = 0; i < nChar; i++) {
  cifrasChar[i] = (char)cifras[i];
}
cifrasChar[nChar] = '\0';
return cifrasChar;
}

/******************************************************************************/

char* testaCifra (int *cifrasInt, int nChar, char **palavras, int nPalavras, int i, int j, int k, int *reps) {
  /* devolve o nº de reps. Faz o XOR com a cifra ijk no vector de
  caracteres e depois corre um strstr para as 3000 palavras aplicado ao vector cifrasChar,
  se o apontador de strstr for diferente de NULL mais do que x vezes, então retorna 1,
  senão retorna 0 */

/*cifra ijk, produção da cifra */
char *match, *cifrasChar;
int n, cifra[3], repsC = 0;

cifra[0] = i;
cifra[1] = j;
cifra[2] = k;

/* codigo XOR cifra */
for (n = 0; n < 400; n++) {
  /* XOR a blocos de 3*/
  cifrasInt[n*3] = cifrasInt[n*3]^cifra[0];
  cifrasInt[n*3+1] = cifrasInt[n*3+1]^cifra[1];
  cifrasInt[n*3+2] = cifrasInt[n*3+2]^cifra[2];
}
/* ultimo elemento */
cifrasInt[nChar-1] = cifrasInt[nChar-1]^cifra[0];
cifrasChar = conversaoIntCharCifras (cifrasInt, nChar);

for (n = 0; n < nPalavras; n++) {
  match = strstr (cifrasChar, palavras[n]);
  if (match != NULL) {
    repsC++;
  }
}
*reps = repsC;
return cifrasChar;
}

/******************************************************************************/

int somaCaracteres (char *cifrasChar, int nChar) {
/* com a cifra desincriptada, faz a soma dos caracteres e devolve o valor da soma*/

int i, soma = 0;

for (i = 0; i < nChar; i++) {
  soma = soma + cifrasChar[i];
}
return soma;
}

/******************************************************************************/

int* copiaVectorIntCifras (int *cifras, int nChar) {
/* faz uma copia do vector e retorna o apontador */
int *cifrasInt, i;

cifrasInt = (int*) calloc (nChar, sizeof (int));
if (cifrasInt == NULL) {
  return NULL;
}

for (i = 0; i < nChar; i++) {
  cifrasInt[i] = cifras[i];
}
return cifrasInt;
}

/******************************************************************************/
