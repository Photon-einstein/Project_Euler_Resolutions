#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define DIMM 80
typedef struct {
	int val;
	int absMin;
} dados;

/*  preenche com os dados presentes no ficheiro, retorna 1 se a função funcionar
bem ou 0 se não funcionar bem */
int lerDados (dados **matriz, char *nomeFicheiro, int dimMax);

/* apaga completamente a matriz e depois retorna a funcao principal */
void apagaMatriz (dados **matriz, int dimMax);

/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
int preencherMinimoDownRightFirstTime (dados **matriz, int dimMax);

/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
int preencherMinimoDownLeft (dados **matriz, int dimMax);

/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
int preencherMinimoDownRight (dados **matriz, int dimMax);

/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
int preencherMinimoUpLeft (dados **matriz, int dimMax);

/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
int preencherMinimoUpRight (dados **matriz, int dimMax);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
dados **matriz;
int i, j, booleano, resposta, alteracao;
char nomeFicheiro[13] = "matrix.txt";
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
/* primeiro resolve-se com movimento: baixo e direita */
booleano = preencherMinimoDownRightFirstTime (matriz, DIMM);
if (booleano == 0) {
  printf ("\nOcorreu um erro na funcao de preencher minimosUpper.");
  return 0;
}

do {
	alteracao = 0;
	booleano = preencherMinimoDownRight (matriz, DIMM);
	if (booleano == 0) {
	  printf ("\nOcorreu um erro na funcao de preencher minimosUpper.");
	  return 0;
	}
	if (booleano == 2 && alteracao == 0) {
		alteracao = 1;
	}
	/* segundo resolve-se com movimento: baixo e esquerda */
	booleano = preencherMinimoDownLeft (matriz, DIMM);
	if (booleano == 0) {
	  printf ("\nOcorreu um erro na funcao de preencher minimosUpper.");
	  return 0;
	}
	if (booleano == 2 && alteracao == 0) {
		alteracao = 1;
	}
	/* terceiro resolve-se com movimento: cima e esquerda */
	booleano = preencherMinimoUpLeft  (matriz, DIMM);
	if (booleano == 0) {
	  printf ("\nOcorreu um erro na funcao de preencher minimosLower.");
	  return 0;
	}
	if (booleano == 2 && alteracao == 0) {
		alteracao = 1;
	}
	/* quarto resolve-se com movimento: cima e direita */
	booleano = preencherMinimoUpRight  (matriz, DIMM);
	if (booleano == 0) {
	  printf ("\nOcorreu um erro na funcao de preencher minimosLower.");
	  return 0;
	}
	if (booleano == 2 && alteracao == 0) {
		alteracao = 1;
	}
} while (alteracao == 1);

