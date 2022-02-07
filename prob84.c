#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXDADO 4
#define NCASAS 40
#define HITS 100000
typedef struct {
	int nomeCasa; /* define o nome da casa */
	int contDefPerm;  /* este campo conta o valor das permanencias em cada casa,
										sem que tenha havido troca de posicao, depois de chegar a
										casa */
} casa;

/* esta funcao retorna 1 se tiver sido realizada com sucesso ou 0 se não tiver
sido realizada com sucesso, gera 2 valores aleatorios para os dados, sabendo que
o maximo valor do dado pode ser maxValue */
int dadoGerador (int *dado1Ap, int *dado2Ap, int maxValue);

/* esta funcao retorna a posicao final depois de sair valorDados e sabendo que
o jogador esta na posInicial e o tabuleiro tem nCasas */
int posTabuleiroCalc (int posInicial, int nCasas, int valorDados);

/* esta funcao retorna 0 se nao houver double ou 1 se tiver havido um double */
int booleanoDouble (int dado1, int dado2);

/* esta funcao calcula a nova posicao do tabuleiro de acordo com a actual
posicao do tabuleiro e de acordo com a communityChest actual e retorna esse
valor */
int posTabuleiroCommunityChest (int posTabuleiro, int communityChest);

/* esta funcao calcula a nova posicao do tabuleiro de acordo com a actual
posicao do tabuleiro e de acordo com a chance pile actual e retorna esse
valor */
int posTabuleiroChance (int posTabuleiro, int chance);

/* esta funcao faz a ordenacao por bubble sort do tabuleiro atraves do criaterio
contDefPerm */
void bubbleSortTabuleiroMonopoly (casa *tabuleiro, int numeroCasas);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int dado1, dado2, booleano, i, contador = 0, posTabuleiro = 0, valorDados;
int nDoubles = 0, communityChest = 1, chance = 1;
casa tabuleiro [NCASAS];

