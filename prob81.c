#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIMM 80
typedef struct {
	int val;
	int minVal;
} dados;

/*  preenche com os dados presentes no ficheiro, retorna 1 se a função funcionar
bem ou 0 se não funcionar bem */
int lerDados (dados **matriz, char *nomeFicheiro, int dimMax);

/* apaga completamente a matriz e depois retorna a funcao principal */
void apagaMatriz (dados **matriz, int dimMax);

/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso ou 0 se não */
int preencherMinimos (dados **matriz, int dimMax);


int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
dados **matriz;
int i, booleano, resposta;
char nomeFicheiro[12] = "matrix.txt";
/* criacao dinamica da matriz */
matriz = (dados**) calloc (DIMM, sizeof (dados*));
if (matriz == NULL) {
  printf ("\nOcorreu um erro a criar a matriz.");
  return 0;
}
for (i = 0; i < DIMM; i++) {
  matriz[i] = (dados*) calloc (DIMM, sizeof (dados));
  if (matriz[i] == NULL) {
    printf ("\nOcorreu um erro a criar o interior da matriz.");
    return 0;
  }
}
booleano = lerDados (matriz, nomeFicheiro, DIMM);
if (booleano == 0) {
  printf ("\nOcorreu um erro na funcao de ler os dados.");
  return 0;
}

booleano = preencherMinimos (matriz, DIMM);
if (booleano == 0) {
  printf ("\nOcorreu um erro na funcao de preencher minimos.");
  return 0;
}
resposta = matriz[DIMM-1][DIMM-1].minVal;
apagaMatriz (matriz, DIMM);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nO caminho minimo desde o cimoLeft ate ao fundoRight e de %d.", resposta);
printf ("\n");
return 0;
}
/******************************************************************************/
int lerDados (dados **matriz, char *nomeFicheiro, int dimMax) {
/* cria dinamicamentea matriz com dimensão dim*dim no maximo e depois preenche
com os dados presentes no ficheiro, retorna 1 se a função funcionar bem ou 0
se não funcionar bem */
if (nomeFicheiro == NULL || dimMax == 0) {
  return 0;
}
int passo, linha, coluna;
FILE *f;
f = fopen (nomeFicheiro, "r");
if (f == NULL) {
  return 0;
}
for (linha = 0; linha < dimMax; linha++) {
  for (coluna = 0; coluna < dimMax; coluna++) {
    fscanf (f, "%d,", &matriz[linha][coluna].val);
		/*printf ("%d ", matriz[linha][coluna].val);*/
  }
	/*printf ("\n");*/
}
/* se chega aqui é porque está tudo ok */
return 1;
}
/******************************************************************************/
void apagaMatriz (dados **matriz, int dimMax) {
/* apaga completamente a matriz e depois retorna a funcao principal */
if (matriz == NULL) {
	return;
}
int passo;
/* vou agora criar a matriz, a parte das colunas */
for (passo == 0; passo < dimMax; passo++) {
  free (matriz[passo]);
}
free (matriz);
return;
}
/******************************************************************************/
int preencherMinimos (dados **matriz, int dimMax) {
/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso ou 0 se não */
if (matriz == NULL || dimMax <= 0) {
  return 0;
}

int linha, coluna, posL, posU, miniL, miniU, validAns;

for (linha = 0; linha < dimMax; linha++) {
  for (coluna = 0; coluna < dimMax; coluna++) {
    if (linha == 0 && coluna == 0) {
      /* primeiro valor da matriz, matriz[0][0] */
      matriz[linha][coluna].minVal =  matriz[linha][coluna].val;
      continue;
    }
    /* vamos agora processar os restantes valores */
    validAns = 0;
    miniL = 0;
    miniU = 0;
    posL = coluna-1;
    posU = linha-1;
    /* teste valor a esquerda */
    if (posL >= 0) {
      validAns++;
      miniL = matriz[linha][posL].minVal;
    }
    /* teste valor cima */
    if (posU >= 0) {
      validAns++;
      miniU = matriz[posU][coluna].minVal;
    }
    /* teste de qual o minimo a incluir na memoria */
    if (validAns == 1) {
      /* apenas ha um minimo aceitavel */
      if (miniL != 0) {
        matriz[linha][coluna].minVal = matriz[linha][coluna].val + miniL;
      } else {
        matriz[linha][coluna].minVal = matriz[linha][coluna].val + miniU;
      }
    } else {
      /* neste caso temos 2 minimos possiveis */
      if (miniL < miniU) {
        /* vou pela esquerda */
        matriz[linha][coluna].minVal = matriz[linha][coluna].val + miniL;
      } else {
        /* neste caso vou por cima */
        matriz[linha][coluna].minVal = matriz[linha][coluna].val + miniU;
      }
    }
  }
}
/* se chega aqui e porque a funcao correu sem erros */
return 1;
}
/******************************************************************************/
