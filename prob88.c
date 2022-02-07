#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabdispersao.h"
#define MAXK 12000
#define MAX 2*MAXK
#define SIZEC 10
typedef struct {
	int k;
	int mps;
} pSumN;

/* esta funcao calcula a soma de minimal product sum  para 2 <= k <= maxK */
int somaCalc (pSumN *v, int maxK);

/* esta funcao calcula o mps de acordo com o indice */
int mpsCalc (int *indice, int dim);

/* esta funcao calcula o ms de acordo com o indice */
int msCalc (int *indice, int dim);

/* faz a insercao na tabela se não existir o elemento, somando nesse caso a
resposta, devolve a soma dos valores nao repetidos */
int encontraSoma (pSumN *v, tabela_dispersao *td, int dim);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int i, nF, *indice, maxIndice, nFactor, mps, kteste, ms, soma, mpsOld[14], msOld[14], dim, booleano;
pSumN *v;
tabela_dispersao *td;

dim = MAXK - 1;
td = tabela_nova(dim, hash_djbm);
if (td == NULL) {
	printf ("\nOcorreu uma falha a criar a tabela de dispersao.");
	return 0;
}


/* vou agora gerar o vector inicial */
v = (pSumN*) calloc (dim, sizeof (pSumN));
if (v == NULL) {
	printf ("\nOcorreu uma falha na criacao do vector.");
	return 0;
}
/* preenchimento inicial do vector */
for (i = 0; i < dim; i++) {
	v[i].k = i+2;
	v[i].mps = 2*v[i].k;
}
/* vamos agora gerar todas as possiveis factorizacoes ate mps = 2k */
nF = (int)log2 (2*MAXK);
indice = (int*) calloc (nF, sizeof(int));
if (indice == NULL) {
	printf ("\nFalhou a criação do vector indices.");
	return 0;
}
maxIndice = MAXK; /* no minimo iremos ter 2 factores */
/* inicializacao dos indices */
for (i = 0; i < nF; i++) {
	indice[i] = 1;
}