srand (time(NULL));
/* inicializacao do tabuleiro */
for (i = 0; i < NCASAS; i++) {
	tabuleiro[i].nomeCasa = i;
	tabuleiro[i].contDefPerm = 0;
}
while (contador < HITS) {
	booleano = dadoGerador (&dado1, &dado2, MAXDADO);
	if (booleano == 0) {
		printf ("\nOcorreu um erro na funcao dadoGerador.");
		return 0;
	}
	booleano = booleanoDouble (dado1, dado2);
	if (booleano == 1) {
		nDoubles++;
	} else {
		nDoubles = 0;
	}
	/* situacao em que ha double */
	if (nDoubles == 3) {
		posTabuleiro = 10;
		tabuleiro[posTabuleiro].contDefPerm++;
		contador++;
		continue;
	}
	/* situacao em que nao ha double */
	valorDados = dado1 + dado2;
	posTabuleiro = posTabuleiroCalc (posTabuleiro, NCASAS, valorDados);
	/* situacoes especiais, caso 1: GTJ */
	if (posTabuleiro == 30) {
		posTabuleiro = 10;
	}
	/* situacao especial, caso 2: caixa comunidade */
	if (posTabuleiro == 2 || posTabuleiro == 17 || posTabuleiro == 33) {
		posTabuleiro = posTabuleiroCommunityChest (posTabuleiro, communityChest);
		communityChest++;
		if (communityChest == 17) {
			/* reset of the community chest pile */
			communityChest = 1;
		}
	}
	/* situacao especial, caso 3: sorte */
	if (posTabuleiro == 7 || posTabuleiro == 22 || posTabuleiro == 36) {
		posTabuleiro = posTabuleiroChance (posTabuleiro, chance);
		chance++;
		if (chance == 16) {
			/* reset of the chance pile */
			chance = 1;
		}
	}
	/* comparacao de posicoes */
	tabuleiro[posTabuleiro].contDefPerm++;
	contador++;
}
bubbleSortTabuleiroMonopoly (tabuleiro, NCASAS);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nThe 6 digit modal string com o dado de 4 faces e: ");
if (tabuleiro[0].nomeCasa < 10) {
	printf ("0%d", tabuleiro[0].nomeCasa);
} else {
	printf ("%d", tabuleiro[0].nomeCasa);
}
if (tabuleiro[1].nomeCasa < 10) {
	printf ("0%d", tabuleiro[1].nomeCasa);
} else {
	printf ("%d", tabuleiro[1].nomeCasa);
}
if (tabuleiro[2].nomeCasa < 10) {
	printf ("0%d", tabuleiro[2].nomeCasa);
} else {
	printf ("%d", tabuleiro[2].nomeCasa);
}
printf ("\n");
return 0;
}
/******************************************************************************/
int dadoGerador (int *dado1Ap, int *dado2Ap, int maxValue) {
/* esta funcao retorna 1 se tiver sido realizada com sucesso ou 0 se não tiver
sido realizada com sucesso, gera 2 valores aleatorios para os dados, sabendo que
o maximo valor do dado pode ser maxValue */
if (dado1Ap == NULL || dado2Ap == NULL) {
	return 0;
}
*dado1Ap = (rand() % maxValue) + 1;
*dado2Ap = (rand() % maxValue) + 1;
return 1;
}
/******************************************************************************/
int posTabuleiroCalc (int posInicial, int nCasas, int valorDados){
/* esta funcao retorna a posicao final depois de sair valorDados e sabendo que
o jogador esta na posInicial e o tabuleiro tem nCasas */
int contador, posTabuleiro = posInicial;
for (contador = 0; contador < valorDados; contador++) {
	posTabuleiro++;
	if (posTabuleiro >= nCasas) {
		posTabuleiro = 0;
	}
}
return posTabuleiro;
}
/******************************************************************************/
int booleanoDouble (int dado1, int dado2) {
/* esta funcao retorna 0 se nao houver double ou 1 se tiver havido um double */
if (dado1 == dado2) {
	return 1;
} else {
	return 0;
}
}
/******************************************************************************/
int posTabuleiroCommunityChest (int posTabuleiro, int communityChest) {
/* esta funcao calcula a nova posicao do tabuleiro de acordo com a actual
posicao do tabuleiro e de acordo com a communityChest actual e retorna esse
valor */
if (communityChest == 1) {
	return 0;
} else if (communityChest == 2) {
	return 10;
} else {
	return posTabuleiro;
}
}
/******************************************************************************/
int posTabuleiroChance (int posTabuleiro, int chance) {
/* esta funcao calcula a nova posicao do tabuleiro de acordo com a actual
posicao do tabuleiro e de acordo com a chance pile actual e retorna esse
valor */
int i;

if (chance == 1) {
	return 0;
} else if (chance == 2) {
	return 10;
} else if (chance == 3) {
	return 11;
} else if (chance == 4) {
	return 24;
} else if (chance == 5) {
	return 39;
} else if (chance == 6) {
	return 5;
} else if (chance == 7 || chance == 8) {
	/* go to the next railway station */
	if (posTabuleiro == 7) {
		/* CH1 */
		return 15;
	} else if (posTabuleiro == 22) {
		/* CH2 */
		return 25;
	} else {
		/* CH3 */
		return 5;
	}
} else if (chance == 9) {
	/* go to next U (utility station */
	if (posTabuleiro == 7 || posTabuleiro == 36) {
		/* U1 */
		return 12;
	} else {
		/* U2 */
		return 28;
	}
} else if (chance == 10) {
	/* go back 3 squares */
	for (i = 0; i < 3; i++) {
		posTabuleiro--;
		if (posTabuleiro == -1) {
			posTabuleiro = 0;
		}
	}
} else {
	/* chance entre 11 e 16 */
	return posTabuleiro;
}
}
/******************************************************************************/
void bubbleSortTabuleiroMonopoly (casa *tabuleiro, int numeroCasas) {
/* esta funcao faz a ordenacao por bubble sort do tabuleiro atraves do criaterio
contDefPerm */
int i, j, auxCasa, auxCont;
for (i = 0; i < numeroCasas-1; i++) {
	for (j = i+1; j < numeroCasas; j++) {
		if (tabuleiro[i].contDefPerm < tabuleiro[j].contDefPerm) {
			/* aux = i */
			auxCasa = tabuleiro[i].nomeCasa;
			auxCont = tabuleiro[i].contDefPerm;
			/* i = j */
			tabuleiro[i].nomeCasa = tabuleiro[j].nomeCasa;
			tabuleiro[i].contDefPerm = tabuleiro[j].contDefPerm;
			/* j = aux */
			tabuleiro[j].nomeCasa = auxCasa;
			tabuleiro[j].contDefPerm = auxCont;
		}
	}
}
return;
}
/******************************************************************************/