/*printf ("\nImpressao dos minimos absolutos da matriz:\n");
for (i = 0; i < DIMM; i++) {
	for (j = 0; j < DIMM; j++) {
		printf ("%d\t", matriz[i][j].absMin);
	}
	printf ("\n");
}*/
resposta = matriz[DIMM-1][DIMM-1].absMin;
/* fim da resolucao do problema */
apagaMatriz (matriz, DIMM);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nO caminho minimo desde a posicao (0,0) ate (DIMM-1, DIMM-1) e de %d.", resposta);
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
int preencherMinimoDownRightFirstTime (dados **matriz, int dimMax) {
/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 ou 0 se houver um erro de execucao do programa */
if (matriz == NULL || dimMax <= 0) {
  return 0;
}
int linha, coluna, posL, posU, miniL, miniU, validAns;

for (linha = 0; linha < dimMax; linha++) {
  for (coluna = 0; coluna < dimMax; coluna++) {
		if (coluna == 0 && linha == 0) {
      /* primeiro valor da matriz sera o dado da matriz[0][0] */
      matriz[linha][coluna].absMin =  matriz[linha][coluna].val;
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
      miniL = matriz[linha][posL].absMin;
    }
    /* teste valor cima */
    if (posU >= 0) {
      validAns++;
      miniU = matriz[posU][coluna].absMin;
    }
    /* teste de qual o minimo a incluir na memoria */
    if (validAns == 1) {
      /* apenas ha um minimo aceitavel */
      if (miniL != 0) {
        matriz[linha][coluna].absMin = matriz[linha][coluna].val + miniL;
      } else {
        matriz[linha][coluna].absMin = matriz[linha][coluna].val + miniU;
      }
    } else if (validAns == 2) {
      /* neste caso temos 2 minimos possiveis */
      if (miniL < miniU) {
        /* vou pela esquerda */
        matriz[linha][coluna].absMin = matriz[linha][coluna].val + miniL;
      } else {
        /* neste caso vou por cima */
        matriz[linha][coluna].absMin = matriz[linha][coluna].val + miniU;
      }
    }
  }
}
/* se chega aqui e porque a funcao correu sem erros */
return 1;
}
/******************************************************************************/
int preencherMinimoDownRight (dados **matriz, int dimMax) {
/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
if (matriz == NULL || dimMax <= 0) {
  return 0;
}
int linha, coluna, posL, posU, miniL, miniU, validAns, newMin, alteracao = 1;

for (linha = 0; linha < dimMax; linha++) {
  for (coluna = 0; coluna < dimMax; coluna++) {
    /* vamos agora processar os restantes valores das restantes colunas */
    validAns = 0;
    miniL = 0;
    miniU = 0;
    posL = coluna-1;
    posU = linha-1;
    /* teste valor a esquerda */
    if (posL >= 0) {
      validAns++;
      miniL = matriz[linha][posL].absMin;
    }
    /* teste valor cima */
    if (posU >= 0) {
      validAns++;
      miniU = matriz[posU][coluna].absMin;
    }
    /* teste de qual o minimo a incluir na memoria */
    if (validAns == 1) {
      /* apenas ha um minimo aceitavel */
      if (miniL != 0) {
				newMin = matriz[linha][coluna].val + miniL;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      } else {
				newMin = matriz[linha][coluna].val + miniU;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
	    	}
      }
    } else if (validAns == 2) {
      /* neste caso temos 2 minimos possiveis */
      if (miniL < miniU) {
        /* vou pela esquerda */
				newMin = matriz[linha][coluna].val + miniL;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      } else {
        /* neste caso vou por cima */
				newMin = matriz[linha][coluna].val + miniU;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
	    	}
      }
    }
  }
}
/* se chega aqui e porque a funcao correu sem erros */
return alteracao;
}
/******************************************************************************/
int preencherMinimoDownLeft (dados **matriz, int dimMax) {
/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
if (matriz == NULL || dimMax <= 0) {
  return 0;
}
int linha, coluna, posL, posU, miniL, miniU, validAns, newMin, alteracao = 1;

/* agora ja e preciso fazer alteracoes aos minimos absolutos */
for (linha = 0; linha < dimMax; linha++) {
  for (coluna = 0; coluna < dimMax; coluna++) {
    /* vamos agora processar os restantes valores das restantes colunas */
    validAns = 0;
    miniL = 0;
    miniU = 0;
    posL = coluna+1;
    posU = linha-1;
    /* teste valor a esquerda */
    if (posL < dimMax) {
      validAns++;
      miniL = matriz[linha][posL].absMin;
    }
    /* teste valor cima */
    if (posU >= 0) {
      validAns++;
      miniU = matriz[posU][coluna].absMin;
    }
    /* teste de qual o minimo a incluir na memoria */
    if (validAns == 1) {
      /* apenas ha um minimo aceitavel */
      if (miniL != 0) {
				newMin = matriz[linha][coluna].val + miniL;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      } else {
				newMin = matriz[linha][coluna].val + miniU;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
      	}
			}
    } else if (validAns == 2)  {
      /* neste caso temos 2 minimos possiveis */
      if (miniL < miniU) {
        /* vou pela esquerda */
				newMin = matriz[linha][coluna].val + miniL;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      } else {
        /* neste caso vou por cima */
				newMin = matriz[linha][coluna].val + miniU;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
	    	}
      	}
    	}
	}
}
/* se chega aqui e porque a funcao correu sem erros */
return alteracao;
}
/******************************************************************************/
int preencherMinimoUpLeft (dados **matriz, int dimMax) {
/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
if (matriz == NULL || dimMax <= 0) {
  return 0;
}
/* agora ja e preciso fazer alteracoes aos minimos absolutos */
int linha, coluna, posL, posD, miniL, miniD, validAns, newMin, alteracao = 1;

for (linha = dimMax-1; linha > -1; linha--) {
  for (coluna = dimMax-1; coluna > -1; coluna--) {
    /* vamos agora processar os restantes valores das restantes colunas */
    validAns = 0;
    miniL = 0;
    miniD = 0;
    posL = coluna+1;
    posD = linha+1;
    /* teste valor a esquerda */
    if (posL < dimMax) {
      validAns++;
      miniL = matriz[linha][posL].absMin;
    }
    /* teste valor cima */
    if (posD < dimMax) {
      validAns++;
      miniD = matriz[posD][coluna].absMin;
    }
    /* teste de qual o minimo a incluir na memoria */
    if (validAns == 1) {
      /* apenas ha um minimo aceitavel */
      if (miniL != 0) {
        newMin = matriz[linha][coluna].val + miniL;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      } else {
				newMin = matriz[linha][coluna].val + miniD;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      }
    } else if (validAns == 2) {
      /* neste caso temos 2 minimos possiveis */
      if (miniL < miniD) {
        /* vou pela esquerda */
				newMin = matriz[linha][coluna].val + miniL;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      } else {
        /* neste caso vou por cima */
				newMin = matriz[linha][coluna].val + miniD;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      }
    }
  }
}
/* se chega aqui e porque a funcao correu sem erros */
return alteracao;
}
/******************************************************************************/
int preencherMinimoUpRight (dados **matriz, int dimMax) {
/* esta funcao preenche os minimos para cada uma das posicoes da matriz e depois,
retorna 1 se tiver executado com sucesso mas sem actualizacao de maximo,
retorna 2 se tiver executado com sucesso e houver actualizacao de maximo ou 0
se houver um erro de execucao do programa */
if (matriz == NULL || dimMax <= 0) {
  return 0;
}
/* agora ja e preciso fazer alteracoes aos minimos absolutos */
int linha, coluna, posL, posD, miniL, miniD, validAns, newMin, alteracao = 1;

for (linha = 0; linha < dimMax; linha++) {
  for (coluna = 0; coluna < dimMax; coluna++) {
    /* vamos agora processar os restantes valores das restantes colunas */
    validAns = 0;
    miniL = 0;
    miniD = 0;
    posL = coluna-1;
    posD = linha+1;
    /* teste valor a esquerda */
    if (posL >= 0) {
      validAns++;
      miniL = matriz[linha][posL].absMin;
    }
    /* teste valor cima */
    if (posD < dimMax) {
      validAns++;
      miniD = matriz[posD][coluna].absMin;
    }
    /* teste de qual o minimo a incluir na memoria */
    if (validAns == 1) {
      /* apenas ha um minimo aceitavel */
      if (miniL != 0) {
        newMin = matriz[linha][coluna].val + miniL;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      } else {
				newMin = matriz[linha][coluna].val + miniD;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      }
    } else if (validAns == 2){
      /* neste caso temos 2 minimos possiveis */
      if (miniL < miniD) {
        /* vou pela esquerda */
				newMin = matriz[linha][coluna].val + miniL;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      } else {
        /* neste caso vou por cima */
				newMin = matriz[linha][coluna].val + miniD;
				if (newMin < matriz[linha][coluna].absMin) {
					matriz[linha][coluna].absMin = newMin;
					alteracao = 2;
				}
      }
    }
  }
}
/* se chega aqui e porque a funcao correu sem erros */
return alteracao;
}
/******************************************************************************/