for (indice[0] = 1; indice[0] < maxIndice+1; indice[0]++) {
	printf ("\nindice[0] = %d", indice[0]);
	fflush (stdout);
	for (i = 0; i < 14; i++) {
		mpsOld[i] = 0;
		msOld[i] = 0;
	}
	mps = indice[0];
	ms = indice[0];
	mpsOld[0] = indice[0];
	msOld[0] = indice[0];
	for (indice[1] = 1; indice[1] < maxIndice+1; indice[1]++) {
		/* teste a 2 factores */
		mps = mpsOld[0]*indice[1];
		ms = msOld[0]+indice[1];
		mpsOld[1] = mps;
		msOld[1] = ms;
		if (mps > MAX) {
			break;
		}
		kteste = 2 + mps - ms;
		if (kteste > MAXK) {
			break;
		}
		if (v[kteste-2].mps > mps ) {
			/* actualizacao do valor de mps */
			v[kteste-2].mps = mps;
		}

		for (indice[2] = 1; indice[2] < maxIndice+1; indice[2]++) {
			/* teste a 3 factores */
			mps = mpsOld[1]*indice[2];
			ms = msOld[1]+indice[2];
			mpsOld[2] = mps;
			msOld[2] = ms;
			if (mps > MAX) {
				break;
			}
			kteste = 3 + mps - ms;
			if (kteste > MAXK) {
				break;
			}
			if (v[kteste-2].mps > mps) {
				/* actualizacao do valor de mps */
				v[kteste-2].mps = mps;
			}

			for (indice[3] = 1; indice[3] < maxIndice+1; indice[3]++) {
				/* teste a 4 factores */
				mps = mpsOld[2]*indice[3];
				ms = msOld[2]+indice[3];
				mpsOld[3] = mps;
				msOld[3] = ms;
				if (mps > MAX) {
					break;
				}
				kteste = 4 + mps - ms;
				if (kteste > MAXK) {
					break;
				}
				if (v[kteste-2].mps > mps) {
					/* actualizacao do valor de mps */
					v[kteste-2].mps = mps;
				}

				for (indice[4] = 1; indice[4] < maxIndice+1; indice[4]++) {
					/* teste a 5 factores */
					mps = mpsOld[3]*indice[4];
					ms = msOld[3]+indice[4];
					mpsOld[4] = mps;
					msOld[4] = ms;
					if (mps > MAX) {
						break;
					}
					kteste = 5 + mps - ms;
					if (kteste > MAXK) {
						break;
					}
					if (v[kteste-2].mps > mps) {
						/* actualizacao do valor de mps */
						v[kteste-2].mps = mps;
					}

					for (indice[5] = 1; indice[5] < maxIndice+1; indice[5]++) {
						/* teste a 6 factores */
						mps = mpsOld[4]*indice[5];
						ms = msOld[4]+indice[5];
						mpsOld[5] = mps;
						msOld[5] = ms;
						if (mps > MAX) {
							break;
						}
						kteste = 6 + mps - ms;
						if (kteste > MAXK) {
							break;
						}
						if (v[kteste-2].mps > mps) {
							/* actualizacao do valor de mps */
							v[kteste-2].mps = mps;
						}
						for (indice[6] = 1; indice[6] < maxIndice+1; indice[6]++) {
							/* teste a 7 factores */
							mps = mpsOld[5]*indice[6];
							ms = msOld[5]+indice[6];
							mpsOld[6] = mps;
							msOld[6] = ms;
							if (mps > MAX) {
								break;
							}
							kteste = 7 + mps - ms;
							if (kteste > MAXK) {
								break;
							}
							if (v[kteste-2].mps > mps) {
								/* actualizacao do valor de mps */
								v[kteste-2].mps = mps;
							}

							for (indice[7] = 1; indice[7] < maxIndice+1; indice[7]++) {
								/* teste a 8 factores */
								mps = mpsOld[6]*indice[7];
								ms = msOld[6]+indice[7];
								mpsOld[7] = mps;
								msOld[7] = ms;
								if (mps > MAX) {
									break;
								}
								kteste = 8 + mps - ms;
								if (kteste > MAXK) {
									break;
								}
								if (v[kteste-2].mps > mps) {
									/* actualizacao do valor de mps */
									v[kteste-2].mps = mps;
								}

								for (indice[8] = 1; indice[8] < maxIndice+1; indice[8]++) {
									/* teste a 9 factores */
									mps = mpsOld[7]*indice[8];
									ms = msOld[7]+indice[8];
									mpsOld[8] = mps;
									msOld[8] = ms;
									if (mps > MAX) {
										break;
									}
									kteste = 9 + mps - ms;
									if (kteste > MAXK) {
										break;
									}
									if (v[kteste-2].mps > mps) {
										/* actualizacao do valor de mps */
										v[kteste-2].mps = mps;
									}

									for (indice[9] = 1; indice[9] < maxIndice+1; indice[9]++) {
										/* teste a 10 factores */
										mps = mpsOld[8]*indice[9];
										ms = msOld[8]+indice[9];
										mpsOld[9] = mps;
										msOld[9] = ms;
										if (mps > MAX) {
											break;
										}
										kteste = 10 + mps - ms;
										if (kteste > MAXK) {
											break;
										}

										if (v[kteste-2].mps > mps) {
											/* actualizacao do valor de mps */
											v[kteste-2].mps = mps;
										}
										for (indice[10] = 1; indice[10] < maxIndice+1; indice[10]++) {
											/* teste a 11 factores */
											mps = mpsOld[9]*indice[10];
											ms = msOld[9]+indice[10];
											mpsOld[10] = mps;
											msOld[10] = ms;
											if (mps > MAX) {
												break;
											}
											kteste = 11 + mps - ms;
											if (kteste > MAXK) {
												break;
											}
											if (v[kteste-2].mps > mps) {
												/* actualizacao do valor de mps */
												v[kteste-2].mps = mps;
											}

											for (indice[11] = 1; indice[11] < maxIndice+1; indice[11]++) {
												/* teste a 12 factores */
												mps = mpsOld[10]*indice[11];
												ms = msOld[10]+indice[11];
												mpsOld[11] = mps;
												msOld[11] = ms;
												if (mps > MAX) {
													break;
												}
												kteste = 12 + mps - ms;
												if (kteste > MAXK) {
													break;
												}
												if (v[kteste-2].mps > mps) {
													/* actualizacao do valor de mps */
													v[kteste-2].mps = mps;
												}

												for (indice[12] = 1; indice[12] < maxIndice+1; indice[12]++) {
													/* teste a 13 factores */
													mps = mpsOld[11]*indice[12];
													ms = msOld[11]+indice[12];
													mpsOld[12] = mps;
													msOld[12] = ms;
													if (mps > MAX) {
														break;
													}
													kteste = 13 + mps - ms;
													if (kteste > MAXK) {
														break;
													}
													if (v[kteste-2].mps > mps) {
														/* actualizacao do valor de mps */
														v[kteste-2].mps = mps;
													}

													for (indice[13] = 1; indice[13] < maxIndice+1; indice[13]++) {
														/* teste a 14 factores */
														mps = mpsOld[12]*indice[13];
														ms = msOld[12]+indice[13];
														mpsOld[13] = mps;
														msOld[13] = ms;
														if (mps > MAX) {
															break;
														}
														kteste = 14 + mps - ms;
														if (kteste > MAXK) {
															break;
														}
														if (v[kteste-2].mps > mps) {
															/* actualizacao do valor de mps */
															v[kteste-2].mps = mps;
														}
													}
												}
											}
										}
									}
								}
							}
						}

					}
				}
			}
		}
	}
}
/* vamos agora calcular a resposta, a soma */
soma = encontraSoma (v, td, dim);
if (soma == 0) {
	printf ("\nOcorreu um erro no calculo da soma.");
	return 0;
}
booleano = tabela_esvazia(td);
if (booleano == TABDISPERSAO_INVALIDA) {
	printf ("\nOcorreu um erro a esvaziar a tabela de dispersao.");
}
/* libertacao da memoria usada */
printf ("\nA soma dos product sum number para k entre 2 e %d e de %d.", MAXK, soma);
fflush (stdout);
free (v);
free (indice);
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nA soma dos product sum number para k entre 2 e %d e de %d.", MAXK, soma);
printf ("\n");
return 0;
}
/******************************************************************************/
int somaCalc (pSumN *v, int maxK) {
/* esta funcao calcula a soma de minimal product sum  para 2 <= k <= maxK */
int soma = 0, i;
for (i = 0; i < maxK; i++) {
	if (i <= 12-2) {
		printf ("\nO product sum de k = %d e de %d", v[i].k, v[i].mps);
	}
	soma = soma + v[i].mps;
}
return soma;
}
/******************************************************************************/
int mpsCalc (int *indice, int dim) {
/* esta funcao calcula o mps de acordo com o indice */
int i, mps = 1;
for (i = 0; i < dim; i++) {
	mps = mps * indice[i];
}
return mps;
}
/******************************************************************************/
int msCalc (int *indice, int dim) {
/* esta funcao calcula o ms de acordo com o indice */
int i, ms = 0;
for (i = 0; i < dim; i++) {
	ms = ms + indice[i];
}
return ms;
}
/******************************************************************************/
int encontraSoma (pSumN *v, tabela_dispersao *td, int dim) {
/* faz a insercao na tabela se não existir o elemento, somando nesse caso a
resposta, devolve a soma dos valores nao repetidos */
char *str;
int psNum, i, soma = 0, booleano;
for (i = 0; i < dim; i++) {
	str = (char*) calloc (SIZEC, sizeof (char));
	if (str == NULL) {
		printf ("\nOcorreu um erro a criar o vector str.");
		return 0;
	}
	sprintf(str, "%d", v[i].mps);
	booleano = tabela_existe(td, str);
	if (booleano == TABDISPERSAO_NAOEXISTE) {
		/*printf ("\nVou somar %d.", esquerda);*/
		soma = soma + v[i].mps;
		booleano = tabela_insere(td, str, str);
		if (booleano == TABDISPERSAO_ERRO) {
			printf ("\nOcorreu um erro na insercao na tabela.");
			return 0;
		}
	}
	free (str);
}
return soma;
}
/******************************************************************************/
