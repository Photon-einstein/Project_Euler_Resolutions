#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIMM 80
typedef struct {
	int val;
	int upperMin; /* tanto sobe como vai para a direita */
	int lowerMin; /* tanto desce como vai para a direita */
	int absMin;
} dados;

/*  preenche com os dados presentes no ficheiro, retorna 1 se a função funcionar
bem ou 0 se não funcionar bem */
int lerDados (dados **matriz, char *nomeFicheiro, int dimMax);

/* apaga completamente a matriz e depois retorna a funcao principal */
void apagaMatriz (dados **matriz, int dimMax);

/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso ou 0 se não */
int preencherMinimoLower (dados **matriz, int dimMax);

/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso ou 0 se não */
int preencherMinimoUpper (dados **matriz, int dimMax);

/* esta funcao vai a matriz e calcula o minimo absoluto para cada uma das posicoes,
retorna 1 se correr tudo bem ou 0 se houver algum erro */
int calculaMinAbsoluto (dados **matriz, int dimMax);

/* faz uma correcao ao minimo absoluto e depois corrige ou mantem,
retorna 1 se correr bem e houver alteracao ou 2 se correr bem sem alteracao
 ou 0 se houver problema */
int correcaoValoresADescer (dados **matriz, int dimMax);

/* esta funcao calcula o minimo da ultima coluna da matriz, retorna o minimo
se correr tudo bem ou -1 se houver algum erro */
int calculaResposta (dados **matriz, int dimMax);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
dados **matriz;
int i, j, booleano, resposta;
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
/* resolucao do problema */
booleano = preencherMinimoUpper (matriz, DIMM);
if (booleano == 0) {
  printf ("\nOcorreu um erro na funcao de preencher minimosUpper.");
  return 0;
}
booleano = preencherMinimoLower (matriz, DIMM);
if (booleano == 0) {
  printf ("\nOcorreu um erro na funcao de preencher minimosLower.");
  return 0;
}

do {
	booleano = correcaoValoresADescer (matriz, DIMM);
	if (booleano == 0) {
	  printf ("\nOcorreu um erro na funcao de preencher minimos absoluto.");
	  return 0;
	}
} while (booleano == 1);

booleano = calculaMinAbsoluto (matriz, DIMM);
if (booleano == 0) {
  printf ("\nOcorreu um erro na funcao de preencher minimos absoluto.");
  return 0;
}
resposta = calculaResposta (matriz, DIMM);
if (resposta == -1) {
  printf ("\nOcorreu um erro na funcao de calcular resposta.");
  return 0;
}
/*printf ("\nImpressao dos minimos absolutos da matriz:\n");
for (i = 0; i < DIMM; i++) {
	for (j = 0; j < DIMM; j++) {
		printf ("%d\t", matriz[i][j].absMin);
	}
	printf ("\n");
}*/

/* fim da resolucao do problema */
apagaMatriz (matriz, DIMM);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nO minimo com 3 ways e de %d.", resposta);
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
/*printf ("\nImpressao da matriz original:\n");*/
for (linha = 0; linha < dimMax; linha++) {
  for (coluna = 0; coluna < dimMax; coluna++) {
    fscanf (f, "%d,", &matriz[linha][coluna].val);
		/*printf ("%d\t", matriz[linha][coluna].val);*/
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
int preencherMinimoLower (dados **matriz, int dimMax) {
/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso ou 0 se não */
if (matriz == NULL || dimMax <= 0) {
  return 0;
}

int linha, coluna, posL, posU, miniL, miniU, validAns;

for (linha = 0; linha < dimMax; linha++) {
  for (coluna = 0; coluna < dimMax; coluna++) {
		if (coluna == 0) {
      /* primeiro valor da matriz sera os dados da primeira coluna */
      matriz[linha][coluna].lowerMin =  matriz[linha][coluna].val;
      continue;
    }
    /* vamos agora processar os restantes valores das restantes colunas */
    validAns = 0;
    miniL = 0;
    miniU = 0;
    posL = coluna-1;
    posU = linha-1;
    /* teste valor a esquerda */
    if (posL >= 0) {
      validAns++;
      miniL = matriz[linha][posL].lowerMin;
    }
    /* teste valor cima */
    if (posU >= 0) {
      validAns++;
      miniU = matriz[posU][coluna].lowerMin;
    }
    /* teste de qual o minimo a incluir na memoria */
    if (validAns == 1) {
      /* apenas ha um minimo aceitavel */
      if (miniL != 0) {
        matriz[linha][coluna].lowerMin = matriz[linha][coluna].val + miniL;
      } else {
        matriz[linha][coluna].lowerMin = matriz[linha][coluna].val + miniU;
      }
    } else {
      /* neste caso temos 2 minimos possiveis */
      if (miniL < miniU) {
        /* vou pela esquerda */
        matriz[linha][coluna].lowerMin = matriz[linha][coluna].val + miniL;
      } else {
        /* neste caso vou por cima */
        matriz[linha][coluna].lowerMin = matriz[linha][coluna].val + miniU;
      }
    }
  }
}
/* se chega aqui e porque a funcao correu sem erros */
return 1;
}
/******************************************************************************/
int preencherMinimoUpper (dados **matriz, int dimMax) {
/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso ou 0 se não */
if (matriz == NULL || dimMax <= 0) {
  return 0;
}

int linha, coluna, posL, posD, miniL, miniD, validAns;

for (linha = dimMax-1; linha > -1; linha--) {
  for (coluna = 0; coluna < dimMax; coluna++) {
		if (coluna == 0) {
      /* primeiro valor da matriz serao os dados da primeira coluna */
      matriz[linha][coluna].upperMin =  matriz[linha][coluna].val;
      continue;
    }
    /* vamos agora processar os restantes valores das restantes colunas */
    validAns = 0;
    miniL = 0;
    miniD = 0;
    posL = coluna-1;
    posD = linha+1;
    /* teste valor a esquerda */
    if (posL >= 0) {
      validAns++;
      miniL = matriz[linha][posL].upperMin;
    }
    /* teste valor cima */
    if (posD < dimMax) {
      validAns++;
      miniD = matriz[posD][coluna].upperMin;
    }
    /* teste de qual o minimo a incluir na memoria */
    if (validAns == 1) {
      /* apenas ha um minimo aceitavel */
      if (miniL != 0) {
        matriz[linha][coluna].upperMin = matriz[linha][coluna].val + miniL;
      } else {
        matriz[linha][coluna].upperMin = matriz[linha][coluna].val + miniD;
      }
    } else {
      /* neste caso temos 2 minimos possiveis */
      if (miniL < miniD) {
        /* vou pela esquerda */
        matriz[linha][coluna].upperMin = matriz[linha][coluna].val + miniL;
      } else {
        /* neste caso vou por cima */
        matriz[linha][coluna].upperMin = matriz[linha][coluna].val + miniD;
      }
    }
  }
}
/* se chega aqui e porque a funcao correu sem erros */
return 1;
}
/******************************************************************************/
int correcaoValoresADescer (dados **matriz, int dimMax) {
/* faz uma correcao ao minimo absoluto e depois corrige ou mantem,
retorna 1 se correr bem e houver alteracao ou 2 se correr bem sem alteracao
 ou 0 se houver problema */
if (matriz == NULL || dimMax <= 0) {
	return 0;
}
/* vamos agora corrigir a situacao de um upperMin estar ok e a celula em baixo
estar errada */
int linha, coluna, pos, val, alteracao = 2;
for (linha = 0; linha < dimMax; linha++) {
	for (coluna = 0; coluna < dimMax; coluna++) {
		/* erro 1.1: apartir de cima */
		pos = linha-1;
		if (pos >= 0) {
			val = matriz[pos][coluna].upperMin + matriz[linha][coluna].val;
			if (val < matriz[linha][coluna].lowerMin) {
				matriz[linha][coluna].lowerMin = val;
				alteracao = 1;
			}
		}
		/* erro 1.2: apartir de cima */
		pos = linha-1;
		if (pos >= 0) {
			val = matriz[pos][coluna].lowerMin + matriz[linha][coluna].val;
			if (val < matriz[linha][coluna].upperMin) {
				matriz[linha][coluna].upperMin = val;
				alteracao = 1;
			}
		}
		/* erro 2.1: apartir da esquerda */
		pos = coluna-1;
		if (pos >= 0) {
			val = matriz[linha][pos].lowerMin + matriz[linha][coluna].val;
			if (val < matriz[linha][coluna].upperMin) {
				matriz[linha][coluna].upperMin = val;
				alteracao = 1;
			}
		}
		/* erro 2.2: apartir da esquerda */
		pos = coluna-1;
		if (pos >= 0) {
			val = matriz[linha][pos].upperMin + matriz[linha][coluna].val;
			if (val < matriz[linha][coluna].lowerMin) {
				matriz[linha][coluna].lowerMin = val;
				alteracao = 1;
			}
		}
		/* erro 3.1: apartir de baixo */
		pos = linha+1;
		if (pos < dimMax) {
			val = matriz[pos][coluna].lowerMin + matriz[linha][coluna].val;
			if (val < matriz[linha][coluna].upperMin) {
				matriz[linha][coluna].upperMin = val;
				alteracao = 1;
			}
		}
		/* erro 3.2: apartir de baixo */
		pos = linha+1;
		if (pos < dimMax) {
			val = matriz[pos][coluna].upperMin + matriz[linha][coluna].val;
			if (val < matriz[linha][coluna].lowerMin) {
				matriz[linha][coluna].lowerMin = val;
				alteracao = 1;
			}
		}
	}
}
return alteracao;
}
/******************************************************************************/
int calculaMinAbsoluto (dados **matriz, int dimMax) {
/* esta funcao vai a matriz e calcula o minimo absoluto para cada uma das posicoes,
retorna 1 se correr tudo bem ou 0 se houver algum erro */
if (matriz == NULL || dimMax <= 0) {
	return 0;
}
int linha, coluna;
for (linha = 0; linha < dimMax; linha++) {
	for (coluna = 0; coluna < dimMax; coluna++) {
		if (matriz[linha][coluna].upperMin < matriz[linha][coluna].lowerMin) {
			matriz[linha][coluna].absMin = matriz[linha][coluna].upperMin;
		} else {
			matriz[linha][coluna].absMin = matriz[linha][coluna].lowerMin;
		}
	}
}
return 1;
}
/******************************************************************************/
int calculaResposta (dados **matriz, int dimMax) {
/* esta funcao calcula o minimo da ultima coluna da matriz, retorna o minimo
se correr tudo bem ou -1 se houver algum erro */
if (matriz == NULL || dimMax <= 0) {
	return -1;
}
int linha, minimo, coluna = dimMax-1;

for (linha = 0; linha < dimMax; linha++) {
	if (linha == 0) {
		minimo = matriz[linha][coluna].absMin;
		continue;
	}
	if (minimo > matriz[linha][coluna].absMin) {
			minimo = matriz[linha][coluna].absMin;
	}
}
return minimo;
}
/******************************************************************************/
